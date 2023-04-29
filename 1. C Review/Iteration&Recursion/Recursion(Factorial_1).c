// Recursion

#include <stdio.h>
#include <time.h>

unsigned long long Factorial(int n) {
    printf("factorial(%d)\n",n);

    if (n <= 1) // Base code
        return 1; //n이 0이거나 1일 경우 1으로 값 고정.
    else 
        return (n * Factorial(n - 1)); //n이 1보다 클 떄, 재귀함수돌려줄 else 지정.
}
int main(int argc, char *argv[]){
    int N = 0; //팩토리얼 돌릴 자연수 값

    printf("N = "); //자연수 값 입력 UI
    scanf("%d", &N); // 팩토리얼 값 scanf로 받음.
    
    clock_t start = clock(); // time.h 헤더 파일, clock 함수를 이용해서 재귀함수 시작 시간 시작.
    printf("%d! : %lld \n",N,Factorial(N)); //펙토리얼 함수 실행
    clock_t end = clock(); //함수 끝날 때, 시간계산
    printf("소요시간 : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC); //소요시간 출력을 위해서 end - start 값을 per_sec 으로 나누어서 ms 단위로 출력.
    
    return 0; //코드 종료.
}