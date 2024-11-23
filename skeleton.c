#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skeleton.h" /* includes enums such as SUCCESS, ABORTED and ERROR */
#include <time.h>

/* HOLY DEFINING! */
#define SKELE_ONE_PRINT(pieces) {						\
	for (size_t i = 0; i < (sizeof(pieces) / sizeof(pieces[0])); i++) {	\
		if (pieces[i] != NULL) printf("%s\n", pieces[i]);		\
		else puts("Core dumped error");					\
	}									\
}

enum ACTIONS {
	WalkUp,
	TalkTo,
	Attack
};

void toggle_quotes (bool *quotesEnabled) {
	*quotesEnabled = !(*quotesEnabled);
}

void set_quote(char **quote, char *newText) {
	*quote = newText;
}

bool is_playing(char *buff) {
	if (buff[0] == 'Y' || buff[0] == 'y') return true;
	return false;
}

void do_cls() {
#ifndef _WIN32
	system("clear");
#else
	system("cls");
#endif
}

void print_skeleton(int whichFrame) {
	char *alive[] = {
		"      .-.",
		"     (o.o)",
		"      |=|",
		"     __|__",
		"   //.=|=.\\\\",
		"  // .=|=. \\\\",
		"  \\\\ .=|=. //",
		"   \\\\(_=_)//",
		"    (:| |:)",
		"     || ||",
		"     () ()",
		"     || ||",
		"     || ||",
		"    ==' '=="
	};

	char *dead[] = {
		"      .-.",
		"     (X.X)",
		"      |=|",
		"     __|__",
		"   //.=|=.\\\\",
		"  // .=|=. \\\\",
		"  \\\\ .=|=. //",
		"   \\\\(_=_)//",
		"    (:| |:)",
		"     || ||",
		"     () ()",
		"     || ||",
		"     || ||",
		"    ==' '=="
	};
	

	switch (whichFrame) {
		case 1:
			SKELE_ONE_PRINT(alive);
			break;
		case 2:
			SKELE_ONE_PRINT(dead);
			break;
	}
}

int main(void) {
	enum PROGRAM_CODES SUCCESS = SUCCESS, ABORTED = ABORTED, ERROR = ERROR;
	enum ACTIONS WalkUp = WalkUp, TalkTo = TalkTo, Attack = Attack;
	int skeleton_health = 100;
	bool isQuotes = false;
	char *currentQuote = "";
	bool canAttack = true;

	char inputBuffer[10];
	puts("Do you wanna play with skeleton?");
	scanf("%s", inputBuffer);
	if (is_playing(inputBuffer) == false) return ABORTED;
	do_cls();
	print_skeleton(1);
	while (true) {
		int action_num;
		if (isQuotes == true) printf("HP: %d\nQuote: %s\nChoose your action:\n0 - Walk up\n1 - Talk to\n2 - Attack! > ", skeleton_health, currentQuote);
		else printf("HP: %d\nChoose your action:\n0 - Walk up\n1 - Talk to\n2 - Attack! > ", skeleton_health);
		scanf("%d", &action_num);
		do_cls();
		if (!isQuotes) toggle_quotes(&isQuotes);
		switch (action_num) {
			case 0:
				set_quote(&currentQuote, "You approached the skeleton. Rude silence...");
				print_skeleton((skeleton_health == 0) ? 2 : 1);
				break;
			case 1:
				if (skeleton_health == 0) {
					set_quote(&currentQuote, "Why are you tryna talk to a corpse?");
				} else {
					set_quote(&currentQuote, "You are telling to the skeleton some words, but he didn't answer...");
				}
				print_skeleton((skeleton_health == 0) ? 2 : 1);
				break;
			case 2:
				int minus_health = rand() % (25 - 3 + 1) + 3;
				int substr = skeleton_health - minus_health;
				if (substr >= 0 && canAttack) {
					skeleton_health = substr;
					char buffer[255];
					memset(buffer, '\0', sizeof(char) * 255);
					sprintf(buffer, "You attacked him! But why?... -%d HP", minus_health); 
					set_quote(&currentQuote, buffer);
				} else {
					canAttack = false;
					skeleton_health = 0;
					set_quote(&currentQuote, "You can't attack him anymore.");
				}
				print_skeleton((skeleton_health == 0) ? 2 : 1);
				break;
			default:
				puts("You wrote an incorrect action number, Doing quitting...");
				return ERROR;
		}
	}

	return SUCCESS;
}
