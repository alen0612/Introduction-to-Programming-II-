#include <stdlib.h>
typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} Node;

void constructTree(Node** head);

void printInfix(Node *root);

void freeTree(Node *root);

char s1[100] , s2[100] ;

int idx ;
