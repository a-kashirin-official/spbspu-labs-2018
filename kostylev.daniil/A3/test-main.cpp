#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"


const double dx = 1e-8;

BOOST_AUTO_TEST_SUITE(CompositeShape_test)

  BOOST_AUTO_TEST_CASE(invalid_argument_add)
  {
    std::shared_ptr<kostylev::Shape> testRect =
      std::make_shared<kostylev::Rectangle>(kostylev::point_t{2.0, 4.0}, 10.0, 10.0 );
    kostylev::CompositeShape testObj(testRect);
    std::shared_ptr<kostylev::Shape> testCirc = nullptr;
    BOOST_CHECK_THROW(testObj.addShape(testCirc), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(invalid_argument_constructor_test)
  {
    std::shared_ptr<kostylev::Shape> testRect = nullptr;
    BOOST_CHECK_THROW(kostylev::CompositeShape testObj(testRect), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(invalid_parametrs_scaling)
  {
    std::shared_ptr<kostylev::Shape> testRect =
      std::make_shared<kostylev::Rectangle>(kostylev::point_t {2.0, 4.0}, 10.0, 10.0);
    kostylev::CompositeShape testObj(testRect);
    std::shared_ptr<kostylev::Shape> testCirc =
      std::make_shared<kostylev::Circle>(kostylev::point_t{0.0, 0.0},5.0);
    testObj.addShape(testCirc);
    BOOST_CHECK_THROW(testObj.scale(-2.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(scale_test)
  {
    std::shared_ptr<kostylev::Shape> testRect =
      std::make_shared<kostylev::Rectangle>(kostylev::point_t{2.0, 4.0}, 10.0, 10.0 );
    std::shared_ptr<kostylev::Shape> testCirc =
      std::make_shared<kostylev::Circle>(kostylev::point_t{0.0, 0.0},5.0);
    kostylev::CompositeShape testObj(testRect);
    testObj.addShape(testCirc);
    double tmpArea = testObj.getArea();
    kostylev::point_t positionBefore = testObj.getFrameRect().pos;
    testObj.scale(2.0);
    BOOST_CHECK_CLOSE(positionBefore.x, testObj.getFrameRect().pos.x, dx);
    BOOST_CHECK_CLOSE(positionBefore.y, testObj.getFrameRect().pos.y, dx);
    BOOST_CHECK_CLOSE(2.0 * 2.0 * tmpArea, testObj.getArea(), dx);
  }

  BOOST_AUTO_TEST_CASE(move_to_point)
  {
    std::shared_ptr<kostylev::Shape> testRect =
      std::make_shared<kostylev::Rectangle>(kostylev::point_t{3.0, 7.0}, 21.0, 10.0);
    std::shared_ptr<kostylev::Shape> testCirc =
      std::make_shared<kostylev::Circle>(kostylev::point_t{0.0, 0.0}, 5.0);
    kostylev::CompositeShape testObj(testRect);
    testObj.addShape(testCirc);
    double tmpHeight = testObj.getFrameRect().height;
    double tmpWidth = testObj.getFrameRect().width;
    double tmpArea = testObj.getArea();
    kostylev::point_t positionAfterMoving = {5.0, 5.0};
    testObj.move(positionAfterMoving);
    BOOST_CHECK_CLOSE(testObj.getFrameRect().pos.x, positionAfterMoving.x, dx);
    BOOST_CHECK_CLOSE(testObj.getFrameRect().pos.y, positionAfterMoving.y, dx);
    BOOST_CHECK_CLOSE(tmpHeight, testObj.getFrameRect().height, dx);
    BOOST_CHECK_CLOSE(tmpWidth, testObj.getFrameRect().width, dx);
    BOOST_CHECK_CLOSE(tmpArea, testObj.getArea(), dx);
  }

  BOOST_AUTO_TEST_CASE(move_by_axes)
  {
    std::shared_ptr<kostylev::Shape> testRect =
      std::make_shared<kostylev::Rectangle>(kostylev::point_t{2.0, 2.0}, 2.0, 2.0 );
    std::shared_ptr<kostylev::Shape> testCirc =
      std::make_shared<kostylev::Circle>(kostylev::point_t{0.0, 0.0},1.0);
    kostylev::CompositeShape testObj(testRect);
    testObj.addShape(testCirc);
    double tmpHeight = testObj.getFrameRect().height;
    double tmpWidth = testObj.getFrameRect().width;
    double tmpArea = testObj.getArea();
    kostylev::point_t positionAfterMoving = {4.0, 3.0};
    testObj.move(3.0, 2.0);
    BOOST_CHECK_CLOSE(testObj.getFrameRect().pos.x, positionAfterMoving.x, dx);
    BOOST_CHECK_CLOSE(testObj.getFrameRect().pos.y, positionAfterMoving.y, dx);
    BOOST_CHECK_CLOSE(tmpHeight, testObj.getFrameRect().height, dx);
    BOOST_CHECK_CLOSE(tmpWidth, testObj.getFrameRect().width, dx);
    BOOST_CHECK_CLOSE(tmpArea, testObj.getArea(), dx);
  }

  BOOST_AUTO_TEST_CASE(invariant_coordinates_test)
  {
    std::shared_ptr<kostylev::Shape> testRect =
      std::make_shared<kostylev::Rectangle>(kostylev::point_t{2.0, 4.0}, 10.0, 10.0 );
    kostylev::CompositeShape testObj(testRect);
    double posX = testObj.getFrameRect().pos.x;
    double posY = testObj.getFrameRect().pos.y;
    testObj.scale(2.0);
    BOOST_CHECK_CLOSE(testObj.getFrameRect().pos.x, posX, dx);
    BOOST_CHECK_CLOSE(testObj.getFrameRect().pos.y, posY, dx);
  }

  BOOST_AUTO_TEST_CASE(general_position)
  {
    kostylev::point_t position = {2.0, 4.0};
    double width = 10.0, height = 10.0;
    std::shared_ptr<kostylev::Shape> testRect =
      std::make_shared<kostylev::Rectangle>(position, width, height);
    kostylev::CompositeShape testObj(testRect);
    BOOST_CHECK_CLOSE(testObj.getFrameRect().pos.x, position.x, dx);
    BOOST_CHECK_CLOSE(testObj.getFrameRect().pos.y, position.y, dx);
    BOOST_CHECK_CLOSE(testObj.getFrameRect().width, width, dx);
    BOOST_CHECK_CLOSE(testObj.getFrameRect().height, height, dx);
  }

  BOOST_AUTO_TEST_CASE(common_area)
  {
    const double width = 2.0, height = 1.0;
    kostylev::point_t position = {2.0, 4.0};
    std::shared_ptr<kostylev::Shape> testRect =
      std::make_shared<kostylev::Rectangle>(position, width, height);
    const double radius = 3.0;
    std::shared_ptr<kostylev::Shape> testCirc =
      std::make_shared<kostylev::Circle>(kostylev::point_t{0.0, 0.0},radius);
    kostylev::CompositeShape testObj(testRect);
    testObj.addShape(testCirc);
    BOOST_CHECK_CLOSE(testObj.getArea(), width * height + 3.14 * radius * radius, dx);
  }

BOOST_AUTO_TEST_SUITE_END()
