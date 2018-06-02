//#ifndef A1_RECTANGLE_HPP
//#define A1_RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
    Rectangle(const point_t & center, const double w, const double h);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move (const point_t & newPoint) override;
    void move (const double dx, const double dy) override;
private:
    rectangle_t rect_;
};

//#endif //A1_RECTANGLE_HPP
