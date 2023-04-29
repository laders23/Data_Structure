#include <stdio.h>
#include <stdlib.h>

typedef struct DQNode {  // Doubly Linked List 구현을 위한 노드 구조체 선언
    char data;
    struct DQNode* llink;
    struct DQNode* rlink;
} DQNode;

typedef struct {  //덱 구현을 위한 front, rear 구조체 선언
    DQNode *front, *rear;
} DQueType;

DQueType* createDQue() {  //덱 초기화 함수
    DQueType* DQ;
    DQ = (DQueType*)malloc(sizeof(DQueType));  //덱으로 사용 할 변수 DQ에 동적메모리 할당
    DQ->front = NULL;
    DQ->rear = NULL;
    return DQ;
}

int isEmpty(DQueType* DQ) {  //덱이 비었을 경우
    if (DQ->front == NULL) {
        printf("\n Linked Queue is Empty");
        return 1;
    } else
        return 0;
}

void insertFront(DQueType* DQ, char item) {             // front방향으로 삽입하는 함수
    DQNode* NewNode = (DQNode*)malloc(sizeof(DQNode));  //삽입 될 값을 저장 할 NewNode 선언 후, 동적 메모리 할당
    NewNode->data = item;                               //데이터 입력
    if (DQ->front == NULL) {                            //덱에 데이터가 없는 경우
        DQ->front = NewNode;
        ;  //데이터가 없는 경우 front와 rear 모두 새로운 노드로 초기화,
        DQ->rear = NewNode;
        NewNode->rlink = NULL;
        NewNode->llink = NULL;
    } else {
        NewNode->llink = NULL;
        NewNode->rlink = DQ->front;  //데이터가 있는경우 새로운 노드의 rlink위치에 DQ->front를 두고,
        DQ->front->llink = NewNode;  // DQ->front의 llink에 새로운 노드를 둠,
        DQ->front = NewNode;         //이후 front를 새로운 노드로 설정해줌
    }
}

void insertRear(DQueType* DQ, char item) {  // rear방향으로 삽입하는 함수
    DQNode* NewNode = (DQNode*)malloc(sizeof(DQNode));
    NewNode->data = item;
    if (DQ->rear == NULL) {  //덱에 데이터가 없는 경우
        DQ->front = NewNode;
        DQ->rear = NewNode;
        NewNode->rlink = NULL;
        NewNode->llink = NULL;
    } else {
        NewNode->llink = DQ->rear;
        NewNode->rlink = NULL;
        DQ->rear->rlink = NewNode;
        DQ->rear = NewNode;
    }
}

char deleteFront(DQueType* DQ) {
    DQNode* temp = DQ->front;  //노드 삭제를 위해 임시노드인 temp 를 front로 설정
    char item;                 //값 반환을 위한 임시 노드 item 선언
    if (isEmpty(DQ))           //덱이 비어있는 경우
        return 0;
    else {
        item = temp->data;
        if (DQ->front->rlink == NULL) {  // front를 제외한 나머지 덱에 값이 없을 경우
            DQ->front = NULL;
            DQ->rear = NULL;
        } else {
            DQ->front = temp->rlink;  // front를 삭제할 다음 노드의 위치로 옮긴 뒤,
            DQ->front->llink = NULL;
        }
    }
    free(temp);  //메모리 해제를 통한 삭제
    return item;
}

char deleteRear(DQueType* DQ) {
    DQNode* temp = DQ->rear;  //노드 삭제를 위해 임시노드인 temp를 rear로 설정
    char item;
    if (isEmpty(DQ))  //덱이 비어있는 경우
        return 0;
    else {
        item = temp->data;
        if (DQ->rear->llink == NULL) {  // rear를 제외한 나머지 덱에 값이 없을 경우
            DQ->front = NULL;
            DQ->rear = NULL;
        } else {
            DQ->rear = temp->llink;  // rear를 삭제할 노드의 이전 위치로 옮긴 뒤,
            DQ->rear->rlink = NULL;
        }
    }
    free(temp);  //메모리 해제를 통한 삭제
    return item;
}
void print_DQue(DQueType* DQ) {
    DQNode* temp;
    temp = DQ->front;
    while (temp != NULL) {
        printf("%c -> ", temp->data);
        temp = temp->rlink;
    }
    printf("\n");
}

void Function(DQueType* DQ) {
    insertFront(DQ, 'A');
    print_DQue(DQ);
    insertRear(DQ, 'B');
    print_DQue(DQ);
    insertFront(DQ, 'C');
    print_DQue(DQ);
    insertRear(DQ, 'D');
    print_DQue(DQ);
    deleteFront(DQ);
    print_DQue(DQ);
    deleteRear(DQ);
    print_DQue(DQ);
}

int main(int argc, char* argv[]) {
    DQueType* DQ;
    DQ = createDQue();
    Function(DQ);
    return 0;
}