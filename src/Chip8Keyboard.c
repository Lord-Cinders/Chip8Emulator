#include "Chip8Keyboard.h"

static void key_in_bounds(int key) { assert(key >= 0 && key < CHIP8_KEYBOARD_SIZE); }

void keyboard_load_map(struct Chip8Keyboard* keyboard, const char* map)
{
    keyboard->keymap = map;
}

int map_keyboard(struct Chip8Keyboard* keyboard, char key) // converts physical keypress to virtual keypress
{
    for(int i = 0; i < CHIP8_KEYBOARD_SIZE; i++)
    {
        if(keyboard->keymap[i] == key) { return i; }
    }

    return -1;
}

void keyboard_key_down(struct Chip8Keyboard* keyboard, int key)
{
    key_in_bounds(key);
    keyboard->keyboard[key] = true;
}

void keyboard_key_up(struct Chip8Keyboard* keyboard, int key)
{
    key_in_bounds(key);
    keyboard->keyboard[key] = false;
}

bool keyboard_is_key_down(struct Chip8Keyboard* keyboard, int key)
{
    key_in_bounds(key);
    return keyboard->keyboard[key];
}