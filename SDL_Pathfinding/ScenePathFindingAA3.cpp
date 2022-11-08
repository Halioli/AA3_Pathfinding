#pragma once
#include "ScenePathFindingAA3.h"
using namespace std;


ScenePathFindingAA3::ScenePathFindingAA3()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	//All nodes set
	graph = new PathFindingGraph(maze->getNumCellX(), maze->getNumCellY(), maze);

	breathFirstSearch = new BFS();
	greedyBFS = new GreedyBFS();
	dijkstra = new Dijkstra();
	aStar = new AStar();
	
	loadTextures("../res/maze.png", "../res/coin.png");
	
	srand((unsigned int)time(NULL));

	Agent* agent = new Agent;
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setTarget(Vector2D(-20, -20));
	agents.push_back(agent);

	Agent* enemyAgent = new Agent;
	enemyAgent->loadSpriteTexture("../res/zombie1.png", 8);
	enemyAgent->setBehavior(new PathFollowing);
	enemyAgent->setTarget(Vector2D(-20, -20));
	enemyAgents.push_back(enemyAgent);

	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1, -1);
	while (!maze->isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	agents[0]->setPosition(maze->cell2pix(rand_cell));
	enemyAgents[0]->setPosition(maze->cell2pix(rand_cell));

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1, -1);
	while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell) < 3))
		coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
}

ScenePathFindingAA3::~ScenePathFindingAA3()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}

	for (int i = 0; i < (int)enemyAgents.size(); i++)
		delete enemyAgents[i];
}

void ScenePathFindingAA3::update(float dtime, SDL_Event* event)
{
	if (_chooseAlgorithm)
	{
		_chooseAlgorithm = false;

		switch (_currentAlgorithm)
		{
			case BREATHFS:
				DoBFS();
				break;

			case GREEDY:
				DoGreedyBFS();
				break;

			case DIJKSTRA:
				DoDijkstra();
				break;

			case ASTAR:
				DoAStar();
				break;

			case NONE:
			default:
				break;
		}
	}

	/* Keyboard & Mouse events */
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
			else if (event->key.keysym.scancode == SDL_SCANCODE_B)
			{
				_currentAlgorithm = BREATHFS;

				DoBFS();
			}
			else if (event->key.keysym.scancode == SDL_SCANCODE_D)
			{
				_currentAlgorithm = DIJKSTRA;

				DoDijkstra();
			}
			else if (event->key.keysym.scancode == SDL_SCANCODE_A)
			{
				_currentAlgorithm = ASTAR;

				DoAStar();
			}
			
			break;

		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
			break;

		default:
			break;
	}

	agents[0]->update(dtime, event);
	enemyAgents[0]->update(dtime, event);

	// if we have arrived to the coin, replace it in a random cell!
	if ((agents[0]->getCurrentTargetIndex() == -1) && (maze->pix2cell(agents[0]->getPosition()) == coinPosition))
	{
		coinPosition = Vector2D(-1, -1);
		while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, maze->pix2cell(agents[0]->getPosition())) < 3))
			coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

		_chooseAlgorithm = true;
	}

	// ENEMY
	if ((enemyAgents[0]->getCurrentTargetIndex() == -1) && (maze->pix2cell(enemyAgents[0]->getPosition()) == enemyAgents[0]->getTarget()))
	{
		enemyAgents[0]->setTarget(Vector2D(-1, -1));
		while ((!maze->isValidCell(enemyAgents[0]->getTarget())) || (Vector2D::Distance(enemyAgents[0]->getTarget(), maze->pix2cell(enemyAgents[0]->getPosition())) < 3))
			enemyAgents[0]->setTarget(Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY())));

		_didGreedy = false;
	}

	if (!_didGreedy)
	{
		DoGreedyBFS(enemyAgents);
		_didGreedy = true;
	}
}

