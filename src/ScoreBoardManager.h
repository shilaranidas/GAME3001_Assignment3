#pragma once
#ifndef __SCORE_BOARD_MANAGER__
#define __SCORE_BOARD_MANAGER__

#include "Config.h"
#include "Label.h"

class ScoreBoardManager
{
public:
	// singleton
	static ScoreBoardManager* Instance()
	{
		if(m_pInstance == nullptr)
		{
			m_pInstance = new ScoreBoardManager();
			return m_pInstance;
		}
		return m_pInstance;
	}

	void Start();
	void Draw() const;

	// getters and setters
	int getScore() const;
	void setScore(int new_score);

	int getLives() const;
	void setLives(int new_lives);
	
	
private:
	ScoreBoardManager();
	~ScoreBoardManager();

	int m_score{};
	int m_lives{};

	Label* m_pLivesLabel{};
	Label* m_pScoreLabel{};
	
	static ScoreBoardManager* m_pInstance;
};
#endif /* defined (__SCORE_BOARD_MANAGER__) */