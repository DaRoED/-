#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "Bullet.h"
#include "LineMesh.h"
#include "UIManager.h"

Player::Player() : Object(ObjectType::Player)
{
}

Player::~Player()
{
}

void Player::Init()
{
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 500;

	_pos.x = 400;
	_pos.y = 500;
}

void Player::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	float stamina = GET_SINGLE(UIManager)->GetStaminaPercent();

	if (_playerTurn == false) return;

	UpdateFireAngle();
	if (stamina != 0.f)
	{
		if (_playerType == PlayerType::MissileTank)
		{
			if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
			{
				stamina = ::clamp(stamina - 100.f * deltaTime, 0.f, 100.f);
				_pos.x -= deltaTime * _stat.speed;
				_dir = Dir::Left;
			}

			if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
			{
				stamina = ::clamp(stamina - 100.f * deltaTime, 0.f, 100.f);
				_pos.x += deltaTime * _stat.speed;
				_dir = Dir::Right;
			}
		}
		else
		{
			if (GET_SINGLE(InputManager)->GetButton(KeyType::LEFT))
			{
				stamina = ::clamp(stamina - 100.f * deltaTime, 0.f, 100.f);
				_pos.x -= deltaTime * _stat.speed;
				_dir = Dir::Left;
			}

			if (GET_SINGLE(InputManager)->GetButton(KeyType::RIGHT))
			{
				stamina = ::clamp(stamina - 100.f * deltaTime, 0.f, 100.f);
				_pos.x += deltaTime * _stat.speed;
				_dir = Dir::Right;
			}
		}

		GET_SINGLE(UIManager)->SetStaminaPercent(stamina);
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		_fireAngle = ::clamp(_fireAngle + deltaTime * 50, 0.f, 75.f);
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		_fireAngle = ::clamp(_fireAngle - deltaTime * 50, 0.f, 75.f);
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::Q))
	{
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::E))
	{
	}

	if (_shoted == false)
	{
		if (GET_SINGLE(InputManager)->GetButton(KeyType::SpaceBar))
		{
			// 미사일 발사 로직
			float percent = GET_SINGLE(UIManager)->GetPowerPercent();
			percent = min(100.f, percent + 100 * deltaTime);
			GET_SINGLE(UIManager)->SetPowerPercent(percent);
		}

		if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::SpaceBar))
		{
			float percent = GET_SINGLE(UIManager)->GetPowerPercent();
			float speed = 10.f * percent;
			float angle = GET_SINGLE(UIManager)->GetBarrelAngle();

			Bullet* bullet = GET_SINGLE(ObjectManager)->CreateObject<Bullet>();
			bullet->SetOwner(this);
			bullet->SetPos(_pos);
			bullet->SetSpeed(Vector(speed * cos(angle * PI / 180), -1 * speed * sin(angle * PI / 180)));
			GET_SINGLE(ObjectManager)->Add(bullet);
			SetShoted(true);
		}
	}
}

void Player::Render(HDC hdc)
{
	if (_dir == Dir::Left)
	{
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());

		if (mesh)
			mesh->Render(hdc, _pos, 0.5f, 0.5f);
	}
	else
	{
		const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());

		if (mesh)
			mesh->Render(hdc, _pos, -0.5f, 0.5f);
	}

	if (_playerTurn)
	{
		RECT rect;
		rect.bottom = static_cast<LONG>(_pos.y - 60);
		rect.left = static_cast<LONG>(_pos.x - 10);
		rect.right = static_cast<LONG>(_pos.x + 10);
		rect.top = static_cast<LONG>(_pos.y - 80);

		HBRUSH brush = ::CreateSolidBrush(RGB(250, 235, 197));
		HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, brush);

		::Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);

		::SelectObject(hdc, oldBrush);
		::DeleteObject(brush);
	}

	// Utils::DrawCircle(hdc, _pos, 50);

	HPEN pen =::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);

	//Pos firePos = GetFirePos();
	//Utils::DrawLine(hdc, Pos(_pos.x + _barrelW.x, _pos.y + _barrelW.y), firePos);

	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}

wstring Player::GetMeshKey()
{
	if (_playerType == PlayerType::MissileTank) return L"MissileTank";
	return L"CanonTank";
}

void Player::UpdateFireAngle()
{
	if (_dir == Dir::Left)
	{
		GET_SINGLE(UIManager)->SetPlayerAngle(180);
		GET_SINGLE(UIManager)->SetBarrelAngle(180 - _fireAngle);
	}
	else
	{
		GET_SINGLE(UIManager)->SetPlayerAngle(0);
		GET_SINGLE(UIManager)->SetBarrelAngle(_fireAngle);
	}
}