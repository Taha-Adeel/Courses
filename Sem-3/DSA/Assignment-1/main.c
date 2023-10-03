#include "music.h"

int main(){
	List library;
	initList(&library);

	//Get songs in library
	printf("Enter all songs (as strings), End with \"-1\"\n");
	while(true){
		char song[100];
		fgets(song, 100, stdin);
		if(strcmp(song, "-1\n")==0){
			printf("All songs entered!\n\n");
			break;
		}
		push_back(&library, song);
	}

	Queue playlist;
	initQueue(&playlist);

	//Create the playlist
	printf("Create Playlist, End with \"-1\"\n");
	while(true){
		char song[100];
		fgets(song, 100, stdin);
		if(strcmp(song, "-1\n")!=0)
			addToPlaylist(&library, &playlist, song);
		else{
			printf("Playlist Ready!\n");
			break;
		}
	}

	Stack recent_songs;
	initStack(&recent_songs);
	
	//Get the users input to play the next/previous song
	char input[10]="";
	while(input[0] != 'e'){
		printf("\nPlay next song, previous songs or end? n/p:k/e\n");
		scanf("%s", input);
		switch(input[0]){
			case 'n':
				playNext(&playlist, &recent_songs);
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