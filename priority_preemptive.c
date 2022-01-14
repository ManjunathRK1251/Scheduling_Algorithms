//priority preemptive
#include<stdio.h>
#include<stdlib.h>
struct process{
	int pid;		//process id
	int bt;			//busrt time
	int at;			//arival time
	int wt;
	int et;
	int rbt;			//waiting time
	int tt;			//turn around time
	int pv;			// priority value ; needed for priority scheduling (lower the value higher the priority)
	struct process *next;
};
struct process *front=NULL,*new,*temp=NULL;
struct process *ganttchart;
int total_burst=0,lst_arrival=0;
int p=0;
void insert(int b,int a){
	temp=front;
	new = (struct process *)malloc(sizeof(struct process));
	new->pid=++p;
	new->bt=b;
	new->at=a;
            new->wt=0;
	new->tt=0;
	new->et=0;
	new->rbt=b;		// FOR SRTF
	new->next=NULL;
	if(front==NULL)
		front=new;
	else
	{
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=new;
	}
}
void runFirst()
{
	/*
		this function will reinitilize the et and rbt , wt and tt .
	*/
	temp=front;
	while(temp!=NULL)
	{
		temp->rbt=temp->bt;
		temp->wt=0;
		temp->tt=0;
		temp->et=0;
		temp->pv=100;
		temp=temp->next;
	}
}
void display(int n){
	float avgWT=0,avgTT=0;
	temp=front;
	printf("\n PROCESS ID\tBURST TIME\tARRIVAL TIME\tWAITING TIME\tTURNAROUND TIME");
	while(temp!=NULL)
	{
		printf("\n %d \t\t %d \t\t %d \t\t %d \t\t %d",temp->pid,temp->bt,temp->at,temp->wt,temp->tt);
		avgWT+=temp->wt;
		avgTT+=temp->tt;
		temp=temp->next;
	}
	printf("\n Average WAITING TIME \t %f \t Average TURNAROUND TIME\t %f \n",(avgWT/n),avgTT/n);
}
void priorityP()
{
	// Preemptive Priority Scheduling
	//DECLARING LOCAL VARIABLES
	int time=0;
	int min=101;					//min = minimum priority value
	runFirst();
	// NEED TO ADD EXTRA PRIORITY ELEMENT
	temp=front;
	printf("\n ENTER PRIORITY VALUES \n");
	while(temp!=NULL)
	{
		printf("\n For Process %d ",temp->pid);
		scanf("%d",&temp->pv);
		temp=temp->next;
	}
	//NOW PERFORM THE SCHEDULING
	while(time<=total_burst)
		{
			ganttchart=NULL;
			temp=front;
			min=101;
			while(temp!=NULL)
			{
				if(temp->rbt!=0){
					if(time>=temp->at&&min>temp->pv)
					{
						min=temp->pv;
						ganttchart=temp;
					}

				}
				temp=temp->next;
			}
			if(ganttchart==NULL)
			{
				//CPU IDLE
				printf("| %d",time);
				time++;
			}
			else{
				printf("| P%d %d",ganttchart->pid,time);
				time+=1;
				ganttchart->rbt-=1;
				ganttchart->wt=time-(ganttchart->at+ganttchart->bt);
				ganttchart->tt=time-ganttchart->at;
			}
		}
}

int main()
{
	int ch,i,n,a,b;
	// INSERT ONCE ONLY ..
	// AND DISPLAY ..
	printf("Enter the no of process \n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
		{
			printf("\n Enter the Burst time And Arrival Time for Process \t %d \t",p+1);
			scanf("%d %d",&b,&a);
			insert(b,a);
			/*
				NOT REQUIRED FOR FCFS
			*/

			total_burst+=b;
			//lst_arrival=a;
	}
	priorityP();
    display(n);
    return 0;
    }