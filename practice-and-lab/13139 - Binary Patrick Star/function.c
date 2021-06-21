#include <stdio.h>
#include <stdlib.h>
#include "function.h"

Node* makeNode(int n){
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->id = n;
    tmp->left = NULL;
    tmp->right = NULL;

    return tmp;
}

Node* buildBinaryTree(int rootNumber, int* leftChild, int* rightChild){
    Node* nodeArray[rootNumber];

    for(int i = 0; i < rootNumber; i++){
        nodeArray[i] = makeNode(i);
    }

    for(int i = 0; i < rootNumber; i++){
        if(leftChild[i] > 0){
            nodeArray[i]->left = nodeArray[leftChild[i]];
        }
        if(rightChild[i] > 0){
            nodeArray[i]->right = nodeArray[rightChild[i]];
        }
    }

    return nodeArray[0];
}

void Traversal(Node* root, int* ans){
    Node* tmp = root;

    if(tmp != NULL){
        Traversal(tmp->left, ans);
        Traversal(tmp->right, ans);
        ans[tmp->id] = 1;
        if(tmp->left != NULL)
            ans[tmp->id] += ans[tmp->left->id];
        if(tmp->right != NULL)
            ans[tmp->id] += ans[tmp->right->id];
    }
    else    return;

}

void freeBinaryTree(Node* root){
    Node* tmp = root;

    if(tmp != NULL){
        freeBinaryTree(tmp->left);
        freeBinaryTree(tmp->right);
        free(tmp);
    }
}
