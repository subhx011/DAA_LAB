#include<stdio.h>

int partition(int a[], int n)
{
    int low = 0;
    int high = n - 1;
    int mid;

    while(low <= high)
    {
        mid = (low + high) / 2;

        if(a[mid] == 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return low;
}

int main()
{
    int a[] = {0,0,0,0,1,1,1,1};

    int n = 8;

    printf("Partition Index = %d", partition(a,n));

    return 0;
}