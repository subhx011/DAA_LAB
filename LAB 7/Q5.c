#include <stdio.h>

int main() {

    int n, i;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1) {
        printf("Invalid input. n must be greater than 1.\n");
        return 0;
    }

    printf("Shooting sequence:\n");

    /*
       Shoot each position in sequence.
       After each shot the target moves
       to an adjacent position.
    */

    for (i = 2; i <= n; i++) {
        printf("Shoot hiding spot %d\n", i);
    }

    printf("Shoot hiding spot 1\n");

    return 0;
}