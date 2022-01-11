//Hooking.cpp
#pragma once
#include "stdafx.h"

namespace Mod_Hub_Base::Protections
{
	bool Anti_CEO_Kick = false;
}

namespace Mod_Hub_Base
{
	using namespace Memory;

	ScriptThread* (*GetActiveThread)() = nullptr;
	HMODULE _hmoduleDLL;
	HANDLE mainFiber;
	DWORD wakeAt;

	std::vector<LPVOID> Hooking::m_hooks;

	IsDlcPresent* Hooking::m_is_dlc_present;
	GetLabelText* Hooking::m_get_label_text;
	Get_Event_Data* Hooking::m_getEvent_Data;
	uint64_t* Hooking::m_frameCount;
	PVOID						Hooking::m_model_spawn_bypass;
	void* Hooking::m_native_return;
	eGameState* Hooking::m_gamestate;
	uint64_t					Hooking::m_world_pointer;
	__int64** Hooking::m_global_pointer;
	static Hooking::NativeRegistrationNew** m_registrationTable;
	static std::unordered_map<uint64_t, Hooking::NativeHandler>	m_handlerCache;
	static std::vector<LPVOID> m_hookedNative;

	const int EVENT_COUNT = 78;
	static std::vector<void*> EventPtr;
	static char EventRestore[EVENT_COUNT] = {};


	/* Start Hooking */
	void Hooking::Start(HMODULE hmoduleDLL)
	{
		_hmoduleDLL = hmoduleDLL;
		Log::Init(hmoduleDLL); // starting the logg / printing to console;

		Log::Msg(R"(
  _____              __   __  __           _ 
 |  __ \             \ \ |  \/  |         | |
 | |__) | __ ___ _____\ \| \  / | ___   __| |
 |  ___/ '__/ _ \______> > |\/| |/ _ \ / _` |
 | |   | | | (_) |    / /| |  | | (_) | (_| |
 |_|   |_|  \___/    /_/ |_|  |_|\___/ \__,_|
)");

		g_YtdLoader = std::make_unique<YTDLoader>(); // Loading YTD / starting YTD

		FindPatterns();
		if (!InitializeHooks()) Cleanup();
	}
	BOOL Hooking::InitializeHooks()
	{
		BOOL returnVal = TRUE;

		if (!iHook.Initialize()) {

			Log::Error("Failed to initialize InputHook");
			returnVal = FALSE;
		}

		if (!HookNatives()) {

			Log::Error("Failed to initialize NativeHooks");
			returnVal = FALSE;
		}

		return returnVal;
	}

	uint64_t CMetaData::m_begin = 0;
	uint64_t CMetaData::m_end = 0;
	DWORD CMetaData::m_size = 0;

	uint64_t CMetaData::begin()
	{
		return m_begin;
	}
	uint64_t CMetaData::end()
	{
		return m_end;
	}
	DWORD CMetaData::size()
	{
		return m_size;
	}

	void CMetaData::init()
	{
		if (m_begin && m_size)
			return;

		m_begin = (uint64_t)GetModuleHandleA(nullptr);
		const IMAGE_DOS_HEADER* headerDos = (const IMAGE_DOS_HEADER*)m_begin;
		const IMAGE_NT_HEADERS* headerNt = (const IMAGE_NT_HEADERS64*)((const BYTE*)headerDos + headerDos->e_lfanew);
		m_size = headerNt->OptionalHeader.SizeOfCode;
		m_end = m_begin + m_size;
		return;
	}

	IsDlcPresent* OG_IS_DLC_PRESENT = nullptr;
	BOOL __cdecl HK_IS_DLC_PRESENT(std::uint32_t hash)
	{
		static uint64_t	last_frame = 0;
		uint64_t current_frame = *Hooking::m_frameCount;
		if (last_frame != current_frame)
		{
			last_frame = current_frame;
			Hooking::onTickInit();
		}
		return OG_IS_DLC_PRESENT(hash);
	}

