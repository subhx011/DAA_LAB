#include <stdio.h>
#include <stdlib.h>

struct Interval
{
    int start;
    int end;
};

/* Compare intervals according to starting time */
int compare(const void *a, const void *b)
{
    struct Interval *i1 = (struct Interval *)a;
    struct Interval *i2 = (struct Interval *)b;

    return i1->start - i2->start;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Interval intervals[n];
    struct Interval merged[n];

    /* Input */
    printf("Enter intervals (start end):\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d",
              &intervals[i].start,
              &intervals[i].end);
    }

    /* Step 1: Sort intervals by starting time */
    qsort(intervals,
          n,
          sizeof(struct Interval),
          compare);

    /* Step 2: Merge overlapping intervals */

    int count = 0;

    merged[0] = intervals[0];
    count = 1;

    for (int i = 1; i < n; i++)
    {
        /* Check for overlap */
        if (intervals[i].start <= merged[count - 1].end)
        {
            /* Merge */
            if (intervals[i].end > merged[count - 1].end)
            {
                merged[count - 1].end = intervals[i].end;
            }
        }
        else
        {
            /* No overlap */
            merged[count] = intervals[i];
            count++;
        }
    }

    /* Output */
    printf("\nMerged intervals:\n");

    for (int i = 0; i < count; i++)
    {
        printf("(%d, %d) ",
               merged[i].start,
               merged[i].end);
    }

    printf("\n");

    return 0;
}