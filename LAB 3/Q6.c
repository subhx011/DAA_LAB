#include <stdio.h>

int main()
{
    int A[100];
    int n;
    int i, j, min, temp;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    /* Selection Sort */
    for (i = 0; i < n - 1; i++)
    {
        min = i;

        for (j = i + 1; j < n; j++)
        {
            if (A[j] < A[min])
            {
                min = j;
            }
        }

        /* Exchange A[i] and A[min] */
        temp = A[i];
        A[i] = A[min];
        A[min] = temp;
    }

    printf("Sorted array:\n");

    for (i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }

    return 0;
}