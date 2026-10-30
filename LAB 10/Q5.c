#include <stdio.h>
#include <stdlib.h>

#define MAX 1005

int parent[MAX], sz[MAX];

typedef struct
{
    int root;
    int index;
    int value;
} Node;

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
    }
    else
    {
        parent[rv] = ru;
        sz[ru] += sz[rv];
    }
}

int compareIndex(const void *a, const void *b)
{
    Node *x = (Node *)a;
    Node *y = (Node *)b;

    if (x->root != y->root)
        return x->root - y->root;

    return x->index - y->index;
}

int compareValue(const void *a, const void *b)
{
    Node *x = (Node *)a;
    Node *y = (Node *)b;

    if (x->root != y->root)
        return x->root - y->root;

    return x->value - y->value;
}

int main()
{
    int n, m;

    printf("Enter number of elements and edges: ");
    scanf("%d %d", &n, &m);

    int arr[MAX], result[MAX];

    Node byIndex[MAX], byValue[MAX];

    printf("Enter permutation:\n");

    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);

        parent[i] = i;
        sz[i] = 1;
    }

    printf("Enter allowed swaps:\n");

    for (int i = 0; i < m; i++)
    {
        int u, v;

        scanf("%d %d", &u, &v);

        unite(u, v);
    }

    for (int i = 1; i <= n; i++)
    {
        int r = find(i);

        byIndex[i - 1].root = r;
        byIndex[i - 1].index = i;

        byValue[i - 1].root = r;
        byValue[i - 1].value = arr[i];
    }

    qsort(byIndex, n, sizeof(Node), compareIndex);

    qsort(byValue, n, sizeof(Node), compareValue);

    for (int i = 0; i < n; i++)
    {
        result[byIndex[i].index] = byValue[i].value;
    }

    printf("Lexicographically smallest permutation:\n");

    for (int i = 1; i <= n; i++)
    {
        printf("%d ", result[i]);
    }

    printf("\n");

    return 0;
}