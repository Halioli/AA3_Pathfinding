#pragma once
#include <list>
#include <vector>
#include "Vector2D.h"

class Node 
{
private:
	Vector2D position;

	int weight;

	~Node();

public:
	std::vector<Node*> neighbours;

	Node(Vector2D pos, int _weight = 0);

	void SetWeight(int _weight) { weight = _weight; }
	int GetWeight() { return weight; }
	void SetPos(Vector2D pos) { position = pos; }
	Vector2D GetPos() { return position; }
};

