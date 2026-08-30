#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int a[], int low, int high)
{
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[high]);

    return i + 1;
}

void quickSort(int a[], int low, int high)
{
    if (low < high)
    {
        int p = partition(a, low, high);

        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));

    FILE *fp;

    /* Generate random numbers and store in file */
    fp = fopen("input.txt", "w");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        free(a);
        return 1;
    }

    srand(time(NULL));

    printf("\nRandom elements:\n");

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 1000;

        fprintf(fp, "%d ", a[i]);

        printf("%d ", a[i]);
    }

    fclose(fp);

    /* Read elements from file */
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("\nError opening file.\n");
        free(a);
        return 1;
    }

    for (int i = 0; i < n; i++)
        fscanf(fp, "%d", &a[i]);

    fclose(fp);

    /* Quick Sort */
    quickSort(a, 0, n - 1);

    printf("\n\nSorted elements:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    free(a);

    return 0;
}