#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <zip_file> [destination_folder]\n", argv[0]);
        return 1;
    }

    char *args[5];
    args[0] = "unzip";
    args[1] = argv[1];

    if (argc >= 3) {
        args[2] = "-d";
        args[3] = argv[2];
        args[4] = NULL;
    } else {
        args[2] = NULL;
    }

    pid_t pid = fork();
    if (pid == 0) {
        execvp("unzip", args);
        perror("exec failed");
        exit(1);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork failed");
        return 1;
    }

    return 0;
}
