#include "Level1Scene.h"
#include "Game.h"
#include "ExplosionManager.h"
#include "BulletManager.h"
#include "Wall.h"
#include "Util.h"
#include "IMGUI_SDL/imgui_sdl.h"
#include <string>

Level1Scene::Level1Scene()
{
	Level1Scene::start();
}

Level1Scene::~Level1Scene()
= default;

void Level1Scene::draw()
{
	drawDisplayList();
	m_pWall->draw();
	m_pWall1->draw();
	if(m_pPlayer->attack)
		m_pPlayer->drawKnife();
	
	
	BulletManager::Instance()->draw();
	ExplosionManager::Instance()->draw();
	m_showEnemeyHealth();
	// ImGui Rendering section - DO NOT MOVE OR DELETE
	//if (m_displayUI)
	//{
		/*ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());
		SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 255, 255, 255, 255);*/
	//}
}

void Level1Scene::update()
{
	updateDisplayList();
	
	if (!m_pPlayer->attack && CollisionManager::squaredDistance(m_pPlayer->getPosition(), m_pPlaneSprite->getPosition()) < (m_pPlayer->getHeight() + m_pPlaneSprite->getHeight()) * 0.5f + 20)
	{
		std::cout << "attack" << std::endl;
		TheSoundManager::Instance()->playSound("yay", 0);
		m_pPlayer->attack = true;
		
	}
	
	//else
		//m_pPlayer->attack = false;
	BulletManager::Instance()->setGameObject(m_pPlaneSprite);
	BulletManager::Instance()->update();
	if (m_pPlaneSprite->getIsColliding()&& !m_update)
	{
		m_pPlaneSprite->m_health -= 20;
		m_pPlayer->m_score++;
		m_update = true;
	}
	m_showEnemeyHealth();
	m_showPlayerHealth();
	m_showPlayerScore();
	ExplosionManager::Instance()->update();
}

