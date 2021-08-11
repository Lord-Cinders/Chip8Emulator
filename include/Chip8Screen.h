#ifndef CHIP8SCREEN_H_
#define CHIP8SCREEN_H_

#include "config.h"

struct Chip8Screen
{
    bool pixels[SCREEN_WIDTH][SCREEN_HEIGHT];
};

void screen_clear(struct Chip8Screen * screen);
void screen_set_pixels(struct Chip8Screen * screen, int x, int y);
bool screen_pixels_is_set(struct Chip8Screen * screen, int x, int y);
bool screen_set_sprite(struct Chip8Screen * screen, int x, int y, const char * sprite, int bytes);
void screen_remove_sprite(struct Chip8Screen * screen, int x, int y, const char * sprite, int bytes);

#endif