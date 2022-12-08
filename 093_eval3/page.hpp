#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Page {
 public:
  std::string name;
  size_t num;
  int type;  // NORMAL = 0, WIN = 1, LOSE = 2
  bool ref;
  std::vector<std::string> navigation;
  std::vector<size_t> nextPage;
  std::vector<std::string> contents;
  std::map<std::string, long int> variable;
  std::vector<std::pair<std::string, long int> > conditions;
  // constructor
  Page() :
      num(0),
      type(0),
      ref(false),
      navigation(std::vector<std::string>()),
      nextPage(std::vector<size_t>()),
      contents(std::vector<std::string>()) {}
  void readPageContent(std::string directoryName);
  void printPage(std::map<std::string, long int> variablePath,
                 std::vector<int> & unavilableIndex);
};
