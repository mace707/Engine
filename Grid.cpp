#include "stdafx.h"
#include "Grid.h"
#include <OpenGl\glut.h>
#include "Squar.h"
#include "XmlWriter.h"
#include "XmlReader.h"
Grid::Grid ( )
{ }


Grid::~Grid ( )
{ }


void Grid::Draw ( )
{
	XYCoordinates coords;
	int listPos = 0;
	glPushMatrix ( );
	glBegin ( GL_QUADS );

	Squar square;
	Squar::Color col;

	listPos += 1;
	for ( int i = 0; i < InvalidList.size ( ); i++ )
	{
		col.R = 1;
		col.G = 1;
		col.B = 1;
		GLfloat qaBlack[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat qaGreen[] = { 0.0, 1.0, 0.0, 1.0 };
		GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 };

		glMaterialfv ( GL_FRONT, GL_AMBIENT, qaWhite );
		glMaterialfv ( GL_FRONT, GL_DIFFUSE, qaGreen );
		glMaterialfv ( GL_FRONT, GL_SPECULAR, qaWhite );
		glMaterialf ( GL_FRONT, GL_SHININESS, 60.0 );
		glNormal3f ( 0.0, 0.0, 1.0 );
		square.Draw ( InvalidList[i].x, InvalidList[i].y, InvalidList[i].x + 1, InvalidList[i].y + 1, col );
	}

	for ( int i = 0; i < TokenList.size(); i++ )
	{
		col.R = 1;
		col.G = 1;
		col.B = 0;
		GLfloat qaBlack[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat qaGold[] = { 1.0, 1.0, 0.0, 1.0 };
		glMaterialfv ( GL_FRONT, GL_AMBIENT, qaGold );
		glMaterialfv ( GL_FRONT, GL_DIFFUSE, qaGold );
		glMaterialfv ( GL_FRONT, GL_SPECULAR, qaWhite );
		glMaterialf ( GL_FRONT, GL_SHININESS, 200.0 );
		glNormal3f ( 0.0, 0.0, 1.0 );
		square.Draw ( TokenList[i].x, TokenList[i].y, TokenList[i].x + 1, TokenList[i].y + 1, col, true );
	}

	glEnd ( );
	glPopMatrix ( );
}

void Grid::ClearList ( vector<XYCoordinates> &list )
{ 
	list.clear ( );
	list.resize ( 0 );
	vector<XYCoordinates> nullList;
	list.swap ( nullList );
}

void Grid::PopulateInvalidList ( XYCoordinates coords )
{
	InvalidList.push_back ( coords );
}

void Grid::PopulateTokenList ( XYCoordinates coords )
{
	TokenList.push_back ( coords );
}

int Grid::TokenListSize ( )
{ 
	return TokenList.size ( );
}

void Grid::DeleteBorder ( int x, int y )
{
	vector<XYCoordinates> updatedInvalidList;
	XYCoordinates updatedCoords;

	for ( int i = 0; i < InvalidList.size ( ); i++ )
	{
		if ( InvalidList[i].x == x && InvalidList[i].y == y )
			continue;

		updatedCoords.x = InvalidList[i].x;
		updatedCoords.y = InvalidList[i].y;

		updatedInvalidList.push_back ( updatedCoords );
		
	}
	ClearList ( InvalidList );
	InvalidList = updatedInvalidList;
}

bool Grid::EatToken ( int x, int y )
{
	vector<XYCoordinates> updatedTokenList;
	XYCoordinates updatedCoords;
	bool tokenEaten = false;
	for ( int i = 0; i < TokenList.size ( ); i++ )
	{
		updatedCoords.x = TokenList[i].x;
		updatedCoords.y = TokenList[i].y;
		if ( TokenList[i].x == x && TokenList[i].y == y )
		{
			tokenEaten = true;
			continue;
		}
		else
		{
			updatedTokenList.push_back ( updatedCoords );
		}
	}

	ClearList ( TokenList );
	for ( int i = 0; i < updatedTokenList.size ( ); i++ )
	{
		PopulateTokenList ( updatedTokenList[i] );
	}
	return tokenEaten;
}

bool Grid::IsNotInvalidPosition ( int x, int y )
{ 
	for ( int i = 0; i < InvalidList.size ( ); i++ )
	{
		if ( InvalidList[i].x == x && InvalidList[i].y == y )
		{
			return false;
		}
	}
	return true;
}

void Grid::GetSaveLists ( const vector<XYCoordinates> &list, vector<int> &xList, vector<int> &yList )
{ 
	for ( int i = 0; i < list.size ( ); i++ )
	{
		xList.push_back ( list[i].x );
		yList.push_back ( list[i].y );
	}
}

void Grid::SaveInvalidList ( )
{ 
	vector<int> xList, yList;
	GetSaveLists ( InvalidList, xList, yList );
	XmlWriter::WriteCoordList ( xList, yList, "InvalidCoords.xml" );
}

void Grid::SaveTokenList ( )
{
	vector<int> xList, yList;
	GetSaveLists ( TokenList, xList, yList );
	XmlWriter::WriteCoordList ( xList, yList, "TokenCoords.xml" );
}

void Grid::SaveMap ( )
{ 
	SaveTokenList ( );
	SaveInvalidList ( );
}


void Grid::LoadInvalidList ( )
{
	vector<int> xList, yList;
	XmlReader::ReadCoordList ( xList, yList, "InvalidCoords.xml" );
	SetLoadLists ( InvalidList, xList, yList );
}

void Grid::LoadTokenList ( )
{
	vector<int> xList, yList;
	XmlReader::ReadCoordList ( xList, yList, "TokenCoords.xml" );
	SetLoadLists ( TokenList, xList, yList );
}

void Grid::SetLoadLists ( vector<XYCoordinates> &list, const vector<int> &xList, const vector<int> &yList )
{
	for ( int i = 0; i < xList.size ( ); i++ )
	{
		XYCoordinates coords;
		coords.x = xList[i];
		coords.y = yList[i];
		list.push_back ( coords );
	}
}

void Grid::LoadMap ( )
{
	LoadTokenList ( );
	LoadInvalidList ( );
}