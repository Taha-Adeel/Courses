#ifndef MUSIC_H
#define MUSIC_H

#include "list.h"
#include "queue.h"
#include "stack.h"
#include "bst.h"
#include "avl.h"

void addToPlaylist(bst* library, avl_tree* playlist, char name[100]){
	if(search_bst(library, name) != NULL){
		printf("Inserting into the play list.\n");
		if(playlist->root == NULL)
			playlist->root = insert_avl_tree(playlist->root, name);

		insert_avl_tree(playlist->root, name);
	}
	else{
		printf("Sorry, song not found\n");
	}
}

void deleteFromPlaylist(avl_tree* playlist, char name[100]){
	if(search_avl_tree(playlist->root, name) != NULL){
		deleteFromPlaylist(playlist, name);
		printf("Song removed from playlist.\n");
	}
	else{
		printf("Song not found.\n");
	}
}

void playNext(avl_node** current_node, Stack* recent_songs){
	// static avl_node* current_node = minValue(playlist->root);
	char song[100];
	avl_node* inorder_successor = successor(*current_node);
	*current_node = inorder_successor;
	strcpy(song, inorder_successor->key);
	if(strcmp(song, "") != 0){
		printf("Playing %s", song);
		push(recent_songs, song);
	}
}

void playPrevious(avl_tree* playlist, Stack* recent_songs, int k){
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