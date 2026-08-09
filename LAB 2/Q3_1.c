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

int main()
{
    int k, n;

    printf("Enter number of arrays: ");
    scanf("%d", &k);

    printf("Enter size of each array: ");
    scanf("%d", &n);

    int arr[MAX][MAX];

    printf("Enter sorted arrays:\n");

    for (int i = 0; i < k; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &arr[i][j]);

    int temp[MAX * MAX];
    int result[MAX * MAX];

    for (int i = 0; i < n; i++)
        temp[i] = arr[0][i];

    int currentSize = n;

    for (int i = 1; i < k; i++)
    {
        merge(temp, currentSize, arr[i], n, result);

        currentSize += n;

        for (int j = 0; j < currentSize; j++)
            temp[j] = result[j];
    }

    printf("\nMerged Array:\n");

    for (int i = 0; i < currentSize; i++)
        printf("%d ", temp[i]);

    return 0;
}