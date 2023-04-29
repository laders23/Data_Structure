#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Recursion

double power(double x, int n)
{
    if (n == 0)
        return 1;
    else if (n % 2 == 0)
        return power(x * x, n / 2);
    else
        return x * power(x * x, (n - 1) / 2);
}

int main(int argc, char *argv[])
{
    int n = 0;
    double x = 0;

    printf("거듭 제곱 할 밑을 입력하세요 : ");
    scanf("%lf", &x);
    printf("거듭 제곱 할 지수를 입력하세요 : ");
    scanf("%d", &n);

    clock_t start = clock();
    printf("%.0lf^%d = %.0lf\n", x, n, power(x, n));
    clock_t end = clock();

    printf("실행시간 : %lf \n", (double)(end - start) / (double)CLOCKS_PER_SEC);

    return 0;
}