//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_SHAPE_HXX_
# define MML_SHAPE_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/shape_utils.hh"
# include "nauths/mml/shapes/shape.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros

# define MMLM_equal(_1, _2, S)                             \
  case shape::MMLM_NAME(S):                                \
    return s1.MMLM_name(S)() == s2.MMLM_name(S)();         \

# define MMLM_assign(_1, _2, S)                            \
  case shape::MMLM_NAME(S):                                \
    data_ = MMLM_Name(S)<T>(shape.MMLM_name(S)());         \
    break;                                                 \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{

  namespace il
  {


    // constructors

    template <typename T>
    template <typename S>
    inline Shape<T>::Shape(S const& shape) throw()
      : data_(shape)
    {
    }

    template <typename T>
    inline Shape<T>::Shape(const Shape& shape) throw()
      : data_(shape.data_)
    {
    }

    template <typename T>
    inline Shape<T>::Shape() throw()
      : data_(Empty<T>())
    {
    }


    template <typename T>
    template <typename S>
    inline Shape<T>::Shape(const Shape<S>& shape)
      : data_(Empty<T>())
    {
      switch (shape.type())
      {
        case shape::EMPTY: break;
        BOOST_PP_SEQ_FOR_EACH(MMLM_assign, _, MMLM_SHAPES)
      }
    }



    // creators

    template <typename T>
    inline typename Shape<T>::ExactRect
    Shape<T>::rect(const ExactPoint& p1, const ExactPoint& p2)
    {
      return ExactRect(p1, p2);
    }

    template <typename T>
    inline typename Shape<T>::ExactRect
    Shape<T>::rect(PrmValueType xmin, PrmValueType ymin, PrmValueType xmax, PrmValueType ymax)
    {
      return rect(ExactPoint(xmin, ymin), ExactPoint(xmax, ymax));
    }


    template <typename T>
    inline typename Shape<T>::ExactCircle
    Shape<T>::circle(PrmValueType radius)
    {
      return circle(ExactPoint(0, 0), radius);
    }

    template <typename T>
    inline typename Shape<T>::ExactCircle
    Shape<T>::circle(PrmValueType x, PrmValueType y, PrmValueType radius)
    {
      return circle(ExactPoint(x, y), radius);
    }

    template <typename T>
    inline typename Shape<T>::ExactCircle
    Shape<T>::circle(const ExactPoint& p, PrmValueType radius)
    {
      return ExactCircle(p, radius);
    }


    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::polygon(const typename ExactPolygon::ExactPoints& ps)
    {
      return ExactPolygon(ps);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::triangle(const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2)
    {
      return polygon(boost::assign::list_of(p0)(p1)(p2));
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::tetragon(const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                       const ExactPoint& p3)
    {
      return polygon(boost::assign::list_of(p0)(p1)(p2)(p3));
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::pentagon(const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                       const ExactPoint& p3, const ExactPoint& p4)
    {
      return polygon(boost::assign::list_of(p0)(p1)(p2)(p3)(p4));
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::hexagon(const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                      const ExactPoint& p3, const ExactPoint& p4, const ExactPoint& p5)
    {
      return polygon(boost::assign::list_of(p0)(p1)(p2)(p3)(p4)(p5));
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::heptagon(const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                       const ExactPoint& p3, const ExactPoint& p4, const ExactPoint& p5,
                       const ExactPoint& p6)
    {
      return polygon(boost::assign::list_of(p0)(p1)(p2)(p3)(p4)(p5)(p6));
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::octagon(const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                      const ExactPoint& p3, const ExactPoint& p4, const ExactPoint& p5,
                      const ExactPoint& p6, const ExactPoint& p7)
    {
      return polygon(boost::assign::list_of(p0)(p1)(p2)(p3)(p4)(p5)(p6)(p7));
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::nonagon(const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                      const ExactPoint& p3, const ExactPoint& p4, const ExactPoint& p5,
                      const ExactPoint& p6, const ExactPoint& p7, const ExactPoint& p8)
    {
      return polygon(boost::assign::list_of(p0)(p1)(p2)(p3)(p4)(p5)(p6)(p7)(p8));
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::decagon(const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                      const ExactPoint& p3, const ExactPoint& p4, const ExactPoint& p5,
                      const ExactPoint& p6, const ExactPoint& p7, const ExactPoint& p8,
                      const ExactPoint& p9)
    {
      return polygon(boost::assign::list_of(p0)(p1)(p2)(p3)(p4)(p5)(p6)(p7)(p8)(p9));
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::hendecagon(const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                         const ExactPoint& p3, const ExactPoint& p4, const ExactPoint& p5,
                         const ExactPoint& p6, const ExactPoint& p7, const ExactPoint& p8,
                         const ExactPoint& p9, const ExactPoint& pa)
    {
      return polygon(boost::assign::list_of(p0)(p1)(p2)(p3)(p4)(p5)(p6)(p7)(p8)(p9)(pa));
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::dodecagon(const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                        const ExactPoint& p3, const ExactPoint& p4, const ExactPoint& p5,
                        const ExactPoint& p6, const ExactPoint& p7, const ExactPoint& p8,
                        const ExactPoint& p9, const ExactPoint& pa, const ExactPoint& pb)
    {
      return polygon(boost::assign::list_of(p0)(p1)(p2)(p3)(p4)(p5)(p6)(p7)(p8)(p9)(pa)(pb));
    }


    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::square(PrmValueType h_side, PrmReal angle)
    {
      // TODO debug::shape: check square size > 0
      return reg_polygon(h_side, 4, angle + 3 * pi() / 4);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::square(PrmValueType x, PrmValueType y,
                     PrmValueType h_side, PrmReal angle)
    {
      // TODO debug::shape: check square size > 0
      return reg_polygon(x, y, h_side, 4, angle + 3 * pi() / 4);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::square(const ExactPoint& p,
                     PrmValueType h_side, PrmReal angle)
    {
      // TODO debug::shape: check square size > 0
      return reg_polygon(p, h_side, 4, angle + pi() / 4);
    }


    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_polygon(PrmValueType radius, PrmNum points, PrmReal angle)
    {
      return reg_polygon(ExactPoint(0, 0), radius, points, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_polygon(PrmValueType x, PrmValueType y,
                          PrmValueType radius, PrmNum points, PrmReal angle)
    {
      return reg_polygon(ExactPoint(x, y), radius, points, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_polygon(const ExactPoint& p,
                          PrmValueType radius, PrmNum points, PrmReal angle)
    {
      return ExactCircle(p, radius).polygonize(points, angle);
    }


    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::equilateral_triangle(PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(radius, 3, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::equilateral_triangle(PrmValueType x, PrmValueType y,
                                   PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(x, y, radius, 3, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::equilateral_triangle(const ExactPoint& p,
                                   PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(p, radius, 3, angle);
    }


    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_pentagon(PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(radius, 5, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_pentagon(PrmValueType x, PrmValueType y,
                           PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(x, y, radius, 5, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_pentagon(const ExactPoint& p,
                           PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(p, radius, 5, angle);
    }


    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_hexagon(PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(radius, 6, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_hexagon(PrmValueType x, PrmValueType y,
                          PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(x, y, radius, 6, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_hexagon(const ExactPoint& p,
                          PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(p, radius, 6, angle);
    }


    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_heptagon(PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(radius, 7, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_heptagon(PrmValueType x, PrmValueType y,
                           PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(x, y, radius, 7, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_heptagon(const ExactPoint& p,
                           PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(p, radius, 7, angle);
    }


    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_octagon(PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(radius, 8, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_octagon(PrmValueType x, PrmValueType y,
                          PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(x, y, radius, 8, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_octagon(const ExactPoint& p,
                          PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(p, radius, 8, angle);
    }


    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_nonagon(PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(radius, 9, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_nonagon(PrmValueType x, PrmValueType y,
                          PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(x, y, radius, 9, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_nonagon(const ExactPoint& p,
                          PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(p, radius, 9, angle);
    }


    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_decagon(PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(radius, 10, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_decagon(PrmValueType x, PrmValueType y,
                          PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(x, y, radius, 10, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_decagon(const ExactPoint& p,
                          PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(p, radius, 10, angle);
    }


    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_hendecagon(PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(radius, 11, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_hendecagon(PrmValueType x, PrmValueType y,
                             PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(x, y, radius, 11, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_hendecagon(const ExactPoint& p,
                             PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(p, radius, 11, angle);
    }


    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_dodecagon(PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(radius, 12, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_dodecagon(PrmValueType x, PrmValueType y,
                            PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(x, y, radius, 12, angle);
    }

    template <typename T>
    inline typename Shape<T>::ExactPolygon
    Shape<T>::reg_dodecagon(const ExactPoint& p,
                            PrmValueType radius, PrmReal angle)
    {
      return reg_polygon(p, radius, 12, angle);
    }



    // conversions

    template <typename T>
    inline Shape<T>::operator bool() const
    {
      return not this->empty();
    }



    // accessors

    template <typename T>
    inline ShapeType
    Shape<T>::type() const
    {
      return apply(TypeFunc());
    }



    // state

    template <typename T>
    inline bool
    Shape<T>::valid() const
    {
      return apply(ValidFunc());
    }



    // geometry

    template <typename T>
    inline typename Shape<T>::ExactRect
    Shape<T>::bounding_rect() const
    {
      return apply(BoundingRectFunc<ExactRect>());
    }

    template <typename T>
    inline typename Shape<T>::ExactPoint
    Shape<T>::center() const
    {
      return apply(CenterFunc<ExactPoint>());
    }

    template <typename T>
    inline Real
    Shape<T>::perimeter() const
    {
      return apply(PerimeterFunc());
    }

    template <typename T>
    inline Real
    Shape<T>::area() const
    {
      return apply(AreaFunc());
    }



    // modifiers

    template <typename T>
    template <typename F>
    inline typename F::result_type
    Shape<T>::apply(F& visitor) const
    {
      return boost::apply_visitor(visitor, data_);
    }

    template <typename T>
    template <typename F>
    inline typename F::result_type
    Shape<T>::apply(F const& visitor) const
    {
      return boost::apply_visitor(visitor, data_);
    }



    // in-place modifiers

    template <typename T>
    template <typename F>
    inline typename F::result_type
    Shape<T>::apply(F& visitor)
    {
      return boost::apply_visitor(visitor, data_);
    }

    template <typename T>
    template <typename F>
    inline typename F::result_type
    Shape<T>::apply(F const& visitor)
    {
      return boost::apply_visitor(visitor, data_);
    }


    template <typename T>
    inline void
    Shape<T>::move_of(const ExactVector& v)
    {
      apply(MoveOfFunc<const ExactVector&>(v));
    }

    template <typename T>
    inline void
    Shape<T>::move_to(const ExactPoint& p)
    {
      apply(MoveToFunc<const ExactPoint&>(p));
    }

    template <typename T>
    inline void
    Shape<T>::scale(PrmReal s)
    {
      apply(ScaleFunc(s));
    }



    // comparison operators

    template <typename T1, typename T2>
    inline bool
    operator==(const Shape<T1>& s1, const Shape<T2>& s2)
    {
      if (s1.type() != s2.type())
        return false;
      switch (s1.type())
      {
        case shape::EMPTY: return true;
        BOOST_PP_SEQ_FOR_EACH(MMLM_equal, _, MMLM_SHAPES)
      }

      // TODO debug::shape: ensure code never reached
      return false;
    }

    template <typename T1, typename T2>
    inline bool
    operator!=(const Shape<T1>& s1, const Shape<T2>& s2)
    {
      return not (s1 == s2);
    }


  }



  // type extraction

  template <typename T>
  inline ShapeType type(const Shape<T>& s)
  {
    return s.type();
  }

  template <typename T1, typename T2>
  inline ShapeType dual_type(const Shape<T1>& s1, const Shape<T2>& s2)
  {
    return s1.type() * s2.type();
  }


}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros undef

# undef MMLM_equal
# undef MMLM_assign



#endif /* !MML_SHAPE_HXX_ */
