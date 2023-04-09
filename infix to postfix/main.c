#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

// 스택 초기화
void init_stack(StackType* s)
{
	s->top = -1;
}

// 공백 상태 검사
int is_empty(StackType* s)
{
	return (s->top == -1);
}

// 포화 상태 검사
int is_full(StackType* s)
{
	return(s->top == (MAX_STACK_SIZE - 1));
}

// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else {
		s->top++;
		s->data[s->top] = item;
		return;
	}
}

//삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		return;
	}
	
	else return s->data[(s->top--)];
}

// 피크함수
element peek(StackType* s)
{
	return s->data[s->top];
}

// 후위 표기 수식 계산 
int eval(char exp[])
{
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;

	StackType s;
	init_stack(&s);

	for (i = 0; i < len; i++)
	{
		ch = exp[i];

		// 숫자인 경우
		if (ch >= '0' && ch <= '9') {
			value = ch - '0';
			push(&s, value);
		}

		// + - * / 인 경우
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {

			// 스택이 비어 있을 경우
			if (is_empty(&s)) {
				fprintf(stderr, "스택 공백 에러\n");
				return 0;
			}
			

			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) {
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}

		else {
			fprintf(stderr, "Error ! 잘못된 값이 있습니다.\n");
			exit(1);
		}

	}

	return pop(&s);
}

// 연산자 우선순위 반환
int prec(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}

// 중위 표기 > 후위 표기
void infix_to_postfix(char exp[],char postfix[])
{
	int i = 0; // 반복문 변수
	int j = 0; // 후위표기식 저장을 위한 변수
	char ch, top_op;
	int len = strlen(exp);
	StackType s;
	init_stack(&s);

	for (i = 0; i < len; i++)
	{
		ch = exp[i];
		switch (ch) {
		case '+': case '-': case '*': case '/':
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
				postfix[j++]=pop(&s);
			push(&s, ch);
			break;

		case '(':
			push(&s, ch);
			break;

		case ')':
			top_op = pop(&s);
			while (top_op != '(') {
				postfix[j++] =  top_op;
				top_op = pop(&s);
			}
			break;
			
		default:
			postfix[j++] = ch;
			break;
		}
	}
	while (!is_empty(&s))
		postfix[j++] = pop(&s);
	postfix[j] = '\0'; // 마지막에 널 문자 추가
}

int main()
{
	int result;
	char s1[30];
	char postfix[30];

	printf("중식표기식을 입력하세요 : ");
	scanf_s("%9s", s1, sizeof(s1));

	infix_to_postfix(s1,postfix);
	printf("후위표기식 전환시 : %s\n", &postfix);

	result = eval((postfix));
	printf("결과는 %d이다.\n", result);

	return 0;
}