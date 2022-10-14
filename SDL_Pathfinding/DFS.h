#pragma once
#include "PathFindingAlgorithm.h"

class DFS : public PathFindingAlgorithm
{
	DFS();
	~DFS();

	public:
		void FindPath(Agent* agent, float dt) override;
};

