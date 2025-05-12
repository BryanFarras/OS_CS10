#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], "--h") == 0 || strcmp(argv[1], "--help") == 0)) {
        printf("Usage: ./print <optional_text>\n");
        printf("If <optional_text> is given, it will be printed.\n");
        return 0;
    }

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            printf("ini diprint: %s ", argv[i]);
        }
        printf("\n");
    } else {
        printf("Hello from print!\n");
    }

    return 0;
}
