
#pragma once

#include "Scene.hh"
#include "Sprite.hh"


class MenuScene : public Scene {
public: 
	explicit MenuScene();
	~MenuScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background;
	Sprite m_play;
	Sprite m_exit;
	Sprite m_lvl1;
	Sprite m_lvl2;
	Sprite m_lvl3;
	int m_score{ 0 };
};