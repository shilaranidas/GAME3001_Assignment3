#pragma once
#ifndef __Wall__
#define __Wall__


#include "TextureManager.h"
#include "SoundManager.h"
#include "Tile.h"
#include "Scene.h"
#include "PathFindingDisplayObject.h"

class Wall final : public PathFindingDisplayObject
{
public:
     Wall();
	~Wall();

	// Inherited via GameObject
	virtual void draw() override;

	virtual void update() override;

	virtual void clean() override;

private:

};


#endif /* defined (__Wall__) */