#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#include "krffs_file_system.h"
#include "krffs_node.h"
#include "krffs_platform.h"

#ifdef WINDOWS
#include <io.h>
#else

#include <unistd.h>

#endif

/*
    Name of the program to check the file system.
 */
#define KRFFS_FILE_SYSTEM_CHECK_UTILITY_NAME "./fsck.krffs "

/*
    The size of buffer to store a command.
 */
#define KRFFS_COMMAND_BUFFER_LENGTH 1024

/*
    defrag.krffs
    Defragments a KRFFS FUSE file system in a file.
    Usage:
        defrag.krffs -h
        defrag.krffs <file>
    Options:
        -h    show help and exit
 */
int main(int argc, char **argv) {
    int exit_status = EXIT_SUCCESS;

    int file_descriptor = -1;
    struct krffs_file_system file_system = {
            .node = NULL
    };

    bool has_help_option = false;
    for (int i = 1; i < argc; ++i) {
        if (strncmp(argv[i], "-h", 2) == 0) {
            has_help_option = true;
            break;
        }
    }

    if (argc <= 1 || has_help_option) {
        fprintf(
                stderr,
                "Usage: %s <file>\n",
                argc >= 1 ?
                argv[0] : "defrag.krffs"
        );

        goto cleanup;
    } else if (argv[1][0] == '-') {
        fprintf(
                stderr,
                "The first parameter is invalid.\n"
                "\n"
                "Usage: %s <file>\n",
                argc >= 1 ?
                argv[0] : "defrag.krffs"
        );

        exit_status =
                EXIT_FAILURE;

        goto cleanup;
    }

    char *path = argv[1];

    /*
        Ensure that the file system is valid by calling the file
        system check utility.

        You can remove this check, if you don't have a working
        `fsck.krffs`.
     */
    char command_buffer[KRFFS_COMMAND_BUFFER_LENGTH + 1];
    command_buffer[KRFFS_COMMAND_BUFFER_LENGTH] = '\0';

    size_t command_length =
            strlen(KRFFS_FILE_SYSTEM_CHECK_UTILITY_NAME);

    strncpy(
            command_buffer,
            KRFFS_FILE_SYSTEM_CHECK_UTILITY_NAME,
            KRFFS_COMMAND_BUFFER_LENGTH
    );
    strncat(
            command_buffer,
            path,
            KRFFS_COMMAND_BUFFER_LENGTH -
            command_length
    );

    int fsck_result =
            system(command_buffer);

    if (fsck_result == -1 &&
        fsck_result == 127) {
        command_length =
                strlen("./"KRFFS_FILE_SYSTEM_CHECK_UTILITY_NAME);

        strncpy(
                command_buffer,
                "./"KRFFS_FILE_SYSTEM_CHECK_UTILITY_NAME,
                KRFFS_COMMAND_BUFFER_LENGTH
        );
        strncat(
                command_buffer,
                path,
                KRFFS_COMMAND_BUFFER_LENGTH -
                command_length
        );
        fsck_result =
                system(command_buffer);
    }

    if (fsck_result != 0) {
        fprintf(
                stderr,
                "Failed check the file system file at '%s'.\n",
                path
        );

        exit_status = EXIT_FAILURE;

        goto cleanup;
    }

    /*
        Open the file with the file system.
     */
    if ((file_descriptor = PLATFORM_PREFIX(open(path, O_RDWR))) == -1) {
        fprintf(
                stderr,
                "Failed to open the file system file at '%s'.\n",
                path
        );

        exit_status =
                EXIT_FAILURE;

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

        exit_status =
                EXIT_FAILURE;

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

        exit_status =
                EXIT_FAILURE;

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

        exit_status =
                EXIT_FAILURE;

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
    if ((file_system.node =
                 krffs_map_file(file_descriptor, 0, file_system.size))
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

    /*
        Check that we have a KRFFS file system by checking the signature at the
        beginning of the file.
     */
    if (file_system.node->magic != KRFFS_File_System_Magic) {
        fprintf(
                stderr,
                "The file system was not found at '%s'. The file system was not "
                "created or the file is corrupted.\n",
                path
        );

        exit_status = EXIT_FAILURE;

        goto cleanup;
    }

    printf("\nDefragmentation program\n");

    // declare nodes
    struct krffs_node *node, *previous_node;
    node = file_system.node;

    // Check if file needs to be defragmented
    unsigned long free_nodes = krffs_count_free_nodes(&file_system);

    // initialize counters
    unsigned long count = 0;
    unsigned long max_contiguous_blocks = 0;

    // loop over the nodes to find the highest number of consecutive reserved
    // nodes for future use
    do {
        switch (node->type) {
            // count consecutive reserved nodes after first free node
            case KRFFS_Reserved_Node:
                ++count;
                break;
                // find the largest number of consecutive reserved blocks
            case KRFFS_Free_Node:
                max_contiguous_blocks =
                        max_contiguous_blocks < count ?
                        count : max_contiguous_blocks;
                count = 0;
                break;
            default:
                break;
        }
        previous_node = node;
        node = krffs_get_next_node(&file_system, previous_node);
    } while (node != file_system.node);

    // if there is more than 1 free node or the last node is not free we need
    // to defrag
    bool needs_defrag =
            free_nodes != 1 || previous_node->type != KRFFS_Free_Node;

    // but not if there is no free space
    if (needs_defrag && free_nodes == 0) {
        needs_defrag = false;
    }

    /*
     * This defragmentation works as follows:
     * We loop through all nodes.
     *      - we save first free node we encounter
     *      - we save all following reserved nodes until the next free node (or
     *        root node in case there is no free node)
     *      - then the block of reserved nodes will be moved to the position of
     *        the first free node, defragmenting the file system
     *      - the resulting free space behind the block will be merged with
     *        the already existing free node to form one larger one
     *      - this process is continued until we reach the root node (the end)
     */

    // only defrag if it is necessary
    if (needs_defrag) {
        printf("Starting defragmentation...\n");

        // declare the necessary nodes
        struct krffs_node
                *next_node,
                *free_node;
        // declare array of reserved nodes to be moved at once
        struct krffs_node *reserved_nodes[max_contiguous_blocks];

        bool in_block = false;
        unsigned long index = 0;
        int root_node_count = 0;

        // initialize variables
        node = file_system.node;
        next_node = krffs_get_next_node(&file_system, node);

        // loop over all nodes and defragment
        do {
            switch (node->type) {
                // add all consecutive reserved nodes to the array
                case KRFFS_Reserved_Node:
                    if (in_block) {
                        reserved_nodes[index++] = node;
                    }
                    break;
                case KRFFS_Root_Node:
                    // check if this is the first root node and ignore it
                    if (++root_node_count > 1) {
                        // if we come out of a block of reserved nodes
                        if (in_block) {
                            in_block = false;

                            ssize_t chunk_size = 0;

                            // get size of the block of nodes to be copied
                            for (unsigned long i = 0; i < index; ++i) {
                                chunk_size += reserved_nodes[i]->size;
                            }

                            // find length of memory to be copied
                            uint64_t difference = reserved_nodes[0] - free_node;
                            // save previous size of free node for later use
                            uint64_t free_node_prev_size =
                                    free_node->previous_node_size;
                            // save size of free node for later use
                            uint64_t free_node_size = free_node->size;

                            // copy the block to the position of the free node
                            // preceding it, basically switch the position of the
                            // free block and the reserved blocks, defragmenting
                            // the fs
                            memcpy(free_node, reserved_nodes[0], chunk_size);

                            // update the pointers of the nodes
                            for (unsigned long i = 0; i < index; ++i) {
                                reserved_nodes[i] -= difference;
                            }

                            // update the previous node size of the first reserved
                            // node
                            reserved_nodes[0]->previous_node_size =
                                    free_node_prev_size;

                            // sync the mapping
                            krffs_sync_mapping(
                                    reserved_nodes[0],
                                    sizeof(*reserved_nodes[0])
                            );

                            // code more or less copied from krffs_allocator.c
                            // get the node following the last reserved node
                            struct krffs_node *following_node =
                                    krffs_get_next_node(
                                            &file_system,
                                            reserved_nodes[index - 1]
                                    );

                            // initialize that node as a free node
                            krffs_initialize_free_node(
                                    following_node,
                                    free_node_size,
                                    reserved_nodes[index - 1]->size
                            );

                            // update the node for the loop conditions
                            // this is the last node in the file system
                            node = following_node;

                            // get the node after the newly created free node
                            // this is the root node
                            following_node =
                                    krffs_get_next_node(
                                            &file_system,
                                            following_node
                                    );

                            // update that nodes previous node size
                            following_node->previous_node_size =
                                    free_node_size;

                            // sync the size change
                            krffs_sync_mapping(
                                    following_node,
                                    sizeof(*following_node)
                            );
                        }
                    }
                    break;
                case KRFFS_Free_Node:
                    // if we come out of a block of reserved nodes
                    if (in_block) {
                        in_block = false;

                        size_t chunk_size = 0;

                        // get size of the block of nodes to be copied
                        for (unsigned long i = 0; i < index; ++i) {
                            chunk_size += reserved_nodes[i]->size;
                        }

                        // find length of memory to be copied
                        uint64_t difference = reserved_nodes[0] - free_node;
                        // save previous size of free node for later use
                        uint64_t free_node_prev_size =
                                free_node->previous_node_size;
                        // save size of free node for later use
                        uint64_t free_node_size = free_node->size;

                        // copy the block to the position of the free node
                        // preceding it, basically switch the position of the
                        // free block and the reserved blocks, defragmenting
                        // the fs
                        memcpy(free_node, reserved_nodes[0], chunk_size);

                        // update the pointers of the nodes
                        for (unsigned long i = 0; i < index; ++i) {
                            reserved_nodes[i] -= difference;
                        }

                        // update the previous node size of the first reserved
                        // node
                        reserved_nodes[0]->previous_node_size =
                                free_node_prev_size;

                        // sync the mapping
                        krffs_sync_mapping(
                                reserved_nodes[0],
                                sizeof(*reserved_nodes[0])
                        );

                        // code more or less copied from krffs_allocator.c
                        // get the node following the last reserved node
                        struct krffs_node *following_node =
                                krffs_get_next_node(
                                        &file_system,
                                        reserved_nodes[index - 1]
                                );

                        // initialize that node as a free node, at the same
                        // time overriding the free node following it to create
                        // one large free node
                        krffs_initialize_free_node(
                                following_node,
                                free_node_size + node->size,
                                reserved_nodes[index - 1]->size
                        );

                        // update the node for the loop conditions
                        node = following_node;

                        // get the node after the newly created free node
                        following_node =
                                krffs_get_next_node(
                                        &file_system,
                                        following_node
                                );

                        // update that nodes previous node size 
                        following_node->previous_node_size =
                                free_node_size + node->size;

                        // sync the size change
                        krffs_sync_mapping(
                                following_node,
                                sizeof(*following_node)
                        );

                        // update the next_node for the loop
                        next_node = following_node;

                        // reset the reserved node index
                        index = 0;
                    }

                    // check if this free node is the first free node
                    if (!in_block && next_node->type == KRFFS_Reserved_Node) {
                        in_block = true;
                        free_node = node;
                    }
                    break;
                default:
                    break;
            }

            node = next_node;
            next_node = krffs_get_next_node(&file_system, node);
            // modified loop condition to allow the defragmentation to trigger if
            // the last node is not a free node
        } while (node != file_system.node || root_node_count <= 1);

        printf("Finished!\n");
        goto cleanup;
    } else {
        printf("No defragmentation necessary.\n");
        goto cleanup;
    }

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
        if (krffs_unmap_file(
                file_system.node,
                file_system.size
        ) == -1) {
            fprintf(
                    stderr,
                    "Failed to unmap the file system file.\n"
            );
        }
    }

    return exit_status;
}
