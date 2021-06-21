#include <stdio.h>
#include <stdlib.h>

struct Node {
    int id;
    struct Node *next;
};

struct Graph {
    int vertices_num;
    struct Node **adjLists;
};

struct Graph* createGraph(int n){
    struct Graph *g = (struct Graph*)malloc(sizeof(struct Graph));
    g->vertices_num = n;
    g->adjLists = (struct Node**)malloc(n*sizeof(struct Node*));

    for(int i = 0; i < n; i++)
        g->adjLists[i] = NULL;

    return g;
}

struct Node* makeNode(int n){
    //printf("make node");
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->id = n;
    node->next = NULL;

    return node;
}

struct Node* insertNode(struct Node* head, int n){
    //printf("insert node\n");
    //fflush(stdout);
    struct Node* newHead = makeNode(n);
    newHead->next = head;

    return newHead;
}

void addEdge(struct Graph* g, int a, int b){
    //printf("add edge a\n");
    g->adjLists[a] = insertNode(g->adjLists[a], b);
    //printf("add edge b\n");
    g->adjLists[b] = insertNode(g->adjLists[b], a);
}

int findMax(struct Graph* g, int now, int prev){
    int ans = now;
    struct Node* tmp = g->adjLists[now];

    for(tmp; tmp; tmp = tmp->next){
        if(tmp->id == prev)    continue;
        else{
            if(tmp->id > ans)   ans = tmp->id;
            int newAns = findMax(g, tmp->id, now);
            if(newAns > ans)    ans = newAns;
        }
    }

    return ans;
}

void freeGraph(struct Graph* g){
    for(int i = 0; i < g->vertices_num; i++){
        struct Node* tmp = g->adjLists[i];
        while(tmp != NULL){
            struct Node* next = tmp->next;
            free(tmp);
            tmp = next;
        }
    }
}

int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		struct Graph *g = createGraph(n);
		for (int i = 0; i < n - 1; i++) {
			int u, v; scanf("%d %d", &u, &v);
			addEdge(g, u, v);
		}
		int q; scanf("%d", &q);
		while (q--) {
			int a, b; scanf("%d %d", &a, &b);
			printf("%d %d\n", findMax(g, a, b), findMax(g, b, a));
		}
		freeGraph(g);
	}
	return 0;
}
