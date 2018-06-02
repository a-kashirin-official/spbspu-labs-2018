//
// Created by Yaroslav on 13.04.2018.
//

#define BOOST_TEST_MODULE testmain
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

erokhin::Rectangle rect({7.0, 17.0}, 3.7, 5.3);
erokhin:: point_t pos{45.0, 36.0};
const double dx = 0.000001;

BOOST_AUTO_TEST_SUITE(testRectangle)
    BOOST_AUTO_TEST_CASE(test_Rect_move1)
    {
        rect.move(13.0, 13.0);
        BOOST_CHECK_EQUAL(rect.getFrameRect().pos.x, 20.0);
        BOOST_CHECK_EQUAL(rect.getFrameRect().pos.y, 30.0);
    }
    BOOST_AUTO_TEST_CASE(test_Rect_move2)
    {
        rect.move(pos);
        BOOST_CHECK_EQUAL(rect.getFrameRect().pos.x, 45.0);
        BOOST_CHECK_EQUAL(rect.getFrameRect().pos.y, 36.0);
    }

    BOOST_AUTO_TEST_CASE(test_Rect_move_width)
    {
        rect.move(13.0, 13.0);
        BOOST_CHECK_EQUAL(rect.getFrameRect().width, 3.7);
    }

    BOOST_AUTO_TEST_CASE(test_Rect_move_height)
    {
        rect.move(13.0, 13.0);
        BOOST_CHECK_EQUAL(rect.getFrameRect().height, 5.3);
    }

    BOOST_AUTO_TEST_CASE(test_Rect_move_area)
    {
        double area = rect.getArea();
        rect.move(pos);
        BOOST_CHECK_CLOSE_FRACTION(area, rect.getArea(), dx);
    }

    BOOST_AUTO_TEST_CASE(test_Rect_scale_area)
    {
        double area = rect.getArea();
        rect.scale(6.7);
        BOOST_CHECK_CLOSE_FRACTION(rect.getArea(), area * 6.7 * 6.7, dx);
    }

    BOOST_AUTO_TEST_CASE(test_Rect_init_exception)
    {
        BOOST_CHECK_THROW(erokhin::Rectangle rect1({7.0, 7.0}, -3.0, 7.0), std::invalid_argument);
        BOOST_CHECK_THROW(erokhin::Rectangle rect2({7.0, 7.0}, 3.0, -7.0), std::invalid_argument);
        BOOST_CHECK_THROW(erokhin::Rectangle rect3({7.0, 7.0}, -3.0, -7.0), std::invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(test_Rect_scale_exception)
    {
        BOOST_CHECK_THROW(rect.scale(-58.0), std::invalid_argument);
    }
BOOST_AUTO_TEST_SUITE_END();

erokhin::Circle circ({7.0, 7.0}, 3.7);

BOOST_AUTO_TEST_SUITE(testCircle)
    BOOST_AUTO_TEST_CASE(test_Circ_move_width)
    {
        circ.move(13.0, 13.0);
        BOOST_CHECK_EQUAL(circ.getFrameRect().width/2, 3.7);
    }

    BOOST_AUTO_TEST_CASE(test_Circ_move_area)
    {
        double area = circ.getArea();
        circ.move(pos);
        BOOST_CHECK_CLOSE_FRACTION(area, circ.getArea(), dx);
    }

    BOOST_AUTO_TEST_CASE(test_Circ_scale_area)
    {
        double area = circ.getArea();
        circ.scale(6.7);
        BOOST_CHECK_CLOSE_FRACTION(circ.getArea(), area * 6.7 * 6.7, dx);
    }

    BOOST_AUTO_TEST_CASE(test_Circ_init_exception)
    {
        BOOST_CHECK_THROW(erokhin::Circle circ1({7.0, 7.0}, -3.0), std::invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(test_circ_scale_exception)
    {
        BOOST_CHECK_THROW(circ.scale(-58.0), std::invalid_argument);
    }
BOOST_AUTO_TEST_SUITE_END()

erokhin::Circle circ2({0.0, 0.0}, 5.0);
erokhin::Rectangle rect2{{10.0, 10.0}, 6.0, 4.0};
std::shared_ptr <erokhin::Shape> ptrcirc2 = std::make_shared <erokhin::Circle> (circ2);
std::shared_ptr <erokhin::Shape> ptrrect2 = std::make_shared <erokhin::Rectangle> (rect2);
erokhin::CompositeShape composite;

BOOST_AUTO_TEST_SUITE(testCompositeShape)
    BOOST_AUTO_TEST_CASE(test_compshape_move1)
    {
        composite.move(10.4, 10.6);
        BOOST_CHECK_EQUAL(composite.getFrameRect().pos.x, 10.4);
        BOOST_CHECK_EQUAL(composite.getFrameRect().pos.y, 10.6);
    }

    BOOST_AUTO_TEST_CASE(test_compshape_move2)
    {
        erokhin::point_t point2 = {0.0, 0.0};
        composite.move(point2);
        BOOST_CHECK_EQUAL(composite.getFrameRect().pos.x, 0.0);
        BOOST_CHECK_EQUAL(composite.getFrameRect().pos.y, 0.0);
    }

    BOOST_AUTO_TEST_CASE(test_compshape_scale_exception1)
    {
        BOOST_CHECK_THROW(composite.scale(5.0), std::invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(test_compshape_area1)
    {
        BOOST_CHECK_EQUAL(composite.getArea(), 0.0);
    }

    BOOST_AUTO_TEST_CASE(test_compshape_add)
    {
        composite.add(ptrcirc2);
        BOOST_CHECK_EQUAL(composite.getFrameRect().height / 2, 5.0);
        BOOST_CHECK_EQUAL(composite.getFrameRect().width / 2, 5.0);
    }

    BOOST_AUTO_TEST_CASE(test_compshape_area2)
    {
        double area = composite.getArea();
        composite.scale(4);
        BOOST_CHECK_CLOSE_FRACTION(composite.getArea(), area * 16.0, dx);
    }

    BOOST_AUTO_TEST_CASE(test_compshape_area3)
    {
        double area = composite.getArea();
        composite.add(ptrrect2);
        BOOST_CHECK_CLOSE_FRACTION(composite.getArea(), area + 24.0, dx);
    }

    BOOST_AUTO_TEST_CASE(test_compshape_getFrameRect)
    {
        BOOST_CHECK_EQUAL(composite.getFrameRect().width, 40.0);
        BOOST_CHECK_EQUAL(composite.getFrameRect().height, 40.0);
    }

    BOOST_AUTO_TEST_CASE(test_compshape_add_exception)
    {
        BOOST_CHECK_THROW(composite.add(nullptr), std::invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(test_compshape_scale_exception2)
    {
        composite.add(ptrcirc2);
        BOOST_CHECK_THROW(composite.scale(-5.0), std::invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(test_compshape_constr)
    {
        erokhin::CompositeShape composite2(ptrrect2);
        BOOST_CHECK_EQUAL(composite2.getArea(), 24.0);
    }

BOOST_AUTO_TEST_SUITE_END()

erokhin::Matrix matrix;
erokhin::Rectangle rect3({10.0, 10.0}, 4.0, 5.0);
erokhin::Circle circ3({0.0, 0.0}, 5.0);
std::shared_ptr <erokhin::Rectangle> ptrrect3 = std::make_shared <erokhin::Rectangle> (rect3);
std::shared_ptr <erokhin::Circle> ptrcirc3 = std::make_shared <erokhin::Circle> (circ3);
std::shared_ptr <erokhin::CompositeShape> ptrcompos= std::make_shared <erokhin::CompositeShape> (ptrrect3);

BOOST_AUTO_TEST_SUITE(testMatrix)
    BOOST_AUTO_TEST_CASE(test_matrix_add)
    {
        BOOST_CHECK_EQUAL(matrix.getRows(), 0);
        BOOST_CHECK_EQUAL(matrix.getColumns(), 0);
    }

    BOOST_AUTO_TEST_CASE(test_matrix_add2)
    {
        matrix.add(ptrrect3);
        BOOST_CHECK_EQUAL(matrix.getRows(), 1);
        BOOST_CHECK_EQUAL(matrix.getColumns(), 1);
    }

    BOOST_AUTO_TEST_CASE(test_matrix_add3)
    {
        matrix.add(ptrcirc3);
        BOOST_CHECK_EQUAL(matrix.getRows(), 1);
        BOOST_CHECK_EQUAL(matrix.getColumns(), 2);
    }

    BOOST_AUTO_TEST_CASE(test_matrix_add4)
    {
        ptrcompos->add(ptrcirc2);
        matrix.add(ptrcompos);
        BOOST_CHECK_EQUAL(matrix.getRows(), 2);
        BOOST_CHECK_EQUAL(matrix.getColumns(), 2);
    }

    BOOST_AUTO_TEST_CASE(test_matrix_exception)
    {
        BOOST_CHECK_THROW(matrix.add(nullptr), std::invalid_argument);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_figure_rotate)
    BOOST_AUTO_TEST_CASE(test_rotate)
    {
        rect3.rotate(90);
        BOOST_CHECK_EQUAL(rect3.getFrameRect().width, 5.0);
        BOOST_CHECK_EQUAL(rect3.getFrameRect().height, 4.0);
    }

    BOOST_AUTO_TEST_CASE(test_rotate2)
    {
        rect3.rotate(270);
        BOOST_CHECK_CLOSE_FRACTION(rect3.getFrameRect().width, 4.0, dx);
        BOOST_CHECK_CLOSE_FRACTION(rect3.getFrameRect().height, 5.0, dx);
    }

    BOOST_AUTO_TEST_CASE(test_rotate3)
    {
        rect3.rotate(45);
        BOOST_CHECK_CLOSE_FRACTION(rect3.getFrameRect().width, rect3.getFrameRect().height, dx);
    }

    BOOST_AUTO_TEST_CASE(test_rotate4)
    {
        rect3.rotate(55);
        BOOST_CHECK_EQUAL(rect3.getFrameRect().pos.x, 10.0);
        BOOST_CHECK_EQUAL(rect3.getFrameRect().pos.y, 10.0);
    }

    BOOST_AUTO_TEST_CASE(test_rotate5)
    {
        circ3.rotate(45);
        BOOST_CHECK_EQUAL(circ3.getFrameRect().width / 2, 5.0);
        BOOST_CHECK_EQUAL(circ3.getFrameRect().height / 2, 5.0);
    }
BOOST_AUTO_TEST_SUITE_END()
