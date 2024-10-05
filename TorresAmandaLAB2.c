/*Torres Amanda 
COP 3502C -20Spring-0004 Week 2 lab on Dynamic Memory Allocation */

#include<stdio.h>
#include<stdlib.h>

typedef struct {
	char lastName[30];
	int scoreAssignment;
	int* quizzes;
	int finalScore;
	int totalScore;
}students;

students* readData(FILE*in,int* noOfRecords,int* noOfQuiz);

int main(void)
{
	int N,M,i,j;
	int holdVal = 0;
	int countVal = 0;
	students* studentPtr;
	students studentHScore;
	FILE* ptr = fopen("input.txt","r");
	FILE* fPtrTwo;
	
	
	if(ptr == NULL)//check if file opened
	{
		printf("ERROR FILE NOT OPENED");
		return 0;
	}
	else
	{
		studentPtr = readData(ptr,&N,&M);
	
		for(i=0;i<N;i++)
		{
			if(holdVal <= studentPtr[i].totalScore)//find max total score, if greater than value held
			{
				holdVal = studentPtr[i].totalScore;//set equal to that value
				countVal = i;//set countVal to i value that had highest total score
			}
		}
		
		fclose(ptr);//close first file
	
		fPtrTwo = fopen("output.txt","w");//create a new file for our output 
	
		if (fPtrTwo == NULL)//check if file was created
		{
			printf("ERROR FILE NOT OPENED\n");
			return 0;
		}
		else //printing all the data
		{
			printf("Name: %s\n",studentPtr[countVal].lastName);//print output to screen
			fprintf(fPtrTwo,"Name: %s\n",studentPtr[countVal].lastName);//print to file 
			
			printf("Assignment: %d\n",studentPtr[countVal].scoreAssignment);
			fprintf(fPtrTwo,"Assignment: %d\n",studentPtr[countVal].scoreAssignment);	
					
			printf("Quizzes: ");
			fprintf(fPtrTwo,"Quizzes: ");
			
				for(j=0;j<M;j++)
				{
					printf("%d ",studentPtr[countVal].quizzes[j]);
					fprintf(fPtrTwo,"%d ",studentPtr[countVal].quizzes[j]);
				}
				
			printf("\nFinal Exam: %d\n",studentPtr[countVal].finalScore);
			fprintf(fPtrTwo,"\nFinal Exam: %d\n",studentPtr[countVal].finalScore);
			
			printf("Total: %d\n",studentPtr[countVal].totalScore);
			fprintf(fPtrTwo,"Total: %d\n",studentPtr[countVal].totalScore);
			
			fclose(fPtrTwo);//close second file
		}
	
		free(studentPtr);//free up allocated data
		
	}
	
	return 0;
	
}


students* readData(FILE* in,int* noOfRecords,int* noOfQuiz)//read date function
{
	int i,j,quizSum=0,totalS;
	
	fscanf(in,"%d",noOfRecords);//get value for number of student records (N)
	fscanf(in,"%d",noOfQuiz);//get value for number of quizzes (M)
	students* studentPtrTwo = (students*)malloc((*noOfRecords)*sizeof(students)); //allocating space for N structs
	
	if(studentPtrTwo == NULL)
		printf("WARNING memory not allocated"); //check that memory was allocated and ptr != NULL
	
	
	for(i=0;i<*noOfRecords;i++)
	{
		studentPtrTwo[i].quizzes = (int*)malloc((*noOfQuiz)*sizeof(int));//allocating space for M quizzes
	}
	
	for(i=0;i<*noOfRecords;i++)//scanning in the data from the file
	{
		fscanf(in,"%s",studentPtrTwo[i].lastName);//get last name
		fscanf(in,"%d",&studentPtrTwo[i].scoreAssignment);//score assignment
	
		for(j=0;j<*noOfQuiz;j++)//for M quizzes
		{
			fscanf(in,"%d",&studentPtrTwo[i].quizzes[j]);
			quizSum += studentPtrTwo[i].quizzes[j]; //finding total sum from the quizzes 
		}
	
		fscanf(in,"%d",&studentPtrTwo[i].finalScore);//final score
		totalS = quizSum + studentPtrTwo[i].scoreAssignment + studentPtrTwo[i].finalScore;//set totalS to sum of all scores
		studentPtrTwo[i].totalScore = totalS;//set students total to totalS
		quizSum =0;
	}
	
	return studentPtrTwo;
	
}
	