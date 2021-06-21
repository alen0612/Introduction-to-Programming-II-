#include <stdio.h>

#define min(a, b) (a<b?a:b)

int illegal = -1;

typedef struct _node{
    int data;
    struct _node *left;
    struct _node *right;
} Node;

Node* makeNode(int n){
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = n;
    head->left = NULL;
    head->right = NULL;

    return head;
}

void check(Node* root, int down, int up, int flag){
    if(root == NULL)    return;

    if(flag == 1){
        root->data = illegal;
        check(root->left, down, up, 1);
        check(root->right, down, up, 1);
    }
    else{
        if(root->data > down && root->data < up){
            check(root->left, down, root->data, 0);
            check(root->right, root->data, up, 0);
        }
        else{
            root->data = illegal;
            check(root->left, down, root->data, 1);
            check(root->right, root->data, up, 1);
        }
    }
}

int updateHeight(Node* root){
    if(root == NULL)    return 0;

    updateHeight(root->left);
    updateHeight(root->right);

    if(root->data < 0){
        if(root->left == NULL && root->right == NULL){
            return -1;
        }
        else if(root->left != NULL && root->right != NULL){
            root->data = min(root->left->data, root->right->data) - 1;
        }
        else if(root->left != NULL && root->right == NULL){
            root->data = root->left->data - 1;
        }
        else{
            root->data = root->right->data - 1;
        }
    }
}

void printValue(Node* node_array[], int n){
    for(int i = 1; i < n; i++){
        printf("%d ", node_array[i]->data);
    }
    printf("%d\n", node_array[n]->data);
}

int main(){
    int n = 0;
    int root_index = 0;
    scanf("%d", &n);

    Node* node_array[n+1];
    int value[n+1];
    int parent_array[n+1];
    char child;

    for(int i = 1; i <= n; i++){
        scanf("%d", &value[i]);
        node_array[i] = makeNode(value[i]);
    }

    for(int i = 1; i <=n; i++){
        scanf("%d", &parent_array[i]);
        if(parent_array[i] == 0){ // root
            root_index = i;
            continue;
        }
        else{
            scanf("%c", &child);
            if(child == 'L'){
                node_array[parent_array[i]]->left = node_array[i];
            }
            else{
                node_array[parent_array[i]]->right = node_array[i];
            }
        }
    }

    check(node_array[root_index], 0, 1000000000, 0);
    updateHeight(node_array[root_index]);

    printValue(node_array, n);

    return 0;
}
