#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DlistNode {
    element data;
    struct DlistNode *llink;
    struct DlistNode *rlink;
} DlistNode;

void DLLinsert(DlistNode **h, element value)  //노드 추가 함수
{
    DlistNode *newNode = (DlistNode *)malloc(sizeof(DlistNode));  //새로 입력 해줄 노드 동적 메모리 선언
    newNode->data = value;                                        //새로운 노드에 데이터값 입력

    if ((*h) == NULL) {
        newNode->llink = NULL;  // 노드의 왼쪽 링크에 NULL값 저장
        newNode->rlink = *h;    //노드의 오른쪽에 이전 값 저장
        *h = newNode;           //헤드포인터에 새로운 노드 연결
    }

    else {
        newNode->llink = NULL;  // 새로운 노드의 좌측 링크를 이전 노드에 연결
        newNode->rlink = *h;    //새로운 노드의 우측 링크를 이전 노드의 우측 링크로 연결
        (*h)->llink = newNode;  // 이전 노드의 오른쪽 링크가 가르키는 곳의 왼쪽 링크를 새로운 노드에 연결
        *h = newNode;           // 이전 노드의 우측 링크에는 새로운 노드 위치
    }
}

void DLLinsert_pos(DlistNode **h) {
    int position;   //입력할 위치 변수 선언
    element value;  //입력할 데이터 변수 선언
    int k = 1;      //위치 비교를 위한 임시 k 선언

    printf("값을 넣을 위치를 입력하세요. : ");
    scanf("%d", &position);
    printf("데이터 값을 입력하세요. : ");
    scanf("%d", &value);

    DlistNode *newNode, *temp;                         //새로운 노드, 임시 노드 temp 선언
    newNode = (DlistNode *)malloc(sizeof(DlistNode));  //새로운 노드 동적 메모리 선언
    newNode->data = value;                             //새로운 노드에 데이터 값 입력

    if (position == 1) {            //첫 번째 위치에 값을 넣을 때,
        if ((*h) == NULL) {         //헤드 포인터가 NULL을 가리킬 때, (노드에 아무런 값이 없을 떄)
            newNode->llink = NULL;  //새로운 노드의 Llink를 NULL에 연결 (헤드 포인터에 연결되어 있는 값이 없으므로)
            newNode->rlink = *h;    //새로운 노드의 Rlink를 헤드포인터에 연결 (헤드 포인터가 NULL을 가리키고 있으므로)
            *h = newNode;           //헤드 포인터에 새로운 노드에 연결 (헤드값을 새로운 노드로 지정)
        } else {                    //헤드포인터가 NULL이 아닌 값을 가리킬 때, (노드에 기존 값이 있을 때)
            newNode->llink = NULL;  //새로운 노드의 Llink를 NULL에 연결 (헤드 포인터에 연결되어 있는 값이 없으므로)
            newNode->rlink = *h;    //새로운 노드의 Rlink를 헤드포인터에 연결 (헤드 포인터가 NULL을 가리키고 있으므로)
            (*h)->llink = newNode;  //헤드 포인터의 Llink를 새로운 노드에 연결 (헤드 노드로 지정 해주기 위해서)
            *h = newNode;           //헤드 포인터에 새로운 노드에 연결 (헤드값을 새로운 노드로 지정)
        }
        return;
    }

    temp = (*h);                                         // 템프에 헤드포인터 입력
    while ((k < position - 1) && temp->rlink != NULL) {  //해당 위치까지 이동하는 반복문
        temp = temp->rlink;                              //링크를 따라 이동
        k++;                                             //현재 위치와 입력된 위치값 비교를 위해 이동할 때마다 임시변수 k + 1
    }

    if (temp->rlink == NULL) {         // 끝단까지 이동한 뒤, 해당 값을 만나지 못하고 NULL을 만났을 때,
        newNode->rlink = temp->rlink;  //새로운 노드의 Rlink를 temp의 Rlink와 연결 (추가 노드의 Rlink값에 NULL연결)
        newNode->llink = temp;         //새로운 노드의 Llink 를 temp에 연결 (추가 노드를 마지막 노드에 앞 링크와 연결 하기 위해서)
        temp->rlink = newNode;         // temp의 Rlink를 새로운 노드와 연결
    } else {                           //입력된 위치를 발견 했을 때,
        newNode->rlink = temp->rlink;  //새로운 노드의 Rlink를 temp의 Rlink에 연결
        newNode->llink = temp;         //새로운 노드의 Llink 를 temp에 연결
        temp->rlink->llink = newNode;  // temp Rlink의 Llink를 새로운 노드에 연결 (특정 위치의 추가 노드를 이전 노드들에 앞뒤 링크들과 연결 하기 위해서)
        temp->rlink = newNode;         // temp의 Rlink를 새로운 노드와 연결
    }
}

