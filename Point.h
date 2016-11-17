#pragma once

class Point {
public:
  /*
    Purpose: Constructor/Default Constructor for the class Point
    Post: Creates an Point object to store x and y values of a point
    Parameters:
      xCoord = x value
      yCoord = y value
  */
  Point(double xCoord = 0.0, double yCoord = 0.0);

  /*
    Purpose: copy constructor for class Point
    Pre: Valid Point object passed
    Post: Creates an Point object with same values of passed Point object
    Parameters:
      &other = Point to copy values from
  */
  Point(const Point& other);

  /*
    Purpose: Returns distance to given point
    Pre: Current point and passed point are valid
    Post: Returns distance between this Point and passed Point
    Parameters:
      &point = Point to calulate distance to
  */
  double distanceTo(const Point& point) const;

  /*
    Purpose: Returns x value
    Pre: Current point is properly constructed
    Post: Returns x value of current Point
  */
  double getX() const;

  /*
    Purpose: Returns y value
    Pre: Current point is properly constructed
    Post: Returns y value of current Point
  */
  double getY() const;

  /*
    Purpose: Overloaded equality comparison operator
    Pre: Current point and passed point are valid
    Post: Returns true if x and y values of both points are within 0.001
    Parameters:
      &compTo = Point to compare to
  */
  bool operator==(const Point& compTo) const;

  /*
    Purpose: Sets x value
    Post: x value is set
    Parameters:
      xCoord = value to set x to
  */
  void setX(double xCoord);

  /*
    Purpose: Sets y value
    Post: y value is set
    Parameters:
      xCoord = value to set y to
  */
  void setY(double yCoord);
private:
  //X and Y values
  double x, y;
};