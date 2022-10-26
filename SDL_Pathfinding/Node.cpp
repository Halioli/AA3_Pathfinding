#include "Node.h"
#include <iostream>

Node::Node(Vector2D pos, float _weight)
{
	SetWeight(_weight);
	SetPos(pos);
}
