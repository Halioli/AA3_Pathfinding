#pragma once

#include "SalesmanProblem.h"

using namespace std;

SalesmanProblem::SalesmanProblem() // Done!
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	//All nodes set
	graph = new PathFindingGraph(maze->getNumCellX(), maze->getNumCellY(), maze);

	greedyBFS = new GreedyBFS();

	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));
	//srand(8);

	Agent* agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setTarget(Vector2D(-20, -20));
	agents.push_back(agent);

	Vector2D rand_cell(-1, -1);
	// set agent position coords to the center of a random cell
	while (!maze->isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	agents[0]->setPosition(maze->cell2pix(rand_cell));

	// set the coins in a random cell (but at least 3 cells far from the agent)
	for (int i = 0; i < numberOfCoins; i++)
	{
		coinPositions.push_back(Vector2D(-1, -1));
		while ((!maze->isValidCell(coinPositions[i])) || (Vector2D::Distance(coinPositions[i], rand_cell) < 3))
			coinPositions[i] = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	}

	// --- Start new: ---
	targetCoin = greedyBFS->GetClosestPoint(coinPositions, agents[0], graph, maze); // Get by searching the nearest coin
	// --- End new: ---
}

SalesmanProblem::~SalesmanProblem()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
		delete agents[i];
}

void SalesmanProblem::update(float dtime, SDL_Event* event)
{
	++_timer;

	/* Keyboard & Mouse events */
	if (_timer % 100 == 0)
	{
		switch (_currentAlgorithm)
		{
		case GREEDY:
			DoGreedyBFS();
			break;

		case NONE:
		default:
			break;
		}
	}

	switch (event->type)
	{
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		else if (event->key.keysym.scancode == SDL_SCANCODE_G)
		{
			_currentAlgorithm = GREEDY;

			DoGreedyBFS();
		}
		else if (event->key.keysym.scancode == SDL_SCANCODE_N)
		{
			// Usefull for when it gets stuck
			_currentAlgorithm = NONE;
		}
		break;

	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		break;

	default:
		break;
	}

	agents[0]->update(dtime, event);

	if (coinPositions.size() <= 0)
	{
		// Reset algorithm to avoid wierd things
		_currentAlgorithm = NONE;

		Vector2D rand_cell(-1, -1);
		// Set the new coins in a random cell (but at least 3 cells far from the agent)
		for (int i = 0; i < numberOfCoins; i++)
		{
			coinPositions.push_back(Vector2D(-1, -1));
			while ((!maze->isValidCell(coinPositions[i])) || (Vector2D::Distance(coinPositions[i], rand_cell) < 3))
				coinPositions[i] = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
		}
	}
	else if (maze->pix2cell(agents[0]->getPosition()) == coinPositions[targetCoin])
	{
		coinPositions[targetCoin] = Vector2D(-1, -1);
		coinPositions.erase(coinPositions.begin() + targetCoin); // Remove targetCoin from vector

		targetCoin = greedyBFS->GetClosestPoint(coinPositions, agents[0], graph, maze); // Get by searching the nearest coin
	}
}

void SalesmanProblem::DoGreedyBFS()
{
	agents[0]->clearPath();

	for (int i = 0; i < (int)agents.size(); ++i)
	{
		// call greedyBFS
		// O creem una escena per cada algorisme, o en una mateixa escena canviem d'algorisme.
		greedyBFS->startingNode = graph->GetNodeByPosition(maze->pix2cell(agents[i]->getPosition()));
		greedyBFS->SetGoalPosition(coinPositions[targetCoin]);

		greedyBFS->GreedyBFSAlgorithm(graph);

		//agents[0]->addPathPoint //<-- add each path node here transformed into cell2pix(cell)
		for (auto point : greedyBFS->pathToGoal)
		{
			agents[i]->addPathPoint(maze->cell2pix(point->GetPos()));
		}
	}
}

void SalesmanProblem::draw()
{
	drawMaze();
	drawCoin();

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	agents[0]->draw();
}

const char* SalesmanProblem::getTitle()
{
	return "SDL Path Finding :: Salesman Problem";
}

void SalesmanProblem::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{
			if (!maze->isValidCell(Vector2D((float)i, (float)j))) // If the current cell is a wall.
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 115, 115, 115, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			}
			else // If the current cell is not a wall (path).
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 0, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			}
		}
	}
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
}

void SalesmanProblem::drawCoin()
{
	for (int i = 0; i < coinPositions.size(); i++)
	{
		Vector2D coin_coords = maze->cell2pix(coinPositions[i]);
		int offset = CELL_SIZE / 2;
		SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
		SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
	}
}

bool SalesmanProblem::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface* image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}
