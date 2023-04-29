#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RECALL 100  // random_read
#define SIZE 10     //기본 설정

typedef struct Stack_Array {
    int top;
    int capacity;
    int* array;
} Stack_Array;

typedef struct StackNode {  //스택과 링크 구조체 동시 선언
    int data;
    struct StackNode* link;
} StackNode;

typedef struct QueueType_Array {
    int front, rear;
    int capacity;
    int* array;
} QueueType_Array;

typedef struct ListNode_Q {  // Linked List로 구현하기 위해, ListNode 구조체 선언
    int data;                //데이터를 저장해줄 변수 선언
    int count;               //배열로 구현한 큐에서의 front,rear값을 받아줄 수 있도록 count 변수 선언
    struct ListNode_Q* link;
} ListNode_Q;

typedef struct {   // Queue 구현을 위한 구조체 선언
    int capacity;  // Queue의 크기를 정해주는 capapcity 선언
    struct ListNode_Q* front;
    struct ListNode_Q* rear;
} LL_Queue;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

int set_size() {
    int size = 0;
    printf("input size : ");
    scanf("%d", &size);
    return size;
}

// ----------------------------------------------구분선-----------------------------------------------

int is_Full_SA(Stack_Array* S) {
    return (S->top == (S->capacity) - 1);
}

int is_Empty_SA(Stack_Array* S) {  //스택이 비어있을 때,
    return (S->top == -1);         // top의 값이 -1일 때, 0을 반환
}

Stack_Array* create_SA() {  //구조체 생성 함수
    Stack_Array* S = malloc(sizeof(Stack_Array));
    if (!S) return NULL;  //정상적으로 동적할당이 되지 않은 경우
    S->top = -1;          // top을 -1로 지정,
    S->capacity = SIZE;
    S->array = malloc(S->capacity * sizeof(int));  // malloc 을 통해 capacity크기 만큼의 배열 생성
    if (!S->array) return NULL;                    //정상적으로 동적할당이 되지 않은 경우
    return S;
}

Stack_Array* Dynamic_array(Stack_Array* S) {                         //스택이 가득 찼을 때, capacity를 늘려줄 동적배열 함수
    S->capacity += 100;                                              // capacity의 값을 *2한 만큼 저장
    S->array = (int*)realloc(S->array, S->capacity * sizeof(int*));  // realloc을 통해 재설정
    return S;
}

void push_SA(Stack_Array* S, int data) {  //스택에 새로운 데이터를 push 해주는 함수
    if (is_Full_SA(S)) {                  //스택이 가득 찼을 경우
        Dynamic_array(S);                 //재할당을 해줄 Dynamic_array 함수 호출
        S->array[++(S->top)] = data;      // Dynamic_array 함수 탈출 후에 data입력을 위해 추가
    } else
        S->array[++(S->top)] = data;  //스택에 빈자리가 있을 경우 data입력
}

void Dynamic_Array_Stack_Random_Access_Read(Stack_Array* S, int size) {
    clock_t start = clock();
    int sum = 0;
    for (int i = 0; i < RECALL; i++) {
        int random_Num = rand() % size;
        sum += S->array[random_Num];
    }
    clock_t end = clock();
    printf("Array sum = %d \n",sum);
    printf("Random_Access_Read_time (Array -> Stack) : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC);
}

void Dynamic_Array_Stack_insertion(Stack_Array* S, int size) {
    clock_t start = clock();
    S = create_SA();
    for (int i = 0; i < size; i++)
        push_SA(S, i);
    clock_t end = clock();
    printf("insertion 실행시간(Array -> Stack) : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC);
    Dynamic_Array_Stack_Random_Access_Read(S, size);
}

// ----------------------------------------------구분선-----------------------------------------------

StackNode* create_LL_S(StackNode** top) {        //스택 생성 및 초기화 함수
    (*top) = NULL;                                         //포인터 탑에 NULL 저장
    StackNode* S = (StackNode*)malloc(sizeof(StackNode));  // StackNode 동적 메모리 선언
    S->link = NULL;                                        // S의 링크에 NULL 저장
    return S;                                              // S를 반환
}

int is_Empty_Stack_LL_S(StackNode** top) {  //스택이 비어있을 경우
    return ((*top)->link == NULL);          //탑포인터의 링크값이 NULL일 때,
}

StackNode* push_LL_S(StackNode** top, int size) {             //스택에 값을 입력하는 함수
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));  //임시로 저장 할 temp 동적 메모리 선언
    for (int i = 0; i < size; i++) {
        temp->data = i;                     // temp의 data에 item 저장
        if (!temp)                          // temp가 정상적으로 선언되지 않았을 경우
            exit(1);
        if (is_Empty_Stack_LL_S(top)) {    // stack이 비어있을 때,
            (*top)->link = temp;           // top의 link를 temp에 연결 (아무것도 없는 상태의 top포인터에 첫노드를 연결)
            temp->link = NULL;             //첫 스택이므로 다음 링크는 NULL
        }
        else {                  // stack에 값이 있으나, 비어있지는 않은 경우
            temp->link = (*top);  // temp의 link를 top포인터에 연결
            (*top) = temp;        // top포인터에 temp저장
        }
    }

    return *top;
}

