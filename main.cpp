#include <iostream>
#include <string>
#include <vector>

#include "fileoperations.h"
int main() {
  std::string keyword;
  std::cout << "Enter the keyword to find : " << std::endl;
  std::getline(std::cin, keyword);
  // Select the directory to look in
  int dir;
  std::cout << "Select the directory to look in :" << std::endl;
  std::cout << "1. From the current directory" << std::endl;
  std::cout << "2. From the root directory" << std::endl;
  std::cout << "3. From the user's directory" << std::endl;
  std::cin >> dir;
  FileOperations::setDirectory(dir);

  // Select the search type
  int search_type;
  std::cout << "Select the search type :" << std::endl;
  std::cout << "1. Locally" << std::endl;
  std::cout << "2. Recursively" << std::endl;
  std::cin >> search_type;
  FileOperations::setSearchType(static_cast<SearchType>(search_type));


  int caseSense = 0;
  std::cout << "Case sensitive occurrences in the content of the files"
            << std::endl;
  std::cout << "1. Yes\t2. No" << std::endl;
  std::cin >> caseSense;
  FileOperations::setCaseType(static_cast<CaseSensitive>(caseSense));

  std::vector<std::string> list_of_files;
  std::vector<std::string> list_of_directories;

  // List down the files and folders in the directory
  FileOperations::contentOfAFolder(&list_of_files, &list_of_directories);


  int nameOrContent = 0;
  std::cout << "Search in the :" << std::endl;
  std::cout << "1. Name of the files" << std::endl;
  std::cout << "2. Name of the folders" << std::endl;
  std::cout << "3. Content of the files" << std::endl;
  std::cout << "4. Content of the file(1 file)" << std::endl;
  std::cin >> nameOrContent;
  if (nameOrContent == 1) {
    // Find the keyword in the files
    std::vector<std::string> marked_files =
        FileOperations::findInFileNames(list_of_files, keyword);
    FileOperations::printFileNames(marked_files);
  } else if (nameOrContent == 2) {
    // Find the keyword in the files
    std::vector<std::string> marked_folders =
        FileOperations::findInFileNames(list_of_directories, keyword);
    FileOperations::printFileNames(marked_folders);
  } else if (nameOrContent == 3) {
    // Find in the content of the files from the directory
    FileOperations::findInFileContent(list_of_files, &keyword);
  } else if (nameOrContent == 4) {
    // Find in the content of the file
    std::string file;
    std::cout << "Enter the name of the file (with path): " << std::endl;
    std::getline(std::cin, file);
    FileOperations::readFileContent(&keyword, file);
  }
  return 0;
}
