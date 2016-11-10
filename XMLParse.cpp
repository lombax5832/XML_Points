#include "XMLParse.h"

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>

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
  size_t openBracketPos = string::npos;
  size_t closeBracketPos = string::npos;
  bool foundPoint = false;
  bool foundX = false;
  bool foundY = false;
  double x = 0.0;
  double y = 0.0;
  string currentLine = "";
  string subString = "";
  stringstream sstrm;
  Point tempPoint;
  
  getline(input, currentLine);
  while (!input.eof()) {
    for (size_t i = 0; i < currentLine.length(); i++) {
      if (currentLine[i] == '<') {
        openBracketPos = i;
        for (; i < currentLine.length(); i++) {
          if (currentLine[i] == '>') {
            closeBracketPos = i;
            break;
          }
        }
        subString = "";// currentLine.substr(openBracketPos + 1, closeBracketPos - openBracketPos - 1);
        cout << subString << endl;
        openBracketPos = string::npos;
        closeBracketPos = string::npos;

        if (!verifyTag(subString)) {
         // exit(1);
        }

        if (subString == TAG_POINT) {
          foundPoint = true;
        }
      }
      else if ((currentLine[i] == '-') || ((currentLine[i] >= '0') && (currentLine[i] <= '9'))) {
        openBracketPos = i;
        for (; i < currentLine.length(); i++) {
          if (currentLine[i] == '<' || currentLine[i] == ' ') {
            closeBracketPos = i;
            cout << openBracketPos << ' ' << closeBracketPos << endl;
            break;
          }
        }
        subString = currentLine.substr(openBracketPos, closeBracketPos - openBracketPos);
        openBracketPos = string::npos;
        closeBracketPos = string::npos;

        sstrm << subString;
        cout << subString << endl;
        if (!foundX) {
          sstrm >> x;
          foundX = true;
        } else if (!foundY) {
          sstrm >> y;
          tempPoint.setX(x);
          tempPoint.setY(y);
          pointList.push_back(tempPoint);
          x = 0.0;
          y = 0.0;
          foundPoint = false;
          foundX = false;
          foundY = false;
        }
      }
    }
    getline(input, currentLine);
    openBracketPos = string::npos;
    closeBracketPos = string::npos;
  }
}

void XMLParse::setInputFile(const string fileName) {
  inputFile = fileName;
}

string XMLParse::getInputFile() const {
  return inputFile;
}

void XMLParse::tabulate() const {
  Point p;
  for (size_t i = 0; i < pointList.size(); i++) {
    p = pointList.at(0);
    cout << "x = ";
    cout << setw(6) << p.getX() << ", ";
    cout << "y = ";
    cout << setw(6) << p.getY() << ", ";
    cout << endl;
  }
}

bool XMLParse::verifyIdentifier(const string input) const {
  for (size_t i = 0; i < input.length(); i++) {
    if (!((input[i] >= 'A' && input[i] <= 'Z') || 
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
  if (!isOpenTag(input)) {
    input = input.substr(1);
    if (verificationStack.top() == input) {
      verificationStack.pop();
      return true;
    }
    return false;
  }
  else {
    if (verifyIdentifier(input)) {
      verificationStack.push(input);
      return true;
    }
    return false;
  }
}

bool XMLParse::isOpenTag(const string input) const {
  return input[0] != '/';
}
