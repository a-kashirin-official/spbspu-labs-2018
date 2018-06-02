
#define BOOST_TEST_MODULE Main
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

const double DELTA_REL = 0.00001;

BOOST_AUTO_TEST_SUITE( Rectangle )

  BOOST_AUTO_TEST_CASE( RectangleParametersPermanence )
  {
    zhukova::Rectangle rect( { 3.0, 3.0 }, 7.0, 1.0 );
    double initialArea = rect.getArea();

    rect.move( 21.0, 21.0 );

    BOOST_CHECK_EQUAL( rect.getFrameRect().width, 7.0 );
    BOOST_CHECK_EQUAL( rect.getFrameRect().height, 1.0 );
    BOOST_CHECK_EQUAL( rect.getArea(), initialArea );
  }

  BOOST_AUTO_TEST_CASE( RectangleScale )
  {
    zhukova::Rectangle rect( { 3.0, 3.0 }, 7.0, 1.0 );
    double initialArea = rect.getArea();

    rect.scale( 7.0 );

    BOOST_CHECK_CLOSE( rect.getArea(), initialArea * pow(7.0, 2.0), DELTA_REL );
  }

  BOOST_AUTO_TEST_CASE( RectangleConstructorParameters )
  {
    BOOST_CHECK_THROW( zhukova::Rectangle rect( { 3.0, 3.0 }, -7.0, 1.0 ), std::invalid_argument );
    BOOST_CHECK_THROW( zhukova::Rectangle rect( { 3.0, 3.0 }, 7.0, -1.0 ), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE( RectangleScalingFactor )
  {
    zhukova::Rectangle rect( { 3.0, 3.0 }, 7.0, 1.0 );
    BOOST_CHECK_THROW( rect.scale(-17.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE( Circle )

  BOOST_AUTO_TEST_CASE( CircleParametersPermanence )
  {
    zhukova::Circle circ( { 7.0, 7.0 }, 11.0 );
    double initialArea = circ.getArea();

    circ.move( 21.0, 21.0 );

    BOOST_CHECK_EQUAL( circ.getFrameRect().width / 2, 11.0 );
    BOOST_CHECK_EQUAL( circ.getArea(), initialArea );
  }

  BOOST_AUTO_TEST_CASE( CircleScale )
  {
    zhukova::Circle circ( { 7.0, 7.0 }, 11.0 );
    double initialArea = circ.getArea();

    circ.scale( 7.0 );

    BOOST_CHECK_CLOSE( circ.getArea(), initialArea * pow(7.0, 2.0), DELTA_REL );
  }

  BOOST_AUTO_TEST_CASE( CircleConstructorParameters )
  {
    BOOST_CHECK_THROW( zhukova::Circle circ( { 7.0, 7.0 }, -11.0 ), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE( CircleScalingFactor )
  {
    zhukova::Circle circ( { 7.0, 7.0 }, 11.0 );
    BOOST_CHECK_THROW( circ.scale(-11.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()
