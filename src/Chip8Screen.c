#include<stdbool.h>
#include<assert.h>
#include<memory.h>
#include "Chip8Screen.h"


static void screen_in_bounds(int x, int y) { assert(x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT); }

void screen_clear(struct Chip8Screen * screen)
{
    memset(screen->pixels, 0, sizeof(screen->pixels)); // set screen to black
}

void screen_set_pixels(struct Chip8Screen * screen, int x, int y)
{
    screen_in_bounds(x, y);
    screen->pixels[x][y] = true;
}

bool screen_pixels_is_set(struct Chip8Screen * screen, int x, int y)
{
    screen_in_bounds(x, y);
    return screen->pixels[x][y];
}

bool screen_set_sprite(struct Chip8Screen * screen, int x, int y, const char * sprite, int bytes)
{
    bool collision = false;

    for(int i = 0; i < bytes; i++)
    {
        char spritepart = sprite[i];
        for(int j = 0; j < 8; j++)
        {
            if((spritepart & (0b10000000 >> j)) == 0) { continue; } // 1 indicates a presence of a sprite

            if(screen->pixels[(j + x) % SCREEN_WIDTH][(i + y) % SCREEN_HEIGHT]) { collision = true; }
            
            screen->pixels[(j + x) % SCREEN_WIDTH][(i + y) % SCREEN_HEIGHT] ^= true; // remove sprite when collision occures
        }
    }
    return collision;
}


void screen_remove_sprite(struct Chip8Screen * screen, int x, int y, const char * sprite, int bytes)
{
    for(int i = 0; i < bytes; i++)
    {
        char spritepart = sprite[i];
        for(int j = 0; j < 8; j++)
        {
            screen->pixels[(j + x) % SCREEN_WIDTH][(i + y) % SCREEN_HEIGHT] = false;
        }
    }
}