//제목 : 프로젝트 3
//작성자 : 문승기
//날짜 : 2020.06.04

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXPR_SIZE 100
typedef int element;

typedef struct {
	element data[EXPR_SIZE];
	int top;
} StackType;

//스택 초기화 함수
void init_stack(StackType* s) {
	s->top = -1;
}

//공백 상태 검출 함수
int is_empty(StackType* s) {
	return (s->top == -1);
}

//포화 상태 검출 함수
int is_full(StackType* s) {
	return (s->top == (EXPR_SIZE - 1));
}

//삽입 함수
void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		s->data[++(s->top)] = item;
}

//삭제 함수
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러 \n");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

//피크 함수
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->data[s->top];
}

//괄호 정상성 체크를 위해 check_matching() 함수 사용 (교재 p.122)
int check_matching(const char* in) {
	StackType s;
	char ch, open_ch;
	int i, n = strlen(in);
	init_stack(&s);

	for (i = 0; i < n; i++) {
		ch = in[i];
		switch (ch) {
		case '(':
			push(&s, ch);
			break;
		case ')':
			if (is_empty(&s))
				return 0;
			else { 
				open_ch = pop(&s);
				if ((open_ch == '(' && ch != ')')) {
					return 0;
				}
				break;
			}
		}
	}
	if (!is_empty(&s)) 
		return 0;
	return 1;
}

//후위표기식 변환을 위해 prec(), infix_to_postfix() 함수 사용 (교재 p.133) -> 수정 필요, 수정완료
int prec(char op) {
	switch (op) {
	case '(': case ')': 
		return 0;
	case '+': case '-':
		return 1;
	case '*': case '/':
		return 2;
	}
	return -1;
}

void infix_to_postfix(char exp[], char postfix[]) {
	int i, pos = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType s;

	init_stack(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		switch (ch) {
		case '+' : case '-': case '*': case '/':
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) {
				postfix[pos++] = pop(&s);
			}
			push(&s, ch);
			break;
		case '(':
			push(&s, ch);
			break;
		case ')':
			top_op = pop(&s);
			while (top_op != '(') {
				postfix[pos++] = top_op;
				top_op = pop(&s);
			}
			break;
		default:
			do {
				postfix[pos++] = ch;
				ch = exp[++i];
			} while (ch >= '0' && ch <= '9');
			postfix[pos++] = ' ';
			i--;
			break;
		}
	}
	while (!is_empty(&s)) {
		postfix[pos++] = pop(&s);
	}
	postfix[pos] = '\0';
}

//후위표기식 계산을 위해 eval() 함수 사용 (교재 p.127) -> 수정 필요, 수정 중
int eval(char exp[]) {
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	int pos;
	char ch, temp[100];
	StackType s;

	init_stack(&s);

	for (i = 0; i < len; i++) {
		ch = exp[i];

		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			for (pos = 0; exp[i] != ' ';)
				temp[pos++] = exp[i++];
			if (ch == ' ')
				continue;
			temp[pos] = '\0';
			value = atoi(temp);
			push(&s, value);		

		}
		else {
			op2 = pop(&s);
			op1 = pop(&s);

			switch (ch) {
			case '+' :
				push(&s, op1 + op2);
				break;
			case '-':
				push(&s, op1 - op2);
				break;
			case '*':
				push(&s, op1 * op2);
				break;
			case '/':
				push(&s, op1 / op2);
				break;
			}
		}
	}
	return pop(&s);
}

int main() {
	int result;
	char input[EXPR_SIZE];
	char postfix[EXPR_SIZE];

	while (1) {
		printf("계산할 수식을 입력하세요: ");
		fgets(input, EXPR_SIZE - 1, stdin);
		input[strlen(input) - 1] = '\0';

		if (check_matching(input) != 1) {
			printf("수식이 잘못되었습니다.\n\n");
			continue;
		}
		
		infix_to_postfix(input, postfix);
		printf("후위 표기식 : %s\n", postfix);
		
		result = eval(postfix);
		printf("연산 결과 => %d\n\n", result);
	}
}