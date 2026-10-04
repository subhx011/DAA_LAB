#include <stdio.h>

#define MAX 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int E, F;
    int dp[MAX + 1][MAX + 1];
    int e, f, x;

    printf("Enter number of eggs: ");
    scanf("%d", &E);

    printf("Enter number of floors: ");
    scanf("%d", &F);

    // 0 floors require 0 attempts
    for (e = 1; e <= E; e++)
        dp[e][0] = 0;

    // 1 floor requires 1 attempt
    for (e = 1; e <= E; e++)
        dp[e][1] = 1;

    // With 1 egg, test floors one by one
    for (f = 1; f <= F; f++)
        dp[1][f] = f;

    for (e = 2; e <= E; e++) {
        for (f = 2; f <= F; f++) {

            dp[e][f] = 99999;

            for (x = 1; x <= f; x++) {

                int attempts = 1 +
                    max(dp[e - 1][x - 1],
                        dp[e][f - x]);

                if (attempts < dp[e][f])
                    dp[e][f] = attempts;
            }
        }
    }

    printf("Minimum number of droppings = %d\n", dp[E][F]);

    return 0;
}