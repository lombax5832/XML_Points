#include "Point.h"

#include<cmath>

Point::Point(double xCoord, double yCoord) {
  setX(xCoord);
  setY(yCoord);
}

Point::Point(const Point & other) {
  setX(other.getX());
  setY(other.getY());
}

double Point::distanceTo(const Point point) const {
  return sqrt(pow(getX() - point.getX(), 2.0) + pow(getY() - point.getY(), 2.0));
}

double Point::getX() const {
  return x;
}

double Point::getY() const {
  return y;
}

void Point::setX(double xCoord) {
  x = xCoord;
}

void Point::setY(double yCoord) {
  y = yCoord;
}
