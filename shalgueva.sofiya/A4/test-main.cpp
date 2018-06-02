#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double EPSILON = 1e-3;

BOOST_AUTO_TEST_SUITE(RotateTests)

  BOOST_AUTO_TEST_CASE(RotateTestRectangle)
  {
    shalgueva::Rectangle rect({ 15.0, 10.0, {0.0, 0.0}});
    shalgueva::rectangle_t test = rect.getFrameRect();
    double tmpArea = rect.getArea();
    rect.rotate(180.0);
    BOOST_CHECK_CLOSE_FRACTION(test.width, rect.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(test.height, rect.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(rect.getArea(), tmpArea, EPSILON);
  }

 BOOST_AUTO_TEST_CASE(RotateTestCircle)
  {
    shalgueva::Circle circle({0.0, 0.0}, 10.0);
    shalgueva::rectangle_t test = circle.getFrameRect();
    double tmpArea = circle.getArea();
    circle.rotate(180.0);
    BOOST_CHECK_CLOSE_FRACTION(test.width, circle.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(test.height, circle.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), tmpArea, EPSILON);
  }


 BOOST_AUTO_TEST_CASE(RotateTestCompositeShape)
  {
    std::shared_ptr<shalgueva::Shape> rect1 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::Rectangle({10.0, 10.0, {-15.0, 15.0}}));
    shalgueva::CompositeShape test(rect1);
    double tmpArea = test.getArea();
    shalgueva::rectangle_t tmpTest = test.getFrameRect();
    test.rotate(180.0);
    BOOST_CHECK_CLOSE_FRACTION(tmpTest.width, test.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(tmpTest.height, test.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(test.getArea(), tmpArea, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixTest)

  BOOST_AUTO_TEST_CASE(Matrix_Test)
  {
    shalgueva::Circle circle( { -2.0, -2.0 }, 2.0 );
    shalgueva::Rectangle rectangle1( {2.0, 2.0, { -2.0, 0.0 }} );
    shalgueva::Rectangle rectangle2({ 6.0, 3.0, { 1.0, 1.0 }} );
    shalgueva::Rectangle rectangle3( {2.0, 4.0, { 3.0, 1.0 } });
    shalgueva::Rectangle rectangle4( {4.0, 4.0, { 3.0, 3.0 } });

    std::shared_ptr<shalgueva::Shape> circlePtr = std::make_shared<shalgueva::Circle>(circle);
    std::shared_ptr<shalgueva::Shape> rectanglePtr1 = std::make_shared<shalgueva::Rectangle>(rectangle1);
    std::shared_ptr<shalgueva::Shape> rectanglePtr2 = std::make_shared<shalgueva::Rectangle>(rectangle2);
    std::shared_ptr<shalgueva::Shape> rectanglePtr3 = std::make_shared<shalgueva::Rectangle>(rectangle3);
    std::shared_ptr<shalgueva::Shape> rectanglePtr4 = std::make_shared<shalgueva::Rectangle>(rectangle4);

    shalgueva::Matrix matrix(circlePtr);
    matrix.addShape(rectanglePtr1);
    matrix.addShape(rectanglePtr2);
    matrix.addShape(rectanglePtr3);
    matrix.addShape(rectanglePtr4);

    std::unique_ptr<std::shared_ptr<shalgueva::Shape>[]> layer1 = matrix[0];
    std::unique_ptr<std::shared_ptr<shalgueva::Shape>[]> layer2 = matrix[1];
    std::unique_ptr<std::shared_ptr<shalgueva::Shape>[]> layer3 = matrix[2];

    BOOST_CHECK(layer1[0] == circlePtr);
    BOOST_CHECK(layer1[1] == rectanglePtr3);
    BOOST_CHECK(layer2[0] == rectanglePtr1);
    BOOST_CHECK(layer2[1] == rectanglePtr4);
    BOOST_CHECK(layer3[0] == rectanglePtr2);
  }


  BOOST_AUTO_TEST_CASE(CheckLayers)
  {
    std::shared_ptr<shalgueva::Shape> circle1 =
      std::make_shared<shalgueva::Circle>(shalgueva::Circle({3.0, 0.0}, 3.0));
    std::shared_ptr<shalgueva::Shape> circle2 =
      std::make_shared<shalgueva::Circle>(shalgueva::Circle({-5.0, -5.0}, 5.0));
    std::shared_ptr<shalgueva::Shape> rect1 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::Rectangle({8.0, 4.0, {0.0, 4.0}}));
    std::shared_ptr<shalgueva::Shape> rect2 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::Rectangle({6.0, 6.0, {-6.0, 1.0}}));
    std::shared_ptr<shalgueva::Shape> rect3 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::Rectangle({2.0, 2.0, {0.0, 0.0}}));
    shalgueva::Matrix matrix(circle1);
    matrix.addShape(circle2);
    matrix.addShape(rect1);
    matrix.addShape(rect2);
    matrix.addShape(rect3);
    size_t quantity = 3;
    BOOST_CHECK_EQUAL(quantity, matrix.getLayersNumber());
  }

BOOST_AUTO_TEST_SUITE_END()
