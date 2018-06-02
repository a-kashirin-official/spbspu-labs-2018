#define BOOST_TEST_MAIN

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace sergeev;

const double EPSILON = 0.000001;

BOOST_AUTO_TEST_CASE(CopyConstructorTest)
{
  CompositeShape c_shape;

  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{{0.0,0.0},2.0,4.0});
  std::shared_ptr< Circle > circ = std::make_shared< Circle >(point_t{5.0,5.0},5.0);
  
  c_shape.add(rect);
  c_shape.add(circ);

  CompositeShape copy_shape{c_shape};

  BOOST_CHECK_EQUAL(copy_shape.getArea(), c_shape.getArea());
  BOOST_CHECK_EQUAL(copy_shape.getListSize(), c_shape.getListSize());
  BOOST_CHECK_EQUAL(copy_shape.getFrameRect().width, c_shape.getFrameRect().width);
  BOOST_CHECK_EQUAL(copy_shape.getFrameRect().height, c_shape.getFrameRect().height);
  BOOST_CHECK_EQUAL(copy_shape.getFrameRect().pos.x, c_shape.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(copy_shape.getFrameRect().pos.y, c_shape.getFrameRect().pos.y);
}

BOOST_AUTO_TEST_CASE(MoveConstructorTest)
{
  CompositeShape c_shape;
  
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{{0.0,0.0},2.0,4.0});
  std::shared_ptr< Circle > circ = std::make_shared< Circle >(point_t{5.0,5.0},5.0);
  
  c_shape.add(rect);
  c_shape.add(circ);

  double area = c_shape.getArea();
  int size = c_shape.getListSize();
  rectangle_t rect_before = c_shape.getFrameRect();

  CompositeShape move_shape{std::move(c_shape)};

  BOOST_CHECK_EQUAL(move_shape.getArea(), area);
  BOOST_CHECK_EQUAL(move_shape.getListSize(), size);
  BOOST_CHECK_EQUAL(move_shape.getFrameRect().pos.x, rect_before.pos.x);
  BOOST_CHECK_EQUAL(move_shape.getFrameRect().pos.y, rect_before.pos.y);
  BOOST_CHECK_EQUAL(move_shape.getFrameRect().width, rect_before.width);
  BOOST_CHECK_EQUAL(move_shape.getFrameRect().height, rect_before.height);

  BOOST_CHECK_EQUAL(c_shape.getArea(), 0.0);
  BOOST_CHECK_EQUAL(c_shape.getListSize(), 0);
  BOOST_CHECK_EQUAL(c_shape.getFrameRect().pos.x, 0.0);
  BOOST_CHECK_EQUAL(c_shape.getFrameRect().pos.y, 0.0);
  BOOST_CHECK_EQUAL(c_shape.getFrameRect().width, 0.0);
  BOOST_CHECK_EQUAL(c_shape.getFrameRect().height, 0.0);
}

BOOST_AUTO_TEST_CASE(CopyOperatorTest)
{
  CompositeShape c_shape, copy_shape;
  
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{{0.0,0.0},2.0,4.0});
  std::shared_ptr< Circle > circ = std::make_shared< Circle >(point_t{5.0,5.0},5.0);
  
  c_shape.add(rect);
  c_shape.add(circ);

  copy_shape = c_shape;

  BOOST_CHECK_EQUAL(copy_shape.getArea(), c_shape.getArea());
  BOOST_CHECK_EQUAL(copy_shape.getListSize(), c_shape.getListSize());
  BOOST_CHECK_EQUAL(copy_shape.getFrameRect().pos.x, c_shape.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(copy_shape.getFrameRect().pos.y, c_shape.getFrameRect().pos.y);
  BOOST_CHECK_EQUAL(copy_shape.getFrameRect().width, c_shape.getFrameRect().width);
  BOOST_CHECK_EQUAL(copy_shape.getFrameRect().height, c_shape.getFrameRect().height);
}

