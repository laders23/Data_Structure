#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct StackNode {  // linked list 구조체 선언
    char data;
    int capacity;
    struct StackNode* link;
} StackNode;

int prec(char op) {  // 연산자 순위를 결정해줄 prec함수 선언
    switch (op) {    // op에 저장된 문자에 따라 우선순위 반환
        case '(':
        case ')':
            return 0;  // 괄호 = 0순위
        case '+':
        case '-':
            return 1;  // +- 1순위
        case '*':
        case '/':
            return 2;  // */ 2순위
        default:
            return -1;
    }
}

StackNode* init_Stack(StackNode** top) {                   // 스택 초기화 함수
    (*top) = NULL;                                         // 포인터 탑에 NULL 저장
    StackNode* S = (StackNode*)malloc(sizeof(StackNode));  // S에 동젇메모리 할당
    S->capacity = 10;                                      // 캐페시터값 10으로 저장
    S->link = NULL;                                        // S의 Link 에 NULL 저장
    return S;
}

int isfull(StackNode** top) {  // 스택의 포화여부를 반환하는 함수
    int n = 0;
    StackNode* p = (*top);  // 임시노드 p 에 포인터 top 저장

    while (p->link != NULL) {  // p 의 링크가 NULL일 때 까지 반복
        p = p->link;
        n++;
    }
    return (n == p->capacity);  // n이 p의 capacity와 같을때
}

int is_Empty(StackNode** top) {     // 스택의 공백 여부를 반환하는 함수
    return ((*top)->link == NULL);  // 포인터 top의 링크가 NULL일 때,
}

StackNode* push(StackNode** top, char open) {                 // 스택의 값을 push하는 함수
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));  // 임시노드 temp 선언 후, 동적 메모리 할당
    temp->capacity = 10;                                      // 이중포인터를 이용해서 capacity를 구조체 안에 넣었기 때문에 해당 노드마다 초기화
    temp->data = open;                                        // temp->data 에 open 저장

    if (!temp)  // temp의 동적 메모리가 정상적으로 할당되지 않았을 경우
        exit(1);
    if (is_Empty(top)) {  // 스택이 비어있는 상황에서 push 하는 경우
        temp->link = (*top);
        (*top) = temp;
    } else if (isfull((top))) {  // 스택이 가득찬 상황에서 push 하는 경우
        printf("스택 오버플로우 \n");
    } else {  // 스택에 값이 있으면서 여유공간이 있을 때, push 하는 경우
        temp->link = (*top);
        (*top) = temp;
    }
    return *top;
}

char pop(StackNode** top) {  // 스택의 값을 pop시키는 함수
    StackNode* temp = NULL;  // 임시노드 temp 선언
    char ch;                 // 임시 문자형 ch 선언
    if (is_Empty(top))       // 스택이 비어있는데 pop 하는 경우
        printf("스택 공백 에러\n");
    else {                    // 스택에 값이 있어서 정상적인 pop이 가능한 경우
        temp = (*top);        // temp에 포인터 top 저장
        ch = temp->data;      // ch에 temp->data 저장
        (*top) = temp->link;  // 포인터 top에 temp의 link값을 저장하면서, top을 이동
        free(temp);           // 임시 노드 temp 메모리 해제
    }
    return ch;  // ch 반환
}

char peek(StackNode** top) {  // 스택의 최상단 값을 보는 함수
    StackNode* temp = NULL;   // 임시노드 temp 선언 후 NULL로 초기화
    char ch;                  // 임시 문자형 ch 선언
    if (is_Empty(top))
        printf("스택 공백 에러\n");
    else {
        temp = (*top);
        ch = temp->data;
    }
    return ch;
}

