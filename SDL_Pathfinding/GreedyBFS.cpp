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
	cameFrom.clear();
	pathToGoal.clear();

	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> tempFrontier;
	tempFrontier.push(startingNode);
	cameFrom[startingNode] = NULL;

	current = startingNode;

	while (!tempFrontier.empty())
	{
		current = tempFrontier.top();
		tempFrontier.pop();
		if (current->GetPos() == goal->GetPos())
			break;

		for (int index = 0; index < current->neighbours.size(); index++)
		{
			if (cameFrom.find(current->neighbours[index]) == cameFrom.end())
			{
				priority = Heuristic(goal, current->neighbours[index]);

				current->neighbours[index]->SetWeight(priority);

				tempFrontier.push(current->neighbours[index]); // S'hauria d'estar ordenant de forma automàtica (gràcies a l'operador(Tomeu))

				cameFrom[current->neighbours[index]] = current;
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

	pathToGoal.push_back(current);

	while (current && (current->GetPos() != startingNode->GetPos()))
	{
		current = cameFrom[current];
		pathToGoal.push_back(current);
	}

	pathToGoal.push_back(startingNode);
	std::reverse(pathToGoal.begin(), pathToGoal.end());
}

void GreedyBFS::GreedyBFSAlgorithmWithEnemies(PathFindingGraph* graph, std::vector<Agent*> _enemyAgents, Grid* _maze)
{
	cameFrom.clear();
	pathToGoal.clear();

	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> tempFrontier;
	tempFrontier.push(startingNode);
	cameFrom[startingNode] = NULL;

	current = startingNode;

	while (!tempFrontier.empty())
	{
		current = tempFrontier.top();
		tempFrontier.pop();
		if (current->GetPos() == goal->GetPos())
			break;

		for (int index = 0; index < current->neighbours.size(); index++)
		{
			if (cameFrom.find(current->neighbours[index]) == cameFrom.end())
			{
				priority = Heuristic(goal, current->neighbours[index]);
					
				for (int i = 0; i < _enemyAgents.size(); i++)
				{
					float result = Heuristic(current->neighbours[index], graph->GetNodeByPosition(_maze->pix2cell(_enemyAgents[i]->getPosition())));// *0.8f);

					priority -= result;
					if (priority < 0) { priority = 0; }
				}

				current->neighbours[index]->SetWeight(priority);

				tempFrontier.push(current->neighbours[index]); // S'hauria d'estar ordenant de forma automàtica (gràcies a l'operador(Tomeu))

				cameFrom[current->neighbours[index]] = current;
			}
		}
	}

	pathToGoal.push_back(current);

	while (current && (current->GetPos() != startingNode->GetPos()))
	{
		current = cameFrom[current];
		pathToGoal.push_back(current);
	}

	pathToGoal.push_back(startingNode);
	std::reverse(pathToGoal.begin(), pathToGoal.end());
}

float GreedyBFS::Heuristic(Node* goal, Node* curr)
{
	// [h(n) = sqrt(pow(n.x - goal.x, 2) + pow(n.y - goal.y, 2))] EUCLIDEA!!!
	float h;

	return h = sqrt(pow(curr->GetPos().x - goal->GetPos().x, 2) + pow(curr->GetPos().y - goal->GetPos().y, 2));
}

