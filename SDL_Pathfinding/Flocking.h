#pragma once
#include "SteeringBehavior.h"

class Flocking : public Agent::SteeringBehavior
{
	Flocking();
	~Flocking();

	void ApplySteeringForce(Agent* agent, float dt);
};

