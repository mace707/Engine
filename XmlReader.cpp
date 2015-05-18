#include "stdafx.h"
#include "XmlReader.h"


XmlReader::XmlReader ( )
{

}


XmlReader::~XmlReader ( )
{ }

void XmlReader::ReadCoordList ( vector<int> &xCoordList, vector<int> &yCoordList, string fileName )
{ 
	if ( xCoordList.size ( ) != yCoordList.size ( ) )
		return;
	XMLDocument Doc;

	Doc.LoadFile ( fileName.c_str() );
	XMLNode* declaration = Doc.FirstChild ( );
	XMLNode* root = declaration->NextSibling ( );

	XMLNode* parentNode = root->FirstChild ( );
	XMLNode* pairNode = nullptr;
	
	for ( pairNode = root->FirstChild ( ); pairNode; pairNode = pairNode->NextSibling ( ) )
	{
		XMLNode* xCoordNode = pairNode->FirstChild ( );
		XMLElement* xCoordElement = xCoordNode->ToElement ( );
		int xCoord = atoi ( xCoordElement->GetText ( ) );

		XMLNode* yCoordNode = pairNode->LastChild ( );
		XMLElement* yCoordElement = yCoordNode->ToElement ( );
		int yCoord = atoi ( yCoordElement->GetText ( ) );

		xCoordList.push_back ( xCoord );
		yCoordList.push_back ( yCoord );
	}
}

