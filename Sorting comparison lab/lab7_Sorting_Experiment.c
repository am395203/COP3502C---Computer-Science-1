/*Torres Amanda 
COP 3502C -20Spring-0004 lab 7: Sorting Experiment */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_VAL 100

void selectionSort(int arr[], int n);  
void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n); 
void mergeSort(int arr[], int l, int r); 
void merge(int arr[], int l, int m, int r); 
void quickSort(int* numbers, int low, int high);
void swap(int* a, int* b);
int partition(int *vals, int low, int high);
long timediff(clock_t t1, clock_t t2);
void fillRand(int *arr, int size, int maxVal);
void copyArray(int *arrOne, int *arrTwo,int size);


int main(void)
{
	int i;
	clock_t start,end;
	int array[] = {10000, 20000, 30000, 40000, 50000, 100000};
	
	for(i=0; i<6; i++)
	{
		int *oriArr = malloc(sizeof(int) * array[i]);
		int *duplicArr = malloc(sizeof(int) * array[i]);
		
		fillRand(oriArr, array[i] ,MAX_VAL);
		copyArray(oriArr,duplicArr,array[i]);
		
		start = clock();
		insertionSort(duplicArr,array[i]); //insertion sort 
		end = clock();
		long elapsed = timediff(start,end);
		printf("\nSorting %d values takes %d milli seconds for Insertion sort\n",array[i],elapsed); 
			
		start = clock();
		bubbleSort(duplicArr,array[i]); //bubble sort
		end = clock();
		elapsed = timediff(start,end);
		printf("\nSorting %d values takes %d milli seconds for Bubble sort\n",array[i],elapsed); 
		
		start = clock();
		selectionSort(duplicArr,array[i]); //selection sort
		end = clock();
		elapsed = timediff(start,end);
		printf("\nSorting %d values takes %d milli seconds for Selection sort\n",array[i],elapsed); 
		
		start = clock();
		mergeSort(duplicArr,0,array[i]-1); //merge sort
		end = clock();
		elapsed = timediff(start,end);
		printf("\nSorting %d values takes %d milli seconds for Merge sort\n",array[i],elapsed); 
		
		start = clock();
		quickSort(duplicArr,0,array[i]); //quick sort
		end = clock();
		elapsed = timediff(start,end);
		printf("\nSorting %d values takes %d milli seconds for Quick sort\n",array[i],elapsed); 
		
		
	}
	
}


///////////////////////////////////////Timediff and array functions////////////////////////////////////////////////////
long timediff(clock_t t1, clock_t t2) 
{
	long elapsed;
	elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
	return elapsed;
	
}


void fillRand(int *arr, int size, int maxVal) //fill the array with random numbers
{
	int i;
	
	for(i=0; i<size; i++)
	{
		arr[i] = rand() % maxVal +1;
	
	}

}


void copyArray(int *arrOne, int *arrTwo,int size) //copy content of 1 array to next 
{
	int i;
	
	for(i=0; i<size; i++)
	{
		arrTwo[i] = arrOne[i];
	
	}
	
}


/////////////Selection Sort//////////////////////////////////////////
void selectionSort(int arr[], int n)
{
	int i, j, min_idx, temp;
	// One by one move boundary of unsorted subarray
	for (i = 0; i < n-1; i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i+1; j < n; j++)
		if (arr[j] < arr[min_idx])
			min_idx = j;
		// Swap the found minimum element with the first element
		temp = arr[i];
		arr[i] = arr[min_idx];
		arr[min_idx] = temp;

	}
}

///////////Bubble Sort/////////////////////////////////////////////////////////
void bubbleSort(int arr[], int n)
{
   int i, j,temp;
   for (i = 0; i < n-1; i++)
   {
        for (j = 0; j < n-i-1; j++)
        {

           if (arr[j] > arr[j+1])
           {//then swap
             temp=arr[j];
             arr[j]=arr[j+1];
             arr[j+1]=temp;
           }
      
        }
		
    }
	
}


///////////Insertion Sort////////////////////////////////////////////////////////
void insertionSort(int arr[], int n)
{
    int i, item, j;
    for (i = 1; i < n; i++)
    {
         item = arr[i];

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
          for(j=i-1; j>=0; j--)
          {
              if(arr[j]>item)
                arr[j+1] = arr[j];
              else
                break;

          }
          arr[j+1] = item;
    }
}


////////////////////Merge Sort//////////////////////////////////////////////////
void mergeSort(int arr[], int l, int r)
{
	if(l<r)
	{
		int m = (l+r)/2;
		mergeSort(arr,l,m); //sort first half 
		mergeSort(arr,m+1,r); //sort second half 
		merge(arr,l,m,r); // merge subarrays 
	
	}
	
}


void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2]; //if your compiler does not support this, create them dynamically.

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}


///////////////Quick Sort///////////////////////////////////////////////////////////
void quickSort(int* numbers, int low, int high) 
{
    // Only have to sort if we are sorting more than one number
    if (low < high) 
	{
        int split = partition(numbers,low,high);
        quickSort(numbers,low,split-1);
        quickSort(numbers,split+1,high);
    }
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}


int partition(int *vals, int low, int high)
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



