#pragma once

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Seek.h"
#include "PathFollowing.h"
#include "Grid.h"
#include "PathFindingGraph.h"
#include "BFS.h"
#include "GreedyBFS.h"
#include "Dijkstra.h"
#include "AStar.h"

class SalesmanProblem : public Scene
{
public:
	SalesmanProblem();
	~SalesmanProblem();
	void update(float dtime, SDL_Event* event);
	void DoGreedyBFS();
	void draw();
	const char* getTitle();

private:
	// --- Start new: ---
	int targetCoin = 0;
	int _timer = 0;
	// --- End new: ---

	enum Algorithm { BREATHFS, GREEDY, DIJKSTRA, ASTAR, NONE };

	Algorithm _currentAlgorithm = NONE;
	int numberOfCoins = 4;

	std::vector<Agent*> agents;
	std::vector<Vector2D> coinPositions;

	Grid* maze;
	bool draw_grid;

	void drawMaze();
	void drawCoin();
	SDL_Texture* background_texture;
	SDL_Texture* coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);

	GreedyBFS* greedyBFS;
	PathFindingGraph* graph;
};