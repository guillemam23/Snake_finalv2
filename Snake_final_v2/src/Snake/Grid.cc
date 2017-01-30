#include <ctime>
#include "Grid.hh"
#include "Window.hh"
#include "IOManager.hh"
#include "TimeManager.hh"
#include "RankingScene.hh"
#include "SceneManager.hh"


Grid::Grid(std::string &&filename, int cellWidth, int cellHeight,int lvl_select) {

    //Carregar el nivell desde XML

	auto lvlData(IOManager::XMLLevel("cfg/Easy.xml",lvl_select, m_rows, m_cols,m_temp, m_vel,m_alimx, m_alimy));
	startTime = clock();
	timer = m_temp;
	TM.setVel(m_vel);
	cellData = new Cell*[m_rows];
	for (int i = 0; i < m_rows; ++i)cellData[i] = new Cell[m_cols];
	srand(unsigned(time(nullptr)));
	for (int i = 0; i < m_rows; ++i) {
		for (int j = 0; j < m_cols; ++j) {
			cellData[i][j].transform.x = j * (cellWidth + 2) + ((W.GetWidth() - cellWidth*m_cols) >> 1);
			cellData[i][j].transform.y = i  * (cellHeight + 2) + ((W.GetHeight() - cellHeight*m_rows) >> 1);
			cellData[i][j].transform.w = cellWidth;
			cellData[i][j].transform.h = cellHeight;
			
			if (i == 0 || j == 0) cellData[i][j].objectID = ObjectID::WALL;
			else if (i == m_rows-1 || j == m_cols-1) cellData[i][j].objectID = ObjectID::WALL;
			else  cellData[i][j].objectID = ObjectID::CELL_EMPTY;
			FoodID(i, j) = lvlData[i][j];
		}
	}
	
	ypos = m_cols / 2;
	xpos = m_rows / 2;
	alim_eat = 0;
	snake.push_back(std::pair<int, int>(ypos-1, xpos));
	snake.push_back(std::pair<int, int>(ypos-2, xpos));
	snake.push_back(std::pair<int, int>(ypos-3, xpos));

	gridState = GridState::ADDING_APPLE;

}

int Grid::getcols() {
	return m_cols;
}
int Grid::getrows() {
	return m_rows;
}
float Grid::getvel() {
	return m_vel;
}
float Grid::gettemp() {
	return timer;
}
Grid::~Grid() {
	for (int i = 0; i < m_rows; ++i) delete[] cellData[i];
	delete[] cellData;
}

inline int Lerp(float v0, float v1, float t) {
	return int(fma(t, v1, fma(-t, v0, v0)));
}

