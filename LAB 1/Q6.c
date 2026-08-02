#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ---------------------------------------------------------
   Method: Brute-force pairwise comparison
   Checks every pair (i, j) for equality.
   Returns 1 if a duplicate exists, 0 otherwise.
   Also reports the number of comparisons performed via out param.
   --------------------------------------------------------- */
int has_duplicate_bruteforce(int arr[], int n, long *comparisons) {
    long count = 0;
    int found = 0;
    for (int i = 0; i < n && !found; i++) {
        for (int j = i + 1; j < n; j++) {
            count++;
            if (arr[i] == arr[j]) {
                found = 1;
                break;
            }
        }
    }
    *comparisons = count;
    return found;
}

/* ---------------------------------------------------------
   Comparator for qsort
   --------------------------------------------------------- */
int cmp_int(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

/* ---------------------------------------------------------
   Method: Sort-then-scan
   Sorts the array (O(n log n)) then does a single linear pass
   to check adjacent elements for equality.
   --------------------------------------------------------- */
int has_duplicate_sorting(int arr[], int n, long *comparisons) {
    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) a[i] = arr[i];

    qsort(a, n, sizeof(int), cmp_int);   /* O(n log n), not counted in comparisons here */

    long count = 0;
    int found = 0;
    for (int i = 0; i < n - 1; i++) {
        count++;
        if (a[i] == a[i + 1]) {
            found = 1;
            break;
        }
    }
    *comparisons = count;
    free(a);
    return found;
}

void generate_random_array(int arr[], int n, int value_range) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % value_range;
    }
}

int main(void) {
    srand((unsigned int) time(NULL));

    /* --- Small demo: show it working directly --- */
    int demo[] = {4, 2, 9, 7, 2, 5};
    int demo_n = sizeof(demo) / sizeof(demo[0]);
    long demo_cmp;
    int demo_result = has_duplicate_bruteforce(demo, demo_n, &demo_cmp);
    printf("=========================================\n");
    printf(" Demo array: {4, 2, 9, 7, 2, 5}\n");
    printf("=========================================\n");
    printf("Duplicate found : %s\n", demo_result ? "YES" : "NO");
    printf("Comparisons used: %ld\n\n", demo_cmp);

    /* --- Performance sweep: brute force vs sort-then-scan --- */
    int sizes[] = {100, 500, 1000, 2000, 4000, 8000, 12000, 16000, 20000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int trials = 5;
    int value_range = 1000000000; /* huge range -> duplicates are rare/no early exit */

    FILE *fp = fopen("uniqueness_results.csv", "w");
    fprintf(fp, "n,comparisons_bruteforce,comparisons_sorting\n");

    printf("=========================================\n");
    printf(" No-duplicate worst case: large value range\n");
    printf(" (forces full scan since arrays are unique)\n");
    printf("=========================================\n");
    printf("%-8s %-22s %-18s\n", "n", "Brute force (avg)", "Sort+scan (avg)");

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        long total_bf = 0, total_sort = 0;

        for (int t = 0; t < trials; t++) {
            int *arr = malloc(n * sizeof(int));
            generate_random_array(arr, n, value_range);
            long cmp_bf, cmp_sort;
            has_duplicate_bruteforce(arr, n, &cmp_bf);
            has_duplicate_sorting(arr, n, &cmp_sort);
            total_bf += cmp_bf;
            total_sort += cmp_sort;
            free(arr);
        }

        double avg_bf = (double) total_bf / trials;
        double avg_sort = (double) total_sort / trials;

        printf("%-8d %-22.1f %-18.1f\n", n, avg_bf, avg_sort);
        fprintf(fp, "%d,%.1f,%.1f\n", n, avg_bf, avg_sort);
    }
    fclose(fp);
    printf("\nResults written to uniqueness_results.csv\n");

    return 0;
}
