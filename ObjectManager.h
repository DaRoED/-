#pragma once

class Object;

class ObjectManager
{
	GNERATE_SINGLE(ObjectManager);
	~ObjectManager();

public:
	void Add(Object* object);
	void Remove(Object* object);
	void Clear();

	const vector<Object*>& GetObjects() { return _objects; }

	template<typename T>
	T* CreateObject()
	{
		// static_assert(std::is_convertible<T*, Object*>);

		T* object = new T();
		object->Init();
		return object;
	}

private:
	vector<Object*> _objects;
};