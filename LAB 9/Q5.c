
#include <stdio.h>

int main(void) {
    int n, i;
    int rating[100], candy[100];
    int total = 0;

    printf("Enter number of children: ");
    scanf("%d", &n);

    if (n < 1 || n > 100) {
        printf("Invalid number of children\n");
        return 1;
    }

    printf("Enter ratings of children:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &rating[i]);
        candy[i] = 1;
    }

    /* Left to right */
    for (i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1]) {
            candy[i] = candy[i - 1] + 1;
        }
    }

    /* Right to left */
    for (i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1] &&
            candy[i] <= candy[i + 1]) {
            candy[i] = candy[i + 1] + 1;
        }
    }

    /* Calculate total candies */
    printf("Candies given to each child: ");

    for (i = 0; i < n; i++) {
        printf("%d ", candy[i]);
        total += candy[i];
    }

    printf("\nMinimum total candies = %d\n", total);

    return 0;
}
