/*
 * This code has been copied from our project 1 part 2
 * https://github.com/toksaitov/syscall-project/blob/master/ish/ish_cstring_utilities.c
 */

#include "string_utils.h"

char *ish_replace_first_character_in_cstring(
        char *string,
        char character,
        char replacement) {
    for (char *cursor = string; *cursor; ++cursor) {
        if (*cursor == character) {
            *cursor =
                    replacement;

            break;
        }
    }

    return string;
}

int ish_is_space(int character) {
    int result =
            character == ' ' ||
            (unsigned int) character - '\t' < 5;

    return result;
}

int ish_is_path_separator(int character) {
    int result =
            character ==
            ISH_Path_Separator;

    return result;
}

int ish_is_uppercase(int character) {
    int result =
            (unsigned int) character - 'A' < 26;

    return result;
}

int ish_convert_to_lowercase(int character) {
    static const int Distance =
            'a' - 'A';

    if (ish_is_uppercase(character)) {
        character +=
                Distance;
    }

    return character;
}

char *ish_carve_token_in_cstring(
        char *string,
        int (*is_separator)(int character),
        char **cursor_after_token) {
    char *result = 0;

    while (*string && is_separator(*string)) {
        ++string;
    }

    if (*string) {
        result =
                string;
    }

    while (*string && !is_separator(*string)) {
        ++string;
    }

    if (cursor_after_token) {
        *cursor_after_token = 0;
    }

    if (*string) {
        *(string++) = '\0';

        if (*string && cursor_after_token) {
            *cursor_after_token =
                    string;
        }
    }

    return result;
}

char *ish_get_token_in_cstring(
        char *string,
        int (*is_separator)(int character),
        char **cursor_after_token) {
    char *result = 0;

    while (*string && is_separator(*string)) {
        ++string;
    }

    if (*string) {
        result =
                string;
    }

    while (*string && !is_separator(*string)) {
        ++string;
    }

    if (cursor_after_token) {
        *cursor_after_token = 0;

        if (*string) {
            *cursor_after_token =
                    string;
        }
    }

    return result;
}

int ish_cstring_starts_with_ignoring_case(
        const char *prefix,
        const char *string) {
    ish_check(prefix && string);

    while (*prefix) {
        if (ish_convert_to_lowercase(*prefix++) !=
            ish_convert_to_lowercase(*string++)) {
            return 0;
        };
    }

    return 1;
}

void ish_combine_path_elements(
        const char *path_element,
        const char *another_path_element,
        char *combined_path,
        unsigned long maximum_combined_path_length) {
    ish_check(path_element && another_path_element && combined_path);

    unsigned long i = 0;

    while (
            i < maximum_combined_path_length &&
            *path_element &&
            !ish_is_path_separator(
                    *path_element)) {
        combined_path[i++] =
                *path_element++;
    }

    if (i < maximum_combined_path_length) {
        combined_path[i++] =
                ISH_Directory_Separator;
    }

    while (
            i < maximum_combined_path_length &&
            *another_path_element) {
        combined_path[i++] =
                *another_path_element++;
    }

    combined_path[i] = '\0';
}
