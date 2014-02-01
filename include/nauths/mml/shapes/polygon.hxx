//
// polygon.hxx for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_POLYGON_HXX_
# define MML_POLYGON_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/lib/utils.hh"
# include "nauths/mml/shapes/polygon.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{

  namespace il
  {


    // constructors

    template <typename T>
    Polygon<T>::Polygon() throw()
      : mean_(0, 0), min_(0, 0), max_(0, 0)
    {
    }

    template <typename T>
    Polygon<T>::Polygon(const ExactPoints& points)
      : points_(points), mean_(0, 0), min_(0, 0), max_(0, 0)
    {
      // TODO debug::polygon: check integrity

      if (valid())
      {
        min_ = points_[0];
        max_ = points_[0];

        Real mx = 0;
        Real my = 0;
        Real ratio = 1. / static_cast<Real>(points.size());

        mml_foreach (ExactPoint& p, points_)
        {
          min_.rx() = std::min(min_.x(), p.x());
          min_.ry() = std::min(min_.y(), p.y());
          max_.rx() = std::max(max_.x(), p.x());
          max_.ry() = std::max(max_.y(), p.y());
          mx += p.x();
          my += p.y();
        }

        mean_ = ExactPoint(mx * ratio, my * ratio);
      }
    }


    template <typename T>
    template <typename T2>
    Polygon<T>::Polygon(const Polygon<T2>& p)
    {
      const typename Polygon<T2>::ExactPoints& ops = p.points_data();
      ExactPoints nps;

      mml_foreach (const typename Polygon<T2>::ExactPoint& op, ops)
        nps.push_back(op);

      new (this) Polygon(nps);
    }


    // accessors

    template <typename T>
    typename Polygon<T>::SizeType
    Polygon<T>::size() const
    {
      return points_.size();
    }

    template <typename T>
    inline typename Polygon<T>::PointRange
    Polygon<T>::points() const
    {
      return PointRange(points_.begin(), points_.end());
    }

    template <typename T>
    inline std::pair<typename Polygon<T>::EdgeIterator,
                     typename Polygon<T>::EdgeIterator>
    Polygon<T>::edges() const
    {
      return tools::range(points_);
    }

    template <typename T>
    inline std::pair<typename Polygon<T>::LineIterator,
                     typename Polygon<T>::LineIterator>
    Polygon<T>::lines() const
    {
      return std::make_pair(LineIterator(tools::begin(points_), &Polygon<T>::e_to_l),
                            LineIterator(tools::end(points_),   &Polygon<T>::e_to_l));
    }


    template <typename T>
    inline const typename Polygon<T>::ExactPoints&
    Polygon<T>::points_data() const
    {
      return points_;
    }



    // state

    template <typename T>
    inline bool
    Polygon<T>::valid() const
    {
      return points_.size() > 2;
    }



    // geometry

    template <typename T>
    inline typename Polygon<T>::ExactRect
    Polygon<T>::bounding_rect() const
    {
      return ExactRect(min_, max_);
    }

    template <typename T>
    inline typename Polygon<T>::ExactPoint
    Polygon<T>::center() const
    {
      return mean_;
    }


    template <typename T>
    Real
    Polygon<T>::perimeter() const
    {
      Real res = 0;

      mml_foreach (ExactEdge e, edges())
        res += (tools::second(e) - tools::first(e)).length();

      return res;
    }

    template <typename T>
    Real
    Polygon<T>::area() const
    {
      Real res = 0;

      mml_foreach (ExactEdge e, edges())
        res = res
        + tools::first(e).x() * tools::second(e).y()
        - tools::first(e).y() * tools::second(e).x();

      return res < 0 ? (res / -2) : (res / 2);
    }



    // modifiers

    template <typename T>
    template <typename F>
    Polygon<T>
    Polygon<T>::transform(F const& ft) const
    {
      ExactPoints np;

      np.reserve(points_.size());
      mml_foreach (ExactPoint& p, np)
        np.push_back(ft(p));

      return np;
    }



    // in-place modifiers

    template <typename T>
    void
    Polygon<T>::move_of(const ExactVector& v)
    {
      mml_foreach (ExactPoint& p, points_)
        p   += v;
      min_  += v;
      max_  += v;
      mean_ += v;
    }

    template <typename T>
    void
    Polygon<T>::move_to(const ExactPoint& p)
    {
      const ExactVector& v = p - mean_;

      mml_foreach (ExactPoint& p, points_)
        p  += v;
      min_ += v;
      max_ += v;
      mean_ = p;
    }


    template <typename T>
    void
    Polygon<T>::scale(PrmReal s)
    {
      mml_foreach (ExactPoint& p, points_)
        p  = mean_ + (p    - mean_) * s;
      min_ = mean_ + (min_ - mean_) * s;
      max_ = mean_ + (max_ - mean_) * s;
    }



    // internal conversion

    template <typename T>
    inline typename Polygon<T>::ExactLine
    Polygon<T>::e_to_l(ExactEdge const& e)
    {
      return ExactLine(tools::first(e), tools::second(e));
    }



    // comparison operators

    template <typename T1, typename T2>
    inline bool
    operator==(const Polygon<T1>& p1, const Polygon<T2>& p2)
    {
      return (p1.points_data() == p2.points_data());
    }

    template <typename T1, typename T2>
    inline bool
    operator!=(const Polygon<T1>& p1, const Polygon<T2>& p2)
    {
      return (p1.points_data() != p2.points_data());
    }


  }

}



#endif /* !MML_POLYGON_HXX_ */
