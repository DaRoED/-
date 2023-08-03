#include "pch.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneMananger.h"
#include "ResourceManager.h"
#include "Game.h"

Game::Game()
{
	
}

Game::~Game()
{
	_CrtDumpMemoryLeaks();
	GET_SINGLE(SceneMananger)->Clear();
	GET_SINGLE(ResourceManager)->Clear();
}

void Game::Init(HWND hwnd)
{
	_hWnd = hwnd;
	_hdc = ::GetDC(hwnd);

	::GetClientRect(hwnd, &_rect);

	_hdcBack = ::CreateCompatibleDC(_hdc);
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);
	HBITMAP prev = (HBITMAP) SelectObject(_hdcBack, _bmpBack);
	::DeleteObject(prev);

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SceneMananger)->Init();
	GET_SINGLE(ResourceManager)->Init();
	GET_SINGLE(SceneMananger)->ChangeScene(SceneType::MenuScene);
}

void Game::Update()
{
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SceneMananger)->Update();
}

void Game::Render()
{
	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	{
		wstring bf = format(L"{0}fps  DT: {1}ms", fps, static_cast<int32>(deltaTime * 1000));
		::TextOut(_hdcBack, 650, 10, bf.c_str(), static_cast<int>(bf.size()));
	}

	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		wstring mousePosStr = format(L"(x: {0}, y: {1})", mousePos.x, mousePos.y);
		::TextOut(_hdcBack, 50, 10, mousePosStr.c_str(), static_cast<int>(mousePosStr.size()));
	}

	GET_SINGLE(SceneMananger)->Render(_hdcBack);

	// 더블 버터링 
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY);
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
