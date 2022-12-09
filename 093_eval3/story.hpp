#include <cstring>
#include <vector>

#include "page.hpp"
/*
Story class represents a story composed of many pages. Pages vector stores many
pages. NumPages is the number of pages. VariablePath contains variable and value
pair declared by pages that being chosen by users.
*/
class Story {
 public:
  std::vector<Page> pages;
  int numPages;
  std::map<std::string, long int> variablePath;
  // constructor
  Story() : pages(std::vector<Page>()), numPages(0){};
  /*
    Helper function to process page declaration lines(eg.1@N:page.txt)
    It takes a line and directory name as inputs and puts a page with its name
    and contents into pages. 
   */
  void pageDelaration(std::string & line, std::string directoryName);
  /*
    Helper function to process variable declaration lines(eg.0$pastry=7)
    It takes a line as input and put page's variable and value pair in the field.
   */
  void pageVariable(std::string & line);
  /*
    Helper function to process two kinds of navigation lines(eg.0:1:sometext 
    0[pastry=7]:1:sometext). It takes a line as input and put conditions pairs,
    nextPage, navigation into the matching page object. 
   */
  void pageNavigation(std::string & line);
  /*
    Main function for step 1 and 4. It takes a ifstream and directory name as 
    inputs. It reads story.txt line by line, determines which type the line is,
    and calls different functions to process it. It also check if page declaration
    appears in order and check whether win and lose page have navigation lines. 
   */
  void readStory(std::ifstream & story, std::string directoryName);
  /*
    Function to build a story. It takes a directory name as input, reads story.txt
    inside the directory and build a story.
    */
  void buildStory(std::string directoryName);
  /*
    Function to print a story for step1. It prints all the pages in story in 
    order. 
   */
  void printStory();
  /*
    Function to check whether the story is valid for step 2. Every page that is 
    referenced by a choice must be valid; Every page (except page 0) is referenced
    by at least one *other* page's choices; At least one page must be a WIN page 
    or LOSE page.
   */
  void checkValidity();
  /*
    Function to display each page according to navigation lines that chosen by the
    users for step 2 and 4.
   */
  void displayPages();
  /*
    Function takes current page number and an unavailable index vector as inputs.
    It also takes an input from std::cin, check if the input is valid (if input 
    is in the unavailable index vector, it is invalid) and return the next page 
    number. 
   */
  int navigateNextPage(int curr, std::vector<int> & unavailableIndex);
  /*
    Function to find all possible paths to win for step3.
   */
  void backtrack();
  /*
    Helper function using backtracking method to find all possible paths to win 
    for step3. It takes path, index, flagwin, winpath as inputs. Path and index 
    store each possible path and its index in navigation vector. Flagwin is used
    to if this path can reach a win page. Winpath stores all the paths that can 
    reach a win page.   
   */
  void backtrackHelper(std::vector<Page> & path,
                       std::vector<int> & index,
                       int * flagwin,
                       std::vector<std::vector<Page> > & winpath);
  /*
    Function to print a path. It takes path, index, winpath as inputs. It checks 
    whether a path is already in winpath. If not, print the path.
   */
  void printPath(std::vector<std::vector<Page> > & winpath,
                 std::vector<Page> & path,
                 std::vector<int> & index);
};
