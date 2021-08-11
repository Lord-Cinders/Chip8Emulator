/*       Memory Functionality       */

#include "Chip8Memory.h"
#include<assert.h>

static void memory_in_bounds(int index) { assert(index >= 0 && index < CHIP8_MEMORY_SIZE ); }

void chip8_memory_set(struct Chip8Memory * memory, int index, unsigned char value)
{
    memory_in_bounds(index);
    memory->memory_array[index] = value;
}

unsigned char chip8_memory_get(struct Chip8Memory * memory, int index)
{
    memory_in_bounds(index);
    return memory->memory_array[index];
}
unsigned short chip8_memory_get_short(struct Chip8Memory * memory, int pc)
{
    unsigned short b1 = chip8_memory_get(memory, pc++);
    unsigned short b2 = chip8_memory_get(memory, pc);

    return b1 << 8 | b2; // returns a 16 bit binary instruction
}