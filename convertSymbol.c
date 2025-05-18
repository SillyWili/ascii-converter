#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void processFile(char file[], size_t file_size, bool condition);
int checkNULL(FILE *pFile);

int main() {

    char read_path[1024] = "";
    processFile(read_path, sizeof(read_path), true);
    FILE *pRead = fopen(read_path, "r");

    char buffer[1024] = {0};

    checkNULL(pRead);

    char write_path[1024] = "";

    processFile(write_path, sizeof(write_path), false);

    FILE *pWrite = fopen(write_path, "w");

    checkNULL(pWrite);

    char symbol = '\0';
    do {
        printf("Please enter the symbol you want to replace: ");
        scanf("%c", &symbol);
    } while (symbol == '\0' || symbol == '\n');

    int buffer_size = sizeof(buffer) / sizeof(buffer[0]);

    while (fgets(buffer, sizeof(buffer), pRead) != NULL) {
        for (int i = 0; i < buffer_size; i++) {
            if (buffer[i] == '\0') {
                break;
            } else if (buffer[i] == symbol) {
                printf("%c", ' ');
                fprintf(pWrite, "%c", ' ');
            } else {
                printf("%c", buffer[i]);
                fprintf(pWrite, "%c", buffer[i]);
            }
        }
    }

    printf("\nSuccessfully written to file!\n");

    fclose(pWrite);
    fclose(pRead);

    return 0;
}

void processFile(char file[], size_t file_size, bool condition) {
    if (condition == 1) {
        // You can also choose the path (relative or absolute)
        printf("Please enter the file/path you want to replace symbol: ");
    } else {
        printf("Please enter the output file name: ");
    }
    fgets(file, file_size, stdin);
    file[strlen(file) - 1] = '\0';
    printf("\nTrying to open the path: %s\n", file);
}

int checkNULL(FILE *pFile) {
    if (pFile == NULL) {
        printf("Failed to open the file, please select a correct path!\n");
        exit(1);
    } else {
        return 0;
    }
}