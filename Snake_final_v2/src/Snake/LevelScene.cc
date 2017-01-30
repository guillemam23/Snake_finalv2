
#include "LevelScene.hh"
#include "GameScene.hh"
#include "ID.hh"
#include "InputManager.hh"
#include "Window.hh"
using namespace std;
#include "IOManager.hh"
#include "MenuScene.hh"
#include "SceneManager.hh"

LevelScene::LevelScene() {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BACKGROUND };
	m_lvl1 = { { W.GetWidth() / 2 - (329 / 2) ,W.GetHeight() / 6, 329, 131 }, ObjectID::BUTTON1 };
	m_lvl2 = { { W.GetWidth() / 2 - (329 / 2) ,W.GetHeight() /2 - 131/2, 329, 131 }, ObjectID::BUTTON2 };
	m_lvl3 = { { W.GetWidth() / 2 - (329 / 2) ,(W.GetHeight() /6) * 4, 329, 131 }, ObjectID::BUTTON3 };

}
LevelScene::~LevelScene() {
}

void LevelScene::OnEntry(void) {
}

void LevelScene::OnExit(void) {
}

void LevelScene::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		cout << ("===============") << endl;
		cout << ("mxp: ", mouseCoords) << endl;
		mouseCoords = IM.GetMouseCoords();
	}
	

	//Detecta si esta apretat i despres detecta si esta dintre de el recuadre LEVEL 1
	
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		if ((IM.GetMouseCoords().x >= m_lvl1.transform.x && IM.GetMouseCoords().y >= m_lvl1.transform.y) &&
			(IM.GetMouseCoords().x <= (m_lvl1.transform.x + 393) && IM.GetMouseCoords().y <= (m_lvl1.transform.y + 131))) {
			m_lvl = 1;
			SM.setlvl(m_lvl);
			SM.AddScene<GameScene>();
			SM.SetCurScene<GameScene>();//Carrega escena a gamescene lvl 1
		}
	}
	//Detecta si esta apretat i despres detecta si esta dintre de el recuadre LEVEL 2
	
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		if ((IM.GetMouseCoords().x >= m_lvl2.transform.x && IM.GetMouseCoords().y >= m_lvl2.transform.y) &&
			(IM.GetMouseCoords().x <= (m_lvl2.transform.x + 393) && IM.GetMouseCoords().y <= (m_lvl2.transform.y + 131))) {
			m_lvl =2;
			SM.setlvl(m_lvl);
			SM.AddScene<GameScene>();
			SM.SetCurScene<GameScene>(); //Carrega escena a gamescene lvl 2
		}
	}
	//Detecta si esta apretat i despres detecta si esta dintre de el recuadre LEVEL 3
	
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		if ((IM.GetMouseCoords().x >= m_lvl3.transform.x && IM.GetMouseCoords().y >= m_lvl3.transform.y) &&
			(IM.GetMouseCoords().x <= (m_lvl3.transform.x + 393) && IM.GetMouseCoords().y <= (m_lvl3.transform.y + 131))) {
			m_lvl = 3;
			SM.setlvl(m_lvl);
			SM.AddScene<GameScene>();
			SM.SetCurScene<GameScene>();//Carrega escena a gamescene lvl 3
		}
	}
	else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		cout << ("mxn: ", IM.GetMouseCoords()) << endl;
	
	}


	/*if (IM.IsKeyHold<'a'>()) cout << ("a hold") << endl;
	if (IM.IsKeyDown<'0'>()) cout << ("0 down") << endl;
	if (IM.IsKeyUp<KEY_BUTTON_DOWN>())cout << ("down arrow up") << endl;*/
}

void LevelScene::Draw(void) {

	m_background.Draw();
	m_lvl1.Draw();
	m_lvl2.Draw();
	m_lvl3.Draw();

}
