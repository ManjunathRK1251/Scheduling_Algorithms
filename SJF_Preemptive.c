#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct process
{
    int id;
    int arrivaltime;
    int bursttime;
    int waitingtime;
    int turnaroundtime;
    int remainingtime;
    int finishedindex;
};

struct process p[10];
int n;

int arrivalcompare(const void *a, const void *b)
{
    return ((struct process *)a)->arrivaltime > ((struct process *)b)->arrivaltime;
}
int finishcompare(const void *a, const void *b)
{
    return ((struct process *)a)->finishedindex > ((struct process *)b)->finishedindex;
}
void Sjfp()
{
    int i, finishedjobs = 0;
    float twt = 0, ttt = 0;
    qsort(p, n, sizeof(p[0]), arrivalcompare); // Sort processes by arrival time

    int curtime = 0;
    while (finishedjobs != n)
    {
        int nextjob = -1, minbursttime = INT_MAX;
        for (i = 0; i < n && p[i].arrivaltime <= curtime; i++)
        {
            if (p[i].remainingtime > 0 && p[i].remainingtime < minbursttime)
            {
                minbursttime = p[i].remainingtime;
                nextjob = i;
            }
        }
        curtime++;
        if (nextjob != -1)
        {
            p[nextjob].remainingtime--;
            if (p[nextjob].remainingtime == 0)
            {
                finishedjobs++;
                p[nextjob].turnaroundtime = curtime - p[nextjob].arrivaltime;
                p[nextjob].waitingtime = p[nextjob].turnaroundtime - p[nextjob].bursttime;
                if (p[nextjob].waitingtime < 0)
                    p[nextjob].waitingtime = 0;
                p[nextjob].finishedindex = finishedjobs;

                twt += p[nextjob].waitingtime;
                ttt += p[nextjob].turnaroundtime;
            }
        }
    }

    qsort(p, n, sizeof(p[0]), finishcompare);

    printf("\nId\tAT\tBT\tWT\tTT\n");
    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrivaltime,
               p[i].bursttime, p[i].waitingtime,
               p[i].turnaroundtime);

    printf("Average waiting time: %f\n", twt / ((float)n));
    printf("Average turnaround time: %f\n", ttt / ((float)n));
}

int main()
{
    int i;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter process details\nArrival time\tBurst time\n");
    for (i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        scanf("%d %d", &p[i].arrivaltime, &p[i].bursttime);
        p[i].remainingtime = p[i].bursttime;
    }

    Sjfp();
}