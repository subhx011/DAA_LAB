
#include <stdio.h>

int main(void) {
    int n, i, j;
    int a[100];
    int min, max, deviation;

    printf("Enter array size: ");
    scanf("%d", &n);

    if (n < 1 || n > 100) {
        printf("Invalid array size\n");
        return 1;
    }

    printf("Enter positive integers:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);

        if (a[i] <= 0 || a[i] > 1000000000) {
            printf("Invalid element\n");
            return 1;
        }

        /* Make every odd number even */
        if (a[i] % 2 != 0)
            a[i] *= 2;
    }

    /* Find the initial minimum and maximum */
    min = a[0];
    max = a[0];

    for (i = 1; i < n; i++) {
        if (a[i] < min)
            min = a[i];

        if (a[i] > max)
            max = a[i];
    }

    deviation = max - min;

    /* Repeatedly reduce the maximum if it is even */
    while (max % 2 == 0) {
        max /= 2;

        if (max < min)
            min = max;

        if (max - min < deviation)
            deviation = max - min;

        /* Find the new maximum */
        for (i = 0; i < n; i++) {
            if (a[i] == max * 2 && a[i] % 2 == 0)
                a[i] /= 2;
        }

        max = a[0];

        for (i = 1; i < n; i++) {
            if (a[i] > max)
                max = a[i];
        }
    }

    printf("Minimum deviation = %d\n", deviation);

    return 0;
}
