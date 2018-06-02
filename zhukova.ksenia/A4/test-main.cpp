#define BOOST_TEST_MODULE Tests
#include <boost/test/included/unit_test.hpp>
#include <boost/shared_array.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

const double DELTA_REL = 0.00001;

BOOST_AUTO_TEST_SUITE( Matrix_Test )

BOOST_AUTO_TEST_CASE( Matrix_CopyConstructor_CorrectSplitting )
{
  std::shared_ptr<zhukova::Shape> rect_ptr{ new zhukova::Rectangle( { 5.0, 5.0 }, 5.0, 5.0) };
  zhukova::CompositeShape compShape(rect_ptr);

  rect_ptr = std::shared_ptr<zhukova::Shape>{ new zhukova::Rectangle( { 6.0, 6.0 }, 5.0, 5.0) };
  compShape.addElement(rect_ptr);

  rect_ptr = std::shared_ptr<zhukova::Shape>{ new zhukova::Rectangle( { 30.0, 30.0 }, 5.0, 5.0) };
  compShape.addElement(rect_ptr);

  zhukova::Matrix M(compShape);

  zhukova::Matrix copyMatrix(M);

  BOOST_CHECK_CLOSE( copyMatrix[0][0]->getFrameRect().pos.x, 5, DELTA_REL );
  BOOST_CHECK_CLOSE( copyMatrix[0][0]->getFrameRect().pos.y, 5, DELTA_REL );

  BOOST_CHECK_CLOSE( copyMatrix[0][1]->getFrameRect().pos.x, 30, DELTA_REL );
  BOOST_CHECK_CLOSE( copyMatrix[0][1]->getFrameRect().pos.y, 30, DELTA_REL );

  BOOST_CHECK_CLOSE( copyMatrix[1][0]->getFrameRect().pos.x, 6, DELTA_REL );
  BOOST_CHECK_CLOSE( copyMatrix[1][0]->getFrameRect().pos.y, 6, DELTA_REL );
}

