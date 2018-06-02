#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"


BOOST_AUTO_TEST_SUITE(RECTANGLE_TESTS)
 const double accuracy = 0.0001;

  BOOST_AUTO_TEST_CASE(TEST_CONSTRUCTOR)
  {
    BOOST_CHECK_THROW(sorvenkov::Rectangle rectangle(-5.0 , 1.0 ,{1.0, 1.0 }), std::invalid_argument);
    BOOST_CHECK_THROW(sorvenkov::Rectangle rectangle( 1.0, -3.0 ,{1.0, 1.0 }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TEST_SIZES_AFTER_MOVE_TO_POINT)
  {
    sorvenkov::Rectangle rectangle( 1.0, 1.0 , {1.0, 1.0 });
    double rectanWidthBeforeMove = rectangle.getFrameRect().width;
    double rectanHeightBeforeMove = rectangle.getFrameRect().height;
    double rectanAreaBeforeMove = rectangle.getArea();

    rectangle.move({ 2.0, 2.0 });
    BOOST_CHECK_CLOSE_FRACTION(rectanWidthBeforeMove, rectangle.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(rectanHeightBeforeMove, rectangle.getFrameRect().height, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(rectanAreaBeforeMove, rectangle.getArea(), accuracy);

}

  BOOST_AUTO_TEST_CASE(TEST_SIZES_AFTER_MOVE_BY_dx_and_dy)
  {
    sorvenkov::Rectangle rectangle( 1.0, 1.0 ,{1.0, 1.0 });
    double rectWidthBeforeMove = rectangle.getFrameRect().width;
    double rectHeightBeforeMove = rectangle.getFrameRect().height;
    double rectAreaBeforeMove = rectangle.getArea();

    rectangle.move(2.0, 2.0);
    BOOST_CHECK_CLOSE_FRACTION(rectWidthBeforeMove, rectangle.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(rectHeightBeforeMove, rectangle.getFrameRect().height, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(rectAreaBeforeMove, rectangle.getArea(), accuracy);

  }

  BOOST_AUTO_TEST_CASE(TEST_SCALE)
  {
    sorvenkov::Rectangle rectangle( 1.0, 1.0 ,{1.0, 1.0});
    double recAreaBeforeScale = rectangle.getArea();
    double recWidthBeforeScale = rectangle.getFrameRect().width;
    double recHeightBeforeScale = rectangle.getFrameRect().height;
    double ratios = 2.0;

    rectangle.scale(ratios);

    BOOST_CHECK_CLOSE_FRACTION(ratios * ratios * recAreaBeforeScale, rectangle.getArea(), accuracy);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getFrameRect().width, ratios * recWidthBeforeScale, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getFrameRect().height, ratios * recHeightBeforeScale, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), ratios * ratios * recAreaBeforeScale, accuracy);
    BOOST_CHECK_THROW(rectangle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(CIRCLE_TESTS)
  const double accuracy = 0.01;

  BOOST_AUTO_TEST_CASE(TEST_CONSTRUCTOR)
  {
    BOOST_CHECK_THROW(sorvenkov::Circle circle(-3.0 ,{1.0 ,1.0 }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TEST_SIZES_AFTER_MOVE_TO_POINT)
  {
    sorvenkov:: Circle circle( 5.0, {-1.0, 1.0 });
    double circleWidthBeforeMove = circle.getFrameRect().width;
    double circleHeightBeforeMove = circle.getFrameRect().height;
    double circleAreaBeforeMove = circle.getArea();

    circle.move({ 2.0, 2.0 });

    BOOST_CHECK_CLOSE_FRACTION(circleWidthBeforeMove, circle.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(circleHeightBeforeMove, circle.getFrameRect().height, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(circleAreaBeforeMove, circle.getArea(), accuracy);

  }

  BOOST_AUTO_TEST_CASE(TEST_SIZES_AFTER_MOVE_BY_dx_and_dy)
  {
    sorvenkov::Circle circle( 5.0, { -1.0, 1.0 });
    double circlWidthBeforeMove = circle.getFrameRect().width;
    double circlHeightBeforeMove = circle.getFrameRect().height;
    double circlAreaBeforeMove = circle.getArea();

    circle.move(2.0, 2.0);

    BOOST_CHECK_CLOSE_FRACTION(circlWidthBeforeMove, circle.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(circlHeightBeforeMove, circle.getFrameRect().height, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(circlAreaBeforeMove, circle.getArea(), accuracy);

  }

  BOOST_AUTO_TEST_CASE(TEST_SCALE)
  {
    sorvenkov::Circle circle(2.0, { -1.0, -1.0 });
  
    double circleWidthBeforeScale = circle.getFrameRect().width;
    double circleHeightBeforeScale = circle.getFrameRect().height;
    double circleAreaBeforeScale = circle.getArea(); 
    double ratioc = 3.0;

    circle.scale(ratioc);

    BOOST_CHECK_CLOSE_FRACTION(circle.getFrameRect().width,  ratioc * circleWidthBeforeScale, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(circle.getFrameRect().height,  ratioc * circleHeightBeforeScale, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(),  ratioc * ratioc * circleAreaBeforeScale, accuracy);
    BOOST_CHECK_THROW(circle.scale(-3.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TRIANGLE_TESTS)
  const double accuracy = 0.01;

  BOOST_AUTO_TEST_CASE(TEST_SIZES_AFTER_MOVE_TO_POINT)
  {
    sorvenkov::Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });
    double trianglWidthBeforeMove = triangle.getFrameRect().width;
    double trianglHeightBeforeMove = triangle.getFrameRect().height;
    double trianglAreaBeforeMove = triangle.getArea();

    triangle.move({ 5.0, 5.0 });

    BOOST_CHECK_CLOSE_FRACTION(trianglWidthBeforeMove, triangle.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(trianglHeightBeforeMove, triangle.getFrameRect().height, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(trianglAreaBeforeMove, triangle.getArea(), accuracy);

  }

  BOOST_AUTO_TEST_CASE(TEST_SIZES_AFTER_MOVE_BY_dx_and_dy)
  {
    sorvenkov::Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });
    double triangleWidthBeforeMove = triangle.getFrameRect().width;
    double triangleHeightBeforeMove = triangle.getFrameRect().height;
    double triangleAreaBeforeMove = triangle.getArea();

    triangle.move(1.0, 1.0);

    BOOST_CHECK_CLOSE_FRACTION(triangleWidthBeforeMove, triangle.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(triangleHeightBeforeMove, triangle.getFrameRect().height, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(triangleAreaBeforeMove, triangle.getArea(), accuracy);

  }

  BOOST_AUTO_TEST_CASE(TEST_SCALE)
  {
    sorvenkov::Triangle triangle({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });
    double ratioscient_ = 2.0;
    double trianglWidthBeforeScale = triangle.getFrameRect().width;
    double trianglHeightBeforeScale = triangle.getFrameRect().height;
    double trianglAreaBeforeScale = triangle.getArea();

    triangle.scale(ratioscient_);

    BOOST_CHECK_CLOSE_FRACTION(ratioscient_ * ratioscient_ * trianglAreaBeforeScale, triangle.getArea(), accuracy);
    BOOST_CHECK_CLOSE_FRACTION(triangle.getFrameRect().width, ratioscient_ * trianglWidthBeforeScale, accuracy);
    BOOST_CHECK_CLOSE_FRACTION(triangle.getFrameRect().height, ratioscient_ * trianglHeightBeforeScale, accuracy);
    BOOST_CHECK_THROW(triangle.scale(-2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_SUITE_END()
