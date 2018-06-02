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
    BOOST_CHECK_THROW(dudina::Rectangle rectangle({ 1, 1 }, -5.0, 1.0), std::invalid_argument);
    BOOST_CHECK_THROW(dudina::Rectangle rectangle({ 1, 1 }, 1.0, -10.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TEST_SIZES_AFTER_MOVE_TO_POINT)
  {
    dudina::Rectangle rectangle({ 1, 1 }, 1.0, 1.0);
    double rectanWidthBeforeMove = rectangle.getFrameRect().width;
    double rectanHeightBeforeMove = rectangle.getFrameRect().height;
    double rectanAreaBeforeMove = rectangle.getArea();

    rectangle.move({ 2, 2 });
    BOOST_CHECK_CLOSE(rectanWidthBeforeMove, rectangle.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE(rectanHeightBeforeMove, rectangle.getFrameRect().height, accuracy);
    BOOST_CHECK_CLOSE(rectanAreaBeforeMove, rectangle.getArea(), accuracy);

}

  BOOST_AUTO_TEST_CASE(TEST_SIZES_AFTER_MOVE_BY_dx_and_dy)
  {
    dudina::Rectangle rectangle({ 1.0, 1.0 }, 1.0, 1.0);
    double rectWidthBeforeMove = rectangle.getFrameRect().width;
    double rectHeightBeforeMove = rectangle.getFrameRect().height;
    double rectAreaBeforeMove = rectangle.getArea();

    rectangle.move(2, 2);
    BOOST_CHECK_CLOSE(rectWidthBeforeMove, rectangle.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE(rectHeightBeforeMove, rectangle.getFrameRect().height, accuracy);
    BOOST_CHECK_CLOSE(rectAreaBeforeMove, rectangle.getArea(), accuracy);

  }

  BOOST_AUTO_TEST_CASE(TEST_SCALE)
  {
    dudina::Rectangle rectangle({ 1.0, 1.0 }, 1.0, 1.0);
    double recAreaBeforeScale = rectangle.getArea();
    double recWidthBeforeScale = rectangle.getFrameRect().width;
    double recHeightBeforeScale = rectangle.getFrameRect().height;
    double coeffi = 2.0;
     
    rectangle.scale(coeffi);

    BOOST_CHECK_CLOSE(coeffi * coeffi * recAreaBeforeScale, rectangle.getArea(), accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, coeffi * recWidthBeforeScale, accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, coeffi * recHeightBeforeScale, accuracy);
    BOOST_CHECK_CLOSE(rectangle.getArea(), coeffi * coeffi * recAreaBeforeScale, accuracy);
    BOOST_CHECK_THROW(rectangle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(CIRCLE_TESTS)
  const double accuracy = 0.01;

  BOOST_AUTO_TEST_CASE(TEST_CONSTRUCTOR)
  {
    BOOST_CHECK_THROW(dudina::Circle circle({ 1, 1 }, -10.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TEST_SIZES_AFTER_MOVE_TO_POINT)
  {
    dudina:: Circle circle({ -1.0, 1.0 }, 5.0);
    double circleWidthBeforeMove = circle.getFrameRect().width;
    double circleHeightBeforeMove = circle.getFrameRect().height;
    double circleAreaBeforeMove = circle.getArea();

    circle.move({ 2.0, 2.0 });

    BOOST_CHECK_CLOSE(circleWidthBeforeMove, circle.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE(circleHeightBeforeMove, circle.getFrameRect().height, accuracy);
    BOOST_CHECK_CLOSE(circleAreaBeforeMove, circle.getArea(), accuracy);

  }

  BOOST_AUTO_TEST_CASE(TEST_SIZES_AFTER_MOVE_BY_dx_and_dy)
  {
    dudina::Circle circle({ -1.0, 1.0 }, 5.0);
    double circlWidthBeforeMove = circle.getFrameRect().width;
    double circlHeightBeforeMove = circle.getFrameRect().height;
    double circlAreaBeforeMove = circle.getArea();

    circle.move(2.0, 2.0);

    BOOST_CHECK_CLOSE(circlWidthBeforeMove, circle.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE(circlHeightBeforeMove, circle.getFrameRect().height, accuracy);
    BOOST_CHECK_CLOSE(circlAreaBeforeMove, circle.getArea(), accuracy);

  }

  BOOST_AUTO_TEST_CASE(TEST_SCALE)
  {
    dudina::Circle circle({ -1.0, -1.0 }, 2.0);
  
    double circleWidthBeforeScale = circle.getFrameRect().width;
    double circleHeightBeforeScale = circle.getFrameRect().height;
    double circleAreaBeforeScale = circle.getArea(); 
    double coef = 3.0;

    circle.scale(coef);

    BOOST_CHECK_CLOSE(circle.getFrameRect().width,  coef * circleWidthBeforeScale, accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height,  coef * circleHeightBeforeScale, accuracy);
    BOOST_CHECK_CLOSE(circle.getArea(),  coef * coef * circleAreaBeforeScale, accuracy);
    BOOST_CHECK_THROW(circle.scale(-3.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TRIANGLE_TESTS)
  const double accuracy = 0.01;

  BOOST_AUTO_TEST_CASE(TEST_SIZES_AFTER_MOVE_TO_POINT)
  {
    dudina::Triangle triangle({ 0.0, 0.0 }, { 6.0, 12.0 }, { 12.0, 0.0 });
    double trianglWidthBeforeMove = triangle.getFrameRect().width;
    double trianglHeightBeforeMove = triangle.getFrameRect().height;
    double trianglAreaBeforeMove = triangle.getArea();

    triangle.move({ 5.0, 5.0 });

    BOOST_CHECK_CLOSE(trianglWidthBeforeMove, triangle.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE(trianglHeightBeforeMove, triangle.getFrameRect().height, accuracy);
    BOOST_CHECK_CLOSE(trianglAreaBeforeMove, triangle.getArea(), accuracy);

  }

  BOOST_AUTO_TEST_CASE(TEST_SIZES_AFTER_MOVE_BY_dx_and_dy)
  {
    dudina::Triangle triangle({ 0.0, 0.0 }, { 6.0, 12.0 }, { 12.0, 0.0 });
    double triangleWidthBeforeMove = triangle.getFrameRect().width;
    double triangleHeightBeforeMove = triangle.getFrameRect().height;
    double triangleAreaBeforeMove = triangle.getArea();

    triangle.move(1.0, 1.0);

    BOOST_CHECK_CLOSE(triangleWidthBeforeMove, triangle.getFrameRect().width, accuracy);
    BOOST_CHECK_CLOSE(triangleHeightBeforeMove, triangle.getFrameRect().height, accuracy);
    BOOST_CHECK_CLOSE(triangleAreaBeforeMove, triangle.getArea(), accuracy);

  }

  BOOST_AUTO_TEST_CASE(TEST_SCALE)
  {
    dudina::Triangle triangle({ 0.0, 0.0 }, { 6.0, 12.0 }, { 12.0, 0.0 });
    double  coefficient_ = 2.0;
    double trianglWidthBeforeScale = triangle.getFrameRect().width;
    double trianglHeightBeforeScale = triangle.getFrameRect().height;
    double trianglAreaBeforeScale = triangle.getArea();
 
    triangle.scale(coefficient_);

    BOOST_CHECK_CLOSE(coefficient_ * coefficient_ * trianglAreaBeforeScale, triangle.getArea(), accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, coefficient_ * trianglWidthBeforeScale, accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, coefficient_ * trianglHeightBeforeScale, accuracy);
    BOOST_CHECK_THROW(triangle.scale(-2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_SUITE_END()
