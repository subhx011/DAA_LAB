#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int point;
    int type;       // 1 = START, 0 = END
} Event;

/* Comparison function for qsort */
int compare(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    /* First sort by point */
    if (e1->point != e2->point)
        return e1->point - e2->point;

    /* At the same point, START must come before END */
    return e2->type - e1->type;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Event *events = (Event *)malloc(2 * n * sizeof(Event));

    printf("Enter intervals (left right):\n");

    for (int i = 0; i < n; i++)
    {
        int l, r;

        scanf("%d %d", &l, &r);

        /* Starting point */
        events[2 * i].point = l;
        events[2 * i].type = 1;

        /* Ending point */
        events[2 * i + 1].point = r;
        events[2 * i + 1].type = 0;
    }

    /* Sort all endpoints */
    qsort(events, 2 * n, sizeof(Event), compare);

    int current = 0;
    int maximum = 0;
    int bestPoint = events[0].point;

    /* Scan sorted events */
    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == 1)
        {
            /* Interval starts */
            current++;

            if (current > maximum)
            {
                maximum = current;
                bestPoint = events[i].point;
            }
        }
        else
        {
            /* Interval ends */
            current--;
        }
    }

    printf("\nPoint with maximum overlap = %d\n", bestPoint);
    printf("Maximum number of intervals = %d\n", maximum);

    free(events);

    return 0;
}