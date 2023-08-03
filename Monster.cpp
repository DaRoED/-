#include "pch.h"
#include "Monster.h"
#include <math.h>
#include "InputManager.h"

Monster::Monster() : Object(ObjectType::Monster)
{

}

Monster::~Monster()
{
}

void Monster::Init()
{
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 10;

	_pos = Pos{ 400, 300 };
	_lookPos = Pos{ 400, 70 };
	_lookDir = _lookPos - _pos;
	_lookDir.Normalize();
}

void Monster::Update()
{

}

void Monster::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 100);

	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);

	Utils::DrawLine(hdc, _pos, _lookPos);
	Utils::DrawLine(hdc, _pos, _viewAngleVec1);
	Utils::DrawLine(hdc, _pos, _viewAngleVec2);

	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);

	Vector V1 = _viewAngleVec1 - _pos;
	Vector V2 = _viewAngleVec2 - _pos;

	V1.Normalize();
	V2.Normalize();

	float viewDot = V1.Dot(V2);
	float viewAngle = acos(viewDot);

	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();
	Vector monsterToMouse = mousePos - _pos;
	monsterToMouse.Normalize();

	float dot = monsterToMouse.Dot(_lookDir);

	bool flag = viewAngle / 2 > acos(dot);

	Utils::DrawTexts(hdc, Vector(30, 30), ::format(L"InViewingAngle({0})  V1V2Angle({1})", flag, roundf(viewAngle * 180 / 3.1416)).c_str());

}
