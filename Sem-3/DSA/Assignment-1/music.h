#ifndef MUSIC_H
#define MUSIC_H

#include "list.h"
#include "queue.h"
#include "stack.h"

void addToPlaylist(List* library, Queue* playlist, char name[100]){
	if(searchInList(library, name)){
		printf("Inserting into the play list.\n");
		enqueue(playlist, name);
	}
	else{
		printf("Sorry, song not found\n");
	}
}

void playNext(Queue* playlist, Stack* recent_songs){
	char song[100];
	strcpy(song, dequeue(playlist));
	if(strcmp(song, "") != 0){
		printf("Playing %s", song);
		push(recent_songs, song);
	}
}

void playPrevious(Queue* playlist, Stack* recent_songs, int k){
	Queue temp_queue;
	initQueue(&temp_queue);

	for(int i=0; i<k; ++i){
		if(recent_songs->m_list.m_size == 0){
			printf("Sorry, there weren’t %d recent songs\n", k);
			break;
		}
		char song[100];
		strcpy(song, pop(recent_songs));
		printf("Playing %s", song);
		enqueue(&temp_queue, song);
	}

	while(temp_queue.m_list.m_size!=0){
		push(recent_songs, dequeue(&temp_queue));
	}
}

#endif