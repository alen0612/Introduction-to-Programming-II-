struct Node {
    int id;
    struct Node *next;
};

struct Graph {
    int vertices_num;
    struct Node **adjLists;
};

struct Graph* createGraph(int);
void addEdge(struct Graph*, int, int);
int findMax(struct Graph*, int, int);
void freeGraph(struct Graph*);
