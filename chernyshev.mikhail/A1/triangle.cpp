#include "triangle.hpp"
#include <cmath>
#include <iostream>
Triangle::Triangle(point_t a, point_t b, point_t c): a_(a), b_(b), c_(c)
{
  point_t h;// точка для медианы

  h.x = a_.x + ((c_.x-a_.x)/2);// точка медианы
  h.y = a_.y + ((c_.y-a_.y)/2);
  
  center_.x = h.x + ((abs(b_.x-h.x))/3);//определение центра тяжести
  center_.y = h.y + ((abs(b_.y-h.y))/3);
}

double Triangle::getArea()const
{
  double ab,bc,ca,p;// 3 стороны и полупериметр
  ab = sqrt(pow((b_.x-a_.x),2)+pow((b_.y-a_.y),2));
  bc = sqrt(pow((c_.x-b_.x),2)+pow((c_.y-b_.y),2));
  ca = sqrt(pow((a_.x-c_.x),2)+pow((a_.y-c_.y),2));
  p = (ab+bc+ca)/2;
  return sqrt(p*(p-ab)*(p-bc)*(p-ca));// расчет по формуле Герона
}

rectangle_t Triangle::getFrameRect()const
{
  rectangle_t rect;
//расчет высоты
  if ((abs(a_.y - b_.y) > abs(b_.y-c_.y))>0)
  {
    rect.height = (abs(a_.y - b_.y));
  }
  else if(abs(b_.y-c_.y)>0)
  {
    rect.height = (abs(b_.y-c_.y));
  }
//расчет ширины
  if (abs(a_.x - c_.x) > abs(b_.x-c_.x))
  {
    rect.width = (abs(a_.x - b_.x));
  }
  else if ((abs(b_.x-c_.x))>0)
  {
    rect.width = (abs(b_.x-c_.x));
  }
  rect.pos = center_;
  return rect;
}

void Triangle::Move(double delta_x, double delta_y)// хх и yy - смещение
{
  center_.x += delta_x;
  center_.y += delta_y;
      
}
void Triangle::Move(point_t newPoint)
{
  center_=newPoint;
}
