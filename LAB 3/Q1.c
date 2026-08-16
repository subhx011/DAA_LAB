#include <stdio.h>

int binarySearch(int arr[], int n, int x, int *comparisons)
{
    int low = 0, high = n - 1;
    *comparisons = 0;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        (*comparisons)++;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int ternarySearch(int arr[], int n, int x, int *comparisons)
{
    int low = 0, high = n - 1;
    *comparisons = 0;

    while (low <= high)
    {
        int third = (high - low) / 3;

        int mid1 = low + third;
        int mid2 = high - third;

        (*comparisons)++;
        if (arr[mid1] == x)
            return mid1;

        (*comparisons)++;
        if (arr[mid2] == x)
            return mid2;

        if (x < arr[mid1])
        {
            high = mid1 - 1;
        }
        else if (x > arr[mid2])
        {
            low = mid2 + 1;
        }
        else
        {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }

    return -1;
}

int main()
{
    int n, x;
    int binaryComparisons, ternaryComparisons;
    int binaryResult, ternaryResult;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements in sorted order:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter element to search: ");
    scanf("%d", &x);

    binaryResult = binarySearch(arr, n, x, &binaryComparisons);
    ternaryResult = ternarySearch(arr, n, x, &ternaryComparisons);

    printf("\n--- Binary Search ---\n");

    if (binaryResult != -1)
        printf("Element found at index %d\n", binaryResult);
    else
        printf("Element not found\n");

    printf("Number of comparisons: %d\n", binaryComparisons);

    printf("\n--- Ternary Search ---\n");

    if (ternaryResult != -1)
        printf("Element found at index %d\n", ternaryResult);
    else
        printf("Element not found\n");

    printf("Number of comparisons: %d\n", ternaryComparisons);

    printf("\n--- Comparison ---\n");

    if (binaryComparisons < ternaryComparisons)
        printf("Binary Search is better for this input.\n");
    else if (ternaryComparisons < binaryComparisons)
        printf("Ternary Search used fewer comparisons for this input.\n");
    else
        printf("Both used the same number of comparisons for this input.\n");

    return 0;
}