#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node* left;
    struct node* right;
};

struct node* createNode(int value)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct node* insertNode(struct node* root,int value)
{
    if(root==NULL)
    {
        return createNode(value);
    }
    else if(value>root->data)
    {
        root->right = insertNode(root->right,value);
    }
    else{
        root->left = insertNode(root->left,value);
    }
    return root;
}

void inorderTraversal(struct node* root) {
    if (root!=NULL)
    {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void insertionSort(int A[],int size)
{
    int key,i;
    for(i=1;i<size;i++)
    {
        int j = i-1;
        key = A[i];
        while(j>=0 && A[j]>key)
        {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = key;
    }
}

void kthSmallestNumber(int A[],int size)
{
    int k;
    insertionSort(A,size);
    printf("Enter the k value: ");
    scanf("%d",&k);

    printf("\nThe kth smallest Value is: %d",A[k-1]);
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

void traversal(int arr[],int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}


int main()
{
    struct node* root = createNode(500);
    root = insertNode(root,200);
    root = insertNode(root,700);
    root = insertNode(root,100);
    root = insertNode(root,250);

    printf("Pictorial representation of the tree is:\n");
    print2D(root,0);

    printf("\nThe Elements of the tree in the sorted order:\n");
    inorderTraversal(root);
    printf("\n");


    int arr[] = { 500, 200, 700, 100, 250};
    printf("Elements in the array are as follows:\n");
    traversal(arr,5);
    kthSmallestNumber(arr,5);

    return 0;

}