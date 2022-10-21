#pragma once
#include "PathFindingAlgorithm.h"
#include <queue>
#include <map>

class BFS : public PathFindingAlgorithm
{
	BFS();
	~BFS();

	public:
		std::priority_queue<Node*> frontier;
		std::map<Node*, Node*> cameFrom;

		Node* current;
		Node* goal;
		Node* startingNode;

		void FindPath(Agent* agent, float dt) override;
		void BFSAlgorithm(PathFindingGraph* graph);
		void PutStartingNodeToFrontier(Node* startingNode);
		void RestorePath();

};

