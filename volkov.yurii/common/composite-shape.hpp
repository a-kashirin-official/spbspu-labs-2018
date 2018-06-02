#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace volkov
{
  class CompositeShape:
    public volkov::Shape
  {
  public:
    CompositeShape(const std::shared_ptr <volkov::Shape> shape_n);
    CompositeShape(const volkov::CompositeShape &copy);
    CompositeShape(volkov::CompositeShape &&move) = default;
    CompositeShape & operator=(const volkov::CompositeShape &copy);
    CompositeShape & operator=(volkov::CompositeShape &&move);
    double getArea() const override;
    volkov::rectangle_t getFrameRect() const override;
    void move(const volkov::point_t & centr_n) override;
    void move(const double dx, const double dy) override;
    void scale(const double f) override;
    void addShape(std::shared_ptr <volkov::Shape> shape_n);
    std::shared_ptr < volkov::Shape > getShape(int const shN) const;
    void removeShape(const int shN);
    void deleteShapes();
    int getSize() const;
  private:
    std::unique_ptr <std::shared_ptr <volkov::Shape>[] > parts_;
    int size_;
  };
}

