#define BOOST_TEST_MAIN
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"

const double EPSILON = 0.0001;


BOOST_AUTO_TEST_SUITE(rectangle_test)

BOOST_AUTO_TEST_CASE(Invalid_Width_Argument)
{
  BOOST_CHECK_THROW( lyachko::Rectangle({ {10.0, 10.0}, -15.0, 15.0 }), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE(InvalidA_Height_Argument)
{
  BOOST_CHECK_THROW( lyachko::Rectangle({ {10.0, 10.0}, 15.0, -15.0 }), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE(Invalid_Scale_Argument)
{
  lyachko::Rectangle rectangle_{ { {1.0, 1.0}, 1.5, 1.5 } };
  BOOST_CHECK_THROW( rectangle_.scale(-10.0), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE(MoveTo)
{
  lyachko::Rectangle rectangle_{ { {1.0, 1.0}, 1.5, 1.5 } };
  double r_original_area = rectangle_.getArea();
  lyachko::point_t r_altered_point = {10.0, 10.0};
  rectangle_.move(r_altered_point);

  BOOST_CHECK_CLOSE_FRACTION(r_original_area, rectangle_.getArea(), EPSILON);
  BOOST_CHECK_EQUAL(r_altered_point.x, rectangle_.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(r_altered_point.y, rectangle_.getFrameRect().pos.y);
  BOOST_CHECK_EQUAL(rectangle_.getFrameRect().width, 1.5);
  BOOST_CHECK_EQUAL(rectangle_.getFrameRect().height, 1.5);
}

BOOST_AUTO_TEST_CASE(ShiftDxDy)
{
  lyachko::Rectangle rectangle_{ { {1.0, 1.0}, 1.5, 1.5 }};
  double r_original_area = rectangle_.getArea();
  lyachko::point_t r_altered_point = {10.0, 10.0};
  rectangle_.move(9.0, 9.0);

  BOOST_CHECK_CLOSE_FRACTION(rectangle_.getArea(), r_original_area, EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(rectangle_.getFrameRect().pos.x, r_altered_point.x, EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(rectangle_.getFrameRect().pos.y, r_altered_point.y, EPSILON);
  BOOST_CHECK_EQUAL(rectangle_.getFrameRect().width, 1.5);
  BOOST_CHECK_EQUAL(rectangle_.getFrameRect().height, 1.5);
}

BOOST_AUTO_TEST_CASE(Scale)
{
  lyachko::Rectangle rectangle_{ { {1.0, 1.0}, 1.5, 1.5 }};
  double r_original_area = rectangle_.getArea();
  const double coeff = 4.0;
  rectangle_.scale(coeff);
  BOOST_CHECK_CLOSE_FRACTION(coeff * coeff * r_original_area, rectangle_.getArea(), EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(circle_test)

BOOST_AUTO_TEST_CASE(Invalid_Radius_Argument)
{
  BOOST_CHECK_THROW(lyachko::Circle({1.0, 1.0}, -5.0), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE(Invalid_Scale_Argument)
{
  lyachko::Circle circle_{ {1.0, 1.0}, 5.0 };
  BOOST_CHECK_THROW( circle_.scale(-10.0), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE(MoveTo)
{
  lyachko::Circle circle_{ {1.0, 1.0}, 5.0 };
  lyachko::rectangle_t c_original_frame = circle_.getFrameRect();
  double c_original_area = circle_.getArea();
  lyachko::point_t c_altered_point = {10.0, 10.0};
  circle_.move(c_altered_point);
  
  BOOST_CHECK_CLOSE_FRACTION(c_original_area, circle_.getArea(), EPSILON);
  BOOST_CHECK_EQUAL(c_altered_point.x, circle_.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(c_altered_point.y, circle_.getFrameRect().pos.y);
  BOOST_CHECK_EQUAL(c_original_frame.width, circle_.getFrameRect().width);
  BOOST_CHECK_EQUAL(c_original_frame.height, circle_.getFrameRect().height);
}

BOOST_AUTO_TEST_CASE(ShiftDxDy)
{
  lyachko::Circle circle_{ {1.0, 1.0}, 5.0 };
  lyachko::rectangle_t c_original_frame = circle_.getFrameRect();
  double c_original_area = circle_.getArea();
  lyachko::point_t c_altered_point = {10.0, 10.0};
  circle_.move(9.0, 9.0);

  BOOST_CHECK_CLOSE_FRACTION(c_altered_point.x, circle_.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(c_altered_point.y, circle_.getFrameRect().pos.y, EPSILON);
  BOOST_CHECK_CLOSE_FRACTION(c_original_area, circle_.getArea(), EPSILON);
  BOOST_CHECK_EQUAL(c_original_frame.width, circle_.getFrameRect().width);
  BOOST_CHECK_EQUAL(c_original_frame.height, circle_.getFrameRect().height);
}

BOOST_AUTO_TEST_CASE(Scale)
{
  lyachko::Circle circle_{ {1.0, 1.0}, 5.0 };
  double c_original_area = circle_.getArea();
  const double coeff = 2.0;
  circle_.scale(coeff);
  BOOST_CHECK_CLOSE_FRACTION(coeff * coeff * c_original_area, circle_.getArea(), EPSILON);
}

BOOST_AUTO_TEST_SUITE_END()
