#define BOOST_TEST_MAIN

#include <stdexcept>
#include <math.h>
#include <memory>
#include <boost/test/included/unit_test.hpp>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

const double ACCURACY = 0.00001;

BOOST_AUTO_TEST_SUITE(CompositeShapeTestSuite)

  BOOST_AUTO_TEST_CASE(ConstructorCopyTest)
  {
    lysenko::Rectangle rectangle({0.0,0.0}, 3.0, 1.0);
    std::shared_ptr<lysenko::Shape> rectangleptr = std::make_shared <lysenko::Rectangle>(rectangle);
    lysenko::Circle circle({0.0,0.0}, 1.0);
    std::shared_ptr<lysenko::Shape> circleptr = std::make_shared <lysenko::Circle>(circle);
    lysenko::CompositeShape compositeshape(rectangleptr);
    compositeshape.addShape(circleptr);
    lysenko::rectangle_t frameRect = compositeshape.getFrameRect();
    lysenko::CompositeShape compositeshape2(compositeshape);
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().height, frameRect.height, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().width, frameRect.width, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().pos.x, frameRect.pos.x, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().pos.y, frameRect.pos.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(ConstructorMoveTest)
  {
    lysenko::Rectangle rectangle({0.0,0.0}, 3.0, 1.0);
    std::shared_ptr<lysenko::Shape> rectangleptr = std::make_shared <lysenko::Rectangle>(rectangle);
    lysenko::Circle circle({0.0,0.0}, 1.0);
    std::shared_ptr<lysenko::Shape> circleptr = std::make_shared <lysenko::Circle>(circle);
    lysenko::CompositeShape compositeshape(rectangleptr);
    compositeshape.addShape(circleptr);
    lysenko::rectangle_t frameRect = compositeshape.getFrameRect();
    lysenko::CompositeShape compositeshape2(std::move(compositeshape));
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().height, frameRect.height, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().width, frameRect.width, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().pos.x, frameRect.pos.x, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().pos.y, frameRect.pos.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(OperatorCopyTest)
  {
    lysenko::Rectangle rectangle({0.0,0.0}, 3.0, 1.0);
    std::shared_ptr<lysenko::Shape> rectangleptr = std::make_shared <lysenko::Rectangle>(rectangle);
    lysenko::Circle circle({0.0,0.0}, 1.0);
    std::shared_ptr<lysenko::Shape> circleptr = std::make_shared <lysenko::Circle>(circle);
    lysenko::CompositeShape compositeshape(rectangleptr);
    compositeshape.addShape(circleptr);
    lysenko::rectangle_t frameRect = compositeshape.getFrameRect();
    lysenko::CompositeShape compositeshape2(circleptr);
    compositeshape2 = compositeshape;
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().height, frameRect.height, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().width, frameRect.width, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().pos.x, frameRect.pos.x, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().pos.y, frameRect.pos.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(OperatorMoveTest)
  {
    lysenko::Rectangle rectangle({0.0,0.0}, 3.0, 1.0);
    std::shared_ptr<lysenko::Shape> rectangleptr = std::make_shared <lysenko::Rectangle>(rectangle);
    lysenko::Circle circle({0.0,0.0}, 1.0);
    std::shared_ptr<lysenko::Shape> circleptr = std::make_shared <lysenko::Circle>(circle);
    lysenko::CompositeShape compositeshape(rectangleptr);
    compositeshape.addShape(circleptr);
    lysenko::rectangle_t frameRect = compositeshape.getFrameRect();
    lysenko::CompositeShape compositeshape2(circleptr);
    compositeshape2 = std::move(compositeshape);
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().height, frameRect.height, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().width, frameRect.width, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().pos.x, frameRect.pos.x, ACCURACY);
    BOOST_CHECK_CLOSE(compositeshape2.getFrameRect().pos.y, frameRect.pos.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(MoveTest)
  {
    lysenko::Rectangle rectangle({0.0,0.0}, 3.0, 1.0);
    std::shared_ptr<lysenko::Shape> rectangleptr = std::make_shared <lysenko::Rectangle>(rectangle);
    lysenko::Circle circle({0.0,0.0}, 1.0);
    std::shared_ptr<lysenko::Shape> circleptr = std::make_shared <lysenko::Circle>(circle);
    lysenko::CompositeShape compositeshape(rectangleptr);
    compositeshape.addShape(circleptr);
    compositeshape.move(1.0, 1.0);
    BOOST_CHECK_CLOSE(1.0, compositeshape.getFrameRect().pos.x, ACCURACY);
    BOOST_CHECK_CLOSE(1.0, compositeshape.getFrameRect().pos.y, ACCURACY);
    BOOST_CHECK_CLOSE(2.0, compositeshape.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(3.0, compositeshape.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getArea()+circle.getArea(), compositeshape.getArea(), ACCURACY);

    compositeshape.move({0.0, 0.0});
    BOOST_CHECK_CLOSE(0.0, compositeshape.getFrameRect().pos.x, ACCURACY);
    BOOST_CHECK_CLOSE(0.0, compositeshape.getFrameRect().pos.y, ACCURACY);
    BOOST_CHECK_CLOSE(2.0, compositeshape.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(3.0, compositeshape.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(rectangle.getArea()+circle.getArea(), compositeshape.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    lysenko::Rectangle rectangle({0.0,0.0}, 3.0, 1.0);
    std::shared_ptr<lysenko::Shape> rectangleptr = std::make_shared <lysenko::Rectangle>(rectangle);
    lysenko::Circle circle({0.0,0.0}, 1.0);
    std::shared_ptr<lysenko::Shape> circleptr = std::make_shared <lysenko::Circle>(circle);
    lysenko::CompositeShape compositeshape(rectangleptr);
    compositeshape.addShape(circleptr);
    lysenko::rectangle_t frameRect = compositeshape.getFrameRect();
    compositeshape.scale(2);
    BOOST_CHECK_CLOSE(frameRect.height*2.0, compositeshape.getFrameRect().height, ACCURACY);
    BOOST_CHECK_CLOSE(frameRect.width*2.0, compositeshape.getFrameRect().width, ACCURACY);
    BOOST_CHECK_CLOSE(frameRect.pos.x, compositeshape.getFrameRect().pos.x, ACCURACY);
    BOOST_CHECK_CLOSE(frameRect.pos.y, compositeshape.getFrameRect().pos.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(InvalidScaleTest)
  {
    lysenko::Rectangle rectangle({0.0,0.0}, 3.0, 1.0);
    std::shared_ptr<lysenko::Shape> rectangleptr = std::make_shared <lysenko::Rectangle>(rectangle);
    lysenko::CompositeShape compositeshape(rectangleptr);
    BOOST_CHECK_THROW(compositeshape.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
