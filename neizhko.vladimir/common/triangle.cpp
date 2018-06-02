#include <iostream>
#include "triangle.hpp"
#include <cmath>

using std::cout;
using std::endl;
using namespace neizhko;

Triangle::Triangle(double Ax, double Ay, double Bx, double By, double Cx, double Cy) :
  tri_A_({Ax, Ay}),
  tri_B_({Bx, By}),
  tri_C_({Cx, Cy})
{
  center_.x = (tri_A_.x + tri_B_.x + tri_C_.x)/3;
  center_.y = (tri_A_.y + tri_B_.y + tri_C_.y)/3;
}

  void Triangle::printInfo() const
{
  cout << ">>>TRIANGLE"<< endl;
  cout << "Area of triangle: " << getArea() << endl;
  cout << "Cords of center of triangle: " << center_.x << " " << center_.y << endl;
  rectangle_t frec;
  frec = getFrameRect();
  cout << "FRAME TRIANGLE" << endl << "Height: " << frec.height << endl;
  cout << "Width: " << frec.width << endl << "x, y cords: " << frec.pos.x << " " << frec.pos.y << endl << endl;
}

void Triangle::move(point_t c)
{
  tri_A_.x += (c.x - center_.x);
  tri_A_.y += (c.y - center_.y);
  tri_B_.x += (c.x - center_.x);
  tri_B_.y += (c.y - center_.y);
  tri_C_.x += (c.x - center_.x);
  tri_C_.y += (c.y - center_.y);
  center_ = c;
}

void Triangle::move(double dx, double dy)
{
  tri_A_.x += dx;
  tri_A_.y += dy;
  tri_B_.x += dx;
  tri_B_.y += dy;
  tri_C_.x += dx;
  tri_C_.y += dy;
  center_.x += dx;
  center_.y += dy;
}

double Triangle::getArea() const
{
  return -0.5 * (tri_A_.x * (tri_B_.y - tri_C_.y) + tri_B_.x * (tri_C_.y - tri_A_.y) + tri_C_.x * (tri_A_.y - tri_B_.y));
}

rectangle_t Triangle::getFrameRect() const
{
  point_t mas[3] = {tri_A_, tri_B_, tri_C_};

  point_t min = mas[0];
  for(int i=1; i<2; i++)
  {
    if(mas[i].y < min.y)
  {
    min = mas[i];
  }
  }

  point_t lowCord;
  lowCord = min;

  point_t max = mas[0];
  for(int i = 1; i < 2; i++)
  {
    if(mas[i].y > max.y)
  {
    max = mas[i];
  }
  }

  point_t highCord;
  highCord = max;

  point_t left = mas[0];
  for(int i=1; i<2; i++)
  {
    if(mas[i].x < min.x)
  {
    left = mas[i];
  }
  }

  point_t leftCord;
  leftCord = left;

  point_t right = mas[0];
  for(int i=1; i<2; i++)
  {
    if(mas[i].x > min.x)
  {
    right = mas[i];
  }
  }

  point_t rightCord;
  rightCord = right;

  double triWidth;
  triWidth = rightCord.x - leftCord.x;

  double triHeight;
  triHeight = highCord.y - lowCord.y;

  point_t triCenter;
  triCenter.x = rightCord.x - (triWidth / 2);
  triCenter.y = highCord.y - (triHeight / 2);

  return {triWidth, triHeight, triCenter};
}

void Triangle::scale(double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("ratio must be >= 0");
  }
  point_t oldCenter = center_;
  tri_A_.x *= ratio; 
  tri_A_.y *= ratio;
  tri_B_.x *= ratio;
  tri_B_.y *= ratio;
  tri_C_.x *= ratio;
  tri_C_.y *= ratio;
  center_.x = (tri_A_.x + tri_B_.x + tri_C_.x)/3;
  center_.y = (tri_A_.y + tri_B_.y + tri_C_.y)/3;
  move(oldCenter);
}

double Triangle::getAB() const
{
  return sqrt(pow(tri_B_.x-tri_A_.x,2)+pow(tri_B_.y-tri_A_.y,2));
}

double Triangle::getBC() const
{
  return sqrt(pow(tri_B_.x-tri_C_.x,2)+pow(tri_B_.y-tri_C_.y,2));
}

double Triangle::getAC() const
{
  return sqrt(pow(tri_C_.x-tri_A_.x,2)+pow(tri_C_.y-tri_A_.y,2));
}
