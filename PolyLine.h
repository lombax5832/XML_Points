#pragma once
using namespace std;
#include"Point.h"

#include<list>
#include<string>

class PolyLine {
public:
  /*
    Purpose: Constructor/Default Constructor for the class PolyLine
    Pre: Two strings to store file names/locations in the class
    Post: Creates an XMLParse object to get an initial list of points
    Parameters:
      &input   = input file name/location
      &output  = input file name/location
  */
  PolyLine(string inputFile = "", string outputFile = "outp.txt");
  
  /*
    Purpose: Adds distance between each point in order
    Pre: A properly constructed PolyLine object
    Post: Returns the distance between each point and the point after it
  */
  double length() const;

  /*
    Purpose: Counts the number of points
    Pre: A properly constructed PolyLine object
    Post: Returns the nubmer of points
  */
  int size() const;

  /*
    Purpose: Inserts a point after a given point
    Pre: A properly constructed PolyLine object
    Post: pntList has new point inserted in it
    Parameters:
      &toInsert   = point to insert
      &insAfter   = point to insert new point after
  */
  void insert(const Point& toInsert, const Point& insAfter);

  /*
    Purpose: Inserts a point at the end of the list
    Pre: A properly constructed PolyLine object
    Post: pntList has new point inserted in it
    Parameters:
      &toInsert   = point to insert
  */
  void PolyLine::insert(const Point& toInsert);

  /*
    Purpose: Removes the point at the given position
    Pre: A properly constructed PolyLine object
    Post: pntList has given point removed from it
    Parameters:
      pos   = point to insert
  */
  void remove(int pos);

  /*
    Purpose: Prints a tabulated list of points
    Pre: A properly constructed PolyLine object
    Post: Organized list of points is printed on console
  */
  void show() const;

  /*
    Purpose: Saves pntList in an XML file format readable by XMLParse
    Pre: A properly constructed PolyLine object
    Post: pntList is saved in outputFile's location
  */
  void store() const;

private:
  //List of points
  list<Point> pntList;

  //Location where pntList will be saved
  string outputFile;
};