#include<stdio.h>
#include<stdlib.h>

int max(int a1,int a2);
struct Node* createNode(int key);
struct Node* insertNode(struct Node* node,int key);
int getHeight(struct Node* node);
int getBalanceFactor(struct Node* node);
void preorder(struct Node* node);
struct Node* leftRotate(struct Node* node);
struct Node* rightRotate(struct Node* node);


struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

int max(int a1,int a2)
{
    return (a1>a2) ? a1 : a2;
}

struct Node* createNode(int key)
{
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->left = NULL;
    temp->right = NULL;
    temp->data = key;
    temp->height = 1;

    return temp;
}

struct Node* insertNode(struct Node* node,int key)
{
    if(node == NULL)
    {
        return createNode(key);
    }
    else if(key<node->data)
    {
        node->left = insertNode(node->left,key);
    }
    else if(key>node->data)
    {
        node->right = insertNode(node->right,key);
    }

    node->height = 1 + max(getHeight(node->left),getHeight(node->right)) ;
    int bf = getBalanceFactor(node);

    if(bf>1 && key<node->left->data)
    {
        return rightRotate(node);
    }
    else if(bf< -1 && key > node->right->data)
    {
        return leftRotate(node);
    }
    else if(bf>1 && node->left!=NULL && key>node->left->data){
        node->left = leftRotate(node);
        return rightRotate(node);
    }
    else if(bf< -1 && node->right!=NULL && key<node->right->data)
    {
        node->right = rightRotate(node);
        return leftRotate(node);
    }

    return node;
}

int getHeight(struct Node* node)
{
    if(node==NULL)
    {
        return 0;
    }
    else{
        return node->height;
    }
}

int getBalanceFactor(struct Node *node)
{
    if(node==NULL)
    {
        return 0;
    }
    int bf = (getHeight(node->left)) - (getHeight(node->right));
    return bf;
}

void preorder(struct Node* node)
{
    if(node!=NULL)
    {
        printf("%d ",node->data);
        preorder(node->left);
        preorder(node->right);
    }
}

struct Node* rightRotate(struct Node* node)
{
    struct Node* x = node->left;
    struct Node* y = x->right;

    x->right = node;
    node->left = y;

    x->height = max(getHeight(x->left),getHeight(x->right)) + 1;
    node->height = max(getHeight(node->left),getHeight(node->right)) + 1;

    return x;
}

// RIGHT ROTATION
//        node    before
//       / \
//      x   C
//     / \
//    A   y
//
//        x     after
//       / \
//      A   node
//         / \
//        y  C


struct Node* leftRotate(struct Node* node)
{
    struct Node* x = node->right;
    struct Node* y = x->left;

    x->left = node;
    node->right = y;

    node->height = max(getHeight(node->left),getHeight(node->right)) + 1;
    x->height = max(getHeight(x->left),getHeight(x->right)) + 1;

    return x;
}
// LEFT ROTATION
//        node      before
//       / \
//      A   x
//         / \
//        y  C
//
//        x      after
//       / \
//      node   C
//     / \
//    A   y

int main()
{
    struct Node* root = NULL;

    root = insertNode(root,1);    
    root = insertNode(root,2);    
    root = insertNode(root,4);    
    root = insertNode(root,5);    
    root = insertNode(root,6);    
    root = insertNode(root,3);

    printf("Preorder Traversal of the given AVL tree is : \n");
    preorder(root);    

    return 0;

}


