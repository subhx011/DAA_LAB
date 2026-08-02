#include <stdio.h>
#include <math.h>

int main()
{
    FILE *fp;

    fp = fopen("graph.csv", "w");

    fprintf(fp, "n,1/n,log2n,12sqrtn,50sqrtn,n^0.51,2^32*n,nlog2n,n^2-324,100n^2+6n,2n^3,n^(log2n)\n");

    for(int n = 2; n <= 100; n++)
    {
        double f1 = 1.0 / n;
        double f2 = log2(n);
        double f3 = 12 * sqrt(n);
        double f4 = 50 * sqrt(n);
        double f5 = pow(n, 0.51);
        double f6 = pow(2,32) * n;
        double f7 = n * log2(n);
        double f8 = n * n - 324;
        double f9 = 100 * n * n + 6 * n;
        double f10 = 2 * pow(n,3);
        double f11 = pow(n, log2(n));

        fprintf(fp,
        "%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
        n,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11);
    }

    fclose(fp);

    printf("Data saved in graph.csv\n");

    return 0;
}