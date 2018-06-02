#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "base-types.hpp"


int main()
{
  Rectangle r({ 20, 30 }, 5, 6);
  r.move(5, 10);
  r.move({ 44.31, 18.19 });
  r.getFrameRect();
  r.getArea();

  Circle c({ 14, 18 }, 3);
  c.move({ 11.31, 10 });
  c.move(5.5, 21.1);
  c.getFrameRect();
  c.getArea();

  Triangle t({ 20, 42 }, { 34, 33 }, { 15, 10 });
  t.move(1.8, 5);
  t.move({ 33, 107 });
  t.getFrameRect();
  t.getArea();

  return 0;
}
