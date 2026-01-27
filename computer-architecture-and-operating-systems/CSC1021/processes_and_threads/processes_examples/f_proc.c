#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct {
    const char *filename;
    uint64_t chars;
    uint64_t words;
    uint64_t lines;
} FileData;

void display_file_data(const FileData fd);
FileData *process_file_data(const char *path);

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: [binary] [files...]\n");
        goto success_end;
    }

    for (size_t i = 1; i < argc; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            goto fail_end;
        } else if (pid == 0) {
            printf("[child process] - %d\n", getpid());
            FileData *fd = process_file_data(argv[i]);
            if (!fd) {
                fprintf(stderr, "failed to process file %s!\n", argv[i]);
            } else {
                display_file_data(*fd);
            }
            free(fd);
        }
    } 

    for (size_t i = 0; i < argc - 1; ++i)
        wait(NULL);

success_end:
    return 0;
fail_end:
    return 1;
}

FileData *process_file_data(const char *path) {
    FileData *fd = (FileData *)calloc(1, sizeof(FileData));
    if (!fd) {
        perror("memory allocation failed");
        abort();
    }

    fd->filename = path;

    FILE *f;
    if ((f = fopen(path, "r")) == NULL) {
        fprintf(stderr, "failed opening file");
        return NULL;
    }
    
    char ch;
    while ((ch = fgetc(f)) != EOF) {
        if (ch == '\n') {
            fd->lines++;
        } else if (ch == 32) {
            fd->words++;
        } else if (ch > 31) {
            fd->chars++;
        }
    }

    fclose(f);
    return fd;
}

void display_file_data(const FileData fd) {
    printf("File [%s] description\n", fd.filename);
    printf("Number of characters: %ld\n", fd.chars);
    printf("Number of words: %ld\n", fd.words);
    printf("Number of lines: %ld\n", fd.lines);
}
