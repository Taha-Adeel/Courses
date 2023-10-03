//Doubly linked list

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	char m_name[100];
	struct node* m_next;
	struct node* m_prev;
} Node;

typedef struct list{
	Node *m_head;
	Node *m_tail;
	int m_size;
} List;

//Iniatialize the list
void initList(List* list){
	list->m_head = NULL;
	list->m_tail = NULL;
	list->m_size = 0;
}

//Adds an element to the end
void push_back(List* list, char name[100]){
	Node* newElem = (Node*) malloc(sizeof(Node));
	strcpy(newElem->m_name, name);
	newElem->m_next = NULL;
	newElem->m_prev = NULL;

	if(list->m_size == 0){
		list->m_head = newElem;
		list->m_tail = newElem;
	}
	else{
		list->m_tail->m_next = newElem;
		newElem->m_prev = list->m_tail;
		list->m_tail = newElem;
	}
	list->m_size++;
}

//Adds an element to the beggining
void push_front(List* list, char name[100]){
	Node* newElem = (Node*) malloc(sizeof(Node));
	strcpy(newElem->m_name, name);
	newElem->m_next = NULL;
	newElem->m_prev = NULL;

	if(list->m_size == 0){
		list->m_head = newElem;
		list->m_tail = newElem;
	}
	else{
		list->m_head->m_prev = newElem;
		newElem->m_next = list->m_head;
		list->m_head = newElem;
	}
	list->m_size++;
}

//Returns and removes the last element
char* pop_back(List* list){
	if(list->m_size==0){
		printf("List is empty\n");
		return "";
	}
	else if(list->m_size==1){
		char* temp=(char*)malloc(100*sizeof(char));
		strcpy(temp, list->m_tail->m_name);
		free(list->m_tail);
		initList(list);
		return temp;
	}
	else{
		char* temp=(char*)malloc(100*sizeof(char));
		strcpy(temp, list->m_tail->m_name);

		list->m_tail = list->m_tail->m_prev;
		free(list->m_tail->m_next);
		list->m_tail->m_next = NULL;
		list->m_size--;
		return temp;
	}
}

//Returns and removes the first element
char* pop_front(List* list){
	if(list->m_size==0){
		printf("List is empty\n");
		return "";
	}
	else if(list->m_size==1){
		char* temp=(char*)malloc(100*sizeof(char));
		strcpy(temp, list->m_head->m_name);
		free(list->m_head);
		initList(list);
		return temp;
	}
	else{
		char* temp=(char*)malloc(100*sizeof(char));
		strcpy(temp, list->m_head->m_name);
		
		list->m_head = list->m_head->m_next;
		free(list->m_head->m_prev);
		list->m_head->m_prev = NULL;
		list->m_size--;
		return temp;
	}
}

//Searchs the list for an element
bool searchInList(List* list, char name[100]){
	for(Node* current=list->m_head; current!=NULL; current=current->m_next){
		if(strcmp(current->m_name, name)==0)
			return true;
	}

	return false;
}

#endif