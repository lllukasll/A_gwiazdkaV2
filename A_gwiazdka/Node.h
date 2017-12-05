#pragma once
class Node
{
public:
	int nodeX,nodeY;
	int parentX, parentY;
	int value;

	double heuristicCost;
	double movementCost, fullCost;


	Node();
	~Node();

	void countHeuristicValue(int finishX, int finishY);
};

