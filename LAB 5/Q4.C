#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Heapify subtree rooted at index i */
void heapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i)
    {
        swap(&a[i], &a[largest]);

        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    /* Build Max Heap */

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    /* Extract elements one by one */

    for (int i = n - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);

        heapify(a, i, 0);
    }
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));

    FILE *fp;

    /* Generate random numbers and store them in file */
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

    /* Heap Sort */

    heapSort(a, n);

    printf("\n\nSorted elements:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    free(a);

    return 0;
}