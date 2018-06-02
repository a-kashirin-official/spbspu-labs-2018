#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "rectangle.hpp"
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <stdexcept>

const double ACCURACY = 0.0001;

BOOST_AUTO_TEST_SUITE(Matrix_test)

  BOOST_AUTO_TEST_CASE(AddShape_test_for_matrix)
  {
    gessen::Rectangle *rect = new gessen::Rectangle({128.0, 256.0}, 14.0, 57.0);
    gessen::Circle *circ = new gessen::Circle ({59.0, 61.0}, 10.0);
    gessen::Matrix mtrx(rect);
    mtrx.addShape(circ);
    BOOST_CHECK_EQUAL(mtrx[0], rect);
    BOOST_CHECK_EQUAL(mtrx[1], circ);
  }

  BOOST_AUTO_TEST_CASE(Test_move)
  {
    gessen::Rectangle *rect = new gessen::Rectangle({128.0, 256.0}, 14.0, 57.0);
    gessen::Circle *circ = new gessen::Circle ({59.0, 61.0}, 10.0);
    gessen::Matrix mtrx(rect);
    mtrx.addShape(circ);
    gessen::Matrix mtrx2(std::move(mtrx));
    BOOST_CHECK_EQUAL(mtrx2[0], rect);
    BOOST_CHECK_EQUAL(mtrx2[1], circ);
  }
BOOST_AUTO_TEST_SUITE_END()
