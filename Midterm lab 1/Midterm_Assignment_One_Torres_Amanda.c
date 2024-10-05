/* COP 3502C Midterm Assignment One
This program is written by: Amanda Torres */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define EMPTY -1
#define SIZE 51

struct stack
{
	int items[SIZE];
    int top;
};

void initialize(struct stack* stackPtr);
int full(struct stack* stackPtr);
int push(struct stack* stackPtr, int value);
int empty(struct stack* stackPtr);
char pop(struct stack* stackPtr);
int pop_int(struct stack* stackPtr);
int top(struct stack* stackPtr);
int isNumber(char c);
int convertToInt(char c);
int isOperator(char c);
int getOperatorPriority(char c);
int isBalancedParenthesis(char * str);
char* convertToPostfix(char * str);
int calculate(int a, int b, char op);
void evaluateix(char * str);
char* menu();



int main(void)
{
	char* str;
	char* postFix;

	while(strcmp(str = menu(),"exit") != 0)
	{
		if(isBalancedParenthesis(str))
		{
			printf("Infix: %s\n",str );
			printf("Parenthesis: balanced\n");
			postFix = convertToPostfix(str);
			printf("Postfix: %s\n",postFix );
			evaluateix(postFix);
			
		}
		else
		{
			printf("Infix: %s\n",str );
			printf("Parenthesis: unbalanced\n");
			printf("Postfix: n/a\n");
			printf("Value: n/a\n");
			
		} 
	}
	
}

///////////Stack Functions//////////////////////////////////////////////////////////////

void initialize(struct stack* stackPtr)//initializes the stack
{
     stackPtr->top = -1;

}

// Returns true iff the stack pointed to by stackPtr is full.
int full(struct stack* stackPtr) 
{
    return (stackPtr->top == SIZE - 1);
}

int push(struct stack* stackPtr, int value) 
{
    // Check if the stack is full.
    if (full(stackPtr))
        return 0;

    // Add value to the top of the stack and adjust the value of the top.
    stackPtr->items[stackPtr->top+1] = value;
    (stackPtr->top)++;
    return 1;
}

int empty(struct stack* stackPtr) 
{
    return (stackPtr->top == -1);
}

char pop(struct stack* stackPtr) 
{
    int retval;

    // Check the case that the stack is empty.
    if (empty(stackPtr))
        return EMPTY;

    // Retrieve the item from the top of the stack, adjust the top and return
    // the item.
    retval = stackPtr->items[stackPtr->top];
    (stackPtr->top)--;
    return retval;
}
int pop_int(struct stack* stackPtr) //pop int values
{
	int retval;

    // Check the case that the stack is empty.
    if (empty(stackPtr))
        return EMPTY;

    // Retrieve the item from the top of the stack, adjust the top and return
    // the item.
    retval = stackPtr->items[stackPtr->top];
    (stackPtr->top)--;
    return retval;

}


int top(struct stack* stackPtr) 
{

    // Take care of the empty case.
    if (empty(stackPtr))
        return EMPTY;

    // Return the desired item.
    return stackPtr->items[stackPtr->top];
}


///////////////////////////created functions///////////////////////////////////

int convertToInt(char c)//if the character is a number char then convert to int by - '0'
{
	return (c = c - '0');
}

