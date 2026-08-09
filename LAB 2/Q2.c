#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000

/*-------------------- Merge Sort --------------------*/

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    int i, j, k;

    for(i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for(i = 0; i < n2; i++)
        R[i] = arr[m + 1 + i];

    i = 0;
    j = 0;
    k = l;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r)
{
    if(l < r)
    {
        int m = (l + r) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

/*---------------- Three Way Merge Sort ----------------*/

void mergeThree(int arr[], int l, int m1, int m2, int r)
{
    int temp[MAX];

    int i = l;
    int j = m1 + 1;
    int k = m2 + 1;
    int t = l;

    while(i <= m1 && j <= m2 && k <= r)
    {
        if(arr[i] <= arr[j] && arr[i] <= arr[k])
            temp[t++] = arr[i++];
        else if(arr[j] <= arr[i] && arr[j] <= arr[k])
            temp[t++] = arr[j++];
        else
            temp[t++] = arr[k++];
    }

    while(i <= m1 && j <= m2)
        temp[t++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];

    while(j <= m2 && k <= r)
        temp[t++] = (arr[j] < arr[k]) ? arr[j++] : arr[k++];

    while(i <= m1 && k <= r)
        temp[t++] = (arr[i] < arr[k]) ? arr[i++] : arr[k++];

    while(i <= m1)
        temp[t++] = arr[i++];

    while(j <= m2)
        temp[t++] = arr[j++];

    while(k <= r)
        temp[t++] = arr[k++];

    for(i = l; i <= r; i++)
        arr[i] = temp[i];
}

void threeWayMergeSort(int arr[], int l, int r)
{
    if(l >= r)
        return;

    int third = (r - l + 1) / 3;

    int m1 = l + third - 1;
    int m2 = l + 2 * third - 1;

    if(m1 < l)
        m1 = l;

    if(m2 < m1 + 1)
        m2 = m1 + 1;

    if(m2 >= r)
        m2 = r - 1;

    threeWayMergeSort(arr, l, m1);
    threeWayMergeSort(arr, m1 + 1, m2);
    threeWayMergeSort(arr, m2 + 1, r);

    mergeThree(arr, l, m1, m2, r);
}

/*----------------------- Main ------------------------*/

int main()
{
    int sizes[] = {1000,2000,5000,10000,20000,50000};
    int n, i;

    printf("Size\tMerge(ms)\tThreeWay(ms)\n");

    for(int s = 0; s < 6; s++)
    {
        n = sizes[s];

        int *a = (int *)malloc(n * sizeof(int));
        int *b = (int *)malloc(n * sizeof(int));

        for(i = 0; i < n; i++)
        {
            a[i] = rand();
            b[i] = a[i];
        }

        clock_t start = clock();
        mergeSort(a,0,n-1);
        clock_t end = clock();

        double mergeTime =
        (double)(end-start)*1000/CLOCKS_PER_SEC;

        start = clock();
        threeWayMergeSort(b,0,n-1);
        end = clock();

        double threeTime =
        (double)(end-start)*1000/CLOCKS_PER_SEC;

        printf("%d\t%.3f\t\t%.3f\n",
               n,mergeTime,threeTime);

        free(a);
        free(b);
    }

    return 0;
}