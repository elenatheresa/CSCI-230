/**
 * evalutate_prefix.c
 * convert binary expresion tree to prefix
 * evaluate prefix expression
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HW3part2.h"

// tree to prefix
void treeToPrefix(node* n, char* s)
{
	char buffer[100] = { 0 };

	if (n != NULL)
	{
		// process node type

		// operator
		if (n->type == OP)
		{
			sprintf(buffer, "%c ", n->op);
		}

		// number
		if (n->type == NUM)
		{
			sprintf(buffer, "%d ", n->num);
		}

		// add to infix string
		strcat(s, buffer);

		// traverse throgh tree
		treeToPrefix(n->left, s);
		treeToPrefix(n->right, s);

	}

}

// evaluate tree directly
// used for checking only
double evaluateTree(node* n) {
	double x = 0, y = 0, z = 0;
	
	// ip op
	if (n->type == OP) {
		x = evaluateTree(n->left);
		y = evaluateTree(n->right);

		// do operation
		if (n->op == '+')
			z = x + y;
		else if (n->op == '-')
			z = x - y;
		else if (n->op == '*')
			z = x * y;
		else if (n->op == '/')
			z = x / y;
		return z;
	}

	// return number
	else return n->num;
}

// evaluate infix expression
double evaluatePrefix(char** input) {

	double val = 0;

	// eat white space
	while (**input == ' ')
	{
		(*input)++;
	}

	// if a number
	if (**input >= '0' && **input <= '9') {

		while (**input >= '0' && **input <= '9')
		{
			val = val * 10;
			val = val + (**input - '0');
			(*input)++;
		}

		return val;
	}

	// operator
	else {

		char operator = **input;
		(*input)++;
		double op1 = evaluatePrefix(input);
		double op2 = evaluatePrefix(input);

		// do operation
		return calculateOperation(operator, op1, op2);
	}
}

// return result of operation
double calculateOperation(char op, double op1, double op2) {

    // add
	if (op=='+') {
		return op1 + op2;
	}

	// minus
	else if (op=='-') {
		return op1 - op2;
	}

	// mul
	else if (op=='*') {
		return op1 * op2;
	}

	// divide
	else if (op == '/') {

		// handle divide by zero
		if (op2 == 0)
		{
			printf("divide by zero encountered\n");
			return 0;
		}
		else
		{
			return op1 / op2;
		}
	}

	else return 0; // default

}

