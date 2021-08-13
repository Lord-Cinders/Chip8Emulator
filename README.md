## Chip8 Emulator

CHIP-8 is an interpretted programming language developed by Joseph Weisbecker in the mid 70s and was initally used on the COSMAC VIP and Telmac 1800 8-bit microcomputers to make game programming easier. CHIP-8 programs are run using a CHIP-8 virtual machine.

### What it does

Runs code intended for the chip8 on modern hardware.

### Does it work

Yes, kindof.

![Invaders](https://github.com/Cinder-Binder/Chip8Emulator/blob/master/screenshots/Invaders.PNG)\
*Space Invaders*

![Tetris](https://github.com/Cinder-Binder/Chip8Emulator/blob/master/screenshots/Pong.PNG)\
 *Tetris*

![Pong](https://github.com/Cinder-Binder/Chip8Emulator/blob/master/screenshots/Tetris.PNG)\
                                         *Pong*



## Compiling and Running

Everything you need to build the project are in the repo (only works on windows for now).
Navigate to the root of the project and use:
```
>> mingw32-make 
```

run:
```
>> cd bin
>> ./main.exe ./[ROM]
```
23 (public domain) ROMs are included in the `bin` directory.


### Based on cowgod's chip8 technical reference - http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#0.





