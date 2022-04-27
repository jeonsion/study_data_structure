#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int bomb;
	struct node* llink;
	struct node* rlink;
}Node;

Node* DL = NULL;

void print_list() {
	Node* p;

	p = DL;
	printf(" (");
	while (p != NULL) {
		printf("%d ", p->bomb);
		p = p->rlink;
	}
	printf(")\n\n");
}

int main() {
	Node* p, * new;

	new = (Node*)malloc(sizeof(Node));
	new->bomb = rand() % 2;
	new->llink = NULL;
	new->rlink = NULL;
	DL = new;

	new = (Node*)malloc(sizeof(Node));
	new->bomb = rand() % 2;
	new->llink = NULL;
	new->rlink = NULL;
	p = DL;
	p->rlink = new;
	p->rlink->llink = new;

	new = (Node*)malloc(sizeof(Node));
	new->bomb = rand() % 2;
	new->llink = NULL;
	new->rlink = NULL;
	p = DL;
	new->rlink = p->rlink;
	p->rlink = new;
	new->llink = p;
	new->rlink->llink = new;

	new = (Node*)malloc(sizeof(Node));
	new->bomb = rand() % 2;
	new->llink = NULL;
	new->rlink = NULL;
	p = p->rlink->rlink;
	new->llink = p;
	p->rlink = new;
	new->rlink = NULL;

	print_list();

	p = DL;
	while (p->rlink != NULL) {
		p = p->rlink;
	}
	int bombCount = 0;
	while (p != NULL) {
		bombCount += p->bomb;
		p = p->llink;
	}

	printf("Bomb Count is %d!!!\n\n", bombCount);
}