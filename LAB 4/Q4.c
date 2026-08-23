#include <stdio.h>
#include <stdlib.h>

struct Event
{
    int time;
    int type;   // +1 = entry, -1 = exit
};

/* Comparison function for qsort */
int compare(const void *a, const void *b)
{
    struct Event *e1 = (struct Event *)a;
    struct Event *e2 = (struct Event *)b;

    return e1->time - e2->time;
}

int main()
{
    int n;

    printf("Enter number of people: ");
    scanf("%d", &n);

    struct Event events[2 * n];

    int entry, exit;

    for (int i = 0; i < n; i++)
    {
        printf("Enter entry and exit time for person %d: ", i + 1);

        scanf("%d %d", &entry, &exit);

        events[2 * i].time = entry;
        events[2 * i].type = 1;

        events[2 * i + 1].time = exit;
        events[2 * i + 1].type = -1;
    }

    /* Sort all events according to time */
    qsort(events, 2 * n, sizeof(struct Event), compare);

    int currentPeople = 0;
    int maxPeople = 0;
    int maxTime = 0;

    /* Scan the sorted events */
    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == 1)
        {
            currentPeople++;

            if (currentPeople > maxPeople)
            {
                maxPeople = currentPeople;
                maxTime = events[i].time;
            }
        }
        else
        {
            currentPeople--;
        }
    }

    printf("\nMaximum number of people = %d\n", maxPeople);
    printf("Time when maximum occurred = %d\n", maxTime);

    return 0;
}