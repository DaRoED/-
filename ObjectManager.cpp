#include "pch.h"
#include "Object.h"
#include "ObjectManager.h"

ObjectManager* ObjectManager::s_instance = nullptr;


ObjectManager::~ObjectManager()
{
	Clear();
}

void ObjectManager::Add(Object* object)
{
	if (object == nullptr) return;
	auto findit = ::find(_objects.begin(), _objects.end(), object);
	if (findit != _objects.end()) return;
	_objects.push_back(object);
}

void ObjectManager::Remove(Object* object)
{
	if (object == nullptr) return;
	
	auto it = std::remove(_objects.begin(), _objects.end(), object);
	_objects.erase(it, _objects.end());
	delete object;
}

void ObjectManager::Clear()
{
	std::for_each(_objects.begin(), _objects.end(), [=](Object* object) { delete object; });
	_objects.clear();
}
