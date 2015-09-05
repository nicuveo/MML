//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_LINE_HXX_
# define MML_LINE_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/line.hh"
# include "nauths/mml/shapes/rect.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{

  namespace il
  {


    // constructors

    /// Creates an invalid ((0, 0) -> (0, 0)) line.
    template <typename T>
    Line<T>::Line() throw()
    {
    }

    /// Creates a (p -> q) line.
    template <typename T>
    Line<T>::Line(const ExactPoint& p, const ExactPoint& q) throw()
    {
      c_[0] = p;
      c_[1] = q;
    }

    /// Creates a ((px, py) -> (qx, qy)) line.
    template <typename T>
    Line<T>::Line(PrmValueType px, PrmValueType py, PrmValueType qx, PrmValueType qy) throw()
    {
      c_[0] = ExactPoint(px, py);
      c_[1] = ExactPoint(qx, qy);
    }


    /// Creates a duplicate of line l.
    template <typename T>
    template <typename T2>
    Line<T>::Line(const Line<T2>& l)
    {
      c_[0] = l.p0();
      c_[1] = l.p1();
    }




    // accessors

    /// Provides a const reference to the underlying point array.
    template <typename T>
    inline typename Line<T>::DataType const&
    Line<T>::data() const
    {
      return c_;
    }


    /// Returns a const reference to the first point.
    template <typename T>
    inline typename Line<T>::ExactPoint const&
    Line<T>::p0() const
    {
      return c_[0];
    }

    /// Returns a const reference to the second point.
    template <typename T>
    inline typename Line<T>::ExactPoint const&
    Line<T>::p1() const
    {
      return c_[1];
    }

    /// Returns a reference to the first point.
    template <typename T>
    inline typename Line<T>::ExactPoint&
    Line<T>::p0()
    {
      return c_[0];
    }

    /// Returns a reference to the second point.
    template <typename T>
    inline typename Line<T>::ExactPoint&
    Line<T>::p1()
    {
      return c_[1];
    }


    /// Returns the x coordinate of the first point.
    template <typename T>
    inline typename Line<T>::PrmValueType
    Line<T>::x0() const
    {
      return p0().x();
    }

    /// Returns the y coordinate of the first point.
    template <typename T>
    inline typename Line<T>::PrmValueType
    Line<T>::y0() const
    {
      return p0().y();
    }

    /// Returns the x coordinate of the second point.
    template <typename T>
    inline typename Line<T>::PrmValueType
    Line<T>::x1() const
    {
      return p1().x();
    }

    /// Returns the y coordinate of the second point.
    template <typename T>
    inline typename Line<T>::PrmValueType
    Line<T>::y1() const
    {
      return p1().y();
    }

    /// Returns a reference to the x coordinate of the first point.
    template <typename T>
    inline typename Line<T>::RefValueType
    Line<T>::x0()
    {
      return p0().x();
    }

    /// Returns a reference to the y coordinate of the first point.
    template <typename T>
    inline typename Line<T>::RefValueType
    Line<T>::y0()
    {
      return p0().y();
    }

    /// Returns a reference to the x coordinate of the second point.
    template <typename T>
    inline typename Line<T>::RefValueType
    Line<T>::x1()
    {
      return p1().x();
    }

    /// Returns a reference to the y coordinate of the second point.
    template <typename T>
    inline typename Line<T>::RefValueType
    Line<T>::y1()
    {
      return p1().y();
    }



    // access operators

    /// Automagically casts the point into a const coordinate array.
    template <typename T>
    inline Line<T>::operator const DataType& () const
    {
      return c_;
    }

    /// Automagically casts the point into a coordinate array.
    template <typename T>
    inline Line<T>::operator DataType& ()
    {
      return c_;
    }


    /// Returns the point of index i (no checks performed).
    template <typename T>
    inline typename Line<T>::ExactPoint const&
    Line<T>::operator[](std::size_t i) const
    {
      return c_[i];
    }

    /// Returns the point of index i (no checks performed).
    template <typename T>
    inline typename Line<T>::ExactPoint&
    Line<T>::operator[](std::size_t i)
    {
      return c_[i];
    }



    // state

    /// Returns whether the line is valid (i.e. the two points are different).
    template <typename T>
    inline bool
    Line<T>::valid() const
    {
      return p0().valid() and p1().valid() and p0() != p1();
    }



    // geometry

    /// Computes the x offset between the two points.
    template <typename T>
    inline typename Line<T>::ValueType
    Line<T>::dx() const
    {
      return x1() - x0();
    }

    /// Computes the y offset between the two points.
    template <typename T>
    inline typename Line<T>::ValueType
    Line<T>::dy() const
    {
      return y1() - y0();
    }

    /// Computes the corresponding vector.
    template <typename T>
    inline typename Line<T>::ExactVector
    Line<T>::delta() const
    {
      return ExactVector(dx(), dy());
    }


    /// Computes the length of the line.
    template <typename T>
    inline Real
    Line<T>::length() const
    {
      Real rx = to<Real>(dx());
      Real ry = to<Real>(dy());

      return std::sqrt(rx * rx + ry * ry);
    }

    /// Computes the squared length of the line.
    template <typename T>
    inline typename Line<T>::ValueType
    Line<T>::sqr_length() const
    {
      return dx() * dx() + dy() * dy();
    }


    /// Creates a (possibly invalid) Rect that wraps this line.
    template <typename T>
    inline typename Line<T>::ExactRect
    Line<T>::bounding_rect() const
    {
      return ExactRect(std::min(x0(), x1()), std::min(y0(), y1()),
                       std::max(x0(), x1()), std::max(y0(), y1()));
    }

    /// Computes the barycenter of the two points.
    template <typename T>
    inline typename Line<T>::ExactPoint
    Line<T>::center() const
    {
      return ExactPoint((x0() + x1()) / 2, (y0() + y1()) / 2);
    }

    /// Returns 0.
    template <typename T>
    inline Real
    Line<T>::perimeter() const
    {
      return 0;
    }

    /// Returns 0.
    template <typename T>
    inline Real
    Line<T>::area() const
    {
      return 0;
    }



    // modification operators

    /// Inverts the line: (p -> q) becomes (q -> p).
    template <typename T>
    inline Line<T>
    Line<T>::operator-() const
    {
      return Line<T>(p1(), p0());
    }



    // in-place modifiers

    template <typename T>
    inline void
    Line<T>::move_of(const ExactVector& v)
    {
      p0() += v;
      p1() += v;
    }

    template <typename T>
    inline void
    Line<T>::move_to(const ExactPoint& p)
    {
      p1() += p - p0();
      p0() = p;
    }


    template <typename T>
    inline void
    Line<T>::scale(PrmReal s)
    {
      (*this) *= s;
    }



    // in-place modification operators

    template <typename T>
    template <typename S>
    inline Line<T>& Line<T>::operator*=(S const& s)
    {
      p1() = p0() + ExactVector(delta() * s);
      return *this;
    }

    template <typename T>
    template <typename S>
    inline Line<T>& Line<T>::operator/=(S const& s)
    {
      p1() = p0() + ExactVector(delta() / s);
     return *this;
    }

    template <typename T>
    template <typename S>
    inline Line<T>& Line<T>::operator%=(S const& s)
    {
      p1() = p0() + ExactVector(delta() % s);
      return *this;
    }



    // comparison operators

    template <typename T1, typename T2>
    inline bool
    operator==(const Line<T1>& l1, const Line<T2>& l2)
    {
      return l1.p0() == l2.p0() and l1.p1() == l2.p1();
    }

    template <typename T1, typename T2>
    inline bool
    operator!=(const Line<T1>& l1, const Line<T2>& l2)
    {
      return l1.p0() != l2.p0() or l1.p1() != l2.p1();
    }



    // basic operations

    template <typename T, typename S>
    inline MML_ENABLE_IF(MML_ISNT_SHAPE(S), Line<MML_RESULT(MML_MUL, T, S)>)
    operator*(const Line<T>& p, S const& s)
    {
      Line<MML_RESULT(MML_MUL, T, S)> res(p);
      res *= s;
      return res;
    }

    template <typename T, typename S>
    inline MML_ENABLE_IF(MML_ISNT_SHAPE(S), Line<MML_RESULT(MML_MUL, T, S)>)
      operator*(S const& s, const Line<T>& p)
    {
      Line<MML_RESULT(MML_MUL, T, S)> res(p);
      res *= s;
      return res;
    }

    template <typename T, typename S>
    inline MML_ENABLE_IF(MML_ISNT_SHAPE(S), Line<MML_RESULT(MML_DIV, T, S)>)
    operator/(const Line<T>& p, S const& s)
    {
      Line<MML_RESULT(MML_DIV, T, S)> res(p);
      res /= s;
      return res;
    }

    template <typename T, typename S>
    inline MML_ENABLE_IF(MML_ISNT_SHAPE(S), Line<MML_RESULT(MML_MOD, T, S)>)
    operator%(const Line<T>& p, S const& s)
    {
      Line<MML_RESULT(MML_MOD, T, S)> res(p);
      res %= s;
      return res;
    }

  }


}



#endif /* !MML_LINE_HXX_ */
