#pragma once
#include "GreedyBFS.h"

GreedyBFS::GreedyBFS() 
{
	current = new Node(Vector2D(0.0f, 0.0f), 0.0f);
	goal = new Node(Vector2D(0.0f, 0.0f), 0.0f);
	startingNode = new Node(Vector2D(0.0f, 0.0f), 0.0f);
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

void GreedyBFS::SetGoalPosition(Vector2D coinPos)
{
	goal->SetPos(coinPos);
}

void GreedyBFS::GreedyBFSAlgorithm(PathFindingGraph* graph)
{
	//int _lowestPriority = 9999;

	current = startingNode;

	while (!frontier.empty())
	{
		current = frontier.top();
		frontier.pop();
		if (current->GetPos() == goal->GetPos())
		{
			//startingNode = current;
			break;
		}

		std::cout << "Current x: " << current->GetPos().x << std::endl;
		std::cout << "Current y: " << current->GetPos().y << std::endl;
		std::cout << "Goal x: " << goal->GetPos().x << std::endl;
		std::cout << "Goal y: " << goal->GetPos().y << std::endl;

		for (int index = 0; index < current->neighbours.size(); index++)
		{
			std::cout << "Neighbour" << index << " x: " << current->neighbours[index]->GetPos().x << std::endl;
			std::cout << "Neighbour" << index << " y: " << current->neighbours[index]->GetPos().y << std::endl;

			if (cameFrom.find(current->neighbours[index]) == cameFrom.end())
			{
				priority = Heuristic(goal, current->neighbours[index]);

				/*if (priority < _lowestPriority)
					_lowestPriority = priority;*/

				current->neighbours[index]->SetWeight(priority);

				frontier.push(current->neighbours[index]); // S'hauria d'estar ordenant de forma automàtica (gràcies a l'operador(Tomeu))

				cameFrom[current->neighbours[index]] = current;
			}
			else
			{
				// Do something
				std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
			}
		}
	}

	/*current = goal
	path = [current]
	while current != start:
		current = came_from[current]
		path.append(current)
	path.append(start) # optional
	path.reverse() # optional*/

	current = goal;
	pathToGoal.push_back(current);
	std::cout << "current.x: " << current->GetPos().x << " starting.x: " << startingNode->GetPos().x << std::endl;
	std::cout << "current.y: " << current->GetPos().y << " starting.y: " << startingNode->GetPos().y << std::endl;
	while (current->GetPos() != startingNode->GetPos()) // PETA pk el punter apunta a un lloc que no esta en mem (null ptr exception)
	{
		current = cameFrom[current];
		pathToGoal.push_back(current);
		std::cout << "EEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << std::endl;
	}
	pathToGoal.push_back(startingNode);
	std::reverse(pathToGoal.begin(), pathToGoal.end());
}

float GreedyBFS::Heuristic(Node* goal, Node* curr)
{
	// [h(n) = sqrt(pow(n.x - goal.x, 2) + pow(n.y - goal.y, 2))] EUCLIDEA!!!
	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> hFrontier = frontier;
	float h;

	return h = sqrt(pow(curr->GetPos().x - goal->GetPos().x, 2) + pow(curr->GetPos().y - goal->GetPos().y, 2));
}

