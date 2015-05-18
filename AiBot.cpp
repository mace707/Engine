#include "stdafx.h"
#include "AiBot.h"
#include <OpenGl\glut.h>
#include <cmath>



AiBot::AiBot ( GLfloat x, GLfloat y )
{ 
	X = x;
	Y = y;
}


AiBot::~AiBot ( )
{ }

void AiBot::Draw ( )
{
	glPushMatrix ( );
	glBegin ( GL_QUADS );

	GLfloat qaBlack[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat qaGreen[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 };

	glMaterialfv ( GL_FRONT, GL_AMBIENT, qaGreen );
	glMaterialfv ( GL_FRONT, GL_DIFFUSE, qaGreen );
	glMaterialfv ( GL_FRONT, GL_SPECULAR, qaWhite );
	glMaterialf ( GL_FRONT, GL_SHININESS, 60.0 );

	glNormal3f ( 0.0, 0.0, 1.0 );
	glVertex2f ( X, Y );
	glVertex2f ( X, Y + 1 );
	glVertex2f ( X + 1, Y + 1 );
	glVertex2f ( X + 1, Y );

	glEnd ( );
	glPopMatrix ( );
}

double AiBot::round ( double x, int prec )
{
	double power = 1.0;
	int i;

	if ( prec > 0 )
	for ( i = 0; i < prec; i++ )
		power *= 10.0;
	else if ( prec < 0 )
	for ( i = 0; i < prec; i++ )
		power /= 10.0;

	if ( x > 0 )
		x = floor ( x * power + 0.5 ) / power;
	else if ( x < 0 )
		x = ceil ( x * power - 0.5 ) / power;

	if ( x == -0 )
		x = 0;

	return x;
}

void AiBot::Move ( GLfloat x, GLfloat y )
{
	X = round ( X, 1 ) + x;
	Y = round ( Y, 1 ) + y;
}

void AiBot::Reset(BotMode mode )
{ 
	switch ( mode )
	{
		case BotMode1: X = 20; Y = 20; break;
		case BotMode2: X = 0; Y = 20; break;
		case BotMode3: X = 20; Y = 0; break;
	}

	MovingListX.clear ( );
	MovingListY.clear ( );
}

void AiBot::FindPathToPlayer ( Grid grid, GLfloat HumanX, GLfloat HumanY )
{ 
	if ( MovingListX.size ( ) == 0 && MovingListY.size ( ) == 0 )
	{
		if ( XBotPos ( ) == HumanX && YBotPos ( ) == HumanY )
		{
			return;
		}
		if ( BotCoordList.size ( ) > 150 )
		{
			BotCoordList.clear ( );
			BotCoordList.resize ( 0 );
		}
		bool XYHumanSmaller = ( HumanX < XBotPos ( ) && HumanY < YBotPos ( ) );
		bool XYHumanBigger = ( HumanX> XBotPos ( ) && HumanY > YBotPos ( ) );
		bool XHumanSmallerYBigger = ( HumanX < XBotPos ( ) && HumanY > YBotPos ( ) );
		bool XHumanBiggerYSmaller = ( HumanX > XBotPos ( ) && HumanY < YBotPos ( ) );
		bool XEqualYBigger = ( HumanX == XBotPos ( ) && HumanY > YBotPos ( ) );
		bool XEqualYSmaller = ( HumanX == XBotPos ( ) && HumanY < YBotPos ( ) );
		bool YEqualXSmaller = ( HumanX < XBotPos ( ) && HumanY == YBotPos ( ) );
		bool YEqualXBigger = ( HumanX > XBotPos ( ) && HumanY == YBotPos ( ) );
		int x = XBotPos ( );
		int y = YBotPos ( );

		TempXBotPos = x;
		TempYBotPos = y;

		if ( XYHumanSmaller )
		{
			if ( CanMove ( grid, x - 1, y ) && !AlreadyMoved2 ( x - 1, y ) )
			{
				PopulateMoveList ( MovingListX, false );
				x -= 1;
			}
			else if ( CanMove ( grid, x, y - 1 ) && !AlreadyMoved2 ( x, y - 1 ) )
			{
				PopulateMoveList ( MovingListY, false );
				y -= 1;
			}
		}
		else if ( XYHumanBigger )
		{
			if ( CanMove ( grid, x + 1, y ) && !AlreadyMoved2 ( x + 1, y ) )
			{
				PopulateMoveList ( MovingListX, true );
				x += 1;
			}
			else if ( CanMove ( grid, x, y + 1 ) && !AlreadyMoved2 ( x, y + 1 ) )
			{
				PopulateMoveList ( MovingListY, true );
				y += 1;
			}
		}
		else if ( XHumanSmallerYBigger )
		{
			if ( CanMove ( grid, x - 1, y ) && !AlreadyMoved2 ( x - 1, y ) )
			{
				PopulateMoveList ( MovingListX, false );
				x -= 1;
			}
			else if ( CanMove ( grid, x, y + 1 ) && !AlreadyMoved2 ( x, y + 1 ) )
			{
				PopulateMoveList ( MovingListY, true );
				y += 1;
			}
		}
		else if ( XHumanBiggerYSmaller )
		{
			if ( CanMove ( grid, x + 1, y ) && !AlreadyMoved2 ( x + 1, y ) )
			{
				PopulateMoveList ( MovingListX, true );
				x += 1;
			}
			else if ( CanMove ( grid, x, y - 1 ) && !AlreadyMoved2 ( x, y - 1 ) )
			{
				PopulateMoveList ( MovingListY, false );
				y -= 1;
			}
		}
		else if ( XEqualYBigger )
		{
			if ( CanMove ( grid, x, y + 1 ) && !AlreadyMoved2 ( x, y + 1 ) )
			{
				PopulateMoveList ( MovingListY, true );
				y += 1;
			}
		}
		else if ( XEqualYSmaller )
		{
			if ( CanMove ( grid, x, y - 1 ) && !AlreadyMoved2 ( x, y - 1 ) )
			{
				PopulateMoveList ( MovingListY, false );
				y -= 1;
			}
		}
		else if ( YEqualXSmaller )
		{
			if ( CanMove ( grid, x - 1, y ) && !AlreadyMoved2 ( x - 1, y ) )
			{
				PopulateMoveList ( MovingListX, false );
				x -= 1;
			}
		}
		else if ( YEqualXBigger )
		{
			if ( CanMove ( grid, x + 1, y ) && !AlreadyMoved2 ( x + 1, y ) )
			{
				PopulateMoveList ( MovingListX, true );
				x += 1;
			}
		}
		if ( CanMove ( grid, x, y ) && !AlreadyMoved2 ( x, y ) )
		{
			//			Bot.Move ( x - Bot.XBotPos ( ), y - Bot.YBotPos ( ) );
			coords.x = XBotPos ( );
			coords.y = YBotPos ( );
			BotCoordList.push_back ( coords );
		}
		else
		{
			x = XBotPos ( );
			y = YBotPos ( );

			bool checkXMinus = false;
			bool checkYPlus = false;
			bool checkYMinus = false;

			coords.x = XBotPos ( ) + 1;
			coords.y = YBotPos ( );

			if ( CanMove ( grid, x + 1, y ) )
			{
				if ( !AlreadyMoved ( coords ) )
				{
					PopulateMoveList ( MovingListX, true );
					x += 1;
					//					Bot.Move ( x - Bot.XBotPos ( ), y - Bot.YBotPos ( ) );
					BotCoordList.push_back ( coords );
				}
				else
				{
					checkXMinus = true;
				}
			}
			else
			{
				checkXMinus = true;
			}

			if ( checkXMinus )
			{
				coords.x = XBotPos ( ) - 1;
				coords.y = YBotPos ( );

				if ( CanMove ( grid, x - 1, y ) && !AlreadyMoved ( coords ) )
				{
					if ( !AlreadyMoved ( coords ) )
					{
						PopulateMoveList ( MovingListX, false );
						x -= 1;
						//						Bot.Move ( x - Bot.XBotPos ( ), y - Bot.YBotPos ( ) );
						BotCoordList.push_back ( coords );
					}
					else
					{
						checkYMinus = true;
					}
				}
				else
				{
					checkYMinus = true;
				}
			}

			if ( checkYMinus )
			{
				coords.x = XBotPos ( );
				coords.y = YBotPos ( ) - 1;

				if ( CanMove ( grid, x, y - 1 ) && !AlreadyMoved ( coords ) )
				{
					if ( !AlreadyMoved ( coords ) )
					{
						PopulateMoveList ( MovingListY, false );
						y -= 1;
						//						Bot.Move ( x - Bot.XBotPos ( ), y - Bot.YBotPos ( ) );
						BotCoordList.push_back ( coords );
					}
					else
					{
						checkYPlus = true;
					}
				}
				else
				{
					checkYPlus = true;
				}
			}

			if ( checkYPlus )
			{
				coords.x = XBotPos ( );
				coords.y = YBotPos ( ) + 1;

				if ( CanMove ( grid, x, y + 1 ) && !AlreadyMoved ( coords ) )
				{
					if ( !AlreadyMoved ( coords ) )
					{
						PopulateMoveList ( MovingListY, true );
						y += 1;
						//						Bot.Move ( x - Bot.XBotPos ( ), y - Bot.YBotPos ( ) );
						BotCoordList.push_back ( coords );
					}

				}
			}
			//	Have a direction list as well as a coordinate list. if a block occurs, leave the second last direction int place.
		}

		if ( TempXBotPos == x && TempYBotPos == y )
		{
			BotCoordList.clear ( );
			BotCoordList.resize ( 0 );
			coords.x = XBotPos ( );
			coords.y = YBotPos ( );
			MovingListY.clear ( );
			MovingListX.clear ( );
			BotCoordList.push_back ( coords );
		}
	}
	else
	{
		if ( MovingListX.size ( ) != 0 )
		{
			Move ( round ( MovingListX.back ( ), 2 ), 0 );
			MovingListX.pop_back ( );
		}
		else if ( MovingListY.size ( ) != 0 )
		{
			Move ( 0, round ( MovingListY.back ( ), 2 ) );
			MovingListY.pop_back ( );
		}
	}

}

bool AiBot::AlreadyMoved ( BotCoords coords )
{
	for ( int i = 0; i < BotCoordList.size ( ); i++ )
	{
		if ( BotCoordList[i].x == coords.x && BotCoordList[i].y == coords.y )
		{
			return true;
		}
	}
	return false;
}

bool AiBot::AlreadyMoved2 ( int x, int y )
{
	for ( int i = 0; i < BotCoordList.size ( ); i++ )
	{
		if ( BotCoordList[i].x == x && BotCoordList[i].y == y )
		{
			return true;
		}
	}
	return false;
}


bool AiBot::CanMove ( Grid grid, int x, int y )
{
//	if ( x < -10 || x > 30 || y < -10 || y > 30 )
//		return false;
	return grid.IsNotInvalidPosition ( x, y );
}

void AiBot::PopulateMoveList ( vector<GLfloat> &list, bool positive )
{
	if ( positive )
	{
		for ( int i = 0; i < 10; i++ )
		{
			list.push_back ( 0.1 );
		}
	}
	else
	{
		for ( int i = 0; i < 10; i++ )
		{
			list.push_back ( -0.1 );
		}
	}
}