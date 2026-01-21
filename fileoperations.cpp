#include "fileoperations.h"
#define CONTINUE_IF_TRUE(cond) \
  if ((cond) == true) continue

FileSettings FileOperations::m_fileSetting{};
std::mutex FileOperations::mtx;

void FileOperations::printFileNames(
    const std::vector<std::string>& listOfMarkedFiles) {
  for (const std::string& file : listOfMarkedFiles) {
    std::cout << file << std::endl;
  }
}
std::vector<std::string> FileOperations::findInFileNames(
    const std::vector<std::string>& listOfFiles, const std::string& keyword) {
  std::vector<std::string> list_of_marked_files;
  for (const std::string& file : listOfFiles) {
    std::string intermediate_pattern = ".*" + keyword + ".*";
    std::regex pattern(intermediate_pattern);
    if (std::regex_search(file, pattern)) {
      list_of_marked_files.push_back(file);
    }
  }
  return list_of_marked_files;
}

bool FileOperations::isSpecialFile(const std::string& fileName) {
  bool specialFile = false;
  if (fileName.empty() == false && fileName[0] == '.') {
    specialFile = true;
  }
  return specialFile;
}

void FileOperations::contentOfAFolder(std::vector<std::string>* listOfFiles,
                                      std::vector<std::string>* listOfFolders) {
  std::string path = getSearchDirectory();
  Logger::addLogs("In directory : " + path);
  for (const auto& file : fs::directory_iterator(path)) {
    if (file.is_regular_file()) {
      std::string fileName = file.path().filename().string();
      bool ret = isSpecialFile(fileName);
      CONTINUE_IF_TRUE(ret);
      listOfFiles->push_back(path + "/" + fileName);
      Logger::addLogs("file : " + path + "/" + fileName);
    }

    if (file.is_directory() && getSearchType() == SEARCH_RECURSIVE) {
      std::string fileName = file.path().filename().string();
      bool ret = isSpecialFile(fileName);
      CONTINUE_IF_TRUE(ret);
      std::string new_path = path + "/" + fileName;
      setSearchDirectory(new_path);
      contentOfAFolder(listOfFiles, listOfFolders);
      listOfFolders->push_back(new_path);
      Logger::addLogs("folder : " + new_path);
    }
  }
}

void FileOperations::setDirectory(const int& dir) {
  std::string look_in_dir;
  switch (dir) {
    case 1:
      setSearchDirectory(CURRENT_DIR);
      break;

    case 2:
      setSearchDirectory(HOME_DIR);
      break;

    case 3:
      std::cout << "Enter the directory to look in : " << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::getline(std::cin, look_in_dir);
      if (fs::exists(look_in_dir)) {
        setSearchDirectory(look_in_dir);
      } else {
        std::cout << "No such directory exists" << std::endl;
        setSearchDirectory(CURRENT_DIR);
      }
      break;

    default:
      break;
  }
}

void FileOperations::findInFileContent(
    const std::vector<std::string>& list_of_files, std::string* keyword) {
  for (const std::string& file : list_of_files) {
    readFileContent(keyword, file);
  }
}

void FileOperations::readFileContent(std::string* keyword,
                                     const std::string& file) {
  if (!fs::exists(file)) {
    std::cout << "File : " << file << " doesnt exists" << std::endl;
    return;
  }
  std::ifstream in_file(file);
  if (!in_file.is_open()) {
    std::cout << "file : " << file << " reading failed: Unable to open file"
              << std::endl;
    return;
  }
  std::string line;
  int line_no = 0;
  int total_occurrence = 0;
  std::cout << "Inside file : \"" << file << "\", keyword : \"" << *keyword
            << "\" found at : " << std::endl;
  while (std::getline(in_file, line)) {
    line_no++;
    if (getCaseType() == CASE_INSENCE) {
      std::transform(line.begin(), line.end(), line.begin(),
                     [](unsigned char ch) { return std::tolower(ch); });
      std::transform(keyword->begin(), keyword->end(), keyword->begin(),
                     [](unsigned char ch) { return std::tolower(ch); });
    }
    size_t pos = line.find(*keyword);
    while (pos != std::string::npos) {
      total_occurrence++;
      std::cout << "line : column = " << line_no << " : " << pos << std::endl;
      pos = line.find(*keyword, pos + (*keyword).length());
    }
  }
  in_file.close();
  std::cout << "Total no of occurrence in this file : " << total_occurrence
            << std::endl
            << std::endl;
}

void FileOperations::setSearchType(const SearchType& searchType) {
  m_fileSetting.m_searchType = searchType;
}
void FileOperations::setCaseType(const CaseSensitive& caseType) {
  m_fileSetting.m_caseType = caseType;
}
void FileOperations::setSearchDirectory(const std::string& path) {
  m_fileSetting.m_dir = path;
}
