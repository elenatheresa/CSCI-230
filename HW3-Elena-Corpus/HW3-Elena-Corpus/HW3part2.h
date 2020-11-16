#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

// constants
#define MAX_CHARS 256

// structure for tree node
typedef struct treeNode
{
	int num;
	char op;
	int type;
	struct treeNode* left;
	struct treeNode* right;
}node;

// labels for operations
enum { NUMBER, PLUS, MINUS, MUL, DIV, LEFT, RIGHT, EOL, OP, NUM };

// structure for tokens
typedef struct tokenType
{
	int value;
	char ch;
	int type;
	char* input;
	int index;

}token;

// expression tree functions

node* createNode(int type, char op, int num, node* left, node* right);
node* expr(token* t);
node* term(token* t);
node* factor(token* t);
int nextToken(token* t);
void printTree(node* n, int level);

// evaluate tree expressions

void treeToPrefix(node* n, char* s);
double evaluateTree(node* n);
double calculateOperation(char op, double operand1, double operand2);
double evaluatePrefix(char** input);

#endif
