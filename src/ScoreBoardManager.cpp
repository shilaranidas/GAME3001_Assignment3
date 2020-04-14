#include "ScoreBoardManager.h"
#include "Game.h"

ScoreBoardManager* ScoreBoardManager::m_pInstance = nullptr;

void ScoreBoardManager::Start()
{
	const SDL_Color yellow = { 255, 255, 0, 255 };
	m_pLivesLabel = new Label("Lives: 5", "Consolas", 24, yellow,
		glm::vec2(10.0f, 10.0f), TTF_STYLE_NORMAL, false);

	m_pScoreLabel = new Label("Score: 0", "Consolas", 24, yellow,
		glm::vec2(470.0f, 10.0f), TTF_STYLE_NORMAL, false);
}

void ScoreBoardManager::Draw() const
{
	m_pLivesLabel->draw();

	m_pScoreLabel->draw();
}

int ScoreBoardManager::getScore() const
{
	return m_score;
}

void ScoreBoardManager::setScore(const int new_score)
{
	m_score = new_score;
	m_pScoreLabel->setText("Score: " + std::to_string(m_score));
}

int ScoreBoardManager::getLives() const
{
	return m_lives;
}

void ScoreBoardManager::setLives(const int new_lives)
{
	m_lives = new_lives;
	if(m_lives < 1)
	{
		Game::Instance()->changeSceneState(END_SCENE);
	}
	m_pLivesLabel->setText("Lives: " + std::to_string(m_lives));
}

ScoreBoardManager::ScoreBoardManager()
{
	Start();
	setScore(Config::SCORE);
	setLives(Config::LIVES);
}

ScoreBoardManager::~ScoreBoardManager()
= default;
