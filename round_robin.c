#include <stdio.h>
struct process
{
    int pid;
    int at, bt, wt, tt, rt, ct;
    int completed;
    int flag;
    int resp_t; //response time
} p[10];
int n;
int q[10]; //queue
int f = -1, r = -1;
void enqueue(int i)
{
    if (r == 10)
        printf("overflow");
    r++;
    q[r] = i;
    if (f == -1)
        f = 0;
}
int dequeue()
{
    if (f == -1)
        printf("underflow");
    int temp = q[f];
    if (f == r)
        f = r = -1;
    else
        f++;
    return temp;
}
int isInQueue(int i)
{
    int k;
    for (k = f; k <= r; k++)
    {
        if (q[k] == i)
            return 1;
    }
    return 0;
}
void sortByArrival()
{
    struct process temp;
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
}
void sortBypid()
{
    struct process temp;
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
        {
            if (p[i].pid > p[j].pid)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
}
void main()
{
    int i, j, time = 0, sum_bt = 0, tq;
    int t, w;
    float avgt = 0, avgw = 0, avgr = 0;
    printf("Enter no of processes:");
    scanf("%d", &n);
    printf("\nEnter the arrival time and burst time of process:\n");
    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("For P%d:", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].completed = 0;
        p[i].flag = 0;
        sum_bt += p[i].bt;
    }
    printf("\nEnter the time quantum:");
    scanf("%d", &tq);
    sortByArrival();
    enqueue(0); // enqueue the first processprintf("Process execution order: ");
    for (time = p[0].at; time < sum_bt;)
    { // run until the total burst time reached
        i = dequeue();
        if (p[i].rt <= tq)
        { /* for processes having remaining time with less than or equal to time quantum */
            if (p[i].flag != 1)
            {
                p[i].flag = 1;
                p[i].resp_t = time - p[i].at;
                avgr += p[i].resp_t;
            }
            time += p[i].rt;
            p[i].rt = 0;
            p[i].completed = 1;
            printf(" |P%d %d", p[i].pid, time);
            p[i].ct = time;
            p[i].wt = time - p[i].at - p[i].bt;
            p[i].tt = time - p[i].at;
            for (j = 0; j < n; j++)
            { /*enqueue the processes which have come while scheduling */
                if (p[j].at <= time && p[j].completed != 1 && isInQueue(j) != 1)
                {
                    enqueue(j);
                }
            }
        }
        else
        { // more than time quantum
            if (p[i].flag != 1)
            {
                p[i].flag = 1;
                p[i].resp_t = time - p[i].at;
                avgr += p[i].resp_t;
            }
            time += tq;
            p[i].rt -= tq;
            printf(" |P%d %d", p[i].pid, time);
            p[i].ct = time;
            for (j = 0; j < n; j++)
            { /*first enqueue the processes which have come while scheduling */
                if (p[j].at <= time && p[j].completed != 1 && i != j && isInQueue(j) != 1)
                {
                    enqueue(j);
                }
            }
            enqueue(i); // then enqueue the uncompleted process
        }
    }
    sortBypid();
    printf("\npid\tArrival Time\tBurst Time\tCompletion time\tTurnAround Time\tWaiting Time\tResponse time");
    for (i = 0; i < n; i++)
    {
        t = p[i].ct - p[i].at;
        avgt += t;
        w = t - p[i].bt;
        avgw += w;
        printf("\n%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t", p[i].pid, p[i].at, p[i].bt, p[i].ct, t, w, p[i].resp_t);
    }
    printf("\nAverage waiting time:%f\n", avgw / n);
    printf("\nAverage turnaround time:%f\n", avgt / n);
    printf("\nAverage response time:%f\n", avgr / n);
}