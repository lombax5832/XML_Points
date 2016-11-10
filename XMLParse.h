#pragma once
using namespace std;
#include<string>
#include<vector>

struct Element {
  string name;
  string value;
  vector<Element> children;
};

class XMLParse {
public:
  XMLParse(string inputFile);

  Element parse();
private:
  string inputFile;
};