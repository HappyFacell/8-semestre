#include <stdio.h>
#include <math.h>

int main()
{
    unsigned int n = 151;
    printf("%d\n", n);
    n = n << 24;
    printf("%d\n", n);
    n = n >> 24;
    printf("%d\n", n);
}