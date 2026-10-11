
#include <stdio.h>

int main(void) {
    int n, i, j;
    int a[100];
    long long cost = 0;

    printf("Enter number of sticks: ");
    scanf("%d", &n);

    if (n < 1 || n > 100) {
        printf("Invalid number of sticks\n");
        return 1;
    }

    printf("Enter stick lengths:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);

        if (a[i] < 0) {
            printf("Invalid stick length\n");
            return 1;
        }
    }

    while (n > 1) {
        /* Sort sticks in ascending order */
        for (i = 0; i < n - 1; i++) {
            for (j = 0; j < n - i - 1; j++) {
                if (a[j] > a[j + 1]) {
                    int temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                }
            }
        }

        /* Connect the two shortest sticks */
        int sum = a[0] + a[1];
        cost += sum;

        /* Remove the first two sticks */
        for (i = 2; i < n; i++)
            a[i - 2] = a[i];

        n -= 2;

        /* Insert the combined stick */
        a[n] = sum;
        n++;
    }

    printf("Minimum total cost = %lld\n", cost);

    return 0;
}
