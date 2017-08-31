#include<stdio.h>
#include<stdlib.h>
struct que_ele {
    int pname;
    int tstamp;
} que_ele;
int columns = 0, q_size = 0, flag = 0, count = 0;
struct que_ele *csq;
int *latest_count, *event_counter, **count_matrix;
void add_event(int p1, int p2, int *latest_count, int *event_counter,
               int **count_matrix, int processes)
{
    if (event_counter[p1 - 1] >= columns
            || event_counter[p2 - 1] >= columns) {
        ++columns;
        int i = 0, *temp;
        for (i = 0; i < processes; ++i) {
            temp = realloc(count_matrix[i], columns);
            if (temp != count_matrix[i])
                free(count_matrix[i]);
            count_matrix[i] = temp;
        }
    }
    if (p2 == 0) {
        ++event_counter[p1 - 1];
        ++latest_count[p1 - 1];
        count_matrix[p1 - 1][event_counter[p1 - 1] - 1] =
            latest_count[p1 - 1];
    } else {
        if (flag == 1) {
            if (latest_count[p1 - 1] >= latest_count[p2 - 1]) {
                ++event_counter[p2 - 1];
                count_matrix[p2 - 1][event_counter[p2 - 1] - 1] =
                    latest_count[p1 - 1] + 1;
                latest_count[p2 - 1] = latest_count[p1 - 1] + 1;
            } else {
                ++event_counter[p2 - 1];
                ++latest_count[p2 - 1];
                count_matrix[p2 - 1][event_counter[p2 - 1] - 1] =
                    latest_count[p2 - 1];
            }
        } else {
            ++event_counter[p1 - 1];
            ++latest_count[p1 - 1];
            count_matrix[p1 - 1][event_counter[p1 - 1] - 1] =
                latest_count[p1 - 1];
        if (latest_count[p1 - 1] >= latest_count[p2 - 1]) {
            ++event_counter[p2 - 1];
            count_matrix[p2 - 1][event_counter[p2 - 1] - 1] =
                latest_count[p1 - 1] + 1;
            latest_count[p2 - 1] = latest_count[p1 - 1] + 1;
        } else {
            ++event_counter[p2 - 1];
            ++latest_count[p2 - 1];
            count_matrix[p2 - 1][event_counter[p2 - 1] - 1] =
                latest_count[p2 - 1];
        }
    }
    }
}

void request_section(int e, int *latest_count, int *event_counter,
                     int **count_matrix, int processes)
{
    int i = 0;
    ++q_size;
    csq = realloc(csq, q_size * sizeof(que_ele));
    que_ele.pname = e - 1;
    que_ele.tstamp = latest_count[e - 1];
    csq[q_size - 1] = que_ele;
    add_event(e, 0, latest_count, event_counter, count_matrix, processes);
    for (i = 0; i < processes; i++) {
        if (i != e - 1)
            add_event(e,i+1, latest_count, event_counter, count_matrix,
                      processes);
    }
    //reply
    flag = 0;
    for (i = 0; i < processes; i++) {
            add_event(i+1,e, latest_count, event_counter, count_matrix,
                      processes);
    }
}

int main()
{
    int n = 0, processes = 0, i = 0, j = 0, cindex = 0, temp =
            0, e = 0, p1 = 0, p2 = 0;
    printf("Enter no of processes : ");
    scanf("%d", &processes);
    latest_count = malloc(processes * sizeof(*latest_count));
    event_counter = malloc(processes * sizeof(*event_counter));
    count_matrix = malloc(processes * sizeof(*count_matrix));
    for (i = 0; i < processes; ++i)
        count_matrix[i] = malloc(0 * sizeof(**count_matrix));
//initialize stuff
    for (i = 0; i < n; i++) {
        latest_count[i] = 0;
        for (j = 0; j < n; j++) {
            count_matrix[i][j] = 0;
        }
    }
    for (i = 0; i < processes; i++) {
        event_counter[i] = 0;
    }
//initialize end
    while (1) {
        printf
        ("1.Independent Event\n2.Dependent Event\n3.Request Critical Section\n4.Release Critical Section\n5.Display counters\n6.Exit\nOperation : ");
        scanf("%d", &n);
        switch (n) {
        case 1:
            printf("Enter process number : ");
            scanf("%d", &e);
            flag = 0;
            add_event(e, 0, latest_count, event_counter, count_matrix,
                      processes);
            break;
        case 2:
            printf("Process From : ");
            scanf("%d", &p1);
            printf("Process To : ");
            scanf("%d", &p2);
            flag = 0;
            add_event(p1, p2, latest_count, event_counter, count_matrix,
                      processes);
            break;
        case 3:
            printf("Enter process no : ");
            scanf("%d", &e);
            flag = 1;
            count = 0;
            request_section(e, latest_count, event_counter, count_matrix,
                            processes);
            break;
        case 4:
            break;
        case 5:
            for (i = 0; i < processes; i++) {
                printf("\t\t");
                for (j = 0; j < columns; j++) {
                    if (i == 0) {
                        printf("E%d\t", j + 1);
                    }
                }
                printf("\n");
                printf("Process(%d) \t", i + 1);
                for (j = 0; j < columns; j++) {
                    printf("%d\t", count_matrix[i][j]);
                }
                printf("\n");
            }
            printf("\n");
            break;
        case 6:
            exit(0);
            break;
        }
    }
    return 0;
}
