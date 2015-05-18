#pragma once

#pragma once
#include "tinyxml2.h"
#include <vector>
#include <string>
using namespace tinyxml2;
using namespace std;

class XmlWriter
{
	public:
	XmlWriter ( );
	~XmlWriter ( );
	
	static void WriteCoordList ( vector<int> xCoordList, vector<int> yCoordList, string fileName );
};

