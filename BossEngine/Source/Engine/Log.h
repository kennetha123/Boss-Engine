#pragma once

#include <memory.h>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace BossEngine
{
	class BE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}

// do macros for core logger.
#define BE_CORE_TRACE(...)	::BossEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BE_CORE_INFO(...)	::BossEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BE_CORE_WARN(...)	::BossEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BE_CORE_ERROR(...)	::BossEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BE_CORE_FATAL(...)	::BossEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// do macros for client logger.
#define BE_TRACE(...)		::BossEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BE_INFO(...)		::BossEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define BE_WARN(...)		::BossEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BE_ERROR(...)		::BossEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define BE_FATAL(...)		::BossEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)
