#pragma once
#ifndef __LEVEL1_SCENE__
#define __LEVEL1_SCENE__

#include "Scene.h"


#include "PlaneSprite.h"
#include "Player.h"
#include "Tile.h"
#include "Wall.h"


class Level1Scene : public Scene
{
public:
	Level1Scene();
	~Level1Scene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	void m_buildGrid();
	void m_resetGrid();
	void m_mapTiles();
private:
	std::vector<Tile*> m_openList;
	std::vector<Tile*> m_closedList;
	glm::vec2 m_mousePosition;
	Wall* m_pWall;
	Wall* m_pWall1;
	Heuristic m_heuristic;
	PlaneSprite* m_pPlaneSprite;
	Player* m_pPlayer;
	// Tile & Grid members
	std::vector<Tile*> m_pGrid;
	void m_spawnPlane();
	void m_spawnPlayer();
	void m_spawnWall();
	void m_spawnObjectAt(PathFindingDisplayObject* object, int tileIndex);
	int m_spawnObject(PathFindingDisplayObject* object);
	void m_computeTileValues();
};

#endif /* defined (__LEVEL1_SCENE__) */