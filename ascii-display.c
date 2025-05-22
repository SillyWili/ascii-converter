#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *CLEAR_SCREEN = "\033[2J\033[H";
const char *HIDE_CURSOR = "\033[?25l";
const char *SHOW_CURSOR = "\033[?25h";
const char *OPEN_BUFFER = "\033[?1049h";
const char *CLOSE_BUFFER = "\033[?1049l";

const int MAX_LINE_LENGHT = 4096;

void clear_screen() { printf("%s", CLEAR_SCREEN); }
void open_buffer() { printf("%s", OPEN_BUFFER); }
void close_buffer() { printf("%s", CLOSE_BUFFER); }
void show_cursor() { printf("%s", SHOW_CURSOR); }
void hide_cursor() { printf("%s", HIDE_CURSOR); }

int main(int argc, char const *argv[]) {

    if (argc == 1) {
        fprintf(stderr,
                "No input file passed as argument for the script.\nPlease "
                "provide a video as input for the script to work.\n\nFor "
                "instructions on how to use this program please refer to the "
                "README.md\nUsage: "
                "%s <video-file.mp4/gif/...>\n",
                argv[0]);
        return 1;
    } else if (argc > 2) {
        printf("WARNING: more than one argument as been passed as input to the "
               "script, only the first will be displayed.\n");
    }

    char script_name[100] = "./ascii-frame-generator.sh ";
    char file_name[100];
    strcpy(file_name, argv[1]);

    printf("\nProcessing frames\n");
    system(strcat(script_name, file_name));
    clear_screen();

    // Main display logic for the program
    // -------------------------------------------------------------------------

    hide_cursor();
    open_buffer();

    FILE *fptr = fopen("frames.txt", "r");
    if (fptr == NULL) {
        perror("Failed to open the frames.txt file\n");
        return 1;
    }

    while (1) {
        int lines_read = 0;
        char line[MAX_LINE_LENGHT];
        while (fgets(line, sizeof(line), fptr) != NULL) {
            if (line[0] == '\n') {
                break;
            }
            fputs(line, stdout);
            fflush(stdout);
            lines_read++;
        }

        usleep(40 * 1000);
        clear_screen();

        if (lines_read == 0) {
            break;
        }
    }

    fclose(fptr);
    close_buffer();
    show_cursor();

    return 0;
}
