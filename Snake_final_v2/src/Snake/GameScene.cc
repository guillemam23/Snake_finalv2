#include "GUI.hh"
#include "LevelScene.hh"
#include "GameScene.hh"
#include "SceneManager.hh"
#include "Grid.hh"
#include "ID.hh"
#include "InputManager.hh"
#include "Window.hh"
#include "IOManager.hh"

using namespace std;
#define CELL_WIDTH 15
#define CELL_HEIGHT 15

GameScene::GameScene() : m_grid("res/cfg/Easy.xml", CELL_WIDTH, CELL_HEIGHT,SM.getlvl()) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BACKGROUND };
	m_apple = { {350, 250, CELL_WIDTH, CELL_HEIGHT}, ObjectID::APPLE };
}

GameScene::~GameScene() {
}

void GameScene::OnEntry(void) {
	cout << "Introduce tu nombre: " << endl;
	cin >> m_grid._name;
	if (m_grid._name.size() > 5) {
		m_grid._name.resize(5);
	}
	cout << m_grid._name << endl;

}

void GameScene::OnExit(void) {
}

void GameScene::Update(void) {
	m_grid.Update(); // Update grid
	m_temp = m_grid.gettemp();
}

void GameScene::Draw(void) {
	m_background.Draw();
	m_grid.Draw(); // Render grid

	GUI::DrawTextBlended<FontID::ARIAL>("Score: " + std::to_string(m_grid._score),
	{ 100, 50, 1, 1 },
	{ 115, 0, 180 }); // Render score que s'anira actualitzant

	GUI::DrawTextBlended<FontID::ARIAL>("Timer: " ,
	{ 450, 50, 1, 1 },
	{ 115, 0, 180 }); // Render score que s'anira actualitzant


	GUI::DrawTextBlended<FontID::ARIAL>("Vides: " + std::to_string(m_grid.vides),
	{ 924, 50, 1, 1 },
	{ 115, 0, 180 }); // Render vides que s'anira actualitzant

}
