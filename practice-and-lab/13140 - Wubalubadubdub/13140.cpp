#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 200000

typedef struct _node{
    int data;
    struct _node* left;
    struct _node* right;
} Node;

Node* makeNode(int i){
    Node* root = (Node*)malloc(sizeof(Node));
    root->data = i;
    root->left = NULL;
    root->right = NULL;

    return root;
}

Node* buildTree(int* input, int begin, int end){
    if((end - begin) <= 0)
        return NULL;

    int newBegin;
    Node *root = makeNode(input[end - 1]);

    if((end - begin) == 1)
        return root;
    newBegin = (begin + end) / 2;
    if(input[newBegin] > root->data){
        for(; newBegin >= begin; newBegin--)
            if(input[newBegin] < root->data)    break;
        newBegin++;
    }
    else{
        for(; newBegin < end - 1; newBegin++)
            if(input[newBegin] > root->data)    break;
    }

    /*for(newBegin = begin; newBegin < end - 1; newBegin++)
        if(input[newBegin] > root->data)    break;*/


    /*for(newBegin = end - 1; newBegin >= begin; newBegin--)
        if(input[newBegin] < root->data)    break;

    newBegin++;*/

    root->right = buildTree(input, newBegin, end - 1);
    root->left = buildTree(input, begin, newBegin);

    return root;
}

void printPreorder(Node* root, int i){
    Node* tmp = root;
    if(tmp != NULL){
        if(i == 0)
            printf("%d", root->data);
        else
            printf(" %d", root->data);
        printPreorder(root->left, 1);
        printPreorder(root->right, 1);
    }
}

int main(){
    int input[MAXNUM];
    int n, counter = 0;
    /*while(scanf("%d ", &n) != EOF){
        input[counter++] = n;
    }*/

    for(int i = 0; i < 9; i++){
        scanf("%d", &input[counter++]);
    }
    //printf("666\n");
    //fflush(stdout);
    Node* root = buildTree(input, 0, counter);

    printPreorder(root, 0);
    printf("\n");

    return 0;
}
