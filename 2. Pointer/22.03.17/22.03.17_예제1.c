#include <stdio.h>

int main (int argc, char* argv[]){
    int x = 1, y = 2;
    int *px;

    printf("x의 주소 : %d, y의 주소 %d\n",&x,&y);

    px = &x; // ?
    printf("2, x=%d, y =%d, *px = %d\n",x,y,px);
    y = *px; // y = 1
    printf("3, x=%d, y =%d, *px = %d\n",x,y,px);
    *px = 0; // x = 0
    printf("4, x=%d, y =%d, *px = %d\n",x,y,px);

    return 0;
}