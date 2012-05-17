//
// tiling.hh for mml
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef MML_TILING_HH_
# define MML_TILING_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/iterator/iterator_facade.hpp>
# include "mml/shapes.hh"
# include "mml/algos.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Macros

// tiling list
//   this is a BOOST_PP_SEQ of tilings
//   it is used to generate redundant tiling code

# define MML_TILINGS                                           \
  ((TRIANGULAR,                triangular))                    \
  ((SQUARE,                    square))                        \
  ((HEXAGONAL,                 hexagonal))                     \
  ((SNUB_HEXAGONAL,            snub_hexagonal))                \
  ((REFLECTED_SNUB_HEXAGONAL,  reflected_snub_hexagonal))      \
  ((TRI_HEXAGONAL,             tri_hexagonal))                 \
  ((ELONGATED_TRIANGULAR,      elongated_triangular))          \
  ((SNUB_SQUARE,               snub_square))                   \
  ((RHOMBITRIHEXAGONAL,        rhombitrihexagonal))            \
  ((TRUNCATED_SQUARE,          truncated_square))              \
  ((TRUNCATED_HEXAGONAL,       truncated_hexagonal))           \
  ((TRUNCATED_TRIHEXAGONAL,    truncated_trihexagonal))        \

# define MML_TILING_NAME(S) BOOST_PP_TUPLE_ELEM(2, 0, S)
# define MML_TILING_name(S) BOOST_PP_TUPLE_ELEM(2, 1, S)



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros

# define MMLM_enum(_1, _2, S) MML_TILING_NAME(S)

# define MMLM_pattern(_1, _2, S)                                         \
  void BOOST_PP_CAT(BOOST_PP_CAT(init_, MML_TILING_name(S)),             \
                    _pattern());
# define MMLM_links(_1, _2, S)                                           \
  void BOOST_PP_CAT(MML_TILING_name(S), _links)(std::vector<IndexType>*, \
                                                IndexType index) const;
