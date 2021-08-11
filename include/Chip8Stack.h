#ifndef CHIP8STACK_H_
#define CHIP8STACK_H_
#include "config.h"

struct Chip8;
struct Chip8Stack
{
    unsigned short stack[CHIP8_MAX_STACK_SIZE]; 
};

void stack_push(struct Chip8 * chip8, unsigned short value);
unsigned short stack_pop(struct Chip8 * chip8);


#endif