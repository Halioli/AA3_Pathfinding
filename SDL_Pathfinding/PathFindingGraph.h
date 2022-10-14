#pragma once
#include <vector>
#include "Node.h"
#include "Vector2D.h"

class PathFindingGraph
{
public:
	PathFindingGraph(int cellWidth, int cellHeight);
	~PathFindingGraph();

	std::vector<Node*> allNodes;

	Node* GetNodeByPosition(Vector2D cellPos);
};

