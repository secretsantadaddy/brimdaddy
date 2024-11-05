#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO1 "fifo1" // FIFO for writing from process1 to process2
#define FIFO2 "fifo2" // FIFO for writing from process2 to process1

int main() {
    char sentence[1024];
    char result[1024];

    // Create FIFOs (named pipes) if they don't exist
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    // Get user input
    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);

    // Write the sentence to FIFO1
    int fd1 = open(FIFO1, O_WRONLY);
    write(fd1, sentence, strlen(sentence) + 1);
    close(fd1);

    // Read the result from FIFO2
    int fd2 = open(FIFO2, O_RDONLY);
    read(fd2, result, sizeof(result));
    close(fd2);

    // Display the result
    printf("Processed output:\n%s", result);

    // Remove the FIFOs
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}
