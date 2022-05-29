#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char a;
    struct node *llink;
    struct node *rlink;
}Node;

void print_reverse(p) {
    while(p!=NULL)  {
        printf("%c", p->data);
        p=p->llink;
    }
}

int main()  {
    Node* p = NULL;   //마지막 노드를 가리키는 head저장

    Node * new_node = (Node *)malloc(sizeof(Node));
    new_node->a = 'I';
    new_node->llink = NULL;
    new_node->rlink = NULL;
    p = new_node;

    Node * new_node = (Node *)malloc(sizeof(Node));
    new_node->a = 'o';
    new_node->rlink = p->rlink;
    p->rlink = new_node;
    p->rlink->llink = p;
    p=new_node;

    Node * new_node = (Node *)malloc(sizeof(Node));
    new_node->a = 'T';
    new_node->rlink = p->rlink;
    p->rlink = new_node;
    p->rlink->llink = p;
    p=new_node;

    print_reverse();
}