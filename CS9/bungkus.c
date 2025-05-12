#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <archive_name.zip> <file1> [file2 ...] [--flag]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        printf("Usage: %s <archive_name.zip> <file1> [file2 ...] [--flag]\n", argv[0]);
        printf("Flags:\n");
        printf("  --help, -h     Show this help message\n");
        printf("  --verbose      Show zip output in detail\n");
        printf("  --quiet        Suppress most of the output\n");
        exit(EXIT_SUCCESS);
    }

    char *zip_cmd = "zip";
    char *args[argc + 3];
    int arg_idx = 0;

    args[arg_idx++] = zip_cmd;
    int i = 1;

    while (i < argc && strncmp(argv[i], "--", 2) != 0) {
        args[arg_idx++] = argv[i++];
    }

    int verbose = 0, quiet = 0;
    while (i < argc) {
        if (strcmp(argv[i], "--verbose") == 0) {
            verbose = 1;
        } else if (strcmp(argv[i], "--quiet") == 0) {
            quiet = 1;
        }
        i++;
    }

    if (verbose) args[arg_idx++] = "-v";
    if (quiet) args[arg_idx++] = "-q";

    args[arg_idx] = NULL;

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execvp(zip_cmd, args);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }

    return 0;
}
