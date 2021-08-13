#include "Chip8.h"
#include "SDL2/SDL.h"

// 0 to F
const char default_character_set[] = {
    0xf0, 0x90, 0x90, 0x90, 0xf0,
    0x20, 0x60, 0x20, 0x20, 0x70,
    0xf0, 0x10, 0xf0, 0x80, 0xf0,
    0xf0, 0x10, 0xf0, 0x10, 0xf0,
    0x90, 0x90, 0xf0, 0x10, 0x10,
    0xf0, 0x80, 0xf0, 0x10, 0xf0,
    0xf0, 0x80, 0xf0, 0x90, 0xf0,
    0xf0, 0x10, 0x20, 0x40, 0x40,
    0xf0, 0x90, 0xf0, 0x90, 0xf0,
    0xf0, 0x90, 0xf0, 0x10, 0xf0,
    0xf0, 0x90, 0xf0, 0x90, 0x90,
    0xe0, 0x90, 0xe0, 0x90, 0xe0,
    0xf0, 0x80, 0x80, 0x80, 0xf0,
    0xe0, 0x90, 0x90, 0x90, 0xe0,
    0xf0, 0x80, 0xf0, 0x80, 0xf0, 
    0xf0, 0x80, 0xf0, 0x80, 0x80
};


void CHIP8_Init(struct Chip8 * chip8) // initialize all memory units to 0
{
    memset(chip8, 0, sizeof(struct Chip8));
    memcpy(&chip8->memory.memory_array, default_character_set, sizeof(default_character_set));
}

void chip8_load(struct Chip8 * chip8, const char * program_buffer, size_t size) // load program into chip memory
{
    assert(size + CHIP8_PROGRAM_START < CHIP8_MEMORY_SIZE);
    memcpy(&chip8->memory.memory_array[CHIP8_PROGRAM_START], program_buffer, size);
    chip8->registers.PC = CHIP8_PROGRAM_START;
}

char stop_until_keypress(struct Chip8 * chip8)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if(event.type == SDL_KEYDOWN)
        {
            char key = event.key.keysym.sym;
            char mapped_key = map_keyboard(&chip8->keyboard, key);
            if (mapped_key != -1) 
            { 
                return mapped_key;
            }
        }
    }
}

