#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace lobanova;

const double EPS = 0.001;

BOOST_AUTO_TEST_SUITE(Rotate_test)

  BOOST_AUTO_TEST_CASE(Area_test)
  {
    Rectangle rect({11.1, 15.6}, 5.4, 9);
    double area = rect.getArea();
    rect.rotate(80);
    BOOST_REQUIRE_CLOSE(area, rect.getArea(), EPS);
    Circle c({6, 9}, 7);
    CompositeShape cs;
    cs.add(&rect);
    cs.add(&c);
    area = cs.getArea();
    cs.rotate(30);
    BOOST_REQUIRE_CLOSE(area, cs.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(Point_test)
  {
    point_t p = {3, 0};
    p.rotate({0, 0}, 90);
    BOOST_REQUIRE_CLOSE(p.x + 1, 1, EPS);
    BOOST_REQUIRE_CLOSE(p.y, 3, EPS);
    p.rotate({3, 3}, 45);
    BOOST_REQUIRE_CLOSE(p.x, 0.87868, EPS);
    BOOST_REQUIRE_CLOSE(p.y, 0.87868, EPS);
  }

  BOOST_AUTO_TEST_CASE(FrameRect_test)
  {
    Rectangle rect({1, 0}, 1, 1);
    Circle c({0, 0}, 0.5);
    CompositeShape cs;
    cs.add(&rect);
    cs.add(&c);
    cs.rotate(90);
    rectangle_t r = cs.getFrameRect();

    BOOST_REQUIRE_CLOSE(r.height, 2, EPS);
    BOOST_REQUIRE_CLOSE(r.width, 1, EPS);
    BOOST_REQUIRE_CLOSE(r.pos.x, 0.5, EPS);
    BOOST_REQUIRE_CLOSE(r.pos.y, 0, EPS);

  }


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Matrix_test)

  BOOST_AUTO_TEST_CASE(AddShape_and_getSizes_and_rewriteOperator_test)
  {
    Rectangle rect1({0, 0}, 2, 3);
    Matrix m;
    m.add(&rect1);
    BOOST_REQUIRE_EQUAL(m.getWidth(), 1);
    BOOST_REQUIRE_EQUAL(m.getHeight(), 1);
    BOOST_REQUIRE_EQUAL(m.getSizeOfLayer(0), 1);
    BOOST_REQUIRE_CLOSE(m[0][0]->getArea(), 6, EPS);
    Rectangle rect2({0, 0}, 2, 2);
    m.add(&rect2);
    BOOST_REQUIRE_EQUAL(m.getWidth(), 1);
    BOOST_REQUIRE_EQUAL(m.getHeight(), 2);
    BOOST_REQUIRE_EQUAL(m.getSizeOfLayer(0), 1);
    BOOST_REQUIRE_CLOSE(m[1][0]->getArea(), 4, EPS);
    Circle c({5, 5}, 1);
    m.add(&c);
    BOOST_REQUIRE_EQUAL(m.getWidth(), 2);
    BOOST_REQUIRE_EQUAL(m.getHeight(), 2);
    BOOST_REQUIRE_EQUAL(m.getSizeOfLayer(0), 2);
    BOOST_REQUIRE_CLOSE(m[0][1]->getArea(), 3.141592, EPS);
    m.~Matrix();

  }

  BOOST_AUTO_TEST_CASE(Add_error_test)
  {
    Matrix m;
    BOOST_CHECK_THROW(m.add(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Out_of_range_test)
  {
    Matrix m;
    BOOST_CHECK_THROW(m.getSizeOfLayer(7), std::out_of_range);
  }



BOOST_AUTO_TEST_SUITE_END()
