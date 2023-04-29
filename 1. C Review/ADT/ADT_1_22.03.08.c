#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define H 100  // Hundred 앞 글자인 H를 따서 define

int main(int argc, char *argv[]) {
    int Score[H] = {0}, Temp[10] = {0}, max = 0;  // Score[H] = 100개의 배열 생성, Temp[10] = 10개의 임의의 수 집어 넣기 위한 배열, max = 최댓값

    srand(time(NULL));  //랜덤 시드를 넣을 때 마다 바뀌어야 하기 때문에, 랜덤값이 랜덤하게 나오지 않는 문제를 해결하기 위해, srand를 이용해 time값으로 시드를 계속 바꿔줌.

    for (int i = 0; i < H; i++)
        Score[i] = (rand() % 101);  // for문 이용으로 Score 배열에 임의의 수 100개를 지정하고, 그 과정에서 0~100 사잇값이어야 하기 때문에, rand값을 % 100 해주어서 범위 지정

    for (int i = 0; i < 10; i++) {
        Temp[i] = Score[(rand() % 101)];  // for문 이용으로 Score 중 임의의 값 10개의 값이여야 하므로, index값에도 rand값을 % 100 해주어서 랜덤값 추출
        if (Temp[i] > max)                // if문 사용으로 Temp값 중에서 최댓값을 찾아 max에 넣음.
            max = Temp[i];
    }

    printf("%d \n", max);  // 위 과정에서 얻은 max값 출력

    return 0;
}