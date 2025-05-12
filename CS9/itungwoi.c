#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add(float num1, float num2) {
    printf("%.2f\n", num1 + num2);
}

void sub(float num1, float num2) {
    printf("%.2f\n", num1 - num2);
}

void mul(float num1, float num2) {
    printf("%.2f\n", num1 * num2);
}

void divi(float num1, float num2) {
    if (num2 == 0) {
        fprintf(stderr, "Error: Division by zero is not allowed.\n");
        exit(1);
    }
    printf("%.2f\n", num1 / num2);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: itungwoi {add|sub|mul|div} num1 num2\n");
        exit(1);
    }

    char *operation = argv[1];
    float num1 = atof(argv[2]);
    float num2 = atof(argv[3]);

    if (num1 == 0 && strcmp(argv[2], "0") != 0) {
        fprintf(stderr, "Error: Invalid input for num1\n");
        exit(1);
    }

    if (num2 == 0 && strcmp(argv[3], "0") != 0) {
        fprintf(stderr, "Error: Invalid input for num2\n");
        exit(1);
    }

    if (strcmp(operation, "add") == 0) {
        add(num1, num2);
    } else if (strcmp(operation, "sub") == 0) {
        sub(num1, num2);
    } else if (strcmp(operation, "mul") == 0) {
        mul(num1, num2);
    } else if (strcmp(operation, "div") == 0) {
        divi(num1, num2);
    } else {
        fprintf(stderr, "Error: Invalid operation '%s'. Use {add|sub|mul|div}\n", operation);
        exit(1);
    }

    return 0;
}
