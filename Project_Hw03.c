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
        fprintf(stderr, "���� ��ȭ ����\n");
        return;
    }
    else
        s->data[++(s->top)] = item;
}

element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else
        return s->data[(s->top)--];
}

element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else
        return s->data[s->top];
}

void infix_to_postfix(char exp[], char postfix[]) {
	int i = 0;
    int pos = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType s;
	init_stack(&s);
	// ���� �ʱ�ȭ
	for (i = 0; i < len; i++) {
		ch = exp[i];
		switch (ch) {
			case '+': case '-': case '*': case '/': 
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
			//printf("%c", pop(&s));
            postfix[pos++]=pop(&s);
			push(&s, ch);
			break;
			case '(': // ���� ��ȣ
			push(&s, ch);
			break;
			case ')': // ������ ��ȣ
			top_op = pop(&s);
			// ���� ��ȣ�� ���� ������ ���
			while (top_op != '(') {
				//printf("%c", top_op);
                 postfix[pos++]=pop(&s);
				top_op = pop(&s);
			}
			break;
			default: 
                do{
                    postfix[pos++] = ch;
                    ch = exp[++i];
                }while(ch>='0' && ch<='9');
                postfix[pos++] = ' ';
                i--;
                break;
		}
	}
    // ���ÿ� ����� �����ڵ� ���
	while (!is_empty(&s))   {
    //printf("%c", pop(&s));
        postfix[pos++]=pop(&s);
    } 
	
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
        if(ch != '+'&& ch!='-'&& ch!='*' && ch != '/')  {   //�Է��� �ǿ������̸��, ���ڷ� ��ȯ�� ���ÿ�  push
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
    init_stack(&s); //���� �ʱ�ȭ


    for(i = 0; i<n; i++)    {       //���ڿ��� ���̸�ŭ �ݺ��� ����
        ch = in[i];
        switch(ch)  {
            case '(' :  case  '[' : case '{'    :
                push(&s, ch);
                break;
            case ')': case ']': case '}'    :
                if(is_empty(&s)) return 0;
                else{
                    open_ch = pop(&s);
                    if((open_ch == '(' && ch !=')') ||  //���ÿ��� ���� open_ch�� ch�� �ٸ��� ����
                        (open_ch == '[' && ch !=']')||
                        (open_ch == '{' && ch !='}')){
                        return 0;
                    }
                    break;
                }
        }
    }
    if(!is_empty(&s))   //������ ������� ������
        return 0;
    
    return 1;
}

int main()  {
    int result;
    char input[EXPR_SIZE];
    char postfix[EXPR_SIZE];

    while(1)    {
        printf("����� ������ �Է��ϼ��� :");
        fgets(input, EXPR_SIZE -1, stdin);
        input[strlen(input) -1] = '\0';

        if(check_matching(input)!= 1){
            printf("������ �߸��Ǿ����ϴ�.\n\n");
            continue;
        }

        infix_to_postfix(input, postfix);
        printf("���� ǥ��� : %s\n", postfix);

        result = eval(postfix);
        printf("���� ��� => %d\n\n", result);
    }
}

//infix_to_postfix ��ġ�� �κк��� �ϸ��