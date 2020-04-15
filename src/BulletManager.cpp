#include "BulletManager.h"

BulletManager* BulletManager::s_pInstance = nullptr;

Bullet* BulletManager::getBullet()
{
	const auto bullet = m_pBulletPool.front();
	bullet->setActive();
	m_pBulletPool.pop_front();
	m_pBulletPool.push_back(bullet);
	return bullet;
}

void BulletManager::setGameObject(GameObject* go)
{
	m_pGameObj = go;
}

void BulletManager::update()
{
	for (auto bullet : m_pBulletPool)
	{
		if (bullet->isActive())
		{
			bullet->setGameObject(m_pGameObj);
			bullet->update();
		}
	}
}

void BulletManager::draw()
{
	for (auto bullet : m_pBulletPool)
	{
		if (bullet->isActive())
		{
			bullet->draw();
		}
	}
}

BulletManager::BulletManager() :m_bulletNumber(20)
{
	m_buildBulletPool();
}

BulletManager::~BulletManager()
= default;

void BulletManager::m_buildBulletPool()
{
	// create the empty object pool structure
	m_pBulletPool = std::list<Bullet*>();

	for (int count = 0; count < m_bulletNumber; ++count)
	{
		m_pBulletPool.push_back(new Bullet());
	}
}
