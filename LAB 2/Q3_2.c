#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void merge(int a[], int n1, int b[], int n2, int result[])
{
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2)
    {
        if (a[i] <= b[j])
            result[k++] = a[i++];
        else
            result[k++] = b[j++];
    }

    while (i < n1)
        result[k++] = a[i++];

    while (j < n2)
        result[k++] = b[j++];
}

int arrays[MAX][MAX * MAX];

int mergeArrays(int left, int right, int size)
{
    if (left == right)
        return size;

    int mid = (left + right) / 2;

    int leftSize = mergeArrays(left, mid, size);
    int rightSize = mergeArrays(mid + 1, right, size);

    int temp[MAX * MAX];

    merge(arrays[left], leftSize,
          arrays[mid + 1], rightSize,
          temp);

    for (int i = 0; i < leftSize + rightSize; i++)
        arrays[left][i] = temp[i];

    return leftSize + rightSize;
}

int main()
{
    int k, n;

    printf("Enter number of arrays: ");
    scanf("%d", &k);

    printf("Enter size of each array: ");
    scanf("%d", &n);

    printf("Enter sorted arrays:\n");

    for (int i = 0; i < k; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &arrays[i][j]);

    int finalSize = mergeArrays(0, k - 1, n);

    printf("\nMerged Array:\n");

    for (int i = 0; i < finalSize; i++)
        printf("%d ", arrays[0][i]);

    return 0;
}