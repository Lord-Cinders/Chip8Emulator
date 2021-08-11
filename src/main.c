/*
 Chip8 Emulator
 Started on 3/8/21
*/

#include <stdio.h>
#include <Windows.h>
#include "SDL2/SDL.h"
#include "Chip8.h"

// virtual key = index of physical key in map
const char keyboard_map[CHIP8_KEYBOARD_SIZE] = {
    SDLK_0, SDLK_1, SDLK_2, SDLK_3,
    SDLK_4, SDLK_5, SDLK_6, SDLK_7,
    SDLK_8, SDLK_9, SDLK_a, SDLK_b,
    SDLK_c, SDLK_d, SDLK_e, SDLK_f};

int main(int argsc, char **argv)
{

    if(argsc < 2)
    {
        printf("File was not specified\n");
        return -1;
    }
    
    const char *filename = argv[1];
    printf("File to read: %s\n", filename);

    FILE* f = fopen(filename, "rb");
    if(!f)
    {
        printf("File failed to load\n");
        fclose(f);
        return -1;
    }

    fseek(f, 0, SEEK_END); 
    long size = ftell(f); // retuns the current file position
    fseek(f, 0, SEEK_SET);

    char buff[size];

    int res = fread(buff, size, 1, f);
    if(res != 1)
    {
        printf("Unable to open file\n");
        fclose(f);
        return -1;
    }

    struct Chip8 chip8;
    CHIP8_Init(&chip8);

    chip8_load(&chip8, "hello", sizeof("hello"));

    // TODO: Shift everything into a differnt file

    // Setting up SDL to Emulate a 640x320p display
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow(
        SCREEN_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH * SCREEN_MULTIPLIER,
        SCREEN_HEIGHT * SCREEN_MULTIPLIER,
        SDL_WINDOW_SHOWN);

    // Needed to render/draw pixels on the window display
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_TEXTUREACCESS_TARGET);
    int w = 0, l = 0;
    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    SDL_DestroyWindow(window);
                    return 0;

                case SDL_KEYDOWN:
                {   
                    char key = event.key.keysym.sym;
                    int mapped_key = map_keyboard(keyboard_map, key);
                    if (mapped_key != -1) { keyboard_key_down(&chip8.keyboard, mapped_key); }
                }
                break;

                case SDL_KEYUP:
                {
                    char key = event.key.keysym.sym;
                    int mapped_key = map_keyboard(keyboard_map, key);
                    if (mapped_key != -1) { keyboard_key_up(&chip8.keyboard, mapped_key); }
                }
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);

        // display test
        // if (w == 64)
        // {
        //     w == 0;
        // }

        // screen_set_sprite(&chip8.screen, 1 + w, 1, &chip8.memory.memory_array[0x1e], 5);
        // screen_set_sprite(&chip8.screen, 6 + w, 1, &chip8.memory.memory_array[0x2d], 5);
        // screen_set_sprite(&chip8.screen, 11 + w, 1, &chip8.memory.memory_array[0x14], 5);
        // screen_set_sprite(&chip8.screen, 16 + w, 1, &chip8.memory.memory_array[0x0a], 5);
        // screen_set_sprite(&chip8.screen, 21 + w, 1, &chip8.memory.memory_array[0x00], 5);

        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            for (int y = 0; y < SCREEN_HEIGHT; y++)
            {
                if (screen_pixels_is_set(&chip8.screen, x, y))
                {
                    SDL_Rect r;
                    r.x = x * SCREEN_MULTIPLIER;
                    r.y = y * SCREEN_MULTIPLIER;
                    r.h = SCREEN_MULTIPLIER;
                    r.w = SCREEN_MULTIPLIER;
                    SDL_RenderFillRect(renderer, &r);
                }
            }
        }
        SDL_RenderPresent(renderer);

        // screen_remove_sprite(&chip8.screen, 1 + w, 1, &chip8.memory.memory_array[0x1e], 5);
        // screen_remove_sprite(&chip8.screen, 6 + w, 1, &chip8.memory.memory_array[0x2d], 5);
        // screen_remove_sprite(&chip8.screen, 11 + w, 1, &chip8.memory.memory_array[0x14], 5);
        // screen_remove_sprite(&chip8.screen, 16 + w, 1, &chip8.memory.memory_array[0x0a], 5);
        // screen_remove_sprite(&chip8.screen, 21 + w, 1, &chip8.memory.memory_array[0x00], 5);
        // w++;
        screen_clear(&chip8.screen);


        if (chip8.registers.delay_timer > 0)
        {
            Sleep(100);
            chip8.registers.delay_timer -= 1;
        }

        if (chip8.registers.sound_timer > 0)
        {
            Beep(500, 100 * chip8.registers.sound_timer);
            chip8.registers.sound_timer = 0;
            // or
            // Beep(500, 100);
            // chip8.registers.sound_timer--;
        }

        unsigned short opcode = chip8_memory_get_short(&chip8.memory, chip8.registers.PC);
        chip8_exec(&chip8, opcode);
        // chip8.registers.PC += 2; // inst is 2 bytes.
    }
    
}