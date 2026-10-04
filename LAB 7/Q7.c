#include <stdio.h>
#include <limits.h>

#define MAX 20

int dp[MAX][MAX];
int split[MAX][MAX];

void printOrder(int i, int j) {

    if (i == j) {
        printf("A%d", i);
        return;
    }

    printf("(");

    printOrder(i, split[i][j]);

    printOrder(split[i][j] + 1, j);

    printf(")");
}

int main() {

    int n, i, j, k, length;

    int p[MAX];

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    printf("Enter %d dimensions:\n", n + 1);

    for (i = 0; i <= n; i++)
        scanf("%d", &p[i]);

    /*
       dp[i][j] = minimum multiplications
       needed to multiply Ai...Aj
    */

    for (i = 1; i <= n; i++)
        dp[i][i] = 0;

    for (length = 2; length <= n; length++) {

        for (i = 1; i <= n - length + 1; i++) {

            j = i + length - 1;

            dp[i][j] = INT_MAX;

            for (k = i; k < j; k++) {

                int cost =
                    dp[i][k] +
                    dp[k + 1][j] +
                    p[i - 1] * p[k] * p[j];

                if (cost < dp[i][j]) {

                    dp[i][j] = cost;

                    split[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum number of scalar multiplications = %d\n",
           dp[1][n]);

    printf("Optimal parenthesization = ");

    printOrder(1, n);

    printf("\n");

    return 0;
}