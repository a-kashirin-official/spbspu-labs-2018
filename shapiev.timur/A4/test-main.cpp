#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include <memory>

const double EPS = 0.001;

BOOST_AUTO_TEST_SUITE(Rotate_Tests)

  BOOST_AUTO_TEST_CASE(CircleTest)
  {
    shapiev::Circle circle({5.0, 7.0}, 14.0);
    shapiev::rectangle_t circBefore = circle.getFrameRect();
    circle.rotate(180.0);
    shapiev::rectangle_t rectAfter = circle.getFrameRect();
    BOOST_CHECK_CLOSE(circBefore.height, rectAfter.height, EPS);
    BOOST_CHECK_CLOSE(circBefore.width, rectAfter.width, EPS);
    BOOST_CHECK_CLOSE(circBefore.pos.x, rectAfter.pos.x, EPS);
    BOOST_CHECK_CLOSE(circBefore.pos.y, rectAfter.pos.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(RectangleTest)
  {
    shapiev::Rectangle rectangle({5.0, 10.0, {10.0, 25.0}});
    rectangle.rotate(180.0);
    shapiev::rectangle_t RectAfter = rectangle.getFrameRect();
    BOOST_REQUIRE_CLOSE_FRACTION(RectAfter.width, 5.0, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(RectAfter.height, 10.0, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(RectAfter.pos.x, 10.0, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(RectAfter.pos.y, 25.0, EPS);
  }
BOOST_AUTO_TEST_SUITE_END()  

BOOST_AUTO_TEST_SUITE(Matrix_Tests)

  BOOST_AUTO_TEST_CASE(AddShapeTest)
  {
  shapiev::Rectangle rect2(3.0, 4.0, { 5.0,6.0 });
  std::shared_ptr<shapiev::Shape> rectPtr2 = std::make_shared<shapiev::Rectangle>(rect2);
  shapiev::Circle circle2({-2.0, -3.0}, 1.0);
  std::shared_ptr<shapiev::Shape> circPtr2 = std::make_shared<shapiev::Circle>(circle2);

  shapiev::Matrix matr;
  matr.addShape(rectPtr2);
  matr.addShape(circPtr2);
    BOOST_REQUIRE_EQUAL(matr[0][0], rectPtr2);
    BOOST_REQUIRE_EQUAL(matr[0][1], circPtr2);
  }

  BOOST_AUTO_TEST_CASE(AddCompositeShapeTest)
  {
    shapiev::Rectangle rect4(5.0, 6.0, { 5.0,0.0 });
    std::shared_ptr<shapiev::Shape> rectPtr4 = std::make_shared<shapiev::Rectangle>(rect4);
    shapiev::Circle circle4({ -5.0, -2.0 }, 4.0);
    std::shared_ptr<shapiev::Shape> circPtr4 = std::make_shared<shapiev::Circle>(circle4);
    shapiev::Matrix matr1;
    shapiev::CompositeShape comp2;
    comp2.addShape(rectPtr4);
    comp2.addShape(circPtr4);


    std::shared_ptr<shapiev::Shape> comp2Ptr
        = std::make_shared<shapiev::CompositeShape>(comp2);
    matr1.addShape(comp2Ptr);

    BOOST_REQUIRE_EQUAL(matr1[0][0], comp2Ptr);
  }


BOOST_AUTO_TEST_SUITE_END()


