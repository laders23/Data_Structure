#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DlistNode //DlistNode 선언
{
    element data;
    struct DlistNode *llink;
    struct DlistNode *rlink;
} DlistNode;

void init(DlistNode* phead){ //헤드를 초기화 시켜주는 함수
    phead->llink = phead; //헤드의 왼쪽 링크 값에 헤드 연결
    phead -> rlink = phead; //헤드의 왼쪽 링크 값에 헤드 연결
}

void dInsert(DlistNode *before, element data) //해당 코드로는 무조건 헤드 우측으로만 넣을 수 있음. (중간 노드의 주소값을 몰라서)
{
    DlistNode *newnode = (DlistNode *)malloc(sizeof(DlistNode)); //새로 입력 해줄 노드 동적 메모리 선언
    newnode->data = data; // 새로운 노드의 데이터 자리에 입력받은 데이터 저장
    newnode->llink = before; // 새로운 노드의 좌측 링크를 이전 노드에 연결
    newnode->rlink = before->rlink; //새로운 노드의 우측 링크를 이전 노드의 우측 링크로 연결
    before->rlink->llink = newnode; // 이전 노드의 오른쪽 링크가 가르키는 곳의 왼쪽 링크를 새로운 노드에 연결
    before->rlink = newnode; // 이전 노드의 우측 링크에는 새로운 노드 위치
}

void Delete_first(DlistNode *delete_node){ //노드 삭제 함수

    delete_node -> llink -> rlink = delete_node -> rlink; //삭제할 노드의 왼쪽 링크가 가르키는 곳의 우측 링크에 삭제할 노드의 우측 링크 연결
    delete_node -> rlink -> llink = delete_node -> llink; //삭제할 노드의 우측 링크가 가르키는 곳의 좌측 링크를 삭제할 노드의 좌측 링크에 연결 (해당 과정을 통해서 삭제할 노드 좌우로 재 연결 해줌)

    free(delete_node); //메모리 해제를 통한 노드 삭제

}

void print_dlist(DlistNode* phead){ //노드 출력을 위한 함수
    DlistNode* p; //포인터 p를 선언
    for(p=phead->rlink; p!=phead; p=p->rlink) //p=phead의 우측 링크값이고, p가 phead가 아닐 때, p에 p의 우측 링크를 타고 계속 이동하며 출력할 수 있는 반복문 설정
        printf("<-| |%d| |->",p->data); //p의 데이터값 출력
    printf("\n");
}

int main(int argc, char *argv[])
{
    DlistNode* head = (DlistNode*)malloc(sizeof(DlistNode)); //헤드 선언
    init(head); //헤드 초기화
    for(int i = 0; i<5; i++){ //입출력 반복문 생성
        dInsert(head,i); //입력 함수 호출
        print_dlist(head); //출력 함수 호출
    }
    Delete_first(head->rlink); // 삭제 함수 호출
    print_dlist(head); //출력 함수 호출로 삭제되었는지 확인.
}