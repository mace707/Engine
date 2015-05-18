#pragma once
#include <OpenGl\glut.h>
#include <vector>
#include "Grid.h"
using namespace std;
class AiBot
{
	public:
	AiBot ( GLfloat x, GLfloat y );
	~AiBot ( );
	void Draw ( );
	void Move ( GLfloat x, GLfloat y );

	int XBotPos ( ) { return X; }
	int YBotPos ( ) { return Y; }

	double round ( double x, int prec );
	
	void FindPathToPlayer ( Grid grid, GLfloat HumanX, GLfloat HumanY );

	enum BotMode
	{
		BotMode1 = 0,
		BotMode2 = 1,
		BotMode3 = 2,
	};

	void Reset (BotMode mode);

	struct BotCoords
	{
		int x, y;
	};

	bool AlreadyMoved ( BotCoords coords );
	bool AlreadyMoved2 ( int x, int y );
	bool CanMove ( Grid grid, int x, int y );
	void PopulateMoveList ( vector<GLfloat> &list, bool positive );

	private:
	GLfloat X, Y;
	int TempXBotPos, TempYBotPos;
	vector<GLfloat> MovingListX;
	vector<GLfloat> MovingListY;
	vector<BotCoords> BotCoordList;
	BotCoords coords;
};

