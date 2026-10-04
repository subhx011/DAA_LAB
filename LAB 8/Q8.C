#include <stdio.h>

#define MAX 50
#define INF 999999.0

void printTree(int root[MAX][MAX], int i, int j) {

    if (i > j)
        return;

    int r = root[i][j];

    printf("Key %d is root of range [%d,%d]\n",
           r, i, j);

    printTree(root, i, r - 1);
    printTree(root, r + 1, j);
}

int main() {

    int n;

    double p[MAX], q[MAX];
    double e[MAX][MAX];
    double w[MAX][MAX];
    int root[MAX][MAX];

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("Enter successful probabilities p1 to p%d:\n", n);

    for (int i = 1; i <= n; i++)
        scanf("%lf", &p[i]);

    printf("Enter unsuccessful probabilities q0 to q%d:\n", n);

    for (int i = 0; i <= n; i++)
        scanf("%lf", &q[i]);

    // Empty subtrees
    for (int i = 1; i <= n + 1; i++) {

        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    // Length of subtree
    for (int length = 1; length <= n; length++) {

        for (int i = 1; i <= n - length + 1; i++) {

            int j = i + length - 1;

            e[i][j] = INF;

            w[i][j] = w[i][j - 1]
                    + p[j]
                    + q[j];

            for (int r = i; r <= j; r++) {

                double cost =
                    e[i][r - 1]
                    + e[r + 1][j]
                    + w[i][j];

                if (cost < e[i][j]) {

                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum expected search cost = %.4lf\n",
           e[1][n]);

    printf("\nRoot structure:\n");

    printTree(root, 1, n);

    return 0;
}