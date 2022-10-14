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
	cameFrom.push_back(startingNode);
}

void GreedyBFS::GreedyBFSAlgorithm(PathFindingGraph* graph)
{
	while (!frontier.empty())
	{
		current = frontier.top();
		if (current == goal) break;

		for (int next = 0; next < current->neighbours.size(); next++)
		{
			if (!cameFrom.at(next))
			{
				priority = Heuristic(goal, current->neighbours);
				frontier.push(current->neighbours[next]);
				
				// Not sure
				current = cameFrom[current->neighbours[next]];
			}
		}
	}
}

float GreedyBFS::Heuristic(Node* goal, Node* curr)
{
	// [h(n) = sqrt(pow(n.x - goal.x, 2) + pow(n.y - goal.y, 2))] EUCLIDEA!!!
	std::priority_queue<Node*> hFrontier = frontier;
	float h;

	return h = sqrt(pow(curr->GetPos().x - goal->GetPos().x, 2) + pow(curr->GetPos().y - goal->GetPos().y, 2));
}

