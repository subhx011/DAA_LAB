#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct
{
    double real;
    double imag;
} Complex;


/* Complex addition */
Complex add(Complex a, Complex b)
{
    Complex c;

    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;

    return c;
}


/* Complex subtraction */
Complex subtract(Complex a, Complex b)
{
    Complex c;

    c.real = a.real - b.real;
    c.imag = a.imag - b.imag;

    return c;
}


/* Complex multiplication */
Complex multiply(Complex a, Complex b)
{
    Complex c;

    c.real = a.real * b.real - a.imag * b.imag;
    c.imag = a.real * b.imag + a.imag * b.real;

    return c;
}


/*
   Recursive FFT

   invert = 0  -> FFT
   invert = 1  -> Inverse FFT
*/
void FFT(Complex *a, int n, int invert)
{
    if (n == 1)
        return;

    /* Divide */
    Complex *even = malloc((n / 2) * sizeof(Complex));
    Complex *odd  = malloc((n / 2) * sizeof(Complex));

    for (int i = 0; i < n / 2; i++)
    {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }

    /* Conquer */
    FFT(even, n / 2, invert);
    FFT(odd, n / 2, invert);

    double angle = 2 * PI / n;

    if (!invert)
        angle = -angle;

    Complex w;
    w.real = 1.0;
    w.imag = 0.0;

    Complex wn;
    wn.real = cos(angle);
    wn.imag = sin(angle);

    /* Combine */
    for (int k = 0; k < n / 2; k++)
    {
        Complex t = multiply(w, odd[k]);

        a[k] = add(even[k], t);
        a[k + n / 2] = subtract(even[k], t);

        w = multiply(w, wn);
    }

    free(even);
    free(odd);
}


/* Convolution using FFT */
void convolution(double A[], int m,
                 double B[], int n,
                 double C[])
{
    int N = 1;

    /*
       Find power of 2 such that
       N >= m + n - 1
    */
    while (N < m + n - 1)
        N *= 2;

    Complex *FA = calloc(N, sizeof(Complex));
    Complex *FB = calloc(N, sizeof(Complex));

    /* Copy A */
    for (int i = 0; i < m; i++)
    {
        FA[i].real = A[i];
        FA[i].imag = 0;
    }

    /* Copy B */
    for (int i = 0; i < n; i++)
    {
        FB[i].real = B[i];
        FB[i].imag = 0;
    }

    /* FFT(A) and FFT(B) */
    FFT(FA, N, 0);
    FFT(FB, N, 0);

    /* Point-wise multiplication */
    for (int i = 0; i < N; i++)
        FA[i] = multiply(FA[i], FB[i]);

    /* Inverse FFT */
    FFT(FA, N, 1);

    /* Store result */
    for (int i = 0; i < m + n - 1; i++)
        C[i] = FA[i].real / N;

    free(FA);
    free(FB);
}


/* Main function */
int main()
{
    int m, n;

    printf("Enter size of vector A: ");
    scanf("%d", &m);

    printf("Enter size of vector B: ");
    scanf("%d", &n);

    if (n < m)
    {
        printf("Error: n must be greater than or equal to m.\n");
        return 0;
    }

    double *A = malloc(m * sizeof(double));
    double *B = malloc(n * sizeof(double));
    double *C = malloc((m + n - 1) * sizeof(double));

    printf("\nEnter elements of A:\n");

    for (int i = 0; i < m; i++)
        scanf("%lf", &A[i]);

    printf("\nEnter elements of B:\n");

    for (int i = 0; i < n; i++)
        scanf("%lf", &B[i]);

    convolution(A, m, B, n, C);

    printf("\nConvolution of A and B:\n");

    for (int i = 0; i < m + n - 1; i++)
        printf("%.2lf ", C[i]);

    printf("\n");

    free(A);
    free(B);
    free(C);

    return 0;
}