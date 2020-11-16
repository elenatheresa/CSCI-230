//Level Order Traversal of Binary Tree 

#include <stdio.h> 
#include <stdlib.h> 
#define maxSize 500 

struct node 
{ 

    int data; 
    struct node* left; 
    struct node* right; 
}; 

  

struct node** createqueue(int *, int *, int *); 
void enqueue(struct node **, int *,int *, struct node *); 
struct node *dequeue(struct node **, int *, int *); 

int isEmpty(struct node *queue, int *size){
    return (*size == 0);
}
void printLevelOrder(struct node* root) 
{ 

    int rear, front, size; 
    struct node **queue = createqueue(&front, &rear, &size); 

    enqueue(queue, &rear, &size, root);
    int count = 0;
    while (!(isEmpty(*queue, &size)))
    { 
        int sum = 0;
        int levelNodes = size;
        int i = 1;
        printf("(Level %d), ", count);
        
        while (levelNodes > 0)
        {
            struct node *n = dequeue(queue, &front, &size);   
            sum = sum + n->data;
            printf("(seq_num = %d value =: %d ),", i ,n->data);
            if(n->right)
                enqueue(queue, &rear,&size, n->right);
            if(n->left)
                enqueue(queue, &rear,&size, n->left);
            levelNodes--;
            i++;   
        }
        printf(" sum = %d",sum);
        printf("\n");
        count++;
    } 
} 

struct node* newNode(int data) 
{ 

    struct node* node = (struct node*) 
                        malloc(sizeof(struct node)); 
    node->data = data; 
    node->left = NULL; 
    node->right = NULL; 
    return(node); 
}   
  
void enqueue(struct node **queue, int *rear,int *size, struct node *new_node) 
{ 
    queue[*rear] = new_node; 
    (*rear)++; 
    (*size)++;
} 


struct node *dequeue(struct node **queue, int *front, int *size) 
{ 
    (*front)++; 
    (*size)--;
    return queue[*front - 1]; 
} 

struct node** createqueue(int *front, int *rear, int *size) 
{ 
    struct node **queue = 
        (struct node **)malloc(sizeof(struct node*)*maxSize); 
    *front = *rear = *size = 0; 
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