#include "stdafx.h"
#include "Squar.h"
#include <OpenGl\glut.h>

Squar::Squar ( )
{ }


Squar::~Squar ( )
{ }

void Squar::Draw ( int x1, int y1, int x2, int y2, Color col, bool token )
{
	glPushMatrix ( );
	glBegin ( GL_QUADS );
	glEnable ( GL_LIGHTING );
	glNormal3f ( 0.0, 0.0, 1.0 );
	if ( token )
	{
		double x1f = x1 + 0.25;
		double x2f = x2 - 0.25;
		double y1f = y1 + 0.25;
		double y2f = y2 - 0.25;

		glVertex2f ( x1f, y1f );
		glVertex2f ( x1f, y2f );
		glVertex2f ( x2f, y2f );
		glVertex2f ( x2f, y1f );
	}
	else
	{
		glVertex2f ( x1, y1 );
		glVertex2f ( x1, y2 );
		glVertex2f ( x2, y2 );
		glVertex2f ( x2, y1 );
	}
	

	

	glEnd ( );
	glPopMatrix ( );
}

