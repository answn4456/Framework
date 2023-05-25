#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "ObjectManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Prototype.h"
#include "ObjectPool.h"

#include <tchar.h>
//#include <afunix.h>

Stage::Stage() : m_pPlayer(nullptr), EnemyList(nullptr), BulletList(nullptr)
{
}

Stage::~Stage()
{
	Destroy();
}

void Stage::Start()
{
	GET_SINGLE(Prototype)->Start();

	{
		GameObject* ProtoObj = GET_SINGLE(Prototype)->GetGameObject("Player");
		if (ProtoObj != nullptr)
		{
			m_pPlayer = ProtoObj->Clone();
			m_pPlayer->Start();
		}
	}

	{
		GameObject* ProtoObj = GET_SINGLE(Prototype)->GetGameObject("Enemy");
		if (ProtoObj != nullptr)
		{
			GameObject* Object = ProtoObj->Clone()->Start();
			GET_SINGLE(ObjectManager)->AddObject(Object);
		}
	}


	BulletList = GET_SINGLE(ObjectManager)->GetObjectList("Bullet");
	EnemyList = GET_SINGLE(ObjectManager)->GetObjectList("Enemy");
}

void Stage::Update()
{
	list<GameObject*>* EnemyList = GET_SINGLE(ObjectManager)->GetObjectList("Enemy");

	if (m_pPlayer)
		m_pPlayer->Update();

	GET_SINGLE(ObjectManager)->Update();
}

void Stage::Render(HDC _hdc)
{
	if (m_pPlayer)
		m_pPlayer->Render(_hdc);

	GET_SINGLE(ObjectManager)->Render(_hdc);

#define debug 1
#if debug
	list<GameObject*>* normalList = GET_SINGLE(ObjectManager)->GetObjectList("NormalBullet");
	list<GameObject*>* enemyList = GET_SINGLE(ObjectManager)->GetObjectList("Enemy");
	list<GameObject*>* guideList = GET_SINGLE(ObjectManager)->GetObjectList("GuideBullet");

	if (normalList != nullptr && !normalList->empty())
	{
		// ** Buffer 생성
		// ** 배열의 길이는 중요하지 않음. (충분하면 됨.)
		char* NormalBuffer = new char[1024];

		// ** 정수를 문자열로 변환. 10진수로 변환됨.
		_itoa(normalList->size(), NormalBuffer, 10);

		// ** 문자열 포인터를 string 으로 변환.
		string str(NormalBuffer);

		// ** 문자열 포인터 전체 삭제.
		delete NormalBuffer;
		NormalBuffer = nullptr;

		// ** 유니코드 형태로 생성.
		wchar_t* t = new wchar_t[(int)str.size()];
		
		// ** 문자열 복사.
		mbstowcs(t, str.c_str(), (int)str.size());
		
		// ** 출력
		TextOut(_hdc, 50, 50, (LPCWSTR)t, (int)str.size());
	}

	if (guideList != nullptr && !guideList->empty())
	{
		char* GuideBuffer = new char[128];
		_itoa(guideList->size(), GuideBuffer, 10);

		string str(GuideBuffer);

		wchar_t* t = new wchar_t[(int)str.size()];
		mbstowcs(t, str.c_str(), (int)str.size());

		delete GuideBuffer;
		GuideBuffer = nullptr;

		TextOut(_hdc, 50, 70, (LPCWSTR)t, (int)str.size());
	}

	if (enemyList != nullptr && !enemyList->empty())
	{
		char* EnemyBuffer = new char[128];
		_itoa((int)enemyList->size(), EnemyBuffer, 10);

		string str(EnemyBuffer);

		wchar_t* t = new wchar_t[(int)str.size()];
		mbstowcs(t, str.c_str(), (int)str.size());

		delete EnemyBuffer;
		EnemyBuffer = nullptr;

		TextOut(_hdc, 50, 50, (LPCWSTR)t, (int)str.size());
	}
#endif //DEBUG
}

void Stage::Destroy()
{
	if (m_pPlayer)
	{
		delete m_pPlayer;
		m_pPlayer = NULL;
	}

	if (EnemyList != nullptr && !EnemyList->empty())
	{
		for (list<GameObject*>::iterator iter = EnemyList->begin(); iter != EnemyList->end(); ++iter)
		{
			delete (*iter);
			(*iter) = nullptr;
		}
		EnemyList->clear();
	}

	if (BulletList != nullptr && !BulletList->empty())
	{
		for (list<GameObject*>::iterator iter = BulletList->begin(); iter != BulletList->end(); ++iter)
		{
			delete (*iter);
			(*iter) = nullptr;
		}
		BulletList->clear();
	}
}
