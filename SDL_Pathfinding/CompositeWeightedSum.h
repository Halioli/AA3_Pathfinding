#pragma once
#include <vector>
#include "SteeringBehavior.h"

class CompositeWeightedSum
{		
	CompositeWeightedSum();
	~CompositeWeightedSum();

	std::vector<std::pair<SteeringBehavior*, float>> steerings;
	
	void ApplySteeringForce(Agent* agent, float dt);
};