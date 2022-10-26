#pragma once
#include "PathFindingAlgorithm.h"
#include <queue>
#include <map>

class BFS : public PathFindingAlgorithm
{
	public:
		BFS();
		~BFS();

		std::priority_queue<Node*> frontier;
		std::map<Node*, Node*> cameFrom;
		std::vector<Node*> pathToGoal;

		Node* current;
		Node* goal;
		Node* startingNode;

		void FindPath(Agent* agent, float dt) override;
		void BFSAlgorithm(PathFindingGraph* graph);
		void PutStartingNodeToFrontier(Node* startingNode);
		void SetGoalPosition(Vector2D coinPos);
		void RestorePath();
		void Heuristic() override {};
};

