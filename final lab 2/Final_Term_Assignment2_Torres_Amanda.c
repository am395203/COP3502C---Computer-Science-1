/* COP 3502C Final term Assignment 2
This program is written by: Amanda Torres */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct treeNode 
{
	char name[25];
	struct treeNode *left;
	struct treeNode *right;
	
}treeNode;
treeNode *root;

treeNode *minVal(treeNode *root);
treeNode *delete(treeNode *root, char name[]);
treeNode *createNewNode(char name[]);
treeNode *insert(treeNode *root, char name[]);
void preOrder(treeNode *root, FILE *fPO);
void postOrder(treeNode *root, FILE *fPO);
void inOrder(treeNode *root, FILE *fPO);
int findHeight(treeNode *root); 
int isBalanced(treeNode* root, FILE *fPO);
int totalCharacters(treeNode *root);
int search(treeNode *root, char name[]);
int countBefore(treeNode* root, char searchKey[]);
 

int main(void)
{
	int i,N,S,D,totalChar,countBef;
	char temp[25];
	FILE * fPIn, *fPOut;
	fPIn = fopen("in.txt","r"); //file pointer to scan in information
	fPOut = fopen("out.txt","w"); //file pointer to print to file
	
	
	if(fPIn == NULL) //fPIn == NULL print error
	{
		printf("ERROR: FILE in.txt NOT OPENED");
		return 0;
		
	}
	if(fPOut == NULL) //fPOut == NULL print error
	{
		printf("ERROR: FILE out.txt NOT CREATED\n");
		return 0;
	}
	
	fscanf(fPIn,"%d %d %d",&N,&S,&D); //scan in N,S, and D
	
	for(i=0; i<N; i++)
	{
		fscanf(fPIn,"%s",temp); //scan in the name
		root = insert(root,temp); //insert into the tree
		
	}
	
	fprintf(fPOut,"Pre Order: "); //pre,in and post order 
	preOrder(root,fPOut);
	fprintf(fPOut,"\nIn Order: ");
	inOrder(root,fPOut);
	fprintf(fPOut,"\nPost Order: ");
	postOrder(root,fPOut);
	
	totalChar = totalCharacters(root); //get total char and print to file 
	fprintf(fPOut,"\nTotal Characters: %d\n",totalChar);
	isBalanced(root,fPOut); //check if balance
	
	fprintf(fPOut,"Search Phase: \n"); //search phase
	for(i=0; i<S; i++)
	{
		fscanf(fPIn, "%s", temp); //scan in from file 
		
		if(search(root,temp)) //if search returns 1
		{
			fprintf(fPOut,"%s Found, ",temp); //print to file that it was found 
			countBef = countBefore(root,temp); //then get the items before
			fprintf(fPOut,"items before: %d\n",countBef);
			
		}
		else //else the function returned 0
		{
			fprintf(fPOut,"%s Not found,items before: 0\n",temp);
			
		}
		
	}
	
	fprintf(fPOut,"Delete Phase: \n"); //delete phase 
	for(i=0; i<D; i++)
	{
		fscanf(fPIn, "%s", temp); //scan in from file 
		
		if(search(root,temp) == 1) //make sure name to be deleted is even in the tree
		{
			fprintf(fPOut,"%s: deleted\n",temp);
			delete(root,temp); //delete the name
			
		}
		else if(search(root,temp) == 0)
		{
			fprintf(fPOut,"%s is not in the tree\n",temp);
			
		}
		
	}
	
	fprintf(fPOut,"In Order: "); //then print to file inOrder 
	inOrder(root,fPOut);
	totalChar = totalCharacters(root); //and get the total characters 
	fprintf(fPOut,"\nTotal Characters: %d\n",totalChar);
	
	fclose(fPIn); //close both files 
	fclose(fPOut);
	
	
}

treeNode *createNewNode(char name[]) //allocate memory and create a new node 
{
	treeNode *newNode = (treeNode*)malloc(sizeof(treeNode)); //allocate memory for node 
	strcpy(newNode->name,name); //copy to name 
	newNode->left = NULL; //set left and right to null
	newNode->right = NULL;
	return newNode; //return the newly created node
	
}


void preOrder(treeNode *root, FILE *fPO) //preorder function 
{
	if(root == NULL) 
	{
		return;
		
	}
	else 
	{
		fprintf(fPO,"%s ",root->name); //print the data first 
		preOrder(root->left,fPO); // call function for left child 
		preOrder(root->right,fPO); //call function for right child
		
	}
	
}


void inOrder(treeNode *root, FILE *fPO) //inorder function
{
	if(root == NULL)
	{
		return;
		
	}
	else
	{
		inOrder(root->left,fPO); //call for left child 
		fprintf(fPO,"%s ",root->name); //print the data 
		inOrder(root->right,fPO); //call for right child 
		
	}
		
}


void postOrder(treeNode *root, FILE *fPO) //post order function
{
	if(root == NULL)
	{
		return;
		
	}
	else
	{
		postOrder(root->left,fPO); //call for left child 
		postOrder(root->right,fPO); //call for right child 
		fprintf(fPO,"%s ",root->name); //then print the data
		
	}
	
}


