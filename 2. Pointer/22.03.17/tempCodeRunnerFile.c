#include <stdio.h>

int main (int argc, char* argv[]){
    int x = 1, y = 2;
    int *px;
    px = &x;
    y = *px;
    *px = 0;

    printf("%d %d %d \n",x,y,px);

    return 0;
}