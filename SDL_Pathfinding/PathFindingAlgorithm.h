#pragma once
#include "PathFindingGraph.h"
#include <string>
#include "Agent.h"

class PathFindingAlgorithm
{
	public:
	

		PathFindingAlgorithm() {};
		~PathFindingAlgorithm() {};

		virtual void FindPath(Agent* agent, float dt) = 0;
		virtual void Heuristic() = 0;
};

