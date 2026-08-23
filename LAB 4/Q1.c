#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int number;
    char colour;
} Item;

int main() {
    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item *items = (Item *)malloc(n * sizeof(Item));

    if (items == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter %d pairs (number colour):\n", n);

    for (int i = 0; i < n; i++) {
        scanf("%d %c", &items[i].number, &items[i].colour);
    }

    /* Arrays for the three colours */
    Item *red = (Item *)malloc(n * sizeof(Item));
    Item *blue = (Item *)malloc(n * sizeof(Item));
    Item *yellow = (Item *)malloc(n * sizeof(Item));

    int r = 0, b = 0, y = 0;

    /* Single traversal */
    for (int i = 0; i < n; i++) {

        if (items[i].colour == 'R') {
            red[r++] = items[i];
        }
        else if (items[i].colour == 'B') {
            blue[b++] = items[i];
        }
        else if (items[i].colour == 'Y') {
            yellow[y++] = items[i];
        }
        else {
            printf("Invalid colour: %c\n", items[i].colour);
            free(items);
            free(red);
            free(blue);
            free(yellow);
            return 1;
        }
    }

    /* Combine the three groups */
    int k = 0;

    for (int i = 0; i < r; i++)
        items[k++] = red[i];

    for (int i = 0; i < b; i++)
        items[k++] = blue[i];

    for (int i = 0; i < y; i++)
        items[k++] = yellow[i];

    printf("\nSorted by colour:\n");

    for (int i = 0; i < n; i++) {
        printf("(%d, %c) ", items[i].number, items[i].colour);
    }

    printf("\n");

    free(items);
    free(red);
    free(blue);
    free(yellow);

    return 0;
}