#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const double EPS = 0.0001;

BOOST_AUTO_TEST_SUITE(CompositeShapeTests)
  BOOST_AUTO_TEST_CASE(ImmutableParametersMoveByAxis)
  {
    std::shared_ptr<shapovalova::Shape> rectanglePtr =
        std::make_shared<shapovalova::Rectangle>(shapovalova::Rectangle ({{20.0, 10.0}, 20.0, 40.0}));
    shapovalova::CompositeShape List(rectanglePtr);
    std::shared_ptr<shapovalova::Shape> circlePtr =
        std::make_shared<shapovalova::Circle>(shapovalova::Circle ({40.0, 80.0}, 10.0));
    List.add(circlePtr);
    double area = List.getArea();
    double width = List.getFrameRect().width;
    double height = List.getFrameRect().height;
    List.move(15.0, 5.0);
    BOOST_REQUIRE_CLOSE_FRACTION(area, List.getArea(), EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(width, List.getFrameRect().width, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(height, List.getFrameRect().height, EPS);
  }

  BOOST_AUTO_TEST_CASE(ImmutableParametersMoveToPoint)
  {
    std::shared_ptr<shapovalova::Shape> rectanglePtr =
        std::make_shared<shapovalova::Rectangle>(shapovalova::Rectangle ({{20.0, 10.0}, 20.0, 40.0}));
    shapovalova::CompositeShape List(rectanglePtr);
    std::shared_ptr<shapovalova::Shape> circlePtr =
        std::make_shared<shapovalova::Circle>(shapovalova::Circle ({40.0, 80.0}, 10.0));
    List.add(circlePtr);
    double area = List.getArea();
    double width = List.getFrameRect().width;
    double height = List.getFrameRect().height;
    List.move({15.0, 5.0});
    BOOST_REQUIRE_CLOSE_FRACTION(area, List.getArea(), EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(width, List.getFrameRect().width, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(height, List.getFrameRect().height, EPS);
  }

  BOOST_AUTO_TEST_CASE(AreaScaling)
  {
    std::shared_ptr<shapovalova::Shape> rectanglePtr =
        std::make_shared<shapovalova::Rectangle>(shapovalova::Rectangle ({{20.0, 10.0}, 20.0, 40.0}));
    shapovalova::CompositeShape List(rectanglePtr);
    std::shared_ptr<shapovalova::Shape> circlePtr =
        std::make_shared<shapovalova::Circle>(shapovalova::Circle ({40.0, 80.0}, 10.0));
    List.add(circlePtr);
    double area = List.getArea();
    shapovalova::point_t pos = List.getFrameRect().pos;
    List.scale(2.0);
    BOOST_REQUIRE_CLOSE_FRACTION(List.getArea(), area * 2.0 * 2.0, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(List.getFrameRect().pos.x, pos.x, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(List.getFrameRect().pos.y, pos.y, EPS);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentOfConstructor)
  {
    std::shared_ptr<shapovalova::Shape> circlePtr = nullptr;
    BOOST_CHECK_THROW(shapovalova::CompositeShape List(circlePtr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentOfAddedElement)
  {
    std::shared_ptr<shapovalova::Shape> rectanglePtr =
        std::make_shared<shapovalova::Rectangle>(shapovalova::Rectangle ({{20.0, 10.0}, 20.0, 40.0}));
    shapovalova::CompositeShape List(rectanglePtr);
    std::shared_ptr<shapovalova::Shape> circlePtr = nullptr;
    BOOST_CHECK_THROW(List.add(circlePtr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentOfScaling)
  {
    std::shared_ptr<shapovalova::Shape> rectanglePtr =
        std::make_shared<shapovalova::Rectangle>(shapovalova::Rectangle ({{20.0, 10.0}, 20.0, 40.0}));
    shapovalova::CompositeShape List(rectanglePtr);
    std::shared_ptr<shapovalova::Shape> circlePtr =
        std::make_shared<shapovalova::Circle>(shapovalova::Circle ({40.0, 80.0}, 10.0));
    List.add(circlePtr);
    BOOST_CHECK_THROW(List.scale(-2.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(GeneralParameters)
  {
    std::shared_ptr<shapovalova::Shape> rectanglePtr =
        std::make_shared<shapovalova::Rectangle>(shapovalova::Rectangle ({{20.0, 10.0}, 20.0, 40.0}));
    shapovalova::CompositeShape List(rectanglePtr);
    BOOST_REQUIRE_EQUAL(rectanglePtr -> getFrameRect().width, List.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(rectanglePtr -> getFrameRect().height, List.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(rectanglePtr -> getFrameRect().pos.x, List.getFrameRect().pos.x);
    BOOST_REQUIRE_EQUAL(rectanglePtr -> getFrameRect().pos.y, List.getFrameRect().pos.y);
  }

  BOOST_AUTO_TEST_SUITE_END()
