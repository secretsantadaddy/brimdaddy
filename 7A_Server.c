#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO1 "fifo1" // FIFO for writing from process1 to process2
#define FIFO2 "fifo2" // FIFO for writing from process2 to process1

// Function to count characters, words, and lines
void count_stats(char *sentence, int *chars, int *words, int *lines) {
    *chars = strlen(sentence);
    *words = 0;
    *lines = 0;

    int in_word = 0;
    for (int i = 0; i < *chars; i++) {
        if (sentence[i] == '\n') {
            (*lines)++;
        }
        if (sentence[i] == ' ' || sentence[i] == '\n' || sentence[i] == '\t') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            (*words)++;
        }
    }
    if (*lines == 0) {
        *lines = 1; // Count a single line if no newlines are present
    }
}

int main() {
    char sentence[1024];
    int chars, words, lines;
    char result[1024];

    // Read the sentence from FIFO1
    int fd1 = open(FIFO1, O_RDONLY);
    read(fd1, sentence, sizeof(sentence));
    close(fd1);

    // Count characters, words, and lines
    count_stats(sentence, &chars, &words, &lines);

    // Write the statistics to a file
    FILE *fp = fopen("output.txt", "w");
    fprintf(fp, "Number of characters: %d\n", chars);
    fprintf(fp, "Number of words: %d\n", words);
    fprintf(fp, "Number of lines: %d\n", lines);
    fclose(fp);

    // Read the result from the file
    fp = fopen("output.txt", "r");
    fread(result, sizeof(char), sizeof(result), fp);
    fclose(fp);

    // Write the result to FIFO2
    int fd2 = open(FIFO2, O_WRONLY);
    write(fd2, result, strlen(result) + 1);
    close(fd2);

    return 0;
}
