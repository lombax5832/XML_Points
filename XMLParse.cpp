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

vector<Point>& XMLParse::parse() {

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
        currentPos = currentLine.find(TAG_POINT, i);
        if (currentPos != currentLine.find('<', i)) {
          cout << "Invalid Tag Encountered" << endl;
          cout << currentPos << ' ' << currentLine.find('<', i) << endl;
          exit(1);
        }
        i = currentPos + TAG_POINT.length() - 1;
        if (currentPos != string::npos) {
          foundPoint = true;
          if (!verifyTag(TAG_POINT)) {
            cout << "Invalid Tag Encountered" << endl;
            exit(1);
          }
        } else {
          break;
        }
      } 
      
      else if (!foundX) {
        currentPos = currentLine.find(TAG_X, i);
        if (currentPos != currentLine.find('<', i)) {
          cout << "Invalid Tag Encountered" << endl;
          cout << currentPos << ' ' << currentLine.find('<', i) << endl;
          exit(1);
        }
        i = currentPos + TAG_X.length();
        if (currentPos != string::npos) {
          foundX = true;
          if (!verifyTag(TAG_X)) {
            cout << "Invalid Tag Encountered" << endl;
            exit(1);
          }
          strm << currentLine.substr(i, currentLine.find(TAG_X_CLOSE, i)-i);
          //verifyTag(TAG_X_CLOSE);
          strm >> x;
        } else {
          break;
        }
      } 

      else if (foundX && !foundXClose) {
        currentPos = currentLine.find(TAG_X_CLOSE, i);
        i = currentPos + TAG_X_CLOSE.length() - 1;
        if (currentPos != string::npos) {
          foundXClose = true;
          if (!verifyTag(TAG_X_CLOSE)) {
            cout << "Invalid Tag Encountered" << endl;
            cout << currentPos << ' ' << currentLine.find('<', i) << ' ' << i << endl;
            exit(1);
          }
        } else {
          break;
        }
      }
      
      else if (!foundY) {
        currentPos = currentLine.find(TAG_Y, i);
        if (currentPos != currentLine.find('<', i)) {
          cout << "Invalid Tag Encountered" << endl;
          cout << currentPos << ' ' << currentLine.find('<', i) << endl;
          exit(1);
        }
        i = currentPos + TAG_Y.length();
        if (currentPos != string::npos) {
          foundY = true;
          if (!verifyTag(TAG_Y)) {
            cout << "Invalid Tag Encountered" << endl;
            exit(1);
          }
          strm << currentLine.substr(i, currentLine.find(TAG_Y_CLOSE, i)-i);
          //verifyTag(TAG_Y_CLOSE);
          strm >> y;
        } else {
          break;
        }
      }

      else if (foundY && !foundYClose) {
        currentPos = currentLine.find(TAG_Y_CLOSE, i);
        i = currentPos + TAG_Y_CLOSE.length() - 1;
        if (currentPos != string::npos) {
          foundYClose = true;
          if (!verifyTag(TAG_Y_CLOSE)) {
            cout << "Invalid Tag Encountered" << endl;
            cout << currentPos << ' ' << currentLine.find('<', i) << ' ' << i << endl;
            exit(1);
          }
        } else {
          break;
        }
      }
      
      else if (foundYClose) {
        currentPos = currentLine.find(TAG_POINT_CLOSE, i);
        i = currentPos + TAG_POINT_CLOSE.length() - 1;
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
  for (size_t i = 0; i < pointList.size(); i++) {
    cout << "x = ";
    cout << setw(6) << pointList.at(i).getX() << ", ";
    cout << "y = ";
    cout << setw(6) << pointList.at(i).getY();
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
