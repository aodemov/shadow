#pragma once

#include <memory>

#include <spdlog/spdlog.h>

namespace Shadow {
class Log {
public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return mCoreLogger; };
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return mClientLogger; };

private:
    static std::shared_ptr<spdlog::logger> mCoreLogger;
    static std::shared_ptr<spdlog::logger> mClientLogger;
};

}

#define SH_CORE_INFO(...) ::Shadow::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SH_CORE_WARN(...) ::Shadow::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SH_CORE_ERROR(...) ::Shadow::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SH_CORE_TRACE(...) ::Shadow::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define SH_INFO(...) ::Shadow::Log::GetClientLogger()->info(__VA_ARGS__)
#define SH_WARN(...) ::Shadow::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SH_ERROR(...) ::Shadow::Log::GetClientLogger()->error(__VA_ARGS__)
#define SH_TRACE(...) ::Shadow::Log::GetClientLogger()->trace(__VA_ARGS__)

