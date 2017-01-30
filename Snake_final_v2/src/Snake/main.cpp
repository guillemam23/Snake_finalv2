

//#include "GameEngine.hh"
#include <iostream>
#include "GameEngine.hh"

// Game constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

int main(int argc, char* args[]) {
	GameEngine::Run<SCREEN_WIDTH, SCREEN_HEIGHT>("Snake");
	
	return 0;

	system("pause");
}