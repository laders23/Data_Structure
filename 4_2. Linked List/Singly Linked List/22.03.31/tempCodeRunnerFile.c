#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode // 리스트 노드 생성
{
    element data;
    struct ListNode *link;
} ListNode;

ListNode *insert_first(ListNode *head, int value) //리스트의 첫부분에 입력하는 함수
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode)); // 동적 메모리 할당을 통해 새로운 노드 p 생성
    p->data = value;                                    // p->data에 데이터 필드 값을 저장
    p->link = head;                                     //헤드 포인터의 값을 복사
    head = p;                                           // 헤드 포인터 변경
    return head;                                        //헤드 포인터 반환
}

ListNode *insert_last(ListNode *head, element value) //가장 마지막에 넣어주는 함수 (insert와 작동 방식은 동일하나 마지막에 들어가야 하므로 리스트의 끝단까지 이동 후, 작동)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode)); //동적 메모리 할당을 통해 새로운 노드 p 생성
    p = head;                                           // p 에 헤드 포인터
    while (p->link != NULL)
        p = p->link;                                          //링크의 끝 부분까지 이동
    ListNode *NewNode = (ListNode *)malloc(sizeof(ListNode)); //새로운 노드 생성
    p->link = NewNode;                                        //새로운 노드 값을 복사
    NewNode->data = value;                                    //새로운 노드에 데이터를 입력
    NewNode->link = NULL;                                     //새로운 노드의 링크포인터 -> NULL

    return head; //헤드 포인터 반환
}

void print_list(ListNode *head) //리스트 프린트 함수
{
    for (ListNode *p = head; p != NULL; p = p->link) //리스트를 차례로 읽어 가는 반복문
        printf("%d->", p->data);
    printf("NULL \n");
}

ListNode *delete_first(ListNode *head) //첫 번째 노드에 들어갈 값을 제거 후, 뒷 노드를 헤드로 지정해서 앞으로 당겨옴
{
    ListNode *removed; //삭제 할 노드 선언
    if (head == NULL)  // ListNode에 아무런 값이 없을 때,
    {
        printf("No element in the list!!\n");
        exit(0);
    }
    else
    {                         // ListNode에 값이 있을 떄,
        removed = head;       // removed에 헤드값 복사
        head = removed->link; //헤드에 removed의 링크값 입력.
        free(removed);        //메모리 해제를 통한 removed 삭제.
    }

    return head;
}

ListNode *delete_last(ListNode *head) //마지막 노드의 값을 제거하는 함수
{
    ListNode *removed; //삭제할 노드 선언
    ListNode *pre;     //선행 노드 선언

    if (head == NULL) // Linked List가 비어있을 때,
    {
        printf("No element in the list!!\n");
        exit(0);
    }
    else if (head->link == NULL)
    {
        free(head);
        head = NULL;
    }
    else
    {
        pre = head;                   //삭제할 노드의 선행 노드의 값을 첫 번째 노드로 지정(선행노드에 head값 복사)
        removed = head->link;         //삭제할 노드를 두 번째 노드로 지정 (removed 에 Head의 link를 복사)
        while (removed->link != NULL) // removed의 링크 타고 NULL직전까지 이동
        {
            pre = removed;
            removed = removed->link;
        }
        free(removed);    //메모리 해제를 통한 노드 삭제
        pre->link = NULL; //선행노드의 링크값 NULL 지정
    }
    return head;
}

ListNode *search_list(ListNode *head, element x) // NodeList를 검색해주는 함수
{
    ListNode *p = head;
    int count = 0; //몇 번째에 위치하고 있는지 저장
    x = 0; //검색할 값
    printf("검색할 값을 입력하십시오. : ");
    scanf("%d", &x);

    while (p != NULL) //리스트의 끝까지 이동하며 데이터 검색
    {
        count++;
        if (p->data == x) //데이터와 입력값이 같을 경우 p를 반환
        {
            printf("%d 번째에 입력한 값인 %d 가 있습니다. \n", count, x);
            return p;
        }
        p = p->link;
    }
    printf("해당 값을 찾을 수 없습니다. \n"); // 해당 값을 찾지 못했을 경우
    return NULL;
}

ListNode *reverse(ListNode *head) // ListNode를 역순으로 바꿔주는 함수
{
    ListNode *p, *q, *r; // p = 역순으로 만들어 줄 리스트, q = 역순으로 만들 노드, r = 역순으로 된 리스트

    p = head;
    q = NULL;
    while (p != NULL)
    {
        r = q; // r = q, q = p를 차례로 따라감.
        q = p;
        p = p->link;
        q->link = r; // q의 링크방향을 r로 바꿔줌.
    }

    return q;
}

int main(int argc, char *argv[])
{
    ListNode *head = NULL;     // insert,delete를 수행하기 위한 head 노드 생성
    ListNode *rev_head = NULL; // reverse 함수 구현을 위한 추가 노드 생성

    for (int i = 0; i < 5; i++) //노드값 입출력 반복 함수
    {
        head = insert_first(head, i); //노드값 입력
        print_list(head);             //노드값 출력
    }
    head = insert_last(head, 10); //마지막 노드에 10을 추가하는 함수
    print_list(head);             //노드 출력 함수
    head = delete_last(head);     //마지막 노드를 삭제하는 함수
    print_list(head);             //노드 출력 함수
    printf("\n------------------------------\n");
    search_list(head, 0); // list 검색 함수
    printf("------------------------------");
    printf("\n 역순 리스트 \n");

    rev_head = reverse(head); //노드 순서를 뒤집어주는 함수
    print_list(rev_head);     //뒤집힌 노드를 출력해주는 함수

    return 0;
}