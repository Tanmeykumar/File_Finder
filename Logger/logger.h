#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;
class Logger {
    static std::string m_log_file_path;
    public:
    static void addLogs(const std::string &log);
    static void createLogsFile();
};