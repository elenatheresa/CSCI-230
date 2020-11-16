#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HW3part2.h"

int main()
{

	// input infix expression
	//char input[256] = 0;

	token t; 

	// prefix result from tree
	char prefix[256] = { 0 };

	// print program title
	//printf("binary expression tree\n\n");
	
	// print input infix expression
    char input[300];
	printf("input infix expression:\n");
	scanf("%s", input);
	
	// set up token
	t.input = input;
	t.index = 0;
	t.ch = 0;
	t.value = 0;
	nextToken(&t);

	// make tree
	node* tree = expr(&t);
	
	// print tree (optional just used for checking)
	//print_tree(tree,0);

	// convert tree to prefix
	treeToPrefix(tree, prefix);

	// print prefix expression

	printf("prefix expression from binary expression tree:\n");
	printf("%s\n\n", prefix);

	// evaluate tree (optional just used for checking)
	//double x = evaluate_tree(tree);
	//printf("%lf\n", x);

	// evaluate prefix expression
	char* p = prefix;
	double y = evaluatePrefix(&p);

	// print result
	printf("result: %lf\n", y);

	return 0;
}



// get next token from input
int nextToken(token* t)
{
	char z = 0;

	// end of input
	if (t->input[t->index] < ' ')
	{
		return EOL;
	}

	// get next char
	z = t->input[(t->index)++];

	// eat white space
	while (z == ' ' && z != '\n')
	{
		z = t->input[(t->index)++];
	}

	// number
	if (z >= '0' && z <= '9')
	{
		
		t->value = 0;
		while (z >= '0' && z <= '9')
		{
			t->value = t->value * 10;
			z = z - '0';
			t->value = t->value + (int)(z);
			z = t->input[(t->index)++];
		}

		t->type = NUMBER;
	
		z = (t->index)--;
		
	}

	// +
	else if (z == '+')
	{
		t->type = PLUS;
		t->ch = z;
	}

	// -
	else if (z == '-')
	{
		t->type = MINUS;
		t->ch = z;
	}

	// *
	else if (z == '*')
	{
		t->type = MUL;
		t->ch = z;
	}

	// /
	else if (z == '/')
	{
		t->type = DIV;
		t->ch = z;
	}

	// (
	else if (z == '(')
	{
		t->type = LEFT;
		t->ch = z;
	}

	// )
	else if (z == ')')
	{
		t->type = RIGHT;
		t->ch = z;
	}

	// bad input
	else
	{
		printf("bad input expression\n");
		exit(0);
	}

	return t->type;
}

// tree functions


// create tree node
node* createNode(int type,char op, int num, node* left, node* right)
{
	node* n = NULL;
	n = (node*)malloc(sizeof(node));
	n->type = type;
	n->op = op;
	n->num = num;
	n->left = left;
	n->right = right;
	return n;
}

// expr-> term | term + expr | term - expr
node* expr(token* t)
{
	node* n = NULL;
	node* x = NULL;
	node* y = NULL;

	n = term(t);
	x = n;

	switch (t->type) {
	case PLUS:
		nextToken(t);
		y = expr(t);
		n = createNode(OP,'+',0,x,y);
		break;
	case MINUS:
		nextToken(t);
		y = expr(t);
		n = createNode(OP,'-', 0,x, y);
		break;
	default:
		break;
	}

	return n;
}

// term->factor* term | factor / term | factor
node* term(token* t)
{
	

	node* x = factor(t);

	node* n = x;
	node* y = NULL;

	switch (t->type) {
	case MUL:
		nextToken(t);
		y = term(t);
		n = createNode(OP,'*',0, x, y);
		break;
	case DIV:
		nextToken(t);
		y = term(t);
		n = createNode(OP,'/',0, x, y);
		break;
	default:
		break;
	}
	
	return n;

}

// factor-> (expr) | num
node* factor(token* t)
{
	node* n = NULL;
	int val = 0;

	switch (t->type) {
	case NUMBER:
		val = t->value;
		n = createNode(NUM,0,val,NULL, NULL);
		nextToken(t);
		break;
	case LEFT:
		nextToken(t);
		n = expr(t);
		if (t->type != RIGHT)
		{
			printf(") expected\n");
			exit(0);
		}
		nextToken(t);
		break;
	default:
		break;
	}

	return n;
}

// print tree sideways
// just used for checking tree
void printTree(node* n, int level)
{
	int i = 0;

	if (n != NULL)
	{
		printTree(n->right, level + 1);

		for (i = 0; i < level;i++)printf(" ");
		if (n->type == OP) printf("%c\n", n->op);
		if (n->type == NUM) printf("%d\n", n->num);
		printTree(n->left, level + 1);

	}
	
}


