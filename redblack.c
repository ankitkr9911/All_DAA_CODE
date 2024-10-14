#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    int color; // 1 for red, 0 for black
    struct node *parent;
    struct node *left;
    struct node *right;
};

struct node *root = NULL;

struct node *BST(struct node *trav, struct node *temp)
{
    if (trav == NULL)
    {
        return temp;
    }
    if (trav->data > temp->data)
    {
        trav->left = BST(trav->left, temp);
        trav->left->parent = trav;
    }
    else if (temp->data > trav->data)
    {
        trav->right = BST(trav->right, temp);
        trav->right->parent = trav;
    }

    return trav;
}

void rightrotate(struct node *temp)
{
    struct node *left = temp->left;
    temp->left = left->right;

    if (temp->left)
    {
        temp->left->parent = temp;
    }
    left->parent = temp->parent;
    if (!temp->parent)
    {
        root = left;
    }
    else if (temp == temp->parent->left)
    {
        temp->parent->left = left;
    }
    else
    {
        temp->parent->right = left;
    }
    left->right = temp;
    temp->parent = left;
}

void leftrotate(struct node *temp)
{
    struct node *right = temp->right;
    temp->right = right->left;
    if (temp->right)
    {
        temp->right->parent = temp;
    }
    right->parent = temp->parent;
    if (!temp->parent)
    {
        root = right;
    }
    else if (temp == temp->parent->left)
    {
        temp->parent->left = right;
    }
    else
    {
        temp->parent->right = right;
    }
    right->left = temp;
    temp->parent = right;
}

void fixup(struct node *ptr)
{
    struct node *parent_ptr = NULL;
    struct node *grandparent_ptr = NULL;

    while ((ptr != root) && (ptr->color != 0) && (ptr->parent->color == 1))
    {
        parent_ptr = ptr->parent;
        grandparent_ptr = ptr->parent->parent;

        /*  Case : A
             Parent of pt is left child
             of Grand-parent of ptr */

        if (parent_ptr == grandparent_ptr->left)
        {
            struct node *uncle_ptr = grandparent_ptr->right;
            /* Case : 1
               The uncle of pt is also red
               Only Recoloring required */

            if (uncle_ptr != NULL && uncle_ptr->color == 1)
            {
                grandparent_ptr->color = 1;
                parent_ptr->color = 0;
                uncle_ptr->color = 0;
                ptr = grandparent_ptr;
            }
            else
            {
                /* Case : 2
                     pt is right child of its parent
                     Left-rotation required */
                if (ptr == parent_ptr->right)
                {
                    leftrotate(parent_ptr);
                    ptr = parent_ptr;
                    parent_ptr = ptr->parent;
                }

                /* Case : 3
                     pt is left child of its parent
                     Right-rotation required */

                rightrotate(grandparent_ptr);
                int t = parent_ptr->color;
                parent_ptr->color = grandparent_ptr->color;
                grandparent_ptr->color = t;
                ptr = parent_ptr;
            }
        }

        /* Case : B
             Parent of pt is right
             child of Grand-parent of
           pt */

        else
        {
            struct node *uncle_ptr = grandparent_ptr->left;
            /*  Case : 1
              The uncle of pt is also red
              Only Recoloring required */
            if ((uncle_ptr != NULL) && (uncle_ptr->color == 1))
            {
                grandparent_ptr->color = 1;
                parent_ptr->color = 0;
                uncle_ptr->color = 0;
                ptr = grandparent_ptr;
            }
            else
            {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (ptr == parent_ptr->left)
                {
                    rightrotate(parent_ptr);
                    ptr = parent_ptr;
                    parent_ptr = ptr->parent;
                }
                /* Case : 3
                     pt is right child of its parent
                     Left-rotation required */
                leftrotate(grandparent_ptr);
                int t = parent_ptr->color;
                parent_ptr->color = grandparent_ptr->color;
                grandparent_ptr->color = t;
                ptr = parent_ptr;
            }
        }
    }
    root->color = 0; // Ensure the root is always black
}

void inorder(struct node *trav)
{
    if (trav != NULL)
    {
        inorder(trav->left);
        printf("%d ", trav->data);
        inorder(trav->right);
    }
}

int main()
{
    int N = 9;
    int arr[] = {12, 20, 9, 17, 18, 32, 27, 42, 80};

    for (int i = 0; i < N; i++)
    {
        struct node *temp = (struct node *)malloc(sizeof(struct node));

        temp->parent = NULL;
        temp->left = NULL;
        temp->right = NULL;
        temp->data = arr[i];
        temp->color = 1;

        root = BST(root, temp);
        fixup(temp);
    }

    printf("Inorder Traversal of the given tree: ");
    inorder(root);

    return 0;
}