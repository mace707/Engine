#pragma comment(lib, "winmm.lib")

#include "stdafx.h"
#include <OpenGl\glut.h>
#include <mmsystem.h>
#include <Windows.h>
#include "Grid.h"
#include "Player.h"
#include "AiBot.h"
#include "Score.h"

enum MENU_ITEM
{
	ITEM_START		= 11,
	ITEM_PAUSE		= 12,
	ITEM_RESET		= 13,

	ITEM_LOAD		= 21,
	ITEM_SAVE		= 22,

	ITEM_WALL		= 31,
	ITEM_TOKEN		= 32,
	ITEM_REMOVE		= 33,

	ITEM_SINGLE		= 41,
	ITEM_MULTI		= 42,
};	

enum BuildingBlock
{ 
	BB_Token,
	BB_Wall,
	BB_Remove,
};

enum BuildingMode
{
	BM_SINGLE,
	BM_MULTI
};

void Init			( void );
void Display		( void );
void Reshape		( int w, int h );
void KeyBoardFunc	( int key, int h, int w );
void IdleFunc		( void );
void Mouse			( int button, int state, int x, int y );
void FindPlayer		( );
void menu			( int item);
void DrawGrid		( );

Grid MainGrid;
Player HumanPlayer;
AiBot Bot ( 24, 24 );
AiBot Bot2 ( -24, 24 );
AiBot Bot3 ( 24, -24 );

BuildingBlock BB;
BuildingMode BM;

BOOL START = FALSE;
BOOL END = FALSE;
BOOL StartPoint = FALSE;
int StartPointX, StartPointY, EndPointX, EndPointY;

Grid::XYCoordinates Coords;

int PlayerScore = 0;
int PlayerLives = 3;
/////////////////////////////////////////////////////////////////////////
//					([])		  |									   //
//	|							  |									|  //
//	|						   *MA|IN*								|  //
//	|							  |									|  //
//								  |									   //
/////////////////////////////////////////////////////////////////////////

