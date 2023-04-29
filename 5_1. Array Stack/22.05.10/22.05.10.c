#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int top;
    int capacity;
    int* array;
} ArrayStack;

ArrayStack* createStack() {
    ArrayStack* S = malloc(sizeof(ArrayStack));
    if (!S)
        return NULL;
    S->capacity = 1;
    S->top = -1;
    S->array = malloc(S->capacity * sizeof(int));
    if (!S->array)
        return 0;

    return S;
}

int is_Full(ArrayStack* S) {
    if (S->top == (S->capacity) - 1)
        return 0;
    else
        return 1;
};


void push(ArrayStack* S, int data) {
    if (isFull(S)) {
        S->capacity *= 2;
        S->array = (int*)realloc(S->array, S->capacity);
    }
    S->array[++S->top] = data;
}

void pop(ArrayStack* S){
    if(is_Empty(S)){

    }

    else return S->array[S->top--];
}

void deleteStack(ArrayStack* S){
    if(S){
        if(S->array)
            free;
            free(S);

    }
}
int main(int argc, char* argv[]) {
}