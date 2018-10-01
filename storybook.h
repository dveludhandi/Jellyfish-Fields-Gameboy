#ifndef STORYBOOK_H
#define STORYBOOK_H

#include <stdbool.h>

typedef enum state {
	STATE_START,
	STATE_RULES,
	STATE_GAME,
	STATE_END,
} state_t;

#endif