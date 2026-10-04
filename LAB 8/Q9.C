#include <stdio.h>

unsigned long long collatz(unsigned long long n) {

    unsigned long long steps = 0;

    printf("%llu", n);

    while (n != 1) {

        if (n % 2 == 0)
            n = n / 2;

        else
            n = 3 * n + 1;

        printf(" -> %llu", n);

        steps++;
    }

    printf("\n");

    return steps;
}

int main() {

    unsigned long long a, b;

    printf("Enter interval [a,b]: ");
    scanf("%llu %llu", &a, &b);

    if (a > b) {
        unsigned long long temp = a;
        a = b;
        b = temp;
    }

    unsigned long long maximumSteps = 0;
    unsigned long long maximumStart = a;

    for (unsigned long long i = a; i <= b; i++) {

        printf("\nStarting value %llu:\n", i);

        unsigned long long steps = collatz(i);

        printf("Number of steps = %llu\n", steps);

        if (steps > maximumSteps) {
            maximumSteps = steps;
            maximumStart = i;
        }

        // Prevent unsigned overflow in loop
        if (i == b)
            break;
    }

    printf("\n--------------------------------\n");

    printf("Starting value with maximum steps = %llu\n",
           maximumStart);

    printf("Maximum steps = %llu\n", maximumSteps);

    return 0;
}