//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_CONTAINS_HXX_
# define MML_CONTAINS_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/algos/contains.hh"
# include "nauths/mml/algos/common.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros

# define MMLM_cimpl(_1, _2, S)                                          \
  template <typename T1, typename T2>                                   \
  inline bool contains(const Shape<T1>& s1, const MMLM_Name(S)<T2>& s2) \
  {                                                                     \
    return local::cswitch1(s1, s2);                                     \
  }                                                                     \
                                                                        \
  template <typename T1, typename T2>                                   \
  inline bool contains(const MMLM_Name(S)<T1>& s1, const Shape<T2>& s2) \
  {                                                                     \
    return local::cswitch2(s1, s2);                                     \
  }                                                                     \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local helpers

namespace mml
{

  namespace local
  {


    // type switch

    template <typename T>
    MML_SHAPE_UNION_VISITOR_WARG_E(CSwitch1, bool, T,
                                   return contains(x, arg_),
                                   return false);
    template <typename T>
    MML_SHAPE_UNION_VISITOR_WARG_E(CSwitch2, bool, T,
                                   return contains(arg_, x),
                                   return true);

    template <typename T1, typename T2>
    inline bool cswitch1(T1 const& s1, T2 const& s2)
    {
      return s1.apply(CSwitch1<T2 const&>(s2));
    }

