#define BOOST_TEST_MODULE COMPOSITE_SHAPE

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

const double epsilon = 1e-4;
const double ratio = 3;

BOOST_AUTO_TEST_SUITE(CompositeShapeTest)

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    auto rect = std::make_shared<babintseva::Rectangle>(babintseva::point_t{5, 5}, 5, 5);

    auto cir = std::make_shared<babintseva::Circle>(babintseva::point_t{4, 4}, 4);

    babintseva::CompositeShape compShape(rect);

    compShape.addShape(cir);

    const double areaBefore = compShape.getArea();

    compShape.move({8, 1});

    BOOST_CHECK_CLOSE(compShape.getArea(), areaBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(RelativeMoving)
  {
    auto rect = std::make_shared<babintseva::Rectangle>(babintseva::point_t{5, 5}, 5, 5);

    auto cir = std::make_shared<babintseva::Circle>(babintseva::point_t{4, 4}, 4);

    babintseva::CompositeShape compShape(rect);

    compShape.addShape(cir);

    const double areaBefore = compShape.getArea();

    compShape.move(8, 1);

    BOOST_CHECK_CLOSE(compShape.getArea(), areaBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(WrongCreation)
  {
    BOOST_CHECK_THROW(babintseva::CompositeShape compShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ParametersAfterMoving)
  {
    auto rect = std::make_shared<babintseva::Rectangle>(babintseva::point_t{5, 5}, 5, 5);

    auto cir = std::make_shared<babintseva::Circle>(babintseva::point_t{4, 4}, 4);

    babintseva::CompositeShape compShape(rect);

    compShape.addShape(cir);

    const double widthBefore = compShape.getFrameRect().width;
    const double heightBefore = compShape.getFrameRect().height;

    compShape.move ({6, 6});

    BOOST_CHECK_CLOSE(compShape.getFrameRect().width, widthBefore, epsilon);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().height, heightBefore, epsilon);

    compShape.move (8, 1);

    BOOST_CHECK_CLOSE(compShape.getFrameRect().width, widthBefore, epsilon);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().height, heightBefore, epsilon);
  }

  BOOST_AUTO_TEST_CASE(ParametersAfterScaling)
  {
    auto rect = std::make_shared<babintseva::Rectangle>(babintseva::point_t{5, 5}, 5, 5);

    auto cir = std::make_shared<babintseva::Circle>(babintseva::point_t{4, 4}, 4);

    babintseva::CompositeShape compShape(rect);

    compShape.addShape(cir);

    const double areaBefore = compShape.getArea();
    const double widthBefore = compShape.getFrameRect().width;
    const double heightBefore = compShape.getFrameRect().height;
    babintseva::rectangle_t coordinatesBefore = compShape.getFrameRect();

    compShape.scale(ratio);

    BOOST_CHECK_CLOSE(compShape.getArea(), areaBefore * ratio * ratio, epsilon);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().width, widthBefore * ratio, epsilon);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().height, heightBefore * ratio, epsilon);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.x, coordinatesBefore.pos.x, epsilon);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.y, coordinatesBefore.pos.y, epsilon);
  }

  BOOST_AUTO_TEST_CASE(WrongAddingTest)
  {
    auto rect = std::make_shared<babintseva::Rectangle>(babintseva::point_t{5, 5}, 5, 5);

    auto cir = std::make_shared<babintseva::Circle>(babintseva::point_t{4, 4}, 4);

    babintseva::CompositeShape compShape(rect);

    BOOST_CHECK_THROW(compShape.addShape(nullptr), std::invalid_argument);
  }
  
  BOOST_AUTO_TEST_CASE(CopyConstructor)
  {
    auto rect = std::make_shared<babintseva::Rectangle>(babintseva::point_t{5, 5}, 5, 5);
    auto cir = std::make_shared<babintseva::Circle>(babintseva::point_t{4, 4}, 4);
    babintseva::CompositeShape compShape(rect);
    compShape.addShape(cir);
    BOOST_CHECK_NO_THROW(babintseva::CompositeShape compShapeCopy(compShape));
  }
  
  BOOST_AUTO_TEST_CASE(CopyOperator)
  {
    auto rect = std::make_shared<babintseva::Rectangle>(babintseva::point_t{5, 5}, 5, 5);
    auto cir = std::make_shared<babintseva::Circle>(babintseva::point_t{4, 4}, 4);
    babintseva::CompositeShape compShape(rect);
    compShape.addShape(cir);
    BOOST_CHECK_NO_THROW(babintseva::CompositeShape compShapeCopy = compShape);
  }

BOOST_AUTO_TEST_SUITE_END()
