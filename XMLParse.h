#pragma once
using namespace std;
#include<string>
#include<list>
#include<stack>

#include"Point.h"

// Constants
// XML Tags we will see
const string TAG_POINT       = "<point>";
const string TAG_POINT_CLOSE = "</point>";
const string TAG_X           = "<x>";
const string TAG_X_CLOSE     = "</x>";
const string TAG_Y           = "<y>";
const string TAG_Y_CLOSE     = "</y>";

class XMLParse {
public:
  /*
    Purpose: Constructor/Default Constructor for the class XMLParse
    Pre: String to store file names/locations in the class
    Post: Creates an XMLParse object to get list of points from a file
    Parameters:
      &input   = input file name/location
  */
  XMLParse(const string inputFile = "inp.txt");

  /*
    Purpose: Parses the XML file and returns the list of points
    Pre: XML file is formatted correctly
    Post: pointList is populated and returned
  */
  list<Point>& parse();

  /*
    Purpose: Sets the inputFile variable
    Pre: 
    Post: inputFile variable is set
    Parameters:
      &fileName   = input file name/location
  */
  void setInputFile(const string fileName);

  /*
    Purpose: Returns the inputFile variable
    Pre: Properly constructed XMLParse object
    Post: inputFile variable is returned
  */
  string getInputFile() const;

private:
  //Where the inputFile is found
  string inputFile;
  //List of points
  list<Point> pointList;
  //Stack used to verify the XML file is formatted properly
  stack<string> verificationStack;

  /*
    Purpose: Converts all alphabetical characters in a string to lowercase
    Pre: Valid string is passed
    Post: input is changed to have all alphabetical characters as lowercase
  */
  void stringToLower(string& input) const;

  /*
    Purpose: Helper function for parse() used to find the next tag
    Pre: Used in a loop to make sure the next tag is what we expect
    Post: currentPos and i are modified during this function's execution
            PROGRAM WILL BE TERMINATED IF UNEXPECTED TAG IS FOUND
    Parameters:
      &currentPos   = can only be location of a tag/value
      &i            = which character we are looking at
      &currentLine  = line that is being checked
      &tagToFind    = tag we are expected to see
  */
  bool findTag(size_t& currentPos, size_t& i, const string& currentLine, const string& tagToFind);

  /*
    Purpose: Verifies that an identifier's name is valid
    Post: returns true if inputted identifier is valid, false otherwise
    Parameters:
      &input = identifier to check for validity
  */
  bool verifyIdentifier(const string input) const;

  /*
    Purpose: Verifies that the structure of the XML file is valid
    Post: returns true if inputted tag is expected, false otherwise
    Parameters:
      &input = tag to check for validity
  */
  bool verifyTag(const string input);

  /*
    Purpose: Returns the name of the inputted tag
    Post: returns the tag without the brackets
    Parameters:
      &input = tag to remove brackets from
  */
  string getTagName(const string input) const;

  /*
    Purpose: Says whether a tag is an opening tag or not(has </ or just <)
    Post: returns true if tag is opening tag, false if closing tag
    Parameters:
      &input = tag check for opening
  */
  bool isOpenTag(const string input) const;

  /*
    Purpose: Adds given point to pointList
    Pre: Given point is valid and properly constructed
    Post: point is added to pointList
    Parameters:
      &point = Point to add to pointList
  */
  void addPointToList(Point& point);
};