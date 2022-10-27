#pragma once
#include <list>
#include <vector>
#include "Vector2D.h"

class Node 
{
private:
	Vector2D position;

	float weight;


public:
	std::vector<Node*> neighbours;

	Node(Vector2D pos, float _weight = 0);
	~Node();


	void SetWeight(float _weight) { weight = _weight; }
	int GetWeight() { return weight; }
	void SetPos(Vector2D pos)
	{
		position = pos;
	}
	Vector2D GetPos()
	{ 
		return position;
	}
};

