#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void processFile(char file[], size_t file_size, bool condition);
int checkNULL(FILE *pFile);
void checkSymbol(char *symbol, bool condition);

int main() {
    // Declare and initialize the read and write variables
    char read_path[1024] = "";
    char write_path[1024] = "";

    // Process first the read part
    processFile(read_path, sizeof(read_path), true);
    FILE *pRead = fopen(read_path, "r");
    checkNULL(pRead);

    char buffer[1024] = {0};

    // Then process the write part
    processFile(write_path, sizeof(write_path), false);
    FILE *pWrite = fopen(write_path, "w");
    checkNULL(pWrite);

    char input_symbol = '\0';
    checkSymbol(&input_symbol, true);

    char output_symbol = '\0';
    checkSymbol(&output_symbol, false);

    int buffer_size = sizeof(buffer) / sizeof(buffer[0]);

    while (fgets(buffer, sizeof(buffer), pRead) != NULL) {
        for (int i = 0; i < buffer_size; i++) {
            if (buffer[i] == '\0') {
                break;
            } else if (buffer[i] == input_symbol) {
                printf("%c", ' ');
                fprintf(pWrite, "%c", output_symbol);
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
    // Checks the condition to display the right message for read or write

    if (condition == true) {
        // You can also choose the path (relative or absolute)
        printf("\nPlease enter the file/path you want to replace symbol: ");
    } else {
        printf("\nPlease enter the output file name: ");
    }
    fgets(file, file_size, stdin);
    file[strlen(file) - 1] = '\0';
    printf("\nTrying to open the path: %s\n", file);
}

int checkNULL(FILE *pFile) {
    if (pFile == NULL) {
        printf("\nFailed to open the file, please select a correct path!\n");
        exit(1);
    } else {
        printf("\nSuccess on opening the file!\n");
        return 0;
    }
}

void checkSymbol(char *symbol, bool condition) {
    do {
        // Checks the condition to display the right message for read or write
        if (condition == true) {
            printf("\nPlease enter the symbol/characther you want to be "
                   "replaced: ");
        } else {
            printf("\nPlease enter the symbol/characther you want to replace "
                   "with: ");
        }
        scanf("%c", symbol);
    } while (*symbol == '\0' || *symbol == '\n');
}