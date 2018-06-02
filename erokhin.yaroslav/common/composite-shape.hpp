//
// Created by Yaroslav on 27.04.2018.
//

#ifndef LABA1_COMPOSITE_SHAPE_HPP
#define LABA1_COMPOSITE_SHAPE_HPP

#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "base-types.hpp"

namespace erokhin
{
    class CompositeShape : public Shape
    {
    public:
        CompositeShape();
        CompositeShape(const std::shared_ptr<Shape> figure);
        double getArea() const override;
        rectangle_t getFrameRect() const override;
        void move(const double dx, const double dy) override;
        void move(const point_t &p) override;
        void scale(const double x) override;
        void add(const std::shared_ptr<Shape> figure);
        void rotate(const double degrees) override;
        void viewName() const override;
    private:
        bool access_;
        point_t posit_;
        std::unique_ptr<std::shared_ptr<Shape> []> digest_;
        unsigned int size_;
        inline point_t maxXY() const;
        inline point_t minXY() const;
    };
}

#endif //LABA1_COMPOSITE_SHAPE_HPP
