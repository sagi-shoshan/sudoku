/*
 *
 * Stack.c
 *
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Stack.h"


struct stack * generateStack(){
	struct stack * st;
	st = malloc(sizeof(*st));
	st->topNode = NULL;
	st->size = 0;
	return st;
}

void freeStackMemory(struct stack * st){
	struct stackNode * current;
	struct stackNode * next;
	current = st->topNode;
	while (current != NULL){
		next = current->next;
		free(current);
		current = next;
	}
	free(st);
	return;
}

/* adding new node with value val to stack st */
void push(struct stack * st, int val){
	struct stackNode * node;
	node = malloc(sizeof(*node));
	node->value = val;
	node->next = st->topNode;
	st->size++;
	st->topNode = node;
	return;
}

/* If the stack contains an item, the function removes the item from the stack and returns its value.
 * Otherwise, returns -1
 *  */
int pop(struct stack * st){
	int val;
	struct stackNode * node;
	if (st->size == 0){
		printf("The stack is empty, no item to pop\n");
		return -1;
	}
	else {
		node = st->topNode;
		val = node->value;
		st->topNode = node->next;
		st->size--;
		free(node);
		return val;
	}
}

/* If the stack contains an item, the function returns the value of the top element of the stack.
 * Otherwise, returns -1
 *  */
int top(struct stack * st){
	int val;
	struct stackNode * node;
	if (st->size == 0){
		printf("The stack is empty\n");
		return -1;
	}
	else {
		node = st->topNode;
		val = node->value;
		return val;
	}
}
