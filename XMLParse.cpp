#include "XMLParse.h"

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
#include<cassert>

XMLParse::XMLParse(const string inputFile) {
  setInputFile(inputFile);
}

void XMLParse::parse() {

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
  bool foundY = false;
  double x = 0.0;
  double y = 0.0;
  stringstream strm;

  getline(input, currentLine);
  while (!input.eof()) {
    for (size_t i = 0; i < currentLine.length(); i++) {

      if (!foundPoint) {
        currentPos = currentLine.find(TAG_POINT, i);
        i = currentPos + TAG_POINT.length() - 1;
        if (currentPos != string::npos) {
          foundPoint = true;
          if(verifyTag(TAG_POINT))
            cout << "Got point." << endl;
        } else {
          break;
        }
      } 
      
      else if (!foundX) {
        currentPos = currentLine.find(TAG_X, i);
        i = currentPos + TAG_X.length();
        if (currentPos != string::npos) {
          foundX = true;
          if (verifyTag(TAG_X)) {
            cout << "Got X." << endl;
          }
          strm << currentLine.substr(i, currentLine.find(TAG_X_CLOSE, i)-i);
          verifyTag(TAG_X_CLOSE);
          strm >> x;
          cout << x << endl;
        } else {
          break;
        }
      } 
      
      else if (!foundY) {
        currentPos = currentLine.find(TAG_Y, i);
        i = currentPos + TAG_Y.length();
       // cout << currentPos << ' ' << i << endl;
        if (currentPos != string::npos) {
          foundY = true;
          if (verifyTag(TAG_Y)) {
            cout << "Got Y." << endl;
          }
          strm << currentLine.substr(i, currentLine.find(TAG_Y_CLOSE, i)-i);
          verifyTag(TAG_Y_CLOSE);
          strm >> y;
          cout << y << endl;
        } else {
          break;
        }
      }
      
      else if (foundY) {
        currentPos = currentLine.find(TAG_POINT_CLOSE, i);
        i = currentPos + TAG_POINT_CLOSE.length() - 1;
        if (currentPos != string::npos) {
          //foundPoint = true;
          if (verifyTag(TAG_POINT_CLOSE)) {
            cout << "Got point close." << endl;
            addPointToList(x,y);
            foundPoint = false;
            foundX = false;
            foundY = false;
            x = 0.0;
            y = 0.0;
          }
        } else {
          break;
        }
      }
    }
    getline(input, currentLine);
  }
}

void XMLParse::setInputFile(const string fileName) {
  inputFile = fileName;
}

string XMLParse::getInputFile() const {
  return inputFile;
}

void XMLParse::tabulate() const {
  for (size_t i = 0; i < pointList.size(); i++) {
    cout << "x = ";
    cout << setw(6) << pointList.at(i).getX() << ", ";
    cout << "y = ";
    cout << setw(6) << pointList.at(i).getY() << ", ";
    cout << endl;
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
    return true;
  } else {
    if (!verificationStack.empty() && verificationStack.top() == getTagName(input)) {
      verificationStack.pop();
      if (!verificationStack.empty()) {
       // cout << verificationStack.top() << " on stack" << endl;
      }
      else
        cout << "stack empty" << endl;
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
