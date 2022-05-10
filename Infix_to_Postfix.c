#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}
StackType;
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
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	} else
	        s->data[++(s->top)] = item;
}
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	} else
	        return s->data[(s->top)--];
}
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	} else
	        return s->data[s->top];
}
int prec(char op) {
	//�������� �켱������ ��ȯ
	switch (op) {
		case '(': case ')': return 0;
		case '+': case '-': return 1;
		case '*': case '/': return 2;
	}
	return -1;
}
void infix_to_postfix(char exp[]) {
	int i = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType s;
	init_stack(&s);
	//���� �ʱ�ȭ
	for (i = 0; i < len; i++) {
		ch = exp[i];
		switch (ch) {
			case '+': case '-': case '*':case'/':
			            while (!is_empty && (prec(ch) <= prec(peek(&s))))            //���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
			printf("%c", pop(&s));
			push(&s, ch);
			//����Ѵ��� ���ÿ� push
			break;
			case '(':                   //���ʰ�ȣ
			push(&s, ch);
			break;
			case ')':                   //������ ��ȣ
			top_op = pop(&s);
			while (top_op != '(') {
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;
			default:               //�ǿ�����
			printf("%c", ch);
			break;
		}
	}
	while (!is_empty(&s))       //���ÿ� ����� �����ڵ� ���
	printf("%c", pop(&s));
}
int main() {
	char expr[2][80] = {
		"8/2-3+(3*2)", "1/2*4(1/4)"
	}
	;
	printf("�������� : %s ==> �������� :", expr[0]);
	infix_to_postfix(expr[0]);
	printf("\n");
	printf("�������� : %s ==> �������� :", expr[1]);
	infix_to_postfix(expr[1]);
	printf("\n");
}