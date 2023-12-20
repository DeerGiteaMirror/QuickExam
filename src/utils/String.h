//
// Created by 张宇衡 on 2023/4/17.
//

#pragma once
#include <cstring>
#include <string>
#include <vector>

namespace QuickExam::utils {

class String {
private:
    static unsigned char ToHex(unsigned char x);

    static unsigned char FromHex(unsigned char x);

public:
    /*!
     * @brief URL编码
     * @param str
     * @return
     */
    static std::string UrlEncode(const std::string &str);

    /*!
     * @brief URL解码
     * @param str
     * @return
     */
    static std::string UrlDecode(const std::string &str);

    /*!
     * @brief 时间戳转字符串
     * @param ts 时间戳
     * @param format 默认为 %Y-%m-%d %H:%M:%S
     * @return
     */
    static std::string Time2Str(time_t ts, const std::string &format = "%Y-%m-%d %H:%M:%S");

    /*!
     * @brief 字符串转时间戳
     * @param str 时间字符串
     * @param format 默认为 %Y-%m-%d %H:%M:%S
     * @return
     */
    static time_t Str2Time(const char *str, const char *format = "%Y-%m-%d %H:%M:%S");

    /*!
     * @brief 字符串分割
     * @param s 字符串
     * @param delim 分隔符
     * @return
     */
    static std::vector<std::string> split(const std::string &s, const char *delim);

    /*!
     * @brief 把一天的时间字符串转换成时间戳
     * @param str 时间字符串
     * @param spliter 分隔符 默认为 :
     * @return 时间戳
     */
    static time_t DayTimeStr2Time(const std::string &str, const std::string &spliter = ":");

    /*!
     * @brief 把时间戳转换成一天的时间字符串
     * @param ts 时间戳
     * @param spliter 分隔符 默认为 :
     * @return 时间字符串
     */
    static std::string Time2DayTimeStr(time_t ts, const std::string &spliter = ":");

    static bool startWith(const std::string &str, const std::string &substr) {
        return str.find(substr) == 0;
    }
};

}  // namespace QuickExam::utils
