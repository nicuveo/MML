//
// line.hxx for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_LINE_HXX_
# define MML_LINE_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "mml/shapes/line.hh"
# include "mml/shapes/rect.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{

  namespace il
  {


    // constructors

    template <typename T>
    Line<T>::Line() throw()
    {
    }

    template <typename T>
    Line<T>::Line(const ExactPoint& p, const ExactPoint& q) throw()
    {
      c_[0] = p;
      c_[1] = q;
    }

    template <typename T>
    Line<T>::Line(PrmValueType px, PrmValueType py, PrmValueType qx, PrmValueType qy) throw()
    {
      c_[0] = ExactPoint(px, py);
      c_[1] = ExactPoint(qx, qy);
    }



    // accessors

    template <typename T>
    inline typename Line<T>::DataType const&
    Line<T>::data() const
    {
      return c_;
    }


    template <typename T>
    inline typename Line<T>::ExactPoint const&
    Line<T>::p0() const
    {
      return c_[0];
    }

    template <typename T>
    inline typename Line<T>::ExactPoint const&
    Line<T>::p1() const
    {
      return c_[1];
    }

    template <typename T>
    inline typename Line<T>::ExactPoint&
    Line<T>::p0()
    {
      return c_[0];
    }

    template <typename T>
    inline typename Line<T>::ExactPoint&
    Line<T>::p1()
    {
      return c_[1];
    }


    template <typename T>
    inline typename Line<T>::PrmValueType
    Line<T>::x0() const
    {
      return p0().x();
    }

    template <typename T>
    inline typename Line<T>::PrmValueType
    Line<T>::y0() const
    {
      return p0().y();
    }

    template <typename T>
    inline typename Line<T>::PrmValueType
    Line<T>::x1() const
    {
      return p1().x();
    }

    template <typename T>
    inline typename Line<T>::PrmValueType
    Line<T>::y1() const
    {
      return p1().y();
    }

    template <typename T>
    inline typename Line<T>::RefValueType
    Line<T>::x0()
    {
      return p0().x();
    }

    template <typename T>
    inline typename Line<T>::RefValueType
    Line<T>::y0()
    {
      return p0().y();
    }

    template <typename T>
    inline typename Line<T>::RefValueType
    Line<T>::x1()
    {
      return p1().x();
    }

    template <typename T>
    inline typename Line<T>::RefValueType
    Line<T>::y1()
    {
      return p1().y();
    }



    // access operators

    template <typename T>
    inline Line<T>::operator const DataType& () const
    {
      return c_;
    }

    template <typename T>
    inline Line<T>::operator DataType& ()
    {
      return c_;
    }


    template <typename T>
    inline typename Line<T>::ExactPoint const&
    Line<T>::operator[](std::size_t i) const
    {
      return c_[i];
    }

    template <typename T>
    inline typename Line<T>::ExactPoint&
    Line<T>::operator[](std::size_t i)
    {
      return c_[i];
    }



    // state

    template <typename T>
    inline bool
    Line<T>::valid() const
    {
      return p0().valid() and p1().valid() and p0() != p1();
    }



    // geometry

    template <typename T>
    inline typename Line<T>::ValueType
    Line<T>::dx() const
    {
      return x1() - x0();
    }

    template <typename T>
    inline typename Line<T>::ValueType
    Line<T>::dy() const
    {
      return y1() - y0();
    }

    template <typename T>
    inline typename Line<T>::ExactVector
    Line<T>::delta() const
    {
      return ExactVector(dx(), dy());
    }


    template <typename T>
    inline Real
    Line<T>::length() const
    {
      Real rx = to<Real>(dx());
      Real ry = to<Real>(dy());

      return std::sqrt(rx * rx + ry * ry);
    }

    template <typename T>
    inline typename Line<T>::ValueType
    Line<T>::sqr_length() const
    {
      return dx() * dx() + dy() * dy();
    }


    template <typename T>
    inline typename Line<T>::ExactRect
    Line<T>::bounding_rect() const
    {
      return ExactRect(std::min(x0(), x1()), std::min(y0(), y1()),
                       std::max(x0(), x1()), std::max(y0(), y1()));
    }

    template <typename T>
    inline typename Line<T>::ExactPoint
    Line<T>::center() const
    {
      return ExactPoint((x0() + x1()) / 2, (y0() + y1()) / 2);
    }

    template <typename T>
    inline Real
    Line<T>::perimeter() const
    {
      return 0;
    }

    template <typename T>
    inline Real
    Line<T>::area() const
    {
      return 0;
    }



    // modification operators

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
