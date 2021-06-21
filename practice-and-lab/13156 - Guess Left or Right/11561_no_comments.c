#include <stdio.h>
#include <stdlib.h>

#define MAXN 200002

int lch[MAXN], rch[MAXN]; // left child, right child
int node_index[MAXN];     // node_index[i] means node[i]'s index in the inorder sequence
int point_to[MAXN];       // point_to[i] means the # of node point to node[i]
int inorder[MAXN];        // correct inorder sequence that we gave
int ans[MAXN];            // the inorder sequence of our final tree structure
int root, idx;

void traverse(int node) {
    if(node) {
        traverse(lch[node]);
        ans[idx++] = node;
        traverse(rch[node]);
    }
}

int main() {
    int N;

    while(scanf("%d", &N) != EOF) {
        for(int i=1; i<=N; i++) {
            scanf("%d %d", &lch[i], &rch[i]);
            point_to[lch[i]] += 1; point_to[rch[i]] += 1;
        }

        //////////
        /*printf("point to:");
        for(int i = 1; i <= N; i++)
            printf("%d ", point_to[i]);
            printf("\n");*/
        //////////

        for(int i=1; i<=N; i++) {
            scanf("%d", &inorder[i]);
            node_index[inorder[i]] = i;
        }

        for(int i=1; i<=N; i++) {
            if(!point_to[i]) {
                root = i;
                break;
            }
        }

        for(int i=1; i<=N; i++) {
            int tmp;
            if(lch[i] != 0 && node_index[lch[i]] > node_index[i]) {
                tmp = lch[i];
                lch[i] = rch[i];
                rch[i] = tmp;
            }
            if(rch[i] != 0 && node_index[rch[i]] < node_index[i]) {
                tmp = rch[i];
                rch[i] = lch[i];
                lch[i] = tmp;
            }
        }

        idx = 1;
        traverse(root);

        for(idx=1; idx<=N; idx++) {
            if(ans[idx] != inorder[idx]){
                printf("NO\n");
                break;
            }
        }
        if(idx == N + 1) printf("YES\n");

        for(int i=1; i<=N; i++) {
            point_to[i] = 0;
        }
    }
    return 0;
}
