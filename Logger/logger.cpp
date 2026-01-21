#include "logger.h"

std::string Logger::m_log_file_path = "/home/tanmey-kumar/Documents/Personal/File_Finder/Log.txt";

void Logger::addLogs(const std::string& logs) {
  if (!fs::exists(m_log_file_path)) {
    createLogsFile();
  }
  std::ofstream out_file(m_log_file_path, std::ios::app);
  if(!out_file) {
    std::cout << "Logger:: log file not opened for log " << std::endl;
    return;
  }
  out_file<<logs;
  out_file << '\n';
}

void Logger::createLogsFile() {
    std::ofstream out_file(m_log_file_path);
    if(!out_file) {
      std::cout << "Logger::Creating LOG FILE failed" << std::endl;
    }
    out_file.close();
}
