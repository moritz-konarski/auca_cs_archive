#include <stdio.h>
#define BUFF_SIZE 1024

int main(int argc, char **argv) {

    if (argc == 1) {
        char buff[BUFF_SIZE];
        while (fgets(buff, BUFF_SIZE, stdin)){
            printf("%s", buff);
        }
    } else {
        for (int i = 1; i < argc; ++i) {
            char buff[BUFF_SIZE];
            FILE *fp = fopen(argv[i], "r");

            while (fgets(buff, BUFF_SIZE, fp)){
                printf("%s", buff);
            }

            fclose(fp);
        }
    }

    return 0;
}