BOOST_AUTO_TEST_CASE(MoveOperatorTest)
{
  CompositeShape c_shape, move_shape;
  
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{{0.0,0.0},2.0,4.0});
  std::shared_ptr< Circle > circ = std::make_shared< Circle >(point_t{5.0,5.0},5.0);
  
  c_shape.add(rect);
  c_shape.add(circ);

  double area = c_shape.getArea();
  int size = c_shape.getListSize();
  rectangle_t rect_before = c_shape.getFrameRect();
  
  move_shape = std::move(c_shape);

  BOOST_CHECK_EQUAL(move_shape.getArea(), area);
  BOOST_CHECK_EQUAL(move_shape.getListSize(), size);
  BOOST_CHECK_EQUAL(move_shape.getFrameRect().pos.x, rect_before.pos.x);
  BOOST_CHECK_EQUAL(move_shape.getFrameRect().pos.y, rect_before.pos.y);
  BOOST_CHECK_EQUAL(move_shape.getFrameRect().width, rect_before.width);
  BOOST_CHECK_EQUAL(move_shape.getFrameRect().height, rect_before.height);

  BOOST_CHECK_EQUAL(c_shape.getArea(), 0.0);
  BOOST_CHECK_EQUAL(c_shape.getListSize(), 0);
  BOOST_CHECK_EQUAL(c_shape.getFrameRect().pos.x, 0.0);
  BOOST_CHECK_EQUAL(c_shape.getFrameRect().pos.y, 0.0);
  BOOST_CHECK_EQUAL(c_shape.getFrameRect().width, 0.0);
  BOOST_CHECK_EQUAL(c_shape.getFrameRect().height, 0.0);
}

BOOST_AUTO_TEST_CASE(ArrayOperatorTest)
{
  CompositeShape c_shape;
  
  const rectangle_t s_rect{{0.0,0.0},2.0,4.0};
  const point_t s_circ{5.0,5.0};
  const double radius = 5.0;

  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(s_rect);
  std::shared_ptr< Circle > circ = std::make_shared< Circle >(s_circ, radius);
  
  c_shape.add(rect);
  c_shape.add(circ);
  
  BOOST_CHECK_CLOSE(c_shape[0]->getArea(), (s_rect.width * s_rect.height), EPSILON);
  BOOST_CHECK_CLOSE(c_shape[1]->getArea(), (M_PI * radius * radius), EPSILON);
}

