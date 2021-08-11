#ifndef CHIP8_H_
#define CHIP8_H_

#include<stddef.h>
#include "config.h"
#include "Chip8Memory.h"
#include "Chip8Registers.h"
#include "Chip8Stack.h"
#include "Chip8Keyboard.h"
#include "Chip8Screen.h"

struct Chip8
{
    struct Chip8Memory memory;
    struct Chip8Registers registers;
    struct Chip8Stack stack;
    struct Chip8Keyboard keyboard;
    struct Chip8Screen screen;
    
};

void CHIP8_Init(struct Chip8 * chip8);
void chip8_load(struct Chip8 * chip8, const char * buf, size_t size);
void chip8_exec(struct Chip8 * chip8, unsigned short opcode);

#endif