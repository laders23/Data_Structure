#include <stdio.h>
#include <stdlib.h>

typedef struct { //Queue에 대한 기본적인 구조체 선언부
    int front, rear;
    int capacity;
    int* array;
} QueueType;

void error(char* message) { //Error 발생 시 해당 에러를 출력해 줄 error 함수
    fprintf(stderr, "%s\n", message);
    exit(1);
}

int is_Full(QueueType* q) { //큐가 가득 찬 경우
    if (q->rear == q->capacity - 1)
        return 1;
    else
        return 0;
}

int is_empty(QueueType* q) { //큐가 비어있는 경우
    if (q->front == q->rear)
        return 1;
    else
        return 0;
}
void enqueue(QueueType* q, int item) { //Insert Data 데이터 삽입 부
    if (is_Full(q)) {
        error("큐가 포화상태입니다.");
        return;
    }
    q->array[++(q->rear)] = item;
}

int dequeue(QueueType* q) { //Delete Data 데이터 삭제 부
    if (is_empty(q)) {
        error("큐가 공백상태입니다.");
        return -1;
    }
    int item = q->array[++(q->front)];
    return item;
}

void queue_print(QueueType* q) { //현재 큐 안에 들어있는 데이터를 출력하는 함수
    for (int i = 0; i < q->capacity; i++) {
        if (i <= q->front || i > q->rear)
            printf(" | ");
        else
            printf("%d | ", q->array[i]);
    }
    printf("\n");
}

QueueType* create_queue() { //큐 생성 함수
    QueueType* p = (QueueType*)malloc(sizeof(QueueType)); //구조체에 대한 동적할당
    int size = 0;
    printf("만들 큐의 크기를 입력하십시오 : "); //만들 큐의 크기를 입력받아 Array에 동적할당
    scanf("%d", &p->capacity);
    p->array = (int*)malloc(sizeof(p->capacity));
    p->rear = -1;
    p->front = -1;
    return p;
}

int main(int argc, char* argv[]) { 
    QueueType* q; //큐 구조체 선언
    q = create_queue(); //큐 생성
    for (int i = 0; i < 5; i++) { //데이터를 0부터 4까지 삽입 및 출력
        enqueue(q, i);
        queue_print(q);
    }

    for (int i = 0; i < 10; i++) { //데이터를 순차적으로 삭제 및 출력
        dequeue(q);
        queue_print(q);
    }

    return 0;
}