# define MMLM_dv(_1, _2, S)                                              \
  E1Value BOOST_PP_CAT(MML_TILING_name(S), _dv()) const;



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{



  namespace tiling
  {

    enum Type
    {
      BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(MMLM_enum, _, MML_TILINGS))
    };

  }

  typedef tiling::Type TilingType;


  // Tessellation
  //   this class describes a tessellation
  //   T1 => the T type of generated shapes, see shape.hh
  //   T2 => the T type of the enclosing shape, idem
  //   I  => the type of indexes used internally
  //         the default (Num [int]) should be large enough for most
  //         tesselations

  template <typename T1, typename T2 = T1, typename I = Num>
  class Tessellation
  {
    public:
      // typedefs

      typedef I IndexType;
      typedef TOOLS_TPL_PRM(IndexType) IndexPrm;
      typedef TOOLS_TPL_REF(IndexType) IndexRef;
      typedef T1 E1Value;
      typedef TOOLS_TPL_PRM(E1Value) E1Prm;
      typedef Point<T1> E1Point;
      typedef Point<T1> E1Vector;
      typedef Shape<T1> E1Shape;
      typedef Rect<T2>  E2Rect;
      typedef Shape<T2> E2Shape;
      typedef Point<Real> RVector;


      // internal iterator type

      class iterator : public boost::iterator_facade<
        iterator, E1Shape, boost::forward_traversal_tag, const E1Shape&>
      {
        public:
          iterator();

          IndexType index() const;
          const std::vector<IndexType>& links() const;

        private:
          friend class boost::iterator_core_access;
          friend class Tessellation;

          iterator(const Tessellation* t, IndexPrm index, bool links, bool strict);

          const E1Shape& dereference() const;
          bool equal(const iterator&) const;
          void increment();
          void compute();

          bool get_l_;
          bool strict_;
          E1Shape current_;
          IndexType index_;
          const Tessellation* tess_;
          std::vector<IndexType> links_;
      };


      // constructors

      Tessellation(TilingType t, const E2Shape& s, E1Prm size_x, PrmReal angle = 0);
      Tessellation(TilingType t, const E2Shape& s, E1Prm size_x, E1Prm size_y, PrmReal angle = 0);
      Tessellation(TilingType t, const E2Shape& s, E1Prm ox, E1Prm oy, E1Prm size_x, PrmReal angle = 0);
      Tessellation(TilingType t, const E2Shape& s, E1Prm ox, E1Prm oy, E1Prm size_x, E1Prm size_y, PrmReal angle = 0);
      Tessellation(TilingType t, const E2Shape& s, const E1Point& offset, E1Prm size_x, PrmReal angle = 0);
      Tessellation(TilingType t, const E2Shape& s, const E1Point& offset, E1Prm size_x, E1Prm size_y, PrmReal angle = 0);


      // accessors

      const std::vector<E1Shape>& pattern() const;
      const E2Shape& bounds() const;
      const E1Point& center() const;
      const E1Vector& dh() const;
      const E1Vector& dv() const;
      TilingType type() const;
      Real angle() const;


      // shapes access
      //   shape computaton is done lazily via an iterator interface
      //   one can use begin/end or the "shapes" accessor to iterate over the
      //   shapes of the tesselation
      //   links  => also generate shape links ("edges")
      //   strict => if true, only return shapes included in the bouding shape
      //             if false, only return shapes that overlap the bouding shape

      std::pair<iterator, iterator> shapes(bool strict, bool links = false) const;
      iterator begin(bool strict, bool links = false) const;
      iterator end() const;


    private:
      // internal helper types
      //   PointsVector is used to generate a set of evenly distributed points
      //   PointsMatrix is used to generate a grid of points, made from
      //     * a x points vector
      //     * a y points vector

      typedef std::vector<E1Point> E1PointsVector;
      typedef std::vector<E1Vector> E1VectorsVector;
      typedef std::vector<E1PointsVector> E1PointsMatrix;

      static void push(std::vector<IndexType>* v, IndexType index, IndexType delta);
      static E1PointsVector create_vector(const E1Vector& ref, PrmNum dem, PrmNum size);
      static E1PointsMatrix create_matrix(const E1Point& p0,
                                          const E1PointsVector& xs,
                                          const E1PointsVector& ys);


      // shape retrieval
      //   this method is only accessible to shape iterator
      //   it retrieves the shape of index i, with i being the first valid
      //   index greater or equal to the "index" parameter
      //   The index parameter is increased accordingly.

      E1Shape get(IndexRef index, std::vector<IndexType>* links, bool strict) const;


      // dv computation
      //   dh (horz delta) gives the distance between a pattern and its next
      //   occurence to the "right"; dv (vert delta) gives the distance to the
      //   next occurence to the "top".

      BOOST_PP_SEQ_FOR_EACH(MMLM_dv, _, MML_TILINGS)


      // links computation
      //   those methods compute the edges (here called "links") between
      //   a shape and those before it (index-wise).

      BOOST_PP_SEQ_FOR_EACH(MMLM_links, _, MML_TILINGS)


      // pattern generation
      //   those methods generate the internal base pattern for each
      //   tesselation

      BOOST_PP_SEQ_FOR_EACH(MMLM_pattern, _, MML_TILINGS)


      // initialization

      void init();


      // data

      const TilingType type_;
      const E2Rect bound_box_;
      const E2Shape bounds_;

      E1Value size_x_;
      E1Value size_y_;
      Real angle_;
      E1Point base_;
      E1Point center_;
      IndexType steps_x_;
      IndexType steps_y_;
      IndexType max_;
      E1Vector dh_;
      E1Vector dv_;
      std::vector<E1Shape> pattern_;
  };

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "mml/tools/tiling.hxx"



#endif /* !MML_TILING_HH_ */
