#pragma once
#include "oatpp/core/base/Environment.hpp"
#include "utils/FileOperate.h"
#include "utils/String.h"
#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>

enum LogPriority {
    PRIORITY_A = 0,
    PRIORITY_V = 1,
    PRIORITY_D = 2,
    PRIORITY_I = 3,
    PRIORITY_W = 4,
    PRIORITY_E = 5,
};

#if defined(NDEBUG)

#    define LOGV(TAG, ...)                                                                         \
        oatpp::base::Environment::logFormatted(                                                    \
            oatpp::base::Logger::PRIORITY_V,                                                       \
            ::utils::FileOperate::basename(std::string(__FILE__)) + ":" +                          \
                std::to_string(__LINE__) + " 【" + TAG + "】",                                     \
            __VA_ARGS__)

#    define LOGD(TAG, ...)                                                                         \
        oatpp::base::Environment::logFormatted(                                                    \
            oatpp::base::Logger::PRIORITY_D,                                                       \
            ::utils::FileOperate::basename(std::string(__FILE__)) + ":" +                          \
                std::to_string(__LINE__) + " 【" + TAG + "】",                                     \
            __VA_ARGS__)

#    define LOGI(TAG, ...)                                                                         \
        oatpp::base::Environment::logFormatted(                                                    \
            oatpp::base::Logger::PRIORITY_I,                                                       \
            ::utils::FileOperate::basename(std::string(__FILE__)) + ":" +                          \
                std::to_string(__LINE__) + " 【" + TAG + "】",                                     \
            __VA_ARGS__)

#    define LOGW(TAG, ...)                                                                         \
        oatpp::base::Environment::logFormatted(                                                    \
            oatpp::base::Logger::PRIORITY_W,                                                       \
            ::utils::FileOperate::basename(std::string(__FILE__)) + ":" +                          \
                std::to_string(__LINE__) + " 【" + TAG + "】",                                     \
            __VA_ARGS__)

#    define LOGE(TAG, ...)                                                                         \
        oatpp::base::Environment::logFormatted(                                                    \
            oatpp::base::Logger::PRIORITY_E,                                                       \
            ::utils::FileOperate::basename(std::string(__FILE__)) + ":" +                          \
                std::to_string(__LINE__) + " 【" + TAG + "】",                                     \
            __VA_ARGS__)

#    define LOGA(TAG, ...)                                                                         \
        LOGV(TAG, __VA_ARGS__);                                                                    \
        LOGD(TAG, __VA_ARGS__);                                                                    \
        LOGI(TAG, __VA_ARGS__);                                                                    \
        LOGW(TAG, __VA_ARGS__);                                                                    \
        LOGE(TAG, __VA_ARGS__);

#else

#    define LOGV(TAG, ...)                                                                         \
        oatpp::base::Environment::logFormatted(oatpp::base::Logger::PRIORITY_V,                    \
                                               std::string(__FILE__) + ":" +                       \
                                                   std::to_string(__LINE__) + " 【" + TAG + "】",  \
                                               __VA_ARGS__)

#    define LOGD(TAG, ...)                                                                         \
        oatpp::base::Environment::logFormatted(oatpp::base::Logger::PRIORITY_D,                    \
                                               std::string(__FILE__) + ":" +                       \
                                                   std::to_string(__LINE__) + " 【" + TAG + "】",  \
                                               __VA_ARGS__)

#    define LOGI(TAG, ...)                                                                         \
        oatpp::base::Environment::logFormatted(oatpp::base::Logger::PRIORITY_I,                    \
                                               std::string(__FILE__) + ":" +                       \
                                                   std::to_string(__LINE__) + " 【" + TAG + "】",  \
                                               __VA_ARGS__)

#    define LOGW(TAG, ...)                                                                         \
        oatpp::base::Environment::logFormatted(oatpp::base::Logger::PRIORITY_W,                    \
                                               std::string(__FILE__) + ":" +                       \
                                                   std::to_string(__LINE__) + " 【" + TAG + "】",  \
                                               __VA_ARGS__)

