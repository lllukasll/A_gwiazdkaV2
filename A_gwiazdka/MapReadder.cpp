#include "stdafx.h"
#include "MapReadder.h"

MapReadder::MapReadder()
{
}


MapReadder::~MapReadder()
{
}

void MapReadder::ReadTxtFile(string path)
{
	ifstream file(path);

	if (file.is_open())
	{
		string myArray[20][20];

		for (int i = 19; i >= 0; i--)
		{
			for (int j = 0; j < 20; j++)
			{
				file >> myArray[i][j];
			}
		}

		for (int i = 19; i >= 0; i--)
		{
			for (int j = 0; j < 20; j++)
			{
				grid[i][j] = stoi(myArray[i][j]);
			}
		}
	}
}
