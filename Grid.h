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

	Grid();
	~Grid();

	void Draw();

	vector<XYCoordinates> GetValidList();

	void PopulateInvalidList(XYCoordinates coords);
	bool IsNotInvalidPosition(int x, int y);
	void DeleteBorder(int x, int y);
	void SaveInvalidList();
	void LoadInvalidList();

	void PopulateTokenList(XYCoordinates coords);
	bool EatToken(int x, int y);
	int TokenListSize();
	void SaveTokenList();
	void LoadTokenList();

	void PopulateBombList(XYCoordinates coords);
	bool ExplodeBomb(int x, int y);
	void SaveBombList();
	void LoadBombList();

	void ClearList(vector<XYCoordinates> &list);
	void SetLoadLists(vector<XYCoordinates> &list, const vector<int> &xList, const vector<int> &yList);
	void GetSaveLists(const vector<XYCoordinates> &list, vector<int> &xList, vector<int> &yList);
	void SaveMap();
	void LoadMap();





private:
	vector<XYCoordinates> InvalidList;
	vector<XYCoordinates> TokenList;
	vector<XYCoordinates> BombList;
	vector<XYCoordinates> WallList;
	vector<XYCoordinates> GunList;
};

