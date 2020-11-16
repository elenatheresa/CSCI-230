#include<stdio.h>
#include <stdlib.h>
#include<string.h>

struct node
{
 struct node *right,*left,*prev;
 char data;
}*cur,*par,*root=NULL;

void postorder(struct node *);

int main()
{
  char a[100];
  int len,i;
  struct node *newNode;

  printf("Enter Expression\n");
  fgets(a, 100, stdin);
  len = strlen(a);

  for(i=len-1 ; i>=0 ; i--)
  {
   newNode=(struct node *)malloc(sizeof(struct node));
   newNode->data=a[i];
   newNode->left=newNode->right=newNode->prev=NULL;

   if(root==NULL)
   {
     root=newNode;
     cur=par=root;
   }

   else
   {

    if(a[i]=='+' ||a[i]=='-' ||a[i]=='*'||a[i]=='/')
    {

     if(par->right==NULL)
     {
      cur=newNode;
      par->right=cur;
      cur->prev=par;
      par=cur;
     }

     else if(par->left==NULL)
     {
      cur=newNode;
      par->left=cur;
      cur->prev=par;
      par=cur;
     }

    else
    {

     while(par->left!=NULL)
     {
      par=par->prev;
     }
     cur=newNode;
     par->left=cur;
     cur->prev=par;
     par=cur;
    }
   }

   else
   {

    if(par->right==NULL)
    {
     cur=newNode;
     par->right=cur;
     cur->prev=par;
    }

    else if(par->left==NULL)
    {
     cur=newNode;
     par->left=cur;
     cur->prev=par;
    }

    else
    {

     while(par->left!=NULL)
     {
      par=par->prev;
     }
     cur=newNode;
     par->left=cur;
     cur->prev=par;
    }
   }
  }
 }

 postorder(root);

 return 0;
}

void postorder(struct node *root)
{
 if(root!=NULL)
 {
  postorder(root->left);
  postorder(root->right);
  printf("%c\t",root->data);
 }
}