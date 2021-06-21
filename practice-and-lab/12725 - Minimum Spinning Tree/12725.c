#include <stdio.h>
#include <stdlib.h>

int ans;

typedef struct _node{
    char data;
    int val;
    struct _node* left;
    struct _node* right;
} Node;

Node* makeNode(char c){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = c;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// prefix : OP <prefix> <prefix> | ID

Node* buildTree(){
    char c;
    c = getchar();

    Node* root  = makeNode(c);

    if(c >= '1' && c <= '9'){
        return root;
    }
    else{
        root->left = buildTree();
        root->right = buildTree();
    }

    return root;
}

int getValue(Node* root){
    if(root == NULL)    return 0;

    if(root->data >= '1' && root->data <= '9'){
        root->val =  root->data - '0';
    }
    else if(root->data == '+')  root->val = getValue(root->left) + getValue(root->right);
    else if(root->data == '-')  root->val = getValue(root->left) - getValue(root->right);
    else    root->val = getValue(root->left) * getValue(root->right);

    return root->val;
}

Node* copyTree(Node* root){
    if(root == NULL)    return NULL;

    Node* newRoot = (Node*)malloc(sizeof(Node));
    newRoot->data = root->data;
    newRoot->val = root->val;
    newRoot->left = copyTree(root->left);
    newRoot->right = copyTree(root->right);

    return newRoot;
}

void updateNode(Node* root){
    if(root->data == '+')   root->val = root->left->val + root->right->val;
    else if(root->data == '-') root->val = root->left->val - root->right->val;
    else root->val = root->left->val * root->right->val;
}

void leftSpin(Node* root){
    if(root->right == NULL) return;
    while(root->right->data == '+' || root->right->data == '-' || root->right->data == '*'){
        // left spin
        Node* newRoot = root->right;
        root->right = newRoot->left;
        newRoot->left = root;
        root = newRoot;

        updateNode(root->left);
        updateNode(root);

        // get value
        int newAns = root->val;
        if(newAns < ans)    ans = newAns;
    }
}

void rightSpin(Node* root){
    if(root->left == NULL)  return;
    while(root->left->data == '+' || root->left->data == '-' || root->left->data == '*'){
        // right spin
        Node* newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;
        root = newRoot;

        updateNode(root->right);
        updateNode(root);

        // get value
        int newAns = root->val;
        if(newAns < ans)    ans = newAns;
    }
}

int main(){
    int n = 0;
    scanf("%d ", &n);

    Node* root = buildTree();

    ans = getValue(root);

    Node* leftSpinTree = copyTree(root);
    Node* rightSpinTree = copyTree(root);

    leftSpin(leftSpinTree);
    rightSpin(rightSpinTree);

    printf("%d\n", ans);

    return 0;
}
