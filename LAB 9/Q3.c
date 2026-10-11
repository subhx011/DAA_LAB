
#include <stdio.h>

int main(void) {
    int n, D, F;
    int d[100], fuel[100];
    int i, j, current = 0, stops = 0;

    printf("Enter destination and initial fuel: ");
    scanf("%d %d", &D, &F);

    printf("Enter number of stations: ");
    scanf("%d", &n);

    if (n < 0 || n > 100 || D < 0 || F < 0)
        return 1;

    for (i = 0; i < n; i++) {
        printf("Enter station distance and fuel: ");
        scanf("%d %d", &d[i], &fuel[i]);
    }

    /* Sort stations by distance */
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (d[j] > d[j + 1]) {
                int temp = d[j];
                d[j] = d[j + 1];
                d[j + 1] = temp;

                temp = fuel[j];
                fuel[j] = fuel[j + 1];
                fuel[j + 1] = temp;
            }
        }
    }

    for (i = 0; i <= n; i++) {
        int next = (i == n) ? D : d[i];
        int distance = next - current;

        while (F < distance) {
            int best = -1;

            /* Choose the largest fuel among
               stations already passed */
            for (j = 0; j < i; j++) {
                if (fuel[j] > best)
                    best = fuel[j];
            }

            if (best <= 0) {
                printf("Destination cannot be reached\n");
                return 0;
            }

            F += best;
            stops++;

            /* Mark the selected fuel as used */
            for (j = 0; j < i; j++) {
                if (fuel[j] == best) {
                    fuel[j] = 0;
                    break;
                }
            }
        }

        F -= distance;
        current = next;
    }

    printf("Minimum refuelling stops = %d\n", stops);

    return 0;
}
