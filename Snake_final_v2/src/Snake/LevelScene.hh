#pragma once

#include "Scene.hh"
#include "Sprite.hh"



class LevelScene : public Scene {
public:
	friend class MenuScene;
	explicit LevelScene();
	~LevelScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	int m_lvl;
private:
	//Grid m_grid;
	Sprite m_background;
	Sprite m_lvl1;
	Sprite m_lvl2;
	Sprite m_lvl3;
	int m_score{ 0 };

};
