#pragma once

#include <chrono>
#include <fstream>
#include <thread>
#include <mutex>


namespace Shadow {

struct ProfilerResult {
    std::string Name;
    long long Start, End;
    std::thread::id ThreadID;
};

class Profiler {
public:
    static Profiler &Instance() {
        static Profiler instance;
        return instance;
    }

    void Init(std::string const &filePath) {
        file.open(filePath);
        WriteHeader();
        resultCount = 0;
    }

    void Shutdown() {
        WriteFooter();
        file.close();
    }

    void WriteResult(ProfilerResult const &result) {
        std::lock_guard<std::mutex> lock(mutex);

        if (resultCount > 0)
            file << ",";

        file << "{";
        file << R"("cat":"function",)";
        file << R"("dur":)" << (result.End - result.Start) << ",";
        file << R"("name":")" << result.Name << "\",";
        file << R"("ph":"X",)";
        file << R"("pid":0,)";
        file << R"("tid":)" << result.ThreadID << ",";
        file << R"("ts":)" << result.Start;
        file << "}";

        resultCount++;
    }

private:
    Profiler()
        : resultCount(0)
    {

    };
    ~Profiler() = default;

    void WriteHeader() {
        file << R"({"otherData": {}, "traceEvents":[)";
    }

    void WriteFooter() {
        file << R"(]})";
    }

    std::ofstream file;
    int resultCount;
    std::mutex mutex;
};

class ProfilerTimer {
public:
    explicit ProfilerTimer(const char* name)
        : result({name, 0,0})
    {
        startTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~ProfilerTimer() {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        result.Start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimepoint).time_since_epoch().count();
        result.End   = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        result.ThreadID = std::this_thread::get_id();

        Profiler::Instance().WriteResult(result);
    }

private:
    ProfilerResult result;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTimepoint;
};

}


#ifdef SH_PROFILE
    #define SH_PROFILE_INIT(filePath) Shadow::Profiler::Instance().Init(filePath)
    #define SH_PROFILE_SHUTDOWN() Shadow::Profiler::Instance().Shutdown()
    #define SH_PROFILE_SCOPE(name) Shadow::ProfilerTimer profilerTimer##__LINE__(name);
    #define SH_PROFILE_FUNCTION() SH_PROFILE_SCOPE(__PRETTY_FUNCTION__)
#else
    #define SH_PROFILE_INIT(filePath)
    #define SH_PROFILE_SHUTDOWN()
    #define SH_PROFILE(name)
    #define SH_PROFILE_FUNCTION()
#endif
