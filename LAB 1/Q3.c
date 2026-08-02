#include <stdio.h>
#include <stdlib.h>
#include <time.h>


long bubble_sort_optimized(int arr[], int n) {
    long comparisons = 0;
    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) a[i] = arr[i];

    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;   
    }
    free(a);
    return comparisons;
}


long bubble_sort_full(int arr[], int n) {
    long comparisons = 0;
    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) a[i] = arr[i];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
        
    }
    free(a);
    return comparisons;
}

void generate_random_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

int main(int argc, char *argv[]) {
    srand((unsigned int) time(NULL));

    int sizes[] = {100, 200, 400, 800, 1000, 1500, 2000, 2500, 3000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int trials_per_size = 5;   

    FILE *fp = fopen("bubble_sort_results.csv", "w");
    if (!fp) {
        fprintf(stderr, "Could not open output file\n");
        return 1;
    }
    fprintf(fp, "n,comparisons_optimized,comparisons_full\n");

    printf("%-8s %-22s %-18s\n", "n", "Optimized (avg)", "Full (avg)");

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        long total_opt = 0, total_full = 0;

        for (int t = 0; t < trials_per_size; t++) {
            int *arr = malloc(n * sizeof(int));
            generate_random_array(arr, n);
            total_opt  += bubble_sort_optimized(arr, n);
            total_full += bubble_sort_full(arr, n);
            free(arr);
        }

        double avg_opt  = (double) total_opt  / trials_per_size;
        double avg_full = (double) total_full / trials_per_size;

        printf("%-8d %-22.1f %-18.1f\n", n, avg_opt, avg_full);
        fprintf(fp, "%d,%.1f,%.1f\n", n, avg_opt, avg_full);
    }

    fclose(fp);
    printf("\nRandom-data results written to bubble_sort_results.csv\n");


    FILE *fp2 = fopen("bubble_sort_bestcase.csv", "w");
    if (!fp2) {
        fprintf(stderr, "Could not open bestcase output file\n");
        return 1;
    }
    fprintf(fp2, "n,comparisons_optimized,comparisons_full\n");

    printf("\n--- Best-case sweep: already-sorted arrays ---\n");
    printf("%-8s %-22s %-18s\n", "n", "Optimized", "Full");
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int *sorted_arr = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) sorted_arr[i] = i; /* already sorted */

        long opt_demo  = bubble_sort_optimized(sorted_arr, n);
        long full_demo = bubble_sort_full(sorted_arr, n);

        printf("%-8d %-22ld %-18ld\n", n, opt_demo, full_demo);
        fprintf(fp2, "%d,%ld,%ld\n", n, opt_demo, full_demo);

        free(sorted_arr);
    }
    fclose(fp2);
    printf("\nBest-case results written to bubble_sort_bestcase.csv\n");

    return 0;
}
