//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_POINT_HXX_
# define MML_POINT_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/point.hh"
# include "nauths/mml/shapes/rect.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{

  namespace il
  {


    // constructors

    template <typename T>
    inline Point<T>::Point() throw()
    {
      rx() = T();
      ry() = T();
    }

    template <typename T>
    inline Point<T>::Point(PrmValueType x, PrmValueType y) throw()
    {
      rx() = x;
      ry() = y;
    }

    template <typename T>
    inline Point<T>::Point(const Point& p) throw()
    {
      rx() = p.x();
      ry() = p.y();
    }


    template <typename T>
    template <typename T2>
    inline Point<T>::Point(T2 const& x, T2 const& y)
    {
      rx() = to<ValueType>(x);
      ry() = to<ValueType>(y);
    }

    template <typename T>
    template <typename T2>
    inline Point<T>::Point(const Point<T2>& p2)
    {
      rx() = to<ValueType>(p2.x());
      ry() = to<ValueType>(p2.y());
    }



    // accessors

    template <typename T>
    inline typename Point<T>::DataType const&
    Point<T>::data() const
    {
      return c_;
    }

    template <typename T>
    inline typename Point<T>::PrmValueType
    Point<T>::x() const
    {
      return c_[0];
    }

    template <typename T>
    inline typename Point<T>::PrmValueType
    Point<T>::y() const
    {
      return c_[1];
    }

    template <typename T>
    inline typename Point<T>::RefValueType
    Point<T>::rx()
    {
      return c_[0];
    }

    template <typename T>
    inline typename Point<T>::RefValueType
    Point<T>::ry()
    {
      return c_[1];
    }



    // access operators

    template <typename T>
    inline Point<T>::operator const DataType& () const
    {
      return c_;
    }

    template <typename T>
    inline Point<T>::operator DataType& ()
    {
      return c_;
    }


    template <typename T>
    inline typename Point<T>::PrmValueType
    Point<T>::operator[](std::size_t i) const
    {
      return c_[i];
    }

    template <typename T>
    inline typename Point<T>::RefValueType
    Point<T>::operator[](std::size_t i)
    {
      return c_[i];
    }



    // state

    template <typename T>
    inline bool
    Point<T>::valid() const
    {
      return x() == x() and y() == y();
    }



    // geometry

    template <typename T>
    inline Real
    Point<T>::length() const
    {
      Real rx = to<Real>(x());
      Real ry = to<Real>(y());

      return std::sqrt(rx * rx + ry * ry);
    }

    template <typename T>
    inline typename Point<T>::ValueType
    Point<T>::sqr_length() const
    {
      return x() * x() + y() * y();
    }


    template <typename T>
    inline typename Point<T>::ExactRect
    Point<T>::bounding_rect() const
    {
      return ExactRect(*this, *this);
    }

    template <typename T>
    inline typename Point<T>::ExactPoint
    Point<T>::center() const
    {
      return *this;
    }

    template <typename T>
    inline Real
    Point<T>::perimeter() const
    {
      return 0;
    }

    template <typename T>
    inline Real
    Point<T>::area() const
    {
      return 0;
    }



    // modifiers

    template <typename T>
    inline Point<T>
    Point<T>::normalized() const
    {
      return (*this) / length();
    }

    template <typename T>
    inline Point<T>
    Point<T>::normal() const
    {
      return Point(-y(), x());
    }



    // modification operators

    template <typename T>
    inline Point<T>
    Point<T>::operator-() const
    {
      return Point(-x(), -y());
    }



    // in-place modifiers

    template <typename T>
    inline void
    Point<T>::normalize()
    {
      (*this) /= length();
    }


    template <typename T>
    inline void
    Point<T>::move_of(const ExactVector& v)
    {
      (*this) += v;
    }

    template <typename T>
    inline void
    Point<T>::move_to(const ExactPoint& p)
    {
      (*this) = p;
    }


    template <typename T>
    inline void
    Point<T>::scale(PrmReal s)
    {
      (*this) *= s;
    }



    // in-place modification operators

    template <typename T>
    template <typename T2>
    inline Point<T>& Point<T>::operator+=(const Point<T2>& p)
    {
      rx() = to<ValueType>(x() + p.x());
      ry() = to<ValueType>(y() + p.y());
      return *this;
    }

    template <typename T>
    template <typename T2>
    inline Point<T>& Point<T>::operator-=(const Point<T2>& p)
    {
      rx() = to<ValueType>(x() - p.x());
      ry() = to<ValueType>(y() - p.y());
      return *this;
    }

    template <typename T>
    template <typename S>
    inline Point<T>& Point<T>::operator*=(S const& s)
    {
      rx() = to<ValueType>(x() * s);
      ry() = to<ValueType>(y() * s);
      return *this;
    }

    template <typename T>
    template <typename S>
    inline Point<T>& Point<T>::operator/=(S const& s)
    {
      rx() = to<ValueType>(x() / s);
      ry() = to<ValueType>(y() / s);
      return *this;
    }

    template <typename T>
    template <typename S>
    inline Point<T>& Point<T>::operator%=(S const& s)
    {
      rx() = to<ValueType>(mml_mod(x(), s));
      ry() = to<ValueType>(mml_mod(y(), s));
      return *this;
    }



    // comparison operators

    template <typename T1, typename T2>
    inline bool
    operator==(const Point<T1>& p1, const Point<T2>& p2)
    {
      return eq(p1.x(), p2.x()) and eq(p1.y(), p2.y());
    }

    template <typename T1, typename T2>
    inline bool
    operator!=(const Point<T1>& p1, const Point<T2>& p2)
    {
      return ne(p1.x(), p2.x()) or ne(p1.y(), p2.y());
    }



    // basic operations

    template <typename T1, typename T2>
    inline Point<MML_RESULT(MML_ADD, T1, T2)>
    operator+(const Point<T1>& p1, const Point<T2>& p2)
    {
      Point<MML_RESULT(MML_ADD, T1, T2)> res(p1);
      res += p2;
      return res;
    }

    template <typename T1, typename T2>
    inline Point<MML_RESULT(MML_SUB, T1, T2)>
    operator-(const Point<T1>& p1, const Point<T2>& p2)
    {
      Point<MML_RESULT(MML_SUB, T1, T2)> res(p1);
      res -= p2;
      return res;
    }

    template <typename T, typename S>
    inline MML_ENABLE_IF(MML_ISNT_SHAPE(S), Point<MML_RESULT(MML_MUL, T, S)>)
    operator*(const Point<T>& p, S const& s)
    {
      Point<MML_RESULT(MML_MUL, T, S)> res(p);
      res *= s;
      return res;
    }

    template <typename T, typename S>
    inline MML_ENABLE_IF(MML_ISNT_SHAPE(S), Point<MML_RESULT(MML_MUL, T, S)>)
      operator*(S const& s, const Point<T>& p)
    {
      Point<MML_RESULT(MML_MUL, T, S)> res(p);
      res *= s;
      return res;
    }

    template <typename T, typename S>
    inline MML_ENABLE_IF(MML_ISNT_SHAPE(S), Point<MML_RESULT(MML_DIV, T, S)>)
    operator/(const Point<T>& p, S const& s)
    {
      Point<MML_RESULT(MML_DIV, T, S)> res(p);
      res /= s;
      return res;
    }

    template <typename T, typename S>
    inline MML_ENABLE_IF(MML_ISNT_SHAPE(S), Point<MML_RESULT(MML_MOD, T, S)>)
    operator%(const Point<T>& p, S const& s)
    {
      Point<MML_RESULT(MML_MOD, T, S)> res(p);
      res %= s;
      return res;
    }


    // misc mathematical tools

    template <typename T1, typename T2>
    inline MML_RESULT(MML_MUL, T1, T2)
    operator*(const Point<T1>& p1, const Point<T2>& p2)
    {
      return dot_product(p1, p2);
    }

    template <typename T1, typename T2>
    inline MML_RESULT(MML_MUL, T1, T2)
    dot_product(const Point<T1>& p1, const Point<T2>& p2)
    {
      return p1.x() * p2.x() + p1.y() * p2.y();
    }

  }


}



#endif /* !MML_POINT_HXX_ */
