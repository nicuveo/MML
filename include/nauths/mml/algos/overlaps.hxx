//
// overlaps.hxx for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_OVERLAPS_HXX_
# define MML_OVERLAPS_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/lib/utils.hh"
# include "nauths/mml/algos/overlaps.hh"
# include "nauths/mml/algos/contains.hh"
# include "nauths/mml/algos/common.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros

# define MMLM_oimpl(_1, _2, S)                                          \
  template <typename T1, typename T2>                                   \
  inline bool overlaps(const Shape<T1>& s1, const MMLM_Name(S)<T2>& s2) \
  {                                                                     \
    return local::oswitch1(s1, s2);                                     \
  }                                                                     \
                                                                        \
  template <typename T1, typename T2>                                   \
  inline bool overlaps(const MMLM_Name(S)<T1>& s1, const Shape<T2>& s2) \
  {                                                                     \
    return local::oswitch2(s1, s2);                                     \
  }                                                                     \

# define MMLM_ooimpl(_, SXS)                                            \
  MMLM_oorimpl(BOOST_PP_SEQ_ELEM(0, SXS), BOOST_PP_SEQ_ELEM(1, SXS))    \

# define MMLM_oorimpl(S1, S2)                                           \
  template <typename T1, typename T2>                                   \
  bool overlaps(const MMLM_Name(S1)<T1>& s1,                            \
                const MMLM_Name(S2)<T2>& s2)                            \
  {                                                                     \
    BOOST_PP_IF(BOOST_PP_LESS_EQUAL(MMLM_VALUE(S1),                     \
                                    MMLM_VALUE(S2)),                    \
                return il::does_overlap(s1, s2),                        \
                return il::does_overlap(s2, s1));                       \
  }                                                                     \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local helpers

namespace mml
{

  namespace local
  {


    // type switch

    template <typename T>
    MML_SHAPE_UNION_VISITOR_WARG_E(OSwitch1, bool, T,
                                   return overlaps(x, arg_),
                                   return true);
    template <typename T>
    MML_SHAPE_UNION_VISITOR_WARG_E(OSwitch2, bool, T,
                                   return overlaps(arg_, x),
                                   return true);

    template <typename T1, typename T2>
    inline bool oswitch1(T1 const& s1, T2 const& s2)
    {
      return s1.apply(OSwitch1<T2 const&>(s2));
    }

    template <typename T1, typename T2>
    inline bool oswitch2(T1 const& s1, T2 const& s2)
    {
      return s2.apply(OSwitch2<T1 const&>(s1));
    }


  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{

  namespace il
  {


    // actual work

    template <typename T1, typename T2>
    inline bool does_overlap(const Point<T1>& s1, const Point<T2>& s2)
    {
      return s1 == s2;
    }

    template <typename T1, typename T2>
    inline bool does_overlap(const Point<T1>& s1, const Line<T2>& s2)
    {
      return contains(s2, s1);
    }

    template <typename T1, typename T2>
    inline bool does_overlap(const Point<T1>& s1, const Rect<T2>& s2)
    {
      return contains(s2, s1);
    }

    template <typename T1, typename T2>
    inline bool does_overlap(const Point<T1>& s1, const Circle<T2>& s2)
    {
      return contains(s2, s1);
    }

    template <typename T1, typename T2>
    inline bool does_overlap(const Point<T1>& s1, const Polygon<T2>& s2)
    {
      return contains(s2, s1);
    }

    template <typename T1, typename T2>
    inline bool does_overlap(const Line<T1>& l1, const Line<T2>& l2)
    {
      return il::lines_overlaps(l1, l2);
    }

    template <typename T1, typename T2>
    inline bool does_overlap(const Line<T1>& l, const Rect<T2>& r)
    {
      return overlaps(l.bounding_rect(), r);
    }

    template <typename T1, typename T2>
    inline bool does_overlap(const Line<T1>& l, const Circle<T2>& c)
    {
      return contains(c, il::closest_on_line(c.center(), l));
    }

    template <typename T1, typename T2>
    inline bool does_overlap(const Line<T1>& l, const Polygon<T2>& p)
    {
      if (contains(p, l[0]))
        return true;
      mml_foreach (const Line<T1>& e, p.lines())
        if (il::lines_intersect(e, l))
          return true;
      return false;
    }

    template <typename T1, typename T2>
    inline bool does_overlap(const Rect<T1>& s1, const Rect<T2>& s2)
    {
      return (le(s1.x_min(), s2.x_max()) and
              ge(s1.x_max(), s2.x_min()) and
              le(s1.y_min(), s2.y_max()) and
              ge(s1.y_max(), s2.y_min()));
    }

    template <typename T1, typename T2>
    inline bool does_overlap(const Rect<T1>& s1, const Circle<T2>& s2)
    {
      return contains(s2, clamp<Real>(s2.center(), s1.min(), s1.max()));
    }

    template <typename T1, typename T2>
    inline bool does_overlap(const Rect<T1>& r, const Polygon<T2>& p)
    {
      return overlaps(r, p.bounding_rect()) and
        (contains(r, p.points_data()[0]) or
         overlaps(p, Line<T2>(r.x_min(), r.y_min(), r.x_min(), r.y_max())) or
         overlaps(p, Line<T2>(r.x_min(), r.y_max(), r.x_max(), r.y_max())) or
         overlaps(p, Line<T2>(r.x_max(), r.y_max(), r.x_max(), r.y_min())) or
         overlaps(p, Line<T2>(r.x_max(), r.y_min(), r.x_min(), r.y_min())));
      return false;
    }

    template <typename T1, typename T2>
    inline bool does_overlap(const Circle<T1>& s1, const Circle<T2>& s2)
    {
      return le((s2.center() - s1.center()).length(), to<Real>(s1.radius() + s2.radius()));
    }

    template <typename T1, typename T2>
    inline bool does_overlap(const Circle<T1>& c, const Polygon<T2>& p)
    {
      if (contains(p, c.center()))
        return true;
      mml_foreach (const Line<T1>& l, p.lines())
        if (overlaps(l, c))
          return true;
      return false;
    }

    template <typename T1, typename T2>
    inline bool does_overlap(const Polygon<T1>& p1, const Polygon<T2>& p2)
    {
      if (overlaps(p1.bounding_rect(), p2.bounding_rect()))
      {
        if (contains(p2, p1.points_data().front()) or
            contains(p1, p2.points_data().front()))
          return true;
        else
          mml_foreach (const Line<T2>& l, p2.lines())
            if (overlaps(p1, l))
              return true;
      }
      return false;
    }


  }



  // specific cases

  BOOST_PP_SEQ_FOR_EACH_PRODUCT(MMLM_ooimpl, (MMLM_SHAPES)(MMLM_SHAPES))



  // semi-specific cases

  BOOST_PP_SEQ_FOR_EACH(MMLM_oimpl, _, MMLM_SHAPES)



  // general cases

  template <typename T1, typename T2>
  inline bool overlaps(const Shape<T1>& s1, const Shape<T2>& s2)
  {
    return local::oswitch1(s1, s2);
  }


}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros undef

# undef MMLM_oimpl
# undef MMLM_ooimpl
# undef MMLM_oorimpl



#endif /* !MML_OVERLAPS_HXX_ */
