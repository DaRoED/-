#include "pch.h"
#include "LineMesh.h"
#include <fstream>

LineMesh::LineMesh()
{
}

LineMesh::~LineMesh()
{
}

void LineMesh::Save(wstring path)
{
	wofstream file;
	file.open(path);

	file << static_cast<int32>(_lines.size()) << endl;
	int32 minX, minY = minX = INT32_MAX, maxX, maxY = maxX = INT32_MIN;

	for (auto& line : _lines)
	{
		POINT from = line.first;
		POINT to = line.second;

		minX = min(min(minX, from.x), min(minX, to.x));
		minY = min(min(minY, from.y), min(minY, to.y));
		maxX = max(max(maxX, from.x), max(maxX, to.x));
		maxY = max(max(maxX, from.x), max(maxY, to.y));
	}

	for (auto& line : _lines)
	{
		POINT from = line.first;
		POINT to = line.second;

		int32 datumPointX = (minX + maxX) / 2;
		int32 datumPointY = (minY + maxX) / 2;

		from.x -= datumPointX; from.y -= datumPointY;
		to.x -= datumPointX; to.y -= datumPointY;

		wstring str = ::format(L"({0},{1})->({2},{3})", from.x, from.y, to.x, to.y);
		file << str << endl;
	}

	file.close();

}

void LineMesh::Load(wstring path)
{
	wifstream file;
	file.open(path);

	int32 count;
	file >> count;

	_lines.clear();


	for (int32 i = 0; i < count; i++)
	{
		//POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		//int32 datumX = mousePos.x, datumY = mousePos.y;

		POINT from, to;
		
		wstring str;
		file >> str;
		::swscanf_s(
			str.c_str(),
			L"(%d,%d)->(%d,%d)",
			&from.x,
			&from.y,
			&to.x,
			&to.y
		);

		_lines.push_back({ from, to });
	}

	file.close();

	int32 minX, minY = minX = INT32_MAX, maxX, maxY = maxX = INT32_MIN;

	for (auto& line : _lines)
	{
		POINT from = line.first;
		POINT to = line.second;

		minX = min(min(minX, from.x), min(minX, to.x));
		minY = min(min(minY, from.y), min(minY, to.y));
		maxX = max(max(maxX, from.x), max(maxX, to.x));
		maxY = max(max(maxX, from.x), max(maxY, to.y));
	}

	_width = maxX - minX;
	_height = maxY - minY;
}

void LineMesh::Render(HDC hdc, Pos pos, float ratioX, float ratioY) const
{
	for (auto& line : _lines)
	{
		POINT pt1 = line.first;
		POINT pt2 = line.second;

		Pos pos1{ pos.x + (float)pt1.x * ratioX, pos.y + (float)pt1.y * ratioY };
		Pos pos2{ pos.x + (float)pt2.x * ratioX, pos.y + (float)pt2.y * ratioY };

		Utils::DrawLine(hdc, pos1, pos2);
	}
}
