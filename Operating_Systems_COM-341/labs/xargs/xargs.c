/*
 * Much of this code has been copied from our project 1 part 2
 * https://github.com/toksaitov/syscall-project/blob/master/ish/ish.c
 * It has been adapted for xargs
 */

#include "string_utils.h"
#include "syscalls.h"
#include "command_line_utils.h"

static const unsigned long Max_Input_String_Length = 255;
static const unsigned long Max_Argument_Count = 255;
static const unsigned long Max_Executable_Path_Length = 1024;

static const char Environment_Variable_Path[] = "PATH";
static const char Fork_Error_Message[] = "fork failure\n";

int main(int argc, char **argv, char **envp) {

    // get the executable paths
    char *paths = ish_get_first_environment_variable(
            Environment_Variable_Path,
            sizeof(Environment_Variable_Path),
            envp);

    // prepare an argument list
    char *arguments[argc + 1];
    arguments[argc] = 0;

    // transfer the arguments from argv
    for (int i = 0; i < argc; ++i) {
        arguments[i] = argv[i + 1];
    }

    // get number of arguments excluding program name
    int argument_count = argc - 1;

    // get the command to be run by xargs
    const char *command = arguments[0];

    // if no command has been given use echo
    if (!command) {
        arguments[0] = "echo";
        argument_count = 1;
    }

    // find the executable path
    char *executable = arguments[0];

    char candidate[Max_Executable_Path_Length + 1];
    candidate[Max_Executable_Path_Length] = '\0';

    char stat_result[256];

    if (stat(executable, stat_result) != 0) {
        executable = 0;
        for (char *cursor = paths; cursor && !executable;) {
            char *path = ish_get_token_in_cstring(cursor,
                                                  ish_is_path_separator,
                                                  &cursor);

            if (path) {
                ish_combine_path_elements(path, arguments[0], candidate,
                                          Max_Executable_Path_Length);

                if (stat(candidate, stat_result) == 0) {
                    executable = candidate;
                }
            }
        }
    }

    if (!executable) {
        return -1;
    }

    // prepare a string for the arguments supplied at each user input loop
    char args[Max_Input_String_Length + 1];
    args[Max_Input_String_Length] = '\0';

    // while the user enters commands
    while (read(0, args, Max_Input_String_Length) >= 0) {

        // the argument processing is done as in the original source and above
        ish_replace_first_character_in_cstring(args, '\n', '\0');

        // prepare an argument array for the args supplied by xargs to the
        // program being run
        char *subarguments[Max_Argument_Count + 1];
        subarguments[Max_Argument_Count] = 0;

        // get the number of supplied arguments and build an array from them
        unsigned long argument_c = ish_build_argument_array_from_input(
                args,
                subarguments,
                Max_Argument_Count);

        // adjust the counter
        argument_c++;

        // create a list for the unified arguments (the original ones from the
        // xargs call and the ones entered on the new line)
        char *arglist[Max_Argument_Count + 1];
        for (int i = 0; i <= Max_Argument_Count; ++i) {
            arglist[i] = 0;
        }

        // get the total number of arguments
        unsigned long len = argument_count + argument_c;

        // build a unified argument array
        for (long i = 0; i < len; ++i) {
            if (i < argument_count) {
                arglist[i] = arguments[i];
            } else {
                arglist[i] = subarguments[i - argument_count];
            }
        }

        // execute the program, supply the arguments, wait for it to finish
        int pid = fork();
        if (pid == 0) {
            execve(executable, arglist, envp);
            return -1;
        } else if (pid > 0) {
            int child_status;
            waitpid(pid, &child_status, 0);
        } else {
            write(2, Fork_Error_Message, sizeof(Fork_Error_Message));
        }
    }
    return 0;
}
