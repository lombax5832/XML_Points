#include "Element.h"

Element::Element(const string initName, const string initValue) {
  parent = nullptr;
  name = initName;
  value = initValue;
}

Element::~Element() {
  while (!children.empty()) {
    delete children.front();
    children.pop_front();
  }
}

void Element::addChild(Element* toAdd) {
  toAdd->setParent(this);
  children.push_back(toAdd);
}

void Element::setValue(const string newValue) {
  value = newValue;
}

Element * Element::getParent() const {
  return parent;
}

bool Element::hasChildren() const {
  return !children.empty();
}

string Element::getValue() const {
  return value;
}

void Element::setParent(Element* newParent) {
  parent = newParent;
}
