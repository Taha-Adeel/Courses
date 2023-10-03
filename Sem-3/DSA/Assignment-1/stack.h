#ifndef STACK_H
#define STACK_H

#include "list.h"

typedef struct stack{
	List m_list;
} Stack;

void initStack(Stack* stack){
	initList(&(stack->m_list));
}

void push(Stack* stack, char name[100]){
	push_back(&stack->m_list, name);
}

char* pop(Stack* stack){
	return pop_back(&(stack->m_list));
}

#endif