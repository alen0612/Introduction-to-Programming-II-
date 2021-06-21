#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int data;
	struct _node *left;
	struct _node *right;
}Node;

Node* constructTree(int map[], int preorder[], int start, int end);
Node* createRoot(int num);
//int findInorder(int inorder[], int start, int end, int target);
void printPostorder(Node *root);

Node* constructTree(int map[], int preorder[], int start, int end){
	static int preorderIndex = 0;

	if(start > end)
		return NULL;

	Node *root = createRoot(preorder[preorderIndex++]);

	if(start == end)
		return root;

	//int inorderIndex = findInorder(inorder, start, end, root->data);

	root->left = constructTree(map, preorder, start, map[root->data]);
	root->right = constructTree(map, preorder, map[root->data], end);

	return root;
}

/*int findInorder(int inorder[], int start, int end, int target){
	for(int i = start; i < end; i++){
		if(inorder[i] == target)
			return i;
	}
}*/

Node* createRoot(int num){
	Node* root = (Node*)malloc(sizeof(Node));

	root->data = num;
	root->left = NULL;
	root->right = NULL;

	return root;
}

void printPostorder(Node *root){
    if (root == NULL)
        return;

    printPostorder(root->left);
    printPostorder(root->right);
    printf("%d ", root->data);
}



int main(){
	int N = 0;

	scanf("%d", &N);
	int inorder[N];
	int preorder[N];
	int map[N];
	int len = sizeof(inorder) / sizeof(inorder[0]);
	for(int i = 0; i < N; i++){
		scanf("%d", &inorder[i]);
		map[inorder[i]] = i;
	}
	for(int j = 0; j < N; j++){
		scanf("%d", &preorder[j]);
	}

	Node *root = constructTree(map, preorder, 0, len-1);
	printPostorder(root);

	return 0;
}

/*
7
2 3 4 5 7 6 9
5 3 2 4 6 7 9
*/
