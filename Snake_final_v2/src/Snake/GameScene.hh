#pragma once

#include "Grid.hh" 
#include "Scene.hh"
#include "Sprite.hh"

// LevelScene class with the main gameplay mode

class GameScene : public Scene {
public:
	friend class LevelScene;
	explicit GameScene();
	~GameScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	Grid m_grid;
	
private:
	Sprite m_background;
	Sprite m_wall;
	Sprite m_apple;
	int m_score{ 0 };
	int m_vides{ 3 };
	float m_temp;
};
