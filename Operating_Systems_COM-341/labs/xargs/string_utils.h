/*
 * Much of this code has been copied from our project 1 part 2
 * https://github.com/toksaitov/syscall-project/blob/master/ish/ish_cstring_utilities.h
 */

#ifndef STRING_UTILS
#define STRING_UTILS

#include "syscalls.h"

#define ish_check(value) \
    do                   \
    {                    \
        if (!(value))    \
            exit(-1);    \
    } while (0)

static const char ISH_Directory_Separator = '/';
static const char ISH_Path_Separator = ':';

char *ish_replace_first_character_in_cstring(
        char *string,
        char character,
        char replacement);

int ish_is_space(int character);

int ish_is_path_separator(int character);

int ish_is_uppercase(int character);

int ish_convert_to_lowercase(int character);

char *ish_carve_token_in_cstring(
        char *string,
        int (*is_separator)(int character),
        char **cursor_after_token);

char *ish_get_token_in_cstring(
        char *string,
        int (*is_separator)(int character),
        char **cursor_after_token);

int ish_cstring_starts_with_ignoring_case(
        const char *prefix,
        const char *string);

void ish_combine_path_elements(
        const char *path_element,
        const char *another_path_element,
        char *combined_path,
        unsigned long maximum_combined_path_length);

#endif
