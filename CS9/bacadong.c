#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        const char *msg = "Usage: bacadong <filename>\n";
        write(STDERR_FILENO, msg, strlen(msg));
        exit(1);
    }

    char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    char buffer[1024];
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    close(fd);
    return 0;
}
