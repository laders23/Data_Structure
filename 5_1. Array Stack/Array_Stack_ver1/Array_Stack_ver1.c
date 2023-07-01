#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100;

typedef int element; 
typedef struct {
    int top; //스택 최상단
    int capacity;  //현재크기
    int* array; //스택을 저장할 배열
} ArrayStack; //스택 구조체 선언

ArrayStack* createStack() { //스택을 생성하는 함수
    ArrayStack* S = malloc(sizeof(ArrayStack)); //동적배열을 통해 S라는 이름의 구조체 생성
    int stack_size = 0; //스택 사이즈 지정 변수 선언 및 초기화

    if (!S) //정상적으로 동적할당이 되지 않았을 경우
        return NULL; 
    printf("스택의 사이즈를 입력해 주세요 : "); 
    scanf("%d", &stack_size);
    S->capacity = stack_size; //스택의 현재크기를 입력받은 만큼 지정
    S->top = -1; //아무것도 없는 상태 = -1
    S->array = malloc(S->capacity * sizeof(int)); //동적 배열 할당 (사이즈는 입력받은 stack_size만큼)
    if (!S->array) 
        return 0;

    return S;
}
int peak(ArrayStack* mys) { //peak 수행 함수
    printf("peak : %d\n", mys->array[mys->top]); //스택 최상단의 데이터 출력
    return mys->top;
}

int is_Full(ArrayStack* mys) { //스택이 가득 찼을 때,
    if (mys->top == (mys->capacity) - 1) //top의 값과 전체 크기에서 -1한 값이 같을 경우 0 반환, 스택이 가득 찼다는 뜻
        return 0;
    else
        return 1;
}

int is_Empty(ArrayStack* mys) { //스택이 비어있을 때,
    if (mys->top < 0) //top의 값이 0보다 작을 때, 0을 반환
        return 0;
    else
        return 1;
}

ArrayStack* push(ArrayStack* mys, element item) { //스택에 새로운 데이터를 Push 하는 함수
    if (is_Full(mys) == 0) { //is_Full 함수의 반환 값이 0일 경우 스택이 가득 찼다는 뜻이므로 에러 출력
        fprintf(stderr, "스택 포화 에러\n");
        return mys;
    } else { //가득 차지 않았을 경우 push 수행
        ++(mys->top); //top의 값을 먼저 1 올려준 뒤,
        mys->array[mys->top] = item; //array의 index값을 스택의 top으로 두고, item 데이터 저장
        printf("%d\n", mys->array[mys->top]); //출력
        return mys;
    }
}

ArrayStack* pop(ArrayStack* mys) { //스택의 최상단 데이터를 꺼내는 함수
    if (is_Empty(mys) == 0) { //is_Empty 함수의 반환값이 0일 경우, 스택이 비어있다는 뜻으로 에러 출력
        fprintf(stderr, "스택의 데이터가 없습니다!\n");
        return 0;
    } else { //비어있지 않을 경우 선출력, 후 1 빼기
        printf("%d\n", mys->array[mys->top]); //출력
        --(mys->top); //top값을 -1해줌
        return mys;
    }
}

int main(int argc, char* argv[]) {
    ArrayStack* mys;
    mys = createStack();

    printf("=======Push=======\n");
    for (int i = 0; i < 5; i++)
        push(mys, i);

    peak(mys);

    printf("=======Pop=======\n");
    for (int j = 0; j < 5; j++)
        pop(mys);

    return 0;
}