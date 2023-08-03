#include "pch.h"
#include "SceneMananger.h"
#include "MenuScene.h"
#include "FortressScene.h"

SceneMananger* SceneMananger::s_instance = nullptr;

void SceneMananger::Init()
{
}

void SceneMananger::Update()
{
	if (_scene)
		_scene->Update();
}

void SceneMananger::Render(HDC hdc)
{
	if (_scene)
		_scene->Render(hdc);
}

void SceneMananger::Clear()
{
	SAFE_DELETE(_scene);
}

void SceneMananger::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType) return;

	Scene* newScene = nullptr;
	
	switch (sceneType)
	{
		case SceneType::MenuScene:
			newScene = new MenuScene();
			break;
		case SceneType::FortressScene:
			newScene = new FortressScene();
			break;

	}

	SAFE_DELETE(_scene);

	_scene = newScene;
	_sceneType = sceneType;

	newScene->Init();
}
