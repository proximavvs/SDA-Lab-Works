#ifndef TREE_H
#define TREE_H

#include "data.h"

typedef struct Node {
    Worker data;
    struct Node *left;
    struct Node *right;
} Node;

Node* insertNode(Node *root, Worker w);
void inorder(Node *root);
void preorder(Node *root);
void postorder(Node *root);
Node* searchNode(Node *root, const char *key);
void bfsTraversal(Node *root);
void freeTree(Node *root);

#endif