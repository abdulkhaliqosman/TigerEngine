#pragma once
#include <cstdio>

namespace jgr
{
	enum class LogLevel
	{
		All,
		Trace,
		Debug,
		Info,
		Warn,
		Error,
		Fatal,
		Off
	};

	class Log
	{
	public:
		JAGUAR_DLL static LogLevel g_LogLevel;

		static constexpr LogLevel DefaultLogLevel = LogLevel::Debug;
	};
}

#define JgrLog(loglevel, ...) if (static_cast<int>(jgr::LogLevel::loglevel) >= static_cast<int>(jgr::Log::g_LogLevel)) { printf("[Log"#loglevel"]:"); printf(__VA_ARGS__); printf("\n"); }
#define JgrLogTrace(...) JgrLog(Trace, __VA_ARGS__);
#define JgrLogDebug(...) JgrLog(Debug, __VA_ARGS__);
#define JgrLogInfo(...) JgrLog(Info, __VA_ARGS__);
#define JgrLogWarn(...) JgrLog(Warn, __VA_ARGS__);
#define JgrLogError(...) JgrLog(Error, __VA_ARGS__);
#define JgrLogFatal(...) JgrLog(Fatal, __VA_ARGS__);