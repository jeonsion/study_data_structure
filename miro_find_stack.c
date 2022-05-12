#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 7

typedef struct {
    int row;
    int col;
} element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
}StackType;

element here = { 1, 0 };

char maze[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1', '1'}, // maze[행][열]이 해당 위치의 미로의 상태
    {'0', '0', '1', '0', '0', '0', '0'},
    {'1', '0', '0', '0', '1', '0', '1'},
    {'1', '0', '1', '0', '1', '0', '1'},
    {'0', '0', '1', '1', '0', '0', '1'},
    {'1', '0', '1', '0', '0', '1', 'x'},
    {'1', '0', '1', '1', '0', '0', '0'}
};

void init_stack(StackType* s) {
    s->top = -1;
}

int is_empty(StackType* s) {
    return (s->top == -1);
}
int is_full(StackType* s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택 포화에러\n");
        return;
    }
    else    {
        s->data[++(s->top)] = item;
       // printf("들어온 좌표 : %d, %d\n", item.row, item.col);
    }
}

element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        //printf("나가는 좌표 : %d, %d\n",s->data[(s->top)].row,s->data[(s->top)].col);
        return s->data[(s->top)--];
}

element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백에러 \n");
        exit(1);
    }
    else return s->data[s->top];
}

void pushLocation(StackType* s, int row, int col) {
    if (row<0 || row>(MAZE_SIZE - 1) || col<0 || col>(MAZE_SIZE - 1))
        return;
    if ((maze[row][col] != '1') && (maze[row][col] != '.')) {
        element temp;
        temp.row = row;
        temp.col = col;
        push(s, temp);
    }
}

void printMaze() {
    system("cls");
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int r, c;
    StackType s;
    init_stack(&s);
    maze[here.row][here.col] = 'e';
    printMaze();
    getchar();              //엔터 누를 대마다 반응

    while (maze[here.row][here.col] != 'x') {
        r = here.row;
        c = here.col;
        maze[r][c] = 'm';
        printMaze();
        getchar();

        maze[r][c] = '.';
        pushLocation(&s, r - 1, c);
        pushLocation(&s, r + 1, c);
        pushLocation(&s, r, c - 1);
        pushLocation(&s, r, c + 1);

        if (is_empty(&s)) {
            printf("실패\n");
            return 0;
        }
        else {
           here = pop(&s);
        }
    }

    //출구를 찾은 경우

    maze[here.row][here.col] = 'm';
    printMaze();
    printf("성공");

}