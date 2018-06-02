#define BOOST_TEST_MODULE mainTests
#include <iostream>
#include <cmath>
#include "circle.hpp"
#include "rectangle.hpp"
#include <boost/test/included/unit_test.hpp>
#include <boost/test/framework.hpp>

using namespace vlasov;

BOOST_AUTO_TEST_SUITE (rectangle)

BOOST_AUTO_TEST_CASE(movingByDifferentials){
  std::cout << "RECTSUITE" << std::endl;
  std::cout << boost::unit_test::framework::current_test_case().p_name << std::endl;
  Rectangle pr(10.0, 12.0, {12.0, 12.0});
  double s = pr.getArea();
  rectangle_t frame = pr.getFrameRect();
  pr.move(10,5);
  BOOST_CHECK_EQUAL(s, pr.getArea());
  BOOST_CHECK_EQUAL(frame.width, pr.getFrameRect().width);
  BOOST_CHECK_EQUAL(frame.height, pr.getFrameRect().height);
  std::cout << "Done" << std::endl;
  }

BOOST_AUTO_TEST_CASE(movingToPosition){
  std::cout << boost::unit_test::framework::current_test_case().p_name << std::endl;
  Rectangle pr(11.1, 12.2, {25.7, 35.6});
  double s = pr.getArea();
  rectangle_t frame = pr.getFrameRect();
  pr.move({10.0, 15.1});
  BOOST_CHECK_EQUAL(s, pr.getArea());
  BOOST_CHECK_EQUAL(frame.width, pr.getFrameRect().width);
  BOOST_CHECK_EQUAL(frame.height, pr.getFrameRect().height);
  std::cout << "Done" << std::endl;
  }

BOOST_AUTO_TEST_CASE(squareScaling){
  std::cout << boost::unit_test::framework::current_test_case().p_name << std::endl;
  Rectangle pr(33.3, 44.4, {55.5, 66.6});
  double s = pr.getArea();
  double scaler = 12.3;
  pr.scale(scaler);
  BOOST_CHECK_EQUAL(s*pow(scaler, 2), pr.getArea());
  std::cout << "Done" << std::endl;
  }

BOOST_AUTO_TEST_CASE(invalidProcessing){
  BOOST_CHECK_THROW(Rectangle pr(-1.23, 4.56, {78.9, 10.11}), std::invalid_argument);
  BOOST_CHECK_THROW(Rectangle pr(1.23, -4.56, {78.9, 10.11}), std::invalid_argument);
  BOOST_CHECK_THROW(Rectangle pr(-1.23, -4.56, {78.9, 10.11}), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(circle)

BOOST_AUTO_TEST_CASE(movingByDifferentials){
  std::cout << "CIRCSUITE" << std::endl;
  std::cout << boost::unit_test::framework::current_test_case().p_name << std::endl;
  Circle cr(10.0, {12.0, 12.0});
  double s = cr.getArea();
  rectangle_t frame = cr.getFrameRect();
  cr.move(10,5);
  BOOST_CHECK_EQUAL(s, cr.getArea());
  BOOST_CHECK_EQUAL(frame.width, cr.getFrameRect().width);
  BOOST_CHECK_EQUAL(frame.height, cr.getFrameRect().height);
  std::cout << "Done" << std::endl;
  }

BOOST_AUTO_TEST_CASE(movingToPosition){
  std::cout << boost::unit_test::framework::current_test_case().p_name << std::endl;
  Circle cr(11.1, {25.7, 35.6});
  double s = cr.getArea();
  rectangle_t frame = cr.getFrameRect();
  cr.move({10.0,15.1});
  BOOST_CHECK_EQUAL(s, cr.getArea());
  BOOST_CHECK_EQUAL(frame.width, cr.getFrameRect().width);
  BOOST_CHECK_EQUAL(frame.height, cr.getFrameRect().height);
  std::cout << "Done" << std::endl;
  }

BOOST_AUTO_TEST_CASE(squareScaling){
  std::cout << boost::unit_test::framework::current_test_case().p_name << std::endl;
  Circle cr(33.3, {55.5, 66.6});
  double s = cr.getArea();
  double scaler = 12.3;
  cr.scale(scaler);
  BOOST_CHECK_CLOSE(s*pow(scaler, 2), cr.getArea(), 0.00001);
  std::cout << "Done" << std::endl;
  }

BOOST_AUTO_TEST_CASE(invalidProcessing){
  BOOST_CHECK_THROW(Circle cr(-1.23, {78.9, 10.11}), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
