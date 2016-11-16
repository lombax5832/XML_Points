#pragma once
using namespace std;
#include"Point.h"

#include<list>
#include<string>
#include<ostream>

class PolyLine {
public:
  PolyLine(string inputFile = "", string outputFile = "outp.txt");
  
  double length() const;
  int size() const;

  void insert(int pos, Point toInsert);
  void remove(int pos);

  void show() const;
  void store() const;

private:
  list<Point> pntList;
  string outputFile;

  void toOStream(ostream& ostrm) const;
};