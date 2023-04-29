#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 5

typedef struct { //큐 구현을 위한 구조체 선언
    int front, rear;
    int capacity;
    int* array;
} QueueType;

QueueType* create_queue() { //큐 생성
    QueueType* p = (QueueType*)malloc(sizeof(QueueType)); //큐 초기화를 위해 임시 구조체 p 생성
    if (!p) //p에 메모리 할당이 정상적으로 되지 않은 경우
        return NULL;
    p->capacity = SIZE; //capacity를 미리 define해놓은 SIZE 값 저장
    p->front = -1; //기본 상태인 -1 저장
    p->rear = -1;
    p->array = malloc(p->capacity * sizeof(int)); //capacity사이즈 만큼 메모리 할당

    if (!p->array) //메모리 할당이 정상적으로 되지 않은 경우
        return NULL;

    return p;
}

int is_Full(QueueType* q) { //큐가 가득 찼을 경우
    return ((q->rear + 1) % q->capacity == q->front); //rear+1 % capacity의 결과값이 front값과 같을 경우 큐가 가득찬 경우
}

int is_empty(QueueType* q) {
    return (q->front == -1); //front가 -1일 때, 초기 상태임으로 큐가 비어있는 상태
}

void enqueue(QueueType* q, int item) { //큐에 값을 추가해주는 함수
    if (is_Full(q)) { //is_Full 함수를 호출하고 가득찼는지 확인
        error("큐가 포화상태입니다.");
        return;
    } else { //가득 차 있지 않은 경우
        q->rear = (q->rear + 1) % q->capacity; //rear 위치 설정
        q->array[q->rear] = item; //위에서 저장 된 위치에 item 저장
        if (q->front == -1) //front가 1일 때 (값입력이 처음일 경우)
            q->front = q->rear; //front에도 rear 위치 저장
    }
}
int dequeue(QueueType* q) { //큐안의 값을 삭제하는 함수
    int item = 0; //item을 0으로 초기화

    if (is_empty(q)) { //is_empty 함수를 호출하고 큐가 비어있는지 확인
        error("큐가 공백상태입니다."); 
        return -1;
    }

    else { //비어있지 않은 경우
        item = q->array[q->front]; //item에 현재 저장되어있는 가장 앞쪽의 값을 저장
        if (q->front == q->rear) //front와 rear가 같아지는 순간 큐가 이제 비어있는 상황임으로 -1로 둘 다 초기화
            q->front = q->rear = -1;
        else //그렇지 않을 경우
            q->front = (q->front + 1) % q->capacity; //front의 값을 한 칸 당겨줌
        return item;
    }
}
void deleteQueue(QueueType* q) { //메모리 해제를 통한 큐 삭제 함수
    if (q) {
        if (q->array)
            free(q->array);
    }
    free(q);
}

void queue_print(QueueType* q) { //현재 큐에 저장된 값을 출력해주는 함수
    if (q->front <= q->rear) { //front가 rear와 같거나 더 작은 경우 (역전되지 않은 경우)
        for (int i = q->front; i < q->capacity; i++) { //i를 front로 잡고 큐의 사이즈만큼 출력
            if (i > q->rear) //큐에 값이 없을 때, (역전되지 않았기 때문에, i가 rear보다 커지는 순간에는 큐가 비어있음)
                printf(" | ");
            else if(q->array[i] != 0) //큐의 값이 0이 아닐 때만 출력 (큐를 0으로 모두 초기화 해놓은 상태라 0이 출력됨을 방지하기 위함)
                printf("%d | ", q->array[i]);
        }
        printf("\n");
    } else { //front값이 rear값을 역전한 경우
        for (int i = q->front; i < q->capacity; i++) { //이 때도 똑같이 front 값을 기준으로 잡고 반복
            if(q->array[i] != 0)
                printf("%d | ", q->array[i]);
        }
        for(int i = 0; i < q->front; i++){ //이 때, 역전되는 상황을 따로 출력 i를 0으로 초기화 한 뒤, front 직전까지 반복
           if (i > q->rear)
                printf(" | ");
            else if(q->array[i] != 0)
                printf("%d | ", q->array[i]);
        }
        
        printf("\n");
    }
}

void make_random_num(QueueType* q) { //랜덤한 값을 생성하고 배열에 추가하는 함수
    srand(time(NULL)); //확실한 랜덤값 시드를 위해 srand 선언
    int random_N[10]; //랜덤값을 저장해줄 임시 배열 선언
    for (int i = 0; i < 10; i++) {
        random_N[i] = rand() % 100;
    }

    for (int i = 0; i < 10; i++) {
        if (random_N[i] % 2 == 1) { //홀수 일 경우
            printf("random NUM : %d\n", random_N[i]);
            enqueue(q, random_N[i]); //큐 삽입
            printf("front : %d | rear : %d\n", q->front, q->rear); //현재 front, rear 값 출력
            queue_print(q); //큐에 저장된 값 출력
            printf("\n");

        } else {
            printf("random NUM : %d\n", random_N[i]); 
            dequeue(q); //큐 삭제
            printf("front : %d | rear : %d\n", q->front, q->rear);
            queue_print(q);
            printf("\n");
        }
    }
}

int main(int argc, char* argv[]) {
    QueueType* myQ = create_queue();
    make_random_num(myQ);
    return 0;
}