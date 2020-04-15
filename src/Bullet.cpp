#include "Bullet.h"
#include "Game.h"
#include <utility>

Bullet::Bullet() : m_currentFrame(0), m_bIsActive(false)
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png",
		"spritesheet", TheGame::Instance()->getRenderer());

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spritesheet");

	TheSoundManager::Instance()->load("../Assets/audio/fire.wav",
		"fire", sound_type::SOUND_SFX);

	// set frame width
	setWidth(52);

	// set frame height
	setHeight(52);

	setIsColliding(false);
	setType(BULLET);

	m_buildAnimations();

	reset();
}

Bullet::~Bullet()
= default;

void Bullet::draw()
{
		TheTextureManager::Instance()->playAnimation(
			"spritesheet", m_pAnimations["bullet"],
			getPosition().x, getPosition().y, m_currentFrame, 0.5f,
			TheGame::Instance()->getRenderer(), 0, 255, true);
}

void Bullet::update()
{
	this->setPosition(this->getPosition() + dir);
}

void Bullet::clean()
{
}

void Bullet::reset()
{
	setPosition(-1000.0f, -1000.0f);
	m_bIsActive = false;
}

bool Bullet::isActive()
{
	return m_bIsActive;
}

void Bullet::setActive()
{
	m_currentFrame = 0;
	m_bIsActive = true;
}

void Bullet::m_buildAnimations()
{
	Animation animation = Animation();

	animation.name = "bullet";
	animation.frames.push_back(m_pSpriteSheet->getFrame("bullet"));
	

	m_pAnimations["bullet"] = animation;
}
