#ifndef composite_shape_hpp
#define composite_shape_hpp

#include <memory>
#include "shape.hpp"

namespace vlasov {

  class CompositeShape : public Shape
  {
    public:
    explicit CompositeShape(std::shared_ptr<Shape> newShape);
    CompositeShape();
    void move(const point_t& point) override;
    void move(const double dx, const double dy) override;
    void scale(const double extender) override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
        
    void add(const std::shared_ptr<Shape> newShape);
    void remove(const int index);

    private:
    int amount_;
    std::unique_ptr<std::shared_ptr<Shape>[]> shapes_;
    };
}
#endif
