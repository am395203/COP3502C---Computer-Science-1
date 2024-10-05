/* COP 3502C Midterm Assignment Two
This program is written by: Amanda Torres */

#include<stdio.h>
#include<stdlib.h>

typedef struct soldier
{
	int data;
	struct soldier *next;
	struct soldier *prev;
	
}soldier;

soldier *head; //pointed to head node in list
soldier *tail; //pointer to last node in list
int soldierCount = 0; //keep track of how many soldier nodes are created;

soldier* create_soldier (int sequence);
soldier* create_reverse_circle(int n);
soldier* rearrange_circle(soldier* head);
int kill(soldier* head, int n, int k);
void display(soldier *h);


int main(void)
{
	soldier *newHead;
	int numSoldiers, skip;
	
	scanf("%d %d",&numSoldiers,&skip);
	
	newHead = create_reverse_circle(numSoldiers);
	printf("List: ");
	display(newHead);
	
	newHead = rearrange_circle(newHead);
	printf("\nAfter Ordering: ");
	display(newHead);
	
	int sur = kill(newHead,numSoldiers,skip);
	printf("\nSurvived:%d\n",sur);
	
}


//////////////////////////Soldier Functions///////////////////////////////////////////////////////////////////////////////////

void display(soldier* head) //displays elements in linked list
{
	soldier *h = head;
	int i =1;
	
	if(head == NULL) //if head == NULL, there are no nodes
	{
		printf("no soldiers\n");
		
	}
	else
	{
		for(i=1;i<=soldierCount;i++) 
		{
			printf("%d ", h->data); //print the data at the specified node
			h = h->next; //move to next node
		}
	
		printf("\n");
	}
}


soldier* create_soldier(int sequence) //creates and returns a node for a soldier
{
	soldier *newSoldier = (soldier*)malloc(sizeof(soldier)); //allocate space for the soldier
	newSoldier->data = sequence; //set data = sequence number
	newSoldier->next = NULL; //set next == NULL
	newSoldier->prev = NULL; //set prev == NULL
	
	return newSoldier; //return the newly created node
	
}


soldier* create_reverse_circle(int n) //creates a linked list of soldier nodes
{
	int i;
	
	for(i = n; i>0; i--) //starting at n for reverse order
	{
		soldier *newSoldier = create_soldier(i); //create a new soldier node with create_soldier for each i

		if(head == NULL) //if no nodes, have head point to newSoldier
		{
			head = newSoldier; //head points at newSoldier
			tail = newSoldier; ///tail also points at newSoldier
			head->next = head; //since circular, head->next and tail->next == head
			tail->next = head;
			
		}
		else //there is a node in the list
		{
			tail->next = newSoldier; //link tail->next to newSoldier 
			newSoldier->prev = tail; //link node to tail
			newSoldier->next = head; //link newSoldier->next to head
			head->prev = newSoldier; //link head-> prev to soldier for circular link
			tail = newSoldier; //get rid of link with previous node and set tail to the newly entered node
			
		}
		soldierCount++;

	}
	
	return head; //return head
}


soldier* rearrange_circle(soldier* head) //rearranges the linked list to the proper order
{
	soldier *tempH = head; //temp pointer to head of linked list
	soldier *nextNode; //temp pointer to next node
	
	do
	{
		nextNode = tempH->next; //point nextNode to temps next address
		tempH->next = tempH->prev; //switch next with prev
		tempH->prev = nextNode; //then set prev to nextNode which was tempH->next
		tempH = nextNode; //set to nextNode to continue
		
	}while(tempH != head);
	
	nextNode = tempH; //set nextNode to point to tempH
	tempH = tail; //set tempH to tail which is now pointing to front
	tail = nextNode; //set tail to nextNode
	
	return tempH; //return tempH
	
}


int kill(soldier* head, int n, int k) //function that kills soldiers based on k-1
{
	soldier *tempH = head;
	soldier *hold = NULL;
	int i,j;
	
	for(i=1;i<n;i++) //repeat for n number of soldiers
	{
		for(j=1;j<k;j++) //from 1 through k-1, skip k-1 nodes
		{
			tempH = tempH->next;	
			
		}
		
		hold = tempH->prev; //set hold to previous node
		hold->next = tempH->next; //next node is tempH->next, to skip tempH
		tempH->next->prev = hold; //set link from prev node hold to next node
		free(tempH); //free the node
		tempH = hold->next; //continue for next node
		soldierCount--;	
	}
	
	return tempH->data; //return the val of final node
}


