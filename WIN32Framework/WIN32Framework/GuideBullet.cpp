#include "GuideBullet.h"
#include "Bullet.h"

GuideBullet::GuideBullet()
{
}

GuideBullet::~GuideBullet()
{
}

void GuideBullet::Start()
{
	Speed = 2.5f;
	BulletBridgeKey = "GuideBullet";
}

void GuideBullet::Update(Transform& transform)
{
	float Horizontal = Target->GetPosition().x - transform.position.x;
	float Vertical = Target->GetPosition().y - transform.position.y;
	
	float Distance = sqrt(double(Horizontal * Horizontal) + double(Vertical * Vertical));
	Vector3 Direction;
	
	if (Distance > 0.0f)
		Direction = Vector3(
			Horizontal / Distance,
			Vertical / Distance,
			0.0f
		);
	else
		Direction = Vector3();
	
	transform.position += Direction * Speed;
}

void GuideBullet::Render(HDC hdc)
{
	Rectangle(hdc,
		(int)(Object->GetPosition().x - Object->GetScale().x * 0.5f),
		(int)(Object->GetPosition().y - Object->GetScale().y * 0.5f),
		(int)(Object->GetPosition().x + Object->GetScale().x * 0.5f),
		(int)(Object->GetPosition().y + Object->GetScale().y * 0.5f)
	);
}

void GuideBullet::Destroy()
{
}
