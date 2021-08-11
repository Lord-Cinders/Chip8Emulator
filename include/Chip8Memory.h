/*
 Memory visualization of Chip8

 +---------------+= 0xFFF (4095) End of Chip-8 RAM
 |               |
 |               |
 |               |
 |               |
 |               |
 | 0x200 to 0xFFF|
 |     Chip-8    |
 | Program / Data|
 |     Space     |
 |               |
 |               |
 |               |
 +- - - - - - - -+= 0x600 (1536) Start of ETI 660 Chip-8 programs
 |               |
 |               |
 |               |
 +---------------+= 0x200 (512) Start of most Chip-8 programs
 | 0x000 to 0x1FF|
 | Reserved for  |
 |  interpreter  |
 +---------------+= 0x000 (0) Start of Chip-8 RAM 

*/


#ifndef CHIP8MEMORY_H_
#define CHIP8MEMORY_H_

#include "config.h"

struct Chip8Memory
{
    unsigned char memory_array[CHIP8_MEMORY_SIZE]; // stores 1 byte in each cell
};

void chip8_memory_set(struct Chip8Memory * memory, int index, unsigned char value);
unsigned char chip8_memory_get(struct Chip8Memory * memory, int index);
unsigned short chip8_memory_get_short(struct Chip8Memory * memory, int pc);

#endif