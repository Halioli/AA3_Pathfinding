#pragma once
#include "PathFindingAlgorithm.h"

class Dijkstra : PathFindingAlgorithm
{
	//Priority Queue
	public:
		Dijkstra();
		~Dijkstra();

		void FindPath(Agent* agent, float dt) override;
};