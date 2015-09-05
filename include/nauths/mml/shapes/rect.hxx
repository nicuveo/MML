//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_RECT_HXX_
# define MML_RECT_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/rect.hh"



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
    template <typename T2>
    Rect<T>::Rect(const Rect<T2>& r)
      : min_(r.min()), max_(r.max())
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



    // modifiers

    template <typename T>
    inline Rect<T>
    Rect<T>::expanded(PrmValueType d) const
    {
      Rect<T> res = *this;
      res.expand(d);
      return res;
    }

    template <typename T>
    inline Rect<T>
    Rect<T>::expanded(PrmValueType dx, PrmValueType dy) const
    {
      Rect<T> res = *this;
      res.expand(dx, dy);
      return res;
    }

    template <typename T>
    inline Rect<T>
    Rect<T>::expanded(PrmValueType dl, PrmValueType dt, PrmValueType dr, PrmValueType db) const
    {
      Rect<T> res = *this;
      res.expand(dl, dt, dr, db);
      return res;
    }

    template <typename T>
    inline Rect<T>
    Rect<T>::expanded(const ExactPoint& d) const
    {
      Rect<T> res = *this;
      res.expand(d);
      return res;
    }
    template <typename T>
    inline Rect<T>
    Rect<T>::expanded(const ExactRect& r) const
    {
      Rect<T> res = *this;
      res.expand(r.x_min(), r.y_min(), r.x_max(), r.y_max());
      return res;
    }

    template <typename T>
    inline Rect<T>
    Rect<T>::shrinked(PrmValueType d) const
    {
      Rect<T> res = *this;
      res.shrink(d);
      return res;
    }

    template <typename T>
    inline Rect<T>
    Rect<T>::shrinked(PrmValueType dx, PrmValueType dy) const
    {
      Rect<T> res = *this;
      res.shrink(dx, dy);
      return res;
    }

    template <typename T>
    inline Rect<T>
    Rect<T>::shrinked(PrmValueType dl, PrmValueType dt, PrmValueType dr, PrmValueType db) const
    {
      Rect<T> res = *this;
      res.shrink(dl, dt, dr, db);
      return res;
    }

    template <typename T>
    inline Rect<T>
    Rect<T>::shrinked(const ExactPoint& d) const
    {
      Rect<T> res = *this;
      res.shrink(d);
      return res;
    }
    template <typename T>
    inline Rect<T>
    Rect<T>::shrinked(const ExactRect& r) const
    {
      Rect<T> res = *this;
      res.shrink(r.x_min(), r.y_min(), r.x_max(), r.y_max());
      return res;
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


    template <typename T>
    inline void
    Rect<T>::expand(PrmValueType d)
    {
      expand(d, d);
    }

    template <typename T>
    inline void
    Rect<T>::expand(PrmValueType dx, PrmValueType dy)
    {
      expand(ExactPoint(dx, dy));
    }

    template <typename T>
    inline void
    Rect<T>::expand(PrmValueType dl, PrmValueType dt, PrmValueType dr, PrmValueType db)
    {
      expand(ExactRect(dl, dt, dr, db));
    }

    template <typename T>
    inline void
    Rect<T>::expand(const ExactPoint& d)
    {
      min_ -= d;
      max_ += d;
    }

    template <typename T>
    inline void
    Rect<T>::expand(const ExactRect& r)
    {
      min_ -= r.min();
      max_ += r.max();
    }

    template <typename T>
    inline void
    Rect<T>::shrink(PrmValueType d)
    {
      expand(-d, -d);
    }

    template <typename T>
    inline void
    Rect<T>::shrink(PrmValueType dx, PrmValueType dy)
    {
      expand(-dx, -dy);
    }

    template <typename T>
    inline void
    Rect<T>::shrink(PrmValueType dl, PrmValueType dt, PrmValueType dr, PrmValueType db)
    {
      expand(-dl, -dt, -dr, -db);
    }

    template <typename T>
    inline void
    Rect<T>::shrink(const ExactPoint& d)
    {
      expand(-d);
    }

    template <typename T>
    inline void
    Rect<T>::shrink(const ExactRect& d)
    {
      expand(-d.min(), -d.max());
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
