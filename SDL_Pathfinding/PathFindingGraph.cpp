#pragma once
#include "PathFindingGraph.h"

PathFindingGraph::PathFindingGraph(int cellWidth, int cellHeight, Grid* _maze)
{
	allNodes.resize(cellHeight);
	// Initialize NODES
	for (int i = 0; i < cellHeight; i++)
	{
		allNodes[i] = std::vector<Node*>(cellWidth);
		for (int j = 0; j < cellWidth; j++)
		{
			allNodes[i][j] = new Node(Vector2D(j, i), 1.f);
		}
	}

	// Initialize NEIGHBOURS
	for (int i = 0; i < cellHeight; i++)
	{
		for (int j = 0; j < cellWidth; j++)
		{
			//_maze->isValidCell() // Checks if the Vector2D isn't a wall

			if (!(i + 1 >= cellHeight) && _maze->isValidCell(allNodes[i + 1][j]->GetPos()))
				(allNodes[i][j])->neighbours.push_back(allNodes[i + 1][j]);

			if (!(i - 1 <= 0) && _maze->isValidCell(allNodes[i - 1][j]->GetPos()))
				(allNodes[i][j])->neighbours.push_back(allNodes[i - 1][j]);

			if (!(j + 1 >= cellWidth) && _maze->isValidCell(allNodes[i][j + 1]->GetPos()))
				(allNodes[i][j])->neighbours.push_back(allNodes[i][j + 1]);

			if (!(j - 1 <= 0) && _maze->isValidCell(allNodes[i][j - 1]->GetPos()))
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