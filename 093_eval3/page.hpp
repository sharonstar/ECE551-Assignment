#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
/*
This class represent a page of the story. The navigation vector stores different
choice sentences for next pages. The nextPage vector stores next pages that this
page can go to. The contents vector reads and stores the content of the page. 
The variable map store the variables that the page declares that its value. The  
conditions vector stores variable and value pair read in the navigation lines.
*/
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

  /*
   This funtion overrides operator == in Page class. It is determined by num.
   */
  friend bool operator==(const Page & lhs, const Page & rhs);

  /*
   This funtion takes the directory name as the input, reads pagename.txt line 
   by line and stores each line into the contents field.
   */
  void readPageContent(std::string directoryName);

  /*
   This funtion takes variablePath that contains all the variables and 
   unavilableIndex as arguments. It prints page contents, and prints navigation
   lines or <UNAVAILABLE> based on whether condition matchs with variable and 
   value.
   */
  void printPage(std::map<std::string, long int> variablePath,
                 std::vector<int> & unavailableIndex);
};
