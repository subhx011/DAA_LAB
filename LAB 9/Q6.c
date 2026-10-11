
#include <stdio.h>
#include <string.h>

#define MAX 1000
#define SIZE 256

int main(void) {
    char s[MAX + 1], result[MAX + 1];
    int freq[SIZE] = {0};
    int last[SIZE];
    int n, k, i, pos;

    printf("Enter string: ");
    scanf("%1000s", s);

    printf("Enter K: ");
    scanf("%d", &k);

    if (k < 0) {
        printf("Invalid K\n");
        return 1;
    }

    n = strlen(s);

    if (k <= 1) {
        printf("Reorganized string: %s\n", s);
        return 0;
    }

    for (i = 0; i < SIZE; i++)
        last[i] = -k;

    for (i = 0; i < n; i++)
        freq[(unsigned char)s[i]]++;

    for (pos = 0; pos < n; pos++) {
        int best = -1;

        /* Select the most frequent available character */
        for (i = 0; i < SIZE; i++) {
            if (freq[i] > 0 && pos - last[i] >= k) {
                if (best == -1 || freq[i] > freq[best])
                    best = i;
            }
        }

        if (best == -1) {
            printf("Reorganization impossible by this greedy method\n");
            return 0;
        }

        result[pos] = (char)best;
        freq[best]--;
        last[best] = pos;
    }

    result[n] = '\0';

    printf("Reorganized string: %s\n", result);

    return 0;
}