void Level1Scene::clean()
{

	removeAllChildren();
}
void Level1Scene::m_mapTiles()
{
	for (auto tile : m_pGrid)
	{
		const auto x = tile->getGridPosition().x;
		const auto y = tile->getGridPosition().y;

		if (y != 0) { tile->setUp(m_pGrid[x + ((y - 1) * Config::COL_NUM)]); }
		if (x != Config::COL_NUM - 1) { tile->setRight(m_pGrid[(x + 1) + (y * Config::COL_NUM)]); }
		if (y != Config::ROW_NUM - 1) { tile->setDown(m_pGrid[x + ((y + 1) * Config::COL_NUM)]); }
		if (x != 0) { tile->setLeft(m_pGrid[(x - 1) + (y * Config::COL_NUM)]); }
	}
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
			case SDLK_BACKQUOTE:
				TheGame::Instance()->m_debug = !TheGame::Instance()->m_debug;
				break;
			
			case SDLK_1:
				//TheGame::Instance()->changeSceneState(SceneState::PLAY_SCENE);
				break;
			case SDLK_2:
				//TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				break;
			}
			//firing keys
			{
				if (keyPressed == SDLK_RIGHT) {
					auto bullet = BulletManager::Instance()->getBullet();
					bullet->dir = glm::vec2(10, 0);
					bullet->setPosition(m_pPlayer->getPosition());					
					TheSoundManager::Instance()->playSound("fire", 0);
					m_update = false;
				}
				if (keyPressed == SDLK_LEFT) {
					auto bullet = BulletManager::Instance()->getBullet();
					bullet->dir = glm::vec2(-10, 0);
					bullet->setPosition(m_pPlayer->getPosition());
					TheSoundManager::Instance()->playSound("fire", 0);
					m_update = false;
				}
				if (keyPressed == SDLK_UP) {
					auto bullet = BulletManager::Instance()->getBullet();
					bullet->dir = glm::vec2(0, -10);
					bullet->setPosition(m_pPlayer->getPosition());
					TheSoundManager::Instance()->playSound("fire", 0);
					m_update = false;
				}
				if (keyPressed == SDLK_DOWN) {
					auto bullet = BulletManager::Instance()->getBullet();
					bullet->dir = glm::vec2(0, 10);
					bullet->setPosition(m_pPlayer->getPosition());
					TheSoundManager::Instance()->playSound("fire", 0);
					m_update = false;
				}
			}
			// movement keys
			{
				if(keyPressed == SDLK_w)
				{
					std::cout << "move forward" << std::endl;
					if (m_pPlayer->getTile()->getUp()->getTileState() != IMPASSABLE && m_pPlayer->getTile()->getUp()->getTileState() != OBSTACLE)
					{
						m_pPlayer->moveUp();
						m_pPlayer->setTile(m_pPlayer->getTile()->getUp());
					}
					else if(m_pPlayer->getTile()->getUp()->getTileState() == IMPASSABLE)
						TheSoundManager::Instance()->playSound("yay", 0);
				}

				if (keyPressed == SDLK_a)
				{
					if (m_pPlayer->getTile()->getLeft()->getTileState() != IMPASSABLE && m_pPlayer->getTile()->getLeft()->getTileState() != OBSTACLE)
					{
						m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
						m_pPlayer->moveLeft();
						m_pPlayer->setTile(m_pPlayer->getTile()->getLeft());
					}
					else if (m_pPlayer->getTile()->getLeft()->getTileState() == IMPASSABLE)
						TheSoundManager::Instance()->playSound("yay", 0);
					//std::cout << "move left" << std::endl;
					
				}

				if (keyPressed == SDLK_s)
				{
					std::cout << "move back" << std::endl;
					if (m_pPlayer->getTile()->getDown()->getTileState() != IMPASSABLE && m_pPlayer->getTile()->getDown()->getTileState() != OBSTACLE)
					{
						m_pPlayer->moveDown();
						m_pPlayer->setTile(m_pPlayer->getTile()->getDown());
					}
					else if (m_pPlayer->getTile()->getDown()->getTileState() == IMPASSABLE)
						TheSoundManager::Instance()->playSound("yay", 0);
				}

				if (keyPressed == SDLK_d)
				{
					if (m_pPlayer->getTile()->getRight()->getTileState() != IMPASSABLE && m_pPlayer->getTile()->getRight()->getTileState() != OBSTACLE)
					{
						m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
						m_pPlayer->moveRight();
						m_pPlayer->setTile(m_pPlayer->getTile()->getRight());
					}
					else if (m_pPlayer->getTile()->getRight()->getTileState() == IMPASSABLE)
						TheSoundManager::Instance()->playSound("yay", 0);
					//std::cout << "move right" << std::endl;
					
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

void Level1Scene::m_showPlayerHealth()
{
	m_pPlayerHealthLabel->value = m_pPlayer->m_health;
	m_pPlayerHealthLabel->setText("your health " + std::to_string(m_pPlayer->m_health) + "%");
}

void Level1Scene::m_showPlayerScore()
{
	m_pPlayerScoreLable->setText("Score:" + std::to_string(m_pPlayer->m_score));
	m_pPlayerScoreLable->value = 0;
}

void Level1Scene::m_initiateLabel()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pPlayerHealthLabel = new Label("your health " + std::to_string(m_pPlayer->m_health) + "%", "Consolas", 15, blue, glm::vec2(100.0f, 15.0f));
	m_pPlayerHealthLabel->value = m_pPlayer->m_health;
	m_pPlayerHealthLabel->setBorder(true);
	m_pPlayerHealthLabel->setBorderColor({ 0,0,0,255 });
	m_pPlayerHealthLabel->setFillColor({ 222,184,135,255 });
	m_pPlayerHealthLabel->setParent(this);
	addChild(m_pPlayerHealthLabel);
	const SDL_Color orange = { 255, 165, 0, 255 };
	m_pPlayerScoreLable = new Label("Score:" + std::to_string(m_pPlayer->m_score), "Consolas", 15, orange, glm::vec2(400.0f, 15.0f));
	m_pPlayerScoreLable->value = 0;
	m_pPlayerScoreLable->setBorder(true);
	m_pPlayerScoreLable->setBorderColor({ 0,0,0,255 });
	m_pPlayerScoreLable->setFillColor({ 255,255,255,255 });
	m_pPlayerScoreLable->setParent(this);
	addChild(m_pPlayerScoreLable);
	const SDL_Color co = { 0, 0, 0, 255 };
	m_pEnemyHealthLabel = new Label("Health " + std::to_string(m_pPlaneSprite->m_health) + "%", "Consolas", 15, co, glm::vec2(700.0f, 15.0f));
	m_pEnemyHealthLabel->value = m_pPlaneSprite->m_health;
	m_pEnemyHealthLabel->setBorder(true);
	m_pEnemyHealthLabel->setBorderColor({ 255,0,0,255 });
	m_pEnemyHealthLabel->setFillColor({ 255,255,154,255 });
	m_pEnemyHealthLabel->setParent(this);
	addChild(m_pEnemyHealthLabel);
}

void Level1Scene::m_spawnPlane()
{
	m_spawnObject(m_pPlaneSprite);
	m_computeTileValues();
	//m_pPlaneSprite->getTile()->setTileState(GOAL);
}
void Level1Scene::m_showEnemeyHealth()
{
	m_pEnemyHealthLabel->setText("Health " + std::to_string(m_pPlaneSprite->m_health) + "%");
	m_pEnemyHealthLabel->value = m_pPlaneSprite->m_health;

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
	
	// setup default heuristic options
	m_heuristic = MANHATTAN;
	m_buildGrid();
	m_pWall = new Wall();
	m_pWall1 = new Wall();
	
	m_spawnWall();
	m_mapTiles();
	m_pPlaneSprite = new PlaneSprite();
	addChild(m_pPlaneSprite);
	m_spawnPlane();

	m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_spawnPlayer();
	m_initiateLabel();
	m_showEnemeyHealth();
	m_showPlayerHealth();
	m_showPlayerScore();

	
	
}
