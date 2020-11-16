#include <stdio.h>
#include <stdlib.h>

typedef struct tNode 
{
  int data; 
  struct tNode* left; 
  struct tNode* right;
}node;

typedef struct sNode
{
  int top;
  struct tNode* items[100];
}stack;

node* createNode(int data);
void preOrder(node* n);
void inOrder(node* n);
void postOrder(node* n);
void deleteTree(node* n);

void push(stack* stck, node* n);
node* pop(stack* stck);
node* peek(stack* stck);
int empty(stack* stck);

int main()
{
   node* t = createNode(1);
   t->left = createNode(-2);
   t->right = createNode(-3);
   t->left->left = createNode(4);
   t->left->right = createNode(5);
   t->right->left = createNode(6);
   t->right->right = createNode(7);
   t->left->right->left = createNode(8);
   t->left->right->right = createNode(9);
   t->right->right->left = createNode(10);
   t->right->right->right = createNode(11);
   t->right->right->right->left = createNode(-12);
   t->right->right->right->right = createNode(-13);
   t->right->right->right->right->left = createNode(14);

   printf("Pre Order\n");
   preOrder(t);

   printf("\nInOrder\n");
   inOrder(t);

   printf("\nPost Order\n");
   postOrder(t);

   return 0;
}

node* createNode(int data)
{
   node* n = (node*)malloc(sizeof(node));
   n->data = data;
   n->left = 0;
   n->right = 0;
   return n;
}

void preOrder(node* n)
{
   if (n==0)
      return;

   stack stck;
   stck.top = 0;

   push(&stck, n);

   while (!empty(&stck))
   {
      node* node = pop(&stck);
      printf("%d", node->data);
      if (node->left)
         push(&stck, node->left);

      if (node->right)
         push(&stck, node->right);
   }
}

void inOrder(node* n)
{
   stack stck;
   stck.top = 0; 

   while (n != 0 || !empty(&stck))
   {
      while (n != 0)
      {
         push(&stck, n);
         n = n->right;
      }

      n = pop(&stck);
      printf("%d", n->data);
      n = n->left;

   }
}

void postOrder(node* n)
{
   if (n == NULL)
      return;

   stack stck;
   stck.top = 0; 

   do
   {
      while (n)
      {
         if (n->left)
            push(&stck, n->left);

         push(&stck, n);
         n = n->right;
      }

      n = pop(&stck);
      if (n->left && peek(&stck) == n->left)
      {
         pop(&stck);
         push(&stck, n);
         n = n->left;
      }

      else
      {
         printf("%d", n->data);
         n = 0; 
      }

   } while (!empty(&stck));
}


void push(stack* stck, node* n)
{
   stck->items[stck->top] = n;
   (stck->top)++;
}

node* pop(stack* stck)
{
   (stck->top)--;
   node* n = stck->items[stck->top];
   return n;
}

node* peek(stack* stck)
{
   node* n = stck->items[(stck->top)-1];
   return n;
}

int empty(stack* stck)
{
   return stck->top == 0;
}


