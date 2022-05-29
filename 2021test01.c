#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char a;
    struct node *llink;
    struct node *rlink;
}Node;



int main()  {
    Node* p = NULL;   //마지막 노드를 가리키는 head저장

    Node * n1 = (Node *)malloc(sizeof(Node));
    n1->a = 'I';
    n1->llink = NULL;
    n1->rlink = NULL;
    p = n1;

    Node * n2 = (Node *)malloc(sizeof(Node));
    n2->a = 'o';
    n2->rlink = p->rlink;
    p->rlink = n2;
    p->rlink->llink = p;
    p=n2;

    Node * n3 = (Node *)malloc(sizeof(Node));
    n3->a = 'T';
    n3->rlink = p->rlink;
    p->rlink = n3;
    p->rlink->llink = p;
    p=n3;

    while(p!=NULL)  {
        printf("%c", p->a);
        p=p->llink;
    }
}