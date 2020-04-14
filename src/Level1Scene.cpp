#include "Level1Scene.h"
#include "Game.h"
#include "ExplosionManager.h"
#include "Wall.h"
#include "Util.h"


Level1Scene::Level1Scene()
{
	Level1Scene::start();
}

Level1Scene::~Level1Scene()
= default;

void Level1Scene::draw()
{
	drawDisplayList();
	ExplosionManager::Instance()->draw();
}

void Level1Scene::update()
{
	updateDisplayList();
	ExplosionManager::Instance()->update();
}

void Level1Scene::clean()
{

	removeAllChildren();
}

void Level1Scene::handleEvents()
{
	auto wheel = 0;

	SDL_Keycode keyPressed;
	SDL_Keycode keyReleased;
	
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;
		case SDL_MOUSEWHEEL:
			wheel = event.wheel.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			{
			auto explosion = ExplosionManager::Instance()->getExplosion();
			explosion->setPosition(m_mousePosition);
			}
			break;
		case SDL_KEYDOWN:
			keyPressed = event.key.keysym.sym;
			switch (keyPressed)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			case SDLK_1:
				//TheGame::Instance()->changeSceneState(SceneState::PLAY_SCENE);
				break;
			case SDLK_2:
				//TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				break;
			}
			// movement keys
			{
				if(keyPressed == SDLK_w)
				{
					std::cout << "move forward" << std::endl;

				}

				if (keyPressed == SDLK_a)
				{
					//std::cout << "move left" << std::endl;
					m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				}

				if (keyPressed == SDLK_s)
				{
					std::cout << "move back" << std::endl;
				
				}

				if (keyPressed == SDLK_d)
				{
					//std::cout << "move right" << std::endl;
					m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
				}
			}
			
			break;
		case SDL_KEYUP:
			keyReleased = event.key.keysym.sym;

			if (keyReleased == SDLK_a)
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
			}

			if (keyReleased == SDLK_d)
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
			}
			break;
			
		}
	}
}
void Level1Scene::m_buildGrid()
{
	const auto size = Config::TILE_SIZE;
	const auto offset = size * 0.5f;

	m_pGrid = std::vector<Tile*>(); // instantiates a structure of type vector<Tile*>

	for (auto row = 0; row < Config::ROW_NUM; ++row)
	{
		for (auto col = 0; col < Config::COL_NUM; ++col)
		{
			auto tile = new Tile(glm::vec2(offset + size * col, offset + size * row),
				glm::vec2(col, row));
			addChild(tile);
			tile->setTileState(UNVISITED);
			m_pGrid.push_back(tile);
		}
	}
}

void Level1Scene::m_spawnWall()
{
	if (m_pWall->getTile() != nullptr)
	{
		m_pWall->getTile()->setTileState(UNVISITED);
	}

	m_spawnObjectAt(m_pWall, 103);
	m_pGrid[63]->setTileState(IMPASSABLE);
	m_pGrid[83]->setTileState(IMPASSABLE);
	m_pGrid[103]->setTileState(IMPASSABLE);
	m_pGrid[123]->setTileState(IMPASSABLE);
	m_pGrid[143]->setTileState(IMPASSABLE);
	if (m_pWall1->getTile() != nullptr)
	{
		m_pWall1->getTile()->setTileState(UNVISITED);
	}

	m_spawnObjectAt(m_pWall1, 48);
	m_pGrid[8]->setTileState(IMPASSABLE);
	m_pGrid[28]->setTileState(IMPASSABLE);
	m_pGrid[48]->setTileState(IMPASSABLE);
	m_pGrid[68]->setTileState(IMPASSABLE);
	m_pGrid[88]->setTileState(IMPASSABLE);

}
void Level1Scene::m_spawnPlayer()
{
	m_spawnObject(m_pPlayer);
	//m_pPlayer->getTile()->setTileState(START);
}

void Level1Scene::m_spawnPlane()
{
	m_spawnObject(m_pPlaneSprite);
	m_computeTileValues();
	//m_pPlaneSprite->getTile()->setTileState(GOAL);
}
void Level1Scene::m_computeTileValues()
{
	for (auto tile : m_pGrid)
	{
		tile->setHeuristic(m_heuristic);
		tile->setTargetDistance(m_pPlaneSprite->getTile()->getGridPosition());
	}
}
int Level1Scene::m_spawnObject(PathFindingDisplayObject* object)
{
	m_resetGrid();

	Tile* randomTile = nullptr;
	auto randomTileIndex = 0;
	do
	{
		randomTileIndex = int(Util::RandomRange(0, m_pGrid.size() - 1));

		randomTile = m_pGrid[randomTileIndex];
	} while (randomTile->getTileState() != UNVISITED // search for empty tile
		//&& !(randomTileIndex == 63 || randomTileIndex == 83 || randomTileIndex == 103 || randomTileIndex == 123 || randomTileIndex == 143
			//|| randomTileIndex == 8 || randomTileIndex == 28 || randomTileIndex == 48 || randomTileIndex == 68 || randomTileIndex == 88
			//|| randomTileIndex == 267 || randomTileIndex == 268 || randomTileIndex == 269 || randomTileIndex == 270 || randomTileIndex == 271)
		);


	if (object->getTile() != nullptr)
	{
		object->getTile()->setTileState(UNVISITED);
	}

	object->setPosition(randomTile->getPosition());
	object->setTile(randomTile);

	return randomTileIndex;
}

void Level1Scene::m_resetGrid()
{
	for (auto tile : m_openList)
	{
		tile->setTileState(UNVISITED);
		m_openList.pop_back();
	}

	for (auto tile : m_closedList)
	{
		tile->setTileState(UNVISITED);
		m_closedList.pop_back();
	}
}

void Level1Scene::m_spawnObjectAt(PathFindingDisplayObject* object, int tileIndex)
{
	m_resetGrid();

	Tile* tile = nullptr;

	do
	{
		tile = m_pGrid[tileIndex];
		tileIndex++;
	} while (tile->getTileState() != UNVISITED); // search for empty tile


	if (object->getTile() != nullptr)
	{
		object->getTile()->setTileState(UNVISITED);
	}

	object->setPosition(tile->getPosition());
	object->setTile(tile);

}


void Level1Scene::start()
{
	m_buildGrid();
	m_pWall = new Wall();
	m_pWall1 = new Wall();
	m_spawnWall();

	m_pPlaneSprite = new PlaneSprite();
	addChild(m_pPlaneSprite);
	m_spawnPlane();

	m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_spawnPlayer();
}
