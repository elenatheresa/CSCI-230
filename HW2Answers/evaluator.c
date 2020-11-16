/*
program#2

An evaluator in C program to calculate the value of simple arithmetic expressions.
- only +, -, *, / operators are allowed.
- need to allow parenthesis ( ).
 Such as, 7+5*8-4/(2-1)+6/2*3-6/(2*3)+(5+(3*(2+1)+2)*6)*3.
- Any level of parenthesis
- allow white spaces in the expression.
- assume that all operands are integers.
- report error on dividing by zero.


*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>



// structure for stack
typedef struct stack_type
{
	int top;
	int items[100];

}stack;

// evaluator functions
int precedence(char op);
int calculate(int a, int b, char op);
int evaluate(char* tokens);

// stack functions
void push(stack* stk, int value);
int pop(stack* stk);
int peek(stack* stk);
int is_empty(stack* stk);

int main()
{
	// print program title
	printf("program 2\n");

	// make expression
	char exp[100] = "7+5*8-4/(2-1)+6/2*3-6/(2*3)+(5+(3*(2+1)+2)*6)*3";

	// evaluate
	printf("Evaluate: %s\n", exp);

	// print result
	printf("%d\n", evaluate(exp));
	return 0;
}

// return precedence of operators. 
int precedence(char op) {
	if (op == '+' || op == '-')
		return 1;
	else if (op == '*' || op == '/')
		return 2;
	else return 0;
}

// do calculation
int calculate(int a, int b, char op)
{
	switch (op)
	{
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/':

		// divide by zero
		if (b == 0)
		{
			printf("divide by zero encountered\n");
			return 0;
		}

		else
		{
			return a / b;
		}

	default: return 0;
	}
}

// evaluate expression and return result 
int evaluate(char* exp) {

	unsigned int i = 0;
	int number = 0;
	int num1;
	int num2;
	int result;
	char op;

	// stack to store integer values. 
	stack values_stk;
	values_stk.top = 0;

	// stack to store operators. 
	stack ops_stk;
	ops_stk.top = 0;

	// loop through expression
	for (i = 0; i < strlen(exp); i++)
	{

		// skip white space 
		if (exp[i] == ' ')
			continue;

		// store open parenthesis 
		else if (exp[i] == '(')
		{
			push(&ops_stk, exp[i]);
		}

		// store number 
		else if (isdigit(exp[i]))
		{
			number = 0;

			// get all digits for number 
			while (i < strlen(exp) && isdigit(exp[i]))
			{
				number = (number * 10) + (exp[i] - '0');
				i++;
			}
			i--; // back one
			// store nunber
			push(&values_stk, number);
		}

		// end parenthesis encountered
		else if (exp[i] == ')')
		{
			// loop to start of open parentehesis
			while (!is_empty(&ops_stk) && peek(&ops_stk) != '(')
			{
				// get second number
				num2 = pop(&values_stk);


				// get first number
				num1 = pop(&values_stk);


				// get operation
				op = pop(&ops_stk);


				// calculate opaeration 
				result = calculate(num1, num2, op);

				// push result onto stack
				push(&values_stk, result);
			}

			// pop opening brace. 
			if (!is_empty(&ops_stk))
				pop(&ops_stk);
		}

		// Current token is an operator. 
		else
		{
			// loop while top of ops stack has same or greater precedence to current token
			// Apply operator on top  of ops stack to top two elements in values stack. 
			while (!is_empty(&ops_stk) && precedence(peek(&ops_stk)) >= precedence(exp[i]))
			{
				// get number 2
				num2 = pop(&values_stk);

				// get number 1
				num1 = pop(&values_stk);

				// get operation
				op = pop(&ops_stk);

				// do calculation
				result = calculate(num1, num2, op);

				// push result onto stack
				push(&values_stk, result);
			}

			// Push current token to 'ops'. 
			push(&ops_stk, exp[i]);
		}
	}

	// apply remaining ops to remaining values in stack 
	while (!is_empty(&ops_stk))
	{

		// get number 2
		num2 = pop(&values_stk);

		// get number 1
		num1 = pop(&values_stk);

		// get result
		op = pop(&ops_stk);

		// do calculation
		result = calculate(num1, num2, op);

		// push result onto stack
		push(&values_stk, result);
	}

	// top of stack contains final result
	result = pop(&values_stk);
	return result;
}


// stack functions

// push item onto stack
void push(stack* stk, int value)
{
	stk->items[stk->top] = value;
	(stk->top)++;
}

// pop item from stack
int pop(stack* stk)
{
	int value = 0;
	(stk->top)--;
	value = stk->items[stk->top];
	return value;
}

// get top of stack
int peek(stack* stk)
{
	int value = stk->items[(stk->top) - 1];
	return value;
}

// return true if stack empty
int is_empty(stack* stk)
{
	return stk->top == 0;
}

