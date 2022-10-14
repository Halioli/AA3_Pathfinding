#pragma once

#include "PathFindingAlgorithm.h"
#include "Node.h"
#include <queue>
#include <stack>

class GreedyBFS : PathFindingAlgorithm
{	
public:
	//FIFO
	std::priority_queue<Node*> frontier;
	std::vector<Node*> cameFrom;

	int priority;

	Node* current;
	Node* goal;
	Node* startingNode;

	GreedyBFS();
	~GreedyBFS();

	void FindPath(Agent* monke, float dt) override;
	float Heuristic(Node* goal, Node* curr);
	void PutStartingNodeToFrontier(Node* startingNode);
	void GreedyBFSAlgorithm(PathFindingGraph* graph);
};