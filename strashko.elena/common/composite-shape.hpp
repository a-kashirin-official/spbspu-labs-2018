#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP

#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "shape.hpp"

namespace strashko
{
  class CompositeShape: public strashko::Shape
  {
  public:
    CompositeShape();
    CompositeShape(const std::shared_ptr< strashko::Shape > shape);
    ~CompositeShape();

    CompositeShape (const CompositeShape &rhs); //конструктор копирования
    CompositeShape (CompositeShape &&rhs);
    std::shared_ptr< strashko::Shape > &operator[](int i) const;
    CompositeShape &operator=(const CompositeShape &rhs);
    CompositeShape &operator=(CompositeShape &&rhs);

    double getArea() const noexcept override;
    strashko::rectangle_t getFrameRect() const noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void move(const strashko::point_t &newcentre) noexcept override;
    void scale(const double factor) override;
    void rotate(const double angle) noexcept override;

    void addShape(std::shared_ptr< strashko::Shape > shape);
    void removeShape(const int shapeNumber);
    void deleteAllShapes() noexcept;
    int getCount() const noexcept;
    std::unique_ptr<strashko::Shape> getCopy() const noexcept override;
    void printInfo() const override;

  private:
    int count_;
    std::unique_ptr< std::shared_ptr< strashko::Shape >[] > arrayOfShapes_;
    double angle_;
  };
}

#endif // COMPOSITESHAPE_HPP