int isNumber(char c)//check if the character being passed is a number or not
{
	if(c <= '9' && c >= '0')
	{
		return 1;
	}
	else if((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a'))
	{
		return 2;
	}
	else
		return 0;
	
}

int isOperator(char c)//determines if the character is an operator 
{
	if( (c == '*') || (c == '/') || (c == '^') || (c == '+') || (c == '-') || (c == '%') )//if one of these then return 1,else return 0
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

int getOperatorPriority(char c)//gets the operator priority 
{
	if(c == '^')
	{
		return 3;
	}
	else if(c == '*' || c == '/' || c =='%')
	{
		return 2;
	}
	else if(c == '+' || c == '-' )
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int isBalancedParenthesis(char * str)//checks if parenthesis are balanced
{
	struct stack stOne;
	initialize(&stOne);
	int i;
	
	for(i=0; str[i] != '\0'; i++)
	{
		if(str[i] == '(') //if == '(' then push to stack
		{
			push(&stOne,str[i]);
			
		}
		else if(str[i] == ')') //if == '(' 
		{
			if(empty(&stOne)) //check if stack is empty
			{
				return 0;
				
			}
			else if(top(&stOne) == '(' ) //if top() == '(', pop it
			{
				pop(&stOne);
				
			}	
		}
	}
	
	if(empty(&stOne)) //if stack is empty then parenthesis are balanced
	{
		return 1;
	}
	else if(!(empty(&stOne))) //else its unbalanced
	{
		return 0;
	}
}

char* convertToPostfix(char * str) //converts the expression to postfix
{
	char* pF = (char*)malloc(sizeof(char) * strlen(str));
	struct stack stTwo;
	initialize(&stTwo);
	int i = 0, j =0;

	for(i=0;i<= strlen(str);i++)
	{
		if(str[i] == ' ') //if ' ' is encountered continue
		{
			continue;
		}
		else if(isNumber(str[i])==1) //if operand, append to pF
		{
			pF[j++] = str[i];
			while(isNumber(str[++i])==1)//if numbers arent separated by ' ' then double digit
			{
				pF[j++] = str[i]; //appened to pF
			}
			i--;
			pF[j++] =' '; //appened next to ' '
		}
		else if(str[i] == '(') //if '(', push to the stack
		{
			push(&stTwo,str[i]);

		}
		else if(isOperator(str[i])) //if an operator, check for any other operator precedence in the stack
		{
			while(getOperatorPriority(top(&stTwo)) >= getOperatorPriority(str[i]) && !(empty(&stTwo)))
			{
				pF[j++] = pop(&stTwo); //if lower priority, keep popping and appending to pF
				
			}
			push(&stTwo,str[i]); //else push next operator
			
		}
		else if(str[i] == ')') //if ')'
		{
			while(top(&stTwo) != '(' && !(empty(&stTwo))) // while top != '(' and !empty
			{
				pF[j++] = pop(&stTwo); //keep popping till found

			}
			pop(&stTwo); //pop '('

		}
		
		else
		{
			while(!(empty(&stTwo))) //pop any remaining 
			{
				pF[j++] = pop(&stTwo);
			}
			
			pF[j] = '\0';//place at end 
		}
		
	}
	return(pF);//return pF expression
}

int calculate(int a, int b, char op) //calculates 2 ints based on passed operator
{
	int i,temp =1;
	switch(op)
	{
		case '+':
			return(a+b);
			break;
			
		case '-':
			return(a-b);
			break;
		
		case '*':
			return(a*b);
			break;
			
		case '/':
			return(a/b);
			break;
		
		case '%':
			return(a%b);
			break;
			
		case '^':
			for(i=0;i<b;i++)
			{
				temp *= a;
			}
			return temp;
			
			break;

	}
}

void evaluateix(char * str) //evaluates the expression and prints the result
{
	struct stack stThree;
	initialize(&stThree);
	int valOne,valTwo,i,result,hold,res;
	char opr;
	
	for(i=0; i<= strlen(str);i++)
	{
		
		if(isOperator(str[i])) //else it is an operator
		{
			opr = str[i]; //set operator to opr
			valTwo = pop_int(&stThree); //pop vals 1 and 2
			valOne = pop_int(&stThree);
			result = calculate(valOne,valTwo,opr); //pass to calculate function
			push(&stThree,result); //push that result into stack
		
		}
		else if(isNumber(str[i]))
		{
			hold = 0;
			while(isNumber(str[i]) ==1)
			{
				hold *= 10; //* hold by 10, ex: digit is 20,
				hold += convertToInt(str[i]); //then add converted char --> == 2, repeats for 0 and gets 20
				i++;
				
			}
			i--;//decrement i due to i++ after last run of while
			push(&stThree,hold);//push hold value
			
		}
	}
	
	result = pop_int(&stThree);
	printf("value: %d\n",result);
	
}

char* menu() //menu function
{
	char* exp;
	char choice,expression[SIZE];
	scanf(" %c",&choice);
	getchar(); 
	
	if(choice == 'e') //if ==e enter expression for evaluation
	{
		scanf("%[^\n]s",expression);
		exp = (char*)malloc(strlen(expression)*sizeof(char)); //allocate memory for pointer
		strcpy(exp,expression); //copy entered expression to pointer exp
		return exp; //return the pointer
	}
	else if(choice == 'x') //else == x
	{
		free(exp); //free up the memory
		return "exit";
		
	}
	
}


