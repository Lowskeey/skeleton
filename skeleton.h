#ifndef SKELETON_H
#define SKELETON_H
#endif
#include <stdbool.h>

enum PROGRAM_CODES {
	SUCCESS,
	ABORTED,
	ERROR
}; /* RETURN THESE CODES! */
void print_skeleton(int whichFrame);
bool is_playing(char *buff);
