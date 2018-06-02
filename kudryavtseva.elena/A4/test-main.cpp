#define USE_DEFINE_MATH
#define BOOST_TEST_MODULE boost_test
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double EPSILON = 0.001;

BOOST_AUTO_TEST_SUITE(AddingShapes)

BOOST_AUTO_TEST_CASE(Size)
{
  kudryavtseva::Rectangle r({2.0,3.0}, 4.0, 5.0);
  kudryavtseva::Circle c({1.0,6.0}, 3.0);
  kudryavtseva::CompositeShape compos(&r);
  compos.add(&c);
  BOOST_CHECK_EQUAL(compos.getSize(),2);
}

BOOST_AUTO_TEST_CASE(SquareOfRectangle)
{
  kudryavtseva::Rectangle r({2.0,3.0}, 4.0, 5.0);
  kudryavtseva::CompositeShape compos(&r);
  BOOST_CHECK_EQUAL(compos.getArea(), 4.0*5.0);
}

BOOST_AUTO_TEST_CASE(SquareOfCircle)
{
  kudryavtseva::Circle c({1.0,6.0}, 3.0);
  kudryavtseva::CompositeShape compos(&c);
  BOOST_CHECK_EQUAL(compos.getArea(), 3.0*3.0*M_PI);
}

BOOST_AUTO_TEST_CASE(ScaleOfRectangle)
{
  kudryavtseva::Rectangle r({2.0,3.0}, 4.0, 5.0);
  double s = r.getArea();
  kudryavtseva::CompositeShape compos(&r);
  compos.scale(2);
  BOOST_CHECK_CLOSE(s*4.0, compos.getArea(), EPSILON);
  BOOST_CHECK_THROW(compos.scale(-2.0), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(ScaleOfCircle)
{
  kudryavtseva::Circle c({1.0,6.0},3.0);
  double s = c.getArea();
  kudryavtseva::CompositeShape compos(&c);
  compos.scale(3.0);
  BOOST_CHECK_CLOSE(s*9.0, compos.getArea(), EPSILON);
  BOOST_CHECK_THROW(compos.scale(-1.0), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(Square)
{
  kudryavtseva::Rectangle r({2.0,3.0}, 4.0, 5.0);
  kudryavtseva::Circle c({1.0,6.0},3.0);
  kudryavtseva::CompositeShape compos(&r);
  compos.add(&c);
  BOOST_CHECK_CLOSE(compos.getArea(), r.getArea()+c.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(CenterOfCircle)
{
  kudryavtseva::Circle c({2.0,1.0},1.0);
  kudryavtseva::CompositeShape compos(&c);
  BOOST_CHECK_CLOSE(compos.getFrameRect().pos.x, 2.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().pos.y, 1.0, EPSILON);
}
BOOST_AUTO_TEST_CASE(CenterOfRectangle)
{
  kudryavtseva::Rectangle r({3.0,4.0},2.0,1.0);
  kudryavtseva::CompositeShape compos(&r);
  BOOST_CHECK_CLOSE(compos.getFrameRect().pos.x, 3.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().pos.y, 4.0, EPSILON);
}
BOOST_AUTO_TEST_CASE(Incorrectness)
{
  BOOST_CHECK_THROW(kudryavtseva::CompositeShape(nullptr), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(IncorrectnessAdding1)
{
  kudryavtseva::Circle c({1.0,2.0},5.0);
  kudryavtseva::CompositeShape compos(&c);
  BOOST_CHECK_THROW(compos.add(nullptr), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(IncorrectIndex)
{
  kudryavtseva::Rectangle r({2.0, 2.0}, 1.0, 4.0);
  kudryavtseva::CompositeShape comp;
  comp.add(&r);
  BOOST_CHECK_THROW(comp[2], std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(IncorrectnessAdding)
{
  kudryavtseva::Rectangle r({1.0,2.0},2.0,1.0);
  kudryavtseva::CompositeShape compos(&r);
  BOOST_CHECK_THROW(compos.add(nullptr), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(EmptyCompositeShape)
{
  kudryavtseva::CompositeShape comp;
  BOOST_REQUIRE_EQUAL(comp.getSize(), 0);
}
BOOST_AUTO_TEST_CASE(RemoveCompositeShape)
{
  kudryavtseva::Rectangle r1({3.0,3.0}, 5.0, 5.0);
  kudryavtseva::Rectangle r2({1.0,3.0}, 3.0, 4.0);
  kudryavtseva::Circle c1({1.0,6.0}, 9.0);
  kudryavtseva::Circle c2({0.0,6.0}, 3.0);
  kudryavtseva::CompositeShape comp;
  comp.add(&c1);
  comp.add(&r1);
  comp.add(&c2);
  comp.add(&r2);
  comp.removeShape(2);
  BOOST_REQUIRE_EQUAL(comp.getSize(), 3);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Moving)

BOOST_AUTO_TEST_CASE(MoveAlongAxesForRectangle)
{
  kudryavtseva::Rectangle r({2.0,3.0}, 4.0, 5.0);
  kudryavtseva::CompositeShape compos(&r);
  compos.move(3.0,2.0);
  BOOST_CHECK_CLOSE(compos.getFrameRect().width, 4.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().height, 5.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().width, r.getWidth(), EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().height, r.getHeight(), EPSILON);
}
BOOST_AUTO_TEST_CASE(MoveAlongAxesForCircle)
{
  kudryavtseva::Circle c({1.0,2.0},1.0);
  kudryavtseva::point_t pos = c.getFrameRect().pos;
  kudryavtseva::point_t pos1 = c.getPos();
  kudryavtseva::CompositeShape compos(&c);
  compos.move(5.0,1.0);
  BOOST_CHECK_CLOSE(compos.getFrameRect().width, 2.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().height, 2.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().pos.x, pos.x+5.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().pos.y, pos.y+1.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().pos.x, pos1.x+5.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().pos.y, pos1.y+1.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().width, c.getRadius()*2.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().height, c.getRadius()*2.0, EPSILON);
}
BOOST_AUTO_TEST_CASE(MoveRectangleToPoint)
{
  kudryavtseva::Rectangle r({2.0,3.0}, 4.0, 5.0);
  kudryavtseva::CompositeShape compos(&r);
  compos.move({1.0,1.0});
  BOOST_CHECK_CLOSE(compos.getFrameRect().width, 4.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().height, 5.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().width, r.getWidth(), EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().height, r.getHeight(), EPSILON);
}
BOOST_AUTO_TEST_CASE(MoveCircleToPoint)
{
  kudryavtseva::Circle c({1.0,2.0},1.0);
  kudryavtseva::point_t pos = c.getFrameRect().pos;
  kudryavtseva::point_t pos1 = c.getPos();
  kudryavtseva::CompositeShape compos(&c);
  compos.move({5.0,1.0});
  BOOST_CHECK_CLOSE(compos.getFrameRect().width, 2.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().height, 2.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().pos.x, pos.x+4.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().pos.y, pos.y-1.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().pos.x, pos1.x+4.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().pos.y, pos1.y-1.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().width, c.getRadius()*2.0, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().height, c.getRadius()*2.0, EPSILON);
}
BOOST_AUTO_TEST_CASE(Move)
{
  kudryavtseva::Rectangle r({2.0,3.0}, 4.0, 5.0);
  kudryavtseva::Circle c({1.0,6.0},3.0);
  kudryavtseva::CompositeShape compos(&r);
  compos.add(&c);
  double s = compos.getArea();
  compos.move(1.0,1.0);
  BOOST_CHECK_CLOSE(s, compos.getArea(),EPSILON);
  compos.move({1.0,1.0});
  BOOST_CHECK_CLOSE(s, compos.getArea(),EPSILON);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Rotate)

BOOST_AUTO_TEST_CASE(RotateOfRectangle)
{
  kudryavtseva::Rectangle r({2.0,3.0}, 4.0, 5.0);
  r.rotate(200.0);
  BOOST_CHECK_CLOSE(r.getFrameRect().pos.x, 2.0,EPSILON);
  BOOST_CHECK_CLOSE(r.getFrameRect().pos.y, 3.0,EPSILON);
 }
BOOST_AUTO_TEST_CASE(RotateOfRectangle2)
{
  kudryavtseva::Rectangle r({2.0,3.0}, 4.0, 5.0);
  r.rotate(200.0);
  BOOST_CHECK_CLOSE(r.getWidth(), 4.0,EPSILON);
  BOOST_CHECK_CLOSE(r.getHeight(), 5.0,EPSILON);
 }

BOOST_AUTO_TEST_CASE(RotateOfCompositeShape)
{
  kudryavtseva::Rectangle r({2.0,3.0}, 4.0, 5.0);
  kudryavtseva::Circle c({1.0,6.0},3.0);
  kudryavtseva::CompositeShape compos(&r);
  compos.add(&c);
  compos.rotate(5.0);
  BOOST_CHECK_CLOSE(compos.getFrameRect().pos.x, 0.869328, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().pos.y, 4.7654, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().width, 6.2694, EPSILON);
  BOOST_CHECK_CLOSE(compos.getFrameRect().height, 8.5361, EPSILON);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestsOfMatrix)

BOOST_AUTO_TEST_CASE(InvalidArgument)
{
  kudryavtseva::Rectangle r({1.1,2.1},3.0,4.0);
  kudryavtseva::Matrix m(&r);
  BOOST_CHECK_THROW(m.add(nullptr),std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(matrix_invalid_argument)
{
  kudryavtseva::Rectangle r({1.1,2.1},3.0,4.0);
  kudryavtseva::Matrix m(&r);
  BOOST_CHECK_THROW(m.getShape(2.0,1.0),std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(Test)
{
  kudryavtseva::Rectangle r({1.1,2.1},3.0,4.0);
  kudryavtseva::Circle c({1.1,2.1},9.0);
  kudryavtseva::CompositeShape compos(&r);
  compos.add(&c);
  kudryavtseva::Matrix m1(&compos);
  kudryavtseva::rectangle_t r1 = m1[0][0]->getFrameRect();
  BOOST_CHECK_CLOSE(r1.pos.x, 1.1, EPSILON);
  BOOST_CHECK_CLOSE(r1.pos.y, 2.1, EPSILON);
  BOOST_CHECK_CLOSE(r1.width, 18.0, EPSILON);
  BOOST_CHECK_CLOSE(r1.height, 18.0, EPSILON);
}
BOOST_AUTO_TEST_SUITE_END()
