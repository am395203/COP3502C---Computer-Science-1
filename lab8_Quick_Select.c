/*Torres Amanda 
COP 3502C -20Spring-0004 lab 8: Quick Select */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 6

void swap(int* a, int* b);
int partition(int *vals, int low, int high);
int quickSelect(int *list, int left, int right, int k); 

int main(void)
{
	int i,userInput,answer;
	int arr[SIZE] = {10,3,5,17,8,0};
	
	printf("Array: ");
	
	for(i=0;i<6;i++)
	{
		printf("%d ",arr[i]);

	}
	
	printf("\nWhich ranked element do you wish to find?(must be > 0):"); //ask user for the desired rank
	scanf("%d",&userInput);
	
	if(userInput > SIZE || userInput < 0) //if user input is not within range
	{
		printf("invalid input\n");
		
	}
	else //else go through with quick select 
	{
		answer = quickSelect(arr,0,SIZE-1,userInput); //get and display the answer 
		printf("The ranked element %d is %d.\n",userInput,answer);
		
	}
	
}

////////////////Quick Select, Partition,Swap//////////////////////////////
int quickSelect(int *list, int left, int right, int k)
{
	
	if(left == right) //if only number, return list[left]
	{
		return list[left];
		
	}
	
	int pivotIndex = partition(list,left,right); //partition the array
	
	if(k-1 == pivotIndex) //partition element is what were looking for 
	{
		return list[pivotIndex]; //so return it 
		
	}
	else if(k-1 < pivotIndex) //element is smaller than the partition element
	{
		return quickSelect(list,left,pivotIndex-1,k); //focus on left side of array
		
	}
	else //else its larger, so focus on right side of array 
	{
		return quickSelect(list,pivotIndex+1,right,k);
		
	}
	
}


void swap(int* a, int* b) //swap function
{
    int t = *a;
    *a = *b;
    *b = t;
}


int partition(int *vals, int low, int high) //partition function
{
  // Pick a random partition element and swap it into index low.
  int i = low + rand()%(high-low+1);
  swap(&vals[low], &vals[i]);

  int lowpos = low; //here is our pivot located.

  low++; //our starting point is after the pivot.

// Run the partition so long as the low and high counters don't cross.
  while(low<=high)
  {
    // Move the low pointer until we find a value too large for this side.
    while(low<=high && vals[low]<=vals[lowpos]) low++;

    // Move the high pointer until we find a value too small for this side.
    while(high>=low && vals[high] > vals[lowpos]) high--;

    // Now that we've identified two values on the wrong side, swap them.
    if (low<high)
     swap(&vals[low], &vals[high]);
  }

  // Swap the pivot element element into its correct location.
  swap(&vals[lowpos], &vals[high]);

  return high; //return the partition point
}

