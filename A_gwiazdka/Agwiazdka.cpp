// Agwiazdka.cpp: Definiuje punkt wejścia dla aplikacji konsolowej.
#include "stdafx.h"
#include "MapReadder.h"
#include "Node.h"
#include <list>
#include <vector>
#include <windows.h>

using namespace std;

vector<Node> openList;
vector<Node> closedList;

int startPointX = 0;
int startPointY = 0;

int finishPointX = 19;
int finishPointY = 19;

Node nodesArray[20][20];

void CheckNewPoint(int oldPointX, int oldPointY, int newPointX, int newPointY);
bool CheckClosedList(int x, int y);
bool CheckOpenList(int x, int y);

int main()
{
	bool error = false;

	MapReadder mapReadder;
	mapReadder.ReadTxtFile("C:\\Users\\Lukasz\\Desktop\\ERIA_C1\\grid.txt");

	//Nadaj węzłom odpowiednie wartości
	for (int i = 19; i >= 0; i--)
	{
		for (int j = 0; j < 20; j++)
		{
			nodesArray[i][j].nodeX = i;
			nodesArray[i][j].nodeY = j;
			nodesArray[i][j].countHeuristicValue(19, 19);
			nodesArray[i][j].value = mapReadder.grid[i][j];
		}
	}

	int activePointX = startPointX;
	int activePointY = startPointY;

	while (finishPointX != activePointX || finishPointY != activePointY)
	{
		closedList.push_back(nodesArray[activePointX][activePointY]);

		//Góra
		if (activePointX + 1 <= finishPointX)
		{
			CheckNewPoint(activePointX, activePointY, activePointX + 1, activePointY);
		}

		//Dół
		if (activePointX - 1 >= 0)
		{
			CheckNewPoint(activePointX, activePointY, activePointX - 1, activePointY);
		}

		//Lewo
		if (activePointY - 1 >= 0)
		{
			CheckNewPoint(activePointX, activePointY, activePointX, activePointY - 1);
		}

		//Prawo
		if (activePointY + 1 <= finishPointY)
		{
			CheckNewPoint(activePointX, activePointY, activePointX, activePointY + 1);
		}

		//Znajdz najmniejsza wartosc fullValue
		if (openList.size()==0)
		{
			cout << "Brak przejscia" <<endl;
			error = true;
			break;
		}
			
		double tmp = openList[0].fullCost;
		for each (Node node in openList)
		{
			if (node.fullCost < tmp)
				tmp = node.fullCost;
		}

		//Przypisz aktywnemu punktowi współrzędne punktu z najmniejszym fullValue
		for each (Node node in openList)
		{
			if (node.fullCost == tmp)
			{
				activePointX = node.nodeX;
				activePointY = node.nodeY;
			}
		}

		//Usuń z openList punkt z najmniejszym fullValue
		int elementToDelete;
		for (int i = 0; i < openList.size(); i++)
		{
			if (openList[i].fullCost == tmp)
			{
				elementToDelete = i;
			}
		}
		openList.erase(openList.begin() + elementToDelete);

	}

	if (!error)
	{
		//Oznacz najkrótszą trasę liczbą 3
		while (activePointX != 0 || activePointY != 0)
		{

			nodesArray[activePointX][activePointY].value = 3;
			int tmpX = nodesArray[activePointX][activePointY].parentX;
			int tmpY = nodesArray[activePointX][activePointY].parentY;
			activePointX = tmpX;
			activePointY = tmpY;
		}
		nodesArray[finishPointX][finishPointY].value = 0;

		//Wypisz Grid z kolorowaną składnią
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		cout << "Grid : " << endl;
		for (int i = 19; i >= 0; i--)
		{
			for (int j = 0; j < 20; j++)
			{
				if (i == 0 && j == 0 || i == 19 && j == 19)
				{
					SetConsoleTextAttribute(hConsole, 0xD);
				}
				else if (nodesArray[i][j].value == 3)
				{
					SetConsoleTextAttribute(hConsole, 0xA);

				}
				else if (nodesArray[i][j].value == 5)
				{
					SetConsoleTextAttribute(hConsole, 0xC);
				}
				else
				{
					SetConsoleTextAttribute(hConsole, 0x7);

				}
				cout << nodesArray[i][j].value << " ";
			}
			cout << endl;
		}
	}
	
	system("PAUSE");
    return 0;
}

void CheckNewPoint(int oldPointX, int oldPointY, int newPointX, int newPointY)
{
	if (!(nodesArray[newPointX][newPointY].value == 5))
	{
		if (!CheckClosedList(newPointX, newPointY))
		{
			if (!CheckOpenList(newPointX, newPointY))
			{
				//Dodaj rodzica
				nodesArray[newPointX][newPointY].parentX = oldPointX;
				nodesArray[newPointX][newPointY].parentY = oldPointY;

				//Dodaj movementCost
				nodesArray[newPointX][newPointY].movementCost = nodesArray[nodesArray[newPointX][newPointY].parentX][nodesArray[newPointX][newPointY].parentY].movementCost + 1;

				//Dodaj pełen koszt
				nodesArray[newPointX][newPointY].fullCost = nodesArray[newPointX][newPointY].heuristicCost + nodesArray[newPointX][newPointY].movementCost;

				//Dodaj do open list
				openList.push_back(nodesArray[newPointX][newPointY]);
			}
			else
			{
				if (nodesArray[newPointX][newPointY].fullCost > (nodesArray[oldPointX][oldPointY].movementCost + nodesArray[newPointX][newPointY].heuristicCost + 1))
				{
					nodesArray[newPointX][newPointY].parentX = newPointX;
					nodesArray[newPointX][newPointY].parentY = newPointY;
				}
			}
		}
	}
}

bool CheckClosedList(int x, int y)
{
	for each (Node node in closedList)
	{
		if (node.nodeX == x && node.nodeY == y)
		{
			return true;
		}
	}
	return false;
}

bool CheckOpenList(int x, int y)
{
	for each (Node node in openList)
	{
		if (node.nodeX == x && node.nodeY == y)
		{
			return true;
		}
	}
	return false;
}
