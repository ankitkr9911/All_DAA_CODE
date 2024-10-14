#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node* left;
    struct node* right;
};

struct node* CreateNode(int data)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct node* InsertNode(struct node* root,int value)
{
    if(root==NULL)
    {
        struct node* root = CreateNode(value);
        return root;
    }

    struct node* queue[100];
    int front=0;
    int rear =0;
    queue[rear++] = root;
    while(front!=rear)
    {
        struct node* temp = queue[front++];//front=1
        if(temp->left==NULL)
        {
            temp->left = CreateNode(value);
            break;
        }
        else{
            queue[rear++] = temp->left;//rear=2;
        }

        if(temp->right==NULL)
        {
            temp->right = CreateNode(value);
            break;
        }
        else{
            queue[rear++] = temp->right;//rear=3
        }
    }
    return root;
}

void preorderTraversal(struct node* root) {
    if (root!=NULL)
    {  
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void inorderTraversal(struct node* root) {
    if (root!=NULL)
    {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void postorderTraversal(struct node* root) {
    if (root != NULL)
    {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

void levelorderTraversal(struct node* root)
{
    if(root==NULL)
    {
        return ;
    }
    struct node* queue[100];
    int front =0 ;
    int rear =0;
    queue[rear++] = root;
    printf("%d ",root->data);
    while(front!=rear)
    {
        struct node *temp = queue[front++];
        if(temp->left!=NULL)
        {
            queue[rear++] = temp->left;
            printf("%d ",temp->left->data);
        }
        if(temp->right!=NULL)
        {
            queue[rear++] = temp->right;
            printf("%d ",temp->right->data);
        }
    }
}

void print2D(struct node* root,int space)
{
    if(root==NULL)
    {
        return;
    }

    space += 10;
    //print the right binary subtree
    print2D(root->right,space);
    printf("\n");
    for(int i=10;i<space;i++)
    {
        printf(" ");
    }
    printf("%d ",root->data);

    print2D(root->left,space);
}

int main()
{
    struct node* root = CreateNode(12);
    root= InsertNode(root,34);
    root= InsertNode(root,54);
    root= InsertNode(root,64);
    root= InsertNode(root,14);
    root= InsertNode(root,4);

    printf("Level order traversal of the tree is : \n");
    levelorderTraversal(root);
    printf("\nPictorial representation of the tree is:\n");
    print2D(root,0);
    return 0;
}