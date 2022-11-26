#include <assert.h>

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#include "page.hpp"

class Story {
 public:
  std::vector<Page> pages;
  int numPages;
  // constructor
  Story() : pages(std::vector<Page>()), numPages(0){};
  //step1: read story.txt, set navigation, nextPage, type, num for each Page
  void readStory(std::ifstream & story, std::string directoryName) {
    std::string line;
    while (std::getline(story, line)) {
      // process blank lines
      if (line.size() == 0) {
        continue;
      }
      // process page declaration lines
      if (line.find("@") != std::string::npos) {
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
        for (size_t i = 0; (int)i < numPages; i++) {
          if (pages[i].num != i) {
            std::cerr << "Page declaration is not in order" << std::endl;
            exit(EXIT_FAILURE);
          }
        }
      }
      else {
        // process navigation lines
        char * end0;
        char * end1;
        long pagenum, pageref;
        pagenum = std::strtol(line.c_str(), &end0, 10);
        if (end0 == line.c_str() || end0[0] != ':') {
          std::cerr << "Invalid page number of reference" << std::endl;
          exit(EXIT_FAILURE);
        }
        if (pagenum >= numPages) {
          std::cerr << "Page has not been declaration" << std::endl;
          exit(EXIT_FAILURE);
        }
        end0++;
        pageref = std::strtol(end0, &end1, 10);
        if (end1[0] != ':') {
          std::cerr << "Page reference is not an invalid integer" << std::endl;
          exit(EXIT_FAILURE);
        }
        pages[pagenum].nextPage.push_back(pageref);
        end1++;
        pages[pagenum].navigation.push_back(end1);
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
  //step1: read a directory, build Story
  void buildStory(std::string directoryName) {
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
  //step1: print story
  void printStory() {
    for (int i = 0; i < numPages; i++) {
      pages[i].printPage();
    }
  }
  // step2.3: verify whether myStory confirms these conditions
  void checkValidity() {
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
        assert(it->nextPage[i] != it->num);
        pages[it->nextPage[i]].ref = true;
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
  void displayPages() {
    int curr = 0;
    while (true) {
      pages[curr].printPage();
      curr = navigateNextPage(curr);
    }
  }
  int navigateNextPage(int curr) {
    if (pages[curr].type != 0) {
      exit(EXIT_SUCCESS);
    }
    // check whether input number is valid
    std::vector<size_t> vec = pages[curr].nextPage;
    int input;
    std::cin >> input;
    while (!std::cin.good() || input == 0 || input > (int)pages[curr].nextPage.size()) {
      std::cin.clear();
      std::cin.ignore();
      std::cout << "That is not a valid choice, please try again\n";
    }
    return (int)pages[curr].nextPage[input - 1];
  }
};
