#pragma once
using namespace std;
#include<string>
#include<list>
#include<stack>

class Element {
public:
  Element(const string name="BODY", const string value="");
  ~Element();

  void addChild(Element* toAdd);
  void setValue(const string value);

  Element* getParent() const;
  bool hasChildren() const;
  string getValue() const;

private:
  Element* parent;
  string name;
  string value;
  list<Element*> children;

  void setParent(Element* parent);
};