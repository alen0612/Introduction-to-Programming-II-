#include <stdio.h>
#include <stdlib.h>

/*
1. Define the tree node structure.
typedef struct Node
{
    int idx;
    struct Node *p, *l, *r; //for the parent, left child and right child
} BTNode;

2. "malloc" an array of BTNode's to build the required tree structure.

3. Find the root of the tree (i.e., the node with a NULL p pointer).

4. Enhance the in-order traversal to check all possible given traversal sequences.

Note that, to pass all the test cases, you may need a more efficient approach.
*/

//Step 1. Define the tree node structure.
typedef struct Node
{
    int idx;
    struct Node *p, *l, *r;
} BTNode;

BTNode *root;
int *inorder;

int pos;

int in_traversal_two_way(BTNode* root)
{
    if(root!=NULL)
    {
        if(in_traversal_two_way(root->l))
        {
            if(root->idx==inorder[pos])
            {
                pos++;
                if(in_traversal_two_way(root->r))
                {
                    return 1;
                }
                return 0;
            }
        }

        if(in_traversal_two_way(root->r))
        {
            if(root->idx==inorder[pos])
            {
                pos++;
                if(in_traversal_two_way(root->l))
                {
                    return 1;
                }
                return 0;
            }
        }

        return 0;
    }

    return 1;
}

int main(void)
{
    int N;
    int i,l,r;
    while(scanf("%d",&N)!=EOF)
    {
        pos = 0;

        inorder = (int *) malloc(N*sizeof(int));

        //Step 2. "malloc" an array of BTNode's to build the required tree structure.
        BTNode *nodeSet = (BTNode *) malloc((N+1)*sizeof(BTNode));

        for(i=1;i<=N;i++)
        {
            nodeSet[i].p = nodeSet[i].l = nodeSet[i].r = NULL;
            nodeSet[i].idx = i;
        }

        for(i=1;i<=N;i++)
        {
            scanf("%d%d",&l,&r);

            if(l!=0)
            {
                nodeSet[l].p = &(nodeSet[i]);
                nodeSet[i].l = &(nodeSet[l]);
            }

            if(r!=0)
            {
                nodeSet[r].p = &(nodeSet[i]);
                nodeSet[i].r = &(nodeSet[r]);
            }
        }
        //end of Step 2

        //Step 3. Find the root of the tree (i.e., the node with a NULL p pointer).
        for(i=1;i<=N;i++)
        {
            if(nodeSet[i].p == NULL)
            {
                root=&(nodeSet[i]);
                break;
            }
        }

        for(i=0;i<N;i++)
        {
            scanf("%d",&(inorder[i]));
        }

        //Step 4. In-order traversal to check all possible given traversal sequences.
        if(in_traversal_two_way(root)) printf("YES\n");
        else printf("NO\n");

        free(inorder);
        free(nodeSet);
    }
    return 0;
}
