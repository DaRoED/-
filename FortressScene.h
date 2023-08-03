#pragma once
#include "Scene.h"

class FortressScene : public Scene
{
public:
	FortressScene();
	virtual ~FortressScene();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void ChangePlayerTurn();

private:
	int32 _playerTurn;
	float sumTime = 0.f;
};

