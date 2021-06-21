#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXEXPR 256
#define NUMSYM 6

char expr[MAXEXPR];  // string to store the input expression.
int pos;             // current position of parsing, from end to start

typedef enum {ID_A, ID_B, ID_C, ID_D, OP_AND, OP_OR} TokenSet;
char sym[NUMSYM];

typedef struct _Node {
    TokenSet data;
    struct _Node *left, *right;
} BTNode;

BTNode* EXPR();
BTNode* FACTOR();
BTNode* makeNode(char c);
void freeTree(BTNode *root);
void printPrefix(BTNode *root);

// EXPR = FACTOR | EXPR OP FACTOR
// FACTOR = ID | (EXPR)

BTNode* EXPR(){
    BTNode* right = FACTOR();

    if(((pos >= 0) && expr[pos] == '&') || ((pos >= 0) && expr[pos] == '|')) {
        BTNode* root = makeNode(expr[pos--]);
        root->right = right;
        root->left = EXPR();
        return root;
    }
    else return right;
}

BTNode* FACTOR(){
    if(expr[pos] >= 'A' && expr[pos] <= 'D'){
        BTNode* root = makeNode(expr[pos--]);
        return root;
    }
    else{
        pos--; // )
        BTNode* root = EXPR(); // EXPR
        pos--; // (
        return root;
    }
}

BTNode* makeNode(char c){
    BTNode* root = (BTNode*)malloc(sizeof(BTNode));

    if(c == 'A')    root->data = ID_A;
    if(c == 'B')    root->data = ID_B;
    if(c == 'C')    root->data = ID_C;
    if(c == 'D')    root->data = ID_D;
    if(c == '&')    root->data = OP_AND;
    if(c == '|')     root->data = OP_OR;

    root->left = NULL;
    root->right = NULL;

    return root;
}

int main(void){
    sym[0]='A';
    sym[1]='B';
    sym[2]='C';
    sym[3]='D';
    sym[4]='&';
    sym[5]='|';
    while (scanf("%s", expr)!=EOF)
    {
        pos = strlen(expr) - 1;
        BTNode *root = EXPR();
        printPrefix(root);
        printf("\n");
        freeTree(root);
    }

    return 0;
}

/* print a tree by pre-order. */
void printPrefix(BTNode *root){
    if (root != NULL) {
        printf("%c",sym[root->data]);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

/* clean a tree.*/
void freeTree(BTNode *root){
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

