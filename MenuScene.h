#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
public:
	MenuScene();
	virtual ~MenuScene();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);
};

