#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max 10000
#define element int

typedef struct SListNode
{ // Singly Linked List 구조체를 생성
    element data;
    struct SListNode *link;
} SListNode;

typedef struct DListNode
{ // Doubly Linked List 구조체를 생성
    int data;
    struct DListNode *rlink;
    struct DListNode *llink;
} DListNode;

void insertion_array(int Array[max])
{ // Array에 0부터 9999까지의 데이터를 입력하는 함수
    clock_t start = clock();
    for (int i = 0; i < max; i++)
        Array[i] = i;
    clock_t end = clock();
    printf("insertion 실행시간(Array) : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC);
}

void random_access_for_read_Array(int Array[max])
{ // Array의 무작위 데이터를 더하는 함수
    clock_t start = clock();
    double sum = 0;
    for (int i = 0; i < 1000; i++)
        sum += Array[rand() % max]; // rand 함수를 통한 난수 생성, max 값인 10000으로 나눈 나머지값인 0부터 9999까지의 난수를 index값으로 받아 무작위 데이터를 선정하고 sum에 더해줌
    printf("Array_sum = %lf \n", sum);
    clock_t end = clock();
    printf("read 실행시간(Array) : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC);
}

void random_access_for_deletion_Array(int Array[max])
{ // Array의 데이터를 삭제하는 함수
    clock_t start = clock();
    for (int i = 0; i < 1000; i++)
        Array[rand() % max] = -1; // rand 함수를 통해 난수 생성, max 값인 10000으로 나눈 나머지 값인 0부터 9999까지의 난수를 index값으로 받아 무작위 데이터를 선정하고 -1로 대치
    clock_t end = clock();
    printf("deletion 실행시간(Array) : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC);
}

void Array_function(int Array[max])
{ //위의 Array관련 함수를 실행시켜줄 함수 호출 (main 함수 정리용)
    insertion_array(Array);
    random_access_for_read_Array(Array);
    random_access_for_deletion_Array(Array);
}

SListNode *insertion_Singly_Linked_List(SListNode *h, element value)
{ // Singly Linked List에 0부터 9999까지 순차적으로 삽입하는 함수
    SListNode *p = (SListNode *)malloc(sizeof(SListNode));
    p->data = value;
    p->link = h;
    h = p;
    return h;
}

SListNode *random_access_for_read_Singly_LinkedList(SListNode *h)
{ //무작위로 선정된 위치값의 데이터를 더해주는 함수
    clock_t start = clock();

    double sum = 0;
    int pos = 0; //무작위 위치를 받아줄 pos 변수 생성
    SListNode *p = NULL;
    for (int i = 0; i < 1000; i++)
    {
        p = h;
        int k = 0;          // pos값과 비교 및 이동을 위한 변수 k 생성
        pos = rand() % max; // rand 함수를 이용해 만들어진 난수를 max로 나눈 나머지값인 0부터 9999까지의 무작위 수를 pos에 저장
        while (k < pos)
        {                       // k가 pos보다 작을 때, 링크를 타고 계속해서 뒷 노드로 이동
            p = p->link;        // p = p가 가리키는 링크를 타고 계속해서 이동
            k++;                //반복 할 때마다, k+1 실행
            if (k == pos)       // while 문을 계속해서 돌다가 k와 pos의 값이 같아질 경우
                sum += p->data; // sum에 p의 data값을 더해주고 탈출
        }
    }
    printf("Singly_sum = %lf \n", sum);
    clock_t end = clock();

    printf("read 실행시간(Singly Linked List) : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC);
    return h; //헤더값 반환
}

SListNode *random_access_for_Deletion_singly_LinkedList(SListNode *h)
{
    clock_t start = clock();
    int pos, temp = max - 1;  //한 개의 노드가 빠진 이후에 갯수를 하나씩 줄여나가면서 해야하기 때문에 임시변수 temp 선언 후, max값인 10000으로 초기화
    SListNode *removed, *pre; //선행 노드 pre와 삭제할 노드 removed 선언

    for (int i = 0; i < 1000; i++)
    {
        int k = 2;                 // pre노드 뒤에 removed가 따라가기 때문에, 2로 선언
        pos = (rand() % temp) + 1; // rand함수로 만든 난수를 temp 값으로 나눈 나머지값을 pos에 저장, 이 때, 경우의 수를 줄이기 위해 매 회 temp값은 1씩 줄이고, pos가 0이 됨을 방지하기 위해 temp값을 9999로 설정하고 +1
        if (pos == 1)              // pos가 1일 때,
        {
            removed = h;       // removed에 head 저장
            h = removed->link; // head에 removed->link값을 넣어줌
            temp--;            // 1회 돌고 난 뒤, temp값 감소를 통해 경우의 수 줄여줌.
            free(removed);     // free 선언을 통해 removed값을 제거
        }

        else
        {
            pre = h;                                 //선행노드에 head값 저장
            removed = h->link;                       //삭제할 노드에 head->link 연결
            while (removed->link != NULL && k < pos) // removed의 link가 NULL이 아니면서, k값이 pos값 보다 작을 때 반복
            {
                k++;
                pre = removed;           // pre에 removed값 저장
                removed = removed->link; // removed->link값을 removed에 넣으면서 후행노드로 이동
            }

            if (k == pos) // k값과 pos값이 만났을 때,
            {
                pre->link = removed->link; // pre의 link값에 removed의 link를 연결하고 removed함수 메모리 해제를 통한 삭제
                temp--;                    //위와 마찬가지로 1회 수행 후 temp값 -1을 통해 경우의 수를 줄여줌
                free(removed);             // free 선언을 통해 removed값 제거
            }
        }
    }
    clock_t end = clock();
    printf("deletion 실행시간(Singly Linked List) : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC);
    return h;
}

SListNode *insertion_iteration_Singly_Linked_List(SListNode *Shead)
{ // Singly 함수에서 head값을 return 해주지 않을 경우 계속해서 같은 위치에 저장됨을 방지하기위한 함수 (main문에 for문 없이 깔끔하게 정리하기 위한 함수)
    clock_t start = clock();
    for (int i = 0; i < max; i++)
        Shead = insertion_Singly_Linked_List(Shead, i); //앞서 사용한 insertion_Singly_Linked_List 함수를 반복 호출
    clock_t end = clock();
    printf("insertion 실행시간(Singly Linked List : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC);
    return Shead;
}

DListNode *insertion_Doubly_Linked_List(DListNode **h, element value)
{                                                                // Doubly Linked List 에서 0~9999까지의 값을 넣는 함수
    DListNode *newNode = (DListNode *)malloc(sizeof(DListNode)); //입력 될 새로운 노드 생성
    newNode->data = value;
    if ((*h) == NULL)
    {                          //헤드 포인터가 가르키는 곳의 값이 NULL일 때,
        newNode->llink = NULL; //새로운 노드의 Llink에 NULL지정
        newNode->rlink = *h;   //새로운 노드의 Rlink에 헤드포인터 지정
        *h = newNode;          //헤드 포인터가 가르키는 곳을 새로운 노드로 설정
    }

    else
    { // 순차적으로 넣는 함수이기 때문에, 위와 동일하게 작동하지만, 이전 노드의 링크를 옮겨주는 작업이 추가
        newNode->llink = NULL;
        newNode->rlink = *h;
        (*h)->llink = newNode; //헤드 포인터가 가르키는 곳의 Llink를 새로운 노드로 설정
        *h = newNode;
    }
    return *h;
}

DListNode *random_access_for_read_Doubly_LinkedList(DListNode **h)
{ // Doubly Linked List의 무작위한 위치 값을 더해주는 함수
    clock_t start = clock();
    double sum = 0;
    int pos = 0;

    DListNode *p = NULL; //헤드포인터를 저장해서 사용할 임시 노드 선언

    for (int i = 0; i < 1000; i++)
    {
        int k = 0; // pos 값 비교를 위한 임시변수 k 선언
        p = (*h);
        pos = rand() % max; // rand함수를 이용해서 난수를 생성하고, max값인 10000으로 나눈 나머지값인 0에서 9999까지의 수를 pos에 저장
        while (k < pos)
        {                 // k가 pos보다 작을 때,
            p = p->rlink; // p의 Rlink를 타고 계속해서 이동
            k++;          // pos값 비교를 위한 임시 변수 k+1
            if (k == pos)
            {                   // k와 pos가 같을 경우
                sum += p->data; //해당 위치의 데이터값을 sum에 더해줌
            }
        }
    }
    printf("Doubly_sum = %lf \n", sum);
    clock_t end = clock();
    printf("read 실행시간(Doubly Linked List : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC);
    return *h;
};

DListNode *random_access_for_Deletion_Doubly_LinkedList(DListNode **h)
{
    clock_t start = clock();
    int temp = max - 1; // temp가 10000일 경우 pos값을 설정하는 rand에서 10000이 되는 경우가 생겨서 0부터 9999까지의 범위를 초과함. 따라서, 9999로 설정
    int count = 0;
    DListNode *pre, *removed; //선행노드 pre와, 삭제할 노드 removed 선언
    for (int i = 0; i < 1000; i++)
    {
        int k = 2;                     // pre노드가 존재하기 때문에, 2번째 부터 비교를 위해 insert와는 달리 k를 2로 초기화
        int pos = (rand() % temp) + 1; // temp값으로 나눈 나머지가 0에서 9998까지 이므로 + 1
        pre = *h;
        if (pos == 1)
        {                                 // pos가 1일 때,
            removed = pre;                // removed에 pre 저장
            removed->rlink->llink = NULL; // removed Rlink의 Llink를 NULL에 연결 (첫 번째 값을 삭제시킬 것이기 때문에 두 번째 값의 Llink는 NULL을 가리킴)
            *h = removed->rlink;          //헤드포인터에 removed Rlink 연결 (첫 번쨰 값 삭제 이후 두 번째 값이 헤드노드가 되기 때문에)
            temp--;                       // temp-1을 통해 경우의 수 1회 줄여줌.
        }
        else
        {                         // pos 값이 2 이상일 때,
            removed = pre->rlink; // removed에 pre->Rlink 연결 (pre를 포인터 헤드로 초기화 해두었기 때문에, 일단 첫 번째 노드를 삭제할 노드로 초기화)

            while (removed->rlink != NULL && k < pos)
            { // removed의 Rlink가 NULL이 아니면서, k값이 pos값 보다 작을 때 반복
                k++;
                pre = removed;            // pre에 removed값 저장
                removed = removed->rlink; // removed->Rlink값을 removed에 넣으면서 후행노드로 이동
            }
            if (k == pos)
            {                                    // k값과 pos값이 만났을 때,
                pre->rlink = removed->rlink;     // pre의 Rlink값에 removed의 Rlink를 연결함으서, 삭제할 노드의 앞노드 Rlink 연결
                removed->rlink = removed->llink; // removed의 Rlink를 removed의 Llink에 연결함으로서, 삭제 노드의 뒷노드 Llink 연결
            }
            temp--;
        }
        free(removed); // removed 메모리 해제를 통한 삭제
    }
    clock_t end = clock();
    printf("deletion 실행시간(Doubly Linked List) : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC);
    return *h;
}

DListNode *insertion_iteration_Doubly_Linked_List(DListNode **Dhead)
{ //헤더값을 반환하고 반복시켜주는 함수
    clock_t start = clock();
    for (int i = 0; i < max; i++)
        insertion_Doubly_Linked_List(Dhead, i); // Doubly Linked List 생성 함수 호출
    clock_t end = clock();
    printf("insertion 실행시간(Doubly Linked List) : %lfms \n", (double)(end - start) / (double)CLOCKS_PER_SEC);
    return *Dhead;
}

int main(int argc, char *argv[])
{
    int Array[max];
    SListNode *Shead = NULL; // Singly Linked List 헤드 선언
    DListNode *Dhead = NULL; // Doubly Linked List 헤드 선언
    srand(time(NULL));       //시드값을 시간으로 설정해 좀 더 확실한 난수가 나올 수 있도록 하는 srand

    printf("=====================insertion 실행 Array VS Singly Linked List=====================\n");
    Array_function(Array);                                       // Array관련 함수를 호출해주는 함수
    Shead = insertion_iteration_Singly_Linked_List(Shead);       // Singly Linked List 생성 함수 호출
    Shead = random_access_for_read_Singly_LinkedList(Shead);     // Singly Linked List 랜덤 덧셈 함수 호출
    Shead = random_access_for_Deletion_singly_LinkedList(Shead); // Singly Linked List 랜덤 삭제 함수 호출

    printf("=====================insertion 실행 Array VS Doubly Linked List=====================\n");
    Array_function(Array);                                        // Array관련 함수를 호출해주는 함수
    Dhead = insertion_iteration_Doubly_Linked_List(&Dhead);       // Doubly Linked List 생성 함수 호출
    Dhead = random_access_for_read_Doubly_LinkedList(&Dhead);     // Doubly Linked List 랜덤 덧셈 함수 호출
    Dhead = random_access_for_Deletion_Doubly_LinkedList(&Dhead); // Doubly Linked List 랜덤 삭제 함수 호출
    return 0;
}