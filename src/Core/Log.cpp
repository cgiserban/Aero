#include "Log.h"

namespace Aero
{
    std::shared_ptr<spdlog::logger> Log::m_coreLogger;
    std::shared_ptr<spdlog::logger> Log::m_clientLogger;

    void Log::init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        m_coreLogger = spdlog::stdout_color_mt("AERO");
        m_coreLogger->set_level(spdlog::level::trace);

        m_clientLogger = spdlog::stdout_color_mt("APP");
        m_clientLogger->set_level(spdlog::level::trace);
    }


}