	GetLabelText* OG_GET_LABEL_TEXT = nullptr;
	const char* HK_GET_LABEL_TEXT(void* _this, const char* label)
	{
		if (std::strcmp(label, "HUD_JOINING") == 0) return Mod_Menu_Name" is fucking best!";
		if (std::strcmp(label, "HUD_TRANSP") == 0) return Mod_Menu_Name" is fucking best!";
		return OG_GET_LABEL_TEXT(_this, label);
	}

	Get_Event_Data* ON_Get_Event_Data = nullptr;
	bool SC_GET_EVENT_DATA(std::int32_t event_Group, std::int32_t event_Index, std::int64_t* args, std::uint32_t arg_Count)
	{
		auto Event_Result = ON_Get_Event_Data(event_Group, event_Index, args, arg_Count);
		if (Event_Result && g_LogScriptEvents) // might but this in a GetTickCount() loop if its lagging or causing crashes
		{
			Log::Msg("\n<===========================================================================>");
			std::string evgroup = std::string("Script event group: ") + std::to_string(event_Group).c_str();
			Log::Msg(_strdup(evgroup.c_str()));
			std::string evindex = std::string("Script event index: ") + std::to_string(event_Index).c_str();
			Log::Msg(_strdup(evindex.c_str()));
			std::string evargcount = std::string("Script event argcount: ") + std::to_string(arg_Count).c_str();
			Log::Msg(_strdup(evargcount.c_str()));
			for (std::uint32_t i = 0; i < arg_Count; ++i) {
				std::string evargs = std::string("Script event args[") + std::to_string(i).c_str() + "] : " + std::to_string(args[i]).c_str();
				Log::Msg(_strdup(evargs.c_str()));
			}
		}
		if (Event_Result)
		{
			static int Event_timer;
			if ((GetTickCount() - Event_timer) > 0) // have all your Special Protections in here to keep from memory crashing / random crashes
			{
				if (args[0] == 1/*Event code*/ && Protections::Anti_CEO_Kick)
				{
					const char* scriptEvent = "CEO Kick"; // just for fun :)
					std::string sender = std::string(" || Sender: ") + PLAYER::GET_PLAYER_NAME(args[1]); // the player trying to Fuck you

					Log::Msg("\n<=========================  ! ATTACKED PROTECTED ! =========================>");
					Log::Msg(" || Script Event: %s", scriptEvent);
					Log::Msg(" || Status: Blocked");
					Log::Msg(_strdup(sender.c_str()));

					return false; // return false to block the code the sender to trying to kick you with
				}
				Event_timer = timeGetTime();
			}
		}
		return Event_Result;
	}

