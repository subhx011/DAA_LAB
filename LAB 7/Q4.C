#include <stdio.h>

void turnOff(int n) {

    if (n == 0)
        return;

    if (n == 1) {
        printf("Toggle switch 1 OFF\n");
        return;
    }

    /*
       Turn off the switches on the right
       so that switch n becomes eligible.
    */

    turnOff(n - 2);

    printf("Toggle switch %d OFF\n", n - 1);

    turnOff(n - 2);

    printf("Toggle switch %d OFF\n", n);
}

int main() {

    int n;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    printf("\nSequence:\n");

    turnOff(n);

    return 0;
}