static void chip8_exec_com(struct Chip8 * chip8, unsigned short opcode)
{
    unsigned short nnn = opcode & 0x0fff;
    unsigned char x = (opcode >> 8) & 0x000f;
    unsigned char y = (opcode >> 4) & 0x000f;
    unsigned char kk = opcode & 0x00ff;
    unsigned char n = opcode & 0x000f;
    switch (opcode & 0xf000)
    {
        case 0x1000: 
        // The interpreter sets the program counter to nnn.
            chip8->registers.PC = nnn;
            break;
        
        case 0x2000: 
        // The interpreter increments the stack pointer, then puts the current PC on the top of the stack. The PC is then set to nnn.
            stack_push(chip8, chip8->registers.PC);
            chip8->registers.PC = nnn;
            break;
        
        case 0x3000:
        //  The interpreter compares register Vx to kk, and if they are equal, increments the program counter by 2.
            if(chip8->registers.V[x] == kk) { chip8->registers.PC += 2; }
            break;
        
        case 0x4000:
        // The interpreter compares register Vx to kk, and if they are not equal, increments the program counter by 2.
            if(chip8->registers.V[x] != kk) { chip8->registers.PC += 2; }
            break;

        case 0x5000:
        // The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2
            if(chip8->registers.V[x] == chip8->registers.V[y]) { chip8->registers.PC += 2; }
            break;
        
        case 0x6000:
        // The interpreter puts the value kk into register Vx.
            chip8->registers.V[x] = kk;
            break;

        case 0x7000:
        // Adds the value kk to the value of register Vx, then stores the result in Vx. 
            chip8->registers.V[x] += kk;
            break;

        case 0x8000:
        // has 9 variants
            switch (opcode & 0x0f)
            {
                case 0x00:
                // Stores the value of register Vy in register Vx.
                    chip8->registers.V[x] = chip8->registers.V[y];
                    break;

                case 0x01:
                // Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx.
                    chip8->registers.V[x] |= chip8->registers.V[y];
                    break;
                
                case 0x02:
                // Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx
                    chip8->registers.V[x] &= chip8->registers.V[y];
                    break;
                
                case 0x03:
                // Performs a bitwise exclusive OR on the values of Vx and Vy, then stores the result in Vx
                    chip8->registers.V[x] ^= chip8->registers.V[y];
                    break;
                
                case 0x04:
                // Set Vx = Vx + Vy, set VF = carry.
                    {
                        unsigned short temp = chip8->registers.V[x] + chip8->registers.V[y];

                        if(temp > 0xff) { chip8->registers.V[REGISTER_F] = 1; }
                        else { chip8->registers.V[REGISTER_F] = 0; }

                        chip8->registers.V[x] = temp;

                    }
                    break;
                    
                
                case 0x05:
                // If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx
                    if(chip8->registers.V[x] > chip8->registers.V[y]) { chip8->registers.V[REGISTER_F] = 1; }
                    else { chip8->registers.V[REGISTER_F] = 0; }

                    chip8->registers.V[x] -= chip8->registers.V[y];
                    break;

                case 0x06:
                // If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2
                    if((chip8->registers.V[x] & 0x01) == 1) { chip8->registers.V[REGISTER_F] = 1; } 
                    else { chip8->registers.V[REGISTER_F] = 0; }

                    chip8->registers.V[x] /= 2;
                    break;

                case 0x07:
                // If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx
                    if(chip8->registers.V[x] < chip8->registers.V[y]) { chip8->registers.V[REGISTER_F] = 1; }
                    else { chip8->registers.V[REGISTER_F] = 0; }

                    chip8->registers.V[x] = chip8->registers.V[y] - chip8->registers.V[x];
                    break;              

                case 0x0E:
                // If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
                    if((chip8->registers.V[x] & 0x80) == 0x80) { chip8->registers.V[REGISTER_F] = 1; } 
                    else { chip8->registers.V[REGISTER_F] = 0; }

                    chip8->registers.V[x] *= 2;
                    break;
            }
            break;
        
        case 0x9000:
        // The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
            if(chip8->registers.V[x] != chip8->registers.V[y]) { chip8->registers.PC += 2; }
            break;
        
        case 0xA000:
        // The value of register I is set to nnn
            chip8->registers.I = nnn;
            break;
        
        case 0xB000:
        // The program counter is set to nnn plus the value of V0.
            chip8->registers.PC = nnn + chip8->registers.V[0];
            break;
        
        case 0xC000:
        // The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx
            {
                srand(clock()); 
                chip8->registers.V[x] = kk & (rand() % 255);
            }
            break;

        case 0xD000:
        // Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision
            {
                const char * sprite_in_memory = (const char*) &chip8->memory.memory_array[chip8->registers.I];
                chip8->registers.V[REGISTER_F] = screen_set_sprite(&chip8->screen, chip8->registers.V[x], chip8->registers.V[y], sprite_in_memory, n);
            }
            break;
        
        case 0xE000:
        // has 2 variations
            switch (opcode & 0x0ff)
            {
                case 0x0AE:
                // Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2.
                    if(keyboard_is_key_down(&chip8->keyboard, chip8->registers.V[x])) { chip8->registers.PC += 2; }
                    break;
                case 0x0A1:
                // Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.
                    if(!keyboard_is_key_down(&chip8->keyboard, chip8->registers.V[x])) { chip8->registers.PC += 2; }
                    break;
            }
        
        case 0xF000:
        // has 9 variations
            switch (opcode & 0x0ff)
            {
                case 0x07:
                // The value of DT is placed into Vx.
                    chip8->registers.V[x] = chip8->registers.delay_timer;
                    break;
                
                case 0x0A:
                // All execution stops until a key is pressed, then the value of that key is stored in Vx
                    {
                        char key = stop_until_keypress(chip8);
                        chip8->registers.V[x] = key;
                    }
                    break;
                
                case 0x015:
                // DT is set equal to the value of Vx.
                    chip8->registers.delay_timer = chip8->registers.V[x];
                    break;
                
                case 0x018:
                // ST is set equal to the value of Vx.
                    chip8->registers.sound_timer = chip8->registers.V[x];
                    break;

                case 0x01E:
                // The values of I and Vx are added, and the results are stored in I.
                    chip8->registers.I += chip8->registers.V[x];
                    break;
                
                case 0x029:
                // The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx
                    chip8->registers.I = chip8->registers.V[x] * DEFAULT_SPRITE_HEIGHT;
                    break;
                
                case 0x033:
                // store BCD representation of Vx in memory locations I, I+1, and I+2
                    {
                        unsigned char hundreds = chip8->registers.V[x] / 100;
                        unsigned char tens = chip8->registers.V[x] / 10 % 10;
                        unsigned char units = chip8->registers.V[x] % 10;
                        chip8_memory_set(&chip8->memory, chip8->registers.I, hundreds);
                        chip8_memory_set(&chip8->memory, chip8->registers.I+1, tens);
                        chip8_memory_set(&chip8->memory, chip8->registers.I+2, units);
                    }
                    break;
                
                case 0x055:
                // The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.
                    for(int i = 0; i <= x; i++)
                    {
                        chip8_memory_set(&chip8->memory, chip8->registers.I + i, chip8->registers.V[i]);
                    }
                    break;
                
                case 0x65:
                // The interpreter reads values from memory starting at location I into registers V0 through Vx
                {
                    for(int i = 0; i <= x; i++)
                    {
                        chip8->registers.V[i] = chip8_memory_get(&chip8->memory, chip8->registers.I + i);
                    }
                    break;
                }
            }
            break;
    }
}

 // Todo: add super chip8 instructions
void chip8_exec(struct Chip8 * chip8, unsigned short opcode)
{
    switch (opcode)
    {
    case 0x00E0: // clears the screen
        screen_clear(&chip8->screen);
        break;
    case 0x00EE: //The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
        chip8->registers.PC = stack_pop(chip8);

    default:
        chip8_exec_com(chip8, opcode);
        break;
    }
}