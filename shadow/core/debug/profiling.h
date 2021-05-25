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
        mFile.open(filePath);
        WriteHeader();
        mResultCount = 0;
    }

    void Shutdown() {
        WriteFooter();
        mFile.close();
    }

    void WriteResult(ProfilerResult const &result) {
        std::lock_guard<std::mutex> lock(mMutex);

        if (mResultCount > 0)
            mFile << ",";

        mFile << "{";
        mFile << R"("cat":"function",)";
        mFile << R"("dur":)" << (result.End - result.Start) << ",";
        mFile << R"("name":")" << result.Name << "\",";
        mFile << R"("ph":"X",)";
        mFile << R"("pid":0,)";
        mFile << R"("tid":)" << result.ThreadID << ",";
        mFile << R"("ts":)" << result.Start;
        mFile << "}";

        mResultCount++;
    }

private:
    Profiler()
        : mResultCount(0)
    {

    };
    ~Profiler() = default;

    void WriteHeader() {
        mFile << R"({"otherData": {}, "traceEvents":[)";
    }

    void WriteFooter() {
        mFile << R"(]})";
    }

    std::ofstream mFile;
    int mResultCount;
    std::mutex mMutex;
};

class ProfilerTimer {
public:
    explicit ProfilerTimer(const char* name)
        : mResult({name, 0, 0})
    {
        mStartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~ProfilerTimer() {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        mResult.Start = std::chrono::time_point_cast<std::chrono::microseconds>(mStartTimepoint).time_since_epoch().count();
        mResult.End   = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        mResult.ThreadID = std::this_thread::get_id();

        Profiler::Instance().WriteResult(mResult);
    }

private:
    ProfilerResult mResult;
    std::chrono::time_point<std::chrono::high_resolution_clock> mStartTimepoint;
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
