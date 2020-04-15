#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PathFindingDisplayObject.h"
#include "PlayerAnimationState.h"
#include "Animation.h"
#include "SpriteSheet.h"
#include <unordered_map>

class Player final: public PathFindingDisplayObject
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void drawKnife();
	// setters
	void setAnimationState(PlayerAnimationState new_state);
	void setAnimation(const Animation& animation);
	bool attack;

private:
	void m_buildAnimations();

	SpriteSheet* m_pSpriteSheet;

	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
};

#endif /* defined (__PLAYER__) */