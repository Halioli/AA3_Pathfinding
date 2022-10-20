#pragma once
#include "GreedyBFS.h"

GreedyBFS::GreedyBFS() 
{
	
}

void GreedyBFS::FindPath(Agent* monke, float dt)
{
	//Vector2D cell = maze->pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
}

void GreedyBFS::PutStartingNodeToFrontier(Node* startingNode)
{
	frontier.push(startingNode);
	cameFrom[startingNode] = NULL;
}

void GreedyBFS::GreedyBFSAlgorithm(PathFindingGraph* graph)
{
	int _lowestPriority = 9999;
	int _nextNodeIndex = -1;

	while (!frontier.empty())
	{
		current = frontier.top();
		if (current == goal) break;

		for (int index = 0; index < current->neighbours.size(); index++)
		{
			if (!cameFrom[current->neighbours[index]])
			{
				for (auto element : current->neighbours)
				{
					// No estem comprovant si ja hi ha elements a la frontera.

					priority = Heuristic(goal, element);

					if (priority < _lowestPriority)
					{
						_lowestPriority = priority;
						_nextNodeIndex = index;
					}

					frontier.push(current->neighbours[index]);
				}
				
				cameFrom[current->neighbours[index]] = current;
			}
		}

		current = cameFrom[current->neighbours[_nextNodeIndex]];
	}
}

float GreedyBFS::Heuristic(Node* goal, Node* curr)
{
	// [h(n) = sqrt(pow(n.x - goal.x, 2) + pow(n.y - goal.y, 2))] EUCLIDEA!!!
	std::priority_queue<Node*> hFrontier = frontier;
	float h;

	return h = sqrt(pow(curr->GetPos().x - goal->GetPos().x, 2) + pow(curr->GetPos().y - goal->GetPos().y, 2));
}

