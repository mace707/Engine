#pragma once
#include <OpenGl\glut.h>
#include <vector>
#include "Grid.h"
using namespace std;
class Player
{
	public:

	enum Direction
	{
		Default = 0,
		Down = 1,
		Up = 2,
		Left = 3,
		Right = 4
	};

	Player ( );
	~Player ( );
	void Move ( GLfloat x, GLfloat y);
	void Draw ( );

	GLfloat XPlayerPos ( ) { return X; }
	GLfloat YPlayerPos ( ) { return Y; }
	void Move ( Grid grid );
	double round ( double x, int prec );
	void PopulateMoveList ( vector<GLfloat> &list, bool positive );
	bool CanMove ( Grid grid, int x, int y );
	void setPlayerDirection ( Direction playerDir );

	private:
	static GLfloat X, Y;
	vector<GLfloat> PlayerMoveListX;
	vector<GLfloat> PlayerMoveListY;
	Direction PlayerDirection = Default;
};

