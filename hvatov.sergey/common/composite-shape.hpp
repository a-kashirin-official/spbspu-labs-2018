#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include "circle.hpp"
#include "rectangle.hpp"
#include "shape.hpp"

#include <memory>

namespace hvatov
{
  // Composite Shape container class
  class CompositeShape :
    public Shape
  {
    // Public members
  public:
    // Default class constructor
    CompositeShape();

    // Fill class constructor
    CompositeShape(const std::shared_ptr< Shape > & ptr);

    // Copying class constructor
    CompositeShape(const CompositeShape & other);
    
    // Moving class constructor
    CompositeShape(CompositeShape && other);

    // Class destructor
    ~CompositeShape();

    // Copying operator = overload
    CompositeShape & operator=(const CompositeShape & other);
    // Moving operator = overload
    CompositeShape & operator=(CompositeShape && other);

    // Operator + overload
    CompositeShape operator+(const CompositeShape & other);

    // Operator [] overload
    const std::shared_ptr<Shape> & operator[](size_t index) const;
    std::shared_ptr<Shape> & operator[](size_t index);

    // Get total area method
    virtual double getArea() const noexcept override;
    
    // Get total frame rect
    virtual rectangle_t getFrameRect() const noexcept override;
    
    // Move all objects methods
    virtual void move(const point_t & pos) noexcept;
    virtual void move(double dx, double dy) noexcept;
    
    // Scale all objects
    virtual void scale(double k) override;
    // Rotate method
    virtual void rotate(double angle) noexcept override;
    
    // Get info method
    virtual std::ostream & getInfo(std::ostream & stream) const noexcept override;
    
    // Get psotion method
    virtual point_t getPosition() const noexcept override;

    // Add new element method
    void addElement(const std::shared_ptr< Shape > & ptr);
    
    // Delete element # index method
    void deleteElement(size_t index);
    
    // Get the size of the constainer method
    size_t getSize() const noexcept;
    
    // Clear the container method
    void clear() noexcept;

    // stream ouput operator override
    friend std::ostream & operator<<(std::ostream & str, const CompositeShape & container);

    // Private members
  private:
    // Current size of the container
    size_t size_;
    // Array of pointers to 
    // the base Shape class
    ArrayType<Shape> array_;
  };

  // stream ouput operator override
  std::ostream & operator<<(std::ostream & str, const CompositeShape & container);
}

#endif // COMPOSITE_SHAPE_HPP

