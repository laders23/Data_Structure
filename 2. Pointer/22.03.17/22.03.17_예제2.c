#include <stdio.h>
#include <string.h>

void reverse(char *s1, char *s2){
    int tmp = strlen(s1); //문자열의 길이를 재기 위해서 strlen 사용 후, tmp에 저장
    char c; // 문자를 임시로 저장해줄 c 선언
    for(int i = 0; i < tmp; i++){
        c = s1[tmp]; //c에 s1[tmp] 값을 입력,
        s2[i]= s1[(tmp-1)-i]; //s2[i]에 s1[tmp-1-i] 값을 입력, i = 0일 때, s2[0] = s1[4] / s1의 index값에(tmp -1 -i) 인 이유는, 문자열 끝에 들어가는 \NULL 문자 제외하기 위함.
        s1[(tmp-1) - i] = c; //s1
    }
}

int main(int argc, char* argv[]){
    
    char s1[100], s2[100], *p, *q; //입력 문자열 저장을 위한 s1, 역순 문자열 저장을 위한 s2, s1값이 있는 주소를 point 해줄 p, s2값이 있는 주소를 point 해줄 q 선언.

    printf("문자열 입력 : "); //입력 문자열 확인용 UI
    scanf("%s",s1); //s1에 문자열 받기

    p = s1; //입력 문자열이 저장된 배열s1에 포인터 p 연결
    q = s2; //역순문자열을 저장할 배열s2에 포인터 q 연결

    reverse(p,q); //역순 문자열으로 만들어 줄 함수

    printf("역순문자열 : %s \n",s2); //역순 문자열 출력

    return 0;
}