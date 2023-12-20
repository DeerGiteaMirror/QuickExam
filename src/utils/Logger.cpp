#include "Logger.h"

namespace QuickExam::utils {

void Logger::log(v_uint32 priority, const std::string &tag, const std::string &message) {
    if (!isLogPriorityEnabled(priority)) {
        return;
    }
    auto time = std::chrono::system_clock::now().time_since_epoch();

    std::lock_guard<std::mutex> lock(m_lock);

    std::stringstream sstr;
    switch (priority) {
        case PRIORITY_V: sstr << "\033[0m V |"; break;

        case PRIORITY_D: sstr << "\033[34m D \033[0m|"; break;

        case PRIORITY_I: sstr << "\033[32m I \033[0m|"; break;

        case PRIORITY_W: sstr << "\033[45m W \033[0m|"; break;

        case PRIORITY_E: sstr << "\033[41m E \033[0m|"; break;

        default: sstr << " " << priority << " |";
    }

    time_t    seconds = std::chrono::duration_cast<std::chrono::seconds>(time).count();
    struct tm now {};
    localtime_r(&seconds, &now);
#ifdef OATPP_DISABLE_STD_PUT_TIME
    char timeBuffer[50];
    strftime(timeBuffer, sizeof(timeBuffer), m_config.timeFormat, &now);
    sstr << timeBuffer;
#else
    sstr << std::put_time(&now, "%Y-%m-%d %H:%M:%S");
#endif

    sstr << "|";

    if (message.empty()) {
        sstr << " " << tag << std::endl;
    } else {
        sstr << " " << tag << " : " << message << std::endl;
    }
    std::cout << sstr.str();

    // 移除\033[0m等颜色占位符
    std::string str = sstr.str();
    if (str.find("\033[0m") != std::string::npos) {
        str.erase(str.find("\033[0m"), 4);
    }
    if (str.find("\033[") != std::string::npos) {
        str.erase(str.find("\033["), 5);
    }

#define TO_FILE(FILE_STREAM, PRIORITY_BUF)                                                         \
    if (FILE_STREAM) {                                                                             \
        (FILE_STREAM) << str;                                                                      \
        (FILE_STREAM).flush();                                                                     \
        if ((PRIORITY_BUF) += str.size() > max_file_size) {                                        \
            roll(priority);                                                                        \
        }                                                                                          \
    } else {                                                                                       \
        reopen(priority);                                                                          \
    }

    switch (priority) {
        case PRIORITY_V: {
            TO_FILE(m_filestream_v, BUFSIZE_V);
        } break;
        case PRIORITY_D: {
            TO_FILE(m_filestream_d, BUFSIZE_D);
        } break;
        case PRIORITY_I: {
            TO_FILE(m_filestream_i, BUFSIZE_I);
        } break;
        case PRIORITY_W: {
            TO_FILE(m_filestream_w, BUFSIZE_W);
        } break;
        case PRIORITY_E: {
            TO_FILE(m_filestream_e, BUFSIZE_E);
        } break;
        default: {
            TO_FILE(m_filestream_a, BUFSIZE_A);
        } break;
    }
    TO_FILE(m_filestream_a, BUFSIZE_A);
}

void Logger::enablePriority(v_uint32 priority) {
    if (priority > PRIORITY_E) {
        return;
    }
    m_logMask |= (1 << priority);
}

void Logger::disablePriority(v_uint32 priority) {
    if (priority > PRIORITY_E) {
        return;
    }
    m_logMask &= ~(1 << priority);
}

bool Logger::isLogPriorityEnabled(v_uint32 priority) {
    if (priority > PRIORITY_E) {
        return true;
    }
    return m_logMask & (1 << priority);
}

bool Logger::reopen(v_uint32 priority) {
#define RE(FILE_STREAM, FILE_NAME, PRIORITY_BUF)                                                   \
    if (FILE_STREAM) {                                                                             \
        (FILE_STREAM).close();                                                                     \
    }                                                                                              \
    (FILE_STREAM).open(FILE_NAME, std::ios::out | std::ios::app);                                  \
    std::ifstream ifs;                                                                             \
    utils::FileOperate::openForRead(ifs, FILE_NAME, std::ios::binary);                             \
    (PRIORITY_BUF) = ifs.tellg();                                                                  \
    ifs.close();                                                                                   \
    return !!(FILE_STREAM);

    switch (priority) {
        case LogPriority::PRIORITY_V: {
            RE(m_filestream_v, m_filename_v, BUFSIZE_V)
        }
        case LogPriority::PRIORITY_D: {
            RE(m_filestream_d, m_filename_d, BUFSIZE_D)
        }
        case LogPriority::PRIORITY_I: {
            RE(m_filestream_i, m_filename_i, BUFSIZE_I)
        }
        case LogPriority::PRIORITY_W: {
            RE(m_filestream_w, m_filename_w, BUFSIZE_W)
        }
        case LogPriority::PRIORITY_E: {
            RE(m_filestream_e, m_filename_e, BUFSIZE_E)
        }
        case LogPriority::PRIORITY_A: {
            RE(m_filestream_a, m_filename_a, BUFSIZE_A)
        }
        default: return false;
    }
}

void Logger::roll(v_uint32 priority) {
#define RO(PRIORITY, FILE_NAME)                                                                      \
    std::string dir_name  = utils::FileOperate::dirname(FILE_NAME);                                  \
    std::string base_name = utils::FileOperate::basename(FILE_NAME);                                 \
    std::string this_file_new_name =                                                                 \
        dir_name + "/" + utils::String::Time2Str(time(0), "%Y-%m-%d_%H:%M:%S") + "." + base_name;    \
    utils::FileOperate::mv(FILE_NAME, this_file_new_name);                                           \
    reopen(PRIORITY);                                                                                \
    std::vector<std::string> files;                                                                  \
    utils::FileOperate::listAllFile(files, utils::FileOperate::dirname(FILE_NAME), ".log");          \
    for (auto &file : files) {                                                                       \
        std::string      base = utils::FileOperate::basename(file);                                  \
        std::string_view base_view(base);                                                            \
        std::string_view time_view = base_view.substr(0, base_view.find('.'));                       \
        std::string      time_str(time_view);                                                        \
        uint64_t         file_time = utils::String::Str2Time(time_str.c_str(), "%Y-%m-%d_%H:%M:%S"); \
        if (file_time + max_history_time < time(0) && file_time != 0) {                              \
            utils::FileOperate::rm(file);                                                            \
        }                                                                                            \
    }

    switch (priority) {
        case LogPriority::PRIORITY_V: {
            RO(LogPriority::PRIORITY_V, m_filename_v)
        } break;
        case LogPriority::PRIORITY_D: {
            RO(LogPriority::PRIORITY_D, m_filename_d)
        } break;
        case LogPriority::PRIORITY_I: {
            RO(LogPriority::PRIORITY_I, m_filename_i)
        } break;
        case LogPriority::PRIORITY_W: {
            RO(LogPriority::PRIORITY_W, m_filename_w)
        } break;
        case LogPriority::PRIORITY_E: {
            RO(LogPriority::PRIORITY_E, m_filename_e)
        } break;
        case LogPriority::PRIORITY_A: {
            RO(LogPriority::PRIORITY_A, m_filename_a)
        } break;

        default: return;
    }
}
}  // namespace QuickExam::utils