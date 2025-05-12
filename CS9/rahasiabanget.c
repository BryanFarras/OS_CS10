#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

char encrypt_char(char c) {
    if (isalpha(c)) {
        if (islower(c))
            return ((c - 'a' + 3) % 26) + 'a';
        else
            return ((c - 'A' + 3) % 26) + 'A';
    }
    return c;
}

void encrypt_and_write(int fd, char *text) {
    for (int i = 0; text[i] != '\0'; ++i) {
        char enc = encrypt_char(text[i]);
        write(fd, &enc, 1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        const char *msg = "Usage: ./rahasiabanget <filename> <text to encrypt>\n";
        write(STDERR_FILENO, msg, strlen(msg));
        exit(1);
    }

    char *filename = argv[1];
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    for (int i = 2; i < argc; ++i) {
        encrypt_and_write(fd, argv[i]);
        if (i < argc - 1) {
            write(fd, " ", 1);
        }
    }
    write(fd, "\n", 1);
    close(fd);

    const char *done = "File created and encrypted.\n";
    write(STDOUT_FILENO, done, strlen(done));
    return 0;
}