#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackNode {  //스택과 링크 구조체 동시 선언
    char data;
    int capacity;
    struct StackNode* link;
} StackNode;

StackNode* createStack(StackNode** top) {                     //스택 생성 및 초기화 함수
    (*top) = NULL;                                            //포인터 탑에 NULL 저장
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));  // StackNode 에 동적 메모리 선언
    temp->capacity = 5;                                       // capacity를 5로 지정
    temp->link = NULL;                                        // temp의 link에 NULL저장
    return temp;                                              // temp반환
}

int isfull(StackNode** top) {  // 스택의 포화여부를 반환하는 함수, 이중포인터 사용
    int n = 0;                 // capacity 값을 비교해 줄 변수 선언
    StackNode* p = (*top);

    while (p->link != NULL) {  // p의 link가 NULL이 아닐 때, 반복 링크를 타고 capacity의 끝까지 이동
        p = p->link;
        n++;
    }
    return (n == p->capacity);  //이중 포인터를 사용했기 때문에, capacity -1이 아닌 capacity 비교
}

int isEmptyStack(StackNode** top) {  //스택이 비어있을 경우
    return ((*top)->link == NULL);   //탑포인터의 링크값이 NULL일 때,
}

StackNode* push(StackNode** top, char ch) {                   //스택에 값을 입력하는 함수
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));  //임시로 저장 할 temp 동적 메모리 선언
    temp->capacity = 5;

    if (!temp)  // temp가 정상적으로 선언되지 않았을 경우
        exit(1);
    if (isEmptyStack(top)) {  // stack이 비어있을 때,
        temp->data = ch;      // temp의 data에 item 저장 // top의 link를 temp에 연결 (아무것도 없는 상태의 top포인터에 첫노드를 연결)
        temp->link = (*top);  //첫 스택이므로 다음 링크는 NULL
        (*top) = temp;
    } else if (isfull((top))) {  //스택이 가득 찬 경우
        printf("스택 오버플로우 \n");
    } else {                  // stack에 값이 있으나, 비어있지는 않은 경우
        temp->data = ch;      // temp의 data에 item 저장
        temp->link = (*top);  // temp의 link를 top포인터에 연결
        (*top) = temp;        // top포인터에 temp저장
    }
    return *top;
}

char pop(StackNode** top) {  //스택 내의 값을 꺼내는 함수
    char output;
    StackNode* temp = NULL;  //임시로 저장 할 temp 선언
    if (isEmptyStack(top))   //스택이 비어있을 경우
        printf("스택 공백 에러\n");
    else {
        temp = (*top);  // temp에 top포인터 값 저장 (최상단 데이터 부터 꺼내와야 하기 때문에 top이 가르키는 값을 저장)
        output = temp->data;
        (*top) = temp->link;  // top포인터에 temp의 링크를 연결 (출력 한 뒤, 다음 스택값을 top으로 지정하기 위함)
        free(temp);           //임시로 사용했던 temp 메모리 해제를 통한 삭제
    }

    return output;
}

void deleteStack(StackNode** top) {  //전체 스택을 삭제하는 함수
    printf("delete Stack\n");
    while (!isEmptyStack(top)) {  //스택 내에 값이 남아있을 경우
        StackNode* temp = NULL;   //임시노드 선 후 top연결
        temp = (*top);            // temp에 포인터탑을 저장하고,
        (*top) = temp->link;      //포인터 탑에 temp의 link값을 저장 함으로서, 뒤로 이동하면서 하나씩 삭제
        free(temp);
    }
}

void check_matching(StackNode** top, char* input) {           //수식을 확인하는 함수
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));  // temp 동적 메모리 할당
    char ch;                                                  //임시 저장용 ch 선언
    int i = 0;                                                // index값 반복을 위한 i 선언
    int count = 0;                                            //정상 수식인지 확인하기 위해 사용할 변수 count 선언

    while (input[i] != '\0') {  // input 값이 끝을 만나기 전까지,
        ch = input[i++];        // ch에 input값을 저장
        switch (ch) {
            case '(':
            case '{':
            case '[':
                push(top, ch);  //위 3가지 케이스의 경우 push 함수 호출
                count++;
                break;

            case ')':
                if (isEmptyStack(top)) {
                    printf("open bracket missing \n");//닫는 괄호가 있지만 여는 괄호가 스택에 없을 경우
                    count--;
                    break;
                } else if (pop(top) != '(') { //괄호의 짝이 맞지 않는 경우
                    printf("wrong pair \n");
                    exit(1);
                } else
                    count--; //위의 조건들에 해당사항이 없을 경우 해당 과정까지는 정상임으로 count--
                break;

            case '}':
                if (isEmptyStack(top)) {
                    printf("open bracket missing \n");
                    count--;
                    break;
                } else if (pop(top) != '{') {
                    printf("wrong pair \n");
                    exit(1);
                } else
                    count--;
                break;
            case ']':
                if (isEmptyStack(top)) {
                    printf("open bracket missing \n");
                    count--;
                    break;
                } else if (pop(top) != '[') {
                    printf("wrong pair \n");
                    exit(1);
                } else
                    count--;
                break;

            default:
                break;
        }
    }
    if (!isEmptyStack(top)) { //여는 괄호는 있는데 닫는 괄호가 없는 경우 (스택에 아직 값이 남아있는 경우)
        printf("close bracket missing \n");
        return;
    } else if (count == 0) //count 값이 0 일 경우 이상이 없음
        printf("이상 없음\n");
    return;
}

int main(int argc, char* argv[]) {
    StackNode* top;
    top = createStack(&top);
    char* input = (char*)malloc(sizeof(char));

    for (int i = 0; i < 4; i++) {
        printf("비교 할 수식을 입력해 주세요 : ");
        scanf("%s", input);
        check_matching(&top, input);
    }

    deleteStack(&top);

    return 0;
}