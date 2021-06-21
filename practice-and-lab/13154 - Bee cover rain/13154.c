#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define f 1
#define ID 0

typedef struct _node{
    int data;
    int flag;
    struct _node *left;
    struct _node *right;
} Node;

int p, q, start;
char input[5000001];

Node* makeNode(int c, int flag){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = c;
    node->flag = flag;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// f : ID | f(f,f)
Node* parse(){
    Node* root;
    if(input[start] == 'f'){
        root = makeNode(input[start], f);
        start += 2;
        root->left = parse();
        start++; // ,
        root->right = parse();
        start++;// )
    }
    else{
        int tmp = 0;
        while(input[start] >= '0' && input[start] <= '9'){
            tmp = tmp * 10 + (input[start++] - '0');
        }
        //printf("current number : %d\n", tmp);
        root = makeNode(tmp, ID);
    }

    return root;
}

long long solve(Node* root){
    if(root == NULL)    return 0;

    if(root->flag == ID)    return root->data;
    else{
        return (p * solve(root->left) + solve(root->right)) % q;
    }
}

void printPrefix(Node* root){
    Node* tmp = root;

    if(tmp != NULL){
        printf("%d ", tmp->data);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

int main(){
    start = 0;
    scanf("%d %d ", &p, &q);
    scanf("%s", input);

    Node* root = parse();

    int ans = solve(root);
    printf("%d\n", ans);

    //printPrefix(root);
    //printf("\n");

    return 0;
}
