//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_CIRCLE_HXX_
# define MML_CIRCLE_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/circle.hh"
# include "nauths/mml/shapes/polygon.hh"
# include "nauths/mml/constants.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{

  namespace il
  {


    // constructors

    template <typename T>
    inline Circle<T>::Circle() throw()
      : radius_(0)
    {
    }

    template <typename T>
    inline Circle<T>::Circle(PrmValueType radius) throw()
      : radius_(radius)
    {
    }

    template <typename T>
    inline Circle<T>::Circle(PrmValueType cx, PrmValueType cy, PrmValueType radius)  throw()
      : center_(cx, cy), radius_(radius)
    {
    }

    template <typename T>
    inline Circle<T>::Circle(const ExactPoint& center, PrmValueType radius) throw()
      : center_(center), radius_(radius)
    {
    }


    template <typename T>
    template <typename T2>
    Circle<T>::Circle(const Circle<T2>& c)
      : center_(c.center()), radius_(to<T>(c.radius()))
    {
    }



    // accessors

    template <typename T>
    inline typename Circle<T>::ExactPoint
    Circle<T>::center() const
    {
      return center_;
    }

    template <typename T>
    inline typename Circle<T>::PrmValueType
    Circle<T>::radius() const
    {
      return radius_;
    }



    // state

    template <typename T>
    inline bool
    Circle<T>::valid() const
    {
      return radius_ > 0;
    }



    // geometry

    template <typename T>
    typename Circle<T>::ExactPolygon
    Circle<T>::polygonize(PrmNum pn, PrmReal a) const
    {
      typename ExactPolygon::ExactPoints res;

      // TODO debug::circle: check pn >= 3

      res.reserve(pn);
      for (int i = 0; i < pn; ++i)
        res.push_back(this->center_ + ExactPoint(
                        this->radius_ * cos(a + i * tau() / pn),
                        this->radius_ * sin(a + i * tau() / pn)));

      return ExactPolygon(res);
    }


    template <typename T>
    inline typename Circle<T>::ExactRect
    Circle<T>::bounding_rect() const
    {
      return ExactRect(center_ - ExactVector(radius_, radius_),
                       center_ + ExactVector(radius_, radius_));
    }

    template <typename T>
    inline Real
    Circle<T>::perimeter() const
    {
      return tau() * this->radius_;
    }

    template <typename T>
    inline Real
    Circle<T>::area() const
    {
      return pi() * std::pow(this->radius_, 2);
    }



    // mutators

    template <typename T>
    inline void
    Circle<T>::set_center(const ExactPoint& c)
    {
      center_ = c;
    }

    template <typename T>
    inline void
    Circle<T>::set_radius(PrmValueType r)
    {
      radius_ = r;
      // TODO debug::circle: check radius?
    }



    // in-place modifiers

    template <typename T>
    inline void
    Circle<T>::move_of(const ExactVector& v)
    {
      set_center(center_ + v);
    }

    template <typename T>
    inline void
    Circle<T>::move_to(const ExactPoint& p)
    {
      set_center(p);
    }


    template <typename T>
    inline void
    Circle<T>::scale(PrmReal s)
    {
      set_radius(to<ValueType>(radius_ * s));
    }



    // comparison operators

    template <typename T1, typename T2>
    inline bool
    operator==(const Circle<T1>& c1, const Circle<T2>& c2)
    {
      return c1.center() == c2.center() and eq(c1.radius(), c2.radius());
    }

    template <typename T1, typename T2>
    inline bool
    operator!=(const Circle<T1>& c1, const Circle<T2>& c2)
    {
      return c1.center() != c2.center() or ne(c1.radius(), c2.radius());
    }


  }

}



#endif /* !MML_CIRCLE_HXX_ */
