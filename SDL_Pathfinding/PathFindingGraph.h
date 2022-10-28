#pragma once
#include <vector>
#include "Node.h"
#include "Vector2D.h"
#include "Grid.h"

class PathFindingGraph
{
public:
	PathFindingGraph(int cellWidth, int cellHeight, Grid* _maze);
	~PathFindingGraph();

	std::vector<std::vector<Node*>> allNodes;

	Node* GetNodeByPosition(Vector2D cellPos);
};

