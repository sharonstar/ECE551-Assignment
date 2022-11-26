#include <iostream>

#include "story.hpp"
int main(int argc, char * argv[]) {
  if (argc != 2) {
    std::cerr << "Wrong number of arguments" << std::endl;
    exit(EXIT_FAILURE);
  }
  char * direname = argv[1];
  Story storyObject;
  storyObject.buildStory(direname);
  storyObject.checkValidity();
  storyObject.displayPages();
  return EXIT_SUCCESS;
}
