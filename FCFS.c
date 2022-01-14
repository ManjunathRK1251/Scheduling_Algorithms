#include <stdio.h>
#include <stdlib.h>

struct process_t
{
	int id;
	int arrival_time;
	int burst_time;
	int waiting_time;
	int turn_around_time;
};

struct process_t processes[10];
int n;

int comparator(const void *a, const void *b)
{
	return ((struct process_t *)a)->arrival_time > ((struct process_t *)b)->arrival_time;
}

void schedule_fcfs()
{
	int i;
	qsort(processes, n, sizeof(processes[0]), comparator); // Sort processes by arrival time

	int cur_time = processes[0].arrival_time;
	float twt = 0, ttt = 0;

	// Compute waiting and turnaround time
	for (i = 0; i < n; i++)
	{
		if (processes[i].arrival_time > cur_time)
			cur_time = processes[i].arrival_time;
		processes[i].waiting_time = cur_time - processes[i].arrival_time;
		processes[i].turn_around_time = processes[i].burst_time + processes[i].waiting_time;
		cur_time += processes[i].burst_time;

		twt += processes[i].waiting_time;
		ttt += processes[i].turn_around_time;
	}

	// Print table
	printf("Id\tAT\tBT\tWT\tTT\n");
	for (i = 0; i < n; i++)
		printf("%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival_time,
			   processes[i].burst_time, processes[i].waiting_time,
			   processes[i].turn_around_time);

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
		processes[i].id = i + 1;
		scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
	}

	schedule_fcfs();
}