#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode { //Linked List로 구현하기 위해, ListNode 구조체 선언
    int data; //데이터를 저장해줄 변수 선언
    int count; //배열로 구현한 큐에서의 front,rear값을 받아줄 수 있도록 count 변수 선언
    struct ListNode* link;
} ListNode;

typedef struct Queue { //Queue 구현을 위한 구조체 선언
    int capacity; //Queue의 크기를 정해주는 capapcity 선언
    struct ListNode* front;
    struct ListNode* rear;
} Queue;

Queue* createQueue() { //큐를 생성 및 초기화를 위한 함수
    Queue* Q; 
    ListNode* temp;
    Q = malloc(sizeof(Queue)); //큐에 동적 메모리 할당
    Q->capacity = 5; //큐의 크기를 5로 설정
    if (!Q) //정상적으로 큐에 동적 메모리가 할당되지 않았을 경우
        return NULL;
    temp = malloc(sizeof(ListNode)); //temp에 동적 메모리 할당
    Q->front = malloc(sizeof(Q->capacity)); //front와 rear의 초기 값 설정을 위해 동적메모리 할당
    Q->rear = malloc(sizeof(Q->capacity));
    Q->front->link = Q->rear->link = NULL;
    Q->front->count = Q->rear->count = -1; //count값을 -로 지정

    return Q;
}
int isFullQueue(Queue* Q) { //큐의 상태 확인을 위한 함수 (가득 찬 경우)
    return (Q->capacity == Q->rear->count + 1); //capacity값과 count+1의 값이 같을 경우 큐가 가득찬 경우
}

int isEmptyQueue(Queue* Q) { //큐의 상태 확인을 위한 함수 (비어있을 경우)
    return (Q->front == NULL); //front가 비어있을 경우
}

void enQueue(Queue* Q, int item) { //큐에 item을 삽입하는 함수
    ListNode* newNode; //새로운 노드 선언
    newNode = malloc(sizeof(ListNode)); //노드 동적 메모리 할당
    if (!newNode) //노드에 메모리 할당이 정상적으로 되지 않았을 경우
        return;

    if (isFullQueue(Q)) {
        printf("[Queue is Full] \n"); //가득 찼을 경우 오류 출력
        return;
    } else {
        newNode->data = item;
        newNode->link = NULL;
        newNode->count = Q->rear->count + 1; //새로운 노드가 들어가면서 rear의 count값이 1 증가해야하기 때문에, 새로운 노드의 count 값을 rear count값의 +1 로 세트
        if (Q->rear->count != -1) { //큐 안에 데이터가 하나 이상 들어있는 경우
            Q->rear->link = newNode;
            Q->rear = newNode;
        }

        if (Q->front->link == NULL) { //큐가 비어있는 상황에서 삽입하는 함수
            Q->rear = newNode;
            Q->front = Q->rear;
        }
    }
}

int deQueue(Queue* Q) {
    int data = 0;
    ListNode* old; //삭제를 위한 old 노드 선언
    old = malloc(sizeof(ListNode));

    if (isEmptyQueue(Q)) { //큐가 비어있을 때,
        printf("[Queue is Empty");
        return 0;
    } else {
        old = Q->front; //old에 front 값 저장
        data = Q->front->data; //반환을 위해 data에 front->data값 저장
        Q->front = Q->front->link; //삭제를 위해서 front의 원래 위치에서 front->link 로 이동
        if (Q->front == NULL) //큐의 값을 꺼낸 뒤, 값이 빈 경우 rear도 초기값으로 변경
            Q->rear = NULL;
        free(old); //old 메모리 해제를 통해 삭제
    }
    return data; //data 반환
}

void deleteQueue(Queue* Q) { //전체 큐를 삭제하는 함수
    ListNode* temp; //임시 노드 temp 선언
    while (Q->front) { //Q->front에 값이 있을 때 반복
        temp = Q->front; //temp에 Q->front 저장
        Q->front = Q->front->link; //링크를 타고 다음 노드로 이동
        free(temp); //메모리 해제를 통한 삭제
    }
    free(Q); //위 과정이 모두 끝나면 큐 자체를 메모리 해제
}

void print_Queue(Queue* Q) { //큐를 출력하는 함수
    ListNode* temp; //임시노드 temp 선언
    temp = Q->front; //temp에 front 저장
    if (temp != NULL) { //temp가 NULL이 아닐 때 반복 
        for (int i = temp->count; i < Q->capacity; i++) { //front 부터 출력해야 하기 때문에, i를 temp->count 로 설정
            printf("%d -> ", temp->data); //데이터 출력
            temp = temp->link; //링크를 타고 다음 노드로 이동
            if (temp == NULL) //temp가 NULL을 만나면 break
                break;
        }
    }
    else
        printf("[Now Queue is Empty]"); //모든 값을 출력한 뒤, 큐가 비었을 경우 (큐가 빈 상태에서 한번 더 dequeue를 하는 상황과는 다름)
}

int main(int argc, char* argv[]) {
    Queue* Q = malloc(sizeof(Queue)); //큐를 구현하기 위해 선언한 Q에 동적 메모리 선언
    Q = createQueue(); //큐 초기화 함수 호출
    printf("=================enQueue=================\n"); //enQueue 과정
    for (int i = 0; i < 6; i++) {
        enQueue(Q, i);
        print_Queue(Q);
        printf("\n");
    }
    printf("=================deQueue=================\n"); //deQueue 과정
    for (int i = 0; i < 5; i++) {
        deQueue(Q);
        print_Queue(Q);
        printf("\n");
    }

    return 0;
}