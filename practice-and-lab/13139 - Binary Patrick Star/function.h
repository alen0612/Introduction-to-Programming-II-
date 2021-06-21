typedef struct _Node {
	struct _Node *left, *right;
	int id;
} Node;

Node* buildBinaryTree(int, int*, int*);
void Traversal(Node*, int*);
void freeBinaryTree(Node*); 

/*
You can malloc the space for every node in advance.

Node* buildBinaryTree(int n, int* lch, int* rch) {
	Node* node = (Node*) malloc(sizeof(Node) * n);
	...
	...
	...
	return node;
}

void freeBinaryTree(Node* root) {
	free(root);
}
*/
