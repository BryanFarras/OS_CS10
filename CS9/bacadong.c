#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {
        const char *msg = "Usage: bacadong [--line] <filename>\n";
        write(STDERR_FILENO, msg, strlen(msg));
        exit(1);
    }

    // Help
    if ((argc == 2) && (strcmp(argv[1], "--h") == 0 || strcmp(argv[1], "--help") == 0)) {
        const char *help =
            "Usage: bacadong [--line] \"<filename with spaces>\"\n"
            "Options:\n"
            "  --line     Show file content with line numbers\n"
            "  --h, --help    Show this help message\n";
        write(STDOUT_FILENO, help, strlen(help));
        return 0;
    }

    int showLine = 0;
    char *filename = NULL;

    if (argc == 3 && strcmp(argv[1], "--line") == 0) {
        showLine = 1;
        filename = argv[2];
    } else if (argc == 2) {
        filename = argv[1];
    }

    if (filename == NULL) {
        const char *msg = "Invalid filename.\n";
        write(STDERR_FILENO, msg, strlen(msg));
        exit(1);
    }

    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    if (!showLine) {
        char buffer[1024];
        ssize_t bytesRead;
        while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, bytesRead);
        }
    } else {
        char c;
        int lineNum = 1;
        ssize_t n;
        dprintf(STDOUT_FILENO, "%4d | ", lineNum++);
        while ((n = read(fd, &c, 1)) > 0) {
            write(STDOUT_FILENO, &c, 1);
            if (c == '\n') {
                dprintf(STDOUT_FILENO, "%4d | ", lineNum++);
            }
        }
    }
    printf("\n");

    close(fd);
    return 0;
}
