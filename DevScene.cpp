#include "pch.h"
#include "DevScene.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Actor.h"

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
{
}

void DevScene::Update()
{
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		_playerPos.x -= GET_SINGLE(TimeManager)->GetDeltaTime() * _speed;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_playerPos.x += GET_SINGLE(TimeManager)->GetDeltaTime() * _speed;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		_playerPos.y -= GET_SINGLE(TimeManager)->GetDeltaTime() * _speed;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		_playerPos.y += GET_SINGLE(TimeManager)->GetDeltaTime() * _speed;
	}
}

void DevScene::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _playerPos, 50);

}
