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

//slows down gameplay to prevent glitching
void waitForVBlank (void) {
	while (SCANLINECOUNTER > 160);
	while (SCANLINECOUNTER < 160);
}

//draws images on GBA
void drawImage3 (int row, int col, int width, int height, const unsigned short *image) {
	for (int r = 0; r < height; r++) {
		DMA[3].src = &image[r * width];
		DMA[3].dst = videoBuffer + ((row + r) * 240 + col);
		DMA[3].cnt = (width) | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT;
	}
}

//checks which key is being clicked
int key_down (int key) {
    static int keybools = 0000000000;
    int bitStatus = (keybools >> key) & 1;
    if ((bitStatus == 0) && (KEY_DOWN_NOW(key))) {
        keybools ^= 1 << key;
        return TRUE;
    }
    if (KEY_DOWN_NOW(key) && (bitStatus == 1)) {
    	return FALSE;
    }
    if ((KEY_DOWN_NOW(key) == FALSE) && (bitStatus == 1)) {
        keybools ^= 1 << key;
        return FALSE;
    } else {
        return FALSE;
    }
}

//checks if Spongebob is near jellyfish
int jelly(Avatar *player, Jellyfish jellies[], int size) {
	for (unsigned int i = 0; i < sizeof(jellies); i++) {
		if (jellies[i].isVisible == 1) {
			if ((player->row >= jellies[i].row) && (player->row <= (jellies[i].row + JELLYFISH_HEIGHT))) {
				if ((player->col >= jellies[i].col) && (player->col <= (jellies[i].col + JELLYFISH_WIDTH))) {
					jellies[i].isVisible = 0;
					size--;
				}
			} else if (((player->row + SPONGEAVATAR_HEIGHT) >= jellies[i].row) && ((player->row + SPONGEAVATAR_HEIGHT) <= (jellies[i].row + JELLYFISH_HEIGHT))) {
				if (((player->col + SPONGEAVATAR_WIDTH) >= jellies[i].col) && ((player->col + SPONGEAVATAR_WIDTH) <= (jellies[i].col + JELLYFISH_WIDTH))) {
					jellies[i].isVisible = 0;
					size--;
				}
			}
		}
	}
	return size;
}

//resets game after jellyfish are found
int reset(int size, Jellyfish jellies[]) {
	size = 3;
	for (unsigned int i = 0; i < sizeof(jellies); i++) {
		jellies[i].isVisible = 1;
	}
	return size;
}