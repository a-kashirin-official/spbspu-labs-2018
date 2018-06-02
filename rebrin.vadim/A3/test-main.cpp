#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <memory>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

#include <boost/test/included/unit_test.hpp>

const double EPS = 1e-4;


BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  BOOST_AUTO_TEST_CASE(CopyOperator)
  {
    rebrin::Rectangle rect1({12.0, 10.0, 0.0, 0.0});
    rebrin::Circle circle1({2.0, 2.0}, 4.9);
    rebrin::CompositeShape comp(std::make_shared < rebrin::Rectangle > (rect1));
    comp.addShape(std::make_shared < rebrin::Circle > (circle1));
    rebrin::CompositeShape comp2(comp);
    BOOST_CHECK_CLOSE(comp.getFrameRect().width, comp2.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().height, comp2.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.x, comp2.getFrameRect().pos.x, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.y, comp2.getFrameRect().pos.y, EPS);
    BOOST_CHECK_CLOSE(comp.getArea(), comp2.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(AssigmentOperator)
  {
    rebrin::Rectangle rect1({12.0, 10.0, 0.0, 0.0});
    rebrin::Circle circle1({2.0, 2.0}, 4.9);
    rebrin::CompositeShape comp(std::make_shared < rebrin::Rectangle > (rect1));
    comp.addShape(std::make_shared < rebrin::Circle > (circle1));
    rebrin::CompositeShape comp2(std::make_shared < rebrin::Rectangle > (rect1));
    comp2 = comp;
    BOOST_CHECK_CLOSE(comp.getFrameRect().width, comp2.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().height, comp2.getFrameRect().height, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.x, comp2.getFrameRect().pos.x, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.y, comp2.getFrameRect().pos.y, EPS);
    BOOST_CHECK_CLOSE(comp.getArea(), comp2.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(DeltaMoving)
  {
    rebrin::Rectangle rect1({12.0, 10.0, 0.0, 0.0});
    rebrin::Rectangle rect2({5.0, 5.0, 3.0, 5.0});
    rebrin::Rectangle rect3({1.0, 14.0, 9.0, 9.5});
    rebrin::Circle circle1({2.0, 2.0}, 4.9);
    rebrin::CompositeShape comp(std::make_shared < rebrin::Rectangle > (rect1));
    comp.addShape(std::make_shared < rebrin::Rectangle > (rect2));
    comp.addShape(std::make_shared < rebrin::Rectangle > (rect3));
    comp.addShape(std::make_shared < rebrin::Circle > (circle1));
    double area = comp.getArea();
    double width = comp.getFrameRect().width;
    double height = comp.getFrameRect().height;
    double x = comp.getFrameRect().pos.x;
    double y = comp.getFrameRect().pos.y;
    double dx = 5.0;
    double dy = 4.0;
    comp.move(dx, dy);
    BOOST_CHECK_CLOSE(comp.getArea(), area, EPS);
    BOOST_CHECK_EQUAL(comp.getFrameRect().width, width);
    BOOST_CHECK_EQUAL(comp.getFrameRect().height, height);
    BOOST_CHECK_EQUAL(comp.getFrameRect().pos.x, x + dx);
    BOOST_CHECK_EQUAL(comp.getFrameRect().pos.y, y + dy);
  }

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    rebrin::Rectangle rect1({12.0, 10.0, 0.0, 0.0});
    rebrin::Rectangle rect2({5.0, 5.0, 3.0, 5.0});
    rebrin::Rectangle rect3({1.0, 14.0, 9.0, 9.5});
    rebrin::Circle circle1({2.0, 2.0}, 4.9);
    rebrin::CompositeShape comp(std::make_shared < rebrin::Rectangle > (rect1));
    comp.addShape(std::make_shared < rebrin::Rectangle > (rect2));
    comp.addShape(std::make_shared < rebrin::Rectangle > (rect3));
    comp.addShape(std::make_shared < rebrin::Circle > (circle1));
    double area = comp.getArea();
    double width = comp.getFrameRect().width;
    double height = comp.getFrameRect().height;
    comp.move({0.0, 0.0});
    BOOST_CHECK_CLOSE(comp.getArea(), area, EPS);
    BOOST_CHECK_EQUAL(comp.getFrameRect().width, width);
    BOOST_CHECK_EQUAL(comp.getFrameRect().height, height);
    BOOST_CHECK_EQUAL(comp.getFrameRect().pos.x, 0.0);
    BOOST_CHECK_EQUAL(comp.getFrameRect().pos.y, 0.0);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    rebrin::Rectangle rect1({12.0, 10.0, 0.0, 0.0});
    rebrin::Rectangle rect2({5.0, 5.0, 3.0, 5.0});
    rebrin::Rectangle rect3({1.0, 14.0, 9.0, 9.5});
    rebrin::Circle circle1({2.0, 2.0}, 4.9);
    rebrin::CompositeShape comp(std::make_shared < rebrin::Rectangle > (rect1));
    comp.addShape(std::make_shared < rebrin::Rectangle > (rect2));
    comp.addShape(std::make_shared < rebrin::Rectangle > (rect3));
    comp.addShape(std::make_shared < rebrin::Circle > (circle1));
    double area = comp.getArea();
    double width = comp.getFrameRect().width;
    double height = comp.getFrameRect().height;
    double x = comp.getFrameRect().pos.x;
    double y = comp.getFrameRect().pos.y;
    comp.scale(3.0);
    BOOST_CHECK_CLOSE(comp.getArea(), area * 3.0 * 3.0, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().width, width * 3.0, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().height, height * 3.0, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.x, x, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.y, y, EPS);
  }

  BOOST_AUTO_TEST_CASE(NewShapeWithNullPtr)
  {
    std::shared_ptr < rebrin::Shape > rect1 = nullptr;
    BOOST_CHECK_THROW(rebrin::CompositeShape comp(rect1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(AddEmptyShape)
  {
    rebrin::Rectangle rect1({12.0, 10.0, 0.0, 0.0});
    rebrin::CompositeShape comp(std::make_shared < rebrin::Rectangle > (rect1));
    std::shared_ptr < rebrin::Shape > rect2 = nullptr;
    BOOST_CHECK_THROW(comp.addShape(rect2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(RemoveNonexistentShape)
  {
    rebrin::Rectangle rect1({12.0, 10.0, 0.0, 0.0});
    rebrin::CompositeShape comp(std::make_shared < rebrin::Rectangle > (rect1));
    BOOST_CHECK_THROW(comp.removeShape(2), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()
