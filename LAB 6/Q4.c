#include <stdio.h>
#include <stdlib.h>

/* Global variable to count total reversal cost */
long long totalCost = 0;
int reversalCount = 0;

/*
    Reverse p[i...j]

    Cost = j-i+1
*/
void reverseArray(int p[], int i, int j)
{
    if (i >= j)
        return;

    int length = j - i + 1;

    totalCost += length;
    reversalCount++;

    while (i < j)
    {
        int temp = p[i];
        p[i] = p[j];
        p[j] = temp;

        i++;
        j--;
    }
}

/*
    Rotate two adjacent blocks:

        A B

    into:

        B A

    using three reversals:

        reverse(A)
        reverse(B)
        reverse(AB)
*/
void rotateBlocks(int p[], int l, int m, int r)
{
    if (l > m || m >= r)
        return;

    reverseArray(p, l, m);
    reverseArray(p, m + 1, r);
    reverseArray(p, l, r);
}


/*
    Stable partition.

    All elements satisfying predicate
    "value <= pivot" are moved before
    all elements greater than pivot.

    The function returns the number of
    elements in the left (low) group.
*/
int stablePartition(int p[], int l, int r, int pivot)
{
    if (l == r)
    {
        if (p[l] <= pivot)
            return 1;
        else
            return 0;
    }

    int mid = (l + r) / 2;

    /*
        Partition left half
    */
    int leftLow = stablePartition(p, l, mid, pivot);

    /*
        Partition right half
    */
    int rightLow = stablePartition(p, mid + 1, r, pivot);

    /*
        After recursive partition:

        [LOW][HIGH] [LOW][HIGH]

        We need:

        [LOW][LOW] [HIGH][HIGH]
    */

    int leftLowEnd = l + leftLow - 1;
    int leftHighStart = leftLowEnd + 1;

    int rightLowStart = mid + 1;
    int rightLowEnd = rightLowStart + rightLow - 1;

    /*
        If both middle blocks exist,
        rotate:

        [left HIGH][right LOW]

        into:

        [right LOW][left HIGH]
    */
    if (leftHighStart <= mid &&
        rightLowStart <= rightLowEnd)
    {
        rotateBlocks(
            p,
            leftHighStart,
            mid,
            rightLowEnd
        );
    }

    return leftLow + rightLow;
}


/*
    Recursive sorting according to values.

    Every recursive call handles a range
    of consecutive values.
*/
void sortByReversal(int p[], int l, int r,
                    int valueLow, int valueHigh)
{
    if (l >= r || valueLow >= valueHigh)
        return;

    int midValue =
        (valueLow + valueHigh) / 2;

    /*
        Partition according to value.
        <= midValue goes left.
        > midValue goes right.
    */
    int leftSize =
        stablePartition(
            p,
            l,
            r,
            midValue
        );

    /*
        Recursively sort the two groups.
    */
    if (leftSize > 0)
    {
        sortByReversal(
            p,
            l,
            l + leftSize - 1,
            valueLow,
            midValue
        );
    }

    if (leftSize < r - l + 1)
    {
        sortByReversal(
            p,
            l + leftSize,
            r,
            midValue + 1,
            valueHigh
        );
    }
}


/* Check whether array is sorted */
int isSorted(int p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (p[i] != i + 1)
            return 0;
    }

    return 1;
}


/* Display permutation */
void display(int p[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);

    printf("\n");
}


int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    int *p = malloc(n * sizeof(int));

    printf("Enter permutation of 1 to %d:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("\nOriginal permutation:\n");
    display(p, n);

    /*
        Sort using only reversal operations
    */
    sortByReversal(
        p,
        0,
        n - 1,
        1,
        n
    );

    printf("\nSorted permutation:\n");
    display(p, n);

    printf("\nNumber of reversals = %d\n",
           reversalCount);

    printf("Total reversal cost = %lld\n",
           totalCost);

    if (isSorted(p, n))
        printf("Correctness: SORTED\n");
    else
        printf("Correctness: NOT SORTED\n");

    free(p);

    return 0;
}