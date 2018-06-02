#ifndef COMPOSITESHAPE_HEADER
#define COMPOSITESHAPE_HEADER

#include <memory>
#include "shape.hpp"

namespace zasyadko
{
class CompositeShape:
  public Shape
{
public:

  CompositeShape(const std::shared_ptr< Shape > shape);
  CompositeShape(const CompositeShape & copyshape);
  CompositeShape(CompositeShape && moveShape);
  CompositeShape & operator= (const CompositeShape & copyshape);
  CompositeShape & operator= (CompositeShape && moveShape);
  
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  int getAmount() const;
  std::shared_ptr<Shape> getShapeInfo(const int number) const;
  
  void move(const point_t & Center) override;
  void move(const double add_x, const double add_y) override;
  void scale(const double factor) override;
  void print() const;
  void addShape(const std::shared_ptr <Shape> new_shape);
  void deleteShape(const int number);
  void deleteAll();
  
 private:
 
  std::unique_ptr < std::shared_ptr < Shape > [] > shapes;
  
  int amount;
};
}
#endif
