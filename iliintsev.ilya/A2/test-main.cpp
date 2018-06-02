#define BOOST_TEST_MODULE Main
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"

using namespace iliintsev;

const double EPSILON = 1e-6;

BOOST_AUTO_TEST_SUITE(RectangleSuite)

BOOST_AUTO_TEST_CASE(Test_move_to_point)
{
  Rectangle rectForMove( { {5.0, 5.0}, 5.0, 5.0} );
  double areaBefore = rectForMove.getArea();
  rectangle_t rectBefore = rectForMove.getFrameRect();

  rectForMove.move( {40.0, 50.0} );

  BOOST_CHECK_CLOSE_FRACTION(rectBefore.width, rectForMove.getFrameRect().width,EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(rectBefore.height, rectForMove.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(areaBefore, rectForMove.getArea(), EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(rectForMove.getFrameRect().pos.x, 40.0, EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(rectForMove.getFrameRect().pos.y, 50.0, EPSILON);
}

BOOST_AUTO_TEST_CASE(RelativeMoving)
{
  Rectangle rectForMove( { {5.0, 5.0}, 5.0, 5.0} );
  rectangle_t rectBeforeMove = rectForMove.getFrameRect();
  double areaBeforeMove = rectForMove.getArea();

  rectForMove.move(-25.0, 25.0);
  rectangle_t rectAfterMove = rectForMove.getFrameRect();

  BOOST_CHECK_CLOSE_FRACTION(areaBeforeMove, rectForMove.getArea(), EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(rectBeforeMove.width, rectAfterMove.width, EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(rectBeforeMove.height, rectAfterMove.height, EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(rectForMove.getFrameRect().pos.x, -20.0, EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(rectForMove.getFrameRect().pos.y, 30.0, EPSILON);
}

BOOST_AUTO_TEST_CASE(Scaling)
{
  Rectangle rectForScale( { {5.0, 5.0}, 5.0, 5.0} );
  double areaBeforeScale = rectForScale.getArea();
  const double ratio = 6.30;

  rectForScale.scale(ratio);

  BOOST_CHECK_CLOSE_FRACTION(ratio * ratio * areaBeforeScale, rectForScale.getArea(), EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(5.0 * ratio, rectForScale.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(5.0 * ratio, rectForScale.getFrameRect().height, EPSILON);
}

BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
{
  BOOST_CHECK_THROW( Rectangle( { {5.0, 5.0}, 5.0, -5.0} ), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
{
  Rectangle rectForScale( { {5.0, 5.0}, 5.0, 5.0} );
  BOOST_CHECK_THROW( rectForScale.scale(-1.0), std::invalid_argument );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleSuite)

BOOST_AUTO_TEST_CASE(Test_move_to_point)
{
  Circle circForMove({5.0, 5.0}, 5.0);
  double areaBefore = circForMove.getArea();
  rectangle_t circBefore = circForMove.getFrameRect();

  circForMove.move( {40.0, 50.0} );

  BOOST_CHECK_CLOSE_FRACTION(circBefore.width, circForMove.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(circBefore.height, circForMove.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(areaBefore, circForMove.getArea(), EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(circForMove.getCenter().x, 40.0,EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(circForMove.getCenter().y, 50.0,EPSILON);
  
}

BOOST_AUTO_TEST_CASE(RelativeMoving)
{
  Circle circForMove({5.0, 5.0}, 5.0);
  rectangle_t circBeforeMove = circForMove.getFrameRect();
  double areaBeforeMove = circForMove.getArea();

  circForMove.move(-25.0, 25.0);
  rectangle_t circAfterMove = circForMove.getFrameRect();

  BOOST_CHECK_CLOSE_FRACTION(areaBeforeMove, circForMove.getArea(), EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(circBeforeMove.width, circAfterMove.width, EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(circBeforeMove.height, circAfterMove.height, EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(circForMove.getCenter().x, -20.0, EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(circForMove.getCenter().y, 30.0, EPSILON);
}

BOOST_AUTO_TEST_CASE(Scaling)
{
  Circle circForScale({5.0, 5.0}, 5.0 );
  double areaBeforeScale = circForScale.getArea();

  const double ratio = 6.30;

  circForScale.scale(ratio);

  BOOST_CHECK_CLOSE_FRACTION(ratio * ratio * areaBeforeScale, circForScale.getArea(), EPSILON);
}

BOOST_AUTO_TEST_CASE(InvalidConstructorParameters)
{
  BOOST_CHECK_THROW( Circle( {5.0, 5.0}, -5.0 ), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE(InvalidScaleParameter)
{
  Circle circForScale( {5.0, 5.0}, 5.0 );
  BOOST_CHECK_THROW( circForScale.scale(-1.0), std::invalid_argument );
}

BOOST_AUTO_TEST_SUITE_END()
