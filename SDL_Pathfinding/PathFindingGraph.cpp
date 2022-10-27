#pragma once
#include "PathFindingGraph.h"

PathFindingGraph::PathFindingGraph(int cellWidth, int cellHeight)
{
	allNodes.resize(cellHeight);
	// Initialize NODES
	for (int i = 0; i < cellHeight; i++)
	{
		allNodes[i] = std::vector<Node*>(cellWidth);
		for (int j = 0; j < cellWidth; j++)
		{
			allNodes[i][j] = new Node(Vector2D(j, i), 0.f);
		}
	}

	// Initialize NEIGHBOURS
	for (int i = 0; i < cellHeight; i++)
	{
		for (int j = 0; j < cellWidth; j++)
		{
			if (!(i + 1 >= cellHeight))
				(allNodes[i][j])->neighbours.push_back(allNodes[i + 1][j]);

			if (!(i - 1 <= 0))
				(allNodes[i][j])->neighbours.push_back(allNodes[i - 1][j]);

			if (!(j + 1 >= cellWidth))
				(allNodes[i][j])->neighbours.push_back(allNodes[i][j + 1]);

			if (!(j - 1 <= 0))
				(allNodes[i][j])->neighbours.push_back(allNodes[i][j - 1]);
		}
	}
}

Node* PathFindingGraph::GetNodeByPosition(Vector2D cellPos)
{
	for (int i = 0; i < allNodes.size(); i++)
	{
		for(int j = 0; j < allNodes[i].size(); j++)
		if (allNodes[i][j]->GetPos() == cellPos)
			return allNodes[i][j];
	}
	return NULL;
}