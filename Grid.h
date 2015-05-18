#pragma once
#include <Windows.h>
#include <vector>
#include "Squar.h"

using namespace std;

class Grid
{
	public:
		struct XYCoordinates
		{
			int x, y;
		};

		Grid ( );
		~Grid ( );

		void Draw ( );
		
		vector<XYCoordinates> GetValidList ( );

		void PopulateInvalidList	( XYCoordinates coords );
		bool IsNotInvalidPosition	( int x, int y );
	
		void PopulateTokenList		( XYCoordinates coords );
		bool EatToken ( int x, int y );
		void DeleteBorder ( int x, int y );

		int TokenListSize ( ); 

		void ClearList ( vector<XYCoordinates> &list );
		void SaveInvalidList ( );
		void SaveTokenList ( );
		void GetSaveLists ( const vector<XYCoordinates> &list, vector<int> &xList, vector<int> &yList );
		void SaveMap ( );
		
		void LoadMap ( );
		void LoadInvalidList ( );
		void LoadTokenList ( );
		void SetLoadLists ( vector<XYCoordinates> &list, const vector<int> &xList, const vector<int> &yList );
	private:
		vector<XYCoordinates> InvalidList;
		vector<XYCoordinates> TokenList;


		
};

