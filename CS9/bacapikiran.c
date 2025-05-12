#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

char decrypt_char(char c) {
    if (isalpha(c)) {
        if (islower(c))
            return ((c - 'a' - 3 + 26) % 26) + 'a';
        else
            return ((c - 'A' - 3 + 26) % 26) + 'A';
    }
    return c;
}

void decrypt_and_print(int fd) {
    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        for (ssize_t i = 0; i < bytesRead; ++i) {
            char dec = decrypt_char(buffer[i]);
            write(STDOUT_FILENO, &dec, 1);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        const char *msg = "Usage: ./bacapikiran <encrypted filename>\n";
        write(STDERR_FILENO, msg, strlen(msg));
        exit(1);
    }

    char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    decrypt_and_print(fd);

    close(fd);
    return 0;
}
