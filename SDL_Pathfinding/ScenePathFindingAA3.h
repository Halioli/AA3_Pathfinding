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
#include "GreedyBFS.h"

class ScenePathFindingAA3 : public Scene
{
	public:
		ScenePathFindingAA3();
		~ScenePathFindingAA3();
		void update(float dtime, SDL_Event* event);
		void draw();
		const char* getTitle();

	private:
		std::vector<Agent*> agents;
		Vector2D coinPosition;

		Grid* maze;
		bool draw_grid;

		void drawMaze();
		void drawCoin();
		SDL_Texture* background_texture;
		SDL_Texture* coin_texture;
		bool loadTextures(char* filename_bg, char* filename_coin);

};
