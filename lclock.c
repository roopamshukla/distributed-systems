#include<stdio.h>
int getSending(int n)
{
    return n / 10;
}

int getReceiving(int n)
{
    return n % 10;
}

int main()
{
    int n = 0, processes = 0, i = 0, j = 0;
    printf("Enter no of events in sequence : ");
    scanf("%d", &n);
    printf("\nEnter no of processes : ");
    scanf("%d", &processes);
    int sequence[n], latest_count[processes], event_counter[processes],
        count_matrix[n][n];
//initialize stuff
    for (i = 0; i < n; i++) {
        sequence[i] = 0;
        latest_count[i] = 0;
        for (j = 0; j < n; j++) {
            count_matrix[i][j] = 0;
        }
    }
    for (i = 0; i < processes; i++) {
        event_counter[i] = 0;
    }
//initialize end
    printf("\nEnter sequence : ");
    for (i = 0; i < n; i++) {
        scanf("%d", &sequence[i]);
    }
    for (i = 0; i < n; i++) {
        if (sequence[i] % 10 == 0) {
            ++latest_count[getSending(sequence[i]) - 1];
            count_matrix[getSending(sequence[i]) -
                         1][event_counter[getSending(sequence[i]) - 1]] =
                             latest_count[getSending(sequence[i]) - 1];
            event_counter[getSending(sequence[i]) - 1]++;
        } else {
            if (latest_count[getSending(sequence[i]) - 1] >
                    latest_count[getReceiving(sequence[i]) - 1]) {
                latest_count[getReceiving(sequence[i]) - 1] =
                    latest_count[getSending(sequence[i]) - 1];
                count_matrix[getReceiving(sequence[i]) -
                             1][event_counter[getReceiving(sequence[i]) -
                                              1]] =
                                                  latest_count[getSending(sequence[i]) - 1];
                event_counter[getReceiving(sequence[i]) - 1]++;
            } else {
                ++latest_count[getReceiving(sequence[i]) - 1];
                count_matrix[getReceiving(sequence[i]) -
                             1][event_counter[getReceiving(sequence[i]) -
                                              1]] =
                                                  latest_count[getReceiving(sequence[i]) - 1];
                event_counter[getReceiving(sequence[i]) - 1]++;
            }
        }
    }
    printf("\n");
    for (i = 0; i < processes; i++) {
        printf("\t\t");
        for (j = 0; j < n; j++) {
            if (i == 0) {
                printf("E%d\t", j + 1);
            }
        }
        printf("\n");
        printf("Process(%d) \t",i+1);
        for (j = 0; j < n; j++) {
            printf("%d\t", count_matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
