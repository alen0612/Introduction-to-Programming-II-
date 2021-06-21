#include <stdio.h>
#include <stdlib.h>

#define f 1
#define ID 0

typedef struct _node{
    int data;
    int flag;
    struct _node* left;
    struct _node* right;
} Node;

int p, q, n, pos;
char input[1000001];

Node* makeNode(int c, int flag){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = c;
    node->flag = flag;
    node->left = node->right = NULL;

    return node;
}

Node* parse(){
    Node* root;

    if(input[pos] == 'f'){
        root = makeNode(input[pos], f);
        pos += 2;
        root->left = parse();
        pos++;
        root->right = parse();
        pos++;
    }
    else{
        int tmp = 0;
        while(input[pos] >= '0' && input[pos] <= '9')
            tmp = tmp * 10 + input[pos++] - '0';
        root = makeNode(tmp, ID);
    }

    return root;
}

long long solve(Node* root, int* arr){
    if(root == NULL)    return 0;
    if(root->flag == ID)    return arr[root->data];
    else    return (p * solve(root->left, arr) + solve(root->right, arr)) % q;
}

void printPrefix(Node* root){
    if(root != NULL){
        printf("%d ", root->data);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

int main() {
    scanf("%d %d", &p, &q);
    scanf("%d", &n);

    int arr[n+1];
    for(int i = 1; i <= n; i++)
        scanf("%d ", &arr[i]);

    scanf("%s", input);

    pos = 0;
    Node* root = parse();

    int time = 0;
    int index, value = 0;
    scanf("%d", &time);

    for(int i = 0; i < time; i++){
        scanf("%d %d", &index, &value);
        arr[index] = value;
        int ans = solve(root, arr);
        printf("%d\n", ans);
    }

    return 0;
}
