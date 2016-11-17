#pragma once

class Point {
public:
  Point(double xCoord = 0.0, double yCoord = 0.0);

  Point(const Point& other);

  double distanceTo(const Point point) const;

  double getX() const;
  double getY() const;

  bool operator==(const Point& compTo) const;

  void setX(double xCoord);
  void setY(double yCoord);
private:
  double x;
  double y;
};