//
// Created by 张宇衡 on 2023/4/17.
//

#include "String.h"
#include <cwctype>

namespace QuickExam::utils {
std::string String::UrlDecode(const std::string &str) {
    std::string strTemp;
    size_t      length = str.length();
    for (size_t i = 0; i < length; i++) {
        if (str[i] == '+')
            strTemp += ' ';
        else if (str[i] == '%') {
            if (i + 2 >= length)
                break;
            unsigned char high = FromHex((unsigned char)str[++i]);
            unsigned char low  = FromHex((unsigned char)str[++i]);
            strTemp += high * 16 + low;
        } else
            strTemp += str[i];
    }
    return strTemp;
}

std::string String::UrlEncode(const std::string &str) {
    std::string strTemp;
    size_t      length = str.length();
    for (size_t i = 0; i < length; i++) {
        if (isalnum((unsigned char)str[i]) || (str[i] == '-') || (str[i] == '_') ||
            (str[i] == '.') || (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else {
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);
            strTemp += ToHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}

unsigned char String::FromHex(unsigned char x) {
    unsigned char y;
    if (x >= 'A' && x <= 'Z')
        y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z')
        y = x - 'a' + 10;
    else if (x >= '0' && x <= '9')
        y = x - '0';
    else
        return 0;
    return y;
}

unsigned char String::ToHex(unsigned char x) {
    return x > 9 ? x + 55 : x + 48;
}

std::string String::Time2Str(time_t ts, const std::string &format) {
    struct tm tm {};
    localtime_r(&ts, &tm);
    char buf[64];
    strftime(buf, sizeof(buf), format.c_str(), &tm);
    return buf;
}

time_t String::Str2Time(const char *str, const char *format) {
    struct tm t {};
    memset(&t, 0, sizeof(t));
    if (!strptime(str, format, &t)) {
        return 0;
    }
    return mktime(&t);
}

std::vector<std::string> String::split(const std::string &s, const char *delim) {
    std::vector<std::string> ret;
    size_t                   last  = 0;
    auto                     index = s.find(delim, last);
    while (index != std::string::npos) {
        if (index - last > 0) {
            ret.push_back(s.substr(last, index - last));
        }
        last  = index + strlen(delim);
        index = s.find(delim, last);
    }
    if (!s.size() || s.size() - last > 0) {
        ret.push_back(s.substr(last));
    }
    return ret;
}

time_t String::DayTimeStr2Time(const std::string &str, const std::string &spliter) {
    std::vector<std::string> vec = split(str, spliter.c_str());
    vec.resize(3);
    vec = split(str, spliter.c_str());
    if (vec.size() != 3) {
        return 0;
    }
    long hour = 0, min = 0, sec = 0;
    hour = strtol(vec[0].c_str(), nullptr, 10);
    min  = strtol(vec[1].c_str(), nullptr, 10);
    sec  = strtol(vec[2].c_str(), nullptr, 10);
    return hour * 3600 + min * 60 + sec;
}

std::string String::Time2DayTimeStr(time_t ts, const std::string &spliter) {
    long hour = ts / 3600;
    long min  = (ts % 3600) / 60;
    long sec  = ts % 60;
    return std::to_string(hour) + spliter + std::to_string(min) + spliter + std::to_string(sec);
}

}  // namespace QuickExam::utils