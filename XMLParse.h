#pragma once
using namespace std;
#include<string>
#include<vector>
#include<stack>

#include"Point.h"

// Constants
// XML Tags we will see
const string TAG_POINT = "Point";
const string TAG_X     = "x";
const string TAG_Y     = "y";

class XMLParse {
public:
  XMLParse(const string inputFile = "input.txt");

  void parse();

  void setInputFile(const string fileName);

  string getInputFile() const;

  void tabulate() const;

private:
  string inputFile;
  vector<Point> pointList;
  stack<string> verificationStack;

  bool verifyIdentifier(const string input) const;

  bool verifyTag(string input);

  bool isOpenTag(const string input) const;
};