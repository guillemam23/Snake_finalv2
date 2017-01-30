
#pragma once
#include "Sprite.hh"
#include "InputManager.hh"
#include <utility>
#include <time.h>
using namespace std;

class Grid {
public:
	Grid(std::string &&fileName, int cellWidth, int cellHeight,int lvl_select);
	~Grid();
	void Update();
	void Draw();
	int getrows();
	int getcols();
	float getvel();
	float gettemp();
	int _score = 0;
	std::string _name;
	int vides = 3;
	
private:
	inline ObjectID &FoodID(int i, int j) const { return cellData[i][j].apple.objectID; }
	inline Transform &AppleTransform(int i, int j) const { return cellData[i][j].apple.transform; }
	inline ObjectID &SnakeID(int i, int j)const { return snakeData[i][j].body.objectID; }

private:
	enum class MoveType { UP, LEFT, DOWN, RIGHT };
	enum class GridState {RESET, COLLISION,MOVING, ADDING_APPLE,ADDING_BODY,PAUSE,LOST_LIFE,GAME_FINISHED};
	struct Cell : public Sprite { Sprite apple; } **cellData; 
	struct Body : public Sprite { Sprite body; } **snakeData;
	int m_rows, m_cols, m_alimx, m_alimy,m_temp, timer;
	float   m_vel;
	double secondsPassed;
	clock_t startTime;
	GridState gridState;
	struct {
		int fromX, fromY, toX, toY;
		Transform fromPos;
		Transform toPos;
		float percent = 0.0f;
		bool reSwap = false;
		void Set(int fx, int fy, int tx, int ty, const Transform &fp, const Transform &tp) {
			fromX = fx, fromY = fy, toX = tx, toY = ty, fromPos = fp, toPos = tp;
		};
	} swapInfo; 
	struct {
		int i, j, fromPos, toPos;
		float percent = 0.0f;
	} shiftInfo;

	vector <std::pair<int,int>> snake;
	Sprite Temporitzador;
	int xpos, ypos;
	int dir = 5;
	int randI, randJ;
	int alim_eat;
	int level = 0;
	int numColas = 3;
};