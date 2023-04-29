// Iteration

#include <stdio.h> //printf, scanf와 같은 기본 입출력을 받기위해 선언
#include <time.h>  //clock 함수 사용을 위해 선언

double power(double x, int n) //거듭제곱을 실행 할 함수 power 선언 x = 밑, n = 지수
{
    double result = 1.0; // return 해줄 result값 선언, n이 0일 때, 1을 반환해야 함으로 1로 초기화

    if (n == 0)
        return result; //지수가 0일 경우, 모든 값은 1로 통일되기 때문에 n = 0일 경우 1을 리턴.

    else
    {
        for (int i = 0; i < n; i++) // iteration 방식에서는 짝수든 홀수든 반복적으로 곱해주는 방식으로 계산하기 때문에 구분없이 지수값만큼 밑을 계속해서 곱한 값을 result에 입력
            result *= x;
        return result; // for 구문이 끝난 뒤 result값을 return
    }
}

int main(int argc, char *argv[])
{
    int n = 0;    //지수
    double x = 0; //밑

    printf("거듭 제곱 할 밑을 입력하세요 : ");   // 거듭제곱 밑 입력 UI
    scanf("%lf", &x);                            // scanf로 x값 입력
    printf("거듭 제곱 할 지수를 입력하세요 : "); //거듭제곱 지수 입력 UI
    scanf("%d", &n);                             // scanf로 n값 입력

    clock_t start = clock();                         // time.h 헤더 파일을 이용해 clock_t 함수 사용, 시작 시간 구함.
    printf("%.0lf^%d = %.0lf\n", x, n, power(x, n)); //함수 실행과 동시에 끝난 뒤 결과값 출력
    clock_t end = clock();                           // time.h 헤더 파일을 이용해 clock_t 함수 사용, 종료 시간 구함.

    printf("실행시간 : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC); // time.h 헤더 파일을 이용해 clock_t 함수 사용, 종료시간 - 시작시간 으로 실행시간을 구함.

    return 0; // return 0로 프로그램 종료
}