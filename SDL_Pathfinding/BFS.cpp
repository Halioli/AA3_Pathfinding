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
				std::cout << "a" << std::endl;
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

	while (current && (current->GetPos() != startingNode->GetPos())) // Es queda en aquest While infinitament (don't fucking know why, bitch)
	{																	// Va "back and forth" entre dos nodes, tota l'estona.
		current = cameFrom[current];
		pathToGoal.push_back(current);
	}

	pathToGoal.push_back(startingNode);
	std::reverse(pathToGoal.begin(), pathToGoal.end());

	// Netejar frontera
	for (int i = 0; i < frontier.size(); i++)
	{
		frontier.pop();
	}
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
