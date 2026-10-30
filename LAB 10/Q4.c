#include <stdio.h>
#include <stdlib.h>

#define MAX 1005

int parent[MAX], sz[MAX];
int active[MAX];

long long weight[MAX], sum[MAX];
long long ans[MAX];

int adj[MAX][MAX];
int degree[MAX];

long long maximum = 0;

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

void unite(int u, int v)
{
    int ru = find(u);
    int rv = find(v);

    if (ru == rv)
        return;

    if (sz[ru] < sz[rv])
    {
        parent[ru] = rv;
        sz[rv] += sz[ru];
        sum[rv] += sum[ru];
    }
    else
    {
        parent[rv] = ru;
        sz[ru] += sz[rv];
        sum[ru] += sum[rv];
    }

    if (sum[ru] > maximum)
        maximum = sum[ru];

    if (sum[rv] > maximum)
        maximum = sum[rv];
}

void activate(int u)
{
    active[u] = 1;

    parent[u] = u;
    sz[u] = 1;
    sum[u] = weight[u];

    if (sum[u] > maximum)
        maximum = sum[u];

    for (int i = 0; i < degree[u]; i++)
    {
        int v = adj[u][i];

        if (active[v])
            unite(u, v);
    }
}

int main()
{
    int n, m, v;
    int a, b;

    printf("Enter vertices and edges: ");
    scanf("%d %d", &n, &m);

    printf("Enter vertex weights:\n");

    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &weight[i]);
        active[i] = 1;
        parent[i] = i;
        sz[i] = 1;
        sum[i] = weight[i];
    }

    printf("Enter edges:\n");

    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &a, &b);

        adj[a][degree[a]++] = b;
        adj[b][degree[b]++] = a;
    }

    printf("Enter number of deletions: ");
    scanf("%d", &v);

    int p[MAX];

    printf("Enter deletion order:\n");

    for (int i = 1; i <= v; i++)
    {
        scanf("%d", &p[i]);
        active[p[i]] = 0;
    }

    maximum = 0;

    // Construct final graph

    for (int i = 1; i <= n; i++)
    {
        if (active[i])
        {
            parent[i] = i;
            sz[i] = 1;
            sum[i] = weight[i];

            if (sum[i] > maximum)
                maximum = sum[i];
        }
    }

    for (int u = 1; u <= n; u++)
    {
        if (active[u])
        {
            for (int j = 0; j < degree[u]; j++)
            {
                int w = adj[u][j];

                if (active[w])
                    unite(u, w);
            }
        }
    }

    // Reverse the deletion process

    for (int i = v; i >= 1; i--)
    {
        ans[i] = maximum;

        activate(p[i]);
    }

    printf("Maximum component weight after each deletion:\n");

    for (int i = 1; i <= v; i++)
    {
        printf("%lld\n", ans[i]);
    }

    return 0;
}