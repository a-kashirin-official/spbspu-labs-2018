#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <stdexcept>
#include <memory>
#include "../common/rectangle.hpp"
#include "../common/circle.hpp"
#include "../common/composite-shape.hpp"

#include <boost/test/included/unit_test.hpp>

const double EPS = 0.000001;

BOOST_AUTO_TEST_SUITE (Rotating)

  BOOST_AUTO_TEST_CASE(RectangleTest)
  {
    belonogova::Rectangle rect ({5.0, 4.0, {0.0, 0.0}});
    belonogova::Rectangle originalRect = rect;
    rect.rotate(30);

    BOOST_CHECK_EQUAL(rect.getArea(), originalRect.getArea());
    BOOST_CHECK_EQUAL(rect.getFrameRect().pos.x, originalRect.getFrameRect().pos.x);
    BOOST_CHECK_EQUAL(rect.getFrameRect().pos.y, originalRect.getFrameRect().pos.y);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeTest)
  {
    std::shared_ptr <belonogova::Shape> rect =
    std::make_shared<belonogova::Rectangle>(belonogova::Rectangle({1.0, 2.0, {-3.0, -4.0}}));
    std::shared_ptr <belonogova::Shape> circ =
    std::make_shared<belonogova::Circle>(belonogova::Circle(2.0, {13.0, 5.0}));
    belonogova::CompositeShape comp(rect);
    comp.addComponent(circ);
    belonogova:: CompositeShape originalComp{comp};
    comp.rotate(90);

    BOOST_CHECK_EQUAL(comp.getArea(), originalComp.getArea());
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.x, originalComp.getFrameRect().pos.x, EPS);
    BOOST_CHECK_CLOSE(comp.getFrameRect().pos.y, originalComp.getFrameRect().pos.y, EPS);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Matrix)

  BOOST_AUTO_TEST_CASE(ConstructorTest)
  {
    belonogova::Matrix matr;
    BOOST_CHECK_EQUAL(matr.getLayers(), 0);
    BOOST_CHECK_EQUAL(matr.getMaxInLayer(), 0);
  }

  BOOST_AUTO_TEST_CASE(CopyConstructorTest)
  {
    std::shared_ptr <belonogova::Shape> rect =
    std::make_shared<belonogova::Rectangle>(belonogova::Rectangle({1.0, 2.0, {-3.0, -4.0}}));
    std::shared_ptr <belonogova::Shape> circ =
    std::make_shared<belonogova::Circle>(belonogova::Circle(2.0, {13.0, 5.0}));
    belonogova::Matrix otherMatr;
    otherMatr.addShapeToLayer(rect);
    otherMatr.addShapeToLayer(circ);
    belonogova::Matrix matr{otherMatr};
    BOOST_CHECK_EQUAL(matr.getLayers(), otherMatr.getLayers());
    BOOST_CHECK_EQUAL(matr.getMaxInLayer(), otherMatr.getMaxInLayer());
  }

  BOOST_AUTO_TEST_CASE(MoveConstructorTest)
  {
    std::shared_ptr <belonogova::Shape> rect =
    std::make_shared<belonogova::Rectangle>(belonogova::Rectangle({1.0, 2.0, {-3.0, -4.0}}));
    std::shared_ptr <belonogova::Shape> circ =
    std::make_shared<belonogova::Circle>(belonogova::Circle(2.0, {13.0, 5.0}));
    belonogova::Matrix otherMatr;
    otherMatr.addShapeToLayer(rect);
    otherMatr.addShapeToLayer(circ);
    double otherLayers = otherMatr.getLayers();
    double otherMaxInLayer = otherMatr.getMaxInLayer();
    belonogova::Matrix matr{std::move(otherMatr)};

    BOOST_CHECK_EQUAL(matr.getLayers(), otherLayers);
    BOOST_CHECK_EQUAL(matr.getMaxInLayer(), otherMaxInLayer);
    BOOST_CHECK_EQUAL(otherMatr.getLayers(), 0);
    BOOST_CHECK_EQUAL(otherMatr.getMaxInLayer(), 0);
  }

  BOOST_AUTO_TEST_CASE(CopyAssigmentOperatorTest)
  {
    std::shared_ptr <belonogova::Shape> rect =
    std::make_shared<belonogova::Rectangle>(belonogova::Rectangle({1.0, 2.0, {-3.0, -4.0}}));
    std::shared_ptr <belonogova::Shape> circ =
    std::make_shared<belonogova::Circle>(belonogova::Circle(2.0, {13.0, 5.0}));
    belonogova::Matrix otherMatr;
    otherMatr.addShapeToLayer(rect);
    otherMatr.addShapeToLayer(circ);
    belonogova::Matrix matr = otherMatr;
    BOOST_CHECK_EQUAL(matr.getLayers(), otherMatr.getLayers());
    BOOST_CHECK_EQUAL(matr.getMaxInLayer(), otherMatr.getMaxInLayer());
  }

  BOOST_AUTO_TEST_CASE(MoveAssigmentOperatorTest)
  {
    std::shared_ptr <belonogova::Shape> rect =
    std::make_shared<belonogova::Rectangle>(belonogova::Rectangle({1.0, 2.0, {-3.0, -4.0}}));
    std::shared_ptr <belonogova::Shape> circ =
    std::make_shared<belonogova::Circle>(belonogova::Circle(2.0, {13.0, 5.0}));
    belonogova::Matrix otherMatr;
    otherMatr.addShapeToLayer(rect);
    otherMatr.addShapeToLayer(circ);
    double otherLayers = otherMatr.getLayers();
    double otherMaxInLayer = otherMatr.getMaxInLayer();
    belonogova::Matrix matr = std::move(otherMatr);

    BOOST_CHECK_EQUAL(matr.getLayers(), otherLayers);
    BOOST_CHECK_EQUAL(matr.getMaxInLayer(), otherMaxInLayer);
    BOOST_CHECK_EQUAL(otherMatr.getLayers(), 0);
    BOOST_CHECK_EQUAL(otherMatr.getMaxInLayer(), 0);
  }

  BOOST_AUTO_TEST_CASE(FormingTest)
  {
    std::shared_ptr <belonogova::Shape> rect0 =
    std::make_shared<belonogova::Rectangle>(belonogova::Rectangle({2.0, 1.0, {-5.0, 5.0}}));
    std::shared_ptr <belonogova::Shape> circ1 =
    std::make_shared<belonogova::Circle>(belonogova::Circle(3.0, {0.0, 0.0}));
    std::shared_ptr <belonogova::Shape> rect2 =
    std::make_shared<belonogova::Rectangle>(belonogova::Rectangle({4.0, 1.0, {-1.0, 0.0}}));
    belonogova::CompositeShape comp(rect0);
    comp.addComponent(circ1);
    comp.addComponent(rect2);
    belonogova::Matrix matr = comp.formMatrix();

    BOOST_CHECK_EQUAL(matr.getLayers(), 2);
    BOOST_CHECK_EQUAL(matr.getMaxInLayer(), 2);
    BOOST_CHECK_EQUAL(matr[0][0], rect0);
    BOOST_CHECK_EQUAL(matr[0][1], circ1);
    BOOST_CHECK_EQUAL(matr[1][0], rect2);
  }

BOOST_AUTO_TEST_SUITE_END()
