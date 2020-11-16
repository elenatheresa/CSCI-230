/*
program#1

Reversed Tree Traversal Without Using Recursion
A recursion-free tree traversal C program to do reversed tree traversal.

Reversed PreOrder:  Root, Right, Left.
Reversed InOrder:     Right, Root, Left.
Reversed PostOrder: Right, Left, Root.

The tree is:
Root = 1, Left(1) = -2, Right(1) = -3;
Left(-2) = 4, Right(-2) = 5;
Left(-3) = 6, Right(-3)= 7;
Left(5) = -8, Right(5)= -9;
Left(7) = 10, Right(7) = 11;
Left(11) = -12, Right(11) = -13;
Left(-13) = 14.

*/

#include <stdio.h>
#include <stdlib.h>

// structure for tree node
typedef struct tree_node
{
	int data;
	struct tree_node* left;
	struct tree_node* right;
}node;

// structure for stack
typedef struct stack_type
{
	int top;
	struct tree_node* items[100];

}stack;

// tree functions
node* create_node(int data);
void pre_order(node* n);
void in_order(node* n);
void post_order(node* n);
void delete_tree(node* n);

// stack functions
void push(stack* stk, node* n);
node* pop(stack* stk);
node* peek(stack* stk);
int is_empty(stack* stk);

int main()
{
	// print program title
	printf("program 1\n");

	// build tree
	node* t = create_node(1);
	t->left = create_node(-2);
	t->right = create_node(-3);
	t->left->left = create_node(4);
	t->left->right = create_node(5);
	t->right->left = create_node(6);
	t->right->right = create_node(7);
	t->left->right->left = create_node(8);
	t->left->right->right = create_node(9);
	t->right->right->left = create_node(10);
	t->right->right->right = create_node(11);
	t->right->right->right->left = create_node(-12);
	t->right->right->right->right = create_node(-13);
	t->right->right->right->right->left = create_node(14);
	
	// pre-order traversal
	printf("pre-order reverse traversal\n");
	pre_order(t);

	// in-order traversal
	printf("\nin-order reverse traversal\n");
	in_order(t);

	// post-order traversal
	printf("\npost-order reverse traversal\n");
	post_order(t);

	return 0;
}


// tree functions

// create tree node
node* create_node(int data)
{
	node* n = (node*)malloc(sizeof(node));
	n->data = data;
	n->left = 0;
	n->right = 0;
	return n;
}

// preorder reverse traversal
void pre_order(node* n)
{
	// Base Case 
	if (n == 0)
		return;

	// Create  stack
	stack stk;
	stk.top = 0;

	// push root onto stack
	push(&stk,n);

	// loop while stack not empty
	while (!is_empty(&stk))
	{
		// pop item from stack 
		node* node = pop(&stk);

		// print node
		printf("%d ", node->data);
	
		// Push left child of node
		if (node->left)
			push(&stk,node->left);

		// Push right children of node
		if (node->right)
			push(&stk,node->right);
	}
}

// inorder reverse traversal
void in_order(node* n)
{
	// make stack
	stack  stk;
	stk.top = 0;
	
	while (n != 0 || !is_empty(&stk))
	{
		// go futhurst right
		while (n != 0)
		{
		    // store on stack
			push(&stk,n);

			// go right
			n = n->right;
		}

		// get net node
		n = pop(&stk);
		
		// print node
		printf("%d ",n->data);

		// get left node
		n = n->left;

	} /* end of while */
}

// post order reverse traversal
void post_order(node* n)
{
	// check for empty tree 
	if (n == NULL)
		return;

	// make stack
	stack stk;
	stk.top = 0;

	do
	{
		// go to right most node 
		while (n)
		{
			// push left child on stack. 
			if (n->left)
				push(&stk, n->left);

			// push root on stack
			push(&stk, n);

			// set to right child   
			n = n->right;
		}

		// pop item from stack     
		n = pop(&stk);


		// if left child and not procesed yet
		if (n->left && peek(&stk) == n->left)
		{
			pop(&stk);  // remove left child from stack 
			push(&stk, n);  // push node back to stack 
			n = n->left; // proceess left child next 						
		}

		// print data
		else  
		{
			printf("%d ", n->data);
		
			n = 0; // clear node
		}

	} while (!is_empty(&stk));
}


// stack functions

// push item onto stack
void push(stack* stk, node* n)
{
	stk->items[stk->top] = n;
	(stk->top)++;
}

// pop item from stack
node* pop(stack* stk)
{
	(stk->top)--;
	node* n = stk->items[stk->top];
	return n;
}

// get top of stack
node* peek(stack* stk)
{
	node* n = stk->items[(stk->top)-1];
	return n;
}

// return true if stack empty
int is_empty(stack* stk)
{
	return stk->top == 0;
}
