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
  // read story.txt, set navigation, nextPage, type, num for each Page
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
        else if (end0[1] != 'N' || end0[1] != 'W' || end0[1] != 'L' || end0[2] != ':') {
          std::cerr << "Invalid page type" << std::endl;
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
        for (int i = 0; i < numPages; i++) {
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
        ///////checkValid()   page reference
        pages[pagenum].nextPage.push_back(pageref);
        end1++;
        pages[pagenum].navigation.push_back(end1);
      }
    }
  }
  // read a directory, build Story
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
  // print story
  void printStory() {
    for (int i = 0; i < numPages; i++) {
      pages[i].printPage();
    }
  }
};