#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char a;
    struct node *llink;
    struct node *rlink;
}Node;



int main()  {
    Node*head = NULL;   //첫번째 노드를 가리키는 head저장

    Node *n1 = (Node*)malloc(sizeof(Node));
    n1->a = "I"
    n1->llink = NULL;
    n1 ->rlink = NULL;

    Node *n2 = (Node*)malloc(sizeof(Node));
    n2->a = "o"
    n2->llink = NULL;
    n2 ->rlink = NULL;



    Node *n3 = (Node*)malloc(sizeof(Node));
    n3->a = "T"
    n3->llink = NULL;
    n3 ->rlink = NULL;
}