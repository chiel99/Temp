#include <stdio.h>

#define BIT_GET(x, n) (x & (1 << n))
#define BIT_SET(x, n) (x | (1 << n))
#define BIT_CLR(x, n) (x & ~(1 << n))
#define BIT_REV(x, n) (x ^ (1 << n))

void print_int_by_bit(int x)
{
    int i;
    for (i = sizeof(int)*8 -1 ; i >= 0 ; i--) {
        printf("%d", BIT_GET(x,i) ? 1 : 0);
        if (i % 8 == 0)
            printf(" ");
    }
    printf("\n");
}

int main()
{
    int i,n;
    scanf("%d %d", &i, &n);

    printf("Input: ");
    print_int_by_bit(i);
    printf("GET  : ");
    print_int_by_bit(BIT_GET(i,n));
    printf("SET  : ");
    print_int_by_bit(BIT_SET(i,n));
    printf("CLR  : ");
    print_int_by_bit(BIT_CLR(i,n));
    printf("REV  : ");
    print_int_by_bit(BIT_REV(i,n));

    return 0;
}
