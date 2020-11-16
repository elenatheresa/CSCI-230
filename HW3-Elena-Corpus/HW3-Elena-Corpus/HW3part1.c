//Level Order Traversal of Binary Tree 

#include <stdio.h> 
#include <stdlib.h> 
#define maxSize 500 

struct node 
{
    int data; 
    struct node* left; 
    struct node* right;
    int level;
};
  
struct node **createqueue(int *, int *);
void enqueue(struct node **, int *, struct node *);
struct node *dequeue(struct node **, int *);

void printLevelOrder(struct node *root)
{ 
    int sum = 0;
    int currentLevel = 0;
    int seq_num = 1;
    int rear, front;
    struct node **queue = createqueue(&front, &rear);
    struct node *tempNode = root;
    printf("level %d", tempNode->level);
    while (tempNode)
    {
        if (tempNode->level != currentLevel)
        {
            printf(", sum = %d.\n", sum);
            sum = 0;
            currentLevel++;
            seq_num = 1;
            printf("level %d", currentLevel);
            printf(", (seq_num = %d, value = %d)", seq_num, tempNode->data);
            seq_num++;
            sum += tempNode->data;
        }
        else{
            printf(", (seq_num = %d, value = %d)", seq_num, tempNode->data);
            seq_num++;
            sum += tempNode->data;
        }
        if (tempNode->right)
            enqueue(queue, &rear, tempNode->right);
        
        if (tempNode->left)
            enqueue(queue, &rear, tempNode->left);
        
        tempNode = dequeue(queue, &front);
    }
    printf(", sum = %d.\n", sum);
} 

struct node* newNode(int data) 
{
    struct node *node = (struct node*) malloc(sizeof(struct node));
    node->data = data; 
    node->left = NULL; 
    node->right = NULL; 
    return(node); 
}   
  
void enqueue(struct node **queue, int *rear, struct node *new_node)
{ 
    queue[*rear] = new_node; 
    (*rear)++; 
}


struct node *dequeue(struct node **queue, int *front)
{ 
    (*front)++;
    return queue[*front - 1]; 
} 

struct node** createqueue(int *front, int *rear)
{ 
    struct node **queue = 
        (struct node **)malloc(sizeof(struct node*)*maxSize); 
    *front = *rear = 0;
    return queue; 
}
  
int main() 
{ 

    struct node *root = newNode(1); 
    root->left  = newNode(-2); 
    root->right = newNode(-3); 
    root->left->left = newNode(4); 
    root->left->right = newNode(5);
    root->left->right->left = newNode(-8);
    root->left->right->right = newNode(-9);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    root->right->right->left = newNode(10);
    root->right->right->right= newNode(11);
    root->right->right->right->left = newNode(-12);
    root->right->right->right->right = newNode(-13);
    root->right->right->right->right->left= newNode(14);

    printLevelOrder(root);

    return 0; 
}
