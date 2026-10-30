#include <stdio.h>
#include <stdlib.h>

#define MAX 10005

int parent[MAX], sz[MAX];
int land[MAX];

int R, C, islands = 0;

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

void unite(int a, int b)
{
    int ra = find(a);
    int rb = find(b);

    if (ra == rb)
        return;

    if (sz[ra] < sz[rb])
    {
        parent[ra] = rb;
        sz[rb] += sz[ra];
    }
    else
    {
        parent[rb] = ra;
        sz[ra] += sz[rb];
    }

    islands--;
}

void addLand(int r, int c)
{
    if (r < 0 || r >= R || c < 0 || c >= C)
        return;

    int id = r * C + c;

    if (land[id])
        return;

    land[id] = 1;
    parent[id] = id;
    sz[id] = 1;

    islands++;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr >= 0 && nr < R &&
            nc >= 0 && nc < C)
        {
            int nid = nr * C + nc;

            if (land[nid])
                unite(id, nid);
        }
    }
}

int main()
{
    int q, r, c;

    printf("Enter rows and columns: ");
    scanf("%d %d", &R, &C);

    for (int i = 0; i < R * C; i++)
        land[i] = 0;

    printf("Enter number of operations: ");
    scanf("%d", &q);

    printf("Enter coordinates:\n");

    for (int i = 0; i < q; i++)
    {
        scanf("%d %d", &r, &c);

        addLand(r, c);

        printf("Number of islands: %d\n", islands);
    }

    return 0;
}