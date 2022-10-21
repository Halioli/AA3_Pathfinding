#include "BFS.h"


BFS::BFS()
{

}

void BFS::FindPath(Agent* agent, float dt)
{

}

void BFS::BFSAlgorithm(PathFindingGraph* graph)
{
	while (!frontier.empty())
	{
		current = frontier.top();
		if (current == goal) break;
		for (int i = 0; i < current->neighbours.size(); i++)
		{
			if (!cameFrom[current->neighbours[i]])
			{
				frontier.push(current->neighbours[i]);
				cameFrom[current->neighbours[i]] = current;
			}
		}
	}
}

void BFS::PutStartingNodeToFrontier(Node* startingNode)
{
	frontier.push(startingNode);
	cameFrom[startingNode] = NULL;
}

void BFS::RestorePath()
{
	current = goal;
	//path = [current] pseudocodi

	while (current != startingNode)
	{
		current = cameFrom[current];
		//path.append(current) pseudocodi
	}

}
