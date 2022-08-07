#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace PaperCraft
{
	// Refererences to external variable declaration.
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// Setup engine log options.
		s_CoreLogger = spdlog::stdout_color_mt("PAPERCRAFT");
		s_CoreLogger->set_level(spdlog::level::trace);

		// Setup client log options.
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}

