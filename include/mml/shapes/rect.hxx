//
// rect.hxx for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_RECT_HXX_
# define MML_RECT_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "mml/shapes/rect.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{

  namespace il
  {


    // constructors

    template <typename T>
    Rect<T>::Rect() throw()
    {
    }

    template <typename T>
    Rect<T>::Rect(const ExactPoint& min, const ExactPoint& max) throw()
      : min_(min), max_(max)
    {
    }

    template <typename T>
    Rect<T>::Rect(PrmValueType xmin, PrmValueType ymin, PrmValueType xmax, PrmValueType ymax) throw()
      : min_(xmin, ymin), max_(xmax, ymax)
    {
    }


    template <typename T>
    inline Rect<T>
    Rect<T>::absolute(const ExactPoint& min, const ExactPoint& max)
    {
      return Rect(min, max);
    }

    template <typename T>
    inline Rect<T>
    Rect<T>::absolute(PrmValueType xmin, PrmValueType ymin, PrmValueType xmax, PrmValueType ymax)
    {
      return Rect(xmin, ymin, xmax, ymax);
    }

    template <typename T>
    inline Rect<T>
    Rect<T>::relative(const ExactPoint& min, const ExactVector& delta)
    {
      return absolute(min, min + delta);
    }

    template <typename T>
    inline Rect<T>
    Rect<T>::relative(PrmValueType xmin, PrmValueType ymin, PrmValueType dx , PrmValueType dy)
    {
      return absolute(xmin, ymin, xmin + dx, ymin + dy);
   }



    // accessors

    template <typename T>
    inline const typename Rect<T>::ExactPoint&
    Rect<T>::min() const
    {
      return min_;
    }

    template <typename T>
    inline const typename Rect<T>::ExactPoint&
    Rect<T>::max() const
    {
      return max_;
    }


    template <typename T>
    inline typename Rect<T>::PrmValueType
    Rect<T>::x_min() const
    {
      return min_.x();
    }

    template <typename T>
    inline typename Rect<T>::PrmValueType
    Rect<T>::x_max() const
    {
      return max_.x();
    }

    template <typename T>
    inline typename Rect<T>::PrmValueType
    Rect<T>::y_min() const
    {
      return min_.y();
    }

    template <typename T>
    inline typename Rect<T>::PrmValueType
    Rect<T>::y_max() const
    {
      return max_.y();
    }



    // state

    template <typename T>
    inline bool
    Rect<T>::valid() const
    {
      return min_.x() < max_.x() and min_.y() < max_.y();
    }



    // geometry

    template <typename T>
    inline typename Rect<T>::ExactVector
    Rect<T>::delta() const
    {
      return max_ - min_;
    }


    template <typename T>
    inline typename Rect<T>::ValueType
    Rect<T>::width() const
    {
      return x_max() - x_min();
    }

    template <typename T>
    inline typename Rect<T>::ValueType
    Rect<T>::height() const
    {
      return y_max() - y_min();
    }


    template <typename T>
    inline typename Rect<T>::ExactRect
    Rect<T>::bounding_rect() const
    {
      return ExactRect(*this);
    }

    template <typename T>
    inline typename Rect<T>::ExactPoint
    Rect<T>::center() const
    {
      return min_ + ExactVector(width() / 2, height() / 2);
    }

    template <typename T>
    inline Real
    Rect<T>::area() const
    {
      return width() * height();
    }

    template <typename T>
    inline Real
    Rect<T>::perimeter() const
    {
      return 2 * width() + 2 * height();
    }



    // mutators

    template <typename T>
    inline void
    Rect<T>::set_min(const ExactPoint& p)
    {
      min_ = p;
    }

    template <typename T>
    inline void
    Rect<T>::set_max(const ExactPoint& p)
    {
      max_ = p;
    }

    template <typename T>
    inline void
    Rect<T>::set_x_min(PrmValueType x)
    {
      min_.rx() = x;
    }

    template <typename T>
    inline void
    Rect<T>::set_x_max(PrmValueType x)
    {
      max_.rx() = x;
    }

    template <typename T>
    inline void
    Rect<T>::set_y_min(PrmValueType y)
    {
      min_.ry() = y;
    }

    template <typename T>
    inline void
    Rect<T>::set_y_max(PrmValueType y)
    {
      max_.ry() = y;
    }



    // in-place modifiers

    template <typename T>
    inline void
    Rect<T>::move_of(const ExactVector& v)
    {
      min_ += v;
      max_ += v;
    }

    template <typename T>
    void
    Rect<T>::move_to(const ExactPoint& p)
    {
      const ExactVector& v = p - center();
      min_ += v;
      max_ += v;
    }


    template <typename T>
    inline void
    Rect<T>::resize_of(PrmValueType dx, PrmValueType dy)
    {
      resize_of(ExactVector(dx, dy));
    }

    template <typename T>
    inline void
    Rect<T>::resize_to(PrmValueType dx, PrmValueType dy)
    {
      resize_to(ExactVector(dx, dy));
    }

    template <typename T>
    inline void
    Rect<T>::resize_of(const ExactVector& d)
    {
      max_ += d;
    }

    template <typename T>
    inline void
    Rect<T>::resize_to(const ExactVector& d)
    {
      max_ = min_ + d;
    }


    template <typename T>
    void
    Rect<T>::scale(PrmReal s)
    {
      const ExactPoint& c = center();
      min_ = (c + (min_ - c) * s);
      max_ = (c + (max_ - c) * s);
    }



    // comparison operators

    template <typename T1, typename T2>
    inline bool
    operator==(const Rect<T1>& r1, const Rect<T2>& r2)
    {
      return r1.min() == r2.min() and r1.max() == r2.max();
    }

    template <typename T1, typename T2>
    inline bool
    operator!=(const Rect<T1>& r1, const Rect<T2>& r2)
    {
      return r1.min() != r2.min() or r1.max() != r2.max();
    }


  }

}



#endif /* !MML_RECT_HXX_ */
