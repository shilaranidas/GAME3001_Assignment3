#pragma once
#ifndef __BULLET__
#define __BULLET__
#include "DisplayObject.h"
#include "Animation.h"
#include <unordered_map>
#include "SpriteSheet.h"

class Bullet : public DisplayObject
{
public:
	Bullet();
	~Bullet();

	// DisplayObject Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void reset();

	// getters and setters
	bool isActive();
	void setActive();
	glm::vec2 dir;

private:
	void m_buildAnimations();

	SpriteSheet* m_pSpriteSheet;

	int m_currentFrame;
	bool m_bIsActive;

	std::unordered_map<std::string, Animation> m_pAnimations;
};

#endif /* defined (__BULLET__) */#pragma once
