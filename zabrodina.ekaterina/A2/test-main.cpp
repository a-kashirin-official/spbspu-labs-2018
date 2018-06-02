#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
//#include <boost/test/included/floating_point_comparison.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include <stdexcept>


const double accuracy = 0.001;

BOOST_AUTO_TEST_SUITE(rectangle_tests)
BOOST_AUTO_TEST_CASE(rectangle_move_on_x_y)
{
  zabrodina::Rectangle rect({0.0, 0.0}, 10.0, 9.0);
  const zabrodina::point_t center_before({rect.getFrameRect().pos.x, rect.getFrameRect().pos.y});
  const double area = rect.getArea();
  const double width = rect.getFrameRect().width;
  const double height = rect.getFrameRect().height;
  rect.move(3.25, 8.1);
  BOOST_CHECK_CLOSE(center_before.x, rect.getFrameRect().pos.x - 3.25, accuracy);
  BOOST_CHECK_CLOSE(center_before.y, rect.getFrameRect().pos.y - 8.1, accuracy);
  BOOST_CHECK_CLOSE(width, rect.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(height, rect.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(area, rect.getArea(), accuracy);
}
BOOST_AUTO_TEST_CASE(rectangle_move_to_x_y)
{
  zabrodina::Rectangle rect({-2.6, -23.5}, 12.3, 4.89);
  const double area = rect.getArea();
  const double width = rect.getFrameRect().width;
  const double height = rect.getFrameRect().height;
  rect.move({-0.45, 2.4});
  BOOST_CHECK_CLOSE(width, rect.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(height, rect.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(area, rect.getArea(), accuracy);
}
BOOST_AUTO_TEST_CASE(rectangle_scale)
{
  zabrodina::Rectangle rect({-0.4, 4.5}, 4.5, 5.4);
  const double area = rect.getArea();
  const double width = rect.getFrameRect().width;
  const double height = rect.getFrameRect().height;
  const double k = 2.5;
  rect.scale(k);
  BOOST_CHECK_CLOSE(area * k * k, rect.getArea(), accuracy);
  BOOST_CHECK_CLOSE(height * k, rect.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(width * k, rect.getFrameRect().width, accuracy);
}
BOOST_AUTO_TEST_CASE(rectangle_wrong_data)
{
  BOOST_CHECK_THROW(zabrodina::Rectangle({0.0, -5.0}, 0, -10), std::invalid_argument);
  zabrodina::Rectangle rect({0.0, 5.0}, 5, 5);
  BOOST_CHECK_THROW(rect.scale(0.0), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(circle_tests)
BOOST_AUTO_TEST_CASE(circle_move_on_x_y)
{
  zabrodina::Circle circl({-2.0, 2.0}, 5.2);
  const zabrodina::point_t center_before({circl.getFrameRect().pos.x, circl.getFrameRect().pos.y});
  const double area = circl.getArea();
  const double width = circl.getFrameRect().width;
  const double height = circl.getFrameRect().height;
  circl.move(1.0, 2.0);
  BOOST_CHECK_CLOSE(center_before.x, circl.getFrameRect().pos.x - 1.0, accuracy);
  BOOST_CHECK_CLOSE(center_before.y, circl.getFrameRect().pos.y - 2.0, accuracy);
  BOOST_CHECK_CLOSE(width, circl.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(height, circl.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(area, circl.getArea(), accuracy);
}
BOOST_AUTO_TEST_CASE(circle_move_to_x_y)
{
  zabrodina::Circle circl({3.5, -2.3}, 2.0);
  const double area = circl.getArea();
  const double width = circl.getFrameRect().width;
  const double height = circl.getFrameRect().height;
  circl.move({0.4, 2.3});
  BOOST_CHECK_CLOSE(width, circl.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(height, circl.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(area, circl.getArea(), accuracy);
}
BOOST_AUTO_TEST_CASE(circle_scale)
{
  zabrodina::Circle circl({-2.3, -1.9}, 3.0);
  const double area = circl.getArea();
  const double k = 2.7;
  circl.scale(k);
  BOOST_CHECK_CLOSE(area * k * k, circl.getArea(), accuracy);
}
BOOST_AUTO_TEST_CASE(circle_wrong_data)
{
  BOOST_CHECK_THROW(zabrodina::Circle({0.5, 1.5}, -5.3), std::invalid_argument);
  zabrodina::Circle circl({2.34, 5.12}, 5.3);
  BOOST_CHECK_THROW(circl.scale(-2.5), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(triangle_tests)
BOOST_AUTO_TEST_CASE(triangle_get_area)
{
  zabrodina::Triangle triangl({0.0, 4.0}, {0.0, 0.0}, {4.0, 0.0});
  BOOST_CHECK_CLOSE(8.0, triangl.getArea(), accuracy);
}
BOOST_AUTO_TEST_CASE(triangle_move_on_x_y)
{
  zabrodina::Triangle triangl({-2.56, 1.23}, {0.0, -1.2}, {2.0, 1.23});
  const double area = triangl.getArea();
  const double width = triangl.getFrameRect().width;
  const double height = triangl.getFrameRect().height;
  triangl.move(5.2, -1.23);
  BOOST_CHECK_CLOSE(width, triangl.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(height, triangl.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(area, triangl.getArea(), accuracy);
}
BOOST_AUTO_TEST_CASE(triangle_move_to_x_y)
{
  zabrodina::Triangle triangl({-2.28, 0.0}, {1.0, 3.24}, {6.23, -3.45});
  const double area = triangl.getArea();
  const double width = triangl.getFrameRect().width;
  const double height = triangl.getFrameRect().height;
  triangl.move({-2.32, 2.32});
  BOOST_CHECK_CLOSE(width, triangl.getFrameRect().width, accuracy);
  BOOST_CHECK_CLOSE(height, triangl.getFrameRect().height, accuracy);
  BOOST_CHECK_CLOSE(area, triangl.getArea(), accuracy);
}
BOOST_AUTO_TEST_CASE(triangle_scale)
{
  zabrodina::Triangle triangl({0.0, 4.3}, {0.0, 0.0}, {3.23, -2.34});
  const double area = triangl.getArea();
  const double k = 0.23;
  triangl.scale(k);
  BOOST_CHECK_CLOSE(area * k * k, triangl.getArea(), accuracy);
}
BOOST_AUTO_TEST_CASE(triangle_wrong_data)
{
  BOOST_CHECK_THROW(zabrodina::Triangle({2.1, 2.1}, {2.1, -1.5}, {2.1, -1.5}), std::invalid_argument);
  zabrodina::Triangle triangl({0.0, 2.3}, {2.34, -3.4}, {6.56, 3.45});
  BOOST_CHECK_THROW(triangl.scale(-1.23), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()
