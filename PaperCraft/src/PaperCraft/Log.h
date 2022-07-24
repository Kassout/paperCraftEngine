#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace PaperCraft
{
	class PAPERCRAFT_API Log
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

// Core log macros
#define PPCF_CORE_ERROR(...)	::PaperCraft::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PPCF_CORE_WARN(...)		::PaperCraft::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PPCF_CORE_INFO(...)		::PaperCraft::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PPCF_CORE_TRACE(...)	::PaperCraft::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PPCF_CORE_FATAL(...)	::PaperCraft::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define PPCF_ERROR(...)	::PaperCraft::Log::GetClientLogger()->error(__VA_ARGS__)
#define PPCF_WARN(...)	::PaperCraft::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PPCF_INFO(...)	::PaperCraft::Log::GetClientLogger()->info(__VA_ARGS__)
#define PPCF_TRACE(...)	::PaperCraft::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PPCF_FATAL(...)	::PaperCraft::Log::GetClientLogger()->fatal(__VA_ARGS__)