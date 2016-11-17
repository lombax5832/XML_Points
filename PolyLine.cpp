#include "PolyLine.h"

#include "XMLParse.h"
#include<iostream>
#include<iomanip>
#include<fstream>

PolyLine::PolyLine(string inputFile, string outFile) {
  outputFile = outFile;
  XMLParse parser(inputFile);
  pntList = parser.parse();
}

double PolyLine::length() const {
  typedef list<Point>::const_iterator Element;
  double currentLength = 0;
  Element it = pntList.begin();
  Element lastPoint = pntList.begin();
  for (Element it = pntList.begin(); it != pntList.end(); it++) {
    if (!(lastPoint == it)) {
      currentLength += it->distanceTo(*lastPoint);
    }
    lastPoint = it;
  }
  return currentLength;
}

int PolyLine::size() const {
  return pntList.size();
}

void PolyLine::insert(const Point& toInsert, const Point& insAfter) {
  for (list<Point>::const_iterator it = pntList.begin(); it != pntList.end(); ++it) {
    if (*it==insAfter) {
      pntList.insert(++it, toInsert);
      break;
    }
  }
}

void PolyLine::insert(const Point& toInsert) {
  pntList.push_back(toInsert);
}

void PolyLine::remove(int pos) {
  list<Point>::const_iterator it = pntList.begin();
  for (int i = 0; it != pntList.end(); it++, i++) {
    if (i == pos) {
      pntList.erase(it);
      break;
    }
  }
}

void PolyLine::show() const {
  int i = 0;
  for (list<Point>::const_iterator it = pntList.begin(); it != pntList.end(); it++, i++) {
    cout << i << "| " << "x = ";
    cout << setw(6) << it->getX() << ", ";
    cout << "y = ";
    cout << setw(6) << it->getY();
    cout << endl;
  }
}

void PolyLine::store() const {
  ofstream strm(outputFile);
  for (list<Point>::const_iterator it = pntList.begin(); it != pntList.end(); it++) {
    strm << "<Point> <x> " << setw(3) << it->getX() << " </x>";
    strm << " <y> " << setw(3) << it->getY() << " </y> </Point>\n";
  }
}
