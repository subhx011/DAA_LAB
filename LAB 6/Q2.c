#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 20

/* Matrix Addition */
void addMatrix(int A[MAX][MAX], int B[MAX][MAX],
               int C[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

/* Matrix Multiplication */
void multiplyMatrix(int A[MAX][MAX], int B[MAX][MAX],
                    int C[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/* Check Zero Matrix */
int isZeroMatrix(int A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (A[i][j] != 0)
                return 0;
        }
    }

    return 1;
}

/* Check Symmetric Matrix */
int isSymmetric(int A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (A[i][j] != A[j][i])
                return 0;
        }
    }

    return 1;
}

/* Determinant using Gaussian elimination */
double determinant(double A[MAX][MAX], int n)
{
    double det = 1.0;

    for (int i = 0; i < n; i++)
    {
        int pivot = i;

        /* Find pivot */
        for (int j = i + 1; j < n; j++)
        {
            if (fabs(A[j][i]) > fabs(A[pivot][i]))
                pivot = j;
        }

        /* Singular matrix */
        if (fabs(A[pivot][i]) < 1e-9)
            return 0;

        /* Swap rows */
        if (pivot != i)
        {
            for (int j = 0; j < n; j++)
            {
                double temp = A[i][j];
                A[i][j] = A[pivot][j];
                A[pivot][j] = temp;
            }

            det = -det;
        }

        det *= A[i][i];

        /* Eliminate below pivot */
        for (int j = i + 1; j < n; j++)
        {
            double factor = A[j][i] / A[i][i];

            for (int k = i; k < n; k++)
            {
                A[j][k] -= factor * A[i][k];
            }
        }
    }

    return det;
}

/* In-place transpose */
void transpose(int A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

/* Display Matrix */
void display(int A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", A[i][j]);

        printf("\n");
    }
}

int main()
{
    int n;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

    printf("Enter order of matrix: ");
    scanf("%d", &n);

    printf("\nEnter Matrix A:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    }

    printf("\nEnter Matrix B:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);
    }

    /* Addition */
    addMatrix(A, B, C, n);

    printf("\nA + B:\n");
    display(C, n);

    /* Multiplication */
    multiplyMatrix(A, B, C, n);

    printf("\nA x B:\n");
    display(C, n);

    /* Zero matrix */
    if (isZeroMatrix(A, n))
        printf("\nA is a zero matrix.\n");
    else
        printf("\nA is not a zero matrix.\n");

    /* Symmetric */
    if (isSymmetric(A, n))
        printf("A is symmetric.\n");
    else
        printf("A is not symmetric.\n");

    /* Determinant */
    double D[MAX][MAX];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            D[i][j] = A[i][j];

    printf("Determinant of A = %.2lf\n",
           determinant(D, n));

    /* Transpose */
    transpose(A, n);

    printf("\nTranspose of A:\n");
    display(A, n);

    return 0;
}