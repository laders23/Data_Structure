 #include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 5

typedef struct { //스택 구조체 생성
    int top;
    int capacity;
    int* array;
} arrayStack;

arrayStack* createStack() { //구조체 생성 함수
    arrayStack* S = malloc(sizeof(arrayStack));
    if (!S) return NULL; //정상적으로 동적할당이 되지 않은 경우
    S->top = -1; //top을 -1로 지정, 
    S->capacity = MAX_STACK_SIZE; //capacity는 define 해놓은 5로 설정 (초기 설정)
    S->array = malloc(S->capacity * sizeof(int)); //malloc 을 통해 capacity크기 만큼의 배열 생성
    if (!S->array) return NULL; //정상적으로 동적할당이 되지 않은 경우
    return S;
}

arrayStack* Dynamic_array(arrayStack* S) { //스택이 가득 찼을 때, capacity를 늘려줄 동적배열 함수
    S->capacity *= 2; //capacity의 값을 *2한 만큼 저장
    S->array = (int*)realloc(S->array, S->capacity * sizeof(int*)); //realloc을 통해 재설정
    printf("Stack is Full, realloc array capacity : %d \n", S->capacity);
    return S;
}

int isFull(arrayStack* S) { //스택이 가득 찼을 때,
    return (S->top == S->capacity - 1); //top의 값과 전체 크기에서 -1한 값이 같을 경우 0을 반환, 스택이 가득 찼다는 뜻
}

void push(arrayStack* S, int data) { //스택에 새로운 데이터를 push 해주는 함수
    if (isFull(S)) { //스택이 가득 찼을 경우
        Dynamic_array(S); //재할당을 해줄 Dynamic_array 함수 호출
        S->array[++(S->top)] = data; //Dynamic_array 함수 탈출 후에 data입력을 위해 추가
    } else
        S->array[++(S->top)] = data; //스택에 빈자리가 있을 경우 data입력
}

int isEmpty(arrayStack* S) { //스택이 비어있을 때,
    return (S->top == -1); //top의 값이 -1일 때, 0을 반환
}

int pop(arrayStack* S) { //스택의 최상단 데이터를 꺼내는 함수
    if (isEmpty(S)) { //스택이 비어있는지 확인하는 if문
        printf("underflow\n"); //isEmpty함수의 반환값이 0일 경우, underflow 출력
        exit(1);
    } else {
        return S->array[S->top--]; //스택에 데이터가 있을 경우 top--를 통해 데이터를 먼저 꺼낸 후에 top값을 줄여줌
    }
}

void deleteStack(arrayStack* S) { //스택을 삭제하는 함수
    if (S) {
        free(S->array); //free를 통한 메모리 해제
    }
    free(S);
}

int main() {
    arrayStack* myS;
    myS = createStack();

    int i;
    for (i = 0; i < 10; i++) {
        push(myS, i);
        printf("push data : %d / index : (%d) \n", i, myS->top);
    }

    int j, tmp;
    for (j = 0; j < 10; j++) {
        tmp = pop(myS);
        printf("pop data : %d / index (%d) \n", tmp,myS->top);
    }
    
    deleteStack(myS);
    return 0;
}
