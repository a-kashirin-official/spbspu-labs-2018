#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstdlib>
#include <new>
#include <stdexcept>

namespace pashin {
  namespace detail {
    template<typename T>
    class Array
    {
    public:
      Array():
        size_(0),
        capacity_(2),
        data_(static_cast<T*>(malloc(capacity_ * sizeof(T))))
      {
        if (!data_) {
          throw std::bad_alloc();
        }
      }
      
      ~Array()
      {
        clear();
      }
      
      friend bool operator==(const Array<T>& lhs, const Array<T>& rhs)
      {
        if (lhs.size_ != rhs.size_) {
          return false;
        }
        for (int i = 0; i < static_cast<int>(lhs.size_); ++i) {
          if (lhs[i] != rhs[i]) {
            return false;
          }
        }
        return true;
      }
      
      T& operator[](std::size_t idx) const
      {
        if (!(idx >= 0 && idx < size_)) {
          throw std::runtime_error("Index out of range");
        }
        return *(data_ + idx);
      }
      
      T* begin() const
      {
        return data_;
      }
      
      T* end() const
      {
        return data_ + size_;
      }
      
      size_t size() const
      {
        return size_;
      }
      
      size_t capacity() const
      {
        return capacity_;
      }
      
      bool empty() const
      {
        if (size_ == 0) {
          return true;
        } else {
          return false;
        }
      }
      
      void resize()
      {
        capacity_ *= 2;
        T* temp = static_cast<T*>(realloc(data_, capacity_ * sizeof(T)));
        if (!temp) {
          throw std::bad_alloc();
        }
        data_ = temp;
      }
      
      void clear()
      {
        free(data_);
      }
      
      void push_back(const T& object)
      {
        if (size_ == capacity_) {
          resize();
        }
        *(data_ + size_) = object;
        ++size_;
      }
      
      void erase(T* pos)
      {
        if (!((pos >= data_) && (pos < data_ + size_))) {
          throw std::runtime_error("Element not found");
        }
        for (auto it = pos; it < end() - 1; ++it) {
          *it = *(it + 1);
        }
        --size_;
      }
      
    private:
      size_t size_;
      size_t capacity_;
      T* data_;
    };
  }
}

#endif  // ARRAY_HPP