char* infix_to_postfix(char exp[], StackNode** top) {  // infix 형태로 저장된 값을 postfix 형태로 변환하는 함수
    int k = 0;                                         // index로 사용 할 변수 k 선언
    char ch, top_op;                                   // operater와 숫자를 저장할 ch, top_op 선언
    char* postfix = (char*)malloc(sizeof(char));       // postfix에 동적메모리 할당
    printf("infix : %s\n", exp);                       // infix 형태로 저장된 값 출력
    int len = strlen(exp);                             // len에 매개변수 exp의 길이 저장

    for (int i = 0; i < len; i++) {  // len의 값 만큼 반복
        ch = exp[i];                 // ch에 exp 값을 넣은 뒤, switch문에 사용
        switch (ch) {
            case '+':
            case '-':
            case '*':
            case '/':
                while (!is_Empty(top) && (prec(ch) <= prec(peek(top))))  // 연산자가 입력 될 경우, 스택에 값이 있고, 우선순위가 더 빠른경우
                    postfix[k++] = pop(top);                             // postfix 배열에 스택 최상단 값 pop
                push(top, ch);                                           // 반복문을 다 돌고 나면 스택노드에 ch push
                break;
            case '(':           // ch가 여는 괄호일 경우
                push(top, ch);  // 스택노드에 ch값 push
                break;
            case ')':                       // ch가 닫는 괄호일 경우
                top_op = pop(top);          // top_op에 pop된 값(스택 노드 최상단 값) 저장
                while (top_op != '(') {     // 괄호 짝이 안맞을 경우 (괄호가 아직 닫히지 않아 수식이 나오는 경우)
                    postfix[k++] = top_op;  // postfix 배열에 top_op값 저장
                    top_op = pop(top);      // top_op 에 pop값(스택 노드 최상단 값) 저장
                }
                break;

            default:                // 피 연산자를 만난 경우
                postfix[k++] = ch;  // postfix 배열에 ch 값 저장                    
                break;
        }
    }
    while (!is_Empty(top))        // 스택이 빌 때 까지
        postfix[k++] = pop(top);  // postfix배열에 pop 값 저장
    return postfix;               // 함수의 모든 과정이 끝나면 postfix값 반환
}

int eval(char* postfix, StackNode** top) {                       // postfix로 변환된 값을 계산하는 함수
    int op1, op2, value;                                         // 피연산자를 저장할 op1,2 / 계산결과를 저장할 value 선언
    int len = strlen(postfix);                                   // postfix의 길이를 저장할 len 선언 후 길이 저장
    char ch;                                                     // 연산자를 저장해줄 ch 선언
    for (int i = 0; i < len; i++) {                              // postfix의 길이만큼 반복
    // if(postfix[i+1] != '+' && postfix[i+1] != '-' && postfix[i+1] != '*' && postfix[i+1] != '/')
        ch = postfix[i];                                         // ch에 postfix값 저장
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {  // 연산자가 아닌 경우
            value = ch - '0';                                    // char형인 ch값을 value에 저장하기위해서 아스키코드 형식으로 저장
            push(top, value);                                    // value 값을 스택에 push
        } else {
            op2 = pop(top);  // op2에 스택 최상단 값 pop 저장 (op1 와 op2 계산을 위해서 op2먼저 저장)
            op1 = pop(top);  // op1에 스택 최상단 값 pop 저장
            switch (ch) {    // ch가 연산자인지 확인 후, 연산자일 경우 계산 결과값을 스택에 push
                case '*':
                    push(top, op1 * op2);
                    break;
                case '/':
                    push(top, op1 / op2);
                    break;
                case '+':
                    push(top, op1 + op2);
                    break;
                case '-':
                    push(top, op1 - op2);
                    break;
            }
        }
    }
    return pop(top);  // 스택 최상단값을 반환
}

int main(int argc, char* argv[]) {
    StackNode* top;
    char* infx = "(4+9)*8+8";               // infix형태의 값 저장
    char* postfix;                           // postfix 선언
    top = init_Stack(&top);                  // 스택 초기화
    postfix = infix_to_postfix(infx, &top);  // postfix에 함수를 통해 변환된 값 저장
    printf("postfix : %s\n", postfix);       // postfix값 출력
    int result = eval(postfix, &top);        // 계산 결과를 result에 eval함수를 통해 반환된 값 저장
    printf("result : %d\n", result);         // result 출력

    return 0;
}