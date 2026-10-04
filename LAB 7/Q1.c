#include <stdio.h> 
int main() 
{ 
    int n, i; printf("Enter number of rows: "); 
    scanf("%d", &n); 
    printf("Minimum number of moves = %d\n", n); 
    printf("Move coins as follows:\n"); 
    for (i = 1; i <= n; i++) 
    { 
        printf("Move coin %d to the corresponding inverted position.\n", i); 
    } 
    return 0; 
}