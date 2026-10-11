
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, i, step;
    double W, total = 0, time = 0;

    printf("Enter number of items: ");
    scanf("%d", &n);

    double *v = malloc(n * sizeof(double));
    double *w = malloc(n * sizeof(double));
    double *lambda = malloc(n * sizeof(double));
    int *used = calloc(n, sizeof(int));

    for (i = 0; i < n; i++) {
        printf("Enter value, weight and decay rate: ");
        scanf("%lf %lf %lf", &v[i], &w[i], &lambda[i]);
    }

    printf("Enter knapsack capacity: ");
    scanf("%lf", &W);

    for (step = 0; step < n && W > 0; step++) {
        int best = -1;
        double density = -1e300;

        for (i = 0; i < n; i++) {
            if (!used[i] && w[i] > 0) {
                double d = v[i] / w[i] - lambda[i] * time;
                if (d > density) {
                    density = d;
                    best = i;
                }
            }
        }

        if (best == -1 || density <= 0)
            break;

        double take = (w[best] < W) ? w[best] : W;
        total += take * density;
        W -= take;
        used[best] = 1;
        time++;
    }

    printf("Total value = %.2f\n", total);

    free(v);
    free(w);
    free(lambda);
    free(used);

    return 0;
}
