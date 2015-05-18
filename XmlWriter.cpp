#include "stdafx.h"
#include "XmlWriter.h"
#include <sstream>

XmlWriter::XmlWriter ( )
{ 

}


XmlWriter::~XmlWriter ( )
{ }

void XmlWriter::WriteCoordList ( vector<int> xCoordList, vector<int> yCoordList, string fileName )
{
	if ( xCoordList.size ( ) != yCoordList.size ( ) )
		return;
	XMLDocument Doc;

	XMLNode* Declaration = Doc.NewDeclaration ( );
	Doc.InsertEndChild ( Declaration );
	XMLNode* root = Doc.NewElement ( "Coordinates" );
	Doc.InsertEndChild ( root );
	

	for ( int i = 0; i < xCoordList.size ( ); i++ )
	{
		stringstream x, y;
		x.str ( "" );
		y.str ( "" );

		x << xCoordList[i];
		y << yCoordList[i];

		XMLNode* coordPair = Doc.NewElement ( "Pair");
		XMLNode* xCoordNode = Doc.NewElement ( "X" );
		XMLNode* yCoordNode = Doc.NewElement ( "Y" );

		XMLText *xCoordText = Doc.NewText ( x.str ( ).c_str ( ) );
		XMLText *yCoordText = Doc.NewText ( y.str ( ).c_str ( ) );

		root->InsertEndChild ( coordPair );
		coordPair->InsertEndChild ( xCoordNode );
		coordPair->InsertEndChild ( yCoordNode );

		xCoordNode->InsertEndChild ( xCoordText );
		yCoordNode->InsertEndChild ( yCoordText );		
	}


	Doc.SaveFile ( fileName.c_str() );
}