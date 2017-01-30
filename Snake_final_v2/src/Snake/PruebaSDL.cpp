//#include <SDL/SDL.h>
//
//int main(int, char*[]) {
//	try {
//		if (SDL_Init(SDL_INIT_VIDEO) != 0) throw SDL_GetError();
//		SDL_Log("Executable built in %s", SDL_GetBasePath());
//	}
//	catch (const char *msg) {
//		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", msg);
//	}
//	SDL_Quit();
//	return 0;
//}