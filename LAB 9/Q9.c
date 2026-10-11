
#include <stdio.h>

int main(void) {
    int n, i, j;
    int freq[100];
    int dp[100][100];
    int sum[100][100];

    printf("Enter number of symbols: ");
    scanf("%d", &n);

    if (n < 1 || n > 100) {
        printf("Invalid number of symbols\n");
        return 1;
    }

    printf("Enter frequencies in alphabetical order:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &freq[i]);

        if (freq[i] < 0) {
            printf("Frequency cannot be negative\n");
            return 1;
        }
    }

    for (i = 0; i < n; i++) {
        sum[i][i] = freq[i];
        dp[i][i] = 0;
    }

    for (i = 0; i < n - 1; i++) {
        sum[i][i + 1] = freq[i] + freq[i + 1];
        dp[i][i + 1] = sum[i][i + 1];
    }

    for (int len = 3; len <= n; len++) {
        for (i = 0; i <= n - len; i++) {
            j = i + len - 1;

            sum[i][j] = sum[i][j - 1] + freq[j];
            dp[i][j] = 2147483647;

            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j]
                           + sum[i][j];

                if (cost < dp[i][j])
                    dp[i][j] = cost;
            }
        }
    }

    printf("Minimum weighted path cost = %d\n", dp[0][n - 1]);

    return 0;
}
