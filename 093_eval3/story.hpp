#include <cstring>
#include <vector>

#include "page.hpp"
class Story {
 public:
  std::vector<Page> pages;
  int numPages;
  std::map<std::string, long int> variablePath;
  // constructor
  Story() : pages(std::vector<Page>()), numPages(0){};
  void pageDelaration(std::string & line, std::string directoryName);
  void pageVariable(std::string & line);
  void pageNavigation(std::string & line);
  void readStory(std::ifstream & story, std::string directoryName);
  void buildStory(std::string directoryName);
  void printStory();
  void checkValidity();
  void displayPages();
  int navigateNextPage(int curr, std::vector<int> & unavilableIndex);
  void backtrack();
  void backtrackHelper(std::vector<Page> & path, std::vector<int> & index, int * flagwin);
};
