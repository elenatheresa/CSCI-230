
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

const int false = 0;

struct node
{
	int data;
	struct node *left;
	struct node *right;
};

struct node *createNode(int data)
{
	struct node *node = (struct node *)malloc(sizeof(struct node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

struct stack
{
	int top;
	unsigned capacity;
	struct node **array;
};

struct stack *createStack(unsigned capacity)
{
	struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
	stack->capacity = capacity;
	stack->top = -1;
	stack->array = (struct node **)malloc(stack->capacity * sizeof(struct node *));
	return (stack);
}

int full(struct stack *stack)
{
	return stack->top == stack->capacity - 1;
}

int empty(struct stack *stack)
{
	return stack->top == -1;
}

void push(struct stack *stack, struct node *node)
{
	if (full(stack))
	{
		printf("stack overflow\n");
		return;
	}
	stack->array[++stack->top] = node;
}

struct node *pop(struct stack *stack)
{
	if (empty(stack))
	{
		printf("stack is empty\n");
		return NULL;
	}

	return stack->array[stack->top--];
}

struct node *peek(struct stack *stack)
{
	if (empty(stack))
	{
		return NULL;
	}

	return stack->array[stack->top];
}

void reverseInOrder(struct node *node)
{
	struct stack *sNode = createStack(20);

	struct node *tempNode = node;
	while (tempNode != NULL || empty(sNode) == false)
	{
		while (tempNode != NULL)
		{
			push(sNode, tempNode);
			tempNode = tempNode->right;
		}
		tempNode = pop(sNode);
		printf("%d ", tempNode->data);
		tempNode = tempNode->left;
	}
}

void reversePostOrder(struct node *node)
{
	struct stack *sNode = createStack(20);
	do
	{
		while (node)
		{
			if (node->left)
			{
				push(sNode, node->left);
			}
			push(sNode, node);
			node = node->right;
		}
		node = pop(sNode);
		if (node->left && peek(sNode) == node->left)
		{
			pop(sNode);
			push(sNode, node);
			node = node->left;
		}
		else
		{
			printf("%d ", node->data);
			node = NULL;
		}
	} while (!empty(sNode));
}

void reversePreOrder(struct node *node)
{
	struct stack *sNode = createStack(20);
	do
	{
		if (!empty(sNode))
		{
			node = pop(sNode);
		}
		while (node)
		{
			printf("%d ", node->data);
			if (node->left)
			{
				push(sNode, node->left);
			}
			node = node->right;
		}

	} while (!empty(sNode));
}

//Test code
int main()
{

	struct node *t = createNode(1);
	t->left = createNode(-2);
	t->right = createNode(-3);
	t->left->left = createNode(4);
	t->left->right = createNode(5);
	t->right->left = createNode(6);
	t->right->right = createNode(7);
	t->left->right->left = createNode(-8);
	t->left->right->right = createNode(-9);
	t->right->right->left = createNode(10);
	t->right->right->right = createNode(11);
	t->right->right->right->left = createNode(-12);
	t->right->right->right->right = createNode(-13);
	t->right->right->right->right->left = createNode(14);
	printf("Reversed Postorder:\n");
	reversePostOrder(t);
	printf("\nReversed Inorder:\n");
	reverseInOrder(t);
	printf("\nReversed PreOrder:\n");
	reversePreOrder(t);
	printf("\n");
	return 0;
}
