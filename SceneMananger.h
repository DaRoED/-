#pragma once

class Scene;

class SceneMananger
{
	GNERATE_SINGLE(SceneMananger);

public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void Clear();

public:
	void ChangeScene(SceneType scenetype);
	Scene* GetCurrentScene() { return _scene; }

private:
	Scene* _scene = nullptr;
	SceneType _sceneType = SceneType::None;
};

