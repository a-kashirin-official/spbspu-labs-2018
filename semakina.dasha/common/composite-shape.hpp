#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace semakina
{
  class CompositeShape:
    public semakina::Shape
  {
  public:
    CompositeShape(const std::shared_ptr <semakina::Shape> shape);
    CompositeShape(const semakina::CompositeShape & compositeshape);
    CompositeShape & operator = (const CompositeShape & compositeshape) noexcept;
    std::shared_ptr<semakina::Shape> operator[](const int index) const;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t & pos) noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double degree) noexcept override;

    void addShape(const std::shared_ptr <semakina::Shape> shape);
    void deleteShape(const int i);
    void clear() noexcept;
    int getCounter() const noexcept;

  private:
    int counter_;
    double degree_;
    std::unique_ptr < std::shared_ptr <semakina::Shape>[] > array_;
  };
}

#endif // COMPOSITESHAPE_HPP
