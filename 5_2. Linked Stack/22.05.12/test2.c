#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void make_random_num(int input[],int min[],int max[]){
 for (int i = 0; i < 10; i++) {
        input[i] = (rand() % 100) + 1;
        if (i < 3) {
            min[i] = 101;
            max[i] = 0;
        }
        printf("%d ", input[i]);
    }
}

void find_min(int input[],int min[]){
    int temp[3] ={0,0};
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 10; i++) {
            if (temp[j] == input[i])
                continue;
            if (input[i] < min[j] && j == 0) {
                min[j] = input[i];
                temp[j] = min[j];
            } else if (input[i] < min[j] && temp[j - 1] < input[i]) {
                min[j] = input[i];
                temp[j] = min[j];
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        if (i < 2)
            temp[i] = 0;
        printf("\n%d번째로 작은 값 : %d",i+1, min[i]);
    }
    }

void find_max(int input[],int max[]){
    int temp[3] = {0,0};
for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 10; i++) {
            if (temp[j] == input[i])
                continue;
            if (input[i] > max[j] && j == 0) {
                max[j] = input[i];
                temp[j] = max[j];
            } else if (input[i] > max[j] && temp[j - 1] > input[i]) {
                max[j] = input[i];
                temp[j] = max[j];
            }
        }
    }

    for (int i = 0; i < 3; i++)
        printf("\n%d번째로 큰 값 : %d",i+1, max[i]);
}
int main(int argc, char* argv[]) {
    srand(time(NULL));
    int input[10], min[5], max[5], temp[3] = {0, 0};
    printf("=====[make_random_num]=============\n");
    make_random_num(input,min,max);
    printf("\n===============[min]===============");
    find_min(input,min);
    printf("\n===============[max]===============");
    find_max(input,max);
    printf("\n=================================\n");

    return 0;
}
