#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {  // 스택과 링크 구조체 동시 선언
    int data;
    struct StackNode* link;
} StackNode;

StackNode* createStack(StackNode** top) {                  // 스택 생성 및 초기화 함수
    (*top) = NULL;                                         // 포인터 탑에 NULL 저장
    StackNode* S = (StackNode*)malloc(sizeof(StackNode));  // StackNode 동적 메모리 선언
    S->link = NULL;                                        // S의 링크에 NULL 저장
    return S;                                              // S를 반환
}

int isEmptyStack(StackNode** top) {  // 스택이 비어있을 경우
    return ((*top)->link == NULL);   // 탑포인터의 링크값이 NULL일 때,
}

StackNode* push(StackNode** top, int item) {                  // 스택에 값을 입력하는 함수
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));  // 임시로 저장 할 temp 동적 메모리 선언
    temp->data = item;                                        // temp의 data에 item 저장
    if (!temp)                                                // temp가 정상적으로 선언되지 않았을 경우
        exit(1);
    if (isEmptyStack(top)) {                // stack이 비어있을 때,
        (*top)->link = temp;                // top의 link를 temp에 연결 (아무것도 없는 상태의 top포인터에 첫노드를 연결)
        temp->link = NULL;                  // 첫 스택이므로 다음 링크는 NULL
        printf("PUSH : %d\n", temp->data);  // push 값 출력
    } else {                                // stack에 값이 있으나, 비어있지는 않은 경우
        temp->link = (*top);                // temp의 link를 top포인터에 연결
        (*top) = temp;                      // top포인터에 temp저장
        printf("PUSH : %d\n", temp->data);
    }
    return *top;
}

void pop(StackNode** top) {  // 스택 내의 값을 꺼내는 함수
    StackNode* temp = NULL;  // 임시로 저장 할 temp 선언
    if (isEmptyStack(top))   // 스택이 비어있을 경우
        printf("스택 공백 에러\n");
    else {
        temp = (*top);                     // temp에 top포인터 값 저장 (최상단 데이터 부터 꺼내와야 하기 때문에 top이 가르키는 값을 저장)
        printf("POP : %d\n", temp->data);  // pop값 출력
        (*top) = temp->link;               // top포인터에 temp의 링크를 연결 (출력 한 뒤, 다음 스택값을 top으로 지정하기 위함)
        free(temp);                        // 임시로 사용했던 temp 메모리 해제를 통한 삭제
    }
}

void peek(StackNode** top) {  // stack의 최상단 데이터를 읽는 함수
    StackNode* temp = NULL;
    if (isEmptyStack(top))
        printf("스택 공백 에러\n");
    else {
        temp = (*top);
        printf("peek : %d\n", temp->data);
    }
}

void printStack(StackNode** top) {  // 전체 스택의 데이터를 출력해주는 함수
    int n = 0;
    StackNode* p = (*top);  // 임시 노드 p 선언
    if (isEmptyStack(top))  // 스택이 비어있을 경우
        printf("스택이 비어 있습니다. \n");
    else {  // 스택에 값이 있을 경우
        while (p->link != NULL) {
            printf("[%d] -> ", p->data);
            p = p->link;
        }
        printf("\n");
    }
}

void deleteStack(StackNode** top) {  // 전체 스택을 삭제하는 함수
    printf("delete Stack\n");
    while (!isEmptyStack(top)) {  // 스택 내에 값이 남아있을 경우
        StackNode* temp = NULL;   // 임시노드 선 후 top연결
        temp = (*top);
        (*top) = temp->link;
        free(temp);
    }
    free(*top);
}

int main(int argc, char* argv[]) {
    StackNode* top;
    top = createStack(&top);

    for (int i = 0; i < 10; i++)
        push(&top, i);

    printStack(&top);
    peek(&top);

    for (int i = 0; i < 10; i++)
        pop(&top);

    deleteStack(&top);

    return 0;
}