#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--h") == 0 || strcmp(argv[1], "--help") == 0) {
            printf("Usage:\n");
            printf("  ./print                -> prints 'Hello from print!'\n");
            printf("  ./print <text>         -> prints the provided text\n");
            printf("  ./print --dir          -> prints current working directory\n");
            printf("  ./print --h or --help  -> shows this help message\n");
            return 0;
        } else if (strcmp(argv[1], "--dir") == 0) {
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("Current Directory: %s\n", cwd);
            } else {
                perror("getcwd failed");
                return 1;
            }
            return 0;
        } else {
            for (int i = 1; i < argc; i++) {
                printf("%s ", argv[i]);
            }
            printf("\n");
            return 0;
        }
    }

    printf("Hello from print!\n");
    return 0;
}
