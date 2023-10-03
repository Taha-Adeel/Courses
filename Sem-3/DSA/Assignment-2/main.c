#include "bst.h" 
#include "avl.h"
#include "music.h"

int main(){
	bst library;
	init_bst(&library);

	printf("Enter name of file from which to read songs.\n");
	char filename[100];
	scanf("%s", filename);
	FILE* songs_file = fopen(filename, "r");
	if(songs_file == NULL){
		printf("Error opening file.\n");
		return -1;
	}

	char songs_arr[50][100];
	int counter = 0;
	char songs[5000];
	fgets(songs, 5000, songs_file);
	char* song = strtok(songs, ":");
	while(song != NULL){
		strcpy(songs_arr[counter++], song);
		song = strtok(NULL, ":");
	}

	construct_bst_from_preorder(&library, songs_arr, counter);

	//Delete unwanted songs
	printf("\nEnter the songs to remove from library. End with \"-1\"\n");
	while(true){
		char song[100];
		scanf("%s", song);
		if(strcmp(song, "-1")!=0)
			if(search_bst(&library, song) != NULL){
				delete_from_bst(&library, song);
				printf("Song removed from library.\n");
			}
			else{
				printf("Song not found.\n");
			}
		else{
			printf("Library Ready!\n\n");
			break;
		}
	}

	avl_tree playlist;
	init_avl_tree(&playlist);

	//Create the playlist
	printf("Create Playlist, End with \"-1\"\n");
	while(true){
		char song[100];
		scanf("%s", song);
		if(strcmp(song, "-1")!=0)
			addToPlaylist(&library, &playlist, song);
		else{
			printf("Playlist Ready!\n\n");
			break;
		}
	}

	//Delete unwanted songs from playlist
	printf("Enter the songs to remove from playlist. End with \"-1\"\n");
	while(true){
		char song[100];
		scanf("%s", song);
		if(strcmp(song, "-1")!=0)
			deleteFromPlaylist(&playlist, song);
		else{
			printf("Playlist Ready!\n\n");
			break;
		}
	}

	Stack recent_songs;
	initStack(&recent_songs);
	
	//Get the users input to play the next/previous song
	avl_node* current_node = minValue(playlist.root);
	char input[10]="";
	while(input[0] != 'e'){
		printf("\nPlay next song, previous songs or end? n/p:k/e\n");
		scanf("%s", input);
		switch(input[0]){
			case 'n':
				playNext(&current_node, &recent_songs);
				break;
			case 'p':
				playPrevious(&playlist, &recent_songs, atoi(input+2));//input+2 gives the numbers present after p:
				break;
			case 'e':
				printf("Bye!\n");
			default:
				break;
		}
	}

	return 0;
}