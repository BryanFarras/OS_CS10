#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <folder_name>\n", argv[0]);
        return 1;
    }

    const char *folder_name = argv[1];
    int status = mkdir(folder_name, 0755);

    if (status == 0) {
        printf("Folder '%s' created successfully.\n", folder_name);
    } else {
        perror("mkdir failed");
        return 1;
    }

    return 0;
}
