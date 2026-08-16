#include <stdio.h>

#define MAX 64

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

/* Add two matrices */
void add(int X[][MAX], int Y[][MAX], int R[][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            R[i][j] = X[i][j] + Y[i][j];
        }
    }
}

/* Subtract two matrices */
void subtract(int X[][MAX], int Y[][MAX], int R[][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            R[i][j] = X[i][j] - Y[i][j];
        }
    }
}

/*
   Multiply two special-pattern matrices

   A = A1 A2
       A2 A1

   B = B1 B2
       B2 B1
*/
void multiply(int A[][MAX], int B[][MAX], int C[][MAX], int n)
{
    int i, j;

    /* Base case */
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int A1[MAX][MAX], A2[MAX][MAX];
    int B1[MAX][MAX], B2[MAX][MAX];

    int P[MAX][MAX], Q[MAX][MAX];
    int R[MAX][MAX], S[MAX][MAX];

    int temp1[MAX][MAX], temp2[MAX][MAX];

    /*
       Extract the four blocks.

       A = A1 A2
           A2 A1

       B = B1 B2
           B2 B1
    */

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < k; j++)
        {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];

            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + k];
        }
    }

    /*
       P = (A1 + A2)(B1 + B2)
    */

    add(A1, A2, temp1, k);
    add(B1, B2, temp2, k);

    multiply(temp1, temp2, P, k);

    /*
       Q = (A1 - A2)(B1 - B2)
    */

    subtract(A1, A2, temp1, k);
    subtract(B1, B2, temp2, k);

    multiply(temp1, temp2, Q, k);

    /*
       R = (P + Q) / 2
       S = (P - Q) / 2
    */

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < k; j++)
        {
            R[i][j] = (P[i][j] + Q[i][j]) / 2;
            S[i][j] = (P[i][j] - Q[i][j]) / 2;
        }
    }

    /*
       Construct result:

       C = R S
           S R
    */

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < k; j++)
        {
            C[i][j] = R[i][j];
            C[i][j + k] = S[i][j];

            C[i + k][j] = S[i][j];
            C[i + k][j + k] = R[i][j];
        }
    }
}

/* Display matrix */
void display(int M[][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int n;
    int i, j;

    printf("Enter size of matrix (power of 2): ");
    scanf("%d", &n);

    printf("Enter elements of first matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of second matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }

    multiply(A, B, C, n);

    printf("\nResultant Matrix:\n");
    display(C, n);

    return 0;
}