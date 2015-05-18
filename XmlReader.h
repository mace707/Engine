#pragma once
#include "tinyxml2.h"
#include <vector>

using namespace tinyxml2; 
using namespace std;

class XmlReader
{
	public:

	XmlReader ( );
	~XmlReader ( );

	static void ReadCoordList ( vector<int> &xCoordList, vector<int> &yCoordList, string fileName );
};