#    define LOGE(TAG, ...)                                                                         \
        oatpp::base::Environment::logFormatted(oatpp::base::Logger::PRIORITY_E,                    \
                                               std::string(__FILE__) + ":" +                       \
                                                   std::to_string(__LINE__) + " 【" + TAG + "】",  \
                                               __VA_ARGS__)

#    define LOGA(TAG, ...)                                                                         \
        LOGV(TAG, __VA_ARGS__);                                                                    \
        LOGD(TAG, __VA_ARGS__);                                                                    \
        LOGI(TAG, __VA_ARGS__);                                                                    \
        LOGW(TAG, __VA_ARGS__);                                                                    \
        LOGE(TAG, __VA_ARGS__);

#endif

namespace QuickExam::utils {
// 自定义日志器 继承oatpp::base::Logger
class Logger : public oatpp::base::Logger {
private:
    std::mutex m_lock;
    v_uint32   m_logMask = (1 << PRIORITY_V) | (1 << PRIORITY_D) | (1 << PRIORITY_I) |
                         (1 << PRIORITY_W) | (1 << PRIORITY_E);
    const char   *m_save_dir;
    std::string   m_filename_v;
    std::string   m_filename_d;
    std::string   m_filename_i;
    std::string   m_filename_w;
    std::string   m_filename_e;
    std::string   m_filename_a;
    std::ofstream m_filestream_v;
    std::ofstream m_filestream_d;
    std::ofstream m_filestream_i;
    std::ofstream m_filestream_w;
    std::ofstream m_filestream_e;
    std::ofstream m_filestream_a;

    uint32_t max_file_size;     // 单个日志最大大小
    uint64_t max_history_time;  // 日志最大保存时间 - 超过的日志将被删除
    uint64_t BUFSIZE_V = 0;
    uint64_t BUFSIZE_D = 0;
    uint64_t BUFSIZE_I = 0;
    uint64_t BUFSIZE_W = 0;
    uint64_t BUFSIZE_E = 0;
    uint64_t BUFSIZE_A = 0;

public:
    Logger(const std::string &saveDir, u_int32_t max_size_mb, u_int32_t preserve_days)
        : m_save_dir(saveDir.c_str()),
          max_file_size(max_size_mb * 1024 * 1024),
          max_history_time(preserve_days * 60 * 60 * 24) {
        QuickExam::utils::FileOperate::mkdir(m_save_dir);
        m_filename_v = m_save_dir + std::string("/verbose.log");
        m_filename_d = m_save_dir + std::string("/debug.log");
        m_filename_i = m_save_dir + std::string("/info.log");
        m_filename_w = m_save_dir + std::string("/warn.log");
        m_filename_e = m_save_dir + std::string("/error.log");
        m_filename_a = m_save_dir + std::string("/all.log");
        reopen(LogPriority::PRIORITY_V);
        reopen(LogPriority::PRIORITY_D);
        reopen(LogPriority::PRIORITY_I);
        reopen(LogPriority::PRIORITY_W);
        reopen(LogPriority::PRIORITY_E);
        reopen(LogPriority::PRIORITY_A);
    }

    void log(v_uint32 priority, const std::string &tag, const std::string &message) override;

    /**
     * 启用某个等级的日志
     * @param priority - 日志等级
     */
    void enablePriority(v_uint32 priority);

    /**
     * 禁用某个等级的日志
     * @param priority - 日志等级
     */
    void disablePriority(v_uint32 priority);

    /**
     * 判断某个等级的日志是否启用
     * @param priority
     * @return - 如果启用返回true，否则返回false
     */
    bool isLogPriorityEnabled(v_uint32 priority) override;

    bool reopen(v_uint32 priority);

    void roll(v_uint32 priority);
};
}  // namespace QuickExam::utils