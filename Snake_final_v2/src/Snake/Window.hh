
//WINDOW

#pragma once
#include <string>
#include <SDL/SDL.h>
#include "Assert.hh"

#define W Window::Instance()

// Window class to store the whole info related to the game screen interface
class Window {
	Window(const std::string &&name, int &&screenWidth, int &&screenHeight) : m_name(name), m_screenWidth(screenWidth), m_screenHeight(screenHeight) {
		//Initialize SDL & Set texture filtering to linear
		ASSERT(!SDL_Init(SDL_INIT_EVERYTHING));
		ASSERT(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"));
		//Create window
		m_SDLWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		ASSERT(m_SDLWindow != nullptr);
	}
	Window(const Window &rhs) = delete;
	Window &operator=(const Window &rhs) = delete;
public:
	inline static Window &Instance(std::string &&name = "", int &&screenWidth = 0, int &&screenHeight = 0) {
		static Window window(std::move(name), std::move(screenWidth), std::move(screenHeight));
		return window;
	}
	~Window() {
		SDL_DestroyWindow(m_SDLWindow), m_SDLWindow = nullptr; //Destroy window
		SDL_Quit(); //Quit SDL subsystems
	}
	inline SDL_Window* operator()(void) const { return m_SDLWindow; }
	inline int GetWidth(void) const { return m_screenWidth; };
	inline int GetHeight(void) const { return m_screenHeight; };
	inline const std::string &GetName(void) const { return m_name; };
private:
	SDL_Window* m_SDLWindow{ nullptr };
	const int m_screenWidth, m_screenHeight;
	const std::string m_name;
};

//
////RENDERER
//SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//
//if (renderer == nullptr) throw SDL_GetError();
//
////SPRITES
//
//SDL_Texture *bgTexture = IMG_LoadTexture(renderer, "../../res/gfx/bg.jpg");
//SDL_Texture *playerTexture = IMG_LoadTexture(renderer, "../../res/gfx/blue.png");
//
//if (bgTexture == nullptr || playerTexture == nullptr) throw SDL_GetError();
//
//SDL_Rect bgRect = { 0,0, WIDTH, HEIGHT };
//SDL_Rect playerRect = { (WIDTH >> 1) - 50, (HEIGHT >> 1) - 50, 100,100 };
//SDL_Rect playerTarget = { 0,0, 100, 100 };
//
////DESTROY
//SDL_DestroyTexture(bgTexture);
//SDL_DestroyTexture(playerTexture);
//SDL_DestroyWindow(window);
//SDL_DestroyRenderer(renderer);
//
//	}
//
//	IMG_Quit();
//	SDL_Quit();
//	return 0;
//}

