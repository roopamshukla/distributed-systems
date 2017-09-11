/* Author : Roopam Shukla
Date : Aug 18, 2017 */
#include<stdio.h>
#include<stdlib.h>
struct que_ele {
    int pname;
    int tstamp;
} que_ele;
int columns = 0, q_size = 0, flag = 0, count = 0, cp = 0, cs = 0;
struct que_ele *csq;
int *latest_count, *event_counter, **count_matrix;
void add_event(int p1, int p2, int *latest_count, int *event_counter,
               int **count_matrix, int processes)
{
    if (event_counter[p1 - 1] + 1 >= columns
            || event_counter[p2 - 1] + 1 >= columns) {
        ++columns;
        int i = 0;
        for (i = 0; i < processes; ++i)
            count_matrix[i] =
                realloc(count_matrix[i], columns * sizeof(**count_matrix));
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

void release_section()
{
    int i = 0;
    if (q_size > 0) {
        if (cs == 0) {
            cs = 1;
            cp = csq[0].pname + 1;
            printf("\n*Process %d gets the CS.*\n\n", cp);
            for (i = 0; i < q_size - 1; i++) {
                csq[i] = csq[i + 1];
            }
            --q_size;
            csq = realloc(csq, q_size * sizeof(que_ele));
        } else {
            printf("\n*Process %d is in CS.*\n\n", cp);
        }
    } else {
        printf("\nCS is free.\n\n");
    }
}

void request_section(int e, int *latest_count, int *event_counter,
                     int **count_matrix, int processes)
{
    int i = 0, cindex = 0;
    ++q_size;
    csq = realloc(csq, q_size * sizeof(que_ele));
    que_ele.pname = e - 1;
    que_ele.tstamp = latest_count[e - 1];
    //csq[q_size - 1] = que_ele;
    add_event(e, 0, latest_count, event_counter, count_matrix, processes);
    for (i = 0; i < processes; i++) {
        if (i != e - 1)
            add_event(e, i + 1, latest_count, event_counter, count_matrix,
                      processes);
    }
    //reply
    flag = 0;
    for (i = 0; i < processes; i++) {
        if (i != e - 1)
            add_event(i + 1, e, latest_count, event_counter, count_matrix,
                      processes);
    }
    for (i = 0; i < q_size; i++) {
        if (que_ele.tstamp <= csq[i].tstamp) {
            cindex = i;
            break;
        } else {
            cindex = i;
        }
    }
    for (i = q_size - 2; i >= cindex; --i) {
        csq[i + 1] = csq[i];
    }
    csq[cindex] = que_ele;
    release_section();
}

int main()
{
    int n = 0, processes = 0, i = 0, j = 0, e = 0, p1 = 0, p2 = 0;
    printf("Enter no of processes : ");
    scanf("%d", &processes);
    latest_count = malloc(processes * sizeof(*latest_count));
    event_counter = malloc(processes * sizeof(*event_counter));
    count_matrix = malloc(processes * sizeof(*count_matrix));

    for (i = 0; i < processes; ++i)
        count_matrix[i] = NULL;

//initialize stuff
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
            cs = 0;
            flag = 1;
            release_section();
            add_event(cp, 0, latest_count, event_counter, count_matrix,
                      processes);
            for (i = 0; i < processes; i++) {
                if (i != e - 1)
                    add_event(cp, i + 1, latest_count, event_counter,
                              count_matrix, processes);
            }
            break;
        case 5:
            for (i = 0; i < processes; i++) {
                printf("\t\t");
                for (j = 0; j < columns; j++) {
                    if (i == 0) {
                        printf(" E%d ", j + 1);
                    }
                }
                printf("\n");
                printf("Process(%d) \t", i + 1);
                for (j = 0; j < columns; j++) {
                    printf(" %2d ", count_matrix[i][j]);
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
