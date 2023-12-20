#pragma once
#include <dirent.h>
#include <iostream>
#include <memory>
#include <regex>
#include <vector>

namespace QuickExam::utils {
class FileOperate {
public:
    // 返回path下的后缀subfile的files
    static void listAllFile(std::vector<std::string> &files,
                            const std::string        &path,
                            const std::string        &subfix);
    static void listAllFile(std::vector<std::string> &files,
                            const std::string        &path,
                            std::regex               &reg);
    static bool mkdir(const std::string &dirname);
    static bool isRunningPidfile(const std::string &pidfile);
    static bool rm(const std::string &path);
    static bool mv(const std::string &from, const std::string &to);
    static bool cp(const std::string &from, const std::string &to);
    static bool realpath(const std::string &path, std::string &rpath);
    static bool symlink(const std::string &frm, const std::string &to);
    static bool unlink(const std::string &filename, bool exist = false);

    /*!
     * @brief 获取文件的目录名
     * @param filename 文件名 - 包含路径
     * @return 文件的目录名
     */
    static std::string dirname(const std::string &filename);

    /*!
     * @brief 获取文件的文件名
     * @param filename 文件名 - 包含路径
     * @return 文件的文件名
     */
    static std::string basename(const std::string &filename);

    static bool        openForRead(std::ifstream          &ifs,
                                   const std::string      &filename,
                                   std::ios_base::openmode mode);
    static bool        openForWrite(std::ofstream          &ofs,
                                    const std::string      &filename,
                                    std::ios_base::openmode mode);
    static FILE       *openForWrite(const std::string &filename, const char *mode);
    static std::string read_file(const std::string &filename);
    static bool        write_file(const std::string &file_name, const std::string &content);

    /*!
     * @brief 判断文件是否存在
     * @param file_name 文件名 - 包含路径
     * @return true 文件存在
     */
    static bool file_exist(const std::string &file_name);

    // 判断是否为目录
    static bool is_dir(const char *path) {
        auto dir = opendir(path);
        if (!dir) {
            return false;
        }
        closedir(dir);
        return true;
    }

    // 判断是否是特殊目录
    static bool is_special_dir(const char *path) {
        return strcmp(path, ".") == 0 || strcmp(path, "..") == 0;
    }

    static void scanDir(const std::string                                               &path_in,
                        const std::function<bool(const std::string &path, bool is_dir)> &cb,
                        bool enter_subdirectory) {
        std::string path = path_in;
        if (path.back() == '/') {
            path.pop_back();
        }

        DIR    *pDir;
        dirent *pDirent;
        if ((pDir = opendir(path.data())) == nullptr) {
            // 文件夹无效
            return;
        }
        while ((pDirent = readdir(pDir)) != nullptr) {
            if (is_special_dir(pDirent->d_name)) {
                continue;
            }
            if (pDirent->d_name[0] == '.') {
                // 隐藏的文件
                continue;
            }
            std::string strAbsolutePath = path + "/" + pDirent->d_name;
            bool        isDir           = is_dir(strAbsolutePath.data());
            if (!cb(strAbsolutePath, isDir)) {
                // 不再继续扫描
                break;
            }
            if (isDir && enter_subdirectory) {
                // 如果是文件夹并且扫描子文件夹，那么递归扫描
                scanDir(strAbsolutePath, cb, enter_subdirectory);
            }
        }
        closedir(pDir);
    }
};
}  // namespace QuickExam::utils