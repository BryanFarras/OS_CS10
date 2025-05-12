#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        write(STDERR_FILENO, "Usage: buatdong <filename> <content>\n", 40);
        exit(1);
    }

    char *filename = argv[1];
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    for (int i = 2; i < argc; ++i) {
        write(fd, argv[i], strlen(argv[i]));
        if (i < argc - 1) {
            write(fd, " ", 1);
        }
    }
    write(fd, "\n", 1);

    close(fd);
    write(STDOUT_FILENO, "Buset bisa dong.\n", 28);
    return 0;
}
