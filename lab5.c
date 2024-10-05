/*Torres Amanda 
COP 3502C -20Spring-0004 lab 5:  Implement a queue using linked list*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define EMPTY -1

struct node 
{
 int data;
 struct node* next;
 
};


struct queue 
{
 struct node* front;
 struct node* back;
 
};

void init(struct queue* qPtr);
void enqueue(struct queue* qPtr,int val);
int dequeue(struct queue* qPtr);
int empty(struct queue* qPtr);
int front(struct queue* qPtr);


int main(void)
{
	struct queue* myQueue = (struct queue*)malloc(sizeof(struct queue));
	init(myQueue);
	
	if(empty(myQueue))
	{
		printf("queue is currently empty\n");
	}
	
	enqueue(myQueue,5);
	enqueue(myQueue,18);
	enqueue(myQueue,9);
	enqueue(myQueue,11);
	
	for( ;!(empty(myQueue)); )
	{
		printf("removed %d from queue\n",front(myQueue));
		dequeue(myQueue);
		
	}
	
	if(empty(myQueue))
	{
		printf("queue is currently empty\n");
	}
	
	free(myQueue);
	
	return 0;
	
}

//////////////////queue functions//////////////////////////////////

void init(struct queue* qPtr) //initialize the qPtr
{
	qPtr->front = NULL;
	qPtr->back = NULL;

}


void enqueue(struct queue* qPtr,int val)
{
	struct node* temp; //create temp node
	temp = malloc(sizeof(struct node));
	temp->data = val;
	temp->next = NULL;
	
	if(qPtr->back == NULL) 
	{
		qPtr->front = temp;
		
	}
	else
	{
		qPtr->back->next = temp;
		
	}
	
	qPtr->back = temp;

}


int dequeue(struct queue* qPtr)
{
	int retval; //create value to hold dequeued val
	
	if(qPtr->front == NULL)
	{
		return EMPTY;
		
	}
	else if(qPtr->front != NULL) //if != null
	{
		retval = qPtr->front->data; //set val to temp
		qPtr->front = qPtr->front->next; //set front to next node
		
		if(qPtr->front == NULL)
		{
			qPtr->back = NULL;
			
		}
		
	}
		return retval; //return retval
}


int empty(struct queue* qPtr)
{
	return(qPtr->front == NULL && qPtr->back == NULL); //returns true if empty
	
}


int front(struct queue* qPtr)
{
	if(qPtr->front != NULL) //if front not null
	{
		return(qPtr->front->data); //returns data at the front
		
	}
	else
	{
		return 0;
		
	}
	
}
