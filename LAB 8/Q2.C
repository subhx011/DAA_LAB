#include <stdio.h>

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

    long long dp[V + 1];

    for (int i = 0; i <= V; i++)
        dp[i] = 0;

    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = coins[i]; j <= V; j++) {
            dp[j] = dp[j] + dp[j - coins[i]];
        }
    }

    printf("Total number of ways = %lld\n", dp[V]);

    return 0;
}