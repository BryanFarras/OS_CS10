#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_to_delete>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    if (remove(filename) == 0) {
        printf("File '%s' udah dihapus.\n", filename);
    } else {
        perror("Error deleting file");
        return 1;
    }

    return 0;
}
