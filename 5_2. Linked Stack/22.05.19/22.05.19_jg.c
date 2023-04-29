#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef char element; // char 자료형으로 element 선언

typedef struct  stackNode{ // linked list의 구조체 선언
   element data;
   struct stackNode* link;
} stackNode;

typedef struct LLStack{ // capacity와 top을 저장하는 스택 구조체 선언
   int capacity;
   struct stackNode* top;
} LLStack;


LLStack* createStack() { // 스택을 초기설정하는 함수
   LLStack* S = (LLStack*)malloc(sizeof(LLStack)); // 스택의 메모리 할당
   S->capacity = 10; // 스택의 capacity 설정
   S->top = NULL; // 아직 값이 없으므로 list 포인터의 주소값 NULL 입력
   return S;
}
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

LLStack* push(LLStack* S, element n) { // 스택에 값을 넣는 PUSH 함수
   stackNode* tmp = (stackNode*)malloc(sizeof(stackNode)); // listnode에 메모리 할당
   tmp->data = n;

   if (isEmpty(S)) { // 현재 스택에 값이 없을 때
      S->top = tmp;
      tmp->link = NULL; // 이전 node가 없기때문에 link값에 NULL 입력
      //printf("PUSH : %c\n", n);
   }
   else if (isfull(S)) { // 스택의 capacity에 달했을 때
      printf("스택 오버플로우\n");
   }
   else {
      tmp->link = S->top; // 이전 top node의 주소를 link에 입력
      S->top = tmp; // 새로운 top의 주소 입력
      //printf("PUSH : %c\n", n);
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
      //printf("POP : %c\n", tmp->data);
      S->top = tmp->link; // top node의 다음 노드를 top에 입력
      free(tmp); // top node의 메모리 초기화
   }
   return ch;
}

char peak(LLStack* S) { // 스택의 top의 값을 구하는 함수
   stackNode* tmp = NULL;
   char ch;
   if (isEmpty(S)) {
      printf("스택 공백 에러\n");
   }
   else {
      tmp = S->top; // 현재 top의 주소를 tmp node에 할당
      ch = tmp->data;
   }
   return ch;
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

int prec(char op) {
   switch (op) {
   case'(': case')': return 0;
   case'+': case'-': return 1;
   case'*': case'/': return 2;
   }
   return -1;
}

char* infix_to_postfix(char* infx, LLStack* S) { // 괄호체크 함수
   int k = 0, p = 0;
   char *psfx;
   psfx = (char*)malloc(sizeof(char));
   element ch, top_op;
   printf("infix : %s\n", infx);
   while (infx[k] != NULL) {
      ch = infx[k++]; // 배열의 형태인 문자열을 차례대로 입력

      switch (ch) { // ch의 상태에 따라 case 실행
      case '+': case '-': case '*': case '/': // 연산자일 경우
         while (!isEmpty(S) && (prec(ch) <= prec(peak(S)))) // 연산자 우선순위
            psfx[p++] = pop(S);
         push(S, ch);
         break;

      case'(': // 여는 괄호일 경우
         push(S, ch); // 닫는괄호 구현을 위해 스택에 저장
         break;
      case')': // 닫는 괄호일 경우
         top_op = pop(S);
         while (top_op != '(') { // 여는 괄호를 만날때까지 출력
            psfx[p++] = top_op;
            top_op = pop(S);
         }
         break;
      default: // 일반 피연산자일 경우 출력
         psfx[p++] = ch;
         break;
      }
   }
   while (!isEmpty(S)) // 스택에 남은 연산자 출력
      psfx[p++] = pop(S);
   return psfx;
}

int eval(char* psfx, LLStack* S) {
   int op1, op2, value, result, i = 0;
   int len = strlen(psfx);
   char ch;

   for (i = 0; i < len; i++) {
      ch = psfx[i];
      if (ch != '+' && ch != '-' && ch != '*' && ch != '/') { // 입력이 피연산자이면
         value = ch - '0'; // ch의 아스키코드 - 0의 아스키코드 int형의 숫자값
         push(S, value);
      }
      else { // 연산자이면 피연산자를 스택에서 제거
         op2 = pop(S);
         op1 = pop(S);
         switch (ch) {
         case '+': push(S, op1 + op2); break;
         case '-': push(S, op1 - op2); break;
         case '*': push(S, op1 * op2); break;
         case '/': push(S, op1 / op2); break;
         }
      }
   }
   return pop(S);
}

int main(void) {
   char* infx = "(2+3)*4+9";
   char* psfx;
   LLStack* myS;
   myS = createStack();
   psfx = infix_to_postfix(infx, myS);
   printf("postfix : ");
   printf("%s\n", psfx);
   int result = eval(psfx, myS);
   printf("result : %d\n", result);

   return 0;
}