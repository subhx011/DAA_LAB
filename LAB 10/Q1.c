#include <stdio.h>
#include <stdlib.h>

#define MAX 1005

int parent[MAX], sz[MAX], parity[MAX];

int find(int x)
{
    if (parent[x] != x)
    {
        int p = parent[x];

        parent[x] = find(parent[x]);
        parity[x] ^= parity[p];
    }

    return parent[x];
}

int addEdge(int u, int v)
{
    int ru = find(u);
    int rv = find(v);

    int pu = parity[u];
    int pv = parity[v];

    if (ru == rv)
    {
        return (pu ^ pv) == 1;
    }

    if (sz[ru] < sz[rv])
    {
        parent[ru] = rv;
        parity[ru] = pu ^ pv ^ 1;
        sz[rv] += sz[ru];
    }
    else
    {
        parent[rv] = ru;
        parity[rv] = pu ^ pv ^ 1;
        sz[ru] += sz[rv];
    }

    return 1;
}

int main()
{
    int n, m, u, v;

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
        sz[i] = 1;
        parity[i] = 0;
    }

    printf("Enter edges:\n");

    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);

        if (addEdge(u, v))
        {
            printf("Edge (%d,%d) ACCEPTED. Graph is bipartite.\n", u, v);
        }
        else
        {
            printf("Edge (%d,%d) REJECTED. Graph is not bipartite.\n", u, v);
        }
    }

    return 0;
}