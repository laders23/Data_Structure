#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define MAX 1000000

void error(char* message) { 
    fprintf(stderr, "%s\n", message);
    exit(1);
}

//  insertion_Dynamic_Array_Stack 함수---------------------------------------------------------------------

typedef struct Dynamic_Array_S {
    int top;
    int capacity;
    int* array;
} Dynamic_Array_S;

Dynamic_Array_S* createStack() {  //구조체 생성 함수
    Dynamic_Array_S* S = malloc(sizeof(Dynamic_Array_S));
    if (!S) return NULL;                           //정상적으로 동적할당이 되지 않은 경우
    S->top = -1;                                   // top을 -1로 지정,
    S->capacity = SIZE;                            // capacity는 define 해놓은 SIZE로 설정 (초기 설정)
    S->array = malloc(S->capacity * sizeof(int));  // malloc 을 통해 capacity크기 만큼의 배열 생성
    if (!S->array) return NULL;                    //정상적으로 동적할당이 되지 않은 경우
    return S;
}

Dynamic_Array_S* Dynamic_array(Dynamic_Array_S* S) {                 //스택이 가득 찼을 때, capacity를 늘려줄 동적배열 함수
    S->capacity += 100000;                                             // capacity의 값을 임의의 수만큼 늘려가면서 비교
    S->array = (int*)realloc(S->array, S->capacity * sizeof(int*));  // realloc을 통해 재설정
    return S;
}

int DA_isFull(Dynamic_Array_S* S) {      //스택이 가득 찼을 때,
    return (S->top == S->capacity - 1);  // top의 값과 전체 크기에서 -1한 값이 같을 경우 0을 반환, 스택이 가득 찼다는 뜻
}

void DA_push(Dynamic_Array_S* S, int data) {  //스택에 새로운 데이터를 push 해주는 함수
    if (DA_isFull(S)) {                       //스택이 가득 찼을 경우
        Dynamic_array(S);                     //재할당을 해줄 Dynamic_array 함수 호출
        S->array[++(S->top)] = data;          // Dynamic_array 함수 탈출 후에 data입력을 위해 추가
        printf("Insertion (Array Stack) : %d\n", S->array[S->top]);
    } else
        S->array[++(S->top)] = data;  //스택에 빈자리가 있을 경우 data입력
    printf("Insertion (Array Stack) : %d\n", S->array[S->top]);
}

int DA_isEmpty(Dynamic_Array_S* S) {  //스택이 비어있을 때,
    return (S->top == -1);            // top의 값이 -1일 때, 0을 반환
}

// insertion_Linked_List_Stack 함수---------------------------------------------------------------------

typedef struct StackNode {
    int data;
    int count;
    struct StackNode* link;
} StackNode;

StackNode* create_Stack(StackNode** top) {                 //스택 생성 및 초기화 함수
    (*top) = NULL;                                         //포인터 탑에 NULL 저장
    StackNode* S = (StackNode*)malloc(sizeof(StackNode));  // StackNode 동적 메모리 선언
    S->link = NULL;                                        // S의 링크에 NULL 저장
    S->count = 0;
    return S;  // S를 반환
}

int isEmptyStack(StackNode** top) {  //스택이 비어있을 경우
    return ((*top)->link == NULL);   //탑포인터의 링크값이 NULL일 때,
}

StackNode* LL_Stack_push(StackNode** top, int item) {         //스택에 값을 입력하는 함수
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));  //임시로 저장 할 temp 동적 메모리 선언
    temp->data = item;                                        // temp의 data에 item 저장
    if (!temp)                                                // temp가 정상적으로 선언되지 않았을 경우
        exit(1);
    if (isEmptyStack(top)) {  // stack이 비어있을 때,
        (*top)->link = temp;  // top의 link를 temp에 연결 (아무것도 없는 상태의 top포인터에 첫노드를 연결)
        temp->link = NULL;    //첫 스택이므로 다음 링크는 NULL
        temp->count++;
        printf("Insertion (Linked List Stack) : %d \n", (*top)->data);
    } else {                  // stack에 값이 있으나, 비어있지는 않은 경우
        temp->link = (*top);  // temp의 link를 top포인터에 연결
        (*top) = temp;        // top포인터에 temp저장
        temp->count++;
        printf("Insertiona (Linked List Stack) : %d \n", (*top)->data);
    }
    return *top;
}

// insertion_Dynamic_Array_Queue 함수---------------------------------------------------------------------

typedef struct Dynamic_Array_Q { //Array로 Queue 구현한 구조체 선언
    int front, rear;
    int capacity;
    int* array;
} Dynamic_Array_Q;

Dynamic_Array_Q* create_queue() { //구조체 생성 함수
    Dynamic_Array_Q* p = (Dynamic_Array_Q*)malloc(sizeof(Dynamic_Array_Q)); 
    int size = 0;
    p->capacity = SIZE; // 기존에 define 해둔 SIZE만큼 capacity 설정
    p->array = (int*)malloc(sizeof(p->capacity)); //해당 capacity 크기만큼 array 동적 할당
    p->rear = -1;
    p->front = -1;
    return p;
}

