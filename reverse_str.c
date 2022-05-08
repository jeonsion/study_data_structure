#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

#define MAX_STACK_SIZE  100

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

void push(StackType *s, element item) {
   if (is_full(s)) {
       fprintf(stderr, "스택 포화 에러\n");
       return;
   }
   else
       s->data[++(s->top)] = item;
}

element pop(StackType *s) {
   if (is_empty(s)) {
       fprintf(stderr, "스택 공백 에러\n");
       exit(1);
   }
   else return
        s->data[(s->top)--];
}

void reverse(char a[], char b[]) {
   int i;
   StackType s;
   init_stack(&s);

   for (i = 0; a[i] != '\0'; i++) {
       push(&s, a[i]);
   }
   for (i = 0; !is_empty(&s); i++) {
       b[i] = pop(&s);
   }

   b[i] = '\0';
}


int main() {
   char str[100];
   char rev[100];

   while (1) {
       printf("문자열을 입력하세요 : ");
       scanf("%s", str);

       reverse(str, rev);  
       printf("원본 : %s\t 역순 %s\n", str, rev);
   }
}


