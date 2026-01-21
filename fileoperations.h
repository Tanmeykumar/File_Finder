
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>

#include "fileconstants.h"
#include "Logger/logger.h"

namespace fs = std::filesystem;

class FileOperations {
  static FileSettings m_fileSetting;
  static std::mutex mtx;

 public:
  static std::vector<std::string> findInFileNames(
      const std::vector<std::string>& listOfFiles, const std::string& keyword);

  static bool isSpecialFile(const std::string& fileName);

  static SearchType getSearchType() { return m_fileSetting.m_searchType; }
  static CaseSensitive getCaseType() { return m_fileSetting.m_caseType; }
  static std::string getSearchDirectory() { return m_fileSetting.m_dir; }

  static void setSearchType(const SearchType& searchType);
  static void setCaseType(const CaseSensitive& caseType);
  static void setSearchDirectory(const std::string& path);

  static void setDirectory(const int& dir);
  static void findInFileContent(const std::vector<std::string>& list_of_files,
                                std::string* keyword);
  static void readFileContent(std::string* keyword, const std::string& file);
  static void contentOfAFolder(std::vector<std::string>* listOfFiles,
                               std::vector<std::string>* listOfFolders);
  static void printFileNames(const std::vector<std::string>& listOfMarkedFiles);
};
