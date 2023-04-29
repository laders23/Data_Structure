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

DequeType* create_Deque() {                                //덱을 초기화 해주는 함수
    DequeType* D = (DequeType*)malloc(sizeof(DequeType));  //초기화 시켜줄 덱 동적메모리 할당
    if (!D)                                                //덱이 정상적으로 생성되지 않았을 경우
        return NULL;
    printf("덱의 사이즈를 입력하십시오. : ");
    scanf("%d", &D->capacity);                     //덱의 사이즈를 지정해서 입력받고
    D->array = (int*)malloc(sizeof(D->capacity));  //입력받은 크기로 배열 동적 메모리 선언
    D->front = -1;                                 // front, rear 초기값 설정
    D->rear = -1;

    if (!D->array)  //배열이 정상적이지 않을 경우
        return NULL;

    for (int i = 0; i < D->capacity; i++)  //배열이 비어있는 것을 -1로 약속, 모든 배열을 -1로 초기화
        D->array[i] = -1;

    return D;
}

int is_Full(DequeType* D) { //덱이 가득 찬 경우
    return ((D->rear + 1) % D->capacity == D->front); //rear+1 % D->capacity값이 D->front와 같을 경우에 반환 (D->rear값에 +1 %D->capacity 한 값이 front와 같다는 것은 덱의 모든 위치를 사용했다는 뜻이므로 )
}

int is_Empty(DequeType* D) { //덱이 비어있을 경우
    return (D->front == -1); //덱 안의 값이 없을 경우 (덱의 값을 꺼낸 뒤, 덱이 빌 경우 front를 -1로 설정해주었기 때문에)
}

void add_deque(DequeType* D, int select) { //덱에 값을 추가하는 함수
    int item = 0; //랜덤한 값을 입력받기 위해 임시 변수 item 선언
    srand(time(NULL));

    item = rand() % 100;
    printf("random Num : %d \n", item);
    switch (select) {
        case 1:
            if (is_Full(D)) {
                error("덱이 포화상태입니다.");
                return;
            } else if (D->front == -1)
                D->rear = D->front = 0;
            else
                D->front = ((D->front - 1) + D->capacity) % D->capacity;

            D->array[D->front] = item;
            break;

        case 2:
            if (is_Full(D)) {
                error("덱이 포화상태입니다.");
                return;
            } else if (D->rear == -1)
                D->front = D->rear = D->capacity - 1;
            else
                D->rear = ((D->rear + 1) + D->capacity) % D->capacity;  // rear 위치 설정
            D->array[D->rear] = item;                                   //위에서 저장 된 위치에 item 저장

        default:
            break;
    }
}

void deque_print(DequeType* D) {
    if (!is_Empty(D)) {
        for (int i = D->front; i < D->front + D->capacity; i++) {
            if (D->front <= D->rear && D->array[i % D->capacity] != -1) {
                printf("%d | ", D->array[i % D->capacity]);
            } else if (D->front > D->rear) {
                if (D->rear > i % D->capacity && D->array[i % D->capacity] != -1)
                    printf("%d | ", D->array[i % D->capacity]);
                else if (D->array[i % D->capacity] != -1)
                    printf("%d | ", D->array[i % D->capacity]);
            }
        }
    }
    printf("\n");
}

void del_deque(DequeType* D, int select) {
    switch (select) {
        case 3:
            if (is_Empty(D)) {
                error("덱이 공백상태 입니다.");
                break;
            } else {
                if (D->front == D->rear) {
                    D->array[D->front] = -1;
                    printf("덱이 비었습니다.");
                    D->front = D->rear = -1;
                } else {
                    D->array[D->front] = -1;
                    D->front = ((D->front + 1) + D->capacity) % D->capacity;
                }
                return;
            }
            break;

        case 4:
            if (is_Empty(D)) {
                error("덱이 공백상태 입니다.");
                break;
            } else {
                if (D->front == D->rear) {
                    D->array[D->front] = -1;
                    printf("덱이 비었습니다.");
                    D->front = D->rear = -1;
                } else {
                    D->array[D->rear] = -1;
                    D->rear = ((D->rear - 1) + D->capacity) % D->capacity;
                }
                return;
            }
    }
    return;
}

void Menu(DequeType* D) {
    int select = 0;
    while (1) {
        printf("front : %d , rear : %d \n", D->front, D->rear);
        printf("1. add_front \n");
        printf("2. add_rear\n");
        printf("3. delete_front\n");
        printf("4. delete_rear\n");
        printf("5. exit\n");
        printf("select : ");
        scanf("%d", &select);

        switch (select) {
            case 1:
                add_deque(D, select);
                deque_print(D);
                break;

            case 2:
                add_deque(D, select);
                deque_print(D);
                break;

            case 3:
                del_deque(D, select);
                deque_print(D);
                break;

            case 4:
                del_deque(D, select);
                deque_print(D);
                break;

            case 5:
                return;
        }
    }
}

int main(int argc, char* argv[]) {
    DequeType* D;
    D = create_Deque();
    
    Menu(D);

    return 0;
}