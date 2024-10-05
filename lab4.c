/*Torres Amanda 
COP 3502C -20Spring-0004 lab 4: Simulate a call center queue system */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define EMPTY -1
#define INIT_SIZE 6

typedef struct customer
{
	int account_no;
	char name[100];
	
}customer;

struct queue 
{
 customer* elements; 
 int front;
 int numElements;
 int queueSize;
};

void init(struct queue* qPtr);
void enqueue(struct queue* qPtr); 
void dequeue(struct queue* qPtr);
int empty(struct queue* qPtr);
void displayQueue(struct queue* qPtr);

int main(void)
{
	int i;
	char choice[2] = {'c','s'};
	struct queue* myQueue = (struct queue*)malloc(sizeof(struct queue));
	init(myQueue);
	rand()%2;
	
	for( ; ; )
	{
		if(choice[rand()%2] == 'c')
		{
			enqueue(myQueue);
			rand()%2;
			
		}
		else if(choice[rand()%2] == 's')
		{
			dequeue(myQueue);
			rand()%2;
				
		}
		
	}	
	
}


////////Queue functions//////////////////////////////////

void init(struct queue* qPtr)//initialize the queue
{

	qPtr->elements = (struct customer*)malloc(sizeof(struct customer)*INIT_SIZE);
	qPtr->front = 0;
	qPtr->numElements = 0;
	qPtr->queueSize = INIT_SIZE;
	
}


void enqueue(struct queue* qPtr)
{
	if(qPtr->numElements == qPtr->queueSize) //if elements == size, then queue is full
	{
		printf("\nQueue is full.call again later.\n");
		printf("Currently in queue: \n"); 
		displayQueue(qPtr); //display who is in the queue
	}
	else //else there is space available in queue
	{
		printf("\nEnter account number: ");
		scanf("%d",&qPtr->elements[(qPtr->front+qPtr->numElements)%qPtr->queueSize].account_no);
	
		printf("Enter name: ");
		getchar();
		scanf("%[^\n]s",qPtr->elements[(qPtr->front+qPtr->numElements)%qPtr->queueSize].name);
		
		qPtr->numElements++; //increase number of elements
		printf("\n");
		displayQueue(qPtr); //display the queue
	}

}


void dequeue(struct queue* qPtr)
{
    if (empty(qPtr)) //if empty, nothing to dequeue
	{
		printf("Queue is empty.No one to serve.\n");

	}
	else //else move front and decrease number of elements
	{
		printf("\nCustomer served.\n");
		qPtr->front = (qPtr->front + 1)%qPtr->queueSize;
		qPtr->numElements--;
		displayQueue(qPtr);
	}

}


int empty(struct queue* qPtr)
{
	  return qPtr->numElements == 0;
}


void displayQueue(struct queue* qPtr)
{
	int i,j;
	
	if(empty(qPtr))
	{
		printf("Queue is empty.\n");
	}
	printf("The queue is: \n");
	if(qPtr->front+qPtr->numElements < qPtr->queueSize)
	{
		for(i=qPtr->front;i<qPtr->front+qPtr->numElements;i++)
		{
			printf("%d %s\n",qPtr->elements[i].account_no,qPtr->elements[i].name);
		}
	}
	else
	{
		for(i=qPtr->front;i<qPtr->queueSize;i++)
		{
			printf("%d %s\n",qPtr->elements[i].account_no,qPtr->elements[i].name);
		}
		
		for(i=0;i<(qPtr->front+qPtr->numElements)%qPtr->queueSize;i++)
		{
			printf("%d %s\n",qPtr->elements[i].account_no,qPtr->elements[i].name);
		}
		
	}
	
}