    template <typename T1, typename T2>
    inline bool cswitch2(T1 const& s1, T2 const& s2)
    {
      return s2.apply(CSwitch2<T1 const&>(s1));
    }


  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{


  // specific cases

  template <typename T1, typename T2>
  inline bool contains(const Point<T1>& p1, const Point<T2>& p2)
  {
    return p1 == p2;
  }

  template <typename T1, typename T2>
  inline bool contains(const Point<T1>&, const Line<T2>&)
  {
    return false;
  }

  template <typename T1, typename T2>
  inline bool contains(const Point<T1>&, const Rect<T2>&)
  {
    return false;
  }

  template <typename T1, typename T2>
  inline bool contains(const Point<T1>&, const Circle<T2>&)
  {
    return false;
  }

  template <typename T1, typename T2>
  inline bool contains(const Point<T1>&, const Polygon<T2>&)
  {
    return false;
  }


  template <typename T1, typename T2>
  inline bool contains(const Line<T1>& l, const Point<T2>& p)
  {
    return eq((p - l[0]).length() + (p - l[1]).length(), l.length());
  }

  template <typename T1, typename T2>
  inline bool contains(const Line<T1>& l1, const Line<T2>& l2)
  {
    return il::lines_contains(l1, l2);
  }

  template <typename T1, typename T2>
  inline bool contains(const Line<T1>&, const Rect<T2>&)
  {
    return false;
  }

  template <typename T1, typename T2>
  inline bool contains(const Line<T1>&, const Circle<T2>&)
  {
    return false;
  }

  template <typename T1, typename T2>
  inline bool contains(const Line<T1>&, const Polygon<T2>&)
  {
    return false;
  }


  template <typename T1, typename T2>
  inline bool contains(const Rect<T1>& s1, const Point<T2>& s2)
  {
    return (ge(s2.x(), s1.x_min()) and le(s2.x(), s1.x_max()) and
            ge(s2.y(), s1.y_min()) and le(s2.y(), s1.y_max()));
  }

  template <typename T1, typename T2>
  inline bool contains(const Rect<T1>& s1, const Line<T2>& s2)
  {
    return contains(s1, s2[0]) and contains(s1, s2[1]);
  }

  template <typename T1, typename T2>
  inline bool contains(const Rect<T1>& s1, const Rect<T2>& s2)
  {
    return (ge(s2.x_min(), s1.x_min()) and le(s2.x_max(), s1.x_max()) and
            ge(s2.y_min(), s1.y_min()) and le(s2.y_max(), s1.y_max()));
  }

  template <typename T1, typename T2>
  inline bool contains(const Rect<T1>& s1, const Circle<T2>& s2)
  {
    return contains(s1, s2.bounding_rect());
  }

  template <typename T1, typename T2>
  inline bool contains(const Rect<T1>& s1, const Polygon<T2>& s2)
  {
    return contains(s1, s2.bounding_rect());
  }


  template <typename T1, typename T2>
  inline bool contains(const Circle<T1>& s1, const Point<T2>& s2)
  {
    return le((s2 - s1.center()).length(), to<Real>(s1.radius()));
  }

  template <typename T1, typename T2>
  inline bool contains(const Circle<T1>& s1, const Line<T2>& s2)
  {
    return contains(s1, s2[0]) and contains(s1, s2[1]);
  }

  template <typename T1, typename T2>
  inline bool contains(const Circle<T1>& s1, const Rect<T2>& s2)
  {
    return (contains(s1, Point<T2>(s2.x_min(), s2.y_min())) and
            contains(s1, Point<T2>(s2.x_min(), s2.y_max())) and
            contains(s1, Point<T2>(s2.x_max(), s2.y_min())) and
            contains(s1, Point<T2>(s2.x_max(), s2.y_max())));
  }

  template <typename T1, typename T2>
  inline bool contains(const Circle<T1>& s1, const Circle<T2>& s2)
  {
    return le((s1.center() - s2.center()).length(),
              std::min(to<Real>(s1.radius()), to<Real>(s2.radius())));
  }

  template <typename T1, typename T2>
  inline bool contains(const Circle<T1>& c, const Polygon<T2>& p)
  {
    mml_foreach (const Point<T2>& pp, p.points())
    {
      if (not contains(c, pp))
        return false;
    }
    return true;
  }


  template <typename T1, typename T2>
  inline bool contains(const Polygon<T1>& poly, const Point<T2>& p)
  {
    if (not contains(poly.bounding_rect(), p))
      return false;

    bool is_in = false;

    mml_foreach (const Line<T1>& l, poly.lines())
    {
      if (contains(l, p))
        return true;
      if (il::above_line(p, l))
        is_in = not is_in;
    }

    return is_in;
  }

  template <typename T1, typename T2>
  inline bool contains(const Polygon<T1>& p, const Line<T2>& l)
  {
    return il::polygon_contains_line(p, l[0], l[1]);
  }

  template <typename T1, typename T2>
  inline bool contains(const Polygon<T1>& p, const Rect<T2>& r)
  {
    return contains(p.bounding_rect(), r) and
      contains(p, Line<T2>(r.x_min(), r.y_min(), r.x_min(), r.y_max())) and
      contains(p, Line<T2>(r.x_min(), r.y_min(), r.x_max(), r.y_min())) and
      contains(p, Line<T2>(r.x_max(), r.y_min(), r.x_max(), r.y_max())) and
      contains(p, Line<T2>(r.x_min(), r.y_max(), r.x_max(), r.y_max()));
  }

  template <typename T1, typename T2>
  inline bool contains(const Polygon<T1>& p, const Circle<T2>& c)
  {
    if (not contains(p.bounding_rect(), c) or
        not contains(p, c.center()))
      return false;

    mml_foreach (const Line<T2>& l, p.lines())
      if (contains(c, il::closest_on_line(c.center(), l)))
        return false;

    return true;
  }

  template <typename T1, typename T2>
  bool contains(const Polygon<T1>& p1, const Polygon<T2>& p2)
  {
    if (not contains(p1.bounding_rect(), p2))
      return false;
    if (contains(p1, p2.bounding_rect()))
      return true;

    mml_foreach (const Line<T2>& l, p2.lines())
      if (not contains(p1, l))
        return false;

    return true;
  }



  // semi-specific cases

  BOOST_PP_SEQ_FOR_EACH(MMLM_cimpl, _, MMLM_SHAPES)



  // general cases

  template <typename T1, typename T2>
  inline bool contains(const Shape<T1>& s1, const Shape<T2>& s2)
  {
    return local::cswitch1(s1, s2);
  }


}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros undef

# undef MMLM_cimpl



#endif /* !MML_CONTAINS_HXX_ */
