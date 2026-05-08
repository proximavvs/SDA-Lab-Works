#ifndef TREE_H
#define TREE_H

#include <stdio.h>
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
void bfsTraversal(Node *root);

Node* searchNode(Node *root, const char *key);

// задание 6 лабы
Node* deleteNode(Node *root, const char *key);

Node* findMin(Node *root);
Node* findMax(Node *root);

int treeHeight(Node *root);

void saveTreeToFile(Node *root, FILE *f);

void deleteWholeTree(Node *root);

#endif