treeNode *insert(treeNode *root, char name[]) //insertion function 
{
	if(root == NULL) //if ==NULL then create and return the new root
	{
		root = createNewNode(name);
		
	}
	else if(strcmp(name,root->name) <= 0) //if the name is <= name in root node,then insert to left 
	{
		root->left = insert(root->left,name);
		
	}
	else //else its > data so insert to right leaf 
	{
		root->right = insert(root->right,name);
		
	}
	return root;	
		
}


int totalCharacters(treeNode* root) //adds up the total characters in the tree
{
	if(root != NULL) //if root is != NULL, then recursively add left and right nodes continuously for each branch
	{
		return strlen(root->name) + totalCharacters(root->left) + totalCharacters(root->right);
		
	}
	else
	{
		return 0; //else return 0, since root is now NULL	
		
	}
	
}


int findHeight(treeNode *root) //function to find the height of the tree
{
	int leftHeight, rightHeight;
	
	if(root == NULL) //when root == NULL, return -1 to take into account the +1
	{
		return -1;
		
	}
	else //else call findHeight for left and right child 
	{
		leftHeight = findHeight(root->left);
		rightHeight = findHeight(root->right);
		
	}
	
	if(leftHeight > rightHeight) //if left > right then return left height + 1
	{
		return leftHeight + 1;
		
	}
	else //else the right height is > then the left, so return right height + 1
	{
		return rightHeight + 1;

	}
		
}


int isBalanced(treeNode* root, FILE *fPO) //checks whether the tree is balanced (1) or not (0)
{
	int leftH, rightH;
	leftH = findHeight(root->left); //call findHeight for left side of tree
	rightH = findHeight(root->right); //call findHeight for right side of tree
	
	fprintf(fPO,"Height left = %d, height right = %d. ",leftH,rightH);
	
	if(abs(leftH - rightH) > 1) //if the abs val of left - right is > than 1, then the tree is not balanced
	{
		fprintf(fPO,"The tree is imbalanced\n"); //return 0 since it is not balanced 
		return 0;
		
	}
	else //else the tree is balanced so return 1
	{
		fprintf(fPO,"The tree is balanced\n");
		return 1;
		
	}

}


int search(treeNode *root, char name[]) //search for item in tree
{
	if(root == NULL) //if name not found return 0
	{
		return 0;
		
	}
	else if(strcmp(name,root->name) == 0) // if == 0, then the name was found so return 1
	{
		return 1;
		
	}
	else if( strcmp(name,root->name) <= 0) //if name is smaller than the root
	{
		return search(root->left,name); //search to the left
		
	}
	else //else the name is greater than the root
	{
		return search(root->right,name); //so search to the right 
		
	}
	
}


int countBefore(treeNode* root, char searchKey[]) //counts items before searchKey 
{
	int itemsBefore = 0;
	
	if(root != NULL) //if root is not == NULL
	{
		
		if(strcmp(root->name,searchKey) < 0) //check if name at root is < searchKey
		{
			itemsBefore++; //if it is then increase the counter by 1
			
		}
		itemsBefore += countBefore(root->left,searchKey); //add up the items from root->left
		itemsBefore += countBefore(root->right,searchKey); //and root->right 
		
	}	
	return itemsBefore; //then return that count
	
}


treeNode *minVal(treeNode *root) //get and return address to min value
{	
	if(root->left == NULL) //if root->left  == NULL then we have the smallest element 
	{
		return root; //so return that address
		
	}
	else //else theres still more to the left
	{
		return minVal(root->left); //call minVal function for root->left 
		
	}

}


treeNode *delete(treeNode *root, char name[]) //delete function
{
	treeNode *temp;
	
	if(root == NULL) //if root == NULL return the root
	{	
		return root; 

	}
	else if(strcmp(name,root->name) < 0) //if the name is smaller then the name at root 
	{
		root->left = delete(root->left,name); //call delete function for root->left 
		
	}
	else if (strcmp(name,root->name) > 0) //else if the name is larger than the name at root
	{
		root->right = delete(root->right,name); //call delete function for root->right 
		
	}
	else //else get into cases: no children, 1 child or 2 children
	{
		if(root->left == NULL && root->right == NULL) //if both left and right are == NULL, the root is lead node and has no children 
		{ 
			free(root); //so free the root and set it to NULL
			root = NULL;
			
		}
		else if(root->left == NULL) //if only left is == NULL, then there is a child to the right
		{
			temp = root; //set temp to root
			root = root->right; //move root to the right child 
			free(temp); //then free the temp 
			
		}
		else if(root->right == NULL) //if right is == NULL, then there is a child to the left
		{
			temp = root; //set temp to root
			root = root->left; //move root to the left child 
			free(temp); //then free the temp
			
		}
		else //else the node has 2 children 
		{ 
			temp = minVal(root->right); //set temp to the address of the smallest val in the right 
			strcpy(root->name,temp->name); //copy from temp->name to root->name
			root->right = delete(root->right,temp->name); //now delete that name from the right 
			
		}
		
	}
	return root; //return root
	
} 

