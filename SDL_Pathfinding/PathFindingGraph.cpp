#pragma once
#include "PathFindingGraph.h"

PathFindingGraph::PathFindingGraph(int cellWidth, int cellHeight)
{
	for (int i = 0; i < cellWidth; i++)
	{
		for (int j = 0; j < cellHeight; j++)
		{
			allNodes.push_back(new Node(Vector2D(i, j)));
		}
	}
}

Node* PathFindingGraph::GetNodeByPosition(Vector2D cellPos)
{
	for (int i = 0; i < allNodes.size(); i++)
	{
		if (allNodes[i]->GetPos() == cellPos)
			return allNodes[i];
	}
	return NULL;
}