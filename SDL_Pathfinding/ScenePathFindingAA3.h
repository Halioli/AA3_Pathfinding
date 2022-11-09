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

class ScenePathFindingAA3 : public Scene
{
	public:
		ScenePathFindingAA3();
		~ScenePathFindingAA3();
		void update(float dtime, SDL_Event* event);
		void DoAStar();
		void DoDijkstra();
		void DoBFS();
		void DoGreedyBFS();
		void DoGreedyBFS(Agent* _agent);
		void draw();
		const char* getTitle();

	private:
		const int NUMBER_OF_ENEMIES = 2;

		enum Algorithm { BREATHFS, GREEDY, DIJKSTRA, ASTAR, NONE };

		Algorithm _currentAlgorithm = NONE;
		bool _chooseAlgorithm = true;

		std::vector<Agent*> agents;
		std::vector<Agent*> enemyAgents;
		Vector2D coinPosition;

		Grid* maze;
		bool draw_grid;

		void drawMaze();
		void drawCoin();
		SDL_Texture* background_texture;
		SDL_Texture* coin_texture;
		bool loadTextures(char* filename_bg, char* filename_coin);

		BFS* breathFirstSearch;
		GreedyBFS* greedyBFS;
		Dijkstra* dijkstra;
		AStar* aStar;
		PathFindingGraph* graph;
};
