#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace lobanova;

const double EPS = 0.0001;

BOOST_AUTO_TEST_SUITE(Composite_shape_test)

  BOOST_AUTO_TEST_CASE(Static_area_test)
  {
    Rectangle rect({11.1, 15.6}, 5.4, 9);
    double area = rect.getArea();
    Circle c({6, 9}, 7);
    area += c.getArea();
    CompositeShape cs;
    cs.add(&rect);
    cs.add(&c);
    BOOST_REQUIRE_CLOSE(area, cs.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(GetSize_and_Clear_test)
  {
    Rectangle rect({11.1, 15.6}, 5.4, 9);
    Circle c({6, 9}, 7);
    CompositeShape cs;
    cs.add(&rect);
    cs.add(&c);
    BOOST_REQUIRE_EQUAL(cs.getSize(), 2);
    cs.clear();
    BOOST_REQUIRE_EQUAL(cs.getSize(), 0);
  }

  BOOST_AUTO_TEST_CASE(Moving_to_vector_test)
  {
    Rectangle rect({11.1, 15.6}, 5.4, 9);
    Circle c({6, 9}, 7);
    CompositeShape cs;
    cs.add(&rect);
    cs.add(&c);
    double area = cs.getArea();
    rectangle_t rt = cs.getFrameRect();
    cs.move(5, 9);
    BOOST_REQUIRE_CLOSE(area, cs.getArea(), EPS);
    BOOST_REQUIRE_CLOSE(cs.getFrameRect().height, rt.height, EPS);
    BOOST_REQUIRE_CLOSE(cs.getFrameRect().width, rt.width, EPS);
  }

  BOOST_AUTO_TEST_CASE(Moving_to_point_test)
  {
    Rectangle rect({11.1, 15.6}, 5.4, 9);
    Circle c({6, 9}, 7);
    CompositeShape cs;
    cs.add(&rect);
    cs.add(&c);
    double area = cs.getArea();
    rectangle_t rt = cs.getFrameRect();
    cs.move({5, 9});
    BOOST_REQUIRE_CLOSE(area, cs.getArea(), EPS);
    BOOST_REQUIRE_CLOSE(area, cs.getArea(), EPS);
    BOOST_REQUIRE_CLOSE(cs.getFrameRect().height, rt.height, EPS);
    BOOST_REQUIRE_CLOSE(cs.getFrameRect().width, rt.width, EPS);
  }

  BOOST_AUTO_TEST_CASE(Scale_test)
  {
    Rectangle rect({11.1, 15.6}, 5.4, 9);
    Circle c({6, 9}, 7);
    CompositeShape cs;
    cs.add(&rect);
    cs.add(&c);
    double area = cs.getArea();
    rectangle_t rt = cs.getFrameRect();
    cs.scale(2);
    BOOST_REQUIRE_CLOSE(area * 2 * 2, cs.getArea(), EPS);
    BOOST_REQUIRE_CLOSE(cs.getFrameRect().pos.x, rt.pos.x, EPS);
    BOOST_REQUIRE_CLOSE(cs.getFrameRect().pos.y, rt.pos.y, EPS);
    BOOST_REQUIRE_CLOSE(cs.getFrameRect().height, rt.height * 2, EPS);
    BOOST_REQUIRE_CLOSE(cs.getFrameRect().width, rt.width * 2, EPS);
    area = cs.getArea();
    rt = cs.getFrameRect();
    cs.scale(0.3);
    BOOST_REQUIRE_CLOSE(area * 0.3 * 0.3, cs.getArea(), EPS);
    BOOST_REQUIRE_CLOSE(area * 0.3 * 0.3, cs.getArea(), EPS);
    BOOST_REQUIRE_CLOSE(cs.getFrameRect().height, rt.height * 0.3, EPS);
    BOOST_REQUIRE_CLOSE(cs.getFrameRect().width, rt.width * 0.3, EPS);
  }

  BOOST_AUTO_TEST_CASE(Assigment_test)
  {
    CompositeShape cs1;
    Rectangle rect({7, 2}, 4, 4);
    cs1.add(&rect);
    CompositeShape cs2 = cs1;
    cs1.add(&rect);
    BOOST_REQUIRE_EQUAL(cs2.getSize(), cs1.getSize() - 1);

  }

  BOOST_AUTO_TEST_CASE(AddShape_error_test)
  {
    Rectangle rect({11.1, 15.6}, 5.4, 9);
    CompositeShape cs;
    cs.add(&rect);
    BOOST_CHECK_THROW(cs.add(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scale_error_test)
  {
    Rectangle rect({11.1, 15.6}, 5.4, 9);
    CompositeShape cs;
    cs.add(&rect);
    BOOST_CHECK_THROW(cs.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Remove_error_test)
  {
    Rectangle rect({11.1, 15.6}, 5.4, 9);
    Circle c({6, 9}, 7);
    CompositeShape cs;
    cs.add(&rect);
    cs.add(&c);
    BOOST_CHECK_THROW(cs.remove(5), std::out_of_range);
  }


BOOST_AUTO_TEST_SUITE_END()
