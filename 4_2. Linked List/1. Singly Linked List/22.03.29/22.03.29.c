#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode //노드 타입
{
    element data;          //원소
    struct ListNode *link; //원소가 들어있는 위치 포인터
} ListNode;

ListNode *insert_first(ListNode *head, int value) //가장 앞쪽에 넣어주는 함수
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode)); // 동적 메모리 할당을 통해 새로운 노드 p 생성
    p->data = value;                                    // p->data에 데이터 필드 값을 저장
    p->link = head;                                     //헤드 포인터의 값을 복사
    head = p;                                           //헤드 포인터 변경
    return head;                                        //헤드 포인터 반환
}

ListNode *insert_last(ListNode *head, element value) //가장 마지막에 넣어주는 함수 (insert와 작동 방식은 동일하나 마지막에 들어가야 하므로 리스트의 끝단까지 이동 후, 작동)
{
  ListNode *p = (ListNode *)malloc(sizeof(ListNode)); //동적 메모리 할당을 통해 새로운 노드 p 생성
  p = head; //p 에 헤드 포인터
  while(p->link != NULL)
  p = p->link; //링크의 끝 부분까지 이동
  ListNode *NewNode = (ListNode *)malloc(sizeof(ListNode)); //새로운 노드 생성
    p->link = NewNode; //새로운 노드 값을 복사
    NewNode->data = value; //새로운 노드에 데이터를 입력
    NewNode->link = NULL; //새로운 노드의 링크포인터 -> NULL

    return head; //헤드 포인터 반환
}

void print_list(ListNode *head) //리스트를 프린트해주는 함수
{
    for (ListNode *p = head; p != NULL; p = p->link) //리스트 한 칸 한 칸 이동하면서 출력해주는 반복문
        printf("%d ->", p->data); 
    printf("NULL \n");
}

int main(int argc, char *argv[])
{
    ListNode *head = NULL; //헤드값 초기화

    for (int i = 20; i >= 0; i--) //입출력 과정 반복문
    {
        head = insert_first(head, i); //insert 함수 호출
        print_list(head); //리스트 출력 함수 호출
    }

    head = insert_last(head,100); //리스트의 마지막부분에 입력해줄 함수 호출
    print_list(head); //마지막 부분에 입력 후, 출력 값

    return 0;
}