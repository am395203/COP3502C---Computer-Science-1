/* COP 3502C Final term Assignment 1
This program is written by: Amanda Torres */

#include<stdio.h>
#include<stdlib.h>


struct dataPoint //struct to hold the x and y of each element
{
	int x;
	int y;
	
};


struct dataPoint *ReadData(struct dataPoint *cen, int *rad, int *numEl);
struct dataPoint *FilterData(struct dataPoint *unSorted, int *rad, int *numEl);
void PlaceToFile(struct dataPoint *filtered,int numEl);
int SearchPhase(struct dataPoint *filtered,int numEl);
void MergeSort(struct dataPoint *filtered, int l, int r);
void Merge(struct dataPoint *filtered, int l, int m, int r);
int BinarySearch(struct dataPoint *filtered, int numEl, struct dataPoint point);


int main(void)
{
	
	struct dataPoint *unsorted, *filtered;
	struct dataPoint center;
	int radius,numElements,i;
	
	unsorted = ReadData(&center,&radius,&numElements);
	filtered = FilterData(unsorted,&radius,&numElements);
	MergeSort(filtered, 0, numElements-1);
	PlaceToFile(filtered,numElements);
	SearchPhase(filtered,numElements);
	
	
}


////////////////////////////Reading, Filtering, Sorting Functions////////////////////////////////////////////////////////
struct dataPoint *ReadData(struct dataPoint *cen, int *rad, int *numEl) //reads and returns data from in.txt
{
	struct dataPoint *temp;
	int i;
	FILE *fPoint;
	fPoint = fopen("in.txt","r"); //open file to read data from
	
	if(fPoint == NULL) //check if file was opened properly or not 
	{
		printf("ERROR: File failed to open.\n");

	}
	else
	{
		fscanf(fPoint,"%d %d %d %d", &cen->x,&cen->y,rad,numEl); //scan from file center, radius and number of elements
		temp = (struct dataPoint*)malloc(sizeof(struct dataPoint) * (*numEl) ); //allocate memory for n data points
		
		for(i=0; i<*numEl; i++) //repeat for all elements 
		{
			fscanf(fPoint,"%d %d", &temp[i].x, &temp[i].y); //scan in data points to temp

		}
		fclose(fPoint); //close file now that all the data has been scanned in 
		
	}
	
	return temp; //return temp pointer
}


struct dataPoint *FilterData(struct dataPoint *unSorted,int *rad, int *numEl) //filters data from ReadData, returns points on/within circle
{
	struct dataPoint *filtered;
	int n = *numEl, n2 = *numEl;
	int radius = *rad;
	double r =radius * radius, total;
	int x,y,i,j=0;


	for(i=0; i<n2 ; i++) //filter the number of points within the circle using (x^2 + y^2 = r^2)
	{
		x = unSorted[i].x;
		y = unSorted[i].y;
		total = (x * x) + (y * y);
		
		if( total > r) //if (x^2 + y^2) > r^2 then point is outside the circle
		{
			n--; //subtract number of elements 
			
		}
		
	}
	
	*numEl = n; //change numEl to new number
	filtered = (struct dataPoint*)malloc(sizeof(struct dataPoint) * n); //allocate memory for those n points within/on the circle
	
	for(i=0; i<n2 ; i++)  //now find the points and place them within the filtered list 
	{
		x = unSorted[i].x;
		y = unSorted[i].y;
		total = (x * x) + (y * y);
		
		if( total <= r) //if (x^2 + y^2) <= r^2 then point is inside/on the circle, put into filtered list
		{
			filtered[j].x = unSorted[i].x;
			filtered[j].y = unSorted[i].y;
			j++;

		}

	}
	
	return filtered; //return filtered list
	
}


void PlaceToFile(struct dataPoint *filtered,int numEl)
{
	int i;
	FILE *fPoint;
	fPoint = fopen("out.txt","w");
	
	if(fPoint == NULL) //check if file was opened properly or not 
	{
		printf("ERROR: File failed to open.\n");

	}
	
	for(i=0;i<numEl;i++)
	{
		fprintf(fPoint,"%d %d\n", filtered[i].x,filtered[i].y); //print the sorted data to out.txt
		
	}
	
	printf("filtered and sorted data written to out.txt\n"); //print out confirmation
	fclose(fPoint); //close the file
}


int SearchPhase(struct dataPoint *filtered,int numEl)
{
	struct dataPoint userInput;
	
	for( ; ; )
	{
		printf("Search input: ");
		scanf("%d %d",&userInput.x,&userInput.y); //get user input 
		
		if(userInput.x == -999 || userInput.y == -999) //if -999 for x or y is entered
		{
			printf("Output: exit\n"); //exit the program
			return 0;	
			
		}
		else
		{
			BinarySearch(filtered,numEl,userInput); //else call binary search function to search for user inputed point
			
		}
		
	}

}


/////////////////////////////////////////Merge Sort, Merge, Binary Search Functions////////////////////////////////////
void MergeSort(struct dataPoint *filtered, int l, int r)
{
	if(l<r)
	{
		int m = (l+r)/2; //get the midpoint 
		MergeSort(filtered,l,m); //sort first half from l to m
		MergeSort(filtered,m+1,r); //sort second half from m+1 to r
		Merge(filtered,l,m,r); //merge the subarrays
		
	}
	
}


void Merge(struct dataPoint *filtered, int l, int m, int r)
{
	int i = l; //set i to start at l
	int j = m+1; // j to start after midpoint
	int k = l; //k  to start at l
	
	struct dataPoint T[50]; //create a temp array to hold the values
	
	while(i<=m && j<= r) //continue till i<= midpoint and j<= upper limit
	{
		if(filtered[i].x < filtered[j].x) //if [i].x < [j].x 
		{
			T[k++] = filtered[i++]; // set temp to [i] value
		}
		else if(filtered[i].x == filtered[j].x && filtered[i].y < filtered[j].y) //if [i] == [j] then check y values
		{
			T[k++] = filtered[i++];// set temp to [i] value
		}
		else
		{
			T[k++] = filtered[j++];// set temp to [j] value
		}

	}
	
	while(i<=m) //if there are excess values in [i] array then put them into temp
	{
		T[k++] = filtered[i++];
	}
	
	while(j<=r)//else if there are excess values in [j] array then put them into temp
	{
		T[k++] = filtered[j++];
	}
	
	for(i = l;i<=r;i++)//put the values from temp into original filtered
	{
		filtered[i] = T[i];
	}

}


int BinarySearch(struct dataPoint *filtered, int numEl, struct dataPoint point)
{
	int l = 0;
	int h = numEl - 1;
	int mid,count = 0;
	
	while(l<=h)
	{
		mid = (l+h)/2;
		
		if(filtered[mid].x == point.x && filtered[mid].y == point.y) //if [mid].x && [mid].y are a match then the point is located at mid so break
		{
			count = 1; //when element is found, set count to 1
			break;
	
		}
		else if(filtered[mid].x > point.x ) // if [mid].x is >, then ignore upper half 
		{
			h = mid - 1;

		}
		else if(filtered[mid].x == point.x && filtered[mid].y > point.y) // if [mid].x is == but [mid].y is >, then ignore upper half 
		{
			h = mid - 1;
			
		}
		else // else ignore the bottom half 
		{
			l = mid + 1;
			
		}
	
	}
	
	if(count == 1) //if the element was found 
	{
		count+=mid; //add mid to count to find the location of the element 
		printf("Output: Found at %d\n",count);
	}
	else //else the element was not found
	{
		printf("Output: Not found\n");
	}
	
}

