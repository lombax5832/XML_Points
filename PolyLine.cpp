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

void PolyLine::insert(int pos, Point toInsert) {
  list<Point>::const_iterator it = pntList.begin();
  for (int i = 0; it != pntList.end(); it++, i++) {
    if (i == pos) {
      pntList.insert(it, toInsert);
    }
  }
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
  toOStream(cout);
}

void PolyLine::store() const {
  ofstream strm(outputFile);
  toOStream(strm);
}

void PolyLine::toOStream(ostream & ostrm) const {
  int i = 0;
  for (list<Point>::const_iterator it = pntList.begin(); it != pntList.end(); it++, i++) {
    ostrm << i << "| " << "x = ";
    ostrm << setw(6) << it->getX() << ", ";
    ostrm << "y = ";
    ostrm << setw(6) << it->getY();
    ostrm << endl;
  }
}
