
#include <stdio.h>
#include <string.h>

#define N 100
#define LEN 1000

int main(void) {
    int n, i, j, k;
    char s[N][LEN];
    int active[N];

    printf("Enter number of strings: ");
    scanf("%d", &n);

    if (n < 1 || n >= N) {
        printf("Invalid number of strings\n");
        return 1;
    }

    printf("Enter the strings:\n");
    for (i = 0; i < n; i++) {
        scanf("%999s", s[i]);
        active[i] = 1;
    }

    /* Remove strings contained in other strings */
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j && active[i] && active[j]) {
                if (strstr(s[j], s[i]) != NULL) {
                    if (strlen(s[j]) > strlen(s[i]) || j < i)
                        active[i] = 0;
                }
            }
        }
    }

    /* Greedily merge strings with maximum overlap */
    while (1) {
        int bestI = -1, bestJ = -1, best = -1;

        for (i = 0; i < n; i++) {
            if (!active[i]) continue;

            for (j = 0; j < n; j++) {
                if (i == j || !active[j]) continue;

                int len1 = strlen(s[i]);
                int len2 = strlen(s[j]);
                int overlap = 0;

                for (k = 1; k <= len1 && k <= len2; k++) {
                    if (strncmp(s[i] + len1 - k, s[j], k) == 0)
                        overlap = k;
                }

                if (overlap > best) {
                    best = overlap;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        if (bestI == -1)
            break;

        if (strlen(s[bestI]) + strlen(s[bestJ]) - best >= LEN) {
            printf("Result too long for the array size\n");
            return 1;
        }

        strcat(s[bestI], s[bestJ] + best);
        active[bestJ] = 0;
    }

    printf("Shortest superstring (greedy result):\n");

    for (i = 0; i < n; i++) {
        if (active[i]) {
            printf("%s\n", s[i]);
            break;
        }
    }

    return 0;
}
