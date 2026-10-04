#include <stdio.h>

long long dp[100];
int split[100];

long long min(long long a, long long b) {
    return (a < b) ? a : b;
}

long long power2(int n) {
    if (n == 0)
        return 1;

    return 2 * power2(n - 1);
}

void hanoi3(int n, char source, char destination, char auxiliary) {

    if (n == 0)
        return;

    hanoi3(n - 1, source, auxiliary, destination);

    printf("Move disk %d from %c to %c\n",
           n, source, destination);

    hanoi3(n - 1, auxiliary, destination, source);
}

void reve(int n, char source, char destination,
          char aux1, char aux2) {

    int k;

    if (n == 0)
        return;

    if (n == 1) {
        printf("Move disk 1 from %c to %c\n",
               source, destination);
        return;
    }

    k = split[n];

    // Move k disks using 4 pegs
    reve(k, source, aux1, destination, aux2);

    // Move remaining n-k disks using 3 pegs
    hanoi3(n - k, source, destination, aux2);

    // Move k disks to destination
    reve(k, aux1, destination, source, aux2);
}

int main() {

    int n = 8;
    int i, k;

    dp[0] = 0;
    dp[1] = 1;

    for (i = 2; i <= n; i++) {

        dp[i] = 999999999;

        for (k = 1; k < i; k++) {

            long long moves =
                2 * dp[k] +
                (power2(i - k) - 1);

            if (moves < dp[i]) {
                dp[i] = moves;
                split[i] = k;
            }
        }
    }

    printf("Minimum moves for %d disks = %lld\n",
           n, dp[n]);

    printf("\nSequence of moves:\n");

    reve(n, 'A', 'D', 'B', 'C');

    return 0;
}