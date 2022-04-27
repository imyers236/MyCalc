#include <iostream>
using namespace std;

#include "myCalc.h"
#include <cstring>


//Write functions in this order.  Constructor and destructor will be built as the
//functions it invokes are written

Calc::Calc(char* argvIn)
{
	// allocates memory to variables
	stk = new Stack[26];
	inFix = argvIn;
	postFix = new char[strlen(inFix)];
	
	if(!CheckTokens())
	{
		cout << "Unexpected Character" << endl;
		exit(EXIT_FAILURE);
	}
	MakeValueTbl();
	Parse();
	if(!CheckParens())
	{
		cout << "Unbalanced Parenthesis" << endl;
		exit(EXIT_FAILURE);
	}
	InFixToPostFix();
	
	
		
	
}

Calc::~Calc()
{}

bool Calc::CheckTokens()
{
 	int i = 0;
 	while (inFix[i] != '\0')
 	{
 		char ch = inFix[i];
 		//checks tokens
 		if (!isdigit(ch) && !isupper(ch) && !((ch >= '(') && (ch <= '+')) && (ch != '-') && !(ch == '/'))
 			return false;
		i++;
	}
 	return true;
}

void Calc::MakeValueTbl()
{
	//makes value table
	valueTbl = new int[26];
	valueIdx = 0;
	for(int i = 0; i < 26; i++)
		valueTbl[i] = valueIdx;
}

void Calc::Parse()
{
	//copy variables to transfer
	char* str = new char[strlen(inFix) + 1];
 	strcpy(str, inFix);
 	char* str1 = new char[strlen(inFix) + 1];
 	strcpy(str1, inFix);
 	char* tmp = new char[strlen(inFix) + 1];
 	//intervals
 	int i = 0;
 	int k = 0;
 	int alphC = 0;
 	//changes digits into letters
 	char alph = 'A';
 	while(str[i] != '\0')
 	{
 		char ch = str[i];
 		if (isdigit(ch)) 
 		{
 			tmp[k] = alph + alphC;
 			alphC++;
 			k++;
 			i++;
 			ch = str[i];
 			while (isdigit(ch))
 			{
 				i++;
 				ch = str[i];
 			}
 		}
 		else
 		{
 			tmp[k] = ch;
 			k++;
 			i++;
 		}
 	}
 	//Uses strtok to find the digit strings and put them in valueTbl
 	char delimiters[] = " ()+-*/";
 	str = strtok(str1,delimiters);
 	while (str != NULL)
 	{
  		valueTbl[valueIdx] = atoi(str);
  		str = strtok(NULL,delimiters);
  		valueIdx++;
 	}
 	//puts the letter expression into inFix
 	strcpy(inFix, tmp);
}

bool Calc::CheckParens()
{
 bool bal = true;
 int i = 0;
 while(inFix[i] != '\0')
 	{
 		char ch = inFix[i];
 		//checks if there is an open parentheis
 		if(ch == '(')
 			stk -> Push('(');
 		else
 		{
 			if(ch == ')')
 			{
 				if(stk -> IsEmpty() == false)
 					stk -> Pop();
 				else
 					bal = false;
 			}
 		}
 		i++;
 	}
 if(bal && stk -> IsEmpty())
 {
 	//checks to make sure the stack is empty
 	bal = true;
 	return bal;
 }
 bal = false;
 return bal;
}

void Calc::DisplayInFix()
{
  		cout << inFix << endl;
}

void Calc::InFixToPostFix()
{
	//put infix to postfix with the stack
	int i = 0;
	int k = 0;
 while(inFix[i] != '\0')
 	{
 		char ch = inFix[i];
 		if (ch == '(')
 			 stk -> Push('(');
 		else if ((ch == '*') || (ch == '+') || (ch == '-') || (ch == '/'))
 			stk -> Push(ch);
 		else if (ch == ')')
 		{
 			while(stk -> Peek() != '(')
 			{
 				postFix[k] = stk -> Peek();
 				stk -> Pop();
 				k++;
 			}
 			stk -> Pop();
 		}
 		else
 		{
 			postFix[k] = ch;
 			k++;
 		}	
 		i++;
 	}
}

void Calc::DisplayPostFix()
{
	cout << postFix << endl;
}

int Calc::Evaluate()
{
 int result = 0;
 int i = 0;
 while(postFix[i] != '\0')
 	{
 		char ch = postFix[i];
 		if ((ch == '*') || (ch == '+') || (ch == '-') || (ch == '/'))
 		{
 			int op2;
 			int op1;
 			//converts operatorands to the number
 			if (stk -> Peek() != result)
 				 op2 = valueTbl[(stk -> Peek() - 'A')];
 			else
 				op2 = result;
 			stk -> Pop();
 			if (stk -> Peek() != result)
 				 op1 = valueTbl[(stk -> Peek() - 'A')];
 			else
 				 op1 = result;
 			//finds the operand and makes the calculation
 			if (ch == '+')
 				 result = op1 + op2;
 			else if (ch == '-')
 				result = op1 - op2;
 			else if (ch == '*')
 				result = op1 * op2;
 			else
 				result = op1 / op2;
 			stk -> Pop();
 			stk -> Push(result);
 		}
 		else
 			stk -> Push(ch);
 		i++;
 	}
 cout << "Result: " << stk -> Peek() << endl;
 return stk -> Peek();
}

int Calc::FindLast(int cur)
{
	cout << "This function was not neccesary for me to use parse since I used a method checked by Dr. De Palma" << endl;
	return 0;
}
