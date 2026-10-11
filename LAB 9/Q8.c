
#include <stdio.h>

int main(void) {
    int n, i, j;
    int start[100], end[100];
    int rooms = 0, maxRooms = 0;

    printf("Enter number of meetings: ");
    scanf("%d", &n);

    if (n < 1 || n > 100) {
        printf("Invalid number of meetings\n");
        return 1;
    }

    printf("Enter start and end time of each meeting:\n");

    for (i = 0; i < n; i++) {
        scanf("%d %d", &start[i], &end[i]);

        if (end[i] < start[i]) {
            printf("Invalid meeting interval\n");
            return 1;
        }
    }

    /* Sort meetings by start time */
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (start[j] > start[j + 1]) {
                int temp = start[j];
                start[j] = start[j + 1];
                start[j + 1] = temp;

                temp = end[j];
                end[j] = end[j + 1];
                end[j + 1] = temp;
            }
        }
    }

    /* Count meetings that overlap */
    for (i = 0; i < n; i++) {
        rooms = 0;

        for (j = 0; j <= i; j++) {
            if (start[j] <= start[i] &&
                end[j] > start[i]) {
                rooms++;
            }
        }

        if (rooms > maxRooms)
            maxRooms = rooms;
    }

    printf("Minimum rooms required = %d\n", maxRooms);

    return 0;
}
