#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "base-types.hpp"


int main()
{
  Rectangle rec({ 25, 35 }, 10, 11);
  rec.move(6, 5);
  rec.move({ 41.32, 19.19 });
  rec.getFrameRect();
  rec.getArea();

  Circle cir({ 24, 28 }, 5);
  cir.move({ 11.31, 10 });
  cir.move(5.7, 20.1);
  cir.getFrameRect();
  cir.getArea();

  Triangle tria({ 3, 32 }, { 21, 18 }, { 15, 10 });
  tria.move(1.9, 7);
  tria.move({ 38, 40 });
  tria.getFrameRect();
  tria.getArea();

  return 0;
}
