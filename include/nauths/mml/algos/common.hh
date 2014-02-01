//
// common.hh for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_COMMON_HH_
# define MML_COMMON_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/shape.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  namespace il
  {

    // above_line
    //   returns true iif point p is above the given line l
    //   computed by testing whether the vertical line passing by p
    //   intersects with l
    //   warning: edge is considered to be [x0...x1[.

    template <typename T1, typename T2>
    bool
    above_line(const Point<T1>& point, const Line<T2>& edge);

    // distance_from_line
    //   returns the distance between a point p and its
    //   projection on line l

    template <typename T1, typename T2>
    Real
    distance_from_line(const Point<T1>& point, const Line<T2>& edge);

    // closest to line
    //   returns the point on l that is the closest to p
    template <typename T1, typename T2>
    Point<T2>
    closest_on_line(const Point<T1>& p, const Line<T2>& l);


    // lines_coeff
    //   outputs num1, num2, dem1 and dem2

    template <typename T1, typename T2>
    void
    lines_coeff(const Line<T1>& l1, const Line<T2>& l2,
                RefReal num1, RefReal num2,
                RefReal dem1, RefReal dem2);

    template <typename T1, typename T2, typename T3, typename T4>
    void
    lines_coeff(const Point<T1>& l1p1, const Point<T2>& l1p2,
                const Point<T3>& l2p1, const Point<T4>& l2p2,
                RefReal num1, RefReal num2,
                RefReal dem1, RefReal dem2);


    // lines_intersect
    //   outputs whether l1 and l2 crosses at a single point

    template <typename T1, typename T2>
    bool
    lines_intersect(const Line<T1>& l1, const Line<T2>& l2);

    // lines_cross
    //   outputs whether l1 and l2 crosses at a single point
    //   (uses gt and lt rather than ge and le)

    template <typename T1, typename T2>
    bool
    lines_strict_intersect(const Line<T1>& l1, const Line<T2>& l2);

    // lines_contains
    //   outputs whether l1 contains l2

    template <typename T1, typename T2>
    bool
    lines_contains(const Line<T1>& l1, const Line<T2>& l2);

    // lines_overlaps
    //   outputs whether l1 overlaps l2

    template <typename T1, typename T2>
    bool
    lines_overlaps(const Line<T1>& l1, const Line<T2>& l2);


    // polygon_contains_line

    template <typename T1, typename T2, typename T3>
    bool
    polygon_contains_line(const Polygon<T1>& p, const Point<T2>& l0, const Point<T3>& l1);


  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/algos/common.hxx"



#endif /* !MML_COMMON_HH_ */
