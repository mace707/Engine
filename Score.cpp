#include "stdafx.h"
#include "Score.h"
#include <sstream>
#include <OpenGl\glut.h>
using namespace std;

Score::Score ( )
{ }


Score::~Score ( )
{ }

void Score::DrawScore ( int score)
{ 
	stringstream ss;
	ss << score;
	string sScore = ss.str();
	for ( int i = 0; i < sScore.length ( ); i++ )
	{
		glPushMatrix ( );
		glTranslatef ( i*2, 52 , 0 );
		DrawNumber ( sScore[i] );
		glPopMatrix ( );
	}

}

void Score::DrawNumber(int num, int xPos, int yPos)
{
	stringstream ss;
	ss << num;
	string sScore = ss.str ( );
	for ( int i = 0; i < sScore.length ( ); i++ )
	{
		glPushMatrix ( );
		glTranslatef ( xPos, yPos, 0 );
		glColor3f ( 1, 0, 0 );
		DrawNumber ( sScore[i] );
		glPopMatrix ( );
	}
}

void Score::DrawNumber ( char val )
{ 
	switch ( val )
	{
		case '0': DrawZero ( ); break;
		case '1': DrawOne ( ); break;
		case '2': DrawTwo ( ); break;
		case '3': DrawThree ( ); break;
		case '4': DrawFour ( ); break;
		case '5': DrawFive ( ); break;
		case '6': DrawSix ( ); break;
		case '7': DrawSeven ( ); break;
		case '8': DrawEight ( ); break;
		case '9': DrawNine ( ); break;
	}
}

void Score::DrawZero ( )
{
	glPushMatrix ( );
	glBegin ( GL_LINES );

	glVertex2f ( 0, 0 );
	glVertex2f ( 0, 5 );

	glVertex2f ( 1, 0 );
	glVertex2f ( 1, 5 );

	glVertex2f ( 0, 0 );
	glVertex2f ( 1, 0 );

	glVertex2f ( 0, 5 );
	glVertex2f ( 1, 5 );

	glEnd ( );
	glPopMatrix ( );
}


void Score::DrawOne ( )
{ 
	glPushMatrix ( );
	glBegin ( GL_LINES );

	glVertex2f ( 0, 0 );
	glVertex2f ( 0, 5 );

	glEnd ( );
	glPopMatrix ( );
}

void Score::DrawTwo ( )
{
	glPushMatrix ( );
	glBegin ( GL_LINES );
	glVertex2f ( 0, 0 );
	glVertex2f ( 1, 0 );

	glVertex2f ( 0, 0 );
	glVertex2f ( 0, 3 );

	glVertex2f ( 0, 3 );
	glVertex2f ( 1, 3 );

	glVertex2f ( 1, 3 );
	glVertex2f ( 1, 5 );

	glVertex2f ( 1, 5 );
	glVertex2f ( 0, 5 );
	glEnd ( );
	glPopMatrix ( );
}

void Score::DrawThree ( )
{
	glPushMatrix ( );
	glBegin ( GL_LINES );

	glVertex2f ( 1, 5 );
	glVertex2f ( 1, 0 );
	glVertex2f ( 0, 0 );
	glVertex2f ( 1, 0 );
	glVertex2f ( 0, 3 );
	glVertex2f ( 1, 3 );
	glVertex2f ( 0, 5 );
	glVertex2f ( 1, 5 );

	glEnd ( );
	glPopMatrix ( );
}

void Score::DrawFour ( )
{
	glPushMatrix ( );
	glBegin ( GL_LINES );

	glVertex2f ( 1, 5 );
	glVertex2f ( 0, 1 );
	glVertex2f ( 0, 1 );
	glVertex2f ( 1, 1 );
	glVertex2f ( 1, 5 );
	glVertex2f ( 1, 0 );

	glEnd ( );
	glPopMatrix ( );
}

void Score::DrawFive ( )
{
	glPushMatrix ( );
	glBegin ( GL_LINES );

	glVertex2f ( 1, 5 );
	glVertex2f ( 0, 5 );
	glVertex2f ( 0, 5 );
	glVertex2f ( 0, 3 );
	glVertex2f ( 0, 3 );
	glVertex2f ( 1, 3 );
	glVertex2f ( 1, 3 );
	glVertex2f ( 1, 0 );
	glVertex2f ( 1, 0 );
	glVertex2f ( 0, 0 );

	glEnd ( );
	glPopMatrix ( );
}

void Score::DrawSix ( )
{
	glPushMatrix ( );
	DrawFive ( );
	glBegin ( GL_LINES );

	
	glVertex2f ( 0, 0 );
	glVertex2f ( 0, 3 );

	glEnd ( );
	glPopMatrix ( );
}

void Score::DrawSeven ( )
{
	glPushMatrix ( );
	glBegin ( GL_LINES );

	glVertex2f ( 0, 5 );
	glVertex2f ( 1, 5 );
	glVertex2f ( 1, 5 );
	glVertex2f ( 1, 0 );

	glEnd ( );
	glPopMatrix ( );
}

void Score::DrawEight ( )
{
	glPushMatrix ( );

	DrawOne ( );
	DrawThree ( );

	glPopMatrix ( );
}

void Score::DrawNine ( )
{
	glPushMatrix ( );
	glTranslatef ( 1, 5, 0 );
	glRotatef ( 180, 0, 0, 1 );
	DrawSix ( );

	glPopMatrix ( );
}