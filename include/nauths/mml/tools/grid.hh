//
// grid.hh for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_GRID_HH_
# define MML_GRID_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <list>
# include <vector>
# include <boost/function.hpp>
# include <boost/unordered_set.hpp>
# include "nauths/mml/shapes.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  template <typename S, typename T, typename F = boost::function1<Shape<T>, S const&> >
  class Grid
  {
    public:
      typedef Num Key;
      typedef S Value;
      typedef Value const* iterator;
      typedef Shape<Key> KeyShape;
      typedef Point<Key> KeyPoint;
      typedef Point<Key> KeyVector;
      typedef Rect<Key> KeyRect;

      Grid(F const& f, const KeyPoint& base, PrmNum size, PrmNum nx, PrmNum ny);
      Grid(F const& f, const KeyShape& base, PrmNum size);

      template <typename T2>
      iterator operator[](Point<T2> const&) const;
      template <typename T2>
      iterator operator[](Shape<T2> const&) const;

      template <typename T2>
      iterator find(Point<T2> const&) const;
      template <typename T2>
      iterator find(Shape<T2> const&) const;

      template <typename T2>
      std::vector<iterator> find_all(Point<T2> const&) const;
      template <typename T2>
      std::vector<iterator> find_all(Shape<T2> const&) const;

      std::pair<float, float> stats() const;

      void insert(Value const& v);
      void erase(Value const& v);

      void clear();

    private:
      typedef std::list<Value> Cell;
      typedef std::vector<Cell> Data;

      Cell* cell(const KeyPoint&);
      const Cell* cell(const KeyPoint&) const;

      template <typename T2>
      KeyPoint pos(Point<T2> const&) const;
      KeyRect rect(const KeyPoint&) const;

      void init();

      Data g_;
      F shape_;

      KeyPoint base_;
      Num size_;
      Num nx_;
      Num ny_;
  };

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/tools/grid.hxx"



#endif /* !MML_GRID_HH_ */
