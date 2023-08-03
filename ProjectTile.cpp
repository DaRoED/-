#include "pch.h"
#include "ProjectTile.h"
#include "TimeManager.h"
#include "ObjectManager.h"

ProjectTile::ProjectTile() : Object(ObjectType::Projectile)
{
}

ProjectTile::~ProjectTile()
{
}

void ProjectTile::Init()
{
	_stat.hp = 1;
	_stat.maxHp = 1;
	_stat.speed = 600;
}

void ProjectTile::Update()
{
	float deletaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_target == nullptr)
	{
		_pos.x += _stat.speed * deletaTime * cos(_barrelAngle);
		_pos.y += _stat.speed * deletaTime * sin(_barrelAngle);

		_sumTime += deletaTime;
		if (_sumTime > 0.2f)
		{
			const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();

			for (Object* object : objects)
			{
				if (object->GetObjectType() != ObjectType::Monster) continue;
				_target = object;
			}
		}
	}
	else
	{
		Vector unitVector = _target->GetPos() - _pos;
		unitVector.Normalize();
		_pos += unitVector * _stat.speed * deletaTime;
	}

	// collsion
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();

	for (Object* object : objects)
	{
		if (object == this || object->GetObjectType() != ObjectType::Monster) continue;
		Pos projectTile = GetPos();
		Pos monster = object->GetPos();

		const float dx = projectTile.x - monster.x;
		const float dy = projectTile.y - monster.y;
		float dist = sqrt(dx * dx + dy * dy);
		
		if (dist < 25)
		{
			GET_SINGLE(ObjectManager)->Remove(this);
			GET_SINGLE(ObjectManager)->Remove(object);
			return;
		}
	}

	if (_pos.y < -200)
	{
		GET_SINGLE(ObjectManager)->Remove(this);
		return;
	}
}

void ProjectTile::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 25);
}