Dynamic_Array_Q* Dynamic_Array_queue(Dynamic_Array_Q* Q) {
    Q->capacity += 1000000;                                             // capacity의 값을 임의의 수만큼 늘려서 realloc을 통해 재할당
    Q->array = (int*)realloc(Q->array, Q->capacity * sizeof(int*));  // realloc을 통해 재설정
    return Q;
}

int DAQ_is_Full(Dynamic_Array_Q* q) { //Queue가 가득 찼을 때,
    if (q->rear == q->capacity - 1)
        return 1;
    else
        return 0;
}

void DAQ_enqueue(Dynamic_Array_Q* q, int item) { //Dynamic_Array_Queue에 값을 enque하는 함수
    if (DAQ_is_Full(q)) {
        Dynamic_Array_queue(q);
        return;
    }
    q->array[++(q->rear)] = item;
    printf("Insertion (Array_Queue) : %d \n", q->array[q->rear]);
}

// insertion_Linked_List_Queue 함수---------------------------------------------------------------------

typedef struct ListNode_Q {
    int data;
    int count;
    struct ListNode_Q* link;
} ListNode_Q;

typedef struct LL_Q {
    struct ListNode_Q* front;
    struct ListNode_Q* rear;
} LL_Q;

LL_Q* LL_createQueue() {  //큐를 생성 및 초기화를 위한 함수
    LL_Q* Q;
    ListNode_Q* temp;
    Q = malloc(sizeof(LL_Q));           //큐에 동적 메모리 할당
    temp = malloc(sizeof(ListNode_Q));  // temp에 동적 메모리 할당
    Q->front = malloc(sizeof(LL_Q));    // front와 rear의 초기 값 설정을 위해 동적메모리 할당
    Q->rear = malloc(sizeof(LL_Q));
    Q->front->link = Q->rear->link = NULL;
    Q->front->count = Q->rear->count = -1;  // count값을 -로 지정

    return Q;
}

void LL_enQueue(LL_Q* Q, int item) {       //큐에 item을 삽입하는 함수
    ListNode_Q* newNode;                   //새로운 노드 선언
    newNode = malloc(sizeof(ListNode_Q));  //노드 동적 메모리 할당
    if (!newNode)                          //노드에 메모리 할당이 정상적으로 되지 않았을 경우
        return;

    newNode->data = item;
    newNode->link = NULL;
    newNode->count = Q->rear->count + 1;  //새로운 노드가 들어가면서 rear의 count값이 1 증가해야하기 때문에, 새로운 노드의 count 값을 rear count값의 +1 로 세트
    if (Q->rear->count != -1) {           //큐 안에 데이터가 하나 이상 들어있는 경우
        Q->rear->link = newNode;
        Q->rear = newNode;
        printf("Insertion (Linked List Queue) : %d \n", Q->rear->data);
    }

    if (Q->front->link == NULL) {  //큐가 비어있는 상황에서 삽입하는 함수
        Q->rear = newNode;
        Q->front = Q->rear;
        printf("Insertion (Linked List Queue) : %d \n", Q->rear->data);
    }
}

// insertion 함수---------------------------------------------------------------------------------------------

Dynamic_Array_S* insertion_Array_Stack_Function() { //Array_Stack push 함수
    Dynamic_Array_S* S;
    S = createStack();
    for (int i = 0; i < MAX; i++)
        DA_push(S, i);
    return S;
}

StackNode* insertion_LL_Stack_Function() { //Linked List Stack push 함수
    StackNode* top;
    top = create_Stack(&top);
    for (int i = 0; i < MAX; i++)
        LL_Stack_push(&top, i);
    return top;
}

Dynamic_Array_Q* insertion_Array_Queue_Function() { //Array_Queue enque 함수
    Dynamic_Array_Q* Q;
    Q = create_queue();
    for (int i = 0; i < MAX; i++)
        DAQ_enqueue(Q, i);
    return Q;
}

LL_Q* insertion_LL_Queue_Function() { //Linked List Queue enque 함수
    LL_Q* Q;
    Q = LL_createQueue();
    for (int i = 0; i < MAX; i++)
        LL_enQueue(Q, i);
    return Q;
}

// Random_Access_For_Read_Array_Stack 함수---------------------------------------------------------------------

void Random_Access_For_Read_Array_Stack(Dynamic_Array_S* S) { //무작위 위치의 값을 추출해 더해주는 함수
    double sum = 0;
    for (int i = 0; i < 100; i++)
        sum += S->array[rand() % MAX];
    printf("Sum(Array_Stack) = %lf \n", sum);
}

// Random_Access_For_Read_LL_Stack 함수---------------------------------------------------------------------

StackNode* Random_Access_For_Read_LL_Stack(StackNode* S) { //무작위 위치의 값을 추출해 더해주는 함수
    double sum = 0;
    int pos = 0;
    StackNode* p = NULL;

    for (int i = 0; i < 100; i++) {
        p = S;
        int k = 0;
        pos = rand() % MAX;
        while (k < pos) {
            p = p->link;
            k++;
            if (k == pos)
                sum += p->data;
        }
    }
    printf("Sum(LL_Stack) = %lf \n", sum);
    return S;
}

