#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const unsigned int SECOND = 1000000;

static const char* prompts[][2] = {
	{"Frank", "What do you need help with?"},
	{"Bob", "Have you thought of any ideas of what to do yet?"},
	{"Frank", "What if you got a second wife?"},
	{"Bob", "Yeah, I agree with Frank, I think that might reduce the amount of fighting in your house."}, 
	{"Frank + Bob", "No problem."}
};
	
static char buf[256];
static char mychat[256][256];
static size_t friendindex = 0;
static size_t myindex = 0;


void cls() {
	system("clear");
}

void writec(char c) {
	putc(c, stdout);
}

void draw_chat_room() {
	char* lbuf = malloc(2048);
	cls();
	printf("Welcome to the chat room!\nCurrent people chatting:\n\tFrank\n\tBob\n\n");
	writec('+');
	for (int i = 0; i < 100; i++) writec('-');
	printf("+\n");
	for (int i = 0; i < 20; i++) {
		if (i >= friendindex + myindex) break;
		if (i % 2 == 0) {
			strcpy(lbuf, "Depo: ");
			strcat(lbuf, mychat[i / 2]);
		} else {
			strcpy(lbuf, prompts[(i - 1)/2][0]);
			strcat(lbuf, ": ");
			strcat(lbuf, prompts[(i - 1)/2][1]);
		}
		size_t length = strlen(lbuf);
		printf("| %s", lbuf);
		for (int i = 0; i < 99 - length; i++) {
			writec(' ');
		}
		printf("|\n");
	}
	writec('+');
	for (int i = 0; i < 100; i++) {
		writec('-');
	}
	printf("+\n");
}

int main() {
	
	cls();
	getchar();
	draw_chat_room();

	while (1) {
		printf("> ");
		fgets(mychat[myindex], 256, stdin);
		mychat[myindex][strlen(mychat[myindex]) - 1] = 0;
		myindex++;
		draw_chat_room();
		usleep(SECOND * (rand() % 2 + 1));
		friendindex++;
		draw_chat_room();
	}

	return 0;	
	
}
