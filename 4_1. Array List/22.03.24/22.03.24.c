// ArrayList

#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ArrayList {
    int capacity;  // Array의 크기를 저장해줄 변수 capacity 선언
    int no;        // Array의 데이터 개수를 설정할 no 선언
    int* array;    //데이터를 저장할 배열 선언
} ArrayList;

ArrayList* create(ArrayList* L) {  // ArrayList를 생성해주는 함수
    printf("set for size : ");
    int size = 0;        //설정할 크기 변수 size 선언 후, scanf를 통해 크기 입력
    scanf("%d", &size);  // size를 입력받아 malloc을 통해 array에 동적 메모리 할당
    L->capacity = size;
    L->array = (int*)malloc(sizeof(L->capacity));
    return L;
}

void resizing(ArrayList* L) {
    L->capacity *= 10;
    L->array = (int*)realloc(L->array, sizeof(L->capacity) * 10);
}

void error(const char* message) {  //에러 메시지 출력 함수
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init(ArrayList* L) {  // Array List 개수 초기화
    L->no = 0;
}

int is_Empty(ArrayList* L) {  // Array가 비어있을 경우
    return L->no == 0;
}

int is_Full(ArrayList* L) {  // Array가 가득찬 경우
    if(L->no == L->capacity)
        resizing(L);
    return L->no == L->capacity;
}

int get_entry(ArrayList* L, int pos) {  // index의 위치가 음수이거나, 원소의 개수보다 클 경우 출력
    if (pos < 0 || pos >= L->no)
        error("위치 오류");
    return L->array[pos];
}

void print_list(ArrayList* L) {  //입력된 내용을 출력하는 함수
    for (int i = 0; i < L->no; i++)
        printf("%d->", L->array[i]);
    printf("\n");
}

void insert(ArrayList* L, int pos, element item) {  //데이터를 입력하는 함수
    if (!is_Full(L) && (pos >= 0) && (pos <= L->no)) {
        for (int i = (L->no - 1); i >= pos; i--)
            L->array[i + 1] = L->array[i];
        L->array[pos] = item;
        L->no++;
    }
}

void insert_last(ArrayList* L, element item) {  //마지막 위치에 데이터를 삽입하는 함수
    if (L->no >= L->capacity)
        error("리스트 오버플로우");
    L->array[L->no++] = item;
}

int F_delete(ArrayList* L, int pos) {  //첫 번째 데이터를 삭제하는 함수
    int item;

    if (pos < 0 || pos >= L->no)
        error("위치 오류");
    item = L->array[pos];

    for (int i = pos; i < (L->no - 1); i++)
        L->array[i] = L->array[i + 1];
    L->no--;
    return item;
}

void call_Function(ArrayList* L) {  //함수 호출을 위한 함수
    create(L);
    init(L);
    for (int i = 0; i < 9; i++) {
        insert(L, i, i * 10);
        print_list(L);
    }
    insert_last(L, 1000);
    F_delete(L, 0);
    print_list(L);
}

int main(int argc, char* argv[]) {
    ArrayList list;
    call_Function(&list);
    return 0;
}