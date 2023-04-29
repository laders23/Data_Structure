//Recursion 형태의 코드
#include <stdio.h>

int factorial(int n){
    if(n <= 1) //Base case
        return 1;
    else
        return(n*factorial(n-1));
}
int main(int argc, char* argv[]){
    int a = 0;
    
    scanf("%d",&a);

    factorial(a);

    printf("%d \n",factorial(a));

    return 0;
}