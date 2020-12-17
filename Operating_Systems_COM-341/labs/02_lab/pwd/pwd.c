#define BUF_SIZE 4096

long strlen(const char *s) {
    long i;
    for (i = 0; s[i] != '\0'; i++) ;
    return i;
}

static char buf[BUF_SIZE];

int main() {

    long len = getcwd(buf, BUF_SIZE);

    write(1, buf, len);

    write(1, "\n", 1);

    return 0;
}
