#include <stdio.h>
#include <limits.h>

#define MAX 100

int main()
{
    int N;

    printf("Enter N: ");
    scanf("%d", &N);

    int arr[N];

    printf("Enter %d dimensions:\n", N);

    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);

    long long dp[MAX][MAX];

    /* Cost of multiplying one matrix = 0 */
    for (int i = 1; i < N; i++)
        dp[i][i] = 0;

    /*
       chainLength represents the number
       of matrices in the chain
    */
    for (int chainLength = 2;
         chainLength <= N - 1;
         chainLength++)
    {
        for (int i = 1;
             i <= N - chainLength;
             i++)
        {
            int j = i + chainLength - 1;

            dp[i][j] = LLONG_MAX;

            /*
               Try every possible split
            */
            for (int k = i; k < j; k++)
            {
                long long cost =
                    dp[i][k]
                    + dp[k + 1][j]
                    + (long long)arr[i - 1]
                    * arr[k]
                    * arr[j];

                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                }
            }
        }
    }

    printf("\nMinimum number of scalar multiplications = %lld\n",
           dp[1][N - 1]);

    return 0;
}