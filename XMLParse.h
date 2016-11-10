#pragma once
using namespace std;
#include<string>
#include<vector>
#include<stack>

#include"Element.h"

class XMLParse {
public:
  XMLParse(const string inputFile);

  Element& parse();

  void setInputFile(const string fileName);

  string getInputFile() const;


private:
  string inputFile;
  stack<string> verificationStack;

  bool verifyIdentifier(const string input) const;

  bool verifyTag(string input);

  bool isOpenTag(const string input) const;
};