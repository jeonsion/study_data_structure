#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define EXPR_SIZE 100

typedef int element;
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

// function prototype
void init_stack(StackType *s);
int is_empty(StackType *s);
int is_full(StackType *s);
void push(StackType *s, element item);
element pop(StackType *s);
element peek(StackType *s);
int check_matching(const char *in);
int prec(char op);
void infix_to_postfix(char exp[], char postfix[]);
int eval(char exp[]);

// main() function
int main() {
    int result = 0;
    char input[EXPR_SIZE] = {0};
    char postfix[EXPR_SIZE] = {0};

    while(1) {
        printf("계산할 수식을 입력하세요 : ");
        fgets(input, EXPR_SIZE-1, stdin);
        input[strlen(input) - 1] = '\0';
        if(strcmp(input, "exit")==0) {
            return 0;
        }

        if(check_matching(input)!=1) {
            printf("수식이 잘못되었습니다.\n\n");
            continue;
        }

        infix_to_postfix(input, postfix);
        printf("후위 표기식 : %s\n", postfix);

        result = eval(postfix);
        printf("연산 결과 => %d\n\n", result);
    }
}

// function definition

// init_stack()
void init_stack(StackType *s) {
    s->top = -1;
}

// is_empty()
int is_empty(StackType *s) {
    return (s->top == -1);
}

// is_full()
int is_full(StackType *s) {
    return (s->top == (MAX_STACK_SIZE-1));
}

// push()
void push(StackType *s, element item) {
    if(is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    } else {
        s->data[++(s->top)] = item;
    }
}

// pop()
element pop(StackType *s) {
    if(is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    } else {
        return s->data[(s->top)--];
    }
}

// peek()
element peek(StackType *s) {
    if(is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    } else {
        return s->data[(s->top)];
    }
}

// check_matching()
int check_matching(const char *in) {
    StackType s;
    char ch, open_ch;
    int i, n = strlen(in);

    init_stack(&s);

    for(i=0; i<n; i++) {
        ch = in[i];
        switch (ch) {
            case '(': case '{': case '[':
                push(&s, ch);
                break;

            case ')': case '}': case ']':
                if(is_empty(&s)) {
                    return 0;
                } else {
                    open_ch = pop(&s);
                    if((open_ch == '(' && ch != ')') || (open_ch == '{' && ch != '}') || (open_ch == '[' && ch != ']')) {
                        return 0;
                    }
                    break;
                }
        }
    }
    if(!is_empty(&s)) {
        return 0;
    }
    return 1;
}

// prec()
int prec(char op) {
    switch (op) {
        case '(': case ')': return 0;
        case '+': case '-': return 1;
        case '*': case '/': return 2;
    }
    return -1;
}

// infix_to_postfix()
void infix_to_postfix(char exp[], char postfix[]) {
    int i = 0, pos = 0;
    char ch, top_op;
    int len = strlen(exp);
    StackType s;

    init_stack(&s);

    for(i=0; exp[i]!='\0'; i++) {
        ch = exp[i];

        switch (ch) {
            case '+': case '-': case '*': case '/':
                while(!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) {
                    postfix[pos++] = pop(&s);
                    postfix[pos++] = ' ';
                }
                push(&s, ch);
                break;
            case '(':
                push(&s, ch);
                break;
            case ')':
            top_op = pop(&s);
                while(top_op != '(') {
                    postfix[pos++] = top_op;
                    top_op = pop(&s);
                }
                postfix[pos++] = ' ';
                break;
            default:
                do {
                    postfix[pos++] = ch;
                    ch = exp[++i];
                } while(ch >= '0' && ch <= '9');
                postfix[pos++] = ' ';
                i--;
                break;
        }
    }
    while(!is_empty(&s)) {
        postfix[pos++] = pop(&s);
        postfix[pos++] = ' ';
    }
}

// eval()
int eval(char exp[]) {
    int op1, op2, i;
    int len = strlen(exp);0
    char ch;
    StackType s;

    init_stack(&s);

    for(i=0; i<len; i++) {
        int value = 0, pos = 0;
        char temp[100] = {0};
        char ch;

        ch = exp[i];

        if(ch == ' ') {
            continue;
        } else if(ch != '+' && ch != '-' &&ch != '*' &&ch != '/') {
            for(pos=0; exp[i]!=' ';) {
                temp[pos++] = exp[i++];
            }
            temp[pos] = '\0';
            value = atoi(temp);
            push(&s, value);
        } else {
            op2 = pop(&s); op1 = pop(&s);
            printf("op1 : %d, op2 : %d\n", op1, op2);
            switch(ch) {
                case '+': push(&s, op1+op2); break;
                case '-': push(&s, op1-op2); break;
                case '*': push(&s, op1*op2); break;
                case '/': push(&s, op1/op2); break;
            }
        }
    }
    return pop(&s);
}