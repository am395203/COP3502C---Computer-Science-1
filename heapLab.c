/*Torres Amanda 
COP 3502C -20Spring-0004 lab 9: Recursive and iterative heap */

#include<stdio.h>
#include<stdlib.h>

int isHeap_iter(int arr[],int n);
int isHeap_recursive(int arr[], int I, int n);


int main(void)
{
	int arr1[6] = {12,13,14,15,110,115}; //minheap array
	int arr2[6] = {12,110,14,15,13,115}; //not a minheap array
	
	//for array 1 
	if(isHeap_iter(arr1,6)) //iterative:
	{
		printf("Array represents a minheap\n");
	}
	else
	{
		printf("Array does not represent a minheap\n");
	}
	
	
	if(isHeap_recursive(arr1,0,6)) //recursive:
	{
		printf("Array represents a minheap\n");
	}
	else
	{
		printf("Array does not represent a minheap\n");
	}
	

	//for array 2 
	if(isHeap_iter(arr2,6)) //iterative:
	{
		printf("Array represents a minheap\n");
	}
	else
	{
		printf("Array does not represent a minheap\n");
	}
	
	
	if(isHeap_recursive(arr2,0,6)) //recursive:
	{
		printf("Array represents a minheap\n");
	}
	else
	{
		printf("Array does not represent a minheap\n");
	}
	
}


int isHeap_iter(int arr[],int n) //iterative function 
{
	int i;
	
	for(i=0 ;i<=(n-2)/2; i++)
	{
		if(arr[2*i+1] < arr[i]) //check if child is < parent 
		{
			return 0; //return 0 since parent should be < child in minheap
			
		}
		else if((2*i+2)<n && arr[2*i+2] < arr[i]) //else check if left/right are < parent 
		{
			return 0;
			
		}
		
	}
	return 1; //return 1 if all other checks fail since it is a minheap 
	
}


int isHeap_recursive(int arr[], int i, int n) //recursive function
{
	int left, right;
	
	if(2*i+2 > n)
	{
		return 1;
		
	}
	else
	{
		left = (arr[i] <= arr[2*i+1]) && isHeap_recursive(arr,2*i+1,n); //check if left child is heap
		right = (2*i + 2 == n) || (arr[i] <= arr[2*i + 2] && isHeap_recursive(arr,2*i + 2,n)); //check if right child exists,then check if its a heap 
		
	}
	return (left && right); //return true if left and right are heap
	
}







