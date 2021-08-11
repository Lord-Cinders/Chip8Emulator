INCLUDES= -I ./include
FLAGS= -g
OBJECTS= ./build/Chip8Memory.o ./build/Chip8Stack.o ./build/Chip8Keyboard.o ./build/Chip8Screen.o ./build/Chip8.o

all: $(OBJECTS)
	gcc $(FLAGS) $(INCLUDES) ./src/main.c $(OBJECTS) -L ./lib -lmingw32 -lSDL2main -lSDL2 -o ./bin/main

./build/Chip8Memory.o: ./src/Chip8Memory.c
	gcc $(FLAGS) $(INCLUDES) ./src/Chip8Memory.c -c -o ./build/Chip8Memory.o

./build/Chip8Stack.o: ./src/Chip8Stack.c
	gcc $(FLAGS) $(INCLUDES) ./src/Chip8Stack.c -c -o ./build/Chip8Stack.o

./build/Chip8Keyboard.o: ./src/Chip8Keyboard.c
	gcc $(FLAGS) $(INCLUDES) ./src/Chip8Keyboard.c -c -o ./build/Chip8Keyboard.o

./build/Chip8Screen.o: ./src/Chip8Screen.c
	gcc $(FLAGS) $(INCLUDES) ./src/Chip8Screen.c -c -o ./build/Chip8Screen.o

./build/Chip8.o: ./src/Chip8.c
	gcc $(FLAGS) $(INCLUDES) ./src/Chip8.c -c -o ./build/Chip8.o

clean:
	del build\*