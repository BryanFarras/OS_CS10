#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    char *args[argc + 1];
    args[0] = "pwd";

    for (int i = 1; i < argc; i++) {
        args[i] = argv[i]; 
    }

    args[argc] = NULL;

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execvp("pwd", args);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }

    return 0;
}