BOOST_AUTO_TEST_CASE( Matrix_AssignmentOperator )
{
  std::shared_ptr<zhukova::Shape> rect_ptr{ new zhukova::Rectangle( { 5.0, 5.0 }, 5.0, 5.0) };
  zhukova::CompositeShape compShape(rect_ptr);

  rect_ptr = std::shared_ptr<zhukova::Shape>{ new zhukova::Rectangle( { 6.0, 6.0 }, 5.0, 5.0) };
  compShape.addElement(rect_ptr);

  rect_ptr = std::shared_ptr<zhukova::Shape>{ new zhukova::Rectangle( { 30.0, 30.0 }, 5.0, 5.0) };
  compShape.addElement(rect_ptr);

  zhukova::Matrix M(compShape);

  zhukova::Matrix copyMatrix = M;

  BOOST_CHECK_CLOSE( copyMatrix[0][0]->getFrameRect().pos.x, 5, DELTA_REL );
  BOOST_CHECK_CLOSE( copyMatrix[0][0]->getFrameRect().pos.y, 5, DELTA_REL );

  BOOST_CHECK_CLOSE( copyMatrix[0][1]->getFrameRect().pos.x, 30, DELTA_REL );
  BOOST_CHECK_CLOSE( copyMatrix[0][1]->getFrameRect().pos.y, 30, DELTA_REL );

  BOOST_CHECK_CLOSE( copyMatrix[1][0]->getFrameRect().pos.x, 6, DELTA_REL );
  BOOST_CHECK_CLOSE( copyMatrix[1][0]->getFrameRect().pos.y, 6, DELTA_REL );
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE( CompositeShape_Test )

  BOOST_AUTO_TEST_CASE( CompositeShape_ParametersPermanence )
  {
    std::shared_ptr<zhukova::Shape> newElem{ new zhukova::Rectangle( { 3.0, 3.0 }, 7.0, 1.0 ) };
    zhukova::CompositeShape compShape( newElem );
    double initialArea = compShape.getArea();

    compShape.move( 21.0, 21.0 );

    BOOST_CHECK_CLOSE( compShape.getFrameRect().width, 7.0, DELTA_REL );
    BOOST_CHECK_CLOSE( compShape.getFrameRect().height, 1.0, DELTA_REL );
    BOOST_CHECK_CLOSE( compShape.getArea(), initialArea, DELTA_REL );
  }

  BOOST_AUTO_TEST_CASE( CompositeShape_Scale )
  {
    std::shared_ptr<zhukova::Shape> newElem{ new zhukova::Rectangle( { 3.0, 3.0 }, 7.0, 1.0 ) };
    zhukova::CompositeShape compShape( newElem );
    double initialArea = compShape.getArea();
    double initialCenterX = compShape.getFrameRect().pos.x;
    double initialCenterY = compShape.getFrameRect().pos.y;

    compShape.scale( 7.0 );

    BOOST_CHECK_CLOSE( compShape.getArea(), initialArea * pow(7.0, 2.0), DELTA_REL );
    BOOST_CHECK_CLOSE( compShape.getFrameRect().pos.x, initialCenterX, DELTA_REL );
    BOOST_CHECK_CLOSE( compShape.getFrameRect().pos.y, initialCenterY, DELTA_REL );
  }

  BOOST_AUTO_TEST_CASE( CompositeShape_ConstructorParameters )
  {
    BOOST_CHECK_THROW( zhukova::CompositeShape compShape( std::shared_ptr<zhukova::Shape>
        { new zhukova::Rectangle( { 3.0, 3.0 }, -7.0, 1.0 ) } ), std::invalid_argument );
    BOOST_CHECK_THROW( zhukova::CompositeShape compShape( std::shared_ptr<zhukova::Shape>
        { new zhukova::Rectangle( { 3.0, 3.0 }, 7.0, -1.0 ) } ), std::invalid_argument );
    BOOST_CHECK_THROW( zhukova::CompositeShape compShape( std::shared_ptr<zhukova::Shape>
        { new zhukova::Circle( { 7.0, 7.0 }, -11.0 ) } ), std::invalid_argument );

    BOOST_CHECK_THROW( zhukova::CompositeShape compShape( nullptr ), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE( CompositeShape_ScalingFactor )
  {
    std::shared_ptr<zhukova::Shape> testElem{ new zhukova::Circle( { 3.0, 3.0 }, 7.0 ) };
    zhukova::CompositeShape compShape( testElem );

    BOOST_CHECK_THROW( compShape.scale( -17.0 ), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE( CompositeShape_AddingElement )
  {
    std::shared_ptr<zhukova::Shape> firstElem{ new zhukova::Circle( { 3.0, 3.0 }, 7.0 ) };
    zhukova::CompositeShape compShape( firstElem );

    BOOST_CHECK_THROW( compShape.addElement( nullptr ), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE( CompositeShape_CopyConstructor )
  {
    std::shared_ptr<zhukova::Shape> rect_ptr{ new zhukova::Rectangle( { 3.0, 3.0 }, 13.0, 17.0 ) };
    zhukova::CompositeShape compShape(rect_ptr);

    zhukova::CompositeShape copyCompShape(compShape);

    copyCompShape.move({ 0, 0 });

    BOOST_CHECK_CLOSE( compShape.getFrameRect().pos.x, 0, DELTA_REL );
    BOOST_CHECK_CLOSE( compShape.getFrameRect().pos.y, 0, DELTA_REL );

    BOOST_CHECK_CLOSE( copyCompShape.getFrameRect().pos.x, 0, DELTA_REL );
    BOOST_CHECK_CLOSE( copyCompShape.getFrameRect().pos.y, 0, DELTA_REL );
  }

  BOOST_AUTO_TEST_CASE( CompositeShape_AssignmentOperator )
  {
    std::shared_ptr<zhukova::Shape> rect_ptr{ new zhukova::Rectangle( { 3.0, 3.0 }, 13.0, 17.0 ) };
    zhukova::CompositeShape compShape(rect_ptr);

    zhukova::CompositeShape copyCompShape(rect_ptr);

    copyCompShape = compShape;

    copyCompShape.move({ 0, 0 });

    BOOST_CHECK_CLOSE( compShape.getFrameRect().pos.x, 0, DELTA_REL );
    BOOST_CHECK_CLOSE( compShape.getFrameRect().pos.y, 0, DELTA_REL );

    BOOST_CHECK_CLOSE( copyCompShape.getFrameRect().pos.x, 0, DELTA_REL );
    BOOST_CHECK_CLOSE( copyCompShape.getFrameRect().pos.y, 0, DELTA_REL );
  }

  BOOST_AUTO_TEST_CASE( CompositeShape_Rotate )
  {
    std::shared_ptr<zhukova::Shape> rect_ptr2{ new zhukova::Rectangle( { 5.0, 5.0 }, 11.0, 5.0 ) };
    zhukova::CompositeShape compShape(rect_ptr2);

    rect_ptr2 = std::shared_ptr<zhukova::Shape>{ new zhukova::Rectangle( { -5.0, -5.0 }, 13.0, 6.0 ) };
    compShape.addElement(rect_ptr2);

    compShape.rotate( 180 );
    
    BOOST_CHECK_CLOSE( compShape[0]->getFrameRect().pos.x, -5, DELTA_REL );
    BOOST_CHECK_CLOSE( compShape[0]->getFrameRect().pos.y, -5, DELTA_REL );

    BOOST_CHECK_CLOSE( compShape[1]->getFrameRect().pos.x, 5, DELTA_REL );
    BOOST_CHECK_CLOSE( compShape[1]->getFrameRect().pos.y, 5, DELTA_REL );

    BOOST_CHECK_CLOSE( compShape[0]->getFrameRect().width, 11, DELTA_REL );
    BOOST_CHECK_CLOSE( compShape[0]->getFrameRect().height, 5, DELTA_REL );

    BOOST_CHECK_CLOSE( compShape[1]->getFrameRect().width, 13, DELTA_REL );
    BOOST_CHECK_CLOSE( compShape[1]->getFrameRect().height, 6, DELTA_REL );
  }

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE( Rectangle_Test )

  BOOST_AUTO_TEST_CASE( Rectangle_ParametersPermanence )
  {
    zhukova::Rectangle rect( { 3.0, 3.0 }, 7.0, 1.0 );
    double initialArea = rect.getArea();

    rect.move( 21.0, 21.0 );

    BOOST_CHECK_EQUAL( rect.getFrameRect().width, 7.0 );
    BOOST_CHECK_EQUAL( rect.getFrameRect().height, 1.0 );
    BOOST_CHECK_EQUAL( rect.getArea(), initialArea );
  }

  BOOST_AUTO_TEST_CASE( Rectangle_Scale )
  {
    zhukova::Rectangle rect( { 3.0, 3.0 }, 7.0, 1.0 );
    double initialArea = rect.getArea();

    rect.scale( 7.0 );

    BOOST_CHECK_CLOSE( rect.getArea(), initialArea * pow(7.0, 2.0), DELTA_REL );
  }

  BOOST_AUTO_TEST_CASE( Rectangle_ConstructorParameters )
  {
    BOOST_CHECK_THROW( zhukova::Rectangle rect( { 3.0, 3.0 }, -7.0, 1.0 ), std::invalid_argument );
    BOOST_CHECK_THROW( zhukova::Rectangle rect( { 3.0, 3.0 }, 7.0, -1.0 ), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE( Rectangle_ScalingFactor )
  {
    zhukova::Rectangle rect( { 3.0, 3.0 }, 7.0, 1.0 );

    BOOST_CHECK_THROW( rect.scale(-17.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE( Circle_Test )

  BOOST_AUTO_TEST_CASE( Circle_ParametersPermanence )
  {
    zhukova::Circle circ( { 7.0, 7.0 }, 11.0 );
    double initialArea = circ.getArea();

    circ.move( 21.0, 21.0 );

    BOOST_CHECK_EQUAL( circ.getFrameRect().width / 2, 11.0 );
    BOOST_CHECK_EQUAL( circ.getArea(), initialArea );
  }

  BOOST_AUTO_TEST_CASE( Circle_Scale )
  {
    zhukova::Circle circ( { 7.0, 7.0 }, 11.0 );
    double initialArea = circ.getArea();

    circ.scale( 7.0 );

    BOOST_CHECK_CLOSE( circ.getArea(), initialArea * pow(7.0, 2.0), DELTA_REL );
  }

  BOOST_AUTO_TEST_CASE( Circle_ConstructorParameters )
  {
    BOOST_CHECK_THROW( zhukova::Circle circ( { 7.0, 7.0 }, -11.0 ), std::invalid_argument );
  }

  BOOST_AUTO_TEST_CASE( Circle_ScalingFactor )
  {
    zhukova::Circle circ( { 7.0, 7.0 }, 11.0 );
    BOOST_CHECK_THROW( circ.scale(-11.0), std::invalid_argument );
  }

BOOST_AUTO_TEST_SUITE_END()
