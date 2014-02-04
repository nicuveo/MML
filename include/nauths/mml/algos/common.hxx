//
// Copyright Antoine Leblanc 2010 - 2014
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_COMMON_HXX_
# define MML_COMMON_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/algos/common.hh"
# include "nauths/mml/algos/contains.hh"
# include "nauths/mml/algos/overlaps.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{

  namespace il
  {


    template <typename T1, typename T2>
    bool
    above_line(const Point<T1>& point, const Line<T2>& edge)
    {
      if (gt(edge.x0(), edge.x1()))
        return above_line(point, -edge);

      return (le(edge.x0(), point.x()) and
              lt(point.x(), edge.x1()) and
              lt(((point.y() - edge.y0()) * (edge.x1() - edge.x0())),
                 ((edge.y1() - edge.y0()) * (point.x() - edge.x0()))));
    }

    template <typename T1, typename T2>
    inline bool
    distance_from_line(const Point<T1>& p, const Line<T2>& l)
    {
      BOOST_AUTO(const& d, p - l[0]);
      return std::abs(d.x() * l.dy() - d.y() * l.dx()) / l.length();
    }

    template <typename T1, typename T2>
    inline Point<T2>
    closest_on_line(const Point<T1>& p, const Line<T2>& l)
    {
      Real k = ((p - l[0]) * l.delta()) / std::pow(l.length(), 2);
      return l[0] + clamp<Real>(k, 0., 1.) * l.delta();
    }


    template <typename T1, typename T2>
    inline void
    lines_coeff(const Line<T1>& l1, const Line<T2>& l2,
                RefReal num1, RefReal num2,
                RefReal dem1, RefReal dem2)
    {
      lines_coeff(l1[0], l1[1], l2[0], l2[1], num1, num2, dem1, dem2);
    }

    template <typename T1, typename T2, typename T3, typename T4>
    void
    lines_coeff(const Point<T1>& l1p1, const Point<T2>& l1p2,
                const Point<T3>& l2p1, const Point<T4>& l2p2,
                RefReal num1, RefReal num2,
                RefReal dem1, RefReal dem2)
    {
      BOOST_AUTO(const& d1, l1p2 - l1p1);
      BOOST_AUTO(const& d2, l2p2 - l2p1);
      BOOST_AUTO(const& n1, d1.normal());
      BOOST_AUTO(const& n2, d2.normal());
      num1 = (l2p1 - l1p1) * n2;
      num2 = (l1p1 - l2p1) * n1;
      dem1 = d1 * n2;
      dem2 = d2 * n1;

      // assert(eq(dem1, dem2));
    }

    template <typename T1, typename T2>
    bool
    lines_intersect(const Line<T1>& l1, const Line<T2>& l2)
    {
      Real n1;
      Real n2;
      Real d1;
      Real d2;

      lines_coeff(l1, l2, n1, n2, d1, d2);
      if (ne(d1, Real(0.)))
      {
        Real k1 = n1 / d1;
        Real k2 = n2 / d2;
        return (ge(k1, Real(0.)) and ge(k2, Real(0.)) and
                le(k1, Real(1.)) and le(k2, Real(1.)));
      }
      return false;
    }

    template <typename T1, typename T2>
    bool
    lines_strict_intersect(const Line<T1>& l1, const Line<T2>& l2)
    {
      Real n1;
      Real n2;
      Real d1;
      Real d2;

      lines_coeff(l1, l2, n1, n2, d1, d2);
      if (ne(d1, Real(0.)))
      {
        Real k1 = n1 / d1;
        Real k2 = n2 / d2;
        return (gt(k1, Real(0.)) and gt(k2, Real(0.)) and
                lt(k1, Real(1.)) and lt(k2, Real(1.)));
      }
      return false;
    }

    template <typename T1, typename T2>
    bool
    lines_contains(const Line<T1>& l1, const Line<T2>& l2)
    {
      Real n1;
      Real n2;
      Real d1;
      Real d2;

      lines_coeff(l1, l2, n1, n2, d1, d2);
      return eq(d1, Real(0.)) and eq(n1, Real(0.)) and contains(l1.bounding_rect(), l2.bounding_rect());
    }

    template <typename T1, typename T2>
    bool
    lines_overlaps(const Line<T1>& l1, const Line<T2>& l2)
    {
      Real n1;
      Real n2;
      Real d1;
      Real d2;

      lines_coeff(l1, l2, n1, n2, d1, d2);
      return eq(d1, Real(0.)) and eq(n1, Real(0.)) and overlaps(l1.bounding_rect(), l2.bounding_rect());
    }

    template <typename T1, typename T2, typename T3>
    bool
    polygon_contains_line(const Polygon<T1>& p, const Point<T2>& l0, const Point<T3>& l1)
    {
      mml_foreach (const Line<T1>& e, p.lines())
      {
        Real n1;
        Real n2;
        Real d1;
        Real d2;

        lines_coeff(l0, l1, e[0], e[1], n1, n2, d1, d2);

        if (ne(d1, Real(0.)))
        {
          Real k1 = n1 / d1;
          Real k2 = n2 / d2;

          if (gt(k1, Real(0.)) and lt(k1, Real(1.)))
          {
            if (gt(k2, Real(0.)) and lt(k2, Real(1.)))
              return false;
            else if (eq(k2, Real(0.)))
              return (polygon_contains_line(p, l0, e[0]) and
                      polygon_contains_line(p, l1, e[0]));
            else if (eq(k2, Real(1.)))
              return (polygon_contains_line(p, l0, e[1]) and
                      polygon_contains_line(p, l1, e[1]));
          }
        }
      }

      return contains(p, (l0 + l1) / 2);
    }

  }

}



#endif /* !MML_COMMON_HXX_ */
