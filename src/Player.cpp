#include "Player.h"
#include "Game.h"

Player::Player(): m_currentAnimationState(PLAYER_IDLE_RIGHT), attack(false)
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet", TheGame::Instance()->getRenderer());

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spritesheet");
	TheSoundManager::Instance()->load("../Assets/audio/knifesharpener1.flac",
		"yay", sound_type::SOUND_SFX);
	// set frame width
	setWidth(53);

	// set frame height
	setHeight(58);

	setPosition(glm::vec2(400.0f, 300.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	setIsColliding(false);
	setType(PLAYER);

	m_buildAnimations();
}

Player::~Player()
= default;

void Player::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	switch(m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["idle"],
			getPosition().x, getPosition().y, m_pAnimations["idle"].current_frame, 0.12f,
			TheGame::Instance()->getRenderer(), 0, 255, true);
		break;
	case PLAYER_IDLE_LEFT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["idle"],
			getPosition().x, getPosition().y, m_pAnimations["idle"].current_frame, 0.12f,
			TheGame::Instance()->getRenderer(), 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_RUN_RIGHT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["run"],
			getPosition().x, getPosition().y, m_pAnimations["run"].current_frame, 0.25f,
			TheGame::Instance()->getRenderer(), 0, 255, true);
		if(attack)
			TheTextureManager::Instance()->draw("knife", this->getPosition().x+20, this->getPosition().y,
				TheGame::Instance()->getRenderer(), 0, 255, true,SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_RUN_LEFT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["run"],
			getPosition().x, getPosition().y, m_pAnimations["run"].current_frame, 0.25f,
			TheGame::Instance()->getRenderer(), 0, 255, true, SDL_FLIP_HORIZONTAL);
		if (attack)
			TheTextureManager::Instance()->draw("knife", this->getPosition().x - 20, this->getPosition().y,
				TheGame::Instance()->getRenderer(), 0, 255, true);
		break;
	}
	
	
	
}

void Player::update()
{
	
}

void Player::clean()
{
}

void Player::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::setAnimation(const Animation& animation)
{
	m_pAnimations[animation.name] = animation;
}
void Player::moveUp()
{
	const glm::vec2 newPosition = getPosition() + glm::vec2(0, -40);

	setPosition(newPosition);
}
void Player::moveDown()
{
	const glm::vec2 newPosition = getPosition() + glm::vec2(0, 40);

	setPosition(newPosition);
}
void Player::moveLeft()
{
	const glm::vec2 newPosition = getPosition() + glm::vec2(-40, 0);

	setPosition(newPosition);
}
void Player::moveRight()
{
	const glm::vec2 newPosition = getPosition() + glm::vec2(40, 0);

	setPosition(newPosition);
}
void Player::drawKnife()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	switch (m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		
		break;
	case PLAYER_IDLE_LEFT:
		
		break;
	case PLAYER_RUN_RIGHT:
		
		if (attack)
			TheTextureManager::Instance()->draw("knife", xComponent + 20, yComponent,
				TheGame::Instance()->getRenderer(), 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_RUN_LEFT:
		
		if (attack)
			TheTextureManager::Instance()->draw("knife", xComponent - 20, yComponent,
				TheGame::Instance()->getRenderer(), 0, 255, true);
		break;
	}
}
void Player::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-idle-0"));
	idleAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-idle-1"));
	idleAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-idle-2"));
	idleAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-idle-3"));

	m_pAnimations["idle"] = idleAnimation;

	Animation runAnimation = Animation();

	runAnimation.name = "run";
	runAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-run-0"));
	runAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-run-1"));
	runAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-run-2"));
	runAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-run-3"));

	m_pAnimations["run"] = runAnimation;
}
