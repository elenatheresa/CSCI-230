#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* left;
    struct node* right;
};

struct node* newNode(int data)
{
    struct node* node = (struct node*)
        malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

void reversePostorder(struct node* node)
{
    if (node == NULL)
        return;
    reversePostorder(node->right);
    reversePostorder(node->left);
    printf("%d ", node->data);
}

void reverseInorder(struct node* node)
{
    if (node == NULL)
        return;
    reverseInorder(node->right);
    printf("%d ", node->data);
    reverseInorder(node->left);
}

void reversePreorder(struct node* node)
{
    if (node == NULL)
        return;
    printf("%d ", node->data);
    reversePreorder(node->right);
    reversePreorder(node->left);

}

int main()
{
    struct node *root = newNode(1);
    root->left       = newNode(-2);
    root->right    = newNode(-3);
    root->left->left   = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    root->left->right->left = newNode(-8);
    root->left->right->right = newNode(-9);
    root->right->right->left   = newNode(10);
    root->right->right->right = newNode(11);
    root->right->right->right->left = newNode(-12);
    root->right->right->right->right = newNode(-13);
    root->right->right->right->right->left   = newNode(14);

    printf("\nReverse Preorder traversal of binary tree is \n");
    reversePreorder(root);
    printf("\nReverse Inorder traversal of binary tree is \n");
    reverseInorder(root);
    printf("\nReverse Postorder traversal of binary tree is \n");
    reversePostorder(root);
    getchar();
    return 0;

}