int main ( int argc, char** argv )
{
	glutInit				( &argc, argv );
//	PlaySound				( TEXT ( "E:\\VSProjects\\OpenGL\\Maze\\Maze2D\\Debug\\Game\\game.wav" ), NULL, SND_ASYNC | SND_LOOP | SND_FILENAME );
	glutInitDisplayMode		( GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize		( 600, 400 );
	glutInitWindowPosition	( 100, 100 );
	glutCreateWindow		( argv[0] );
	
	int gameMenu = glutCreateMenu ( menu );
	glutAddMenuEntry ( "Start", ITEM_START );
	glutAddMenuEntry ( "Pause", ITEM_PAUSE );
	glutAddMenuEntry ( "Reset", ITEM_RESET );

	int fileMenu = glutCreateMenu ( menu );
	glutAddMenuEntry ( "Load Map", ITEM_LOAD );
	glutAddMenuEntry ( "Save Map", ITEM_SAVE );

	int engineMenu = glutCreateMenu ( menu );
	glutAddMenuEntry ( "Border", ITEM_WALL );
	glutAddMenuEntry ( "Token", ITEM_TOKEN );
	glutAddMenuEntry ( "Remove", ITEM_REMOVE );

	int modeMenu = glutCreateMenu ( menu );
	glutAddMenuEntry ( "Single Edit", ITEM_SINGLE );
	glutAddMenuEntry ( "Multiple Edit", ITEM_MULTI );

	glutCreateMenu ( menu );
	glutAddSubMenu ( "Game", gameMenu );
	glutAddSubMenu ( "File", fileMenu );
	glutAddSubMenu ( "Engine", engineMenu );
	glutAddSubMenu ( "Mode", modeMenu );
	glutAttachMenu ( GLUT_RIGHT_BUTTON );

	Init					( );
	glutIdleFunc			( IdleFunc );
	glutDisplayFunc			( Display );
	glutReshapeFunc			( Reshape );
	glutMouseFunc			( Mouse );
	glutSpecialFunc			( KeyBoardFunc );
	glutMainLoop			( );
	return 0;
}

void menu ( int item)
{ 
	switch ( item )
	{
		case ITEM_START:	START = TRUE;				break;
		case ITEM_LOAD:		MainGrid.LoadMap ( );		break;
		case ITEM_SAVE:		MainGrid.SaveMap ( );		break;
		case ITEM_WALL:		BB = BB_Wall;				break;
		case ITEM_TOKEN:	BB = BB_Token;				break;
		case ITEM_REMOVE:	BB = BB_Remove;				break;
		case ITEM_SINGLE:	BM = BM_SINGLE;				break;
		case ITEM_MULTI:	BM = BM_MULTI;				break;

	}
}

void Init ( void )
{
	glClearColor ( 0.0, 0.0, 0.0, 0.0 );
	glMatrixMode ( GL_PROJECTION );
	glLoadIdentity ( );
	glOrtho ( -60, 60, -60, 60, -1.0, 1.0 );

	glLightModelf ( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
	glEnable ( GL_LIGHTING );
	glEnable ( GL_LIGHT0 );

	glEnable ( GL_LIGHT1 );
	GLfloat qaAmbientLight[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat qaDiffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv ( GL_LIGHT0, GL_AMBIENT, qaAmbientLight );
	glLightfv ( GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight );
	glLightfv ( GL_LIGHT0, GL_SPECULAR, qaSpecularLight );

	GLfloat qaAmbientLight2[] = { 0.8, 0.2, 0.2, 1.0 };
	GLfloat qaDiffuseLight2[] = { 0.8, 0.0, 0.8, 1.0 };
	GLfloat qaSpecularLight2[] = { 1.0, 0.0, 1.0, 1.0 };
	glLightfv ( GL_LIGHT1, GL_AMBIENT, qaAmbientLight2 );
	glLightfv ( GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight2 );
	glLightfv ( GL_LIGHT1, GL_SPECULAR, qaSpecularLight2 );

	GLfloat qaLightPosition[] = { 10, 20, 1.0, 1.0 };
	GLfloat qaLightPosition2[] = { 30, 20, 1.0, 1.0 };
	glLightfv ( GL_LIGHT0, GL_POSITION, qaLightPosition );
	glLightfv ( GL_LIGHT1, GL_POSITION, qaLightPosition2 );
}

void Display ( void )
{
	
	glClear ( GL_COLOR_BUFFER_BIT );
	glPushMatrix ( );

	HumanPlayer.Move ( MainGrid );
	HumanPlayer.Draw ( );
	if ( MainGrid.EatToken ( HumanPlayer.XPlayerPos ( ), HumanPlayer.YPlayerPos ( ) ) )
	{
		PlayerScore += 1;		
	}

	glPushMatrix ( );
		Score newScore;
		newScore.DrawScore ( PlayerScore);
		newScore.DrawNumber ( PlayerLives, -55, 20);
	glPopMatrix ( );
	
	MainGrid.Draw ( );
	//DrawGrid ( );
	if (START)
		FindPlayer ( );
	Bot.Draw ( );
	Bot2.Draw ( );
	Bot3.Draw ( );
	glEnd ( );
	glPopMatrix ( );
	glutSwapBuffers ( );
}

void Reshape ( int w, int h )
{
	glViewport		( 0, 0, w, h );
	glLoadIdentity	( );
	glOrtho ( -30.0, 30, -30, 30, -1.0, 1.0 );
//	gluPerspective ( 60, double ( w ) / double ( h ), 1, 256 );
}

void KeyBoardFunc ( int key, int h, int w )
{
	if ( key == GLUT_KEY_END )
	{
		START = TRUE;
	}

	if ( START )
	{
		if ( key == GLUT_KEY_UP )
		{
			HumanPlayer.setPlayerDirection ( Player::Up );
		}
		if ( key == GLUT_KEY_DOWN )
		{
			HumanPlayer.setPlayerDirection ( Player::Down );
		}
		if ( key == GLUT_KEY_RIGHT )
		{
			HumanPlayer.setPlayerDirection ( Player::Right );
		}
		if ( key == GLUT_KEY_LEFT )
		{
			HumanPlayer.setPlayerDirection ( Player::Left );
		}
	}
	if ( key == GLUT_KEY_F5 )
	{
		MainGrid.SaveMap ( );
	}

	if ( key == GLUT_KEY_F8 )
	{
		MainGrid.LoadMap ( );
	}
}

void DrawGrid ( )
{ 
	glPushMatrix ( );

	glBegin ( GL_LINES );

	glColor3f ( 1.0, 1.0, 0.0 );
	for ( int i = -25; i < 26; i++ )
	{
		for ( int j = -25; j < 26; j++ )
		{
			glVertex2f ( i, j );
			glVertex2f ( i + 1, j );

			glVertex2f ( i, j );
			glVertex2f ( i, j + 1 );
		}
	}

	glEnd ( );

	glPopMatrix ( );
}

void IdleFunc ( )
{
	Display ( );
	glutPostRedisplay ( );
}

void Mouse ( int button, int state, int x, int y )
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev ( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev ( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv ( GL_VIEWPORT, viewport );

	winX = ( float )x;
	winY = ( float )viewport[3] - ( float )y;
	glReadPixels ( x, int ( winY ), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject ( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ );
	if ( button == GLUT_LEFT_BUTTON && state == GLUT_SINGLE )
	{


		if ( BM == BM_SINGLE )
		{

			Coords.x = posX;
			Coords.y = posY;

			if ( Coords.x < 0 )
				Coords.x -= 1;
			else
				Coords.x += 1;

			if ( Coords.y < 0 )
				Coords.y -= 1;
			else
				Coords.y += 1;

			switch ( BB )
			{
				case BB_Token:	MainGrid.PopulateTokenList ( Coords );		break;
				case BB_Wall:	MainGrid.PopulateInvalidList ( Coords );	break;
			}
		}
		else if ( BM == BM_MULTI )
		{
			StartPoint = !StartPoint;
			if ( StartPoint )
			{
				StartPointX = posX;
				StartPointY = posY;

				if ( StartPointX < 0 )
					StartPointX -= 1;

				if ( StartPointY <= 0 )
					StartPointY -= 1;
			}
			else
			{
				EndPointX = posX;
				EndPointY = posY;

				int xDiff = abs ( EndPointX - StartPointX );
				int yDiff = abs ( EndPointY - StartPointY );

				//PAsing through to many times

				

				if ( EndPointX < 0 )
					EndPointX -= 1;


				if ( EndPointY < 0 )
					EndPointY -= 1;

				if ( xDiff > yDiff )
				{

					for ( int i = fmin ( StartPointX, EndPointX ); i < fmax ( StartPointX, EndPointX ); i++ )
					{
						Coords.x = i;
						Coords.y = StartPointY;
						switch ( BB )
						{
							case BB_Token:	MainGrid.PopulateTokenList ( Coords );		break;
							case BB_Wall:	MainGrid.PopulateInvalidList ( Coords );	break;
						}
					}
				}
				else
				{
					for ( int i = fmin ( StartPointY, EndPointY ); i < fmax ( StartPointY, EndPointY ); i++ )
					{
						Coords.x = StartPointX;
						Coords.y = i;
						switch ( BB )
						{
							case BB_Token:	MainGrid.PopulateTokenList ( Coords );		break;
							case BB_Wall:	MainGrid.PopulateInvalidList ( Coords );	break;
						}
					}
				}
			}
		}
	}

	if ( button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN && BB == BB_Remove )
	{

		MainGrid.EatToken ( posX, posY );
		//MainGrid.DeleteBorder ( posX, posY );
	}
	
}

void FindPlayer ( )
{
	Bot.FindPathToPlayer ( MainGrid, HumanPlayer.XPlayerPos ( ), HumanPlayer.YPlayerPos ( ) );
	Bot2.FindPathToPlayer ( MainGrid, HumanPlayer.XPlayerPos ( ), HumanPlayer.YPlayerPos ( ) );
	Bot3.FindPathToPlayer ( MainGrid, HumanPlayer.XPlayerPos ( ), HumanPlayer.YPlayerPos ( ) );

	if ( Bot.XBotPos ( ) == Bot2.XBotPos ( ) && Bot.YBotPos ( ) == Bot2.YBotPos ( ) )
		Bot.Reset (AiBot::BotMode1);

	if ( Bot.XBotPos ( ) == Bot3.XBotPos ( ) && Bot.YBotPos ( ) == Bot3.YBotPos ( ) )
		Bot.Reset ( AiBot::BotMode3 );


	if ( Bot2.XBotPos ( ) == Bot3.XBotPos ( ) && Bot2.YBotPos ( ) == Bot3.YBotPos ( ) )
		Bot2.Reset ( AiBot::BotMode2 );

	if ( (Bot.XBotPos ( ) == HumanPlayer.XPlayerPos ( ) && Bot.YBotPos ( ) == HumanPlayer.YPlayerPos ( )) ||
		(Bot2.XBotPos ( ) == HumanPlayer.XPlayerPos ( ) && Bot2.YBotPos ( ) == HumanPlayer.YPlayerPos ( )) ||
		(Bot3.XBotPos ( ) == HumanPlayer.XPlayerPos ( ) && Bot3.YBotPos ( ) == HumanPlayer.YPlayerPos ( )) )
	{
		START = FALSE;
		PlayerLives -= 1;
		Bot.Reset ( AiBot::BotMode1 );
		Bot2.Reset ( AiBot::BotMode2 );
		Bot3.Reset ( AiBot::BotMode3 );
	}

	if ( MainGrid.TokenListSize ( ) == 0 || PlayerLives == 0 )
	{
		START = FALSE;
		if ( PlayerLives == 0 );
			glDisable ( GL_LIGHTING );
	}
}

