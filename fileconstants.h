#define CURRENT_DIR "."
#define HOME_DIR "/home/tanmey-kumar"

enum SearchType { SEARCH_NONE = 0, SEARCH_LOCAL, SEARCH_RECURSIVE };

enum CaseSensitive { CASE_NONE = 0, CASE_SENSE, CASE_INSENCE };

struct FileSettings {
  std::string m_dir;
  SearchType m_searchType;
  CaseSensitive m_caseType;
};
