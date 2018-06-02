#define BOOST_TEST_MODULE Main
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>

const double EPSILON = 1e-4;

BOOST_AUTO_TEST_SUITE(CompositeShapeSuite)

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    dumaev::Circle circle({1, 1}, 9);
    dumaev::Rectangle rectangle({0, 0}, 20, 15);
    std::shared_ptr<dumaev::Shape> circlePtr = std::make_shared<dumaev::Circle>(circle);
    std::shared_ptr<dumaev::Shape> rectanglePtr = std::make_shared<dumaev::Rectangle>(rectangle);
    dumaev::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);

    const double areaBefore = compositeShape.getArea();

    compositeShape.move({2, 3});

    BOOST_CHECK_CLOSE(areaBefore, compositeShape.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MoveOn)
  {
    dumaev::Circle circle({2, 2}, 2);
    dumaev::Rectangle rectangle({0, 0}, 20, 15);
    std::shared_ptr<dumaev::Shape> circlePtr = std::make_shared<dumaev::Circle>(circle);
    std::shared_ptr<dumaev::Shape> rectanglePtr = std::make_shared<dumaev::Rectangle>(rectangle);
    dumaev::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);

    const double areaBefore = compositeShape.getArea();

    compositeShape.move(2, 3);

    BOOST_CHECK_CLOSE(areaBefore, compositeShape.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(IncorrectCreation)
  {
    BOOST_CHECK_THROW(dumaev::CompositeShape compositeShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(IncorrectAddition)
  {
    dumaev::Circle circle({2, 2}, 2);
    std::shared_ptr<dumaev::Shape> circlePtr = std::make_shared<dumaev::Circle>(circle);
    dumaev::CompositeShape compositeShape(circlePtr);
    BOOST_CHECK_THROW(compositeShape.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(ParametersAfterScaling)
  {
    dumaev::Circle circle({2, 2}, 2);
    dumaev::Rectangle rectangle({0, 0}, 20, 15);
    std::shared_ptr<dumaev::Shape> circlePtr = std::make_shared<dumaev::Circle>(circle);
    std::shared_ptr<dumaev::Shape> rectanglePtr = std::make_shared<dumaev::Rectangle>(rectangle);
    dumaev::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);

    const double areaBefore = compositeShape.getArea();
    const double heightBefore = compositeShape.getFrameRect().height;
    const double widthBefore = compositeShape.getFrameRect().width;
    dumaev::rectangle_t coordinatesBefore = compositeShape.getFrameRect();

    compositeShape.scale(2);

    BOOST_CHECK_CLOSE(areaBefore * 2 * 2, compositeShape.getArea(), EPSILON);
    BOOST_CHECK_CLOSE(heightBefore * 2, compositeShape.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(widthBefore * 2, compositeShape.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(coordinatesBefore.pos.x, compositeShape.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(coordinatesBefore.pos.y, compositeShape.getFrameRect().pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ParametersAfterMoving)
  {
    dumaev::Circle circle({2, 2}, 2);
    dumaev::Rectangle rectangle({0, 0}, 20, 15);
    std::shared_ptr<dumaev::Shape> circlePtr = std::make_shared<dumaev::Circle>(circle);
    std::shared_ptr<dumaev::Shape> rectanglePtr = std::make_shared<dumaev::Rectangle>(rectangle);
    dumaev::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);

    const double widthBefore = compositeShape.getFrameRect().width;
    const double heightBefore = compositeShape.getFrameRect().height;

    compositeShape.move({3, 3});

    BOOST_CHECK_CLOSE(widthBefore, compositeShape.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(heightBefore, compositeShape.getFrameRect().height, EPSILON);

    compositeShape.move(3, 3);

    BOOST_CHECK_CLOSE(widthBefore, compositeShape.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(heightBefore, compositeShape.getFrameRect().height, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
  {
    dumaev::Circle circle({2, 2}, 2);
    dumaev::Rectangle rectangle({0, 0}, 20, 15);
    std::shared_ptr<dumaev::Shape> circlePtr = std::make_shared<dumaev::Circle>(circle);
    std::shared_ptr<dumaev::Shape> rectanglePtr = std::make_shared<dumaev::Rectangle>(rectangle);
    dumaev::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);

    BOOST_CHECK_THROW(compositeShape.scale(-2), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(CopyConstructor)
  {
    dumaev::Circle circle({1, 1}, 9);
    dumaev::Rectangle rectangle({0, 0}, 20, 15);
    std::shared_ptr<dumaev::Shape> circlePtr = std::make_shared<dumaev::Circle>(circle);
    std::shared_ptr<dumaev::Shape> rectanglePtr = std::make_shared<dumaev::Rectangle>(rectangle);
    dumaev::CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);

    BOOST_CHECK_NO_THROW(dumaev::CompositeShape compositeShapeCopy(compositeShape));
  }
  BOOST_AUTO_TEST_CASE(CopyOperator)
  {
    dumaev::Circle circle({1, 1}, 9);
    dumaev::Rectangle rectangle({0, 0}, 20, 15);
    std::shared_ptr<dumaev::Shape> circlePtr = std::make_shared<dumaev::Circle>(circle);
    std::shared_ptr<dumaev::Shape> rectanglePtr = std::make_shared<dumaev::Rectangle>(rectangle);
    dumaev::CompositeShape compositeShape(circlePtr);
    BOOST_CHECK_NO_THROW(dumaev::CompositeShape compositeShapeCopy = compositeShape);
  }

BOOST_AUTO_TEST_SUITE_END()
