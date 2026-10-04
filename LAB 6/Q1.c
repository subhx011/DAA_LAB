#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* (i) Finding maximum */
int findMax(int a[], int n)
{
    int max = a[0];

    for (int i = 1; i < n; i++)
    {
        if (a[i] > max)
            max = a[i];
    }

    return max;
}

/* (ii) Finding first and second largest */
void findLargestTwo(int a[], int n)
{
    int first, second;

    if (a[0] > a[1])
    {
        first = a[0];
        second = a[1];
    }
    else
    {
        first = a[1];
        second = a[0];
    }

    for (int i = 2; i < n; i++)
    {
        if (a[i] > first)
        {
            second = first;
            first = a[i];
        }
        else if (a[i] > second)
        {
            second = a[i];
        }
    }

    printf("Largest = %d\n", first);
    printf("Second Largest = %d\n", second);
}

/* (iii) Finding mean */
double findMean(int a[], int n)
{
    long long sum = 0;

    for (int i = 0; i < n; i++)
        sum += a[i];

    return (double)sum / n;
}

/* Function used for median */
int compare(const void *x, const void *y)
{
    return (*(int *)x - *(int *)y);
}

/* (iv) Finding median */
double findMedian(int a[], int n)
{
    int *b = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        b[i] = a[i];

    qsort(b, n, sizeof(int), compare);

    double median;

    if (n % 2 == 0)
        median = (b[n / 2 - 1] + b[n / 2]) / 2.0;
    else
        median = b[n / 2];

    free(b);

    return median;
}

/* (v) Finding standard deviation */
double findSD(int a[], int n)
{
    double mean = findMean(a, n);
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        double difference = a[i] - mean;
        sum += difference * difference;
    }

    return sqrt(sum / n);
}

/* (vi) Finding mode */
int findMode(int a[], int n)
{
    int mode = a[0];
    int maxCount = 1;

    for (int i = 0; i < n; i++)
    {
        int count = 0;

        for (int j = 0; j < n; j++)
        {
            if (a[i] == a[j])
                count++;
        }

        if (count > maxCount)
        {
            maxCount = count;
            mode = a[i];
        }
    }

    return mode;
}

/* (vii) Removing duplicates */
int removeDuplicates(int a[], int n)
{
    int newSize = 0;

    for (int i = 0; i < n; i++)
    {
        int duplicate = 0;

        for (int j = 0; j < newSize; j++)
        {
            if (a[i] == a[j])
            {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate)
        {
            a[newSize] = a[i];
            newSize++;
        }
    }

    return newSize;
}

/* (viii) Reversing array */
void reverseArray(int a[], int n)
{
    int i = 0, j = n - 1;

    while (i < j)
    {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;

        i++;
        j--;
    }
}

/* (ix) Partition with respect to pivot
   Elements >= pivot come before elements < pivot
*/
void partitionArray(int a[], int n, int pivot)
{
    int i = 0;
    int j = n - 1;

    while (i <= j)
    {
        while (i <= j && a[i] >= pivot)
            i++;

        while (i <= j && a[j] < pivot)
            j--;

        if (i < j)
        {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;

            i++;
            j--;
        }
    }
}

/* Display array */
void display(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("\nMaximum = %d\n", findMax(a, n));

    printf("\nFirst and Second Largest:\n");
    findLargestTwo(a, n);

    printf("\nMean = %.2lf\n", findMean(a, n));

    printf("Median = %.2lf\n", findMedian(a, n));

    printf("Standard Deviation = %.2lf\n", findSD(a, n));

    printf("Mode = %d\n", findMode(a, n));

    int newSize = removeDuplicates(a, n);

    printf("\nAfter removing duplicates:\n");
    display(a, newSize);

    reverseArray(a, newSize);

    printf("After reversing:\n");
    display(a, newSize);

    int pivot;
    printf("\nEnter pivot: ");
    scanf("%d", &pivot);

    partitionArray(a, newSize, pivot);

    printf("After partitioning:\n");
    display(a, newSize);

    free(a);

    return 0;
}