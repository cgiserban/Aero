#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"
#include <memory>

namespace Aero
{

    class Log
    {
    public:
        static void init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){return m_coreLogger;}
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger(){return m_clientLogger;}

        static std::shared_ptr<spdlog::logger> m_coreLogger;
        static std::shared_ptr<spdlog::logger> m_clientLogger;
    };
}
//CORE LOGGING MACROS
#define AERO_CORE_TRACE(...) :: Aero::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AERO_CORE_INFO(...) :: Aero::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AERO_CORE_WARN(...) :: Aero::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AERO_CORE_ERROR(...) :: Aero::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AERO_CORE_FATAL(...) :: Aero::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define AERO_CLIENT_TRACE(...) :: Aero::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AERO_CLIENT_INFO(...) :: Aero::Log::GetClientLogger()->info(__VA_ARGS__)
#define AERO_CLIENT_WARN(...) :: Aero::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AERO_CLIENT_ERROR(...) :: Aero::Log::GetClientLogger()->error(__VA_ARGS__)
#define AERO_CLIENT_FATAL(...) :: Aero::Log::GetClientLogger()->fatal(__VA_ARGS__)



