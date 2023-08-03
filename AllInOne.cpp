#include <Windows.h>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <format>
#include <map>

using int8 =	__int8;
using int16 =	__int16;
using int32 =	__int32;
using int64 =	__int64;

using uint8 =	unsigned	__int8;
using uint16 =	unsigned	__int16;
using uint32 =	unsigned	__int32;
using uint64 =	unsigned	__int64;


struct Stat
{
	int32 hp = 0;
	int32 maxHp = 0;
	float speed = 0;
};


struct Vector
{
	Vector() { }
	Vector(float x, float y) : x(x), y(y) { }
	Vector(POINT pt) : x((float)pt.x), y((float)pt.y) {}

	Vector operator+(const Vector& other)
	{
		Vector ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}

	Vector operator-(const Vector& other)
	{
		Vector ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}

	Vector operator*(const Vector& other)
	{
		Vector ret;
		ret.x = x * other.x;
		ret.y = y * other.y;
		return ret;
	}

	Vector operator*(float n)
	{
		Vector ret;
		ret.x = x * n;
		ret.y = y * n;
		return ret;
	}

	Vector operator/(const Vector& other)
	{
		Vector ret;
		ret.x = x / other.x;
		ret.y = y / other.y;
		return ret;
	}

	Vector operator/(float n)
	{
		Vector ret;
		ret.x = x / n;
		ret.y = y / n;
		return ret;
	}

	void operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void operator*=(const Vector& other)
	{
		x *= other.x;
		y *= other.y;
	}

	void operator/=(const Vector& other)
	{
		x /= other.x;
		y /= other.y;
	}

	float LengthSquared()
	{
		return x * x + y * y;
	}

	float Length()
	{
		return ::sqrt(LengthSquared());
	}

	void Normalize()
	{
		float length = Length();
		if (length < 0.00000000001f) return;

		x /= length;
		y /= length;
	}

	float Dot(Vector other)
	{
		return x * other.x + y * other.y;
	}

	float Cross(Vector other)
	{
		return x * other.y - other.x * y;
	}

	float x;
	float y;
};

using Pos = Vector;

class Utils
{
public:
	static void DrawTexts(HDC hdc, Pos pos, const std::wstring& str);
	static void DrawRect(HDC hdc, Pos pos, int32 w, int32 h);
	static void DrawCircle(HDC hdc, Pos pos, int32 radius);
	static void DrawLine(HDC hdc, Pos from, Pos to);
};

#define GNERATE_SINGLE(classname)											\
private:																	\
	classname() {};															\
public:																		\
	static classname* GetInstance()											\
	{																		\
		if (s_instance == nullptr) s_instance = new classname();			\
		return s_instance;													\
	}																		\
private:																	\
	static classname* s_instance;											\


#define GET_SINGLE(classname) classname::GetInstance()

#define SAFE_DELETE(ptr)		\
	if (ptr)					\
	{							\
		delete ptr;				\
		ptr = nullptr;			\
	}							

enum class SceneType
{
	None,
	DevScene,
	GameScene,
	EditScene,
	MenuScene,
	FortressScene,
};

enum class Dir
{
	Left,
	Right
};


const int32 GWinSizeX = 800;
const int32 GWinSizeY = 600;

const int32 GMinimapSizeX = 200;
const int32 GMinimapSizeY = 128;

const float PI = 3.141593;

using namespace std;