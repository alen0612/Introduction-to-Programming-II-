#include <stdio.h>
#include <stdlib.h>

#define MAXN 200002


int lch[MAXN], rch[MAXN]; // left child, right child
int node_index[MAXN];     // node_index[i] means node[i]'s index in the inorder sequence
int point_to[MAXN];       // point_to[i] means the # of node point to node[i]
int inorder[MAXN];        // correct inorder sequence that we gave
int ans[MAXN];            // the inorder sequence of our final tree structure
int root, idx;

// inorder
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

        // Assuming that the first node is on the left, and the second node is on the right.
        for(int i=1; i<=N; i++) {
            scanf("%d %d", &lch[i], &rch[i]);
            point_to[lch[i]] += 1; point_to[rch[i]] += 1;
        }

        // Read in inorder sequence and record the index of inorder[i]
        for(int i=1; i<=N; i++) {
            scanf("%d", &inorder[i]);
            node_index[inorder[i]] = i;
        }

        // If no one point to the node, means that the node is root
        for(int i=1; i<=N; i++) {
            if(!point_to[i]) {
                root = i;
                break;
            }
        }

        // KEY: For every node,
        //      comparing the node's index in inorder sequence and the node's left child's index in inorder sequence.
        //      If left child index in the inorder sequence is greater than node's index,
        //      it means that the left child should be the right child, actually.
        //      Similarly, if the right child index in the inorder sequence is less than the node's index,
        //      it means that your right child should be your left child, actually.
        //
        //      ex:     0     Take node 0 for example.
        //             / \    If lch[0]=2 and rch[0]=1, inorder sequence = 102,
        //            1   2   we can see that node_index[lch[0]]=2 is greater than node_index[0]=1.
        //                    Meaning that the node 2 is actually the right child.
        //                    Then we need to exchange lch[0] ans rch[0] to form the correct order.
        //
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

        // Initial the idx everytime,
        // and construct the inorder sequence with the left and right children after reorganizing.
        idx = 1;
        traverse(root);

        // Compare our final result with the input inorder sequence.
        for(idx=1; idx<=N; idx++) {
            if(ans[idx] != inorder[idx]){
                printf("NO\n");
                break;
            }
        }
        if(idx == N + 1) printf("YES\n");

        // initial point_to array
        for(int i=1; i<=N; i++) {
            point_to[i] = 0;
        }
    }
    return 0;
}
