#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 50
#define MAZE_SIZE 7

typedef struct {
    int row;
    int col;
}element;

typedef struct {
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
}QueueType;

element here = {1, 0};

char maze[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1', '1'}, // maze[��][��]�� �ش� ��ġ�� �̷��� ����
    {'0', '0', '1', '0', '0', '0', '0'},
    {'1', '0', '0', '0', '1', '0', '1'},
    {'1', '0', '1', '0', '1', '0', '1'},
    {'0', '0', '1', '1', '0', '0', '1'},
    {'1', '0', '1', '0', '0', '1', 'x'},
    {'1', '0', '1', '1', '0', '0', '0'}
};

void error(char *message)   {
    fprintf(stderr, "%s\n", message);
}

void init_queue(QueueType *q)   {
    q->rear = 0;
    q->front = 0;
}

int is_full(QueueType *q)   {
    return (q->front ==(q->rear+1)%MAX_QUEUE_SIZE);
}

int is_empty(QueueType *q)   {
    return (q->front == q->rear);
}

void enqueue(QueueType *q, element item)    {
    if(is_full(q))  {
        error("ť�� ��ȭ�����Դϴ�.");
        return ;
    }
    q->rear = (q->rear +1) % MAX_QUEUE_SIZE;
    q->data[q->rear]= item;
}

element dequeue(QueueType *q)   {
    if(is_empty(q)) {
        error("ť�� ��������Դϴ�.");
        exit(1);
    }
    q->front = (q->front +1) %MAX_QUEUE_SIZE;
    return q->data[q->front];
}

void pushLocation(QueueType *q, int row, int col)   {
    //
    if ((row>=0 && row<=(MAZE_SIZE - 1)) && (col>=0 && col<=(MAZE_SIZE - 1)))
        return;
    if ((maze[row][col] != '1') && (maze[row][col] != '.')) {
        element temp;
        temp.row = row;
        temp.col = col;
        enqueue(q, temp);
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

int main()  {
    int r, c;
    QueueType q;
    init_queue(&q);

    maze[here.row][here.col] = 'e';
    printMaze();
    getchar();              //���� ���� �븶�� ����

    while (maze[here.row][here.col] != 'x') {
        r = here.row;
        c = here.col;
        maze[r][c] = 'm';
        printMaze();
        getchar();

        maze[r][c] = '.';
        
        pushLocation(&q, r + 1, c);
        pushLocation(&q, r - 1, c);
        pushLocation(&q, r, c + 1);
        pushLocation(&q, r, c - 1);

        if (is_empty(&q)) {
            printf("����\n");
            return 0;
        }
        else {
           here = dequeue(&q);
        }
    }

    //�ⱸ�� ã�� ���

    maze[here.row][here.col] = 'm';
    printMaze();
    printf("����");



}