BOOST_AUTO_TEST_CASE(WrongRangeTest)
{
  CompositeShape c_shape;
  BOOST_CHECK_THROW(c_shape[0], std::out_of_range);

  std::shared_ptr< Circle > circ = std::make_shared< Circle >(point_t{5.0,5.0},5.0);
  c_shape.add(circ);
  BOOST_CHECK_THROW(c_shape[1], std::out_of_range);

  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{{0.0,0.0},2.0,4.0});
  c_shape.add(rect);
  BOOST_CHECK_THROW(c_shape[2], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(getAreaTest)
{
  CompositeShape c_shape;
  
  const rectangle_t s_rect{{0.0,0.0},2.0,4.0};
  const point_t s_circ{5.0,5.0};
  const double radius = 5.0;

  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(s_rect);
  std::shared_ptr< Circle > circ = std::make_shared< Circle >(s_circ, radius);
  
  c_shape.add(rect);
  c_shape.add(circ);

  BOOST_CHECK_CLOSE(c_shape.getArea(), (s_rect.height * s_rect.width + radius * radius * M_PI), EPSILON);
}

BOOST_AUTO_TEST_CASE(getFrameRectTest)
{
  CompositeShape c_shape;

  const rectangle_t s_rect{{0.0,0.0},2.0,4.0};
  const point_t s_circ{5.0,5.0};
  const double radius = 4.0;
  
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(s_rect);
  std::shared_ptr< Circle > circ = std::make_shared< Circle >(s_circ, radius);
  
  c_shape.add(rect);
  c_shape.add(circ);

  
  BOOST_CHECK_CLOSE(c_shape.getFrameRect().pos.x,4.0, EPSILON);
  BOOST_CHECK_CLOSE(c_shape.getFrameRect().pos.y,3.5, EPSILON);
  BOOST_CHECK_CLOSE(c_shape.getFrameRect().width,10.0, EPSILON);
  BOOST_CHECK_CLOSE(c_shape.getFrameRect().height,11.0, EPSILON);
}

BOOST_AUTO_TEST_CASE(ShiftTest)
{
  CompositeShape c_shape;
  
  const rectangle_t s_rect{{0.0,0.0},2.0,4.0};
  const point_t s_circ{5.0,5.0};
  const double radius = 5.0;

  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(s_rect);
  std::shared_ptr< Circle > circ = std::make_shared< Circle >(s_circ, radius);
  c_shape.add(rect);
  c_shape.add(circ);

  const double dx = 10.0, dy = 10.0;
  c_shape.move(dx, dy);

  BOOST_CHECK_CLOSE(c_shape[0]->getFrameRect().pos.x, (s_rect.pos.x + dx), EPSILON);
  BOOST_CHECK_CLOSE(c_shape[0]->getFrameRect().pos.y, (s_rect.pos.y + dy), EPSILON);
  BOOST_CHECK_CLOSE(c_shape[0]->getArea(), (s_rect.height * s_rect.width), EPSILON);

  BOOST_CHECK_CLOSE(c_shape[1]->getFrameRect().pos.x, (s_circ.x + dx), EPSILON);
  BOOST_CHECK_CLOSE(c_shape[1]->getFrameRect().pos.y, (s_circ.y + dy), EPSILON);
  BOOST_CHECK_CLOSE(c_shape[1]->getArea(), (M_PI * radius * radius), EPSILON);
}

BOOST_AUTO_TEST_CASE(CoordsShiftTest)
{
  CompositeShape c_shape;
  
  const rectangle_t s_rect{{0.0,0.0},2.0,4.0};
  const point_t s_circ{5.0,5.0};
  const double radius = 4.0;

  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(s_rect);
  std::shared_ptr< Circle > circ = std::make_shared< Circle >(s_circ, radius);
  c_shape.add(rect);
  c_shape.add(circ);

  point_t before = c_shape.getFrameRect().pos;
  const point_t point{10.0, 15.0};
  c_shape.move(point);

  BOOST_CHECK_CLOSE(c_shape[0]->getFrameRect().pos.x - s_rect.pos.x, point.x - before.x, EPSILON);
  BOOST_CHECK_CLOSE(c_shape[0]->getFrameRect().pos.y - s_rect.pos.y, point.y - before.y, EPSILON);
  BOOST_CHECK_CLOSE(c_shape[0]->getArea(), (s_rect.height * s_rect.width), EPSILON);

  BOOST_CHECK_CLOSE(c_shape[1]->getFrameRect().pos.x - s_circ.x, point.x - before.x, EPSILON);
  BOOST_CHECK_CLOSE(c_shape[1]->getFrameRect().pos.y - s_circ.y, point.y - before.y, EPSILON);
  BOOST_CHECK_CLOSE(c_shape[1]->getArea(), (M_PI * radius * radius), EPSILON);
}

BOOST_AUTO_TEST_CASE(ScaleTest)
{
  CompositeShape c_shape;
  
  const rectangle_t s_rect{{0.0,0.0},2.0,4.0};
  const point_t s_circ{5.0,5.0};
  const double radius = 5.0;
  const double factor = 2.0;

  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(s_rect);
  std::shared_ptr< Circle > circ = std::make_shared< Circle >(s_circ, radius);
  c_shape.add(rect);
  c_shape.add(circ);
  point_t shape_center = c_shape.getFrameRect().pos;
  c_shape.scale(factor);

  BOOST_CHECK_CLOSE(c_shape[0]->getFrameRect().pos.x, s_rect.pos.x + (s_rect.pos.x - c_shape.getFrameRect().pos.x) * (factor - 1), EPSILON);
  BOOST_CHECK_CLOSE(c_shape[0]->getFrameRect().pos.y, s_rect.pos.y + (s_rect.pos.y - c_shape.getFrameRect().pos.y) * (factor - 1), EPSILON);
  BOOST_CHECK_CLOSE(c_shape[0]->getArea(), (s_rect.width * s_rect.height * factor * factor), EPSILON);

  BOOST_CHECK_CLOSE(c_shape[1]->getFrameRect().pos.x, s_circ.x + (s_circ.x - c_shape.getFrameRect().pos.x) * (factor - 1), EPSILON);
  BOOST_CHECK_CLOSE(c_shape[1]->getFrameRect().pos.y, s_circ.y + (s_circ.y - c_shape.getFrameRect().pos.y) * (factor - 1), EPSILON);
  BOOST_CHECK_CLOSE(c_shape[1]->getArea(), (M_PI * radius * radius * factor * factor), EPSILON);

  BOOST_CHECK_CLOSE(c_shape.getFrameRect().pos.x, shape_center.x, EPSILON);
  BOOST_CHECK_CLOSE(c_shape.getFrameRect().pos.y, shape_center.y, EPSILON);
}

BOOST_AUTO_TEST_CASE(WrongScaleFactorTest)
{
  CompositeShape c_shape;
  
  const rectangle_t s_rect{{0.0,0.0},2.0,4.0};
  const point_t s_circ{5.0,5.0};
  const double radius = 5.0;
  const double factor = -2.0;

  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(s_rect);
  std::shared_ptr< Circle > circ = std::make_shared< Circle >(s_circ, radius);
  c_shape.add(rect);
  c_shape.add(circ);

  BOOST_CHECK_THROW(c_shape.scale(factor), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(getListSizeTest)
{
  CompositeShape c_shape;

  const rectangle_t s_rect{{0.0,0.0},2.0,4.0};
  const point_t s_circ{5.0,5.0};
  const double radius = 5.0;

  BOOST_CHECK_EQUAL(c_shape.getListSize(), 0);
  
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(s_rect);
  c_shape.add(rect);

  BOOST_CHECK_EQUAL(c_shape.getListSize(), 1);

  std::shared_ptr< Circle > circ = std::make_shared< Circle >(s_circ, radius);
  c_shape.add(circ);

  BOOST_CHECK_EQUAL(c_shape.getListSize(), 2);
}

BOOST_AUTO_TEST_CASE(AddTest)
{
  CompositeShape c_shape;

  const rectangle_t s_rect{{0.0,0.0},2.0,4.0};
  const point_t s_circ{5.0,5.0};
  const double radius = 5.0;
  
  BOOST_CHECK_EQUAL(c_shape.getListSize(), 0);

  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(s_rect);
  c_shape.add(rect);

  BOOST_CHECK_EQUAL(c_shape.getListSize(), 1);

  std::shared_ptr< Circle > circ = std::make_shared< Circle >(s_circ, radius);
  c_shape.add(circ);

  BOOST_CHECK_EQUAL(c_shape.getListSize(), 2);
}

BOOST_AUTO_TEST_CASE(DisposeTest)
{
  CompositeShape c_shape;

  const rectangle_t s_rect{{0.0,0.0},2.0,4.0};
  const point_t s_circ{5.0,5.0};
  const double radius = 5.0;

  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(s_rect);
  std::shared_ptr< Circle > circ = std::make_shared< Circle >(s_circ, radius);
  c_shape.add(rect);
  c_shape.add(circ);

  c_shape.dispose(1);
  BOOST_CHECK_EQUAL(c_shape.getListSize(), 1);
  c_shape.dispose(0);
  BOOST_CHECK_EQUAL(c_shape.getListSize(), 0);
}

BOOST_AUTO_TEST_CASE(CleanTest)
{
  CompositeShape c_shape;
  
  const rectangle_t s_rect{{0.0,0.0},2.0,4.0};
  const point_t s_circ{5.0,5.0};
  const double radius = 5.0;
  
  std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(s_rect);
  std::shared_ptr< Circle > circ = std::make_shared< Circle >(s_circ, radius);
  c_shape.add(rect);
  c_shape.add(circ);

  c_shape.clean();

  BOOST_CHECK_EQUAL(c_shape.getListSize(), 0);
  BOOST_CHECK_THROW(c_shape[0], std::out_of_range);
  BOOST_CHECK_THROW(c_shape[1], std::out_of_range);
}