void DLLdelete_pos(DlistNode **h)  //삭제 함수
{
    DlistNode *pre, *removed;  //선행노드 pre와, 삭제할 노드 removed 선언
    int k = 2;                 // pre노드가 존재하기 때문에, 2번째 부터 비교를 위해 insert와는 달리 k를 2로 초기화
    int pos = 0;               //위치값을 저장할 pos 선언
    printf("몇 번째 데이터를 삭제하시겠습니까? : ");
    scanf("%d", &pos);
    pre = *h;  // pre에 헤드포인터 저장

    if (pos <= 0)  // pos가 0보다 작거나 같을 때,
    {
        printf("잘못된 위치입니다. \n");
        exit(0);
    }

    else if (pos == 1) {                   // pos가 1일 때,
        if (pre->rlink == NULL) {          // pos가 1이고, 해당 노드에 데이터가 1개 밖에 없을 때,
            free(*h);                      //헤드포인터 메모리 해제를 통해 삭제,
            *h = NULL;                     //헤드포인터에 NULL 연결
        } else {                           // pos가 1이고, 해당 노드에 데이터가 2개 이상 존재할 때,
            removed = pre;                 // removed에 pre 저장
            removed->rlink->llink = NULL;  // removed Rlink의 Llink를 NULL에 연결 (첫 번째 값을 삭제시킬 것이기 때문에 두 번째 값의 Llink는 NULL을 가리킴)
            *h = removed->rlink;           //헤드포인터에 removed Rlink 연결 (첫 번쨰 값 삭제 이후 두 번째 값이 헤드노드가 되기 때문에)
        }
    }

    else if (pre->rlink == NULL) {  //리스트에 아무런 값이 없을 때
        printf("No element in the list!!\n");
        exit(0);
    }

    else {                     // pos 값이 2 이상일 때,
        removed = pre->rlink;  // removed에 pre->Rlink 연결 (pre를 포인터 헤드로 초기화 해두었기 때문에, 일단 첫 번째 노드를 삭제할 노드로 초기화)

        while (removed->rlink != NULL && k < pos) {  // removed의 Rlink가 NULL이 아니면서, k값이 pos값 보다 작을 때 반복
            k++;
            pre = removed;             // pre에 removed값 저장
            removed = removed->rlink;  // removed->Rlink값을 removed에 넣으면서 후행노드로 이동
        }
        if (k == pos) {                       // k값과 pos값이 만났을 때,
            pre->rlink = removed->rlink;      // pre의 Rlink값에 removed의 Rlink를 연결함으서, 삭제할 노드의 앞노드 Rlink 연결
            removed->rlink = removed->llink;  // removed의 Rlink를 removed의 Llink에 연결함으로서, 삭제 노드의 뒷노드 Llink 연결
        }
    }
    free(removed);  // removed 메모리 해제를 통한 삭제
}
void print_dlist(DlistNode *head) {          //노드 출력을 위한 함수
    DlistNode *p;                            //포인터 p를 선언
    for (p = head; p != NULL; p = p->rlink)  // p=phead의 우측 링크값이고, p가 phead가 아닐 때, p에 p의 우측 링크를 타고 계속 이동하며 출력할 수 있는 반복문 설정
        printf("<-| |%d| |->", p->data);     // p의 데이터값 출력
    printf("\n");
}

int main(int argc, char *argv[]) {
    DlistNode *head = NULL;  //헤드 초기화

    for (int i = 0; i < 5; i++) {  //함수 호출 반복문
        DLLinsert(&head, i);       // Insert함수 호출
        print_dlist(head);         // Print 함수 호출
    }

    printf("----------------insert_pos----------------\n");  //구분선
    DLLinsert_pos(&head);                                    // Insert_Pos 함수호출
    print_dlist(head);                                       // Print 함수 호출

    printf("----------------delete_pos----------------\n");  //구분선
    DLLdelete_pos(&head);                                    // Delete_Pos 함수 호출
    print_dlist(head);                                       // Print 함수 호출
}