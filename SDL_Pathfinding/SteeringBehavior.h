#pragma once
#include "Agent.h"

class SteeringBehavior
{
	SteeringBehavior();
	~SteeringBehavior();

	virtual void ApplySteeringForce(Agent* agent, float dt);
};