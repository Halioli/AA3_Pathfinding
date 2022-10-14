#include "Node.h"
#include <iostream>

Node::Node(Vector2D pos, int _weight)
{
	SetWeight(_weight);
	SetPos(pos);
}
