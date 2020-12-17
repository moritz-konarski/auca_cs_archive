/*
 * Much of this code has been copied from our project 1 part 2
 * https://github.com/toksaitov/syscall-project/blob/master/ish/ish_shell_utilities.h
 */

#ifndef COMMAND_LINE_UTILS
#define COMMAND_LINE_UTILS

#include "string_utils.h"

char *ish_get_first_environment_variable(
        const char *key, unsigned long key_length,
        char **environment);

unsigned long ish_build_argument_array_from_input(
        char *input,
        char **arguments,
        unsigned long max_argument_count);

#endif
