
#include "MenuScene.hh"
#include "LevelScene.hh"
#include "SceneManager.hh"
#include "ID.hh"
#include "InputManager.hh"
#include "Window.hh"
using namespace std;



MenuScene::MenuScene() {

	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BACKGROUND };
	m_play = { {W.GetWidth() / 2-(329/2) ,W.GetHeight()  / 4, 329, 131 }, ObjectID::BUTTON_PLAY };
	m_exit = { { W.GetWidth() / 2 - (329 / 2) ,W.GetHeight() / 2 +45, 329, 131 }, ObjectID::BUTTON_EXIT };
	

}
MenuScene::~MenuScene() {
}

void MenuScene::OnEntry(void) {
}

void MenuScene::OnExit(void) {
}

void MenuScene::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
	cout<<("===============")<< endl;
		cout <<("mxp: ", mouseCoords)<< endl;
		mouseCoords = IM.GetMouseCoords();
	}
	
	//Detecta si esta apretat i despres detecta si esta dintre de el recuadre play
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		if ((IM.GetMouseCoords().x >= m_play.transform.x && IM.GetMouseCoords().y >= m_play.transform.y) && 
			(IM.GetMouseCoords().x <= (m_play.transform.x + 393) && IM.GetMouseCoords().y <= (m_play.transform.y + 131))) {
			SM.SetCurScene<	LevelScene>();
			cout << "play" << endl;
		}
	}
	//Detecta si esta apretat i despres detecta si esta dintre de el recuadre exit
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		if ((IM.GetMouseCoords().x >= m_exit.transform.x && IM.GetMouseCoords().y >= m_exit.transform.y) && 
			(IM.GetMouseCoords().x <= (m_exit.transform.x + 393) && IM.GetMouseCoords().y <= (m_exit.transform.y + 131))) {
			cout << "exit" << endl;
			SetState<SceneState::EXIT>();
		
		}
	}
	else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		cout << ("mxn: ", IM.GetMouseCoords())<< endl;
	}
							// Test InputManager key methods
	if (IM.IsKeyHold<'a'>()) cout << ("a hold") << endl;
	if (IM.IsKeyDown<'0'>()) cout << ("0 down") << endl;
	if (IM.IsKeyUp<KEY_BUTTON_DOWN>())cout << ("down arrow up") << endl;
}

void MenuScene::Draw(void) {
	m_background.Draw();
	m_play.Draw();
	m_exit.Draw();
	

}
