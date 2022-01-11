// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Library Files:
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Winmm.lib")

// Windows Header Files:
#include <windows.h>
#include <winsdkver.h>
#include <MinHook.h>
#include <sdkddkver.h>
#include <winternl.h>
#include <WinUser.h>
#include <d3d11.h>

#include <cassert>
#include <cinttypes>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <atomic>
#include <Mmsystem.h>
#include <xkeycheck.h>
#include <chrono>
#include <deque>
#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <Psapi.h>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <timeapi.h>
#include <time.h>
#include <intrin.h>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <memory> 
#include <stdarg.h> 
#include <limits>
#include <mutex>
#include <optional>
#include <sstream>
#include <stack>
#include <ShlObj.h>
#include <string>
#include <xstring>
#include <xutility>
#include <thread>
#include <type_traits>
#include <vector>
#include <locale>
#include <codecvt>
#include <stdio.h>

#define MODBASE_WIDE_IMPL(str) L ## str
#define MODBASE_WIDE(str) MODBASE_WIDE_IMPL(str)

#define MODBASE_STRINGIZE_IMPL(x) #x
#define MODBASE_STRINGIZE(x) MODBASE_STRINGIZE_IMPL(x)

#define Mod_Menu_Name "Mod Hub Base"
extern std::string Menu_Path;

namespace Mod_Hub_Base
{
	using namespace std::literals::string_literals;
	using namespace std::chrono_literals;
	using namespace std;
	namespace fs = std::filesystem;

	inline bool g_LogScriptEvents = false;
}

// Additional Header Files:
#include "Log.h"
#include "Memory.h"
#include "types.h"
#include "enums.h"
#include "InputHook.h"
#include "keyboard.h"
#include "CrossMapping.h"
#include "NativeInvoker.h"
#include "nativeCaller.h"
#include "natives.h"
#include "Hooking.h"
#include "types.h"
#include "YTDLoader.h"


// Menu Files:
#include "UI.h"
#include "Main_Script.h"
#include "Functions.h"

extern std::atomic_bool Mod_running;
extern int g_SelectedPlayer;

class globalHandle
{
private:
	void* _handle;

public:
	globalHandle(int index)
		: _handle(&Hooking::m_global_pointer[index >> 18 & 0x3F][index & 0x3FFFF])
	{ }

	globalHandle(void* p)
		: _handle(p)
	{ }

	globalHandle(const globalHandle& copy)
		: _handle(copy._handle)
	{ }

	globalHandle At(int index)
	{
		return globalHandle(reinterpret_cast<void**>(this->_handle) + (index));
	}

	globalHandle At(int index, int size)
	{
		// Position 0 = Array Size
		return this->At(1 + (index * size));
	}

	template <typename T>
	T* Get()
	{
		return reinterpret_cast<T*>(this->_handle);
	}

	template <typename T>
	T& As()
	{
		return *this->Get<T>();
	}
};

