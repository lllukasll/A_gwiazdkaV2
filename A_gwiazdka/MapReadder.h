#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class MapReadder
{
public:
	int grid[20][20];
	MapReadder();
	~MapReadder();
	void ReadTxtFile(string path);
};