void LL_Stack_insertion_Random_Access_Read(StackNode** top, int size) {
    clock_t start = clock();
    int sum = 0;
    int pos = 0;

    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    for (int i = 0; i < RECALL; i++) {
        temp = (*top);
        int k = 0;                  // pos값과 비교 및 이동을 위한 변수 k 생성
        pos = rand() % size;        // rand 함수를 이용해 만들어진 난수를 max로 나눈 나머지값인 0부터 9999까지의 무작위 수를 pos에 저장
        while (k < pos) {           // k가 pos보다 작을 때, 링크를 타고 계속해서 뒷 노드로 이동
            temp = temp->link;      // p = p가 가리키는 링크를 타고 계속해서 이동
            k++;                    //반복 할 때마다, k+1 실행
            if (k == pos)           // while 문을 계속해서 돌다가 k와 pos의 값이 같아질 경우
                sum += temp->data;  // sum에 p의 data값을 더해주고 탈출
        }
    }

    clock_t end = clock();
    printf("LL_Stack sum = %d \n",sum);
    printf("Random_Access_Read_time (Linked List -> Stack) : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC);
}

void LL_Stack_insertion(int size) {
    clock_t start = clock();
    StackNode* top;
    top = create_LL_S(&top);

    for (int i = 0; i < size; i++)
        push_LL_S(&top, i);
    clock_t end = clock();
    printf("insertion 실행시간(Linked List -> Stack) : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC);
    LL_Stack_insertion_Random_Access_Read(&top, size);
}

// ----------------------------------------------구분선-----------------------------------------------
/* void Dynamic_Array_Queue_insertion_Random_Access_Read() {

}

int is_Full_QA(QueueType_Array* q) {
    return (q->rear == q->capacity - 1);
}

int is_empty_QA(QueueType_Array* q) {
    if (q->front == q->rear)
        return 1;
    else
        return 0;
}

int is_Full_LLQueue(LL_Queue* Q) {               //큐의 상태 확인을 위한 함수 (가득 찬 경우)
    return (Q->capacity == Q->rear->count + 1);  // capacity값과 count+1의 값이 같을 경우 큐가 가득찬 경우
}

int is_Empty_LLQueue(LL_Queue* Q) {  //큐의 상태 확인을 위한 함수 (비어있을 경우)
    return (Q->front == NULL);       // front가 비어있을 경우
}

void Dynamic_Array_Queue_insertion(QueueType_Array* Q, int size) {
    clock_t start = clock();
    // create_Queue
    Q = (QueueType_Array*)malloc(sizeof(QueueType_Array));
    Q->capacity = size;
    Q->array = (int*)malloc(sizeof(Q->capacity));
    Q->rear = -1;
    Q->front = -1;

    // enqueue
    for (int i = 0; i < size; i++) {
        if (is_Full_QA(Q)) {
            error("큐가 포화상태입니다.");
            return;
        }
        Q->array[++(Q->rear)] = i;
    }

    clock_t end = clock();

    printf("insertion 실행시간(Array -> Queue) : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC);
    Dynamic_Array_Queue_insertion_Random_Access_Read();
}

void LL_Queue_insertion_Random_Access_Read() {
}

void LL_Queue_insertion(LL_Queue* Q, int size) {
    clock_t start = clock();
    ListNode_Q* temp;
    Q = malloc(sizeof(LL_Queue));  //큐에 동적 메모리 할당
    Q->capacity = size;
    if (!Q)  //정상적으로 큐에 동적 메모리가 할당되지 않았을 경우
        return;
    temp = malloc(sizeof(ListNode_Q));       // temp에 동적 메모리 할당
    Q->front = malloc(sizeof(Q->capacity));  // front와 rear의 초기 값 설정을 위해 동적메모리 할당
    Q->rear = malloc(sizeof(Q->capacity));
    Q->front->link = Q->rear->link = NULL;
    Q->front->count = Q->rear->count = -1;  // count값을 -로 지정

    for (int i = 0; i < size; i++) {
        ListNode_Q* newNode;                   //새로운 노드 선언
        newNode = malloc(sizeof(ListNode_Q));  //노드 동적 메모리 할당
        if (!newNode)                          //노드에 메모리 할당이 정상적으로 되지 않았을 경우
            return;

        if (is_Full_LLQueue(Q)) {
            printf("[Queue is Full] \n");  //가득 찼을 경우 오류 출력
            return;
        } else {
            newNode->data = i;
            newNode->link = NULL;
            newNode->count = Q->rear->count + 1;  //새로운 노드가 들어가면서 rear의 count값이 1 증가해야하기 때문에, 새로운 노드의 count 값을 rear count값의 +1 로 세트
            if (Q->rear->count != -1) {           //큐 안에 데이터가 하나 이상 들어있는 경우
                Q->rear->link = newNode;
                Q->rear = newNode;
            }

            if (Q->front->link == NULL) {  //큐가 비어있는 상황에서 삽입하는 함수
                Q->rear = newNode;
                Q->front = Q->rear;
            }
        }
    }
    clock_t end = clock();
    printf("insertion 실행시간(Linked List -> Queue) : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC);
    LL_Queue_insertion_Random_Access_Read();
} */

void Call_Function(Stack_Array* S, StackNode* LL_S, QueueType_Array* Q, LL_Queue* LL_Q, int size) {
    Dynamic_Array_Stack_insertion(S, size);
    LL_Stack_insertion(size);

   /*  Dynamic_Array_Queue_insertion(Q, size);
    LL_Queue_insertion(LL_Q, size); */
}

// ---------------------------------------------구분선---------------------------------------------ㅁ
int main(int argc, char* argv[]) {
    srand(time(NULL));
    Stack_Array* S;
    StackNode* LL_S;
    QueueType_Array* Q;
    LL_Queue* LL_Q;
    int size = 0;
    size = set_size();
    Call_Function(S, LL_S, Q, LL_Q, size);

    return 0;
}