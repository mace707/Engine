#include "stdafx.h"
#include "Player.h"
#include <OpenGl\glut.h>
#include <cmath>
GLfloat Player::X = -24;
GLfloat Player::Y = -24;

Player::Player ( )
{ }


Player::~Player ( )
{ }

void Player::setPlayerDirection ( Direction playerDir )
{ 
	PlayerDirection = playerDir;
}

void Player::Draw ( )
{ 
	glPushMatrix ( );
	glBegin ( GL_QUADS );
	glColor3f(0, 1, 0);
	glVertex2f ( X, Y );
	glVertex2f ( X, Y + 1 );
	glVertex2f ( X + 1, Y + 1 );
	glVertex2f ( X + 1, Y );

	glEnd ( );
	glPopMatrix ( );
}


void Player::Move (Grid grid )
{

	if ( PlayerMoveListX.size ( ) == 0 && PlayerMoveListY.size ( ) == 0 )
	{
		int x = XPlayerPos ( );
		int y = YPlayerPos ( );

		switch ( PlayerDirection )
		{
			case Up: y += 1; break;
			case Down: y -= 1; break;
			case Left: x -= 1; break;
			case Right: x += 1; break;
		}

		if ( CanMove (grid, x, y ) )
		{
			if ( PlayerDirection == Up )
			{
				PopulateMoveList ( PlayerMoveListY, true );
			}
			else if ( PlayerDirection == Down )
			{
				PopulateMoveList ( PlayerMoveListY, false );
			}
			else if ( PlayerDirection == Left )
			{
				PopulateMoveList ( PlayerMoveListX, false );
			}
			else if ( PlayerDirection == Right )
			{
				PopulateMoveList ( PlayerMoveListX, true );
			}
		}
	}
	else
	{
		if ( PlayerDirection == Up || PlayerDirection == Down )
		{
			if ( PlayerMoveListY.size ( ) != 0 )
			{
				Move ( 0, round ( PlayerMoveListY.back ( ), 2 ) );
				PlayerMoveListY.pop_back ( );
			}
			else if ( PlayerMoveListX.size ( ) != 0 )
			{
				Move ( round ( PlayerMoveListX.back ( ), 2 ), 0 );
				PlayerMoveListX.pop_back ( );
			}
		}
		else if ( PlayerDirection == Left || PlayerDirection == Right )
		{
			if ( PlayerMoveListX.size ( ) != 0 )
			{
				Move ( round ( PlayerMoveListX.back ( ), 2 ), 0 );
				PlayerMoveListX.pop_back ( );
			}
			else if ( PlayerMoveListY.size ( ) != 0 )
			{
				Move ( 0, round ( PlayerMoveListY.back ( ), 2 ) );
				PlayerMoveListY.pop_back ( );
			}
		}
	}
}

void Player::PopulateMoveList ( vector<GLfloat> &list, bool positive )
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

double Player::round ( double x, int prec )
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

bool Player::CanMove ( Grid grid, int x, int y )
{
//	if ( x < -10 || x > 30 || y < -10 || y > 30 )
//		return false;
	return grid.IsNotInvalidPosition ( x, y );
}

void Player::Move ( GLfloat x, GLfloat y )
{
	X = round(X,1) + x;
	Y = round(Y,1) + y;
}