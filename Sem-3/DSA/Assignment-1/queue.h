#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

typedef struct queue{
	List m_list;
} Queue;

void initQueue(Queue* queue){
	initList(&(queue->m_list));
}

void enqueue(Queue* queue, char name[100]){
	push_back(&queue->m_list, name);
}

char* dequeue(Queue* queue){
	return pop_front(&(queue->m_list));
}

#endif