#include <stdio.h>

int comparisons = 0;

void maxMin(int arr[], int low, int high, int *max, int *min)
{
    int mid;
    int max1, min1, max2, min2;

    /* Only one element */
    if (low == high)
    {
        *max = arr[low];
        *min = arr[low];
        return;
    }

    /* Two elements */
    if (high == low + 1)
    {
        comparisons++;

        if (arr[low] > arr[high])
        {
            *max = arr[low];
            *min = arr[high];
        }
        else
        {
            *max = arr[high];
            *min = arr[low];
        }

        return;
    }

    /* Divide */
    mid = (low + high) / 2;

    /* Conquer */
    maxMin(arr, low, mid, &max1, &min1);
    maxMin(arr, mid + 1, high, &max2, &min2);

    /* Combine: compare the two maximums */
    comparisons++;

    if (max1 > max2)
        *max = max1;
    else
        *max = max2;

    /* Combine: compare the two minimums */
    comparisons++;

    if (min1 < min2)
        *min = min1;
    else
        *min = min2;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter array elements:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int maximum, minimum;

    maxMin(arr, 0, n - 1, &maximum, &minimum);

    printf("\nMaximum = %d\n", maximum);
    printf("Minimum = %d\n", minimum);

    printf("Number of comparisons = %d\n", comparisons);

    printf("3n/2 = %.1f\n", 1.5 * n);

    return 0;
}