#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double EPS = 0.0001;

BOOST_AUTO_TEST_SUITE(RotateTests)

  BOOST_AUTO_TEST_CASE(RotateCircle)
  {
    shapovalova::Circle circle ({5.0, 5.0}, 20.0);
    shapovalova::rectangle_t frameRect = circle.getFrameRect();
    double area = circle.getArea();
    circle.rotate(180.0);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.width, circle.getFrameRect().width, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.height, circle.getFrameRect().height, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.pos.x, circle.getFrameRect().pos.x, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.pos.y, circle.getFrameRect().pos.y, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(area, circle.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(RotateRectangle)
  {
    shapovalova::Rectangle rectangle ({{5.0, 5.0}, 20.0, 6.0});
    shapovalova::rectangle_t frameRect = rectangle.getFrameRect();
    double area = rectangle.getArea();
    rectangle.rotate(180.0);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.width, rectangle.getFrameRect().width, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.height, rectangle.getFrameRect().height, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.pos.x, rectangle.getFrameRect().pos.x, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.pos.y, rectangle.getFrameRect().pos.y, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(area, rectangle.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(RotateCompositeShape)
  {
    std::shared_ptr<shapovalova::Shape> rectanglePtr =
        std::make_shared<shapovalova::Rectangle>(shapovalova::Rectangle ({{5.0, 5.0}, 20.0, 6.0}));
    shapovalova::CompositeShape List(rectanglePtr);
    shapovalova::rectangle_t frameRect = List.getFrameRect();
    double area = List.getArea();
    List.rotate(180.0);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.width, List.getFrameRect().width, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.height, List.getFrameRect().height, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.pos.x, List.getFrameRect().pos.x, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(frameRect.pos.y, List.getFrameRect().pos.y, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(area, List.getArea(), EPS);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixTests)

  BOOST_AUTO_TEST_CASE(InvalidConstructor)
  {
    BOOST_CHECK_THROW(shapovalova::Matrix matrix(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidAdd)
  {
    std::shared_ptr<shapovalova::Shape> rectanglePtr =
        std::make_shared<shapovalova::Rectangle>(shapovalova::Rectangle ({{5.0, 5.0}, 20.0, 6.0}));
    shapovalova::Matrix matrix(rectanglePtr);
    BOOST_CHECK_THROW(matrix.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MatrixTest)
  {
    std::shared_ptr<shapovalova::Shape> rectanglePtr1 =
        std::make_shared<shapovalova::Rectangle>(shapovalova::Rectangle ({{2.0, 2.0}, 8.0, 4.0}));
    std::shared_ptr<shapovalova::Shape> rectanglePtr2 =
        std::make_shared<shapovalova::Rectangle>(shapovalova::Rectangle ({{0.0, 8.0}, 2.0, 6.0}));
    std::shared_ptr<shapovalova::Shape> circlePtr1 =
        std::make_shared<shapovalova::Circle>(shapovalova::Circle ({9.0, 6.0}, 4.0));
    std::shared_ptr<shapovalova::Shape> circlePtr2 =
        std::make_shared<shapovalova::Circle>(shapovalova::Circle ({4.0, 7.0}, 4.0));
    shapovalova::Matrix matrix(rectanglePtr1);
    matrix.addShape(rectanglePtr2);
    matrix.addShape(circlePtr1);
    matrix.addShape(circlePtr2);
    std::unique_ptr<std::shared_ptr<shapovalova::Shape>[]> layer1 = matrix[0];
    std::unique_ptr<std::shared_ptr<shapovalova::Shape>[]> layer2 = matrix[1];
    std::unique_ptr<std::shared_ptr<shapovalova::Shape>[]> layer3 = matrix[2];
    BOOST_CHECK(layer1[0] == rectanglePtr1);
    BOOST_CHECK(layer1[1] == rectanglePtr2);
    BOOST_CHECK(layer2[0] == circlePtr1);
    BOOST_CHECK(layer2[1] == nullptr);
    BOOST_CHECK(layer3[0] == circlePtr2);
    BOOST_CHECK(layer3[1] == nullptr);
  }

BOOST_AUTO_TEST_SUITE_END()
