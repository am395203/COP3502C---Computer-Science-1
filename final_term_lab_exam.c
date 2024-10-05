/* COP 3502C Final term Lab Exam 
This program is written by: Amanda Torres */

#include<stdio.h>
#include<stdlib.h>


struct node 
{
	int key;
	int count;
	struct node *left;
	struct node *right;
	
};
struct node* root;


struct node *createNode(int key, int count);
struct node *insert(struct node *root, int key, int count);
struct node *findMax(struct node *root);
void inOrder(struct node *root, FILE *fOut);
int totalIncome(struct node *root);
int totalLeaf(struct node *root);


int main(void)
{
	FILE *inFile;
	FILE *outFile;
	int N,i,tempK,tempC,leafN,total;
	struct node *max;
	
	inFile = fopen("in.txt","r");
	outFile = fopen("out.txt","w");
	
	if(inFile == NULL)
	{
		printf("ERROR. FILE FAILED TO OPEN\n");
		return 0;
		
	}
	
	fscanf(inFile,"%d",&N);

	for(i=0; i<N; i++)
	{
		fscanf(inFile,"%d %d", &tempK,&tempC);
		root = insert(root,tempK,tempC);
		
	}
	
	printf("Tree constructed from the file\n");
	fprintf(outFile,"Tree constructed from the file\n");
	
	printf("In-order:");
	fprintf(outFile,"In-order:");
	inOrder(root,outFile);
	
	max = findMax(root);
	printf("\nHighest income: %d Total people with highest income: %d\n",max->key,max->count);
	fprintf(outFile,"\nHighest income: %d Total people with highest income: %d\n",max->key,max->count);
	
	leafN = totalLeaf(root);
	printf("Total single children in the tree: %d\n",leafN);
	fprintf(outFile,"Total single children in the tree: %d\n",leafN);
	
	total = totalIncome(root);
	printf("Total income in the area: %d\n",total);
	fprintf(outFile,"Total income in the area: %d\n",total);
	
	fclose(inFile);
	fclose(outFile);
	
}


struct node *createNode(int key, int count) //create new node function
{
	struct node* nNode;
	nNode = (struct node*)malloc(sizeof(struct node)); //allocate memory for new node 
	nNode->key = key; //set key val 
	nNode->count = count; //set count val
	nNode->left = NULL; //left pointer to NULL
	nNode->right = NULL; //right pointer to NULL
	
	return nNode; //return the newly created node 
		
}


struct node *insert(struct node *root, int key, int count) //insert function 
{
	if(root == NULL) //if no nodes then set root to newly created node 
	{
		root = createNode(key,count);
		
	}
	else if(key < root->key) //if current key < tree->key then call insert to the left node 
	{
		root->left = insert(root->left,key,count);
		
	}
	else //else key is > tree->key so call insert to right node 
	{
		root->right = insert(root->right,key,count);
		
	}
	
	return root;	
		
}


struct node *findMax(struct node *root) //find max function 
{
	if(root->right == NULL)//when right child == NULL, no more nodes to right, so we found max val
	{
		return root; //so return root 
		
	}
	else
	{
		return findMax(root->right); //call findMax for root->right 
		
	}
			
}


void inOrder(struct node *root, FILE *fOut) //inOrder function (L,D,R)
{
	if(root == NULL) //when root == NULL then return 
	{
		return;
		
	}
	else
	{
		inOrder(root->left,fOut); //call for left
		printf("(%d,%d),",root->key,root->count); //print data
		fprintf(fOut,"(%d,%d),",root->key,root->count); //print data to file
		inOrder(root->right,fOut); //call for right 
		
	}
	
}


int totalIncome(struct node *root) //total income function 
{
	if(root != NULL) //continue while root != NULL, return (key * count) and continue for left and right nodes 
	{
		return (root->key * root->count) + totalIncome(root->left) + totalIncome(root->right);
		
	}
	else
	{
		return 0;
		
	}
	
}


int totalLeaf(struct node *root) // gets the total number of leaf nodes 
{
	if(root == NULL) //once root == NULL return 0
	{
		return 0;
		
	}
	else if(root->left == NULL && root->right == NULL) //if the node doesnt have a left or right child then it is a leaf, return 1
	{
		return 1;
		
	}
	else //call totalLeaf for right and left and add them up 
	{
		return totalLeaf(root->left) + totalLeaf(root->right);
		
	}
	
}
