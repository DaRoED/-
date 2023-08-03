#include "pch.h"
#include "Bullet.h"
#include "TimeManager.h"
#include "SceneMananger.h"
#include "ObjectManager.h"
#include "FortressScene.h"
#include "UIManager.h"

Bullet::Bullet() : Object(ObjectType::Projectile)
{
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	_radius = 20.f;

}

void Bullet::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	
	// Wind
	float windPercent = GET_SINGLE(UIManager)->GetWindPercent();
	Vector w = { 7 * windPercent * deltaTime, 0 };
	_speed += w;
	// Gravity
	Vector g = { 0, 980 * deltaTime };
	_speed += g;
	
	_pos += _speed * deltaTime;

	// Ãæµ¹ 
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects)
	{
		if (object->GetObjectType() != ObjectType::Player) continue;
		if (_owner == object) continue;

		Vector dir = object->GetPos() - _pos;
		if (dir.Length() < _radius + object->GetRadius())
		{
			FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneMananger)->GetCurrentScene());

			if (scene)
				scene->ChangePlayerTurn();

			GET_SINGLE(ObjectManager)->Remove(this);
			return;
		}
	}

	if (_pos.y > GWinSizeY * 1.5 || _pos.y < -GWinSizeY * 1.5)
	{
		FortressScene* scene = dynamic_cast<FortressScene*>(GET_SINGLE(SceneMananger)->GetCurrentScene());

		if (scene)
			scene->ChangePlayerTurn();

		GET_SINGLE(ObjectManager)->Remove(this);
		return;
	}
}

void Bullet::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, static_cast<int32>(_radius));
}
