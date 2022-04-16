#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
	int coef;
	int expon;
	struct ListNode* link;
}ListNode;

typedef struct ListType {
	int size;
	ListNode* head;
	ListNode* tail;
}ListType;

void error(char* message) {
	fprintf(stderr, "\n", message);
	exit(1);
}

ListType* create() {
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

void insert_last(ListType* plist, int coef, int expon) {
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL)
		error("메모리 할당 에러");
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;

	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++;
}

void poly_print(ListType* plist) {
	ListNode* p = plist->head;

	printf("polynomial =  ");
	for (; p; p = p->link) {
		printf("%dx^%d", p->coef, p->expon);
		if (p->link != NULL) {
			printf("+ ");
		}
	}
	printf("\n");
}

void poly_add(ListType* plist1, ListType* plist2, ListType* plist3) {
	ListNode* p = plist1->head;
	ListNode* q = plist2->head;
	int sum;

	while (p && q) {
		if (p->expon == q->expon) {
			sum = p->coef + q->coef;
			if (sum != 0) {
				insert_last(plist3, sum, p->expon); //q->expon 해도 상관없음
				p = p->link;
				q = q->link;
			} 
		
		}
		else if (p->expon > q->expon) {
			insert_last(plist3, p->coef, p->expon);
			p = p->link;
		}
		else {
			insert_last(plist3, q->coef, q->expon);
			q = q->link;
		}
	}

	for (; p; p = p->link) {
		insert_last(plist3, p->coef, p->expon);
	}
	for (; q; q = q->link) {
		insert_last(plist3, q->coef, q->expon);
	}
}

int main() {
	ListType* A, * B, * C;

	A = create();
	B = create();
	C = create();


	insert_last(A, 3, 12);
	insert_last(A, 2, 8);
	insert_last(A, 1, 0);


	insert_last(B, 8, 12);
	insert_last(B, -3, 10);
	insert_last(B, 10, 6);

	poly_print(A);
	poly_print(B);

	poly_add(A, B, C);
	poly_print(C);

	free(A);
	free(B);
	free(C);
}