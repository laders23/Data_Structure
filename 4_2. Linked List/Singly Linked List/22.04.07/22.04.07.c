#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode //리스트 생성
{
    element data;
    struct ListNode *link;

} ListNode;

ListNode *insert_first(ListNode *head, element value) //첫 번째 노드에 값 추가
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode)); //리스트 노드에 동적 메모리 선언
    node->data = value; //노드 data 위치에 value 저장
    if (head == NULL) //노드에 데이터가 없을 때,
    {
        head = node; //node를 head로 지정
        node->link = head; //원형 리스트이므로 node->link에 head 연결
    }
    else
    {
        node->link = head->link; // 노드 링크에 head->link값 연결(원형 리스트 이므로, head가 마지막 위치에 있고, head->link를 첫 번째 node->link에 연결)
        head->link = node; // head->link에 node 연결
    }

    return head; //head값 반환
}

ListNode *insert_last(ListNode *head, element value) //리스트 노드의 마지막에 값 추가
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode)); //리스트 노드에 동적 메모리 선언
    node->data = value; //노드 data 위치에 value값 저장
    if (head == NULL) //노드에 데이터가 없을 때,
    {
        head = node; //node를 헤드로 지정
        node->link = head; //node -> link를 head로 지정
    }
    else 
    {
        node->link = head->link; //node->link 에 head->link연결
        head->link = node; //head->link 에 node 연결
        head = node; //head = node 값 저장
    }

    return head; //head값 반환
}

ListNode *delete_first(ListNode *head) //첫 번째 노드 값을 지우는 함수
{
    ListNode *removed = NULL, *pre = NULL; //삭제할 노드의 데이터를 담을 removed와, 그 선행노드인 pre 선언
    pre = head; //pre 에 head 지정
    removed = pre->link; //removed 에 pre->link값 저장
    pre->link = removed->link; //pre->link 에 removed->link값 연결 (해당 과정을 통해 removed가 삭제되어도 바로 다른 노드와 연결)
    free(removed); //removed 메모리 해제를 통해서 노드 삭제

    return head; //head 값 반환
}

ListNode *delete_last(ListNode *head) //마지막 노드 값을 지우는 함수
{
    ListNode *removed = NULL, *pre = NULL; //삭제할 노드의 데이터를 담을 removed와, 그 선행노드인 pre 선언
    pre = head; //pre에 head 지정

    while (pre->link != head) //선행 노드의 link값이 head를 가르킬 때 까지 반복
        pre = pre->link; //링크를 타고 선행노드의 link값이 head를 가르킬 때 까지 이동

    head = pre; //pre 노드를 head로 지정
    removed = pre->link; //pre->link 값을 removed에 연결
    pre->link = removed->link; //pre->link 를 removed->link에 연결 (해당 과정을 통해 removed가 삭제되어도 바로 다른 노드와 연결)
    free(removed); //removed 메모리 해제를 통해 노드 삭제

    return head; //head값 반환
}

void print_list(ListNode *head) //리스트를 출력해주는 함수
{
    ListNode *p = head->link; //노드 p 에 head->link값 연결
    while (p != head) //p가 head일 때 까지 반복
    {
        printf("%d ->", p->data); //p의 데이터값 출력
        p = p->link; //링크를 타고 노드 이동
    }
    printf("%d ->", p->data); //리스트 출력
    p = p->link; //정상적으로 연결 됐는지 확인해주기 위해 한 번더 이동
    printf("%d ->", p->data); //정상적으로 원형 리스트가 구현되어 있는지 확인해주기 위해 한 번더 출력
    printf("\n");
}

int main(int argc, char *argv[])
{
    ListNode *head = NULL;
    printf("----------insert_first----------- \n"); //구분선
    for (int i = 0; i < 5; i++) //insert_first 함수를 반복해줄 반복문
    {
        head = insert_first(head, i); //insert_first 함수 호출
        print_list(head); //출력 함수 호출
    }
    printf("----------insert_last------------ \n"); //구분선
    head = insert_last(head, 10); //insert_last 함수 호출
    print_list(head); //출력 함수 호출
    printf("----------delete_first----------- \n"); //구분선
    head = delete_first(head); //delete_first 함수 호출
    print_list(head); //출력 함수 호출
    printf("----------delete_last------------ \n"); //구분선
    head = delete_last(head); //delete_last 함수 호출
    print_list(head); // 출력 함수 호출

    return 0; //프로그램 종료 
}