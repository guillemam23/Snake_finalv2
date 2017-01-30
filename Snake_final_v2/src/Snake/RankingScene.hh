#pragma once
#include "Scene.hh"
#include "Sprite.hh"
#include "Score.hh"


class RankingScene : public Scene {
public:
	//friend class MenuScene;
	explicit RankingScene();
	~RankingScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	Score ranking[10] = {};

private:
	Sprite m_background;

};
