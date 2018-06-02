//
// Created by Yaroslav on 30.03.2018.
//

#ifndef LABA1_RECTANGLE_HPP
#define LABA1_RECTANGLE_HPP

#include "shape.hpp"

namespace erokhin
{
    class Rectangle : public Shape {
    public:
        Rectangle(const point_t &pos, const double width, const double height);
        double getArea() const override;
        rectangle_t getFrameRect() const override;
        void move(const double dx, const double dy) override;
        void move(const point_t &p) override;
        void scale(const double x) override;
        void rotate(const double degrees) override;
        void viewName() const override ;
    private:
        double width_, height_;
        point_t posit_;
        double angle_;
        double rectw_, recth_;
    };
}
#endif //LABA1_RECTANGLE_HPP
