all:
	g++ -std=c++17 -static-libstdc++ -Iinclude -Iinclude/sdl2 -Iinclude/headers -Llib -o main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer && main.exe