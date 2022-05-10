#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define EXPR_SIZE 100
typedef int elemet;

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

void infix_to_postfix(char exp[], char postfix[]) {
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

int prec(char op) {
	switch (op) {
		case '(': case ')': return 0;
		case '+': case '-': return 1;
		case '*': case '/': return 2;
	}
	return -1;
}

int eval(char exp[])    {
    int op1, op2, value, i=0;
    int len = strlen(exp);
    char ch;
    
    StackType s;
    init_stack(&s);

    for(i = 0; i<len; i++)  {
        ch = exp[i];
        if(ch != '+'&& ch!='-'&& ch!='*' && ch != '/')  {   //입력이 피연산자이며니, 숫자로 변환후 스택에  push
            value = ch - '0';
            push(&s, value);
        }
        else{
            op2 = pop(&s); op1 = pop(&s);
            switch (ch) {
                case '+' : push(&s, op1 + op2); break;
                case '-' : push(&s, op1 - op2); break;
                case '*' : push(&s, op1 * op2); break;
                case '/' : push(&s, op1 / op2); break;         
            }
        }
    }
    return pop(&s);
}

int check_matching(const char* in)  {
    StackType s;
    char ch, open_ch;
    int i, n = strlen(in);
    init_stack(&s); //스택 초기화


    for(i = 0; i<n; i++)    {       //문자열의 길이만큼 반복문 시행
        ch = in[i];
        switch(ch)  {
            case '(' :  case  '[' : case '{'    :
                push(&s, ch);
                break;
            case ')': case ']': case '}'    :
                if(is_empty(&s)) return 0;
                else{
                    open_ch = pop(&s);
                    if((open_ch == '(' && ch !=')') ||  //스택에서 꺼낸 open_ch와 ch가 다르면 오류
                        (open_ch == '[' && ch !=']')||
                        (open_ch == '{' && ch !='}')){
                        return 0;
                    }
                    break;
                }
        }
    }
    if(!is_empty(&s))   //스택이 비어있지 않으면
        return 0;
    
    return 1;
}

int main()  {
    int result;
    char input[EXPR_SIZE];
    char postfix[EXPR_SIZE];

    while(1)    {
        printf("계산할 수식을 입력하세요 :");
        fgets(input, EXPR_SIZE -1, stdin);
        input[strlen(input) -1] = '\0';

        if(check_matching(input)!= 1){
            printf("수식이 잘못되었습니다.\n\n");
            continue;
        }

        infix_to_postfix(input, postfix);
        printf("후위 표기식 : %s\n", postfix);

        result = eval(postfix);
        printf("연산 결과 => %d\n\n", result);
    }
}

//infix_to_postfix 고치는 부분부터 하면됨