#include "XMLParse.h"

#include<iostream>
#include<fstream>
#include<string>

XMLParse::XMLParse(const string inputFile) {
  setInputFile(inputFile);
}

Element& XMLParse::parse() {
  Element body;
  Element* elementParent = &body;
  Element* currentElement;

  ifstream input(inputFile);

  // Prints an error if the file could not be opened for input
  if (!input) {
    cout << "Could not open file " << inputFile << " for input" << endl;
    exit(1);
  }

  // Temporary storage for loop
  size_t openBracketPos = string::npos;
  size_t closeBracketPos = string::npos;
  size_t currentPos = 0;
  string currentLine = "";
  string subString = "";
  
  getline(input, currentLine);
  while (!input.eof()) {
    for (int i = 0; i < currentLine.length(); i++) {

      if (openBracketPos == string::npos) {
        if (currentLine[i] == '<') {

          openBracketPos = i;
          for (; i < currentLine.length(); i++) {
            if (currentLine[i] == '>') {
              closeBracketPos = i;
              break;
            }
          }
        } else if (currentLine[i] != ' ') {

        }
      }

      if ((openBracketPos != string::npos) && (closeBracketPos != string::npos)) {
        subString = currentLine.substr(openBracketPos + 1, closeBracketPos - openBracketPos - 1);
        if (!verifyTag(subString)) {
          cout << "Tag name: " << subString << " is an invalid identifier." << endl;
          exit(1);
        }
        if (isOpenTag(subString)) {
          currentElement = new Element(subString);
          elementParent->addChild(currentElement);
        }
      }
    }
    getline(input, currentLine);
    openBracketPos = string::npos;
    closeBracketPos = string::npos;
  }

  return body;
}

void XMLParse::setInputFile(const string fileName) {
  inputFile = fileName;
}

string XMLParse::getInputFile() const {
  return inputFile;
}

bool XMLParse::verifyIdentifier(const string input) const {
  for (int i = 0; i < input.length(); i++) {
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
  if (input[0] = '/') {
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
