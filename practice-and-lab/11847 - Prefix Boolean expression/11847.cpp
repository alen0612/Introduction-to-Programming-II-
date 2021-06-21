#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

// prefix = ID | OP <prefix> <prefix>
// root
// root->left
// root-> right

typedef struct _node{
    char data;
    struct _node* left;
    struct _node* right;
} BTNode;

BTNode* makeNode(char c){
    BTNode* tmp = (BTNode*)malloc(sizeof(BTNode));
    tmp->data = c;
    tmp->left = NULL;
    tmp->right = NULL;

    return tmp;
}

BTNode* build(){
    BTNode* head;

    char c;
    c = getchar();

    head = makeNode(c);
    if(c >= 'A' && c <= 'D'){
        return head;
    }
    else{
        head->left = build();
        head->right = build();
    }

    return head;
}

int solve(BTNode* root, int i){
    BTNode* tmp = root;
    if(tmp->data == '&'){
        return (solve(tmp->left, i) & solve(tmp->right, i));
    }
    else if(tmp->data == '|'){
        return (solve(tmp->left, i) | solve(tmp->right, i));
    }
    else{
        return ((i >> ('D' - tmp->data))  & 1);
    }
}

void printTree(BTNode* root){
    BTNode* tmp = root;

    if(root == NULL)
        return;
    else{
        printf("%c", tmp->data);
        printTree(root->left);
        printTree(root->right);
    }
}

int main(){
    BTNode* root =  build();

    int ans = 0;

    for(int i = 0; i < 16; i++){
        ans = solve(root, i);
        printf("%d %d %d %d ", (i >> 3) & 1, (i >> 2) & 1, (i >> 1) & 1, i & 1);
        printf("%d\n", ans);
    }

    return 0;
}
