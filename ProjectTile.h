#pragma once
#include "Object.h"
class ProjectTile : public Object
{
public:
	ProjectTile();
	virtual ~ProjectTile();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetAngle(float angle) { _barrelAngle = angle; }

private:
	float _barrelAngle;
	float _sumTime = 0.f;
	Object* _target = nullptr;
};
