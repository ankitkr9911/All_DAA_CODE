#include<stdio.h>
#include<stdlib.h>

#define MAX 3
#define MIN 1

struct BTreeNode{
    int keys[MAX];
    struct BTreeNode* children[MAX+1];
    int numkeys;
    int leaf;
};

struct BTreeNode* createNode(int leaf)
{
    struct BTreeNode* node = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    node->numkeys = 0;
    node->leaf = leaf;
    for(int i=0;i<MAX;i++)
    {
        node->children[i]= NULL;
    }
    return node;
}

void traversal(struct BTreeNode* root)
{
    if(root==NULL)   return;
    int i;

    for(i=0;i<root->numkeys;i++)
    {
        if(!root->leaf)
        {
            traversal(root->children[i]);
        }
        printf("%d ",root->keys[i]);
    }

    // After printing keys, if the node is not a leaf
    if(!root->leaf)
    {
        traversal(root->children[i]);
    }
}
//                 [10, 20]
//                /   |   \
//          [5, 6] [12, 15] [25, 30]

// 5 6 10 12 15 20 25 30


void splitChild(struct BTreeNode* parent, int i) {
    // Get the child node that needs to be split
    struct BTreeNode* child = parent->children[i];

    // Create a new node to store the second half of the keys
    struct BTreeNode* newNode = createNode(child->leaf);

    // Set the number of keys in the new node to MIN
    newNode->numkeys = MIN;

    // Move the last MIN keys from the child to the new node
    for (int j = 0; j < MIN; j++) {
        // Copy keys from the child node to the new node
        newNode->keys[j] = child->keys[j + MIN + 1];
    }

    // If the child is not a leaf, move its children pointers to the new node
    if (!child->leaf) {
        for (int j = 0; j <= MIN; j++) {
            // Copy child pointers from the old child to the new node
            newNode->children[j] = child->children[j + MIN + 1];
        }
    }

    // Reduce the number of keys in the old child node
    child->numkeys = MIN;


    // Make space for the new child in the parent node's children array
    for (int j = parent->numkeys; j >= i + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }

    // Link the new node to the parent node
    parent->children[i + 1] = newNode;

    // Shift the keys in the parent node to make space for the new key
    for (int j = parent->numkeys - 1; j >= i; j--) {
        // Move the keys to the right to create space for the new key
        parent->keys[j + 1] = parent->keys[j];
    }

    // Move the middle key from the child to the parent
    parent->keys[i] = child->keys[MIN];

    // Increase the number of keys in the parent node
    parent->numkeys++;
}


void insertNonFull(struct BTreeNode* node,int key)
{
    int i = node->numkeys - 1;  //Start from the last key in the node

    // If the node is a leaf, insert the key directly
    if(node->leaf)
    {
        // Shift keys to make space for the new key
        while(i>=0 && node->keys[i]>key)
        {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        // Insert the new key at the correct position
        node->keys[i+1] = key;
        node->numkeys++;
    }
    else{
        // The node is not a leaf, find the child where the key needs to go
        while(i>=0 && node->keys[i]>key){
            i--;
        }
        // Move to the correct child (i+1)
        i++;
        // If the child is full, split it
        if(node->children[i]->numkeys==MAX)
        {
            splitChild(node,i);
            // After splitting, decide whether to go to the left or right child
            if(key>node->keys[i]){
                i++;
            }
        }
        // Insert the key into the appropriate child
        insertNonFull(node->children[i],key);
    }
}


void insert(struct BTreeNode** root,int key)
{
    struct BTreeNode* node = *root;

    // Check if the current node is full 
    if(node->numkeys==MAX)
    {
        // Create a new node to become the new root, since the current node is full
        struct BTreeNode* newNode = createNode(0);
        newNode->children[0] = node;
        // Update the root pointer to point to the new node (making it the new root)
        *root = newNode;
        splitChild(newNode,0);
        insertNonFull(newNode,key);
       
    }
    else{
        // If the current node is not full, insert the key into it
        insertNonFull(node,key);
    }
}

int main()
{
    struct BTreeNode* root = createNode(1);

    insert(&root,1);
    insert(&root,2);
    insert(&root,3);
    insert(&root,4);
    insert(&root,5);
    insert(&root,6);
    insert(&root,7);
    insert(&root,8);
    insert(&root,9);
    insert(&root,10);

    traversal(root);

    return 0;
}
