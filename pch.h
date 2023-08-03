#pragma once

#include <Windows.h>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <format>
#include <map>

#include "types.h"
#include "Utils.h"
#include "Defines.h"
#include "enums.h"
#include "Values.h"

#define _CTRDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif // DEBUG



using namespace std;