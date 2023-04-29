#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count = 0;

struct addressBook
{
    char name[10]; //이름
    char phone[15]; //전화번호
    char addr[50]; //주소
    char birthday[8]; //생일
} aB[50]; // 구조체 이름

void list(void) //주소록의 정보를 확인하는 함수
{
    if (count == 0) //count가 0 일 때, 데이터가 등록되기 이전이라는 뜻이므로, 아래와 같이 출력.
        printf("등록된 데이터가 없습니다. \n");
    
    else{
        printf("\n이름\t전화번호\t주소\t생일 \n"); //count가 1 이상일 경우 데이터 출력을 위해 종류 먼저 출력
        printf("---------------------------------------\n");
        for (int i = 0; i < count; i++) //count 개수에 따라 구조체 배열의 개수가 몇 개인지 알 수 있기 떄문에, 해당 인덱스 값까지 반복실행
            printf("%s\t%s\t%s\t%s \n", aB[i].name, aB[i].phone, aB[i].addr, aB[i].birthday); //이름,번호,주소,생일 순으로 출력.
    }
}

void append(void) //주소록에 추가하는 함수
{
    printf("추가할 이름 : "); 
    scanf("%s", aB[count].name); // 이름입력 , 구조체 배열 인덱스값에 count입력 , 계속해서 새로운 값이 들어갈 것이기 때문에
    printf("추가할 전화번호 : ");
    scanf("%s", aB[count].phone); // 전화번호 입력
    printf("추가할 주소 : ");
    scanf("%s",aB[count].addr); // 주소 입력
    printf("추가할 생일 : ");
    scanf("%s",aB[count].birthday); // 생일 입력
    count++; //해당 함수가 끝날 때 마다 입력값이 추가되므로 count + 1
}

void search() // 주소록 검색 함수
{
    char name[10]; //임시로 이름을 받아줄 name 선언

    printf("검색할 이름 : ");
    scanf("%s",name);
    if(count == 0) //count가 0 일때에는, 입력된 데이터값이 없다는 뜻이므로, 아래와 같이 출력.
        printf("등록된 데이터가 없습니다. \n");
    for(int i = 0; i<count; i++){ //count값 만큼 구조체 배열 내의 데이터가 할당되어 있기 때문에 0부터 count-1(i<count)까지 실행.
        if(strcmp(name,aB[i].name) == 0){ //임시로 이름을 받아줄 name과 구조체 aB[i].name의 값을 비교하고 일치하면 0을 출력하는 strcmp함수 이용, 참일경우 아래와 같이 출력 후 브레이크로 for문 종료
            printf("%s\t%s\t%s\t%s \n", aB[i].name, aB[i].phone, aB[i].addr, aB[i].birthday);
            break;
        }
        else if(i+1 == count) //데이터 값은 있지만 일치하는 결과가 없는 경우 출력.
            printf("해당 이름으로 등록된 데이터가 없습니다. \n");
    }
}
void del(void) //주소록 삭제 함수
{
    char name[10]; //임시로 이름을 저장할 name 선언
    int i, j;
    printf("삭제할 이름 : ");
    scanf("%s", name);

    if(count == 0) //등록된 데이터가 없을 경우
        printf("등록된 데이터가 없습니다. \n");

    for (i = 0; i < count; i++) //count값 만큼 구조체 배열 내의 데이터가 할당되어 있기 때문에 0부터 count-1(i<count)까지 실행.
    {
        if (strcmp(name, aB[i].name) == 0) //입력받은 이름과 구조체 배열 내의 데이터가 일치할 경우, 아래 for문을 사용해 그 다음칸의 데이터를 앞으로 한 칸씩 덮어 씌움.
        {
            for (j = i; j + 1 < count; j++)
            {
                strcpy(aB[i].name, aB[j + 1].name); //strcpy 함수를 사용해서 삭제할 칸의 다음 칸 데이터로 대치
                strcpy(aB[i].phone, aB[j + 1].phone);
                strcpy(aB[i].addr, aB[j + 1].addr);
                strcpy(aB[i].birthday, aB[j + 1].birthday);
            }
            printf("삭제완료! \n\n");
            count--; //한 개의 데이터가 삭제됐으므로 count역시 -1
        }
        else if(i == count) //i와 count 가 같을 때 아래와 같이 출력. (데이터가 있지만 일치하지 않는 경우)
            printf("%s의 정보가 없습니다. \n\n",name);
    }
}
void menu(void) // 메뉴 출력 함수
{
    char choise;
    do
    {
        printf("\n\n================================================\n");
        printf("------------------주소록메뉴--------------------\n");
        printf("1)목록보기\t 2)추가 \t3)검색 \t4)삭제 \t5)종료 \n");
        printf("=================================================\n");
        scanf("%c", &choise);
        getchar();
        switch (choise)
        {
        case '1':
            list(); //1을 입력하면 list함수 실행
            break;
        case '2':
            append(); //2를 입력하면 append 함수 실행
            getchar();
            break;
        case '3':
            search(); //3을 입력하면 search 함수 실행
            getchar();
            break;
        case '4':
            del(); //4를 입력하면 del 함수 실행
            getchar();
            break;
        case '5': //5를 입력하면 프로그램 종료
            printf("\n 주소록 프로그램을 종료합니다. \n"); return;
        default: //해당 케이스에 속하지 않는 다른 번호가 입력될 경우 출력.
            printf("메뉴 번호를 다시 확인해주세요. \n");
        }
        
    }
    while(choise != '5'); //5가 아닌 숫자를 고를 경우 계속해서 반복
}

int main(int argc, char *argv[])
{
    menu(); //menu 함수 실행

    return 0;
}