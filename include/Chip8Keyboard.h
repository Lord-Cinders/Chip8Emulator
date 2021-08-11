/*
 Keyboard Layout
     1 2 3 C
     4 5 6 D
     7 8 9 E
     A 0 B F
 
 MAP(KEY) = 0xKEY
 (0 <= KEY <= F)

*/


#ifndef CHIP8KEYBOARD_H_
#define CHIP8KEYBOARD_H_

#include "config.h"

struct Chip8Keyboard
{
    bool keyboard[CHIP8_KEYBOARD_SIZE];
    const char * keymap;
};

void keyboard_load_map(struct Chip8Keyboard* keyboard, const char* map);
int map_keyboard(struct Chip8Keyboard* keyboard, char key);
void keyboard_key_down(struct Chip8Keyboard* keyboard, int key);
void keyboard_key_up(struct Chip8Keyboard* keyboard, int key);
bool keyboard_is_key_down(struct Chip8Keyboard* keyboard, int key);


#endif