#pragma once

#ifdef __DEBUG
#define DEBUGOUT( X, ... ) Log::Debug( X, __VA_ARGS__ )
#else
#define DEBUGOUT( X, ... )
#endif

#if _DEBUG
#define DEBUGMSG Log::Debug
#else
#define DEBUGMSG //
#endif
namespace Mod_Hub_Base
{
	class Log
	{
	public:
		static void Init(HMODULE hModule);
#ifdef _DEBUG
		static void Debug(const char* fmt, ...);
#endif
		static void Msg(const char* fmt, ...);
		static void Error(const char* fmt, ...);
		static void Fatal(const char* fmt, ...);
		static void Main_Logger(const char* type, const char* format, std::va_list args);
	};
}