// Random_Access_For_Read_Array_Queue 함수---------------------------------------------------------------------

void Random_Access_For_Read_Array_Queue(Dynamic_Array_Q* Q) { //무작위 위치의 값을 추출해 더해주는 함수
    double sum = 0;
    for (int i = 0; i < 100; i++)
        sum += Q->array[rand() % MAX];
    printf("Sum(Array_Queue) = %lf \n", sum);
}

// Random_Access_For_Read_LL_Queue 함수---------------------------------------------------------------------

LL_Q* Random_Access_For_Read_LL_Queue(LL_Q* Q) { //무작위 위치의 값을 추출해 더해주는 함수
    double sum = 0;
    int pos = 0;
    ListNode_Q* p = NULL;

    for (int i = 0; i < 100; i++) {
        p = Q->front;
        int k = 0;
        pos = rand() % MAX;
        while (k < pos) {
            p = p->link;
            k++;
            if (k == pos)
                sum += p->data;
        }
    }
    printf("Sum(LL_Queue) = %lf \n", sum);
    return Q;
}

void call_Function() { //함수들을 호출해주는 함수
    Dynamic_Array_S* DS;
    StackNode* S;
    Dynamic_Array_Q* DQ;
    LL_Q* LL_Q;
    double time_to_Array_Stack;
    double time_to_LL_Stack;
    double time_to_Array_Queue;
    double time_to_LL_Queue;
    double time_to_Read_Array_Stack;
    double time_to_Read_LL_Stack;
    double time_to_Read_Array_Queue;
    double time_to_Read_LL_Queue;

    clock_t SA_start = clock();
    DS = insertion_Array_Stack_Function();
    clock_t SA_end = clock();
    time_to_Array_Stack = (double)(SA_end - SA_start) / (double)CLOCKS_PER_SEC;

    clock_t LL_S_start = clock();
    S = insertion_LL_Stack_Function();
    clock_t LL_S_end = clock();
    time_to_LL_Stack = (double)(LL_S_end - LL_S_start) / (double)CLOCKS_PER_SEC;

    clock_t QA_start = clock();
    DQ = insertion_Array_Queue_Function();
    clock_t QA_end = clock();
    time_to_Array_Queue = (double)(QA_end - QA_start) / (double)CLOCKS_PER_SEC;

    clock_t LL_Q_start = clock();
    LL_Q = insertion_LL_Queue_Function();
    clock_t LL_Q_end = clock();
    time_to_LL_Queue = (double)(LL_Q_end - LL_Q_start) / (double)CLOCKS_PER_SEC;

    printf("==================================================================================\n");
    printf("SIZE : %d\n",MAX);
    printf("==================================== Sum data ====================================\n");

    clock_t Random_Read_SA_Start = clock();
    Random_Access_For_Read_Array_Stack(DS);
    clock_t Random_Read_SA_End = clock();
    time_to_Read_Array_Stack = (double)(Random_Read_SA_End - Random_Read_SA_Start) / (double)CLOCKS_PER_SEC;

    clock_t Random_Read_LL_S_Start = clock();
    Random_Access_For_Read_LL_Stack(S);
    clock_t Random_Read_LL_S_End = clock();
    time_to_Read_LL_Stack = (double)(Random_Read_LL_S_End - Random_Read_LL_S_Start) / (double)CLOCKS_PER_SEC;

    clock_t Random_Read_QA_Start = clock();
    Random_Access_For_Read_Array_Queue(DQ);
    clock_t Random_Read_QA_End = clock();
    time_to_Read_Array_Queue = (double)(Random_Read_QA_End - Random_Read_QA_Start) / (double)CLOCKS_PER_SEC;

    clock_t Random_Read_LL_Q_Start = clock();
    Random_Access_For_Read_LL_Queue(LL_Q);
    clock_t Random_Read_LL_Q_End = clock();
    time_to_Read_LL_Queue = (double)(Random_Read_LL_Q_End - Random_Read_LL_Q_Start) / (double)CLOCKS_PER_SEC;

    printf("==================================== Insertion Function ====================================\n");
    printf("Insertion Time(Array_Stack): %lf\n", time_to_Array_Stack);
    printf("Insertion Time(Linked_List_Stack): %lf\n", time_to_LL_Stack);
    printf("Insertion Time(Array_Queue): %lf\n", time_to_Array_Queue);
    printf("Insertion Time(Linked_List_Queue): %lf\n", time_to_LL_Queue);
    printf("==================================== Random_Access_For_Read ====================================\n");
    printf("Random Read Time(Array_Stack) : %lf\n", time_to_Read_Array_Stack);
    printf("Random Read Time(Linked_List_Stack) : %lf\n", time_to_Read_LL_Stack);
    printf("Random Read Time(Array_Queue) : %lf\n", time_to_Read_Array_Queue);
    printf("Random Read Time(Linked_List_Queue) : %lf\n", time_to_Read_LL_Queue);
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    call_Function();
    return 0;
}