#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Simulate n tosses of a coin with given probability of heads (p_head).
   Returns the number of heads observed. */
long simulate_tosses(long n, double p_head) {
    long heads = 0;
    for (long i = 0; i < n; i++) {
        double r = (double) rand() / ((double) RAND_MAX + 1.0); /* uniform in [0,1) */
        if (r < p_head) {
            heads++;
        }
    }
    return heads;
}

int main(void) {
    srand((unsigned int) time(NULL));

    long n = 10000;   /* number of tosses */

    printf("=========================================\n");
    printf(" PART 1: FAIR COIN (p = 0.5), n = %ld tosses\n", n);
    printf("=========================================\n");
    long heads_only_fair = simulate_tosses(n, 0.5);
    printf("Heads   : %ld\n", heads_only_fair);
    printf("Tails   : %ld\n", n - heads_only_fair);
    printf("P(Heads): %.5f\n\n", (double) heads_only_fair / n);
    printf("This is close to the theoretical value of 0.5, confirming\n");
    printf("the coin is fair (each outcome equally likely).\n\n");

    printf("=========================================\n");
    printf(" PART 2: FAIR vs BIASED COIN COMPARISON\n");
    printf(" (n = %ld tosses each)\n", n);
    printf("=========================================\n");

    double p_fair = 0.5;
    double p_biased = 0.7;      /* example: biased towards heads */

    long heads_fair   = simulate_tosses(n, p_fair);
    long heads_biased = simulate_tosses(n, p_biased);

    printf("%-20s %-15s %-15s %-15s\n", "Coin Type", "True P(H)", "Observed Heads", "Est. P(H)");
    printf("%-20s %-15.2f %-15ld %-15.5f\n", "Fair Coin",   p_fair,   heads_fair,   (double) heads_fair / n);
    printf("%-20s %-15.2f %-15ld %-15.5f\n", "Biased Coin", p_biased, heads_biased, (double) heads_biased / n);

    printf("\nObservation:\n");
    printf(" - Fair coin's estimated P(Heads) is close to 0.50\n");
    printf(" - Biased coin's estimated P(Heads) is close to %.2f\n", p_biased);
    printf(" - Both estimates converge towards their TRUE underlying\n");
    printf("   probability as the number of tosses increases, but the\n");
    printf("   biased coin systematically favors one outcome.\n");

    return 0;
}
