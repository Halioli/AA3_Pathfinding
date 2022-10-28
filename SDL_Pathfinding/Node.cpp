#include "Node.h"
#include <iostream>

Node::Node(Vector2D pos, float _weight)
{
	SetWeight(_weight);
	SetPos(pos);
	cost = 0.f;
}

void Node::SetCost(float _cost)
{
	cost = _cost;
}

float Node::GetCost()
{
	return cost;
}
