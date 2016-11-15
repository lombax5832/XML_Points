#include "XMLParse.h"

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>

XMLParse::XMLParse(const string inputFile) {
  setInputFile(inputFile);
}

list<Point>& XMLParse::parse() {

  ifstream input(inputFile);

  // Prints an error if the file could not be opened for input
  if (!input) {
    cout << "Could not open file " << inputFile << " for input" << endl;
    exit(1);
  }

  // Temporary storage for loop
  string currentLine = "";
  size_t currentPos = 0;
  bool foundPoint = false;
  bool foundX = false;
  bool foundXClose = false;
  bool foundY = false;
  bool foundYClose = false;
  double x = 0.0;
  double y = 0.0;
  stringstream strm;
  
  while (!input.eof()) {
    getline(input, currentLine);
    for (size_t i = 0; i < currentLine.length(); i++) {
      //cout << i << endl;

      if (!foundPoint) {
        if (findTag(currentPos, i, currentLine, TAG_POINT)) {
          foundPoint = true;
        }
      } 
      
      else if (!foundX) {
        if (findTag(currentPos, i, currentLine, TAG_X)) {
          foundX = true;
          strm << currentLine.substr(i, currentLine.find(TAG_X_CLOSE, i) - i);
          strm >> x;
        }
      } 

      else if (foundX && !foundXClose) {
        if (findTag(currentPos, i, currentLine, TAG_X_CLOSE)) {
          foundXClose = true;
        }
      }
      
      else if (!foundY) {
        if (findTag(currentPos, i, currentLine, TAG_Y)) {
          foundY = true;
          strm << currentLine.substr(i, currentLine.find(TAG_Y_CLOSE, i) - i);
          strm >> y;
        }
      }

      else if (foundY && !foundYClose) {
        if (findTag(currentPos, i, currentLine, TAG_Y_CLOSE)) {
          foundYClose = true;
        }
      }
      
      else if (foundYClose) {
        currentPos = currentLine.find(TAG_POINT_CLOSE, i);
        i = currentPos + TAG_POINT_CLOSE.length();
        if (currentPos != string::npos) {
          if (verifyTag(TAG_POINT_CLOSE)) {
            addPointToList(x,y);
            foundPoint = false;
            foundX = false;
            foundXClose = false;
            foundY = false;
            foundYClose = false;
            x = 0.0;
            y = 0.0;
          }
        } else {
          break;
        }
      }
    }
  }
  return pointList;
}

void XMLParse::setInputFile(const string fileName) {
  inputFile = fileName;
}

string XMLParse::getInputFile() const {
  return inputFile;
}

void XMLParse::tabulate() const {
  typedef list<Point> PointList;
  for (PointList::const_iterator it = pointList.begin(); it != pointList.end(); ++it) {
    cout << "x = ";
    cout << setw(6) << it->getX() << ", ";
    cout << "y = ";
    cout << setw(6) << it->getY();
    cout << endl;
  }
}

bool XMLParse::findTag(size_t& currentPos, size_t& i, string& currentLine, const string& tagToFind) {
  currentPos = currentLine.find(tagToFind, i);
  if (currentPos != currentLine.find('<', i)) {
    cout << "Invalid Tag Encountered" << endl;
    cout << currentPos << ' ' << currentLine.find('<', i) << endl;
    exit(1);
  }
  i = currentPos + tagToFind.length();
  if (currentPos != string::npos) {
    if (!verifyTag(tagToFind)) {
      cout << "Invalid Tag Encountered" << endl;
      exit(1);
    }

    return true;
  } else {
    return false;
  }
}

bool XMLParse::verifyIdentifier(const string input) const {
  for (size_t i = 0; i < input.length(); i++) {
    if (((input[i] >= 'A' && input[i] <= 'Z') ||
      (input[i] >= 'a' && input[i] <= 'z') ||
      (input[i] == '_'))) {
      continue;
    }
    if ((i != 0) && (input[i] >= '0' && input[i] <= '9')) {
      continue;
    }
    return false;
  }
  return true;
}

bool XMLParse::verifyTag(string input) {
  if (isOpenTag(input)) {
    if (!verifyIdentifier(getTagName(input))) {
      return false;
    }
    verificationStack.push(getTagName(input));
    //cout << verificationStack.top() << " on stack" << endl;
    //cout << verificationStack.size() << " on stack" << endl;
    return true;
  } else {
    if (!verificationStack.empty() && (verificationStack.top() == getTagName(input))) {
      verificationStack.pop();
      if (!verificationStack.empty()) {
        //cout << verificationStack.top() << " on stack" << endl;
        //cout << verificationStack.size() << " on stack" << endl;
      }
      return true;
    }
    return false;
  }
}

string XMLParse::getTagName(const string input) const {
  if (isOpenTag(input)) {
    return input.substr(1, input.length() - 2);
  }
  return input.substr(2, input.length() - 3);
}

bool XMLParse::isOpenTag(const string input) const {
  return input.substr(0, 2) != "</";
}

void XMLParse::addPointToList(double x, double y) {
  Point toAdd(x, y);
  pointList.push_back(toAdd);
}
