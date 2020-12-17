#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "krffs_file_system.h"
#include "krffs_node.h"
#include "krffs_platform.h"
#include "krffs_utilities.h"

#ifdef WINDOWS
#include <io.h>
#else

#include <unistd.h>

#endif

// error codes
static const int KRFFS_Invalid_Link_Error = -10,
        KRFFS_Out_of_Range_Node_Error = -11,
        KRFFS_Invalid_Magic_Signature_Error = -12,
        KRFFS_Unknown_Node_Type_Error = -13;

/*
    fsck.krffs
    Checks the consistency of a KRFFS file system in a file.
    Usage:
        fsck.krffs -h
        fsck.krffs <file>
    Options:
        -h    show help and exit
 */
int main(int argc, char **argv) {

    // set initial exit status
    int exit_status = EXIT_SUCCESS;

    // initialize file descriptor for file system
    int file_descriptor = -1;

    // initialize file system
    struct krffs_file_system file_system = {
            .node = NULL
    };

    // parse command line options
    bool has_help_option = false;
    for (int i = 1; i < argc; ++i) {
        if (strncmp(argv[i], "-h", 2) == 0) {
            has_help_option = true;
            break;
        }
    }

    // options are not correct, error out
    if (argc <= 1 || has_help_option) {
        fprintf(
                stderr,
                "Usage: %s <file>\n",
                argc >= 1 ?
                argv[0] : "fsck.krffs"
        );

        goto cleanup;
        // provide help if required
    } else if (argv[1][0] == '-') {
        fprintf(
                stderr,
                "The first parameter is invalid.\n"
                "\n"
                "Usage: %s <file>\n",
                argc >= 1 ?
                argv[0] : "fsck.krffs"
        );

        exit_status = EXIT_FAILURE;
        goto cleanup;
    }

    // get path of file system
    char *path = argv[1];

    printf("Performing file system check...\n");

    /*
        Open the file with the file system.
     */
    if ((file_descriptor = PLATFORM_PREFIX(open(path, O_RDWR))) == -1) {
        fprintf(
                stderr,
                "Failed to open the file system file at '%s'.\n",
                path
        );

        exit_status = EXIT_FAILURE;

        goto cleanup;
    }

    /*
        Get file information.
     */
    struct stat file_info;
    if (fstat(file_descriptor, &file_info) == -1) {
        fprintf(
                stderr,
                "Failed to get file information for '%s'.\n",
                path
        );

        exit_status = EXIT_FAILURE;

        goto cleanup;
    }

    /*
        Check that we have a regular file (not a directory or a socket).
     */
    if (!S_ISREG(file_info.st_mode)) {
        fprintf(
                stderr,
                "The file system file at '%s' is not a regular file.\n",
                path
        );

        exit_status = EXIT_FAILURE;

        goto cleanup;
    }

    /*
        Check that the file is big enough to contain a file system.
     */
    if (file_info.st_size < sizeof(*file_system.node) * 2) {
        fprintf(
                stderr,
                "The file at '%s' is not big enough to contain a file system.\n",
                path
        );

        exit_status = EXIT_FAILURE;

        goto cleanup;
    }

    /*
        Save the size of the file.
     */
    file_system.size = file_info.st_size;

    /*
        Map the file system file into memory. Changes to memory at
        `file_system.node` after a successful call to `krffs_map_file` will be
        written directly to a file (right away or after calls to
        `krffs_unmap_file` or `krffs_sync_mapping`).

        The kernel uses its virtual memory system to implement the memory
        mapping.
     */
    if (
            (file_system.node = krffs_map_file(file_descriptor, 0,
                                               file_system.size))
            == (void *) -1) {
        fprintf(
                stderr,
                "Failed to map the file system file at '%s' into memory.\n",
                path
        );

        exit_status = EXIT_FAILURE;

        goto cleanup;
    }

    /*
        It's possible to close the file after a call to `krffs_map_file`. Memory
        pages will still be mapped to the file.
     */
    if (PLATFORM_PREFIX(close(file_descriptor)) == -1) {
        fprintf(
                stderr,
                "Failed to close the file system file at '%s'.\n",
                path
        );

        exit_status =
                EXIT_FAILURE;

        goto cleanup;
    }
    file_descriptor = -1;

    // get root node for easier use
    struct krffs_node *root_node = file_system.node;

    /*
        Check that we have a KRFFS file system by checking the signature at the
        beginning of the file.
     */
    if (root_node->magic != KRFFS_File_System_Magic) {
        exit_status = KRFFS_Invalid_Magic_Signature_Error;

        fprintf(stderr, "Root node magic number mismatch.\n"
                        "Is %x, should be %x",
                root_node->magic, KRFFS_File_System_Magic);

        goto cleanup;
    }

    /*
        Check that we have a root node at the beginning of the file.
     */
    if (root_node->type != KRFFS_Root_Node ||
        root_node->id != krffs_calculate_djb_hash(
                (uint8_t *) KRFFS_File_System_Root_Node_Name)
            ) {
        exit_status = KRFFS_Unknown_Node_Type_Error;

        fprintf(stderr, "No root node at beginning of file.\n"
                        "Node type is %d, should be %d\n", root_node->type,
                KRFFS_Root_Node);

        goto cleanup;
    }

    /*
        Perform file system checks by going through each metadata node and
        analyzing it.

        The following checks are performed

            * Nodes' links are consecutive.                             XXX
            * Nodes' links are in the range of the file system space.   XXX
            * Nodes' signatures are valid.                              XXX
            * Nodes' types are either 'Reserved' or 'Free'.             XXX
            * The last node links to the first node.                    XXX

        The process prints debug information for each node. It can be silenced
        by redirecting the output to `> /dev/null`.

        Parent programs can get result of the analysis by reading the exit
        status.

        The following status codes are returned on error

            * Found a nonconsecutive link:                        -10
            * Found a link leading outside the file system space: -11
            * Found a node with an invalid signature:             -12
            * Found a node of an unknown type:                    -13
     */

    printf("Checking all nodes...\n");

    // declaring nodes
    struct krffs_node *node, *previous_node = 0;
    node = root_node;
    bool is_first_node = true;

    // initialize counters
    uint64_t free_space = 0, total_space = 0;
    uint64_t free_nodes = 0, total_nodes = 0;

    // header for the output table
    printf("Type     | Address        | Size bytes | Size MB\n");

    do {
        // Check the node type
        switch (node->type) {
            case KRFFS_Root_Node:
                printf("root     | ");
                if (!is_first_node) {
                    fprintf(stderr, "\nFound root node in middle of "
                                    "filesystem.\n"
                                    "Type is %d, should be either %d "
                                    "(reserved) or %d (free).\n", node->type,
                            KRFFS_Reserved_Node, KRFFS_Free_Node);

                    exit_status = KRFFS_Invalid_Link_Error;

                    goto cleanup;
                }
                is_first_node = false;
                break;
            case KRFFS_Free_Node:
                printf("free     | ");
                free_space += node->size;
                ++free_nodes;
                break;
            case KRFFS_Reserved_Node:
                printf("reserved | ");
                break;
            default:
                printf("unknown node\n");
                fprintf(stderr, "Unknown node found.\n"
                                "Type is %d, should be either %d "
                                "(reserved) or %d (free).\n", node->type,
                        KRFFS_Reserved_Node, KRFFS_Free_Node);

                exit_status = KRFFS_Unknown_Node_Type_Error;

                goto cleanup;
        }

        total_space += node->size;
        ++total_nodes;

        // Check if node is in file system
        if (!krffs_is_node_in_file_system(&file_system, node)) {
            exit_status = KRFFS_Out_of_Range_Node_Error;

            fprintf(stderr, "\nNode is not in file system.\n");

            goto cleanup;
        }

        // Check if node has a valid signature
        if (node->magic != KRFFS_File_System_Magic) {
            exit_status = KRFFS_Invalid_Magic_Signature_Error;

            fprintf(stderr, "\nNode magic number mismatch.\n"
                            "Is %x, should be %x",
                    node->magic, KRFFS_File_System_Magic);

            goto cleanup;
        }

        // Check if nodes are consecutive
        if (node <= previous_node) {
            exit_status = KRFFS_Invalid_Link_Error;

            fprintf(stderr, "Nodes are not consecutive in memory.\n");

            goto cleanup;
        }

        // print debug information
        printf("%p | ", node);
        printf("%10"PRIu64, node->size);
        printf(" | %8.1lf KB\n", (10.0 * node->size / 1024.0) / 10.0);

        // get the next node
        previous_node = node;
        node = krffs_get_next_node(&file_system, previous_node);

    } while (node != root_node);

    // Check if the final node is the root node again
    if (node != root_node || node->type != KRFFS_Root_Node ||
        node >= previous_node) {
        exit_status = KRFFS_Invalid_Link_Error;

        fprintf(stderr, "Last node does not link to root node.\n");

        goto cleanup;
    }

    // print diagnostic summary
    printf("\nDone! No errors found.\nFile System Summary\n");
    printf("\nTotal space: %12"PRIu64, total_space);
    printf(" %8.1lf KB\n", (10 * total_space / 1024.0) / 10.0);
    printf("Used space:  %12"PRIu64, total_space - free_space);
    printf(" %8.1lf KB\n", (10 * (total_space - free_space) / 1024.0) / 10.0);
    printf("Free space:  %12"PRIu64, free_space);
    printf(" %8.1lf KB\n", (10 * free_space / 1024.0) / 10.0);
    printf("Free space (%%): %9.1lf\n", 100.0 * free_space / total_space);
    printf("\nTotal nodes: %4"PRIu64"\n", total_nodes);
    printf("Used nodes:  %4"PRIu64"\n", total_nodes - free_nodes);
    printf("Free nodes:  %4"PRIu64"\n", free_nodes);

    // Check if there is only 1 free node and that that node is last
    bool needs_defrag =
            free_nodes != 1 || previous_node->type != KRFFS_Free_Node;
    // but not if there is no free space
    if (needs_defrag && free_nodes == 0) {
        needs_defrag = false;
    }

    printf("\nNeeds defragmentation: %s\n", needs_defrag ? "yes" : "no");

    cleanup:
    if (file_descriptor != -1) {
        if (PLATFORM_PREFIX(close(file_descriptor)) == -1) {
            fprintf(
                    stderr,
                    "Failed to close the file system file.\n"
            );
        }
    }

    if (file_system.node != NULL) {
        if (krffs_unmap_file(file_system.node, file_system.size) == -1) {
            fprintf(
                    stderr,
                    "Failed to unmap the file system file.\n"
            );
        }
    }

    return exit_status;
}
