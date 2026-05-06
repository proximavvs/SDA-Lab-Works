#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node* createNode(Worker w) {
    Node *node = malloc(sizeof(Node));

    node->data = w;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// вставка
Node* insertNode(Node *root, Worker w) {

    if (root == NULL)
        return createNode(w);

    if (strcmp(w.fio, root->data.fio) < 0)
        root->left = insertNode(root->left, w);
    else
        root->right = insertNode(root->right, w);

    return root;
}

// inorder (LNR)
void inorder(Node *root) {

    if (!root)
        return;

    inorder(root->left);

    printWorker(root->data, 0);

    inorder(root->right);
}

// preorder (NLR)
void preorder(Node *root) {

    if (!root)
        return;

    printWorker(root->data, 0);

    preorder(root->left);
    preorder(root->right);
}

// postorder (LRN)
void postorder(Node *root) {

    if (!root)
        return;

    postorder(root->left);
    postorder(root->right);

    printWorker(root->data, 0);
}

// поиск
Node* searchNode(Node *root, const char *key) {

    if (!root)
        return NULL;

    int cmp = strcmp(key, root->data.fio);

    if (cmp == 0)
        return root;

    if (cmp < 0)
        return searchNode(root->left, key);

    return searchNode(root->right, key);
}

// минимум
Node* findMin(Node *root) {

    while (root && root->left)
        root = root->left;

    return root;
}

// максимум
Node* findMax(Node *root) {

    while (root && root->right)
        root = root->right;

    return root;
}

// высота дерева
int treeHeight(Node *root) {

    if (!root)
        return 0;

    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);

    if (leftHeight > rightHeight)
        return leftHeight + 1;

    return rightHeight + 1;
}

// удаление узла
Node* deleteNode(Node *root, const char *key) {

    if (!root)
        return NULL;

    int cmp = strcmp(key, root->data.fio);

    if (cmp < 0) {
        root->left = deleteNode(root->left, key);
    }

    else if (cmp > 0) {
        root->right = deleteNode(root->right, key);
    }

    else {

        // нет детей
        if (!root->left && !root->right) {
            free(root);
            return NULL;
        }

        // один ребёнок справа
        if (!root->left) {
            Node *temp = root->right;
            free(root);
            return temp;
        }

        // один ребёнок слева
        if (!root->right) {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        // два ребёнка
        Node *temp = findMin(root->right);

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data.fio);
    }

    return root;
}

// сохранение дерева
void saveTreeToFile(Node *root, FILE *f) {

    if (!root)
        return;

    fprintf(f, "%s;%s;%.2f;%d\n",
        root->data.fio,
        root->data.position,
        root->data.salary,
        root->data.shipped_goods);

    saveTreeToFile(root->left, f);
    saveTreeToFile(root->right, f);
}

// удаление всего дерева
void deleteWholeTree(Node *root) {

    if (!root)
        return;

    deleteWholeTree(root->left);
    deleteWholeTree(root->right);

    free(root);
}