#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int data;
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

void print_list(ListNode *head) //리스트 프린트 함수
{
    for (ListNode *p = head; p != NULL; p = p->link) //리스트를 차례로 읽어 가는 반복문
        printf("%d->", p->data);
    printf("NULL \n");
}

ListNode *insert_pos(ListNode *head, int pos) //입력해준 위치에 새로운 노드를 넣어주는 함수
{
    int value = 0;
    int k = 1;                                                // k 변수 선언 = 위치 확인 용
    ListNode *p = NULL, *q = NULL;                            // 해당 노드 위치의 데이터를 잠시 보관해줄 임시 노드 p, q 선언
    ListNode *NewNode = (ListNode *)malloc(sizeof(ListNode)); //새로운 노드 동적메모리 선언
     p = head;                                                 // p에 head 저장
    printf("몇 번째 위치에 넣으시겠습니까? : ");
    scanf("%d", &pos);
    printf("어떤 값을 입력하시겠습니까? : ");
    scanf("%d", &value);
    NewNode->data = value;                                    //새로운 노드에 데이터값 저장
    
    if (pos <= 0) // pos가 0보다 작거나 같을 때,
    {
        printf("잘못된 위치입니다. \n");
        exit(0);
    }

    else if (pos == 1) // pos가 1일 때,
    {
        NewNode->link = p; //새로운 노드의 링크를 p에 연결
        head = NewNode;    //헤드에 새로운 노드를 저장
    }

    else // pos가 1보다 클 때,
    {
        while (p != NULL && k < pos) //새로운 노드를 저장할 pos 위치까지 이동시켜줄 반복문
        {
            k++; //k를 순차적으로 증가
            q = p; // p의 값을 q에 복사
            p = p->link; //p에 p->link를 통해 다음 노드로 이동
        }
        if (p == NULL) //리스트 노드에 아무런 데이터가 존재하지 않을 때,
        {
            q->link = NewNode; //q의 링크를 새로운 노드로 선언해주고,
            NewNode->link = NULL; //새로운 노드의 링크를 널값으로 지정
        }
        else //pos위치를 만나서 그 자리에 새로운 노드를 넣을 때,
        {
            q->link = NewNode; //q의 링크에 새로운 노드 연결
            NewNode->link = p; //새로운 노드의 링크는 p에 연결
        }
    }
    return head; //헤드값 반환
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
    else if (head->link == NULL) //head의 link 값이 NULL일 때,
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
    return head; //head값 반환
}

ListNode *delete_pos(ListNode *head, int pos) //입력한 pos위치의 노드를 지우는 함수
{

    ListNode *removed, *pre; //선행 노드 pre와 삭제할 노드 removed 선언

    int k = 2; //pre노드 뒤에 removed가 따라가기 때문에, 2로 선언

    printf("몇 번째 데이터를 삭제하시겠습니까? : ");
    scanf("%d", &pos);

    if (pos <= 0) //pos가 0보다 작거나 같을 때,
    {
        printf("잘못된 위치입니다. \n"); 
        exit(0);
    }

    else if (pos == 1) //pos가 1일 때,
        {
            removed = head; //removed에 head 저장
            head = removed->link; //head에 removed->link값을 넣어줌, (delete_first 함수와 구현 방식 동일)
            free(removed);
        }

    else if (head == NULL) //리스트에 아무런 값이 없을 때
    {
        printf("No element in the list!!\n");
        exit(0);
    }
    else if (head->link == NULL) //head->link 값이 NULL일 떄 : 데이터가 1개 밖에 없을 때,
    {
        free(head);
        head = NULL;
    }

    else
    {
        pre = head; //선행노드에 head값 저장
        removed = head->link; //삭제할 노드에 head->link 연결
        while (removed->link != NULL && k < pos) //removed의 link가 NULL이 아니면서, k값이 pos값 보다 작을 때 반복
        {
            k++;
            pre = removed; //pre에 removed값 저장
            removed = removed->link; //removed->link값을 removed에 넣으면서 후행노드로 이동
        }

        if (k == pos) //k값과 pos값이 만났을 때,
        {
            pre->link = removed->link; //pre의 link값에 removed의 link를 연결하고 removed함수 메모리 해제를 통한 삭제
            free(removed);
        }
    }
    return head;
}

void deleteLinkedList(ListNode *head) //LinkedList를 아예 삭제하는 함수
{
    ListNode *auxilaryNode, *iterator; //임시 노드 2개 선언
    iterator = head; //head값 저장
    while (iterator) //iterator 값이 없을 때 까지 반복
    {
        printf("삭제할 노드의 데이터 : %d\n", iterator->data); //삭제할 노드의 데이터 확인 함수
        auxilaryNode = iterator->link; //auxilaryNode에 iterator->link값을 통해 뒷 노드로 이동
        free(iterator); //메모리 반환을 통해 iterator 삭제
        iterator = auxilaryNode; // iterator에 다시 auxilaryNode를 넣어줌으로서 해당 과정 반복을 통해 전체 삭제
    }
    head = NULL; //head에 NULL을 저장하면서 해당 노드 전체 삭제
}

int main(int argc, char *argv[])
{
    ListNode *head = NULL;

    printf("-----------insert_first-----------\n");
    for (int i = 0; i < 5; i++)
    {
        head = insert_first(head, i); //리스트에 노드 추가를 위한 함수
        print_list(head);
    }
    printf("-----------insert_position-----------\n");
    head = insert_pos(head, 0); //특정 위치에 노드를 삽입시켜주는 함수
    print_list(head);
    printf("-----------delete_position-----------\n");
    head = delete_pos(head, 0); //특정 위치의 노드를 삭제시키는 함수
    print_list(head);
    printf("-----------deleteLinkedList-----------\n");
    deleteLinkedList(head); // LinkedList 전체 삭제 함수

    return 0;
}