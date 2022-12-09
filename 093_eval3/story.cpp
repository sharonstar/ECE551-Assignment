#include "story.hpp"

#include <assert.h>

#include <algorithm>

// helper funtions for step1,2,4
// process page declaration lines
void Story::pageDelaration(std::string & line, std::string directoryName) {
  Page pageObject;
  char * end0;
  long numofPage;
  numofPage = std::strtol(line.c_str(), &end0, 10);
  if (end0[0] != '@' || end0 == line.c_str()) {
    std::cerr << "Invalid page number" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (numofPage < 0) {
    std::cerr << "Page number is negative" << std::endl;
    exit(EXIT_FAILURE);
  }
  pageObject.num = numofPage;
  if (end0[1] == 'N') {
    pageObject.type = 0;
  }
  else if (end0[1] == 'W') {
    pageObject.type = 1;
  }
  else if (end0[1] == 'L') {
    pageObject.type = 2;
  }
  else if (end0[1] != 'N' || end0[1] != 'W' || end0[1] != 'L') {
    std::cerr << "Invalid page type" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (end0[2] != ':') {
    std::cerr << "There is not : after page type " << std::endl;
    exit(EXIT_FAILURE);
  }
  end0 += 3;
  char * end1 = std::strchr(end0, '.');
  if (strcmp(end1, ".txt") != 0) {
    std::cerr << "Invalid pagefile name" << std::endl;
    exit(EXIT_FAILURE);
  }
  pageObject.name = end0;
  pageObject.readPageContent(directoryName);
  pages.push_back(pageObject);
  numPages++;
}
// process variable declaration lines
void Story::pageVariable(std::string & line) {
  char * end0;
  char * end1;
  long pagenum, value;
  pagenum = std::strtol(line.c_str(), &end0, 10);
  if (pagenum >= numPages) {
    std::cerr << "Page has not been declaration" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string::size_type pos1 = line.find('$') + 1;
  std::string::size_type pos2 = line.find('=');
  if (pos2 == std::string::npos) {
    std::cerr << "Invalid variable declaration(doesn't have =)" << std::endl;
    exit(EXIT_FAILURE);
  }
  value = std::strtol(line.substr(pos2 + 1).c_str(), &end1, 10);
  if (end1 == line.substr(pos2 + 1).c_str() || end1[0] != '\0') {
    std::cerr << "Invalid variable value" << std::endl;
    exit(EXIT_FAILURE);
  }
  pages[pagenum].variable[line.substr(pos1, pos2 - pos1)] = value;
}
// process navigation lines
void Story::pageNavigation(std::string & line) {
  char * end0;
  char * end1;
  char * end2;
  char * end3;
  long pagenum, pageref, value;
  pagenum = std::strtol(line.c_str(), &end0, 10);
  if (pagenum >= numPages) {
    std::cerr << "Page has not been declaration" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (end0[0] == '[') {
    std::string::size_type pos1 = std::string(end0).find('=');
    if (pos1 == std::string::npos) {
      std::cerr << "Invalid condition(doesn't have =)" << std::endl;
      exit(EXIT_FAILURE);
    }
    value = std::strtol(end0 + pos1 + 1, &end2, 10);
    if (end2 == std::string(end0).substr(pos1 + 1).c_str() || end2[0] != ']') {
      std::cerr << "Invalid condition(variable's value is invalid)" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::pair<std::string, long int> conPair(std::string(end0).substr(1, pos1 - 1),
                                             value);
    pages[pagenum].conditions.push_back(conPair);
    end3 = end2 + 2;
  }
  else {
    pages[pagenum].conditions.push_back(std::pair<std::string, long int>());
    end3 = end0 + 1;
  }
  pageref = std::strtol(end3, &end1, 10);
  if (end1[0] != ':') {
    std::cerr << "Page reference is not an invalid integer" << std::endl;
    exit(EXIT_FAILURE);
  }
  pages[pagenum].nextPage.push_back(pageref);
  end1++;
  pages[pagenum].navigation.push_back(end1);
}

// step1: read story.txt, set navigation, nextPage, type, num for each Page
void Story::readStory(std::ifstream & story, std::string directoryName) {
  std::string line;
  while (std::getline(story, line)) {
    // process blank lines
    if (line.size() == 0) {
      continue;
    }
    // check which type the line is
    char * end;
    std::strtol(line.c_str(), &end, 10);
    if (end == line.c_str()) {
      std::cerr << "The first one is not a number" << std::endl;
      exit(EXIT_FAILURE);
    }
    if (end[0] == '@') {  // process page declaration lines
      pageDelaration(line, directoryName);
      // check if page declaration appears in order
      for (size_t i = 0; (int)i < numPages; i++) {
        if (pages[i].num != i) {
          std::cerr << "Page declaration is not in order" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
    }
    else if (end[0] == ':' || end[0] == '[') {  // process navigation lines
      pageNavigation(line);
    }
    else if (end[0] == '$') {  // process variable declaration lines
      pageVariable(line);
    }
    else {
      std::cerr << "Lines don't belong to any type" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  // check win and lose page should not have navigation lines
  std::vector<Page>::iterator it = pages.begin();
  while (it != pages.end()) {
    if (it->type != 0) {
      if (!it->nextPage.empty()) {
        std::cerr << "WIN and LOSE pages have navigation lines" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    it++;
  }
}
// step1: read a directory, build Story
void Story::buildStory(std::string directoryName) {
  std::string story = directoryName + "/story.txt";
  std::ifstream inputFile;
  inputFile.open(story.c_str(), std::ifstream::in);
  if (inputFile.is_open()) {
    readStory(inputFile, directoryName);
    inputFile.close();
  }
  else {
    std::cerr << "Can't open file: story.txt" << std::endl;
    exit(EXIT_FAILURE);
  }
}
// step1: print story
void Story::printStory() {
  std::vector<int> unavilableIndex;
  for (int i = 0; i < numPages; i++) {
    std::cout << "Page " << pages[i].num << std::endl;
    std::cout << "==========" << std::endl;
    pages[i].printPage(variablePath, unavilableIndex);
  }
}
// step2.3: verify whether myStory confirms these conditions
void Story::checkValidity() {
  std::vector<Page>::iterator it = pages.begin();
  int numWin = 0;
  int numLose = 0;
  while (it != pages.end()) {
    // 3a. Every page that is referenced by a choice is valid
    for (int i = 0; i < (int)it->nextPage.size(); i++) {
      if ((int)it->nextPage[i] >= numPages) {
        std::cerr << "Page that is referenced by a choice is invalid" << std::endl;
        exit(EXIT_FAILURE);
      }
      if (it->nextPage[i] != it->num) {
        pages[it->nextPage[i]].ref = true;
      }
    }
    // 3b. Every page (except page 0) is referenced by at least one *other* page's choices
    if (it->ref == false && it->num != 0) {
      std::cerr << "A page has not been referenced by others" << std::endl;
      exit(EXIT_FAILURE);
    }
    // 3c. At least one page must be a WIN page/LOSE page
    if (it->type == 1) {
      numWin++;
    }
    else if (it->type == 2) {
      numLose++;
    }
    it++;
  }
  assert(numWin != 0 && numLose != 0);
}
// step2.4: display each page according to navigation lines
void Story::displayPages() {
  int curr = 0;
  std::vector<int> unavailableIndex;
  while (true) {
    if (pages[curr].variable.size() != 0) {
      std::map<std::string, long int>::iterator it = pages[curr].variable.begin();
      while (it != pages[curr].variable.end()) {
        variablePath[it->first] = it->second;
        it++;
      }
    }
    pages[curr].printPage(variablePath, unavailableIndex);
    curr = navigateNextPage(curr, unavailableIndex);
    if (curr == -1) {
      return;
    }
  }
}
int Story::navigateNextPage(int curr, std::vector<int> & unavailableIndex) {
  if (pages[curr].type != 0) {
    return -1;
  }
  // check whether input number is valid
  int input;
  std::cin >> input;
  while (!std::cin.good() || input < 1 || input > (int)pages[curr].nextPage.size() ||
         std::count(unavailableIndex.begin(), unavailableIndex.end(), input) > 0) {
    if (!std::cin.good()) {
      std::cin.clear();
      std::string badinput;
      std::cin >> badinput;
    }
    // check whether input is in unavailableIndex
    if (std::count(unavailableIndex.begin(), unavailableIndex.end(), input) > 0) {
      std::cout << "That choice is not available at this time, please try again"
                << std::endl;
    }
    else {
      std::cout << "That is not a valid choice, please try again" << std::endl;
    }
    std::cin >> input;
  }
  return (int)pages[curr].nextPage[(int)input - 1];
}
// step3: find all possible paths to win
void Story::backtrack() {
  std::vector<Page> path;
  std::vector<int> index;
  // check whether print win path repetitively
  std::vector<std::vector<Page> > winpath;
  int flagwin = 0;
  path.push_back(pages[0]);
  backtrackHelper(path, index, &flagwin, winpath);
  if (flagwin == 0) {
    std::cout << "This story is unwinnable!" << std::endl;
  }
}
// backtracking helper function
void Story::backtrackHelper(std::vector<Page> & path,
                            std::vector<int> & index,
                            int * flagwin,
                            std::vector<std::vector<Page> > & winpath) {
  if (path.back().type == 1) {
    // set flag when reach a win page
    *flagwin = 1;
    printPath(winpath, path, index);
    winpath.push_back(path);
  }
  else {
    for (int i = 0; i < (int)path.back().nextPage.size(); i++) {
      // check whether there are repetitive pages in path
      int flag = 0;
      for (int j = 0; j < (int)path.size(); j++) {
        if (path[j].num == path.back().nextPage[i]) {
          flag = 1;
          break;
        }
      }
      if (flag == 1) {
        continue;
      }
      path.push_back(pages[(int)path.back().nextPage[i]]);
      index.push_back(i);
      backtrackHelper(path, index, flagwin, winpath);
      path.pop_back();
      index.pop_back();
    }
  }
}
// Function to print a path
void Story::printPath(std::vector<std::vector<Page> > & winpath,
                      std::vector<Page> & path,
                      std::vector<int> & index) {
  if (winpath.size() == 0) {
    for (int i = 0; i < (int)path.size() - 1; i++) {
      std::cout << path[i].num << "(" << index[i] + 1 << "),";
    }
    std::cout << path.back().num << "(win)" << std::endl;
  }
  // check whether a path is already in winpath
  for (int i = 0; i < (int)winpath.size(); i++) {
    if (winpath[i] == path) {
      break;
    }
    else {
      for (int i = 0; i < (int)path.size() - 1; i++) {
        std::cout << path[i].num << "(" << index[i] + 1 << "),";
      }
      std::cout << path.back().num << "(win)" << std::endl;
      return;
    }
  }
}
