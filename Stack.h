/*
 *
 * Stack.h
 *
 * the following is an implementation of a dynamically-sized stack
 * basic commands of a stack data structure are included
 *
 */

#ifndef STACK_H_
#define STACK_H_

struct stack{
	int size;
	struct stackNode * topNode;
};

struct stackNode{
	int value;
	struct stackNode * next;
};

struct stack * generateStack();

void freeStackMemory(struct stack * st);

void push(struct stack * st, int val);

int pop(struct stack * st);

int top(struct stack * st);


#endif /* STACK_H_ */
