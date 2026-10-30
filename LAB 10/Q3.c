#include <stdio.h>

#define MAX 1005

int parent[MAX], sz[MAX];
long long weight[MAX];

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
        weight[rv] += weight[ru];
    }
    else
    {
        parent[rv] = ru;
        sz[ru] += sz[rv];
        weight[ru] += weight[rv];
    }
}

int main()
{
    int n, m, K;
    int u, v;

    printf("Enter vertices, edges and K: ");
    scanf("%d %d %d", &n, &m, &K);

    printf("Enter vertex weights:\n");

    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &weight[i]);

        parent[i] = i;
        sz[i] = 1;
    }

    printf("Enter edges:\n");

    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);
        unite(u, v);
    }

    long long ans = -1;
    int found = 0;

    for (int i = 1; i <= n; i++)
    {
        if (find(i) == i)
        {
            if (sz[i] <= K)
            {
                if (!found || weight[i] > ans)
                    ans = weight[i];

                found = 1;
            }
        }
    }

    if (found)
        printf("Maximum component weight = %lld\n", ans);
    else
        printf("No component satisfies the size constraint.\n");

    return 0;
}