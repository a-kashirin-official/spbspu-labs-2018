#define BOOST_TEST_MODULE test-Main
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace vlasov;

const double EPS = 0.00001;

BOOST_AUTO_TEST_SUITE(RectangleTests)

  BOOST_AUTO_TEST_CASE(PermanencyOfRectangleAfterCentreMovement)
  {
    vlasov::Rectangle objRect({17.32, 52.47, 30.54, 55.98});
    objRect.move(3.12, 7.75);
    BOOST_REQUIRE_CLOSE((objRect.getFrameRect().width), 52.47, EPS);
    BOOST_REQUIRE_CLOSE((objRect.getFrameRect().height), 17.32, EPS);
    BOOST_REQUIRE_CLOSE(objRect.getArea(), (17.32 * 52.47), EPS);
  }

  BOOST_AUTO_TEST_CASE(PermanencyOfRectangleAfterAxisOffset)
  {
    vlasov::Rectangle objRect({17.32, 52.47, 30.54, 55.98});
    objRect.move(43.21,54.22);
    BOOST_REQUIRE_CLOSE((objRect.getFrameRect().width), 52.47, EPS);
    BOOST_REQUIRE_CLOSE((objRect.getFrameRect().height), 17.32, EPS);
    BOOST_REQUIRE_CLOSE(objRect.getArea(), (17.32 * 52.47), EPS);
  }

  BOOST_AUTO_TEST_CASE(RectangleQuadraticChangeAreaAfterScale)
  {
    vlasov::Rectangle objRect({17.32, 52.47, 30.54, 55.98});
    objRect.scale(3);
    BOOST_REQUIRE_CLOSE(objRect.getArea(), (17.32 * 52.47 * pow(3,2)), EPS);
  }

  BOOST_AUTO_TEST_CASE(RectangleCheckIncorrectParametrs)
  {
    BOOST_CHECK_THROW(vlasov::Rectangle objRect({-1, 52.47, 30.54, 55.98}),std::invalid_argument);
    BOOST_CHECK_THROW(vlasov::Rectangle objRect({17.32, -10, 30.54, 55.98}),std::invalid_argument);
    vlasov::Rectangle objRect({17.32, 52.47, 30.54, 55.98});
    BOOST_CHECK_THROW(objRect.scale(-1),std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(RectangleCheckIncorrectParametrs2)
  {
    BOOST_CHECK_THROW(vlasov::Rectangle objRect({-1, -52.47, 30.54, 55.98}),std::invalid_argument);
    BOOST_CHECK_THROW(vlasov::Rectangle objRect({-17.32, -10, 30.54, 55.98}),std::invalid_argument);
    vlasov::Rectangle objRect({17.32, 52.47, 30.54, 55.98});
    BOOST_CHECK_THROW(objRect.scale(-1),std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTests)

  BOOST_AUTO_TEST_CASE(PermanencyOfCircleAferCenterMovement)
  {
    vlasov::Circle objCircle(4.12, {18.08, 37.01});
    objCircle.move({13.51, 12.25});
    BOOST_REQUIRE_CLOSE((objCircle.getFrameRect().width / 2), 4.12, EPS);
    BOOST_REQUIRE_CLOSE(objCircle.getArea(), (M_PI * 4.12 * 4.12), EPS);
  }

  BOOST_AUTO_TEST_CASE(PermanencyOfCircleAferAxisOffset)
  {
    vlasov::Circle objCircle(4.12, {30.15, 41.81});
    objCircle.move(43.21,54.22);
    BOOST_REQUIRE_CLOSE((objCircle.getFrameRect().width / 2), 4.12, EPS);
    BOOST_REQUIRE_CLOSE(objCircle.getArea(), (M_PI * 4.12 * 4.12), EPS);
  }

  BOOST_AUTO_TEST_CASE(CircleQuadraticAreaChangeAfterScaling)
  {
    vlasov::Circle objCircle(4.12, {30.15, 41.81});
    objCircle.scale(3);
    BOOST_REQUIRE_CLOSE(objCircle.getArea(), (M_PI * 4.12 * 4.12 * pow(3,2)), EPS);
  }

  BOOST_AUTO_TEST_CASE(CircleCheckIncorrectParametrs)
  {
    BOOST_CHECK_THROW(vlasov::Circle objCircle(-1,{30.15, 41.81}),std::invalid_argument);
    vlasov::Circle objCircle(4.12, {30.15, 41.81});
    BOOST_CHECK_THROW(objCircle.scale(-1),std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(COMP_TESTS)

  BOOST_AUTO_TEST_CASE(NopointerAndIndex)
  {
    BOOST_CHECK_THROW(CompositeShape compShape(nullptr), std::invalid_argument);
    std::shared_ptr<vlasov::Shape> rectPtr = std::make_shared<vlasov::Rectangle>(vlasov::Rectangle({5.0, 5.0, 0.0, 0.0}));
    CompositeShape compShape(rectPtr);
    BOOST_CHECK_THROW(compShape.removeShape(2),std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rectangle)
  {
    std::shared_ptr<vlasov::Shape> rectPtr = std::make_shared<vlasov::Rectangle>(vlasov::Rectangle ({5.0,5.0,0.0,0.0}));
    CompositeShape compShape(rectPtr);

    BOOST_CHECK_CLOSE(compShape.getArea(), 25.0, EPS);
    compShape.scale(2.0);
    BOOST_CHECK_CLOSE(compShape.getArea(), 100.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(rectPlusCirc)
  {
    std::shared_ptr<vlasov::Shape> rectPtr = std::make_shared<vlasov::Rectangle>(vlasov::Rectangle ({5.0,5.0,0.0,0.0}));
    CompositeShape compShape(rectPtr);
    std::shared_ptr<vlasov::Shape> circPtr = std::make_shared<vlasov::Circle>(vlasov::Circle (5.0,{0.0,0.0}));
    compShape.addShape(circPtr);

    BOOST_CHECK_CLOSE(compShape.getArea(),25.0+M_PI*5.0*5.0,EPS);
  }

  BOOST_AUTO_TEST_CASE(allFigures)
  {
    CompositeShape compShape;
    BOOST_CHECK_CLOSE(compShape.getArea(),0,EPS);
    std::shared_ptr<vlasov::Shape> rectPtr = std::make_shared<vlasov::Rectangle>(vlasov::Rectangle ({5.0,5.0,0.0,0.0}));
    compShape.addShape(rectPtr);
    BOOST_CHECK_CLOSE(compShape.getArea(),25.0,EPS);
    std::shared_ptr<vlasov::Shape> circPtr = std::make_shared<vlasov::Circle>(vlasov::Circle (5.0,{0.0,0.0}));
    compShape.addShape(circPtr);
    BOOST_CHECK_CLOSE(compShape.getArea(), 25+M_PI*5.0*5.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(movement)
  {
    std::shared_ptr<vlasov::Shape> rectPtr = std::make_shared<vlasov::Rectangle>(vlasov::Rectangle ({5.0,5.0,0.0,0.0}));
    CompositeShape compShape(rectPtr);
    std::shared_ptr<vlasov::Shape> circPtr = std::make_shared<vlasov::Circle>(vlasov::Circle (5.0,{0.0,0.0}));
    compShape.addShape(circPtr);
    compShape.move({5.0,5.0});

    BOOST_CHECK_CLOSE(compShape.getArea(), 25.0+M_PI*5.0*5.0, EPS);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.y, 5.0, EPS);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.x, 5.0, EPS);

    compShape.move(5.0,5.0);

    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.x, 10.0, EPS);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.y, 10.0, EPS);
  }

BOOST_AUTO_TEST_SUITE_END()
