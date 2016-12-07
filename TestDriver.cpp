using namespace std;
#include<iostream>

#include"PolyLine.h"

const string INPUT_FILE = "inp.txt";

int main() {
  PolyLine* polyLine = new PolyLine(INPUT_FILE);
  int selector = 5;//Defualt to polyLine->show();
  //Values used for removing/inserting a new point
  int nodePos = 0;
  double afterX = 0.0;
  double afterY = 0.0;
  double newX = 0.0;
  double newY = 0.0;
  while(true){
    switch (selector) {
      //Terminate Program
    case 0:
      return 0;
      break;
      //Create new PolyLine
    case 1:
      delete polyLine;
      polyLine = new PolyLine();
      break;
      //Calculate length
    case 2:
      cout << "Length: " << polyLine->length() << endl;
      break;
      //Insert new node
    case 3:
      if (polyLine->size() > 0) {
        cout << "Enter x and y of a new point followed by the x and y" 
          << " of an existing point: " << endl;
        cin >> newX >> newY >> afterX >> afterY;
        polyLine->insert(Point(newX, newY), Point(afterX, afterY));
      } else {
        cout << "Enter x and y of a new point: " << endl;
        cin >> newX >> newY;
        polyLine->insert(Point(newX, newY));
      }
      break;
      //Remove node
    case 4:
      cout << "Enter position: " << endl;
      cin >> nodePos;
      polyLine->remove(nodePos);
      break;
      //Show Object
    case 5:
      polyLine->show();
      break;
      //Show num of points
    case 6:
      cout << "Number of points: " << polyLine->size() << endl;
      break;
      //Save to file
    case 7:
      polyLine->store();
      break;
    default:
      break;
    }
    //Print menu options
    cout << endl << "Commands:" << endl;
    cout << "0: Terminate Program" << endl;
    cout << "1: Create new empty PolyLine Object" << endl;
    cout << "2: Print the length of all lines connecting subsequent points" << endl;
    cout << "3: Insert a new point after an existing given point" << endl;
    cout << "4: Remove a point" << endl;
    cout << "5: Print all points" << endl;
    cout << "6: Print number of points" << endl;
    cout << "7: Store object in outp.txt" << endl;
    cout << "Enter a command number: ";
    if (!(cin >> selector)) {
      selector = 8;
    }
    cout << endl;
    cin.clear();
    cin.ignore(string::npos, '\n');
  }
  return 0;
}