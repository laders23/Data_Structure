#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef char element; // char 자료형으로 element 선언

typedef struct { // linked list의 구조체 선언
   element data;
   struct stackNode* link;
} stackNode;

typedef struct { // capacity와 top을 저장하는 스택 구조체 선언
   int capacity;
   struct stackNode* top;
} LLStack;

int isEmpty(LLStack* S) { // 스택의 공백여부를 반환하는 함수
   return (S->top == NULL);
}
int isfull(LLStack* S) { // 스택의 포화여부를 반환하는 함수
   int n = 0;
   stackNode* p = S->top;
   while (p->link != NULL) {
      p = p->link;
      n++;
   }
   return (n == S->capacity - 1);
}


LLStack* createStack() { // 스택을 초기설정하는 함수
   LLStack* S = (LLStack*)malloc(sizeof(LLStack)); // 스택의 메모리 할당
   S->capacity = 10; // 스택의 capacity 설정
   S->top = NULL; // 아직 값이 없으므로 list 포인터의 주소값 NULL 입력
   return S;
}

LLStack* Push(LLStack* S, element n) { // 스택에 값을 넣는 PUSH 함수
   stackNode* tmp = (stackNode*)malloc(sizeof(stackNode)); // listnode에 메모리 할당
   tmp->data = n;

   if (isEmpty(S)) { // 현재 스택에 값이 없을 때
      S->top = tmp;
      tmp->link = NULL; // 이전 node가 없기때문에 link값에 NULL 입력
      printf("PUSH : %c\n", n);
   }
   else if (isfull(S)) { // 스택의 capacity에 달했을 때
      printf("스택 오버플로우\n");
   }
   else {
      tmp->link = S->top; // 이전 top node의 주소를 link에 입력
      S->top = tmp; // 새로운 top의 주소 입력
      printf("PUSH : %c\n", n);
   }
   return S;
}

char pop(LLStack* S) { // 스택의 값을 제거하는 함수
   stackNode* tmp = NULL;
   char ch;
   if (isEmpty(S)) { // 스택이 공백 상태일 때
      printf("스택 공백 에러\n");
   }
   else {
      tmp = S->top; // 현재 top의 주소를 tmp node에 할당
      ch = tmp->data;
      printf("POP : %c\n", tmp->data);
      S->top = tmp->link; // top node의 다음 노드를 top에 입력
      free(tmp); // top node의 메모리 초기화
   }
   return ch;
}

void peak(LLStack* S) { // 스택의 top의 값을 구하는 함수
   stackNode* tmp = NULL;
   if (isEmpty(S)) {
      printf("스택 공백 에러\n");
   }
   else {
      tmp = S->top; // 현재 top의 주소를 tmp node에 할당
      printf("peek : %d\n", tmp->data);
   }
   return;
}



void printStack(LLStack* S) { // 스택을 출력하는 함수
   int n = 0;
   stackNode* p = S->top;
   if (isEmpty(S)) {
      printf("스택에 값이 없습니다.\n");
   }
   else {
      while (p != NULL) {
         printf("[%d] -> ", p->data); // top부터 차례대로 출력
         p = p->link;
      }
      printf("\n");
   }
   return;
}
void deleteStack(LLStack* S) { // 스택을 삭제하는 함수
   printf("delete Stack\n");
   while (!isEmpty(S)) { // listnode를 반복하여 삭제
      stackNode* tmp = NULL;
      tmp = S->top;
      S->top = tmp->link;
      free(tmp); // node를 삭제
   }
   free(S); // 스택 구조체 삭제
   return;
}

void check_matching(char* expr, LLStack* S) { // 괄호체크 함수
   int k = 0;
   element ch; // 괄호를 저장할 변수 선언
   printf("%s\n", expr); 
   while (expr[k] != NULL) {
      ch = expr[k++]; // 배열의 형태인 문자열을 차례대로 입력
      switch (ch) { // ch의 상태에 따라 case 실행
      case '(': case '[': case '{': { // 여는 괄호일 때 값을 push
         Push(S, ch);
         break;
      }
      case ')': { // 닫는 소괄호일떄
         if (isEmpty(S)) { // 닫는괄호가 있지만 비교할 여는괄호가 스택에 없을 때
            printf("\n여는 괄호 없음\n");
            exit(1);
         }
         else {
            if (pop(S) != '(') { // 여는괄호가 소괄호가 아닐 떄
               printf("\n괄호의 짝이 맞지 않음\n");
               exit(1);
            }
         }
         break;
      }
      case '}': { // 닫는 중괄호일떄
         if (isEmpty(S)) { // 닫는괄호가 있지만 비교할 여는괄호가 스택에 없을 때
            printf("\n여는 괄호 없음\n");
            exit(1);
         }
         else {
            if (pop(S) != '{') { // 여는괄호가 중괄호가 아닐 떄
               printf("\n괄호의 짝이 맞지 않음\n");
               exit(1);
            }
         }
         break;
      }
      case ']': { // 닫는 대괄호일떄
         if (isEmpty(S)) { // 닫는괄호가 있지만 비교할 여는괄호가 스택에 없을 때
            printf("\n여는 괄호 없음\n");
            exit(1);
         }
         else {
            if (pop(S) != '[') { // 여는괄호가 대괄호가 아닐 떄
               printf("\n괄호의 짝이 맞지 않음\n");
               exit(1);
            }
         }
         break;
      }
      }
   }
   if (!isEmpty(S)) { // 닫는괄호를 전부 검사하였지만 여는괄호가 스택에 남았을 때
      printf("\n닫는 괄호 없음\n");
      exit(1);
   }
   printf("\n이상 없음\n"); // switch문에서 성공적으로 빠져나왔을 때
   return;
}

int main(void) {
   //char* exp = "[({2+3}*4)+9]";
   char* exp = "[({2+3*4)}+9]"; // wrong pair
   //char* exp = "[({2+3}*4)+9"; // no closed bracket
   //char* exp = "({2+3}*4)+9]"; // no open bracket
   LLStack* myS;
   myS = createStack();
   check_matching(exp, myS);
   
   return 0;
}