#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void processFile(char file[], size_t file_size, bool condition);
int checkNULL(FILE *pFile);
void checkSymbol(char *symbol, bool condition);
void convertSymbol(char buffer[], size_t size_buffer, int *element_size,
                   char *input_symbol, char *output_symbol, FILE *pWrite,
                   FILE *pRead);

int main() {
    // Declare and initialize the read and write variables
    char read_path[1024] = "";
    char write_path[1024] = "";

    // Process first the read part
    processFile(read_path, sizeof(read_path), true);
    FILE *pRead = fopen(read_path, "r");
    checkNULL(pRead);

    // Then process the write part
    processFile(write_path, sizeof(write_path), false);
    FILE *pWrite = fopen(write_path, "w");
    checkNULL(pWrite);

    // Asks for the input symbol/characther
    char input_symbol = '\0';
    checkSymbol(&input_symbol, true);

    // Asks for the output symbol/characther
    char output_symbol = '\0';
    checkSymbol(&output_symbol, false);

    // Initialize the buffer and the elements size in bytes
    char buffer[1024] = {0};
    int element_size = sizeof(buffer) / sizeof(buffer[0]);

    convertSymbol(buffer, sizeof(buffer), &element_size, &input_symbol,
                  &output_symbol, pWrite, pRead);

    printf("\nSuccessfully written to file!\n");

    // Closes both files
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
        printf("\nPlease enter the output file/path name: ");
    }
    fgets(file, file_size, stdin);
    file[strlen(file) - 1] = '\0';
    printf("\nTrying to open the path: %s\n", file);
}

int checkNULL(FILE *pFile) {
    if (pFile == NULL) {
        printf("\nFailed to open the file, please select a correct path!\n");
        exit(1); // Exits the program entirely
    } else {
        printf("\nSuccess on opening the file!\n");
        return 0;
    }
}

void checkSymbol(char *symbol, bool condition) {
    do {
        // Checks the condition to display the right message for read or write
        if (condition == true) {
            printf("\nPlease enter the input symbol/characther you want to be "
                   "replaced: ");
        } else {
            printf("\nPlease enter the output symbol/characther you want to "
                   "replace "
                   "with: ");
        }
        scanf("%c", symbol);
    } while (*symbol == '\0' || *symbol == '\n');
}

void convertSymbol(char buffer[], size_t size_buffer, int *element_size,
                   char *input_symbol, char *output_symbol, FILE *pWrite,
                   FILE *pRead) {
    while (fgets(buffer, size_buffer, pRead) != NULL) {
        for (int i = 0; i < (*element_size); i++) {
            if (buffer[i] == '\0') {
                break;
            } else if (buffer[i] == (*input_symbol)) {
                printf("%c", (*output_symbol));
                fprintf(pWrite, "%c", (*output_symbol));
            } else {
                printf("%c", buffer[i]);
                fprintf(pWrite, "%c", buffer[i]);
            }
        }
    }
}