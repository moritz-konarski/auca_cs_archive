#include <stdio.h>

// program that emulates the standard 'yes' program
// see 'man yes' for information
int main(int argc, char **argv) {
    // if no arguments are given
    if (argc == 1) {
        // output 'y' until terminated
        while (1) {
            putc('y', stdout);
            putc('\n', stdout);
        }
    } else {
        // print all arguments until terminated
        while (1) {
            // cycle through all arguments
            for (int i = 1; i < argc; ++i) {
                printf("%s ", argv[i]);
            }
            putc('\n', stdout);
        }
    }

    return 0;
}
