#include "page.hpp"
bool operator==(const Page & lhs, const Page & rhs) {
  return lhs.num == rhs.num;
}
void Page::readPageContent(std::string directoryName) {
  std::string path = directoryName + "/" + name;
  std::ifstream inputFile;
  inputFile.open(path.c_str());
  if (inputFile.fail()) {
    std::cerr << "Can't open file: " << name << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string line;
  while (!inputFile.eof()) {
    std::getline(inputFile, line);
    contents.push_back(line);
  }
}
void Page::printPage(std::map<std::string, long int> variablePath,
                     std::vector<int> & unavailableIndex) {
  std::vector<std::string>::const_iterator it = contents.begin();
  unavailableIndex.clear();
  while (it != contents.end()) {
    std::cout << *it << std::endl;
    it++;
  }
  // normal type page: print navigation lines
  if (type == 0) {
    std::cout << "What would you like to do?" << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < (int)navigation.size(); i++) {
      std::map<std::string, long int>::iterator it =
          variablePath.find(conditions[i].first);
      if (conditions[i].first == "" ||
          (it != variablePath.end() && it->second == conditions[i].second) ||
          (it == variablePath.end() && conditions[i].second == 0)) {
        std::cout << " " << i + 1 << ". " << navigation[i] << std::endl;
      }
      else {
        std::cout << " " << i + 1 << ". "
                  << "<UNAVAILABLE>" << std::endl;
        unavailableIndex.push_back(i + 1);
      }
    }
  }
  else if (type == 1) {
    std::cout << "Congratulations! You have won. Hooray!" << std::endl;
  }
  else {
    std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
  }
}
