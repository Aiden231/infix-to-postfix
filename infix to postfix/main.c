#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

// ���� �ʱ�ȭ
void init_stack(StackType* s)
{
	s->top = -1;
}

// ���� ���� �˻�
int is_empty(StackType* s)
{
	return (s->top == -1);
}

// ��ȭ ���� �˻�
int is_full(StackType* s)
{
	return(s->top == (MAX_STACK_SIZE - 1));
}

// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else {
		s->top++;
		s->data[s->top] = item;
		return;
	}
}

//�����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		return;
	}
	
	else return s->data[(s->top--)];
}

// ��ũ�Լ�
element peek(StackType* s)
{
	return s->data[s->top];
}

// ���� ǥ�� ���� ��� 
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

		// ������ ���
		if (ch >= '0' && ch <= '9') {
			value = ch - '0';
			push(&s, value);
		}

		// + - * / �� ���
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {

			// ������ ��� ���� ���
			if (is_empty(&s)) {
				fprintf(stderr, "���� ���� ����\n");
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
			fprintf(stderr, "Error ! �߸��� ���� �ֽ��ϴ�.\n");
			exit(1);
		}

	}

	return pop(&s);
}

// ������ �켱���� ��ȯ
int prec(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}

// ���� ǥ�� > ���� ǥ��
void infix_to_postfix(char exp[],char postfix[])
{
	int i = 0; // �ݺ��� ����
	int j = 0; // ����ǥ��� ������ ���� ����
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
	postfix[j] = '\0'; // �������� �� ���� �߰�
}

int main()
{
	int result;
	char s1[30];
	char postfix[30];

	printf("�߽�ǥ����� �Է��ϼ��� : ");
	scanf_s("%9s", s1, sizeof(s1));

	infix_to_postfix(s1,postfix);
	printf("����ǥ��� ��ȯ�� : %s\n", &postfix);

	result = eval((postfix));
	printf("����� %d�̴�.\n", result);

	return 0;
}