//Log.cpp
#include "stdafx.h"
#include <time.h>
#include <cstdio>
namespace Mod_Hub_Base
{
	fs::path m_FilePath;
	std::ofstream m_File;
	std::ofstream m_Console;
	std::ifstream m_Input;
	std::mutex m_Mutex;
	std::vector<std::unique_ptr<char[]>> m_Messages;

#define CHARS_FOR_BUFF 4096
#define CHARS_FOR_PARAMS 3500

	static bool useFileOutput = true;

	void Log::Init(HMODULE hModule) {
		try
		{
			m_FilePath.append(std::getenv("appdata"));
			m_FilePath.append(Mod_Menu_Name);
			if (!fs::exists(m_FilePath))
				fs::create_directory(m_FilePath);
			m_FilePath.append(Mod_Menu_Name ".log");
		}
		catch (fs::filesystem_error const&)
		{
		}

		if (!AttachConsole(GetCurrentProcessId()))
			AllocConsole();
		SetConsoleTitleW(MODBASE_WIDE(Mod_Menu_Name));
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);

		m_Console.open("CONOUT$");
		m_Input.open("CONIN$");
		m_File.open(m_FilePath, std::ios_base::out | std::ios_base::app);
	}

#ifdef _DEBUG
	void Log::Debug(const char* fmt, ...)
	{

		va_list va_alist;
		char chLogBuff[CHARS_FOR_BUFF];
		char chParameters[CHARS_FOR_PARAMS];
		char szTimestamp[30];
		struct tm current_tm;
		time_t current_time = time(NULL);

		localtime_s(&current_tm, &current_time);
		sprintf_s(szTimestamp, "[%s] [%02d:%02d:%02d] DEBUG: %%s", Mod_Menu_Name, current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);

		va_start(va_alist, fmt);
		_vsnprintf_s(chParameters, sizeof(chParameters), fmt, va_alist);
		va_end(va_alist);
		sprintf_s(chLogBuff, szTimestamp, chParameters);

		if (useFileOutput) {
			FILE* file;
			if ((fopen_s(&file, g_debugLogFile, "a")) == 0)
			{
				fprintf_s(file, "%s", chLogBuff);
				fclose(file);
			}
		}
		sprintf_s(chLogBuff, "%s\n", chParameters);
		printf(szTimestamp, chLogBuff);
		OutputDebugStringA(chLogBuff);

	}
#endif

	void Log::Msg(const char* fmt, ...) {
		va_list va_alist;
		va_start(va_alist, fmt);
		Log::Main_Logger(Mod_Menu_Name, fmt, va_alist);
		va_end(va_alist);
	}




	void Log::Error(const char* fmt, ...) {
		va_list va_alist;
		char chLogBuff[CHARS_FOR_BUFF];
		char chParameters[CHARS_FOR_PARAMS];
		char szTimestamp[30];
		struct tm current_tm;
		time_t current_time = time(NULL);

		localtime_s(&current_tm, &current_time);
		sprintf_s(szTimestamp, "[%02d:%02d:%02d] ERROR: %%s\n", current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
		string Error_msg = string("FATAL ERROR: ") + string(fmt);
		va_start(va_alist, fmt);
		Log::Main_Logger(Mod_Menu_Name, _strdup(Error_msg.c_str()), va_alist);
		_vsnprintf_s(chParameters, sizeof(chParameters), fmt, va_alist);
		va_end(va_alist);
		sprintf_s(chLogBuff, szTimestamp, chParameters);

		MessageBoxA(NULL, chLogBuff, "ERROR", MB_ICONERROR);
	}

	void Log::Fatal(const char* fmt, ...) {
		va_list va_alist;
		char chLogBuff[CHARS_FOR_BUFF];
		char chParameters[CHARS_FOR_PARAMS];
		char szTimestamp[30];
		struct tm current_tm;
		time_t current_time = time(NULL);
		FILE* file;

		localtime_s(&current_tm, &current_time);
		sprintf_s(szTimestamp, "[%s] [%02d:%02d:%02d] FATAL: %%s\n", Mod_Menu_Name, current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec);
		va_start(va_alist, fmt);
		string Error_msg = string("FATAL ERROR: ") + string(fmt);
		Log::Main_Logger(Mod_Menu_Name, _strdup(Error_msg.c_str()), va_alist);
		_vsnprintf_s(chParameters, sizeof(chParameters), fmt, va_alist);
		va_end(va_alist);

		sprintf_s(chLogBuff, szTimestamp, chParameters);
		MessageBoxA(NULL, chLogBuff, "FATAL ERROR", MB_ICONERROR);

		ExitProcess(0);
	}

	void Log::Main_Logger(const char* type, const char* format, std::va_list args)
	{

		std::lock_guard lock(m_Mutex);

		auto time = std::time(nullptr);
		auto tm = std::localtime(&time);

		char prefix[64] = {};
		std::snprintf(prefix, sizeof(prefix) - 1, "[%s] [%02d:%02d:%02d] ", type, tm->tm_hour, tm->tm_min, tm->tm_sec);

		std::size_t messageLength = std::vsnprintf(nullptr, 0, format, args) + 1;
		auto messageBuffer = std::make_unique<char[]>(messageLength);

		std::uninitialized_fill_n(messageBuffer.get(), messageLength, '\0');
		std::vsnprintf(messageBuffer.get(), messageLength, format, args);

		m_File << prefix << messageBuffer.get() << std::endl;
		m_Console << prefix << messageBuffer.get() << std::endl;

		m_Messages.push_back(std::move(messageBuffer));

	}
}
