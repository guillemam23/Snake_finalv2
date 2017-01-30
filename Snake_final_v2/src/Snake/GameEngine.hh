#pragma once
#include <SDL/SDL.h>
#include <SDL\SDL_image.h>
#include "MenuScene.hh"
#include "LevelScene.hh"
#include "GameScene.hh"
#include "Window.hh"
#include "Renderer.hh"
#include "SceneManager.hh"
#include "InputManager.hh"
#include "TimeManager.hh"
#include "RankingScene.hh"

//Carregar arxius

namespace GameEngine {

	void LoadMedia(void) {

		R.LoadFont<FontID::ARIAL>("fnt/arial.ttf", 40);
		R.LoadFont<FontID::CANDY>("fnt/candy.ttf", 50);
		R.LoadFont<FontID::FACTORY>("fnt/candsb.ttf", 80);

		R.LoadTexture<ObjectID::BACKGROUND>("gfx/background.png");
		R.LoadTexture<ObjectID::BUTTON_PLAY>("gfx/play_button.png");
		R.LoadTexture<ObjectID::BUTTON_EXIT>("gfx/quit_button.png");
		R.LoadTexture<ObjectID::BUTTON1>("gfx/level1_button.png");
		R.LoadTexture<ObjectID::BUTTON2>("gfx/level2_button.png");
		R.LoadTexture<ObjectID::BUTTON3>("gfx/level3_button.png");
		R.LoadTexture<ObjectID::WALL>("gfx/Cellwall.png");
		R.LoadTexture<ObjectID::APPLE>("gfx/apple.png");
		R.LoadTexture<ObjectID::CELL_EMPTY>("gfx/cell_empty.png");
		R.LoadTexture<ObjectID::SNAKE_HEAD>("gfx/head.png");
		R.LoadTexture<ObjectID::SNAKE_BODY>("gfx/body.png");
		R.LoadTexture<ObjectID::TEMP>("gfx/Temp.png");
	}

	//! Adds the game scenes into the Scene Manager and decides which is the first screen

	void AddScenes(void) {
		SM.AddScene<MenuScene>();
		SM.AddScene<RankingScene>();
		SM.AddScene<LevelScene>();
		SM.SetCurScene<	MenuScene>();
	}
	/**
	* Runs the game specifying the window's name and dimensions
	* @tparam screenWidth Determines the window's width
	* @tparam screenHeight Determines the window's height
	* @param name Determines the window's title
	*/
	template<int screenWidth, int screenHeight>
	void Run(std::string &&name) {
		Window::Instance(std::move(name), screenWidth, screenHeight); // Initialize window Singleton instance for the first time
		LoadMedia(); // Loads the resource assets
		AddScenes(); // Loads the scenes
		bool m_isRunning{ true }; // Decides if the game loop is running
		Scene *&m_curScene(SM.GetCurScene()); // Defines a reference to a pointer that points to the current scene pointer (mindblown)

		while (!IM.HasQuit() && m_isRunning) { // Checks while game's still playable
#pragma region GAME_UPDATE
			TM.Update([&] {
				switch (m_curScene->GetState()) { // Check for the state of the screen
				case SceneState::RUNNING:	IM.Update(); m_curScene->Update(); break; // Updates the InputManager and the current scene
				case SceneState::EXIT:	m_isRunning = false; break; // Triggers an end of the game looping
				case SceneState::SLEEP: default:;
				}});
#pragma endregion
#pragma region GAME_DRAW
			if (m_curScene->CheckState<SceneState::RUNNING>()) { // If screen object exists and its state is running
				R.Clear();	// Clear the screen buffer
				m_curScene->Draw(); // Call the draw method of the scene
				R.Render();	// Update the screen buffer with all sprites that were pushed
			}

#pragma endregion
		}
	}
}

