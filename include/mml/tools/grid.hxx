//
// grid.hxx for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_GRID_HXX_
# define MML_GRID_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "mml/algos.hh"
# include "mml/tools/grid.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Macros

# define MML_GRID_FOR_INTERNAL(tt, shape, type)         \
  const Rect<tt>& r = shape.bounding_rect();            \
  const KeyPoint& pmin = pos(r.min());                  \
  const KeyPoint& pmax = pos(r.max());                  \
  for (Num y = pmin.y(); y <= pmax.y(); ++y)            \
    for (Num x = pmin.x(); x <= pmax.x(); ++x)          \
      if (type c = cell(KeyPoint(x, y)))                \

# define MML_GRID_FILTER(cell, test, todo)      \
  mml_foreach (Value const& v, *cell)           \
  if (test)                                     \
    todo(&v);

# define MML_GRID_FOR(tt, shape)       MML_GRID_FOR_INTERNAL(tt, shape, Cell*)
# define MML_GRID_CONST_FOR(tt, shape) MML_GRID_FOR_INTERNAL(tt, shape, const Cell*)



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{


  template <typename S, typename T, typename F>
  Grid<S, T, F>::Grid(F const& f, const KeyPoint& base, PrmNum size, PrmNum nx, PrmNum ny)
    : shape_(f), base_(base), size_(size), nx_(nx), ny_(ny)
  {
    init();
  }

  template <typename S, typename T, typename F>
  Grid<S, T, F>::Grid(F const& f, const KeyShape& base, PrmNum size)
    : shape_(f), size_(size)
  {
    const KeyRect& r(base.bounding_rect());

    base_ = r.min();
    nx_ = r.width() / size + 1;
    ny_ = r.height() / size + 1;

    init();
  }


  template <typename S, typename T, typename F>
  template <typename T2>
  inline typename Grid<S, T, F>::iterator
  Grid<S, T, F>::operator[](const Point<T2>& p) const
  {
    return find(p);
  }

  template <typename S, typename T, typename F>
  template <typename T2>
  inline typename Grid<S, T, F>::iterator
  Grid<S, T, F>::operator[](const Shape<T2>& s) const
  {
    return find(s);
  }


  template <typename S, typename T, typename F>
  template <typename T2>
  inline typename Grid<S, T, F>::iterator
  Grid<S, T, F>::find(const Point<T2>& p) const
  {
    if (const Cell* c = cell(pos(p)))
    {
      MML_GRID_FILTER(c, contains(shape_(v), p), return);
    }
    return 0;
  }

  template <typename S, typename T, typename F>
  template <typename T2>
  inline typename Grid<S, T, F>::iterator
  Grid<S, T, F>::find(const Shape<T2>& s) const
  {
    MML_GRID_CONST_FOR(T2, s)
    {
      MML_GRID_FILTER(c, overlaps(shape_(v), s), return);
    }
    return 0;
  }


  template <typename S, typename T, typename F>
  template <typename T2>
  std::vector<typename Grid<S, T, F>::iterator>
  Grid<S, T, F>::find_all(const Point<T2>& p) const
  {
    std::vector<iterator> res;
    if (Cell* c = cell(pos(p)))
    {
      MML_GRID_FILTER(c, contains(shape_(v), p), res.push_back);
    }
    return res;
  }

  template <typename S, typename T, typename F>
  template <typename T2>
  std::vector<typename Grid<S, T, F>::iterator>
  Grid<S, T, F>::find_all(const Shape<T2>& s) const
  {
    std::vector<iterator> res;
    MML_GRID_CONST_FOR(T2, s)
    {
      MML_GRID_FILTER(c, overlaps(shape_(v), s), res.push_back);
    }
    return res;
  }


  template <typename S, typename T, typename F>
  std::pair<float, float>
  Grid<S, T, F>::stats() const
  {
    float mean = 0;
    float stdev = 0;

    for (Num y = 0; y < ny_; ++y)
      for (Num x = 0; x < nx_; ++x)
      {
        const Cell* c = cell(KeyPoint(x, y));
        size_t s = c->size();
        mean += s;
        stdev += s * s;
      }
    mean /= nx_ * ny_;
    stdev = sqrt(stdev / (nx_ * ny_) - mean * mean);

    return std::make_pair(mean, stdev);
  }


  template <typename S, typename T, typename F>
  void
  Grid<S, T, F>::insert(Value const& v)
  {
    const Shape<T>& s = shape_(v);
    MML_GRID_FOR(T, s)
      if (overlaps(s, rect(KeyPoint(x, y))))
        c->push_back(v);
  }

  template <typename S, typename T, typename F>
  void
  Grid<S, T, F>::erase(Value const& v)
  {
    const Shape<T>& s = shape_(v);
    MML_GRID_FOR(T, s)
      c->erase(v); // TODO: check me
  }


  template <typename S, typename T, typename F>
  void
  Grid<S, T, F>::clear()
  {
    g_.clear();
    init();
  }


  template <typename S, typename T, typename F>
  inline typename Grid<S, T, F>::Cell*
  Grid<S, T, F>::cell(const KeyPoint& p)
  {
    if (p.x() >= 0 and p.x() < nx_ and
        p.y() >= 0 and p.y() < ny_)
      return &g_[p.y() * nx_ + p.x()];
    return 0;
  }

  template <typename S, typename T, typename F>
  inline const typename Grid<S, T, F>::Cell*
  Grid<S, T, F>::cell(const KeyPoint& p) const
  {
    if (p.x() >= 0 and p.x() < nx_ and
        p.y() >= 0 and p.y() < ny_)
      return &g_[p.y() * nx_ + p.x()];
    return 0;
  }


  template <typename S, typename T, typename F>
  template <typename T2>
  inline typename Grid<S, T, F>::KeyPoint
  Grid<S, T, F>::pos(const Point<T2>& p) const
  {
    return KeyPoint((to<Num>(p.x()) - base_.x()) / size_,
                    (to<Num>(p.y()) - base_.y()) / size_);
  }

  template <typename S, typename T, typename F>
  inline typename Grid<S, T, F>::KeyRect
  Grid<S, T, F>::rect(const KeyPoint& p) const
  {
    return KeyRect(base_ + KeyVector((p.x() + 0) * size_, (p.y() + 0) * size_),
                   base_ + KeyVector((p.x() + 1) * size_, (p.y() + 1) * size_));
  }


  template <typename S, typename T, typename F>
  inline void
  Grid<S, T, F>::init()
  {
    assert(nx_ > 0);
    assert(ny_ > 0);
    assert(size_ > 0);
    g_.resize(nx_ * ny_);
  }


}



#endif /* !MML_GRID_HXX_ */