	bool Hooking::HookNatives()
	{
		MH_STATUS status = MH_CreateHook(Hooking::m_is_dlc_present, HK_IS_DLC_PRESENT, (void**)&OG_IS_DLC_PRESENT);
		if ((status != MH_OK && status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(Hooking::m_is_dlc_present) != MH_OK)
			return false;
		Hooking::m_hooks.push_back(Hooking::m_is_dlc_present);

		status = MH_CreateHook(Hooking::m_get_label_text, HK_GET_LABEL_TEXT, (void**)&OG_GET_LABEL_TEXT);
		if (status != MH_OK || MH_EnableHook(Hooking::m_get_label_text) != MH_OK)
			return false;
		Hooking::m_hooks.push_back(Hooking::m_get_label_text);

		//Get Event Data = Can use for event logging and event blocking ;)
		status = MH_CreateHook(Hooking::m_getEvent_Data, SC_GET_EVENT_DATA, (void**)&ON_Get_Event_Data);
		if (status != MH_OK || MH_EnableHook(Hooking::m_getEvent_Data) != MH_OK)
			return false;
		Hooking::m_hooks.push_back(Hooking::m_getEvent_Data);

		return true;
	}

	void __stdcall ScriptFunction(LPVOID lpParameter)
	{
		try
		{
			ScriptMain();

		}
		catch (...)
		{
			Log::Error("Failed scriptFiber");
		}
	}

	void Hooking::onTickInit()
	{
		if (mainFiber == nullptr)
			mainFiber = IsThreadAFiber() ? GetCurrentFiber() : ConvertThreadToFiber(nullptr);

		if (timeGetTime() < wakeAt)
			return;

		static HANDLE scriptFiber;
		if (scriptFiber)
			SwitchToFiber(scriptFiber);
		else
			scriptFiber = CreateFiber(NULL, ScriptFunction, nullptr);
	}

	void Hooking::FailPatterns(const char* name)
	{
		Log::Error("Finding %s", name);
		Cleanup();
	}

	/*
	//CPatternResult
	*/

	CPatternResult::CPatternResult(void* pVoid) :
		m_pVoid(pVoid)
	{}
	CPatternResult::CPatternResult(void* pVoid, void* pBegin, void* pEnd) :
		m_pVoid(pVoid),
		m_pBegin(pBegin),
		m_pEnd(pEnd)
	{}
	CPatternResult::~CPatternResult() {}

	/*
	//CPattern Public
	*/

	CPattern::CPattern(char* szByte, char* szMask) :
		m_szByte(szByte),
		m_szMask(szMask),
		m_bSet(false)
	{}
	CPattern::~CPattern() {}

	CPattern& CPattern::find(int i, uint64_t startAddress)
	{
		match(i, startAddress, false);
		if (m_result.size() <= i)
			m_result.push_back(nullptr);
		return *this;
	}

	CPattern& CPattern::virtual_find(int i, uint64_t startAddress)
	{
		match(i, startAddress, true);
		if (m_result.size() <= i)
			m_result.push_back(nullptr);
		return *this;
	}

	CPatternResult	CPattern::get(int i)
	{
		if (m_result.size() > i)
			return m_result[i];
		return nullptr;
	}

	/*
	//CPattern Private
	*/
	bool	CPattern::match(int i, uint64_t startAddress, bool virt)
	{
		if (m_bSet)
			return false;
		uint64_t	begin = 0;
		uint64_t	end = 0;
		if (!virt)
		{
			CMetaData::init();
			begin = CMetaData::begin() + startAddress;
			end = CMetaData::end();
			if (begin >= end)
				return false;
		}
		int		j = 0;
		do
		{
			if (virt)
				begin = virtual_find_pattern(startAddress, (BYTE*)m_szByte, m_szMask) + 1;
			else
				begin = find_pattern(begin, end, (BYTE*)m_szByte, m_szMask) + 1;
			if (begin == NULL)
				break;
			j++;
		} while (j < i);

		m_bSet = true;
		return true;
	}

	bool	CPattern::byte_compare(const BYTE* pData, const BYTE* btMask, const char* szMask)
	{
		for (; *szMask; ++szMask, ++pData, ++btMask)
			if (*szMask == 'x' && *pData != *btMask)
				break;
		if ((*szMask) != 0)
			return false;
		return true;
	}


	uint64_t	CPattern::find_pattern(uint64_t address, uint64_t end, BYTE* btMask, char* szMask)
	{
		size_t len = strlen(szMask) + 1;
		for (uint64_t i = 0; i < (end - address - len); i++)
		{
			BYTE* ptr = (BYTE*)(address + i);
			if (byte_compare(ptr, btMask, szMask))
			{
				m_result.push_back(CPatternResult((void*)(address + i)));
				return address + i;
			}
		}
		return NULL;
	}

	uint64_t	CPattern::virtual_find_pattern(uint64_t address, BYTE* btMask, char* szMask)
	{
		MEMORY_BASIC_INFORMATION mbi;
		char* pStart = nullptr;
		char* pEnd = nullptr;
		char* res = nullptr;
		size_t	maskLen = strlen(szMask);

		while (res == nullptr && sizeof(mbi) == VirtualQuery(pEnd, &mbi, sizeof(mbi)))
		{
			pStart = pEnd;
			pEnd += mbi.RegionSize;
			if (mbi.Protect != PAGE_READWRITE || mbi.State != MEM_COMMIT)
				continue;

			for (int i = 0; pStart < pEnd - maskLen && res == nullptr; ++pStart)
			{
				if (byte_compare((BYTE*)pStart, btMask, szMask))
				{
					m_result.push_back(CPatternResult((void*)pStart, mbi.BaseAddress, pEnd));
					res = pStart;
				}
			}

			mbi = {};
		}
		return (uint64_t)res;
	}

	void	failPat(const char* name)
	{
		Log::Error("Failed to find %s pattern.", name);
	}

	template <typename T>
	void	setPat
	(
		const char* name,
		char* pat,
		char* mask,
		T** out,
		bool		rel,
		int			offset = 0,
		int			deref = 0,
		int			skip = 0
	)
	{
		T* ptr = nullptr;

		CPattern pattern(pat, mask);
		pattern.find(1 + skip);
		if (rel)
			ptr = pattern.get(skip).get_rel<T>(offset);
		else
			ptr = pattern.get(skip).get<T>(offset);

		while (true)
		{
			if (ptr == nullptr)
				failPat(name);

			if (deref <= 0)
				break;
			ptr = *(T**)ptr;
			--deref;
		}

		*out = ptr;
		return;
	}

	template <typename T>
	void	setFn
	(
		const char* name,
		char* pat,
		char* mask,
		T* out,
		int			skip = 0
	)
	{
		char* ptr = nullptr;

		CPattern pattern(pat, mask);
		pattern.find(1 + skip);
		ptr = pattern.get(skip).get<char>(0);

		if (ptr == nullptr)
			failPat(name);

		*out = (T)ptr;
		return;
	}

	template <typename T>
	void	setPattern
	(
		const char* name,
		char* pat,
		char* mask,
		T** out,
		bool		rel,
		int			offset = 0,
		int			deref = 0,
		int			skip = 0
	)
	{
		T* ptr = nullptr;

		CPattern pattern(pat, mask);
		pattern.find(1 + skip);
		if (rel)
			ptr = pattern.get(skip).get_rel<T>(offset);
		else
			ptr = pattern.get(skip).get<T>(offset);

		while (true)
		{
			if (ptr == nullptr)
				Log::Error(name);

			if (deref <= 0)
				break;
			ptr = *(T**)ptr;
			--deref;
		}

		*out = ptr;
		return;
	}

	void Hooking::FindPatterns()
	{
		HANDLE steam = GetModuleHandleA("steam_api64.dll");

		auto p_fixVector = pattern("83 79 18 00 48 8B D1 74 4A FF 4A 18");
		auto p_nativeReg = pattern("76 32 48 8B 53 40 48 8D 0D");
		auto p_gameState = pattern("48 85 C9 74 4B 83 3D");
		auto p_getEventData = pattern("48 85 C0 74 14 4C 8B 10");
		auto p_getLabelText = pattern("48 89 5C 24 ? 57 48 83 EC 20 48 8B DA 48 8B F9 48 85 D2 75 44 E8");
		auto p_worldPtr = pattern("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07");
		auto p_globaldPtr = pattern("4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11");
		auto p_modelSpawnBypass = pattern("48 8B C8 FF 52 30 84 C0 74 05 48");
		auto p_nativeReturnAddress = pattern("FF E3");
		auto p_ActiveScriptThread = pattern("E8 ? ? ? ? 48 8B 88 10 01 00 00");


		Log::Msg("[ Getting Hooking Start Up <!> PTR ]");

		Log::Msg("[ Getting Start Up Frame count ].");
		setPat<uint64_t>("Frame Count",
			"\x8B\x15\x00\x00\x00\x00\x41\xFF\xCF",
			"xx????xxx",
			&Hooking::m_frameCount,
			true,
			2);


		Log::Msg("[ Getting Start Up <!> Is Dlc Present ]");
		setFn<IsDlcPresent*>("Is Dlc Present",
			"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x81\xF9\x00\x00\x00\x00",
			"xxxx?xxxxxxx????",
			&Hooking::m_is_dlc_present);

		char* c_location = nullptr;
		void* v_location = nullptr;

		Log::Msg("[ Getting Start Up <!> Swapchain. ]");
		Log::Msg("[ Getting Start Up <!> Return Native. ]");

		Log::Msg("[ Getting Start Up <!> Vector3 Result Fixer Func.. ]");
		v_location = p_fixVector.count(1).get(0).get<void>(0);
		if (v_location != nullptr) scrNativeCallContext::SetVectorResults = (void(*)(scrNativeCallContext*))(v_location);

		Log::Msg("[ Getting Start Up <!> Native Registration Table... ]");
		c_location = p_nativeReg.count(1).get(0).get<char>(9);
		c_location == nullptr ? FailPatterns("Native Registration Table") : m_registrationTable = reinterpret_cast<decltype(m_registrationTable)>(c_location + *(int32_t*)c_location + 4);

		Log::Msg("[ Getting Start Up <!> Game State. ]");
		c_location = p_gameState.count(1).get(0).get<char>(2);
		c_location == nullptr ? FailPatterns("gameState") : m_gamestate = reinterpret_cast<decltype(m_gamestate)>(c_location + *(int32_t*)c_location + 5);

		Log::Msg("[ Getting Start Up <!> Event Data.. ]");
		c_location = p_getEventData.count(1).get(0).get<char>(-28);
		c_location == nullptr ? FailPatterns("Get Event Data") : Hooking::m_getEvent_Data = reinterpret_cast<decltype(Hooking::m_getEvent_Data)>(c_location);

		Log::Msg("[ Getting Start Up <!> H Game Label Text... ]");
		c_location = p_getLabelText.count(1).get(0).get<char>(0);
		c_location == nullptr ? FailPatterns("Get Label Text") : Hooking::m_get_label_text = reinterpret_cast<decltype(Hooking::m_get_label_text)>(c_location);



		Log::Msg("[ Getting Start Up <!> World Pointer. ]");
		c_location = p_worldPtr.count(1).get(0).get<char>(0);
		c_location == nullptr ? FailPatterns("World Pointer") : Hooking::m_world_pointer = reinterpret_cast<uint64_t>(c_location) + *reinterpret_cast<int*>(reinterpret_cast<uint64_t>(c_location) + 3) + 7;

		Log::Msg("[ Getting Start Up <!> Global Pointer.. ]");
		c_location = p_globaldPtr.count(1).get(0).get<char>(0);
		__int64 patternAddr = NULL;
		c_location == nullptr ? FailPatterns("Global Pointer") : patternAddr = reinterpret_cast<decltype(patternAddr)>(c_location);
		Hooking::m_global_pointer = (__int64**)(patternAddr + *(int*)(patternAddr + 3) + 7);

		Log::Msg("[ Bypassing <!> Object Restrictions. ]");
		c_location = p_modelSpawnBypass.count(1).get(0).get<char>(8);
		c_location == nullptr ? FailPatterns("Model Spawn Bypass") : Hooking::m_model_spawn_bypass = reinterpret_cast<decltype(Hooking::m_model_spawn_bypass)>(c_location);

		Log::Msg("[ Getting Start Up <!> Return Natives.. ]");
		c_location = p_nativeReturnAddress.count(1).get(0).get<char>(0);
		c_location == nullptr ? FailPatterns("Native Return Adress") : Hooking::m_native_return = reinterpret_cast<decltype(Hooking::m_native_return)>(c_location);


		Log::Msg("[ Gettin Start Up <!> script thread. ]");
		c_location = p_ActiveScriptThread.count(1).get(0).get<char>(1);
		c_location == nullptr ? FailPatterns("Active Script Thread") : GetActiveThread = reinterpret_cast<decltype(GetActiveThread)>(c_location + *(int32_t*)c_location + 4);


		Log::Msg("[ Getting Start Up <!> Event Hook.. ]");
		if ((c_location = Memory::pattern("48 83 EC 28 E8 ? ? ? ? 48 8B 0D ? ? ? ? 4C 8D 0D ? ? ? ? 4C 8D 05 ? ? ? ? BA 03").count(1).get(0).get<char>(0)))
		{
			int i = 0, j = 0, matches = 0, found = 0;
			char* pattern = "\x4C\x8D\x05";
			while (found != EVENT_COUNT)
			{
				if (c_location[i] == pattern[j])
				{
					if (++matches == 3)
					{
						EventPtr.push_back((void*)(reinterpret_cast<uint64_t>(c_location + i - j) + *reinterpret_cast<int*>(c_location + i + 1) + 7));
						found++;
						j = matches = 0;
					}
					j++;
				}
				else
				{
					matches = j = 0;
				}
				i++;
			}
		}
		Log::Msg("[ Initializing <!> natives... ]");
		CrossMapping::initNativeMap();

		MessageBoxA(NULL, Mod_Menu_Name " LOADED!", "LOADED!", MB_ICONINFORMATION);
		Log::Msg(Mod_Menu_Name " <!> loaded!");

	}

	static Hooking::NativeHandler _Handler(uint64_t origHash)
	{
		uint64_t newHash = CrossMapping::MapNative(origHash);
		if (newHash == 0)
		{
			return nullptr;
		}

		Hooking::NativeRegistrationNew* table = m_registrationTable[newHash & 0xFF];

		for (; table; table = table->getNextRegistration())
		{
			for (uint32_t i = 0; i < table->getNumEntries(); i++)
			{
				if (newHash == table->getHash(i))
				{
					return table->handlers[i];
				}
			}
		}
		return nullptr;
	}

	Hooking::NativeHandler Hooking::GetNativeHandler(uint64_t origHash)
	{
		auto& handler = m_handlerCache[origHash];

		if (handler == nullptr)
		{
			handler = _Handler(origHash);
		}

		return handler;
	}
	eGameState Hooking::GetGameState()
	{
		return *m_gamestate;
	}
	uint64_t Hooking::getWorldPtr()
	{
		return Hooking::m_world_pointer;
	}

	__int64** Hooking::getGlobalPtr()
	{
		return Hooking::m_global_pointer;
	}

	void WAIT(DWORD ms)
	{
		wakeAt = timeGetTime() + ms;
		SwitchToFiber(mainFiber);
	}

	void __declspec(noreturn) Hooking::Cleanup()
	{
		iHook.Remove();

		Log::Msg("Cleaning up hooks");
		for (auto func : m_hooks)
		{
			MH_STATUS status;
			if ((status = MH_DisableHook(func)) == MH_OK)
			{
				Log::Msg("Successfully disabled hooks");
			}
			else
			{
				Log::Msg("Failed to disable hookS %p (%s)", func, MH_StatusToString(status));
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50));

		for (auto func : m_hooks)
		{
			MH_STATUS status;
			if ((status = MH_RemoveHook(func)) == MH_OK)
			{
				Log::Msg("Successfully Cleaning up hooks");
				Log::Msg(Mod_Menu_Name" Successfully <!> unloaded.");
			}
			else
			{
				Log::Msg("Failed to unhook %p (%s)", func, MH_StatusToString(status));
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
		fclose(stdout);
		FreeConsole();
		MessageBoxA(NULL, Mod_Menu_Name " UN LOADED!", "UN LOADED!", MB_ICONHAND);
		FreeLibraryAndExitThread(static_cast<HMODULE>(_hmoduleDLL), 0);
	}

	void Hooking::defuseEvent(RockstarEvent e, bool toggle)
	{
		static const unsigned char retn = 0xC3;
		char* p = (char*)EventPtr[e];
		if (toggle)
		{
			if (EventRestore[e] == 0)
				EventRestore[e] = p[0];
			*p = retn;
		}
		else
		{
			if (EventRestore[e] != 0)
				*p = EventRestore[e];
		}
	}

	MinHookKeepalive::MinHookKeepalive()
	{
		MH_Initialize();
	}

	MinHookKeepalive::~MinHookKeepalive()
	{
		MH_Uninitialize();
	}

	MinHookKeepalive g_MinHookKeepalive;
}
