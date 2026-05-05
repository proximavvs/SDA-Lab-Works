#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node* createNode(Worker w) {
    Node *node = malloc(sizeof(Node));
    node->data = w;
    node->left = node->right = NULL;
    return node;
}

// вставка (по ФИО)
Node* insertNode(Node *root, Worker w) {
    if (root == NULL)
        return createNode(w);

    if (strcmp(w.fio, root->data.fio) < 0)
        root->left = insertNode(root->left, w);
    else
        root->right = insertNode(root->right, w);

    return root;
}

// LNR
void inorder(Node *root) {
    if (!root) return;
    inorder(root->left);
    printWorker(root->data, 0);
    inorder(root->right);
}

// NLR
void preorder(Node *root) {
    if (!root) return;
    printWorker(root->data, 0);
    preorder(root->left);
    preorder(root->right);
}

// LRN
void postorder(Node *root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printWorker(root->data, 0);
}

// поиск по ФИО
Node* searchNode(Node *root, const char *key) {
    if (!root) return NULL;

    int cmp = strcmp(key, root->data.fio);

    if (cmp == 0) return root;
    if (cmp < 0) return searchNode(root->left, key);
    return searchNode(root->right, key);
}

void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}