#include <stdio.h>
#include <stdlib.h>

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

    int position = pivotIndex - low + 1;

    if (position == k)
        return a[pivotIndex];

    if (k < position)
        return quickSelect(a, low, pivotIndex - 1, k);

    return quickSelect(a, pivotIndex + 1, high, k - position);
}

int main()
{
    int n, k;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = (int *)malloc(n * sizeof(int));

    printf("Enter elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter K: ");
    scanf("%d", &k);

    if (k < 1 || k > n)
    {
        printf("Invalid value of K.\n");
        free(a);
        return 0;
    }

    int result = quickSelect(a, 0, n - 1, k);

    printf("%d-th smallest element = %d\n", k, result);

    free(a);

    return 0;
}