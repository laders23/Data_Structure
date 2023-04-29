#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {  //덱 구조체 선언
    int data;
    int front, rear;
    int capacity;
    int* array;
} DequeType;

void error(char* message) {  //에러 발생 시 에러메시지 출력 함수
    fprintf(stderr, "%s\n", message);
}

DequeType* create_Deque() {  //덱을 초기화 해주는 함수
    int size = 5;
    DequeType* D = (DequeType*)malloc(sizeof(DequeType));  //초기화 시켜줄 덱 동적메모리 할당
    if (!D)                                                //덱이 정상적으로 생성되지 않았을 경우
        return NULL;
    D->capacity = size;
    D->array = (int*)malloc(sizeof(D->capacity));  //입력받은 크기로 배열 동적 메모리 선언
    D->front = -1;                                 // front, rear 초기값 설정
    D->rear = -1;

    if (!D->array)  //배열이 정상적이지 않을 경우
        return NULL;

    for (int i = 0; i < D->capacity; i++)  //배열이 비어있는 것을 -1로 약속, 모든 배열을 -1로 초기화
        D->array[i] = -1;

    return D;
}

int is_Full(DequeType* D) {                            //덱이 가득 찬 경우
    return ((D->rear + 1) % D->capacity == D->front);  // rear+1 % D->capacity값이 D->front와 같을 경우에 반환 (D->rear값에 +1 %D->capacity 한 값이 front와 같다는 것은 덱의 모든 위치를 사용했다는 뜻이므로 )
}

int is_Empty(DequeType* D) {  //덱이 비어있을 경우
    return (D->front == -1);  //덱 안의 값이 없을 경우 (덱의 값을 꺼낸 뒤, 덱이 빌 경우 front를 -1로 설정해주었기 때문에)
}
void add_front(DequeType* D, char item) {  // front에 삽입하는 함수
    if (is_Full(D)) {                      //덱이 포화상태일 경우
        error("덱이 포화상태입니다.");
        return;
    } else if (D->front == -1)  // front에 처음 삽입되는 경우 front와 rear 모두 0으로 초기화
        D->front = D->rear = 0;
    else
        D->front = ((D->front - 1) + D->capacity) % D->capacity;  //덱에 데이터가 있는 경우

    D->array[D->front] = item;  // front를 index값으로 받아 item 저장
}

void add_rear(DequeType* D, char item) {
    if (is_Full(D)) {
        error("덱이 포화상태입니다.");
        return;
    } else if (D->rear == -1)  // rear에 처음 삽입될 경우
        D->front = D->rear = D->capacity - 1;
    else
        D->rear = ((D->rear + 1) + D->capacity) % D->capacity;  // rear 위치 설정
    D->array[D->rear] = item;                                   //위에서 저장 된 위치에 item 저장
}

void del_front(DequeType* D) {  // front값을 지우는 함수
    if (is_Empty(D)) {          //덱이 비어있을 경우 오류 출력
        error("덱이 공백상태 입니다.");
        return;
    } else {                          // 덱이 비어있지 않을 경우
        if (D->front == D->rear) {    // front와 rear값이 같을 경우 (크기가 5만큼인 원형 배열의 경우 가득 찼다고 하더라도, 데이터가 없는 경우를 제외하고, front와 rear는 같아질 수 없음)
            D->array[D->front] = -1;  //-해당 위치를 -1로 초기화
            printf("덱이 비었습니다.");
            D->front = D->rear = -1;                                  // front,rear 모두 -1로 초기화
        } else {                                                      //덱에 값이 남아있는 경우
            D->array[D->front] = -1;                                  //해당 위치의 데이터를 -1로 바꾸고,
            D->front = ((D->front + 1) + D->capacity) % D->capacity;  // D->front 재 설정
        }
        return;
    }
}

void del_rear(DequeType* D) {  // rear값을 지우는 함수
    if (is_Empty(D)) {         //덱이 비어있을 경우 오류 출력
        error("덱이 공백상태 입니다.");
        return;
    } else {  //덱이 비어있지 않을 경우
        if (D->front == D->rear) {
            D->array[D->front] = -1;
            printf("덱이 비었습니다.");
            D->front = D->rear = -1;
        } else {  //덱에 값이 남아있는 경우
            D->array[D->rear] = -1;
            D->rear = ((D->rear - 1) + D->capacity) % D->capacity;
        }
        return;
    }
}

void deque_print(DequeType* D) {  //덱의 데이터를 출력하는 함수
    if (!is_Empty(D)) { //덱이 비어있지 않은 경우
        for (int i = D->front; i < D->front + D->capacity; i++) { //i를 front로 설정, D->capacity 값으로 나눈 나머지값을 비교하기 위해 조건을 front+capacity로 설정
            if (D->front <= D->rear && D->array[i % D->capacity] != -1) { //front값이 역전되지 않은 경우
                printf("%c | ", D->array[i % D->capacity]);
            } else if (D->front > D->rear) { //front 값이 역전 된 경우
                if (D->rear > i % D->capacity && D->array[i % D->capacity] != -1) //rear값이 i%capacity 값보다 클 경우 (역전 된 이후, front부터 capacity까지 출력)
                    printf("%c | ", D->array[i % D->capacity]);
                else if (D->array[i % D->capacity] != -1) //역전 된 이후, capacity에서 rear까지 출력 (front = 3, rear = 2이고, capacity가 5일 경우 0,1,2 출력)
                    printf("%c | ", D->array[i % D->capacity]);
            }
        }
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    DequeType* D;
    D = create_Deque();
    
    add_front(D, 'A');
    deque_print(D);
    add_rear(D, 'B');
    deque_print(D);
    add_front(D, 'C');
    deque_print(D);
    add_rear(D, 'D');
    deque_print(D);
    del_front(D);
    deque_print(D);
    del_rear(D);
    deque_print(D);

    return 0;
}