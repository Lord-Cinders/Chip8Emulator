#ifndef CONFIG_H_
#define CONFIG_H_



// Note to future self - I hope you're not this stupid
// Note 2 - maybe later
// #ifdef _WIN32
//     #include<windows.h>
// #else 
//     #include<unistd.h>
//     #define Sleep(time) ( usleep(time / 100) ) // might not work, need a lab rat
// #endif
// 

#include<stdbool.h>
#include<stdlib.h>
#include<memory.h>
#include<assert.h>
#include<time.h>


/* Screen Enums*/
#define SCREEN_TITLE "CHIP 8 Emulator"
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define SCREEN_MULTIPLIER 10
#define DEFAULT_SPRITE_HEIGHT 5

/* Memory Enums*/
#define CHIP8_MEMORY_SIZE 4096
#define CHIP8_PROGRAM_START 0x200

/* Registers Enums*/
#define CHIP8_REGISTERS 16
#define CHIP8_MAX_STACK_SIZE 16
#define REGISTER_F 15

/* Keyboard Enums*/
#define CHIP8_KEYBOARD_SIZE 16
#define CHARACTER_SET_START_ADDRESS 0x00

#endif