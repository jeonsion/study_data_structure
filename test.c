#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
}StackType;

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
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else
        s->data[++(s->top)] = item;
}

element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return s->data[(s->top)--];
}
element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return s->data[s->top];
}
int prec(char op) {
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
	// 스택 초기화
	for (i = 0; i < len; i++) {
		ch = exp[i];
		switch (ch) {
			case '+': case '-': case '*': case '/': 
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
			printf("%c", pop(&s));
			push(&s, ch);
			break;
			case '(': // 왼쪽 괄호
			push(&s, ch);
			break;
			case ')': // 오른쪽 괄호
			top_op = pop(&s);
			// 왼쪽 괄호를 만날 때까지 출력
			while (top_op != '(') {
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;
			default: // 피연산자
			printf("%c", ch);
			break;
		}
	}
	while (!is_empty(&s)) // 스택에 저장된 연산자들 출력
	printf("%c", pop(&s));
}
int main() {
	char expr[2][80] = {
		"8/2-3+(3*2)", "1/2*4*(1/4)"
	}
	;
	printf("중위수식: %s ==> 후위수식:", expr[0]);
	infix_to_postfix(expr[0]);
	printf("\n");
	printf("중위수식: %s ==> 후위수식:", expr[1]);
	infix_to_postfix(expr[1]);
	printf("\n");
}