void Grid::Update() {

	Temporitzador = { { (W.GetWidth() / 2), 45, 5*timer, 20 }, ObjectID::TEMP };
	//Comptador de temps enrere
	secondsPassed = (clock() - startTime) / CLOCKS_PER_SEC;

	if (secondsPassed >= 1) {
		timer--; 
		startTime = clock();
	}
	if (timer <= 0) {
		timer = m_temp;
		vides--;
		gridState = GridState::LOST_LIFE;
	}
	
	
	switch (gridState) {
	// Afegeix noves pomes cuan no en queden
	case GridState::ADDING_APPLE: {

		randI = rand() % (m_rows-1);
		randJ = rand() % (m_cols-1);
		if (randI == 0) randI = 1;
		if (randJ == 0) randJ = 1;
		for (int i = 1; i < m_rows; ++i) {
			for (int j = 1; j < m_cols; ++j) {
				if (i == randI && j == randJ) {
					cellData[i][j].objectID = ObjectID::APPLE;
					cout << i << "," << j << endl;
				}
			}
		}
	
		gridState = GridState::MOVING;
		break;
	}
 // Reset el estat de l'snake per tornarlo al centre
	case GridState::RESET: {

		cellData[ypos][xpos].objectID = ObjectID::CELL_EMPTY;
			dir = 5;
			xpos = m_rows / 2;
			ypos = m_cols / 2;

		cellData[ypos][xpos].objectID = ObjectID::SNAKE_HEAD;

	}
	 //Reinicia la snake, borra les cues despres de perdre una vida
	case GridState::LOST_LIFE: {
		cellData[ypos][xpos].objectID = ObjectID::CELL_EMPTY;
		for (int i = 0; i < snake.size() - 1; i++) {
			cellData[snake[i ].first][snake[i].second].objectID = ObjectID::CELL_EMPTY;
		}
		dir = 5;
		xpos = m_rows / 2;
		ypos = m_cols / 2;
		
		snake.erase(snake.begin()+numColas, snake.begin() + snake.size());
		gridState = GridState::MOVING;
		
		break;
	}
	case GridState::PAUSE: {

		break;
	}

	//Crida a la escena del Ranking (no finalitzat) 
	case GridState::GAME_FINISHED: {

		//cridar funcio guardar del ranking cc
		SM.SetCurScene<	RankingScene>();
	}
	//Detecta les tecles de moviment i cambia la direcci?del moviment.
	case GridState::MOVING: {
		//Directions: 0 - up / 1- right / 2 - down / 3 - left
		cellData[ypos][xpos].objectID = ObjectID::SNAKE_HEAD;
		
		if (IM.IsKeyDown<KEY_BUTTON_UP>() && dir != 2) {
			cout << ("Fletxa Adalt") << endl;
			dir = 0;
		}
		if (IM.IsKeyDown<KEY_BUTTON_RIGHT>() && dir != 3 && dir != 5) {
			cout << ("Fletxa Dreta") << endl;
			dir = 1;
		}
		if (IM.IsKeyDown<KEY_BUTTON_DOWN>() && dir != 0 ) {
			cout << ("Fletxa Abaix") << endl;
			dir = 2;
		}
		if (IM.IsKeyDown<KEY_BUTTON_LEFT>() && dir != 1) {
			cout << ("Fletxa Esquerra") << endl;
			dir = 3;
		}
		if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>()) {
			cout << ("Esc") << endl;
			dir = 5;

		}

		} 
	}


	//Detecta la direccio seleccionada per moure l'snake i mirar que no hi hagi colisions
	if (dir == 0) {
		ypos--;
		cellData[ypos + 1][xpos].objectID = ObjectID::CELL_EMPTY;
		snake[0].first = ypos+1;
		snake[0].second = xpos;
		if (ypos == 0) {

			//Detecci車 serp amb paret superior. Es reincia el joc i el jugador perd una vida
		
				dir = 5;
				xpos = m_rows / 2;
				ypos = m_cols / 2;
				vides --;

				cellData[ypos][xpos].objectID = ObjectID::WALL;
				gridState = GridState::LOST_LIFE;
			}

		cellData[ypos][xpos].objectID = ObjectID::SNAKE_HEAD;
	}
	if (dir == 1) {
		xpos++;
		cellData[ypos][xpos - 1].objectID = ObjectID::CELL_EMPTY;
		snake[0].first = ypos;
		snake[0].second = xpos-1;
		if (xpos + 1 == m_cols) {

			//Detecci車 serp amb paret dreta. Es reincia el joc i el jugador perd una vida

			dir = 5;
			xpos = m_rows / 2;
			ypos = m_cols / 2;
			vides--;

			cellData[ypos][xpos].objectID = ObjectID::WALL;
			gridState = GridState::LOST_LIFE;
		}
		cellData[ypos][xpos].objectID = ObjectID::SNAKE_HEAD;
	}
	if (dir == 2) {
		ypos++;
		cellData[ypos - 1][xpos].objectID = ObjectID::CELL_EMPTY;
		snake[0].first = ypos-1;
		snake[0].second = xpos;
		if (ypos +1 == m_rows) {

			//Detecci車 serp amb paret inferior. Es reincia el joc i el jugador perd una vida

			dir = 5;
			xpos = m_rows / 2;
			ypos = m_cols / 2;
			vides--;

			cellData[ypos][xpos].objectID = ObjectID::WALL;
			gridState = GridState::LOST_LIFE;
		}
		cellData[ypos][xpos].objectID = ObjectID::SNAKE_HEAD;
	}
	if (dir == 3) {
		xpos--;
		cellData[ypos][xpos+1].objectID = ObjectID::CELL_EMPTY;
		snake[0].first = ypos;
		snake[0].second = xpos+1;
		if (xpos == 0) {
			//Detecci車 serp amb paret esquerra. Es reincia el joc i el jugador perd una vida
			dir = 5;
			xpos = m_rows / 2;
			ypos = m_cols / 2;
			vides--;

			cellData[ypos][xpos].objectID = ObjectID::WALL;
			gridState = GridState::LOST_LIFE;
		}
		cellData[ypos][xpos].objectID = ObjectID::SNAKE_HEAD;

	}
	if (dir == 5) {
		snake[0].first = ypos;
		snake[0].second = xpos+1;
		cellData[ypos][xpos].objectID = ObjectID::SNAKE_HEAD;
	}
	
	//Comprovaci?per veure si menja pomes.
	if (ypos == randI && xpos == randJ) {
		snake.push_back(std::pair<int, int>(randI, randJ));	
		alim_eat++;
		_score = _score + (alim_eat*100);
		m_vel = m_vel + 1.0f;
		TM.setVel(m_vel);
		cout << TM.getVel() << endl;
		gridState = GridState::ADDING_APPLE;
	}
	//Comprovaci?per veure si s ha arribat a menjar les pomes necesaries per pujar de Level
	if (alim_eat == m_alimx + (m_alimy * level)) {

		cellData[ypos][xpos + 1].objectID = ObjectID::CELL_EMPTY;
		level++;
		numColas = snake.size();
		//guardado colas x lvl
		alim_eat = 0;
		dir = 5;
		xpos = m_rows / 2;
		ypos = m_cols / 2;
		gridState = GridState::ADDING_APPLE;
		cout << "lvl up" << endl;

	}
	//comprovaci?per veure si s ha perdut la partida a 0 vides
	if (vides == 0) {
		//menu ranking
		gridState = GridState::GAME_FINISHED;
		cout << "Has perdido" << endl;
	}
	//Borra el cos de l'snake anterior i cambia posicions dels bodies de l'snake per fer el moviment del cos
	for (int i = snake.size() - 1; i > 0; i--) {
		cellData[snake[snake.size()-1].first][snake[snake.size() - 1].second].objectID = ObjectID::CELL_EMPTY;
		snake[i].first = snake[i - 1].first;
		snake[i].second = snake[i - 1].second;
		cellData[snake[i].first][snake[i].second].objectID = ObjectID::SNAKE_BODY;

	}
	//Comproba si el cap toca el cos de l'snake per perdre una vida
	for (int i = 0; i < snake.size() - 1; i++) {
		if (snake[i].first == ypos && snake[i].second == xpos) {
			vides--;
			gridState = GridState::RESET;
		}
	}

}

void Grid::Draw() {

	for (int i = 0; i < m_rows; ++i) for (int j = 0; j < m_cols; ++j) cellData[i][j].Draw();
	for (int i = 0; i < m_rows; ++i) for (int j = 0; j < m_cols; ++j) { cellData[i][j].apple.Draw();
	}
	Temporitzador.Draw();
}