#include "MainUpdate.h"
#include "Player.h"
#include "Enemy.h"
#include "G_Enemy.h"
#include "ObjectManager.h"

MainUpdate::MainUpdate() : m_pPlayer(NULL)
{
}

MainUpdate::~MainUpdate()
{
	Destroy();
}

void MainUpdate::Start()
{
	m_hdc = GetDC(g_hWnd);

	m_pPlayer = new Player();
	m_pPlayer->Start();
}

void MainUpdate::Update()
{
	if (m_pPlayer)
		m_pPlayer->Update();
}

void MainUpdate::Render()
{

	list<GameObject*>* EnemyList = ObjectManager::GetInstance()->GetObjectList("Enemy");
	list<GameObject*>* BulletList = ObjectManager::GetInstance()->GetObjectList("Bullet");
	Rectangle(m_hdc, 0, 0, WIDTH, HEIGHT);

	if (m_pPlayer)
		m_pPlayer->Render(m_hdc);

	if (EnemyList != nullptr && !EnemyList->empty())
	{
		for (list<GameObject*>::iterator iter = EnemyList->begin(); iter != EnemyList->end(); ++iter)
			(*iter)->Render(m_hdc);
		for (list<GameObject*>::iterator iter = BulletList->begin(); iter != BulletList->end(); ++iter)
			(*iter)->Render(m_hdc);
	}
}

void MainUpdate::Destroy()
{
	if (m_pPlayer)
	{
		delete m_pPlayer;
		m_pPlayer = NULL;
	}
}
