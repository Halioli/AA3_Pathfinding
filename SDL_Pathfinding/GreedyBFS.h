#pragma once

#include "PathFindingAlgorithm.h"
#include "Node.h"
#include <queue>
#include <stack>
#include <map>
#include <algorithm>

class GreedyBFS : PathFindingAlgorithm
{	
public:
	struct CompareNodes
	{
		bool operator()(Node* a, Node* b)
		{
			return ((a->GetWeight()) > (b->GetWeight()));
		}
	};

	//FIFO
	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> frontier;
	std::map<Node*, Node*> cameFrom;
	std::vector<Node*> pathToGoal;

	int priority;

	Node* current;
	Node* goal;
	Node* startingNode;

	GreedyBFS();
	~GreedyBFS();

	void FindPath(Agent* monke, float dt) override;
	float Heuristic(Node* goal, Node* curr);
	void Heuristic() override {};
	void PutStartingNodeToFrontier(Node* startingNode);
	void SetGoalPosition(Vector2D coinPos);
	void GreedyBFSAlgorithm(PathFindingGraph* graph);
};