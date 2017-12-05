#include "stdafx.h"
#include "Node.h"
#include "math.h"


Node::Node()
{
	movementCost = 0;
	fullCost = 0;
}


Node::~Node()
{
}

void Node::countHeuristicValue(int finishX, int finishY)
{
	heuristicCost = sqrt(pow(finishX - nodeX, 2) + pow(finishY - nodeY, 2));
}
