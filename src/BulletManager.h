#pragma once
#ifndef __BULLET_MANAGER__
#define __BULLET_MANAGER__
#include <list>
#include "Bullet.h"

/* Singleton */
class BulletManager
{
public:
	static BulletManager* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new BulletManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	Bullet* getBullet();
	void setGameObject(GameObject* go);
	void update();
	void draw();

private:
	BulletManager();
	~BulletManager();

	void m_buildBulletPool();
	GameObject* m_pGameObj;
	int m_bulletNumber;
	std::list<Bullet*> m_pBulletPool;

	static BulletManager* s_pInstance;
};

#endif /* defined (__BULLET_MANAGER__) */#pragma once
