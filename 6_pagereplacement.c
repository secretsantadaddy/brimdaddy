#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

// Queue structure for LRU
typedef struct {
    char data[MAX_FRAMES][2];
    int end;
} queue;

// Enqueue and Dequeue functions for LRU
void enqueue(queue *q, char page, int index) {
    q->data[index][0] = page;
}

void dequeue(queue *q, int index) {
    for (int i = index; i < q->end - 1; i++) {
        q->data[i][0] = q->data[i + 1][0];
        q->data[i][1] = q->data[i + 1][1];
    }
    q->end--;
}

// LRU page replacement algorithm
void lru(char string[], int frameSize, int count) {
    int cnt, cnt2, selector, flag, min, faults = 0;
    queue q;
    q.end = 0;

    printf("\nData Requested\tFrame contents\tPage Fault\n");
    printf("==============================================");

    for (cnt = 0; cnt < count; cnt++) {
        printf("\n\n\t%c", string[cnt]);
        flag = 0;
        
        for (cnt2 = 0; cnt2 < q.end; cnt2++) {
            if (string[cnt] == q.data[cnt2][0]) {
                flag = 1;
                q.data[cnt2][1] = cnt;
                break;
            }
        }

        if (flag == 0) {
            faults++;
            if (q.end < frameSize) {
                enqueue(&q, string[cnt], q.end);
                q.data[q.end][1] = cnt;
                q.end++;
            } else {
                min = q.data[0][1];
                selector = 0;
                
                for (cnt2 = 1; cnt2 < q.end; cnt2++) {
                    if (q.data[cnt2][1] < min) {
                        min = q.data[cnt2][1];
                        selector = cnt2;
                    }
                }
                
                dequeue(&q, selector);
                enqueue(&q, string[cnt], selector);
                q.data[selector][1] = cnt;
            }
            
            printf("\t  ");
            for (cnt2 = 0; cnt2 < q.end; cnt2++) {
                printf("%c   ", q.data[cnt2][0]);
            }
            printf("\t\tY");
        } else {
            printf("\t  ");
            for (cnt2 = 0; cnt2 < q.end; cnt2++) {
                printf("%c   ", q.data[cnt2][0]);
            }
            printf("\t\tN");
        }
    }
    printf("\n\n==============================================\n");
    printf("\nTotal no. of Page Faults: %d\n\n", faults);
}

// FCFS page replacement algorithm
void fcfs(char string[], int frameSize, int count) {
    int faults = 0, index = 0;
    char frames[MAX_FRAMES];
    int frame_count = 0;
    
    printf("\nData Requested\tFrame contents\tPage Fault\n");
    printf("==============================================");

    for (int i = 0; i < count; i++) {
        printf("\n\n\t%c", string[i]);
        int flag = 0;

        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == string[i]) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            faults++;
            if (frame_count < frameSize) {
                frames[frame_count++] = string[i];
            } else {
                frames[index] = string[i];
                index = (index + 1) % frameSize;
            }

            printf("\t  ");
            for (int k = 0; k < frame_count; k++) {
                printf("%c   ", frames[k]);
            }
            printf("\t\tY");
        } else {
            printf("\t  ");
            for (int k = 0; k < frame_count; k++) {
                printf("%c   ", frames[k]);
            }
            printf("\t\tN");
        }
    }
    printf("\n\n==============================================\n");
    printf("\nTotal no. of Page Faults: %d\n\n", faults);
}

// Optimal page replacement algorithm
void optimal(char string[], int frameSize, int count) {
    int faults = 0;
    char frames[MAX_FRAMES];
    int frame_count = 0;

    printf("\nData Requested\tFrame contents\tPage Fault\n");
    printf("==============================================");

    for (int i = 0; i < count; i++) {
        printf("\n\n\t%c", string[i]);
        int flag = 0;

        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == string[i]) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            faults++;
            if (frame_count < frameSize) {
                frames[frame_count++] = string[i];
            } else {
                int farthest = i, replace_index = -1;

                for (int j = 0; j < frame_count; j++) {
                    int k;
                    for (k = i + 1; k < count; k++) {
                        if (frames[j] == string[k]) {
                            if (k > farthest) {
                                farthest = k;
                                replace_index = j;
                            }
                            break;
                        }
                    }

                    if (k == count) {
                        replace_index = j;
                        break;
                    }
                }

                frames[replace_index] = string[i];
            }

            printf("\t  ");
            for (int j = 0; j < frame_count; j++) {
                printf("%c   ", frames[j]);
            }
            printf("\t\tY");
        } else {
            printf("\t  ");
            for (int j = 0; j < frame_count; j++) {
                printf("%c   ", frames[j]);
            }
            printf("\t\tN");
        }
    }
    printf("\n\n==============================================\n");
    printf("\nTotal no. of Page Faults: %d\n\n", faults);
}

int main() {
    char pageString[MAX_PAGES];
    int frameSize = 3;
    int count;

    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &count);

    printf("Enter the page reference string: ");
    for (int i = 0; i < count; i++) {
        scanf(" %c", &pageString[i]);
    }

    printf("\n\n--- FCFS Page Replacement ---\n");
    fcfs(pageString, frameSize, count);

    printf("\n\n--- LRU Page Replacement ---\n");
    lru(pageString, frameSize, count);

    printf("\n\n--- Optimal Page Replacement ---\n");
    optimal(pageString, frameSize, count);

    return 0;
}

