#include <stdio.h>
#include "myLib.h"
#include "storybook.h"
#include "jellyfishFields.h"
#include "text.h"
#include "font.h"
#include "gameBackground.h"
#include "jellyfish.h"
#include "spongeAvatar.h"
#include "score.h"
#include "rules.h"

volatile unsigned short *videoBuffer = (volatile unsigned short *)0x6000000;


int main (void) {
	REG_DISPCNT = MODE3 | BG2_ENABLE;
	state_t state = STATE_START;

	Jellyfish jelly1 = {120, 190, 1};
	Jellyfish jelly2 = {110, 50, 1};
	Jellyfish jelly3 = {75, 100, 1};
	Jellyfish jellies[3] = {jelly1, jelly2, jelly3};
	// int size = sizeof(jellies);
	int size = 3;
	// int reached = 0;
	int direction = 0;

	Avatar player = {0, 0};

	while (TRUE) {
		waitForVBlank();
		switch (state) {
			//waitForVBlank();
			case STATE_START:
			    drawImage3 (0, 0, 240, 160, jellyfishFields);
			    if (key_down(BUTTON_START)) {
			    	state = STATE_RULES;
			    }
			    if (key_down (BUTTON_SELECT)) {
			    	state = STATE_START;
			    }
			    break;
			case STATE_RULES:
				//waitForVBlank();
				drawImage3 (0, 0, RULES_WIDTH, RULES_HEIGHT, rules);
			    if (key_down (BUTTON_START)) {
			    	state = STATE_GAME;
			    }
			    if (key_down (BUTTON_SELECT)) {
			    	state = STATE_START;
			    }
			    break; 
			case STATE_GAME:
				//waitForVBlank();

				int rd = 5;
				int cd = 5;
				int oldRow = player.row;
				int oldCol = player.col;
				char num[60];

				// if (reached == 0) {
					drawImage3 (0, 0, GAMEBACKGROUND_WIDTH, GAMEBACKGROUND_HEIGHT, gameBackground);
					//drawImage3 (0, 0, SPONGEAVATAR_WIDTH, SPONGEAVATAR_HEIGHT, spongeAvatar);
				// }

				if (jelly1.isVisible == 1) {
					drawImage3 (120, 190, JELLYFISH_WIDTH, JELLYFISH_HEIGHT, jellyfish);
				}
				if (jelly2.isVisible == 1) {
					drawImage3 (110, 50, JELLYFISH_WIDTH, JELLYFISH_HEIGHT, jellyfish);
				}
				if (jelly3.isVisible == 1) {
					drawImage3 (75, 100, JELLYFISH_WIDTH, JELLYFISH_HEIGHT, jellyfish);
				}

				sprintf(num, "Jellyfish left: %d", size);
				drawString(150, 110, num, WHITE);

				if (key_down (BUTTON_UP)) {
					oldRow = player.row;
					player.row -= rd;
					direction = 1;
				}
				if (key_down (BUTTON_DOWN)) {
					oldRow = player.row;
					player.row += rd;
					direction = 2;
				}
				if (key_down (BUTTON_LEFT)) {
					oldCol = player.col;
					player.col -= cd;
					direction = 3;
				}
				if (key_down (BUTTON_RIGHT)) {
					oldCol = player.col;
					player.col += cd;
					direction = 4;
				}

				if (player.row < 0) {
					player.row = 0;
					rd = 0;
					//rd = -rd;
				}
				if (player.row > 130) {
					player.row = 130;
					rd = 0;
					//rd = -rd;
				}
				if (player.col < 0) {
					player.col = 0;
					cd = 0;
					//cd = -cd;
				}
				if (player.col > 210) {
					player.col = 210;
					cd = 0;
					//cd = -cd;
				}
				// reached = 1;
				if (direction == 1) {
					//up
					drawImage3(oldRow - SPONGEAVATAR_HEIGHT + rd, oldCol, SPONGEAVATAR_WIDTH, rd, gameBackground);
					drawImage3(oldRow - SPONGEAVATAR_HEIGHT + rd, oldCol, SPONGEAVATAR_WIDTH, SPONGEAVATAR_HEIGHT, gameBackground);
					drawImage3(oldRow - 30, oldCol - 30, 90, 90, gameBackground);
				} else if (direction == 2) {
					//down
					drawImage3(oldRow, oldCol, SPONGEAVATAR_WIDTH, rd, gameBackground);
					drawImage3(oldRow - SPONGEAVATAR_HEIGHT + rd, oldCol, SPONGEAVATAR_WIDTH, SPONGEAVATAR_HEIGHT, gameBackground);
					drawImage3(oldRow - 30, oldCol - 30, 90, 90, gameBackground);
				} else if (direction == 3) {
					//left
					drawImage3(oldRow, oldCol + SPONGEAVATAR_WIDTH - cd, cd, SPONGEAVATAR_HEIGHT, gameBackground);
					drawImage3(oldRow - SPONGEAVATAR_HEIGHT + rd, oldCol, SPONGEAVATAR_WIDTH, SPONGEAVATAR_HEIGHT, gameBackground);
					drawImage3(oldRow - 30, oldCol - 30, 90, 90, gameBackground);
				} else if (direction == 4) {
					//right
					drawImage3(oldRow, oldCol, cd, SPONGEAVATAR_HEIGHT, gameBackground);
					drawImage3(oldRow - SPONGEAVATAR_HEIGHT + rd, oldCol, SPONGEAVATAR_WIDTH, SPONGEAVATAR_HEIGHT, gameBackground);
					drawImage3(oldRow - 30, oldCol - 30, 90, 90, gameBackground);
				}
				drawImage3 (oldRow, oldCol, oldCol + SPONGEAVATAR_WIDTH - cd, oldRow + SPONGEAVATAR_HEIGHT - rd, gameBackground);
				drawImage3(oldRow - 30, oldCol - 30, 90, 90, gameBackground);
				if (jelly1.isVisible == 1) {
					drawImage3 (120, 190, JELLYFISH_WIDTH, JELLYFISH_HEIGHT, jellyfish);
				}
				if (jelly2.isVisible == 1) {
					drawImage3 (110, 50, JELLYFISH_WIDTH, JELLYFISH_HEIGHT, jellyfish);
				}
				if (jelly3.isVisible == 1) {
					drawImage3 (75, 100, JELLYFISH_WIDTH, JELLYFISH_HEIGHT, jellyfish);
				}
				//waitForVBlank();
				sprintf(num, "Jellyfish left: %d", size);
				//waitForVBlank();
				drawString(150, 110, num, WHITE);
				drawImage3 (player.row, player.col, SPONGEAVATAR_WIDTH, SPONGEAVATAR_HEIGHT, spongeAvatar);

				waitForVBlank();
				size = jelly(&player, jellies, size);

				if (size == 0) {
					size = reset(size, jellies);
					drawImage3(0, 0, GAMEBACKGROUND_WIDTH, GAMEBACKGROUND_HEIGHT, gameBackground);
					// reached = 0;
					state = STATE_END;
				}
				if (key_down (BUTTON_SELECT)) {
			    	state = STATE_START;
			    }
			    if (key_down (BUTTON_START)) {
			    	state = STATE_END;
			    }
			    break;
			case STATE_END:
				drawImage3 (0, 0, SCORE_WIDTH, SCORE_HEIGHT, score);
			    if (key_down (BUTTON_START)) {
			    	state = STATE_START;
			    }
			    if (key_down (BUTTON_SELECT)) {
			    	state = STATE_START;
			    }
			    break;
		}
	}
	return 0;
}