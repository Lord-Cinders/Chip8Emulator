#ifndef CHIP8REGISTERS_H_
#define CHIP8REGISTERS_H_

#include "config.h"

struct Chip8Registers
{
    unsigned char V[CHIP8_REGISTERS]; //The VF register should not be used by any program
    unsigned short I; // 16 bit register used to store memory addresses
    unsigned char delay_timer; // When set to a non zero value, it is decrememnted at a rate of 60hz
    unsigned char sound_timer; // When set to a non zero value, it is decrememnted at a rate of 60hz
    unsigned short PC; // contains the address of the current instruction
    unsigned char stack_pointer; // points to the top of the memory stack
};

#endif