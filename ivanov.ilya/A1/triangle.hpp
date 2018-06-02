#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"

class Triangle : public Shape
{
public:
    Triangle(const point_t & value_A, const point_t & value_B, const point_t & value_C);
    void show() const override;
    void setPoints(const point_t & value_A, const point_t & value_B, const point_t & value_C);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & point) override;
    void move(double dx, double dy) override;
private:
    point_t pos_;
    point_t A_vershina_;
    point_t B_vershina_;
    point_t C_vershina_;
    static double getMin(const double & value_A, const double & value_B, const double & value_C);
    static double getMax(const double & value_A, const double & value_B, const double & value_C);
};
#endif
