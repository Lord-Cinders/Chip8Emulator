#include "Chip8Stack.h"
#include "Chip8.h"
#include<assert.h>

static void stack_in_bounds(struct Chip8 * chip8) { assert(chip8->registers.stack_pointer < CHIP8_MAX_STACK_SIZE); }

void stack_push(struct Chip8 * chip8, unsigned short value)
{
    stack_in_bounds(chip8);
    chip8->stack.stack[chip8->registers.stack_pointer] = value;
    chip8->registers.stack_pointer++;
}

unsigned short stack_pop(struct Chip8 * chip8)
{
    chip8->registers.stack_pointer--;
    stack_in_bounds(chip8);
    return chip8->stack.stack[chip8->registers.stack_pointer];
}