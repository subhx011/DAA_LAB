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

int quickSelect(int a[], int low, int high, int k)
{
    if (low == high)
        return a[low];

    int pivotIndex = partition(a, low, high);

    int count = pivotIndex - low + 1;

    if (k == count)
        return a[pivotIndex];

    if (k < count)
        return quickSelect(a, low, pivotIndex - 1, k);

    return quickSelect(a, pivotIndex + 1, high, k - count);
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    if (n % 2 == 1)
    {
        int k = (n + 1) / 2;
        int median = quickSelect(a, 0, n - 1, k);

        printf("Median = %d\n", median);
    }
    else
    {
        int k1 = n / 2;
        int k2 = (n / 2) + 1;

        int x = quickSelect(a, 0, n - 1, k1);
        int y = quickSelect(a, 0, n - 1, k2);

        printf("Median = %.2f\n", (x + y) / 2.0);
    }

    free(a);

    return 0;
}