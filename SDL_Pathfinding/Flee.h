#pragma once
#include "SteeringBehavior.h"

class Flee : public Agent::SteeringBehavior
{
	Flee();
	~Flee();

	void ApplySteeringForce(Agent* agent, float dt);
};