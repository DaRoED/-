#pragma once
#include "Object.h"
class Monster : public Object
{
public:
	Monster();
	virtual ~Monster();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	Vector _viewAngleVec1 = { 550.f, 60.f };
	Vector _viewAngleVec2 = { 250.f, 60.f };
	Vector _lookPos = {};
	Vector _lookDir = {};
};

