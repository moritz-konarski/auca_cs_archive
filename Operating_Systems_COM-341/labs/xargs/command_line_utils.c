/*
 * This code has been copied from our project 1 part 2
 * https://github.com/toksaitov/syscall-project/blob/master/ish/ish_shell_utilities.c
 */

#include "command_line_utils.h"

char *ish_get_first_environment_variable(
        const char *key, unsigned long key_length,
        char **environment) {
    ish_check(key && environment);

    char *result = 0;

    for (char **variable = environment; *variable; ++variable) {
        if (ish_cstring_starts_with_ignoring_case(
                key, *variable)) {
            result =
                    *variable;
            result +=
                    key_length;

            break;
        }
    }

    return result;
}

unsigned long ish_build_argument_array_from_input(
        char *input,
        char **arguments,
        unsigned long max_argument_count) {
    unsigned long argument_index = 0;

    for (char *cursor = input;
         cursor && argument_index < max_argument_count;
         ++argument_index) {
        arguments[argument_index] =
                ish_carve_token_in_cstring(
                        cursor,
                        ish_is_space,
                        &cursor);
    }
    arguments[argument_index] = 0;

    unsigned long argument_count =
            argument_index == 0 ? 0 : argument_index - 1;

    return argument_count;
}
