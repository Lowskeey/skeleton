#ifndef SKELETON_H
#define SKELETON_H
#endif
#include <stdbool.h>

enum PROGRAM_CODES {
	SUCCESS,
	ABORTED,
	ERROR
}; /* RETURN THESE CODES! */
void toggle_quotes (bool *quotesEnabled);
void set_quote(char **quote, char *newText);
void do_cls();
void print_skeleton(int whichFrame);
bool is_playing(char *buff);
