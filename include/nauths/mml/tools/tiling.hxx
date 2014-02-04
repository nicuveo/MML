//
// Copyright Antoine Leblanc 2010 - 2014
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_TILING_HXX_
# define MML_TILING_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/tools/tiling.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros

# define MMLM_case_links(_1, _2, S)                                    \
  case tiling::MML_TILING_NAME(S):                                     \
    BOOST_PP_CAT(MML_TILING_name(S), _links)(rmap, index, links);      \
    break;

# define MMLM_case_dv(_1, F, S)                                        \
  case tiling::MML_TILING_NAME(S):                                     \
    F = to<E1Value>(BOOST_PP_CAT(MML_TILING_name(S), _dv)());          \
    break;

# define MMLM_case_pattern(_1, _2, S)                                  \
  case tiling::MML_TILING_NAME(S):                                     \
    BOOST_PP_CAT(BOOST_PP_CAT(init_, MML_TILING_name(S)), _pattern)(); \
    break;

# define MMLM_ratio(A, B) (A) / (A + B)



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{

  namespace tiling
  {


    inline Real ratio(Num p1, Num p2)
    {
      if (p2 > p1)
        return 1. - ratio(p2, p1);

      switch (p1 * 100 + p2)
      {
        case  303: return 0.50;                                       //  triangle ->  triangle
        case  403: return MMLM_ratio(3., root_3());                   //    square ->  triangle
        case  404: return 0.50;                                       //    square ->    square
        case  603: return 0.75;                                       //   hexagon ->  triangle
        case  604: return MMLM_ratio(root_3(), 1.);                   //   hexagon ->    square
        case  606: return 0.50;                                       //   hexagon ->   hexagon
        case  803: return MMLM_ratio(3. * (1. + root_2()), root_3()); //   octagon ->  triangle
        case  804: return MMLM_ratio(1. + root_2(), 1.);              //   octagon ->    square
        case  806: return MMLM_ratio(1. + root_2(), root_3());        //   octagon ->   hexagon
        case  808: return 0.50;                                       //   octagon ->   octagon
        case 1203: return MMLM_ratio(3. * (2. + root_3()), root_3()); // dodecagon ->  triangle
        case 1204: return MMLM_ratio(2. + root_3(), 1.);              // dodecagon ->    square
        case 1206: return MMLM_ratio(2. + root_3(), root_3());        // dodecagon ->   hexagon
        case 1208: return MMLM_ratio(2. + root_3(), root_2() + 1.);   // dodecagon ->   octagon
        case 1212: return 0.5;                                        // dodecagon -> dodecagon
      }

      // FIXME
      assert(not "reached");

      return 0. / 0.;
    }


  }



  // internal iterator type

  template <typename T1, typename T2, typename I>
  inline Tessellation<T1, T2, I>::iterator::iterator()
    : index_(0, 0), tess_(0)
  {
  }

  template <typename T1, typename T2, typename I>
  inline Tessellation<T1, T2, I>::iterator::iterator(const Tessellation* t, IndexPrm i, bool l, bool s)
    : get_l_(l), strict_(s), index_(i, i), tess_(t)
  {
  }

  template <typename T1, typename T2, typename I>
  typename Tessellation<T1, T2, I>::iterator
  Tessellation<T1, T2, I>::iterator::begin(const Tessellation* t, bool l, bool s)
  {
    iterator res(t, 0, l, s);

    res.index_map_.reset(new IndexMap());
    res.compute();

    return res;
  }

  template <typename T1, typename T2, typename I>
  typename Tessellation<T1, T2, I>::iterator
  Tessellation<T1, T2, I>::iterator::end(const Tessellation* t, IndexPrm max)
  {
    return iterator(t, max, false, false);
  }


  template <typename T1, typename T2, typename I>
  inline typename Tessellation<T1, T2, I>::IndexType
  Tessellation<T1, T2, I>::iterator::index() const
  {
    return index_.first;
  }

  template <typename T1, typename T2, typename I>
  inline const typename Tessellation<T1, T2, I>::Links&
  Tessellation<T1, T2, I>::iterator::links() const
  {
    return links_;
  }


  template <typename T1, typename T2, typename I>
  inline const typename Tessellation<T1, T2, I>::E1Shape&
  Tessellation<T1, T2, I>::iterator::dereference() const
  {
    return current_;
  }

  template <typename T1, typename T2, typename I>
  inline bool
  Tessellation<T1, T2, I>::iterator::equal(const iterator& si) const
  {
    return tess_ == si.tess_ and index_.second == si.index_.second;
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::iterator::increment()
  {
    index_.first  += 1;
    index_.second += 1;
    compute();
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::iterator::compute()
  {
    current_ = tess_->get(index_map_, index_.second, (get_l_ ? &links_ : 0), strict_);
    if (index_map_)
      (*index_map_)[index_.second] = index_.first;
  }



  // constructors

  template <typename T1, typename T2, typename I>
  Tessellation<T1, T2, I>::Tessellation(TilingType t, const E2Shape& s,
                                        E1Prm size_x, PrmReal a)
    : type_(t), bound_box_(s.bounding_rect()), bounds_(s),
      size_x_(size_x), size_y_(0), angle_(a), center_(0, 0)
  {
    init();
  }

  template <typename T1, typename T2, typename I>
  Tessellation<T1, T2, I>::Tessellation(TilingType t, const E2Shape& s,
                                        const E1Vector& size, PrmReal a)
    : type_(t), bound_box_(s.bounding_rect()), bounds_(s),
      size_x_(size.x()), size_y_(size.y()), angle_(a), center_(0, 0)
  {
    init();
  }

  template <typename T1, typename T2, typename I>
  Tessellation<T1, T2, I>::Tessellation(TilingType t, const E2Shape& s,
                                        E1Prm ox, E1Prm oy, E1Prm size_x, PrmReal a)
    : type_(t), bound_box_(s.bounding_rect()), bounds_(s),
      size_x_(size_x), size_y_(0), angle_(a), center_(ox, oy)
  {
    init();
  }

  template <typename T1, typename T2, typename I>
  Tessellation<T1, T2, I>::Tessellation(TilingType t, const E2Shape& s,
                                        E1Prm ox, E1Prm oy, const E1Vector& size, PrmReal a)
    : type_(t), bound_box_(s.bounding_rect()), bounds_(s),
      size_x_(size.x()), size_y_(size.y()), angle_(a), center_(ox, oy)
  {
    init();
  }

  template <typename T1, typename T2, typename I>
  Tessellation<T1, T2, I>::Tessellation(TilingType t, const E2Shape& s,
                                        const E1Point& offset, E1Prm size_x, PrmReal a)
    : type_(t), bound_box_(s.bounding_rect()), bounds_(s),
      size_x_(size_x), size_y_(0), angle_(a), center_(offset)
  {
    init();
  }

  template <typename T1, typename T2, typename I>
  Tessellation<T1, T2, I>::Tessellation(TilingType t, const E2Shape& s,
                                        const E1Point& offset, const E1Vector& size, PrmReal a)
    : type_(t), bound_box_(s.bounding_rect()), bounds_(s),
      size_x_(size.x()), size_y_(size.y()), angle_(a), center_(offset)
  {
    init();
  }



  // accessors

  template <typename T1, typename T2, typename I>
  inline const std::vector<typename Tessellation<T1, T2, I>::E1Shape>&
  Tessellation<T1, T2, I>::pattern() const
  {
    return pattern_;
  }

  template <typename T1, typename T2, typename I>
  inline const typename Tessellation<T1, T2, I>::E2Shape&
  Tessellation<T1, T2, I>::bounds() const
  {
    return bounds_;
  }

  template <typename T1, typename T2, typename I>
  inline const typename Tessellation<T1, T2, I>::E1Point&
  Tessellation<T1, T2, I>::center() const
  {
    return center_;
  }

  template <typename T1, typename T2, typename I>
  inline const typename Tessellation<T1, T2, I>::E1Vector&
  Tessellation<T1, T2, I>::dh() const
  {
    return dh_;
  }

  template <typename T1, typename T2, typename I>
  inline const typename Tessellation<T1, T2, I>::E1Vector&
  Tessellation<T1, T2, I>::dv() const
  {
    return dv_;
  }

  template <typename T1, typename T2, typename I>
  inline TilingType
  Tessellation<T1, T2, I>::type() const
  {
    return type_;
  }

  template <typename T1, typename T2, typename I>
  inline Real
  Tessellation<T1, T2, I>::angle() const
  {
    return angle_;
  }



  // shapes access

  template <typename T1, typename T2, typename I>
  inline std::pair<typename Tessellation<T1, T2, I>::iterator,
                   typename Tessellation<T1, T2, I>::iterator>
  Tessellation<T1, T2, I>::shapes(bool s, bool l) const
  {
    return std::make_pair(begin(s, l), end());
  }

  template <typename T1, typename T2, typename I>
  inline typename Tessellation<T1, T2, I>::iterator
  Tessellation<T1, T2, I>::begin(bool s, bool l) const
  {
    return iterator::begin(this, l, s);
  }

  template <typename T1, typename T2, typename I>
  inline typename Tessellation<T1, T2, I>::iterator
  Tessellation<T1, T2, I>::end() const
  {
    return iterator::end(this, max_);
  }



  // internal helper types

  template <typename T1, typename T2, typename I>
  void
  Tessellation<T1, T2, I>::push(IndexMapPrm imap, IndexPrm index, Links* v, IndexType delta, Real d)
  {
    if (ge(index, delta))
    {
      typename IndexMap::const_iterator it = imap.find(index - delta);
      if (it != imap.end())
        v->push_back(std::make_pair(it->second, d));
    }
  }

  template <typename T1, typename T2, typename I>
  typename Tessellation<T1, T2, I>::E1PointsVector
  Tessellation<T1, T2, I>::create_vector(const E1Vector& ref, PrmNum dem, PrmNum size)
  {
    E1PointsVector res(size);

    for (Num i = 0; lt(i, size); ++i)
      res[i] = E1Point((i / dem) * ref + ((i % dem) * ref) / to<Real>(dem));

    return res;
  }

  template <typename T1, typename T2, typename I>
  typename Tessellation<T1, T2, I>::E1PointsMatrix
  Tessellation<T1, T2, I>::create_matrix(const E1Point& p0,
                                         const E1PointsVector& xs,
                                         const E1PointsVector& ys)
  {
    typedef typename E1PointsVector::size_type IndexType;

    E1PointsMatrix res(ys.size(), E1PointsVector(xs.size(), p0));

    for (IndexType y = 0; y < ys.size(); ++y)
      for (IndexType x = 0; x < xs.size(); ++x)
        res[y][x] += ys[y] + xs[x];

    return res;
  }



  // shape retrieval

  template <typename T1, typename T2, typename I>
  inline typename Tessellation<T1, T2, I>::E1Shape
  Tessellation<T1, T2, I>::get(IndexMapPtr imap, IndexRef index, Links* links, bool strict) const
  {
    while (index < max_)
    {
      IndexType i1y = (index / pattern_.size()) / steps_x_;
      IndexType i1x = (index / pattern_.size()) % steps_x_;
      IndexType i2  = (index % pattern_.size());

      const E1Point p = base_ + to<Num>(i1y) * dv_ + to<Num>(i1x) * dh_;
      const E1Shape res = pattern_[i2].moved_of(p);

      if (strict ? contains(bounds_, res) : overlaps(bounds_, res))
      {
        if (links)
        {
          // FIXME
          assert(imap);
          IndexMapPrm rmap = *imap;

          links->clear();
          switch (type_)
          {
            BOOST_PP_SEQ_FOR_EACH(MMLM_case_links, _, MML_TILINGS)
          }
        }

        return res;
      }

      index += 1;
    }

    return E1Shape();
  }



  // dv computation

  template <typename T1, typename T2, typename I>
  inline Real
  Tessellation<T1, T2, I>::triangular_dv() const
  {
    return size_x_ * root_3();
  }

  template <typename T1, typename T2, typename I>
  inline Real
  Tessellation<T1, T2, I>::square_dv() const
  {
    return size_x_;
  }

  template <typename T1, typename T2, typename I>
  inline Real
  Tessellation<T1, T2, I>::hexagonal_dv() const
  {
    return size_x_ * root_3_div_3();
  }

  template <typename T1, typename T2, typename I>
  inline Real
  Tessellation<T1, T2, I>::snub_hexagonal_dv() const
  {
    return size_x_ * root_3();
  }

  template <typename T1, typename T2, typename I>
  inline Real
  Tessellation<T1, T2, I>::reflected_snub_hexagonal_dv() const
  {
    return size_x_ * root_3();
  }

  template <typename T1, typename T2, typename I>
  inline Real
  Tessellation<T1, T2, I>::tri_hexagonal_dv() const
  {
    return size_x_ * root_3();
  }

  template <typename T1, typename T2, typename I>
  inline Real
  Tessellation<T1, T2, I>::elongated_triangular_dv() const
  {
    return size_x_ * (2. + root_3());
  }

  template <typename T1, typename T2, typename I>
  inline Real
  Tessellation<T1, T2, I>::snub_square_dv() const
  {
    return size_x_;
  }

  template <typename T1, typename T2, typename I>
  inline Real
  Tessellation<T1, T2, I>::rhombitrihexagonal_dv() const
  {
    return size_x_ * root_3();
  }

  template <typename T1, typename T2, typename I>
  inline Real
  Tessellation<T1, T2, I>::truncated_square_dv() const
  {
    return size_x_;
  }

  template <typename T1, typename T2, typename I>
  inline Real
  Tessellation<T1, T2, I>::truncated_hexagonal_dv() const
  {
    return size_x_ * root_3();
  }

  template <typename T1, typename T2, typename I>
  inline Real
  Tessellation<T1, T2, I>::truncated_trihexagonal_dv() const
  {
    return size_x_ * root_3_div_3();
  }


  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::triangular_links(IndexMapPrm imap, IndexPrm index, Links* v) const
  {
    IndexType pi = (index % pattern_.size());
    Real d = triangular_dv() / 3.;

    switch (pi)
    {
      case 0:
        push(imap, index, v, pattern_.size() * steps_x_ - 3, d);
        push(imap, index, v, 3,                              d);
        break;
      case 1:
        push(imap, index, v, 1,                              d);
        break;
      case 2:
        push(imap, index, v, 1,                              d);
        break;
      case 3:
        push(imap, index, v, 1,                              d);
        push(imap, index, v, 5,                              d);
        break;
      default:
        assert(false); // FIXME
    }
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::square_links(IndexMapPrm imap, IndexPrm index, Links* v) const
  {
    push(imap, index, v, 1,        size_x_);
    push(imap, index, v, steps_x_, size_x_);
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::hexagonal_links(IndexMapPrm imap, IndexPrm index, Links* v) const
  {
    IndexType pi = (index % pattern_.size());
    Real d = hexagonal_dv();

    switch (pi)
    {
      case 0:
        push(imap, index, v, 1,                              d);
        push(imap, index, v, pattern_.size() * steps_x_,     d);
        push(imap, index, v, pattern_.size() * steps_x_ - 1, d);
        push(imap, index, v, pattern_.size() * steps_x_ + 1, d);
        break;
      case 1:
        push(imap, index, v, 1,                              d);
        push(imap, index, v, pattern_.size() * steps_x_,     d);
        break;
      default:
        assert(false); // FIXME
    }
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::snub_hexagonal_links(IndexMapPrm imap, IndexPrm index, Links* v) const
  {
    IndexType n  = pattern_.size();
    IndexType i1 = (index % n) / 9;
    IndexType i2 = (index % n) % 9;

    Real hex_d = snub_hexagonal_dv() * (2. / 21.);
    Real tri_d = snub_hexagonal_dv() * (1. / 21.);

    switch (i2)
    {
      case 0:
        switch (i1)
        {
          case  0:
            push(imap, index, v, n * steps_x_ + 2, hex_d);
            break;
          case  2:
          case  5:
          case  8:
          case 11:
            push(imap, index, v, n + 2,            hex_d);
            push(imap, index, v, n - 22,           hex_d);
            break;
          default:
            push(imap, index, v, 2,                hex_d);
            break;
        }
        break;

      case 1:
        switch (i1)
        {
          case 0:
            push(imap, index, v, n *  steps_x_      +  4, tri_d);
            push(imap, index, v, n * (steps_x_ - 1) + 28, hex_d);
            break;
          case 1:
            push(imap, index, v,                       4, tri_d);
            push(imap, index, v, n * (steps_x_ - 1) + 28, hex_d);
            break;
          case  2:
            push(imap, index, v, n                  +  4, tri_d);
            push(imap, index, v, n *  steps_x_      + 28, hex_d);
            break;
          case  5:
          case  8:
          case 11:
            push(imap, index, v, n                  + 4, tri_d);
            push(imap, index, v,                     28, hex_d);
            break;
          default:
            push(imap, index, v,                      4, tri_d);
            push(imap, index, v,                     28, hex_d);
            break;
        }
        break;

      case 2:
        push(imap, index, v, 1, tri_d);
        push(imap, index, v, 2, hex_d);
        break;

      case 3:
        push(imap, index, v, 1, tri_d);
        switch (i1)
        {
          case  0:
          case  1:
            push(imap, index, v, n * (steps_x_ - 1) + 22, tri_d);
            break;
          case  2:
            push(imap, index, v, n * steps_x_ + 22, tri_d);
            break;
          default:
            push(imap, index, v, 22, tri_d);
            break;
        }
        break;

      case 4:
        push(imap, index, v, 1, tri_d);
        switch (i1)
        {
          case  0:
          case  1:
            push(imap, index, v, n * (steps_x_ - 1) + 22, hex_d);
            break;
          case  4:
          case  7:
          case 10:
          case 13:
            break;
          default:
            push(imap, index, v, 22, hex_d);
            break;
        }
        break;

      case 5:
        push(imap, index, v, 1, tri_d);
        push(imap, index, v, 5, hex_d);
        break;

      case 6:
      case 7:
        push(imap, index, v, 1, tri_d);
        break;

      case 8:
        push(imap, index, v, 1, tri_d);
        push(imap, index, v, 8, hex_d);
        break;
    }
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::reflected_snub_hexagonal_links(IndexMapPrm imap, IndexPrm index, Links* v) const
  {
    IndexType n  = pattern_.size();
    IndexType i1 = (index % n) / 9;
    IndexType i2 = (index % n) % 9;

    Real hex_d = snub_hexagonal_dv() * (2. / 21.);
    Real tri_d = snub_hexagonal_dv() * (1. / 21.);

    switch (i2)
    {
      case 0:
        switch (i1)
        {
          case  0:
            push(imap, index, v, n * (steps_x_ - 2) + 2, hex_d);
            break;
          case  2:
          case  5:
          case  8:
          case 11:
            break;
          default:
            push(imap, index, v, 2, hex_d);
            break;
        }
        break;

      case 1:
        switch (i1)
        {
          case 0:
            push(imap, index, v, n * (steps_x_ - 2) +  4, tri_d);
            push(imap, index, v, n * (steps_x_ - 1) + 28, hex_d);
            break;
          case 1:
            push(imap, index, v,                       4, tri_d);
            push(imap, index, v, n * (steps_x_ - 1) + 28, hex_d);
            break;
          case  2:
            push(imap, index, v, n * (steps_x_ - 2) + 28, hex_d);
            break;
          case  5:
          case  8:
          case 11:
            push(imap, index, v,                      28, hex_d);
            break;
          default:
            push(imap, index, v,                       4, tri_d);
            push(imap, index, v,                      28, hex_d);
            break;
        }
        break;

      case 2:
        push(imap, index, v, 1, tri_d);
        push(imap, index, v, 2, hex_d);
        break;

      case 3:
        push(imap, index, v, 1, tri_d);
        switch (i1)
        {
          case  0:
          case  1:
            push(imap, index, v, n * (steps_x_ - 1) + 22, tri_d);
            break;
          case  2:
            push(imap, index, v, n * (steps_x_ - 2) + 22, tri_d);
            break;
          default:
            push(imap, index, v, 22, tri_d);
            break;
        }
        break;

      case 4:
        push(imap, index, v, 1, tri_d);
        switch (i1)
        {
          case  0:
          case  1:
            push(imap, index, v, n * (steps_x_ - 1) + 22, hex_d);
            break;
          case  4:
          case  7:
          case 10:
          case 13:
            push(imap, index, v, n + 22, hex_d);
            break;
          default:
            push(imap, index, v, 22, hex_d);
            break;
        }
        break;

      case 5:
        push(imap, index, v, 1, tri_d);
        push(imap, index, v, 5, hex_d);
        break;

      case 6:
        push(imap, index, v, 1, tri_d);
        switch (i1)
        {
          case  1:
          case  4:
          case  7:
          case 10:
            push(imap, index, v, n - 4, tri_d);
            break;
        }
        break;

      case 7:
        push(imap, index, v, 1, tri_d);
        switch (i1)
        {
          case  1:
          case  4:
          case  7:
          case 10:
            push(imap, index, v, n - 2, hex_d);
            break;
        }
        break;

      case  8:
        push(imap, index, v, 1, tri_d);
        push(imap, index, v, 8, hex_d);
        break;
    }
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::tri_hexagonal_links(IndexMapPrm imap, IndexPrm index, Links* v) const
  {
    IndexType n = pattern_.size();
    IndexType i = index % n;

    Real d = tri_hexagonal_dv() / 3.;

    switch (i)
    {
      case 0:
        push(imap, index, v, n * steps_x_ + 1, d);
        push(imap, index, v, 2,                d);
      case 1:
        push(imap, index, v, 3 - i,            d);
        push(imap, index, v, 4 - i,            d);
        break;
      case 2:
        push(imap, index, v, n * steps_x_ + 1, d);
        push(imap, index, v, 2,                d);
        break;
      case 3:
        push(imap, index, v, 2,                d);
        push(imap, index, v, 3,                d);
        break;
      case 4:
      case 5:
        push(imap, index, v, i - 1,            d);
        break;
    }
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::elongated_triangular_links(IndexMapPrm imap, IndexPrm index, Links* v) const
  {
    IndexType n = pattern_.size();
    IndexType i = index % n;

    Real sqa_d = size_x_;
    Real tri_d = triangular_dv() / 3.;
    Real mix_d = size_x_ * ((root_3_div_3() + 1.) / 2.);

    switch (i)
    {
      case 0:
        push(imap, index, v, n * steps_x_ - 4, mix_d);
      case 1:
        push(imap, index, v, n, sqa_d);
        break;
      case 2:
        push(imap, index, v, 2, mix_d);
      case 4:
        push(imap, index, v, n - 1, tri_d);
        break;
      case 3:
        push(imap, index, v, 1, tri_d);
        push(imap, index, v, 2, mix_d);
        break;
      case 5:
        push(imap, index, v, 1, tri_d);
        push(imap, index, v, 4, mix_d);
        break;
    }
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::snub_square_links(IndexMapPrm imap, IndexPrm index, Links* v) const
  {
    IndexType n = pattern_.size();
    IndexType i = index % n;

    Real tri_d = size_x_ * ( root_3_div_3()      /      (root_3() + 1.) );
    Real mix_d = size_x_ * ((root_3_div_3() + 1) / (2 * (root_3() + 1.)));

    switch (i)
    {
      case  0:
        push(imap, index, v, n * steps_x_ - 11, mix_d);
        break;
      case  1:
        push(imap, index, v, 1,                 mix_d);
        push(imap, index, v, 7,                 mix_d);
        push(imap, index, v, 8 + n * steps_x_,  tri_d);
        break;
      case  4:
        push(imap, index, v, 1,                 mix_d);
        push(imap, index, v, 2,                 tri_d);
        break;
      case  6:
        push(imap, index, v, 4,                 mix_d);
        break;
      case  7:
        push(imap, index, v, 1,                 mix_d);
        push(imap, index, v, n * steps_x_ - 4,  tri_d);
        push(imap, index, v, n * steps_x_ + 4,  mix_d);
        break;
      case  8:
        push(imap, index, v, 2,                 mix_d);
        push(imap, index, v, 5,                 mix_d);
        break;
      case  9:
        push(imap, index, v, 5,                 mix_d);
        push(imap, index, v, 16,                mix_d);
        break;
      case 10:
        push(imap, index, v, 1,                 mix_d);
        push(imap, index, v, 10,                mix_d);
        push(imap, index, v, 14,                tri_d);
        break;

      case  2:
      case  5:
      case 11:
        push(imap, index, v, 2, mix_d);
        break;
    }
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::rhombitrihexagonal_links(IndexMapPrm imap, IndexPrm index, Links* v) const
  {
    IndexType n = pattern_.size();
    IndexType i = index % n;

    Real hex_d = size_x_ / 2.;
    Real tri_d = rhombitrihexagonal_dv() / 6.;

    switch (i)
    {
      case  0:
        push(imap, index, v, 9,                hex_d);
        push(imap, index, v, 7,                hex_d);
        push(imap, index, v, 5 + n * steps_x_, hex_d);
        break;
      case  1:
        push(imap, index, v, 7,                hex_d);
        break;
      case  2:
        push(imap, index, v, 2,                hex_d);
        push(imap, index, v, 1 + n * steps_x_, hex_d);
        push(imap, index, v, 3 + n * steps_x_, tri_d);
        break;
      case  3:
        push(imap, index, v, 3,                hex_d);
        break;
      case  4:
        push(imap, index, v, 3,                hex_d);
        push(imap, index, v, 4,                hex_d);
        push(imap, index, v, 6,                tri_d);
        break;
      case  5:
      case  6:
      case  7:
        push(imap, index, v, i - 1,            hex_d);
        break;
      case  8:
        push(imap, index, v, 6,                tri_d);
        push(imap, index, v, 5,                tri_d);
        push(imap, index, v, 1 + n * steps_x_, tri_d);
        break;
      case  9:
        push(imap, index, v, 6,                tri_d);
      case 10:
      case 11:
        push(imap, index, v, 4,                tri_d);
        push(imap, index, v, 5,                tri_d);
        break;
    }
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::truncated_square_links(IndexMapPrm imap, IndexPrm index, Links* v) const
  {
    IndexType n = pattern_.size();
    IndexType i = index % n;

    Real mix_d = size_x_ / 2.;
    Real oct_d = mix_d * root_2();

    push(imap, index, v, 2, mix_d);
    switch (i)
    {
      case 0:
        push(imap, index, v, 1,                mix_d);
        push(imap, index, v, 3,                oct_d);
        push(imap, index, v, n * steps_x_ - 1, oct_d);
        push(imap, index, v, n * steps_x_ + 1, mix_d);
        push(imap, index, v, n * steps_x_ + 3, oct_d);
        break;
      case 1:
        push(imap, index, v, 1,                oct_d);
        break;
      case 2:
        push(imap, index, v, 1,                mix_d);
        push(imap, index, v, n * steps_x_ + 1, mix_d);
        break;
    }
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::truncated_hexagonal_links(IndexMapPrm imap, IndexPrm index, Links* v) const
  {
    IndexType n = pattern_.size();
    IndexType i = index % n;

    Real tri_d = size_x_ * ((1. + 2. / root_3()) / (root_3() + 2.));
    Real dod_d = size_x_;

    switch (i)
    {
      case 0:
        push(imap, index, v, 2,                tri_d);
        push(imap, index, v, 3,                tri_d);
        push(imap, index, v, 4,                tri_d);
        push(imap, index, v, 5,                dod_d);
        push(imap, index, v, 6,                dod_d);
        push(imap, index, v, n * steps_x_ - 1, dod_d);
        push(imap, index, v, n * steps_x_ + 1, tri_d);
        push(imap, index, v, n * steps_x_ + 5, dod_d);
        break;
      case 1:
        push(imap, index, v, 1,                dod_d);
        push(imap, index, v, 2,                tri_d);
        push(imap, index, v, 3,                tri_d);
        push(imap, index, v, 6,                dod_d);
        break;
      case 2:
        push(imap, index, v, 2,                tri_d);
        push(imap, index, v, n * steps_x_ + 1, tri_d);
        break;
      case 3:
        push(imap, index, v, 2,                tri_d);
        push(imap, index, v, 3,                tri_d);
        break;
      case 4:
        push(imap, index, v, 3,                tri_d);
        break;
      case 5:
        push(imap, index, v, 4,                tri_d);
        break;
    }
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::truncated_trihexagonal_links(IndexMapPrm imap, IndexPrm index, Links* v) const
  {
    IndexType n = pattern_.size();
    IndexType i = index % n;

    Real dod_squ = truncated_trihexagonal_dv() / 2.;;
    Real dod_hex = size_x_ / 3.;
    Real hex_squ = size_x_ / 6.;

    switch (i)
    {
      case  0:
        push(imap, index, v,  3,                dod_squ);
        push(imap, index, v,  8,                dod_hex);
        push(imap, index, v, n * steps_x_ -  8, dod_squ);
        push(imap, index, v, n * steps_x_ -  3, dod_hex);
        push(imap, index, v, n * steps_x_ +  2, dod_squ);
        push(imap, index, v, n * steps_x_ +  7, dod_hex);
        push(imap, index, v, n * steps_x_ +  8, dod_hex);
        break;
      case  1:
        push(imap, index, v, n * steps_x_ -  4, dod_hex);
        push(imap, index, v, n * steps_x_ - 10, dod_squ);
        break;
      case  2:
        push(imap, index, v,  1,                dod_hex);
        push(imap, index, v,  2,                dod_hex);
        push(imap, index, v, n * steps_x_ +  1, dod_hex);
        push(imap, index, v, n * steps_x_ -  9, hex_squ);
        break;
      case  3:
        push(imap, index, v,  2,                dod_hex);
        push(imap, index, v,  3,                dod_hex);
        break;
      case  4:
        push(imap, index, v,  3,                dod_hex);
        break;
      case  5:
        push(imap, index, v,  4,                dod_hex);
        break;
      case  6:
        push(imap, index, v,  4,                hex_squ);
        push(imap, index, v,  6,                dod_squ);
        push(imap, index, v, n * steps_x_ +  3, hex_squ);
        push(imap, index, v, n * steps_x_ +  5, dod_squ);
        break;
      case  7:
        push(imap, index, v,  7,                dod_squ);
        push(imap, index, v,  6,                dod_squ);
        push(imap, index, v,  5,                hex_squ);
        push(imap, index, v,  4,                hex_squ);
        break;
      case  8:
        push(imap, index, v,  5,                hex_squ);
        push(imap, index, v,  8,                dod_squ);
        push(imap, index, v, 16,                hex_squ);
        break;
      case  9:
        push(imap, index, v,  5,                hex_squ);
        push(imap, index, v,  8,                dod_squ);
        push(imap, index, v, n * steps_x_ +  4, hex_squ);
        break;
      case  10:
        push(imap, index, v,  9,                dod_squ);
        push(imap, index, v,  6,                hex_squ);
        push(imap, index, v,  5,                hex_squ);
        break;
      case  11:
        push(imap, index, v, 10,                dod_squ);
        push(imap, index, v,  6,                hex_squ);
        break;
    }
  }


  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::init_triangular_pattern()
  {
    E1Point p00 = (dh_ + dv_) / -2;
    E1Point p01 = p00 + dh_;
    E1Point p10 = E1Point(0, 0);
    E1Point p11 = p10 + dh_;
    E1Point p20 = p00 + dv_;
    E1Point p21 = p20 + dh_;

    pattern_.push_back(E1Shape::triangle(p10, p00, p01));
    pattern_.push_back(E1Shape::triangle(p10, p01, p11));
    pattern_.push_back(E1Shape::triangle(p10, p11, p21));
    pattern_.push_back(E1Shape::triangle(p10, p21, p20));
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::init_square_pattern()
  {
    E1Point base = (dh_ + dv_) / -2;

    pattern_.push_back(
      E1Shape::tetragon(
        base,
        base + dh_,
        base + dh_ + dv_,
        base +       dv_));
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::init_hexagonal_pattern()
  {
    E1Point base = E1Point(-dh_ / 3. - dv_ / 2.);
    E1VectorsVector xs = create_vector(dh_, 6, 8);
    E1VectorsVector ys = create_vector(dv_, 2, 4);
    E1PointsMatrix p = create_matrix(base, xs, ys);

    pattern_.push_back(E1Shape::hexagon(p[0][1], p[0][3], p[1][4],
                                        p[2][3], p[2][1], p[1][0]));
    pattern_.push_back(E1Shape::hexagon(p[1][4], p[1][6], p[2][7],
                                        p[3][6], p[3][4], p[2][3]));
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::init_snub_hexagonal_pattern()
  {
    E1Point base = E1Point((-9 * (dh_ + dv_)) / 14.);
    E1VectorsVector xs = create_vector(dh_, 14, 21);
    E1VectorsVector ys = create_vector(dv_, 14, 18);
    E1PointsMatrix p = create_matrix(base, xs, ys);

    for (int by = 0; by < 5; ++by)
      for (int bx = 0; bx < 3; ++bx)
      {
        if (by == 0 and bx == 0)
          continue;

        int x = 5 * bx + by;
        int y = 3 * by + bx;

        pattern_.push_back(E1Shape::hexagon (p[y + 1][x + 1], p[y + 1][x + 3], p[y + 2][x + 4],
                                             p[y + 3][x + 3], p[y + 3][x + 1], p[y + 2][x + 0]));
        pattern_.push_back(E1Shape::triangle(p[y + 0][x + 0], p[y + 0][x + 2], p[y + 1][x + 1]));
        pattern_.push_back(E1Shape::triangle(p[y + 1][x + 1], p[y + 0][x + 2], p[y + 1][x + 3]));
        pattern_.push_back(E1Shape::triangle(p[y + 0][x + 2], p[y + 0][x + 4], p[y + 1][x + 3]));
        pattern_.push_back(E1Shape::triangle(p[y + 1][x + 3], p[y + 0][x + 4], p[y + 1][x + 5]));
        pattern_.push_back(E1Shape::triangle(p[y + 1][x + 3], p[y + 1][x + 5], p[y + 2][x + 4]));
        pattern_.push_back(E1Shape::triangle(p[y + 2][x + 4], p[y + 1][x + 5], p[y + 2][x + 6]));
        pattern_.push_back(E1Shape::triangle(p[y + 2][x + 4], p[y + 2][x + 6], p[y + 3][x + 5]));
        pattern_.push_back(E1Shape::triangle(p[y + 3][x + 3], p[y + 2][x + 4], p[y + 3][x + 5]));
      }
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::init_reflected_snub_hexagonal_pattern()
  {
    E1Point base = E1Point((9 * (dh_ - dv_)) / 14.);
    E1VectorsVector xs = create_vector(-dh_, 14, 21);
    E1VectorsVector ys = create_vector( dv_, 14, 18);
    E1PointsMatrix p = create_matrix(base, xs, ys);

    for (int by = 0; by < 5; ++by)
      for (int bx = 0; bx < 3; ++bx)
      {
        if (by == 0 and bx == 0)
          continue;

        int x = 5 * bx + by;
        int y = 3 * by + bx;

        pattern_.push_back(E1Shape::hexagon (p[y + 1][x + 1], p[y + 2][x + 0], p[y + 3][x + 1],
                                             p[y + 3][x + 3], p[y + 2][x + 4], p[y + 1][x + 3]));
        pattern_.push_back(E1Shape::triangle(p[y + 0][x + 0], p[y + 1][x + 1], p[y + 0][x + 2]));
        pattern_.push_back(E1Shape::triangle(p[y + 1][x + 1], p[y + 1][x + 3], p[y + 0][x + 2]));
        pattern_.push_back(E1Shape::triangle(p[y + 0][x + 2], p[y + 1][x + 3], p[y + 0][x + 4]));
        pattern_.push_back(E1Shape::triangle(p[y + 1][x + 3], p[y + 1][x + 5], p[y + 0][x + 4]));
        pattern_.push_back(E1Shape::triangle(p[y + 1][x + 3], p[y + 2][x + 4], p[y + 1][x + 5]));
        pattern_.push_back(E1Shape::triangle(p[y + 2][x + 4], p[y + 2][x + 6], p[y + 1][x + 5]));
        pattern_.push_back(E1Shape::triangle(p[y + 2][x + 4], p[y + 3][x + 5], p[y + 2][x + 6]));
        pattern_.push_back(E1Shape::triangle(p[y + 3][x + 3], p[y + 3][x + 5], p[y + 2][x + 4]));
      }
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::init_tri_hexagonal_pattern()
  {
    E1Point base = E1Point(-dh_ / 2. - dv_ / 4.);
    E1VectorsVector xs = create_vector(dh_, 4, 8);
    E1VectorsVector ys = create_vector(dv_, 4, 5);
    E1PointsMatrix p = create_matrix(base, xs, ys);

    pattern_.push_back(E1Shape::hexagon (p[0][1], p[0][3], p[1][4],
                                         p[2][3], p[2][1], p[1][0]));
    pattern_.push_back(E1Shape::hexagon (p[2][3], p[2][5], p[3][6],
                                         p[4][5], p[4][3], p[3][2]));
    pattern_.push_back(E1Shape::triangle(p[0][3], p[0][5], p[1][4]));
    pattern_.push_back(E1Shape::triangle(p[1][4], p[2][3], p[2][5]));
    pattern_.push_back(E1Shape::triangle(p[2][5], p[2][7], p[3][6]));
    pattern_.push_back(E1Shape::triangle(p[3][6], p[4][5], p[4][7]));
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::init_elongated_triangular_pattern()
  {
    Real vden = root_3() + 2;
    E1Point base = E1Point(-dh_ / 2. - dv_ / 2.);
    E1VectorsVector xs = create_vector(dh_, 2, 4);
    E1VectorsVector ys(5);

    ys[0] = E1Vector();
    ys[1] = E1Vector((dv_ * (1               )) / vden);
    ys[2] = E1Vector((dv_ * (1 + root_3() / 2)) / vden);
    ys[3] = E1Vector((dv_ * (2 + root_3() / 2)) / vden);
    ys[4] = dv_;

    E1PointsMatrix p = create_matrix(base, xs, ys);

    pattern_.push_back(E1Shape::tetragon(p[0][0], p[0][2], p[1][2], p[1][0]));
    pattern_.push_back(E1Shape::tetragon(p[2][1], p[2][3], p[3][3], p[3][1]));

    pattern_.push_back(E1Shape::triangle(p[1][0], p[1][2], p[2][1]));
    pattern_.push_back(E1Shape::triangle(p[1][2], p[2][3], p[2][1]));

    pattern_.push_back(E1Shape::triangle(p[4][0], p[3][1], p[4][2]));
    pattern_.push_back(E1Shape::triangle(p[4][2], p[3][1], p[3][3]));
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::init_snub_square_pattern()
  {
    Real den = root_3() + 1;
    E1Point base = E1Point(((root_3_div_2() + 1) * (dh_ + dv_)) / -den);
    E1PointsMatrix p(9, E1PointsVector(9));

    for (int y = 0; y < 9; ++y)
      for (int x = 0; x < 9; ++x)
      {
        RVector rh = ((x % 3 + x / 3) / 2. + (x / 3) * root_3_div_2()) * dh_ / den;
        RVector rv = ((y % 3 + y / 3) / 2. + (y / 3) * root_3_div_2()) * dv_ / den;

        p[y][x] = base + E1Vector(rh + rv);
      }

    pattern_.push_back(E1Shape::tetragon(p[1][2], p[2][4], p[4][3], p[3][1]));
    pattern_.push_back(E1Shape::triangle(p[1][0], p[1][2], p[3][1]));
    pattern_.push_back(E1Shape::triangle(p[4][5], p[4][3], p[2][4]));

    pattern_.push_back(E1Shape::tetragon(p[4][5], p[5][7], p[7][6], p[6][4]));
    pattern_.push_back(E1Shape::triangle(p[4][3], p[4][5], p[6][4]));
    pattern_.push_back(E1Shape::triangle(p[7][8], p[7][6], p[5][7]));

    pattern_.push_back(E1Shape::tetragon(p[2][4], p[1][6], p[3][7], p[4][5]));
    pattern_.push_back(E1Shape::triangle(p[0][4], p[1][6], p[2][4]));
    pattern_.push_back(E1Shape::triangle(p[4][5], p[3][7], p[5][7]));

    pattern_.push_back(E1Shape::tetragon(p[5][1], p[4][3], p[6][4], p[7][2]));
    pattern_.push_back(E1Shape::triangle(p[3][1], p[4][3], p[5][1]));
    pattern_.push_back(E1Shape::triangle(p[7][2], p[6][4], p[8][4]));
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::init_rhombitrihexagonal_pattern()
  {
    Real hden = root_3() + 1;
    Real vden = root_3() + 3;
    E1Point base = E1Point(
      (root_3() / 2.    ) * dh_ / -hden +
      (root_3() / 2. + 1) * dv_ / -vden);

    E1VectorsVector xs(10);
    E1VectorsVector ys(12);

    ys[ 0] = E1Vector();
    ys[ 1] = E1Vector((dv_ * (1               ) / 2.) / vden);
    ys[ 2] = E1Vector((dv_ * (0 +     root_3()) / 2.) / vden);
    ys[ 3] = E1Vector((dv_ * (1 +     root_3()) / 2.) / vden);
    ys[ 4] = E1Vector((dv_ * (3 +     root_3()) / 2.) / vden);
    ys[ 5] = E1Vector((dv_ * (4 +     root_3()) / 2.) / vden);
    ys[ 6] = E1Vector((dv_ * (3 + 2 * root_3()) / 2.) / vden);
    ys[ 7] = E1Vector((dv_ * (4 + 2 * root_3()) / 2.) / vden);
    ys[ 8] = dv_;
    ys[ 9] = dv_ + ys[1];
    ys[10] = dv_ + ys[2];
    ys[11] = dv_ + ys[3];

    xs[0] = E1Vector();
    xs[1] = E1Vector((dh_ * (-1 +     root_3()) / 2.) / hden);
    xs[2] = E1Vector((dh_ * ( 0 +     root_3()) / 2.) / hden);
    xs[3] = E1Vector((dh_ * ( 1 +     root_3()) / 2.) / hden);
    xs[4] = E1Vector((dh_ * ( 0 + 2 * root_3()) / 2.) / hden);
    xs[5] = E1Vector((dh_ * ( 1 + 2 * root_3()) / 2.) / hden);
    xs[6] = dh_;
    xs[7] = dh_ + xs[1];
    xs[8] = dh_ + xs[2];
    xs[9] = dh_ + xs[3];

    E1PointsMatrix p = create_matrix(base, xs, ys);

    pattern_.push_back(E1Shape::hexagon (p[2][2], p[3][4], p[4][4],
                                         p[5][2], p[4][0], p[3][0]));
    pattern_.push_back(E1Shape::hexagon (p[6][5], p[7][7], p[8][7],
                                         p[9][5], p[8][3], p[7][3]));

    pattern_.push_back(E1Shape::tetragon(p[ 0][3], p[ 1][5], p[ 3][4], p[ 2][2]));
    pattern_.push_back(E1Shape::tetragon(p[ 3][4], p[ 3][6], p[ 4][6], p[ 4][4]));
    pattern_.push_back(E1Shape::tetragon(p[ 4][4], p[ 6][5], p[ 7][3], p[ 5][2]));
    pattern_.push_back(E1Shape::tetragon(p[ 4][6], p[ 5][8], p[ 7][7], p[ 6][5]));
    pattern_.push_back(E1Shape::tetragon(p[ 7][7], p[ 7][9], p[ 8][9], p[ 8][7]));
    pattern_.push_back(E1Shape::tetragon(p[ 8][7], p[10][8], p[11][6], p[ 9][5]));

    pattern_.push_back(E1Shape::triangle(p[ 3][4], p[ 1][5], p[ 3][6]));
    pattern_.push_back(E1Shape::triangle(p[ 4][4], p[ 4][6], p[ 6][5]));
    pattern_.push_back(E1Shape::triangle(p[ 7][7], p[ 5][8], p[ 7][9]));
    pattern_.push_back(E1Shape::triangle(p[ 8][7], p[ 8][9], p[10][8]));
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::init_truncated_square_pattern()
  {
    Real den = root_2() + 2;
    E1Point base = E1Point(((root_2() + 1) * (dh_ + dv_)) / (-2 * den));

    E1VectorsVector xs(7);
    E1VectorsVector ys(6);

    ys[0] = E1Vector();
    ys[1] = E1Vector((dv_ * (0 + root_2_div_2())) / den);
    ys[2] = E1Vector((dv_ * (1 + root_2_div_2())) / den);
    ys[3] = E1Vector((dv_ * (1 + root_2()      )) / den);
    ys[4] = dv_;
    ys[5] = dv_ + ys[1];

    xs[0] = E1Vector();
    xs[1] = E1Vector((dh_ * (0 + root_2_div_2())) / den);
    xs[2] = E1Vector((dh_ * (1 + root_2_div_2())) / den);
    xs[3] = E1Vector((dh_ * (1 + root_2()      )) / den);
    xs[4] = dh_;
    xs[5] = dh_ + xs[1];
    xs[6] = dh_ + xs[2];

    E1PointsMatrix p = create_matrix(base, xs, ys);

    pattern_.push_back(E1Shape::octagon (p[0][1], p[0][2], p[1][3], p[2][3],
                                         p[3][2], p[3][1], p[2][0], p[1][0]));
    pattern_.push_back(E1Shape::octagon (p[2][3], p[2][4], p[3][5], p[4][5],
                                         p[5][4], p[5][3], p[4][2], p[3][2]));
    pattern_.push_back(E1Shape::tetragon(p[1][3], p[1][4], p[2][4], p[2][3]));
    pattern_.push_back(E1Shape::tetragon(p[3][5], p[3][6], p[4][6], p[4][5]));
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::init_truncated_hexagonal_pattern()
  {
    Real hden =     root_3() + 2;
    Real vden = 2 * root_3() + 3;
    E1Point base = E1Point(dh_ / -2 + hden * dv_ / (-2 * vden));

    E1VectorsVector xs(11);
    E1VectorsVector ys(10);

    ys[0] = E1Vector();
    ys[1] = E1Vector((dv_ * (1 + 0 * root_3()) / 2.) / vden);
    ys[2] = E1Vector((dv_ * (1 + 1 * root_3()) / 2.) / vden);
    ys[3] = E1Vector((dv_ * (3 + 1 * root_3()) / 2.) / vden);
    ys[4] = E1Vector((dv_ * (3 + 2 * root_3()) / 2.) / vden);
    ys[5] = E1Vector((dv_ * (4 + 2 * root_3()) / 2.) / vden);
    ys[6] = E1Vector((dv_ * (4 + 3 * root_3()) / 2.) / vden);
    ys[7] = E1Vector((dv_ * (6 + 3 * root_3()) / 2.) / vden);
    ys[8] = dv_;
    ys[9] = dv_ + ys[1];

    xs[ 0] = E1Vector();
    xs[ 1] = E1Vector((dh_ * (1 + 0 * root_3()) / 2.) / hden);
    xs[ 2] = E1Vector((dh_ * (1 + 1 * root_3()) / 2.) / hden);
    xs[ 3] = E1Vector((dh_ * (2 + 1 * root_3()) / 2.) / hden);
    xs[ 4] = E1Vector((dh_ * (3 + 1 * root_3()) / 2.) / hden);
    xs[ 5] = E1Vector((dh_ * (3 + 2 * root_3()) / 2.) / hden);
    xs[ 6] = dh_;
    xs[ 7] = dh_ + xs[1];
    xs[ 8] = dh_ + xs[2];
    xs[ 9] = dh_ + xs[3];
    xs[10] = dh_ + xs[4];

    E1PointsMatrix p = create_matrix(base, xs, ys);

    pattern_.push_back(E1Shape::dodecagon(p[0][2], p[0][4], p[1][5], p[2][6],
                                          p[3][6], p[4][5], p[5][4], p[5][2],
                                          p[4][1], p[3][0], p[2][0], p[1][1]));
    pattern_.push_back(E1Shape::dodecagon(p[4][5], p[4][7], p[5][8], p[6][9],
                                          p[7][9], p[8][8], p[9][7], p[9][5],
                                          p[8][4], p[7][3], p[6][3], p[5][4]));
    pattern_.push_back(E1Shape::triangle(p[1][5], p[1][ 7], p[2][6]));
    pattern_.push_back(E1Shape::triangle(p[3][6], p[4][ 7], p[4][5]));
    pattern_.push_back(E1Shape::triangle(p[5][8], p[5][10], p[6][9]));
    pattern_.push_back(E1Shape::triangle(p[7][9], p[8][10], p[8][8]));
  }

  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::init_truncated_trihexagonal_pattern()
  {
    Real hden = 3 * root_3() + 3;
    Real vden =     root_3() + 3;
    E1Point base = E1Point(
      (root_3_div_2() + 1) * dh_ / -hden +
      (root_3_div_2() + 1) * dv_ / -vden);

    E1VectorsVector xs(15);
    E1VectorsVector ys(14);

    ys[ 0] = E1Vector();
    ys[ 1] = E1Vector((dv_ * (1 + 0 * root_3()) / 2.) / vden);
    ys[ 2] = E1Vector((dv_ * (0 + 1 * root_3()) / 2.) / vden);
    ys[ 3] = E1Vector((dv_ * (1 + 1 * root_3()) / 2.) / vden);
    ys[ 4] = E1Vector((dv_ * (3 + 1 * root_3()) / 2.) / vden);
    ys[ 5] = E1Vector((dv_ * (4 + 1 * root_3()) / 2.) / vden);
    ys[ 6] = E1Vector((dv_ * (3 + 2 * root_3()) / 2.) / vden);
    ys[ 7] = E1Vector((dv_ * (4 + 2 * root_3()) / 2.) / vden);
    ys[ 8] = dv_;
    ys[ 9] = dv_ + ys[1];
    ys[10] = dv_ + ys[2];
    ys[11] = dv_ + ys[3];
    ys[12] = dv_ + ys[4];
    ys[13] = dv_ + ys[5];

    xs[ 0] = E1Vector();
    xs[ 1] = E1Vector((dh_ * (1 + 0 * root_3()) / 2.) / hden);
    xs[ 2] = E1Vector((dh_ * (1 + 1 * root_3()) / 2.) / hden);
    xs[ 3] = E1Vector((dh_ * (3 + 1 * root_3()) / 2.) / hden);
    xs[ 4] = E1Vector((dh_ * (3 + 2 * root_3()) / 2.) / hden);
    xs[ 5] = E1Vector((dh_ * (4 + 2 * root_3()) / 2.) / hden);
    xs[ 6] = E1Vector((dh_ * (3 + 3 * root_3()) / 2.) / hden);
    xs[ 7] = E1Vector((dh_ * (4 + 3 * root_3()) / 2.) / hden);
    xs[ 8] = E1Vector((dh_ * (4 + 4 * root_3()) / 2.) / hden);
    xs[ 9] = E1Vector((dh_ * (6 + 4 * root_3()) / 2.) / hden);
    xs[10] = E1Vector((dh_ * (6 + 5 * root_3()) / 2.) / hden);
    xs[11] = E1Vector((dh_ * (7 + 5 * root_3()) / 2.) / hden);
    xs[12] = dh_;
    xs[13] = dh_ + xs[1];
    xs[14] = dh_ + xs[2];

    E1PointsMatrix p = create_matrix(base, xs, ys);

    pattern_.push_back(E1Shape::dodecagon(p[0x0][0x2], p[0x0][0x3], p[0x1][0x4], p[0x3][0x5],
                                          p[0x4][0x5], p[0x6][0x4], p[0x7][0x3], p[0x7][0x2],
                                          p[0x6][0x1], p[0x4][0x0], p[0x3][0x0], p[0x1][0x1]));
    pattern_.push_back(E1Shape::dodecagon(p[0x4][0x8], p[0x4][0x9], p[0x5][0xa], p[0x7][0xb],
                                          p[0x8][0xb], p[0xa][0xa], p[0xb][0x9], p[0xb][0x8],
                                          p[0xa][0x7], p[0x8][0x6], p[0x7][0x6], p[0x5][0x7]));

    pattern_.push_back(E1Shape::hexagon  (p[0x3][0x5], p[0x2][0x7], p[0x3][0x8],
                                          p[0x4][0x8], p[0x5][0x7], p[0x4][0x5]));
    pattern_.push_back(E1Shape::hexagon  (p[0x7][0x3], p[0x6][0x4], p[0x7][0x6],
                                          p[0x8][0x6], p[0x9][0x4], p[0x8][0x3]));
    pattern_.push_back(E1Shape::hexagon  (p[0x7][0xb], p[0x6][0xd], p[0x7][0xe],
                                          p[0x8][0xe], p[0x9][0xd], p[0x8][0xb]));
    pattern_.push_back(E1Shape::hexagon  (p[0xb][0x9], p[0xa][0xa], p[0xb][0xc],
                                          p[0xc][0xc], p[0xd][0xa], p[0xc][0x9]));

    pattern_.push_back(E1Shape::tetragon (p[0x1][0x4], p[0x0][0x6], p[0x2][0x7], p[0x3][0x5]));
    pattern_.push_back(E1Shape::tetragon (p[0x4][0x5], p[0x5][0x7], p[0x7][0x6], p[0x6][0x4]));
    pattern_.push_back(E1Shape::tetragon (p[0x7][0x2], p[0x7][0x3], p[0x8][0x3], p[0x8][0x2]));
    pattern_.push_back(E1Shape::tetragon (p[0x5][0xa], p[0x4][0xc], p[0x6][0xd], p[0x7][0xb]));
    pattern_.push_back(E1Shape::tetragon (p[0x8][0xb], p[0x9][0xd], p[0xb][0xc], p[0xa][0xa]));
    pattern_.push_back(E1Shape::tetragon (p[0xb][0x8], p[0xb][0x9], p[0xc][0x9], p[0xc][0x8]));
  }


  template <typename T1, typename T2, typename I>
  inline void
  Tessellation<T1, T2, I>::init()
  {
    if (size_y_ <= 0)
      switch (type_)
      {
        BOOST_PP_SEQ_FOR_EACH(MMLM_case_dv, size_y_, MML_TILINGS)
      }

    // TODO: debug::tiling: check size_x > 0 and size_y > 0

    dh_ = E1Vector(size_x_ * std::cos(angle_), size_x_ * std::sin(angle_));
    dv_ = E1Vector((dh_.normal() * Real(size_y_)) / size_x_);
    angle_ = acos(dh_.x() / dh_.length()); // corrects angle

    E1Value tmpx = to<E1Value>(mml_mod(center_.x(), size_x_));
    E1Value tmpy = to<E1Value>(mml_mod(center_.y(), size_y_));
    center_ =
      E1Point(bounds_.center()) +
      E1Vector((tmpx * dh_) / to<Real>(size_x_) +
               (tmpy * dv_) / to<Real>(size_y_));

    E1Value dt = bound_box_.width() + bound_box_.height();
    steps_x_ = std::max(to<IndexType>(dt / size_x_ + 2), IndexType(3));
    steps_y_ = std::max(to<IndexType>(dt / size_y_ + 2), IndexType(3));

    base_ = center_
      - to<E1Value>(steps_x_ / 2) * dh_
      - to<E1Value>(steps_y_ / 2) * dv_;

    switch (type_)
    {
      BOOST_PP_SEQ_FOR_EACH(MMLM_case_pattern, _, MML_TILINGS)
    }

    max_ = steps_y_ * steps_x_ * pattern_.size();
  }


}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros undef

# undef MMLM_case_links
# undef MMLM_case_dv
# undef MMLM_case_pattern
# undef MMLM_ratio



#endif /* !MML_TILING_HXX_ */
