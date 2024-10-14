#include<stdio.h>
#include<stdlib.h>

#define MAX 4
#define MIN 2

struct BTreeNode{
    int keys[MAX];
    struct BTreeNode* children[MAX+1];
    int numkeys;
    int leaf;
    struct BTreeNode* next;
};

struct BTreeNode* createNode(int leaf) {
    struct BTreeNode* node = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    node->numkeys = 0;
    node->leaf = leaf;
    node->next = NULL;
    for(int i = 0; i <= MAX; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void splitChild(struct BTreeNode* parent, int i) {
    struct BTreeNode* child = parent->children[i];
    struct BTreeNode* newNode = createNode(child->leaf);
    
    // In B+ tree, we keep a copy of the middle key in both parent and right child
    newNode->numkeys = MIN;
    
    // Copy the last MIN keys from child to newNode
    for (int j = 0; j < MIN; j++) {
        newNode->keys[j] = child->keys[j + MIN];
    }
    
    // If not leaf, move the corresponding children
    if (!child->leaf) {
        for (int j = 0; j <= MIN; j++) {
            newNode->children[j] = child->children[j + MIN];
        }
    }
    
    // Reduce the number of keys in child
    child->numkeys = MIN;
    
    // Move parent's children to make space for newNode
    for (int j = parent->numkeys; j > i; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    
    // Link newNode to parent
    parent->children[i + 1] = newNode;
    
    // Move parent's keys to make space for middle key from child
    for (int j = parent->numkeys - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    
    // Copy the middle key of child to parent
    parent->keys[i] = child->keys[MIN - 1];
    parent->numkeys++;
    
    // Update leaf node links
    if (child->leaf) {
        newNode->next = child->next;
        child->next = newNode;
    }
}

void insertNonFull(struct BTreeNode* node, int key) {
    int i = node->numkeys - 1;

    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numkeys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->numkeys == MAX) {
            splitChild(node, i);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

void insert(struct BTreeNode** root, int key) {
    struct BTreeNode* node = *root;

    if (node->numkeys == MAX) {
        struct BTreeNode* newNode = createNode(0);
        newNode->children[0] = node;
        *root = newNode;
        splitChild(newNode, 0);
        insertNonFull(newNode, key);
    } else {
        insertNonFull(node, key);
    }
}

void traverse(struct BTreeNode* root) {
    if (root == NULL) return;
    
    // Traverse till leaf level
    while (!root->leaf) {
        root = root->children[0];
    }
    
    // Print all keys in the leaf nodes by following the linked list
    while (root != NULL) {
        for (int i = 0; i < root->numkeys; i++) {
            printf("%d ", root->keys[i]);
        }
        root = root->next;
    }
    printf("\n");
}

int main() {
    struct BTreeNode* root = createNode(1);

    insert(&root, 1);
    insert(&root, 4);
    insert(&root, 7);
    insert(&root, 10);
    insert(&root, 17);
    insert(&root, 21);
    insert(&root, 31);
    insert(&root, 25);
    insert(&root, 19);
    insert(&root, 20);
    insert(&root, 28);
    insert(&root, 42);

    printf("B+ Tree leaf nodes: ");
    traverse(root);

    return 0;
}