void ScenePathFindingAA3::DoAStar()
{
	agents[0]->clearPath();

	// == NEED TO ADD DIFERENT COSTS/WEIGHTS TO EACH NODE CONNECTION ==
	for (int i = 0; i < (int)agents.size(); i++)
	{
		// call A*
		aStar->startingNode = graph->GetNodeByPosition(maze->pix2cell(agents[i]->getPosition()));
		aStar->SetGoalPosition(coinPosition);

		aStar->AStarAlgorithm(graph);

		for (auto point : aStar->pathToGoal)
		{
			agents[i]->addPathPoint(maze->cell2pix(point->GetPos()));
		}
	}
}

void ScenePathFindingAA3::DoDijkstra()
{
	agents[0]->clearPath();

	// == NEED TO ADD DIFERENT COSTS/WEIGHTS TO EACH NODE CONNECTION ==
	for (int i = 0; i < (int)agents.size(); i++)
	{
		// call Dijkstra
		dijkstra->startingNode = graph->GetNodeByPosition(maze->pix2cell(agents[i]->getPosition()));
		dijkstra->SetGoalPosition(coinPosition);

		dijkstra->DijkstraAlgorithm(graph);

		for (auto point : dijkstra->pathToGoal)
		{
			agents[i]->addPathPoint(maze->cell2pix(point->GetPos()));
		}
	}
}

void ScenePathFindingAA3::DoBFS()
{
	agents[0]->clearPath();

	for (int i = 0; i < (int)agents.size(); i++)
	{
		// call BFS
		breathFirstSearch->startingNode = graph->GetNodeByPosition(maze->pix2cell(agents[i]->getPosition()));
		breathFirstSearch->SetGoalPosition(coinPosition);

		breathFirstSearch->BFSAlgorithm(graph);

		for (auto point : breathFirstSearch->pathToGoal)
		{
			agents[i]->addPathPoint(maze->cell2pix(point->GetPos()));
		}
	}
}

void ScenePathFindingAA3::DoGreedyBFS()
{
	agents[0]->clearPath();

	for (int i = 0; i < (int)agents.size(); i++)
	{
		// call greedyBFS
		// O creem una escena per cada algorisme, o en una mateixa escena canviem d'algorisme.
		greedyBFS->startingNode = graph->GetNodeByPosition(maze->pix2cell(agents[i]->getPosition()));
		greedyBFS->SetGoalPosition(coinPosition);

		greedyBFS->GreedyBFSAlgorithm(graph);

		//agents[0]->addPathPoint //<-- add each path node here transformed into cell2pix(cell)
		for (auto point : greedyBFS->pathToGoal)
		{
			agents[i]->addPathPoint(maze->cell2pix(point->GetPos()));
		}
	}
}

void ScenePathFindingAA3::DoGreedyBFS(std::vector<Agent*> _agents)
{
	for (int i = 0; i < (int)_agents.size(); i++)
	{
		_agents[i]->clearPath();

		// call greedyBFS
		// O creem una escena per cada algorisme, o en una mateixa escena canviem d'algorisme.
		greedyBFS->startingNode = graph->GetNodeByPosition(maze->pix2cell(_agents[i]->getPosition()));
		greedyBFS->SetGoalPosition(_agents[i]->getTarget());

		greedyBFS->GreedyBFSAlgorithm(graph);

		//agents[0]->addPathPoint //<-- add each path node here transformed into cell2pix(cell)
		for (auto point : greedyBFS->pathToGoal)
		{
			_agents[i]->addPathPoint(maze->cell2pix(point->GetPos()));
		}
	}
}

void ScenePathFindingAA3::draw()
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
	enemyAgents[0]->draw();
}

const char* ScenePathFindingAA3::getTitle()
{
	return "SDL Path Finding :: PathFinding AA3";
}

void ScenePathFindingAA3::drawMaze()
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
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), (float)(255 * (float)((float)maze->getTerrainWeight(j, i) / 10)), 0, 0, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			}
		}
	}
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
}

void ScenePathFindingAA3::drawCoin()
{
	Vector2D coin_coords = maze->cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}


bool ScenePathFindingAA3::loadTextures(char* filename_bg, char* filename_coin)
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
