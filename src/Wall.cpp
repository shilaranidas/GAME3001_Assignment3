#include "Wall.h"
#include "Game.h"

Wall::Wall()
{
	TheTextureManager::Instance()->load("../Assets/textures/wall.png",
		"wall", TheGame::Instance()->getRenderer());

	const auto size = TheTextureManager::Instance()->getTextureSize("wall");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0.0f, 0.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setType(WALL);
}

Wall::~Wall()
{
}

void Wall::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("wall", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, true);
}

void Wall::update()
{
}

void Wall::clean()
{
}
