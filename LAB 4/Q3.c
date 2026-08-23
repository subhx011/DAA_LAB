#include <stdio.h>
#include <stdlib.h>

int found = 0;

/* Comparison function for qsort */
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

/* Binary Search */
int binarySearch(int arr[], int n, int key)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
            return 1;

        else if (arr[mid] < key)
            low = mid + 1;

        else
            high = mid - 1;
    }

    return 0;
}

/*
   Choose k-1 elements.
   When k-1 elements are selected,
   search for the required last element.
*/
void findKSum(int arr[], int n, int k,
              int start, int count,
              int currentSum, int target)
{
    if (found)
        return;

    /* We have selected k-1 elements */
    if (count == k - 1)
    {
        int required = target - currentSum;

        if (binarySearch(arr, n, required))
        {
            found = 1;
        }

        return;
    }

    /* Select the next element */
    for (int i = start; i < n; i++)
    {
        findKSum(arr, n, k,
                 i + 1,
                 count + 1,
                 currentSum + arr[i],
                 target);
    }
}

int main()
{
    int n, k, T;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int S[n];

    printf("Enter elements of S:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &S[i]);
    }

    printf("Enter k: ");
    scanf("%d", &k);

    printf("Enter target T: ");
    scanf("%d", &T);

    /* Sort the set */
    qsort(S, n, sizeof(int), compare);

    findKSum(S, n, k, 0, 0, 0, T);

    if (found)
        printf("YES: %d elements can add up to %d\n", k, T);
    else
        printf("NO: No %d elements add up to %d\n", k, T);

    return 0;
}