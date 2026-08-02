#include <stdio.h>
#include <stdlib.h>


long hanoi(int n, char from, char aux, char to, int print_moves) {
    if (n == 0) return 0;

    long moves = 0;
    moves += hanoi(n - 1, from, to, aux, print_moves);

    if (print_moves) {
        printf("Move disc %d from %c to %c\n", n, from, to);
    }
    moves += 1;

    moves += hanoi(n - 1, aux, from, to, print_moves);
    return moves;
}

int main(void) {
    
    int demo_n = 4;
    printf("=========================================\n");
    printf(" Full move sequence for n = %d discs\n", demo_n);
    printf("=========================================\n");
    long demo_moves = hanoi(demo_n, 'A', 'B', 'C', 1);
    printf("Total moves for n = %d: %ld\n\n", demo_n, demo_moves);

    
    int max_n = 20;
    FILE *fp = fopen("hanoi_results.csv", "w");
    if (!fp) {
        fprintf(stderr, "Could not open output file\n");
        return 1;
    }
    fprintf(fp, "n,moves,formula_2n_minus_1\n");

    printf("=========================================\n");
    printf(" Move counts for n = 1..%d discs\n", max_n);
    printf("=========================================\n");
    printf("%-6s %-15s %-15s\n", "n", "Moves (sim)", "2^n - 1");

    for (int n = 1; n <= max_n; n++) {
        long moves = hanoi(n, 'A', 'B', 'C', 0);   
        long formula = (1L << n) - 1;             
        printf("%-6d %-15ld %-15ld\n", n, moves, formula);
        fprintf(fp, "%d,%ld,%ld\n", n, moves, formula);
    }

    fclose(fp);
    printf("\nResults written to hanoi_results.csv\n");

    return 0;
}
