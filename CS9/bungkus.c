#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <archive_name.zip> <file1> [file2 ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *args[argc + 2];
    args[0] = "zip";
    args[1] = argv[1]; 

    for (int i = 2; i < argc; i++) {
        args[i] = argv[i];
    }
    args[argc] = NULL;

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execvp("zip", args);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL); 
    }

    return 0;
}
