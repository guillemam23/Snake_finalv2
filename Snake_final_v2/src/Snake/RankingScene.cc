#include "GameScene.hh"
#include "RankingScene.hh"
#include "SceneManager.hh"
#include "IOManager.hh"
#include "GUI.hh"

RankingScene::RankingScene() {

	//background
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BACKGROUND };

}
RankingScene::~RankingScene() {
}
void RankingScene::OnEntry(void) {

	Score scoretemp;
	scoretemp.name = SM.GetScene<GameScene>()->m_grid._name;
	scoretemp.score = SM.GetScene<GameScene>()->m_grid._score;

	//Cridem Saferanking

	IOManager::SaveRanking(scoretemp);
}

void RankingScene::OnExit(void) {
}

void RankingScene::Update(void) {
}

void RankingScene::Draw(void) {

	m_background.Draw();

	for (int i = 9; i >= 0; i--) {
		GUI::DrawTextBlended<FontID::ARIAL>(ranking[i].name + "   " + std::to_string(ranking[i].score),
		{ W.GetWidth() / 2 , W.GetHeight() - 180 - (50 * i), 1, 1 },
		{ 255, 255, 255 });
	}
	GUI::DrawTextBlended<FontID::ARIAL>("RANKING",
	{W.GetWidth()/2, 50, 1, 1 },
	{ 115, 0, 180 }); // Render score que s'anira actualitzant
}



