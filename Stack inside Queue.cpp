#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"stack_struct.h"
#include"queue_stack_t.h"

void displayStack(stack_t s);
void displayQueue(queue_t q);

int main() {
	FILE* inp = fopen("courses.txt", "r");
	if (inp == NULL)
		printf("error");
	else {
		stack_t s;
		initializeS(&s);
		queue_t q;
		initializeQ(&q);

		SType t;
		char c;

		while (fscanf(inp, " %d%d%c", &t.code, &t.credit, &c) != EOF) {
			
			push(&s, t);

			if (c == '\n') {
				insertQ(&q, s);
				initializeS(&s);
			}
		}
		displayQueue(q);
	}
	return 0;
}

void displayStack(stack_t s) {

	SType t;

	while (!isEmptyS(&s)) {
		t = pop(&s);
		printf("%d %d --> ", t.code, t.credit);
		if (s.top == -1)
			printf("END\n");
	}
}
void displayQueue(queue_t q) {

	QType t;
	printf("QUEUE CONTENT\n--------------\n");

	while (!isEmptyQ(&q)) {
		t = removeQ(&q);
		displayStack(t);
	}

}