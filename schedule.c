/* 
Natasha Y Jeppu
14CO228

Program to compare Scheduling algorithms
1.Takes random number of processes (5-54)
2.Cpu burst times,priority and arrival times assigned randomly
3.Assumption: if same priority,processes execute in the order of arrival times.
4.Display function displaying the tat and waiting times for all processes has been commented under every scheduling function definition. You could un-comment to see individual tat and waiting times.
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct process
{
	int pid;
	int cpu_burst;
	int wt,tat,at,st,remain_t,ht;
	int p_comp;
	int prty;
};

void fcfs(int,struct process*);
void sjfs(int,struct process*);
void priority(int,struct process *);
void round_rob(int,struct process *);
void sjfs_p(int,struct process*);
void priority_p(int,struct process *);

void display(int ,struct process*);
void display_avg(int,struct process*);
void initialise(int,struct process*);
void sort(struct process *,int,int);
void sortprior(struct process *,int,int);

void main()
{
	int num;
	srand(time(NULL)); 
	num=5+random()%50;         //number of processes (5-54)
	
	struct process *p=(struct process *)malloc(sizeof(struct process)*num);
	int i;
	p[0].at=0;
	for(i=0;i<num;i++)
	{
		p[i].cpu_burst=1+random()%50;    //Cpu burst times(1-30)
		p[i].remain_t=p[i].cpu_burst;
		p[i].prty=1+random()%10;	 //Priority
		p[i].pid=i+1;
		if(i==0)
			continue;
		p[i].at=1+random()%20;		 //Arrival time
				
	}
	
	printf("Number of processes: %d\n",num);

	printf("%-12s%-10s%-10s%-10s\n","Process","CPU_Burst","At","Prior");
	for(i=0;i<num;i++)
		printf("%-12d%-10d%-10d%-10d\n",p[i].pid,p[i].cpu_burst,p[i].at,p[i].prty);
		
	int ch,chrr;
	do
	{
		printf("\nEnter Algo number:\n1.FCFS\n2.SJFS_NON-PRE-EMPTIVE\n3.SJFS_PRE-EMPTIVE\n4.PRIORITY_NON-PRE-EMPTIVE\n5.PRIORITY_PRE-EMPTIVE\n6.ROUND ROBIN\n7.Exit\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:printf("FCFS:\n");
				fcfs(num,p);break;
			case 2:printf("\nSJFS_NON-PRE-EMPTIVE:\n");
				sjfs(num,p);break;
			case 3:printf("\nSJFS_PRE-EMPTIVE:\n");
				sjfs_p(num,p);break;
			case 4:printf("\nPRIORITY_NON-PRE-EMPTIVE:\n");
				priority(num,p);break;
			case 5:printf("\nPRIORITY_PRE-EMPTIVE:\n");
				priority_p(num,p);break;
			case 6:do{
					printf("\nROUND ROBIN:\n");
					round_rob(num,p);
					printf("Enter:\n1.To enter new time quantum\n2.To exit\n");
					scanf("%d",&chrr);
				}while(chrr == 1);break;
			case 7:printf("\nExiting...\n");exit(0);break;
			default:printf("Not valid.Try again!\n");break;
		}
	}while(1);	


	printf("\n\n");
	printf("FCFS:\n");
	fcfs(num,p);
	printf("\nSJFS_NON-PRE-EMPTIVE:\n");
	sjfs(num,p);
	printf("\nSJFS_PRE-EMPTIVE:\n");
	sjfs_p(num,p);
	printf("\nPRIORITY_NON-PRE-EMPTIVE:\n");
	priority(num,p);
	printf("\nPRIORITY_PRE-EMPTIVE:\n");
	priority_p(num,p);
	printf("\nROUND ROBIN:\n");
	round_rob(num,p);
	
	
}

void display(int num,struct process *p)
{
	int i;
	printf("%-12s%-10s%-10s%-10s%-10s%-10s\n","Process","CPU_Burst","At","Prior","Wt","Tat");
	for(i=0;i<num;i++)
		printf("%-12d%-10d%-10d%-10d%-10d%-10d\n",p[i].pid,p[i].cpu_burst,p[i].at,p[i].prty,p[i].wt,p[i].tat);
		
}


//Initialise values for waiting,turnaround,start,halt and remaining time and process complete trigger
void initialise(int num,struct process *p)                 
{
	int i;
	for(i=0;i<num;i++)
	{
		p[i].wt=0;
		p[i].tat=0;
		p[i].st=0;
		p[i].p_comp=0;
		p[i].ht=0;
		p[i].remain_t=p[i].cpu_burst;
	}
}


// sort based on remaining time
void sort(struct process *p,int start,int end)
{
	int i,pos,j;
	struct process temp;
	for(i=start;i<end;i++)
    	{	
        	pos=i;
       		for(j=i+1;j<end;j++)
        	{
        	    if(p[j].remain_t<p[pos].remain_t)
        	        pos=j;
        	}
 
        	temp=p[i];
		p[i]=p[pos];
		p[pos]=temp;
    	}
	
}


// sort based on priority
void sortprior(struct process *p,int start,int end)
{
	int i,pos,j;
	struct process temp;
	for(i=start;i<end;i++)
    	{	
        	pos=i;
       		for(j=i+1;j<end;j++)
        	{
        	    if(p[j].prty<p[pos].prty)
        	        pos=j;
        	}
 
        	temp=p[i];
		    p[i]=p[pos];
		    p[pos]=temp;
    	}
	
}

//first come first serve
void fcfs(int num,struct process *p)
{
	initialise(num,p);
	int i,pos,j;
	struct process temp;
	for(i=0;i<num;i++)
    	{	
		p[i].p_comp=0;
        	pos=i;
       		for(j=i+1;j<num;j++)
        	{
        	    if(p[j].at<p[pos].at)
        	        pos=j;
        	}
 
        	temp=p[i];
		p[i]=p[pos];
		p[pos]=temp;
    	}
	p[0].wt=0;
	p[0].tat=p[0].cpu_burst;
	float avg_wt=0.0,avg_tat=0.0;
	for(i=1;i<num;i++)
	{
		
		p[i].wt=p[i-1].wt+p[i-1].cpu_burst;
		avg_wt+=p[i].wt;
		p[i].tat=p[i].wt+p[i].cpu_burst;
		avg_tat+=p[i].tat;
		
	}
	//display(num,p);
	printf("Average wt = %f\n",avg_wt/num);
	printf("Average tat = %f\n",avg_tat/num);
}


//shortest job first - non pre-emptive
void sjfs(int num,struct process *p)
{
	int i,pos,j;
	struct process temp;
	initialise(num,p);
	for(i=0;i<num;i++)
    	{	
		p[i].p_comp=0;
        	pos=i;
       		for(j=i+1;j<num;j++)
        	{
        	    if(p[j].at<p[pos].at)
        	        pos=j;
        	}
 
        	temp=p[i];
		p[i]=p[pos];
		p[pos]=temp;
    	}

	int tst=0,k=0;
	float avg_wt=0.0,avg_tat=0.0;
	for(i=0;i<num;i++)
	{
		if(p[i].p_comp==1)
			continue;
		k=i;
		
		while(p[i].at<=tst && i<num)
			i++;
		sort(p,k,i);
		i=k;
		if(p[i].at>tst)
			p[i].st=p[i].at;
		else
			p[i].st=tst;
		tst+=p[i].cpu_burst;
		p[i].p_comp=1;
		p[i].wt=p[i].st-p[i].at;
		p[i].tat=p[i].wt+p[i].cpu_burst;
		avg_wt+=p[i].wt;
		avg_tat+=p[i].tat;
	}
	
	//display(num,p);
	printf("Average wt = %f\n",avg_wt/num);
	printf("Average tat = %f\n",avg_tat/num);	
}


//priority - non pre-emptive
void priority(int num,struct process *p)
{
	int i,pos,j;
	struct process temp;
	initialise(num,p);
	for(i=0;i<num;i++)
    	{	
		p[i].p_comp=0;
        	pos=i;
       		for(j=i+1;j<num;j++)
        	{
        	    if(p[j].at<p[pos].at)
        	        pos=j;
        	}
 
        	temp=p[i];
		p[i]=p[pos];
		p[pos]=temp;
    	}

	int tst=0,k=0;
	float avg_wt=0.0,avg_tat=0.0;
	for(i=0;i<num;i++)
	{
		if(p[i].p_comp==1)
			continue;
		k=i;
		
		while(p[i].at<=tst && i<num && tst!=0)
			i++;
		sortprior(p,k,i);
		i=k;
		if(p[i].at>tst)
			p[i].st=p[i].at;
		else
			p[i].st=tst;
		tst+=p[i].cpu_burst;
		p[i].p_comp=1;
		p[i].wt=p[i].st-p[i].at;
		p[i].tat=p[i].wt+p[i].cpu_burst;
		avg_wt+=p[i].wt;
		avg_tat+=p[i].tat;
	}
	
	//display(num,p);
	printf("Average wt = %f\n",avg_wt/num);
	printf("Average tat = %f\n",avg_tat/num);
}



//round robin
void round_rob(int num,struct process *p)
{
	int time_quant;
	do
	{	printf("Enter time quantum between 3 and 10: ");
		scanf("%d",&time_quant);
		if(time_quant<3 || time_quant>10)
			printf("\nCheck range\n");
	}while(time_quant<3 || time_quant>10);
	int time=0;
	int i;
	for(i=0;i<num;i++)
		time+=p[i].cpu_burst;

	int pos,j;
	struct process temp;
	initialise(num,p);
	for(i=0;i<num;i++)
    	{	
		p[i].p_comp=0;
        	pos=i;
       		for(j=i+1;j<num;j++)
        	{
        	    if(p[j].at<p[pos].at)
        	        pos=j;
        	}
 
        	temp=p[i];
		p[i]=p[pos];
		p[pos]=temp;
    	}


	float avg_wt=0.0,avg_tat=0.0;
	int tst=0,k,flag;
	while(time)
	{
		k=0;
		flag=0;
		for(i=0;i<num;i++)
		{
			if(p[i].p_comp==1)
				continue;
			
			if(p[i].at<=tst || p[i].remain_t!=p[i].cpu_burst)
			{
				p[i].st=tst;
				if(p[i].remain_t==p[i].cpu_burst)
					p[i].wt=p[i].st-p[i].at;
				else
					p[i].wt+=p[i].st-p[i].ht;
				if(p[i].remain_t>=time_quant)
				{
					p[i].remain_t-=time_quant;
					time-=time_quant;
					tst+=time_quant;
				}
				else
				{
					tst+=p[i].remain_t;
					time-=p[i].remain_t;
					p[i].remain_t=0;	
				}
				p[i].ht=tst;
				if(p[i].remain_t==0)
					p[i].p_comp=1;
			}
		}
		
		while(p[k].at<=tst && k<num)
		{
			if(p[k].p_comp==0)
			{	flag=1;
				break;
			}
			k++;
		}
		if(flag==0)
			tst+=1;
		
	}


	for(i=0;i<num;i++)
	{
		avg_wt+=p[i].wt;
		p[i].tat=p[i].wt+p[i].cpu_burst;
		avg_tat+=p[i].tat;
	}
	//display(num,p);
	printf("Average wt = %f\n",avg_wt/num);
	printf("Average tat = %f\n",avg_tat/num);	
}


//sjfs - pre-emptive
void sjfs_p(int num,struct process *p)
{
	int time=0;
	int i;
	for(i=0;i<num;i++)
		time+=p[i].cpu_burst;

	int pos,j;
	struct process temp;
	initialise(num,p);
	for(i=0;i<num;i++)
    	{	
		p[i].p_comp=0;
        	pos=i;
       		for(j=i+1;j<num;j++)
        	{
        	    if(p[j].at<p[pos].at)
        	        pos=j;
        	}
 
        	temp=p[i];
		p[i]=p[pos];
		p[pos]=temp;
    	}
	//display(num,p);
	float avg_wt=0.0,avg_tat=0.0;	
	int tst=0,k,flag,new_process,curr=-1;
	i=0;
	while(time)
	{
		flag=0;
		k=0;

		while(p[k].at<=tst && k<num)
		{
			if(p[k].p_comp==0)
			{	flag=1;
				break;
			}
			k++;
		}
		if(flag==0)
		{
			tst+=1;
			continue;
		}
		new_process=0;
		for(j=0;j<num;j++)
			if(p[j].at==tst)
			{
				new_process=1;
				break;
			}
		if(new_process==1)
		{
			if(curr==-1)
			{
				curr=j;
				p[curr].st=tst;
				p[curr].wt=tst-p[curr].at;
			}
			if(p[curr].remain_t>p[j].remain_t)
			{
				p[curr].ht=tst;
				printf("pre-empting... Process:%d ",p[curr].pid);
				sort(p,curr,j+1);
				p[curr].st=tst;
				printf("replaced by Process:%d\n",p[curr].pid);
				if(p[curr].remain_t==p[curr].cpu_burst)
					p[curr].wt=tst-p[curr].at;
				else
					p[curr].wt+=p[curr].st-p[curr].ht;
			}
		}

		p[curr].remain_t-=1;
		time-=1;
		tst+=1;
		if(p[curr].remain_t==0)
		{
			p[curr].p_comp=1;
			if(p[curr+1].at<=tst && curr+1<num)
			{
				curr++;
				p[curr].st=tst;
				if(p[curr].remain_t==p[curr].cpu_burst)
					p[curr].wt=tst-p[curr].at;
				else
					p[curr].wt+=p[curr].st-p[curr].ht;
			}
			else 
				curr=-1;
		}

		
			
		
	}
	for(i=0;i<num;i++)
	{
		avg_wt+=p[i].wt;
		p[i].tat=p[i].wt+p[i].cpu_burst;
		avg_tat+=p[i].tat;
	}
	//display(num,p);
	printf("Average wt = %f\n",avg_wt/num);
	printf("Average tat = %f\n",avg_tat/num);			
}


//priority - pre-emptive
void priority_p(int num,struct process *p)
{
	int time=0;
	int i;
	for(i=0;i<num;i++)
		time+=p[i].cpu_burst;

	int pos,j;
	struct process temp;
	initialise(num,p);
	for(i=0;i<num;i++)
    	{	
		p[i].p_comp=0;
        	pos=i;
       		for(j=i+1;j<num;j++)
        	{
        	    if(p[j].at<p[pos].at)
        	        pos=j;
        	}
 
        	temp=p[i];
		p[i]=p[pos];
		p[pos]=temp;
    	}

	float avg_wt=0.0,avg_tat=0.0;	
	int tst=0,k,flag,new_process,curr=-1;
	i=0;
	while(time)
	{
		flag=0;
		k=0;

		while(p[k].at<=tst && k<num)
		{
			if(p[k].p_comp==0)
			{	flag=1;
				break;
			}
			k++;
		}
		if(flag==0)
		{
			tst+=1;
			continue;
		}
		new_process=0;
		for(j=0;j<num;j++)
			if(p[j].at==tst)
			{
				new_process=1;
				break;
			}
		if(new_process==1)
		{
			if(curr==-1)
			{
				curr=j;
				p[curr].st=tst;
				p[curr].wt=tst-p[curr].at;
			}
			if(p[curr].prty > p[j].prty)
			{
				p[curr].ht=tst;
				printf("pre-empting... Process:%d ",p[curr].pid);
				sortprior(p,curr,j+1);
				p[curr].st=tst;
				printf("replaced by Process:%d\n",p[curr].pid);
				if(p[curr].remain_t==p[curr].cpu_burst)
					p[curr].wt=tst-p[curr].at;
				else
					p[curr].wt+=p[curr].st-p[curr].ht;
			}
		}

		p[curr].remain_t-=1;
		time-=1;
		tst+=1;
		if(p[curr].remain_t==0)
		{
			p[curr].p_comp=1;
			if(p[curr+1].at<=tst && curr+1<num)
			{
				curr++;
				p[curr].st=tst;
				if(p[curr].remain_t==p[curr].cpu_burst)
					p[curr].wt=tst-p[curr].at;
				else
					p[curr].wt+=p[curr].st-p[curr].ht;
			}
			else 
				curr=-1;
		}

		
			
		
	}
	for(i=0;i<num;i++)
	{
		avg_wt+=p[i].wt;
		p[i].tat=p[i].wt+p[i].cpu_burst;
		avg_tat+=p[i].tat;
	}
	//display(num,p);
	printf("Average wt = %f\n",avg_wt/num);
	printf("Average tat = %f\n",avg_tat/num);						
}
