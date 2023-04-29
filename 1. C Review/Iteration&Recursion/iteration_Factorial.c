//iteration 

#include <stdio.h>
#include <time.h>

unsigned long long Factorial(int n)
{
    unsigned long long result = 1; //결과값을 넣어 줄 result 선언.
    for (; n >= 1; n--){ //for문 사용으로 n이 1보다 크거나 같을 때, 계속해서 n값을 result에 곱해줌.
        printf("Factorial(%d) \n",n); //과정을 나타내는 Factorial 출력.
        result *= n;
    }

    return result;
}

int main(int argc, char *argv[])
{
    int N = 0;

    printf("N = "); //자연수 값 입력 UI
    scanf("%d", &N); // 팩토리얼 값 scanf로 받음.

    clock_t start = clock(); // time.h 헤더 파일, clock 함수를 이용해서 재귀함수 시작 시간 시작.
    printf("%d! : %lld \n", N, Factorial(N)); //펙토리얼 함수 실행
    clock_t end = clock(); //함수 끝날 때, 시간계산

    printf("소요시간 : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC); //소요시간 출력을 위해서 end - start 값을 per_sec 으로 나누어서 ms 단위로 출력.

    return 0;
}