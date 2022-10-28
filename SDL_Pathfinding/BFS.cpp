#include "BFS.h"


BFS::BFS()
{
	current = new Node(Vector2D(0.0f, 0.0f), 0.0f);
	goal = new Node(Vector2D(0.0f, 0.0f), 0.0f);
	startingNode = new Node(Vector2D(0.0f, 0.0f), 0.0f);
}

void BFS::FindPath(Agent* agent, float dt)
{

}

void BFS::BFSAlgorithm(PathFindingGraph* graph)
{
	cameFrom.clear();
	pathToGoal.clear();

	std::queue<Node*> tempFrontier;
	tempFrontier.push(startingNode);
	cameFrom[startingNode] = NULL;

	current = startingNode;

	while (!tempFrontier.empty())
	{
		current = tempFrontier.front();
		tempFrontier.pop();
		if (current->GetPos() == goal->GetPos()) 
			break;

		for (int i = 0; i < current->neighbours.size(); i++)
		{
			if (cameFrom.find(current->neighbours[i]) == cameFrom.end())
			{
				tempFrontier.push(current->neighbours[i]);

				cameFrom[current->neighbours[i]] = current;
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

void BFS::PutStartingNodeToFrontier(Node* startingNode)
{
	frontier.push(startingNode);
	cameFrom[startingNode] = NULL;
}

void BFS::SetGoalPosition(Vector2D coinPos)
{
	goal->SetPos(coinPos);
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
