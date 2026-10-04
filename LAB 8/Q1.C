#include <stdio.h>
#include <limits.h>

int main() {
    int n, V;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter coin denominations:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter target amount: ");
    scanf("%d", &V);

    int dp[V + 1];

    dp[0] = 0;

    for (int i = 1; i <= V; i++)
        dp[i] = INT_MAX;

    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                if (dp[i - coins[j]] + 1 < dp[i])
                    dp[i] = dp[i - coins[j]] + 1;
            }
        }
    }

    if (dp[V] == INT_MAX)
        printf("It is not possible to make the amount.\n");
    else
        printf("Minimum number of coins = %d\n", dp[V]);

    return 0;
}