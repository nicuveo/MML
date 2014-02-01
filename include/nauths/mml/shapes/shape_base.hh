//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_SHAPE_BASE_HH_
# define MML_SHAPE_BASE_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/mpl/logical.hpp>
# include <boost/type_traits.hpp>
# include "nauths/mml/types.hh"
# include "nauths/mml/shapes/shape_type.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Macros

# define MML_IS_SHAPE(T)                                       \
  boost::is_base_of<mml::il::ShapeCommonBase, T>

# define MML_ISNT_SHAPE(T)                                     \
  boost::mpl::not_< MML_IS_SHAPE(T) >



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros

# define MMLM_exact(_1, T, S)                                  \
  typedef MMLM_Name(S)<T> BOOST_PP_CAT(Exact, MMLM_Name(S));



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  namespace il
  {

    // ShapeCommonBase
    //   Non-template common base to all shapes, used as a flag to identify
    //   shapes, as for all shape S `boost::is_base_of<ShapeCommonBase, S>` is
    //   true. This is typically used with ̀boost::enable_if`.

    class ShapeCommonBase
    {
    };


    // ShapeBase
    //   Template base class for shapes; does typedefs and virtual method
    //   declarations. Those virtual methods are not used; in fact, by default,
    //   they aren't even declared, as the mml always manipulates exact types.

    template <typename E, typename T>
    class ShapeBase : public ShapeCommonBase
    {
      public:
        // types

        typedef T ValueType;
        typedef E ExactType;
        typedef TOOLS_TPL_PRM(ValueType) PrmValueType;
        typedef TOOLS_TPL_REF(ValueType) RefValueType;
        BOOST_PP_SEQ_FOR_EACH(MMLM_exact, T, MMLM_SHAPES)
        typedef Point<T>   ExactVector;
        typedef Shape<T>   ExactShape;


        // state

        bool empty() const;


        // modifiers

        ExactType moved_of(PrmValueType, PrmValueType) const;
        ExactType moved_to(PrmValueType, PrmValueType) const;
        ExactType moved_of(const ExactVector&) const;
        ExactType moved_to(const ExactPoint&) const;

        ExactType scaled(PrmReal) const;


        // in-place modifiers

        void move_of(PrmValueType, PrmValueType);
        void move_to(PrmValueType, PrmValueType);


# ifdef MML_STATIC_CHECKING

        // static checking: state

        virtual ShapeType type() const = 0;
        virtual bool valid() const = 0;


        // static checking: geometry

        virtual ExactRect bounding_rect() const = 0;
        virtual ExactPoint center() const = 0;
        virtual Real perimeter() const = 0;
        virtual Real area() const = 0;


        // static checking: in-place modifiers

        virtual void move_of(const ExactVector&) = 0;
        virtual void move_to(const ExactPoint&) = 0;

        virtual void scale(PrmReal) = 0;

# endif

    };


    // TypedShapeBase
    //   A simple "overlay" of ShapeBase, but with knowledge of the exact
    //   ShapeType (using CRTP).

    template <typename E, typename T, ShapeType Type>
    class TypedShapeBase : public ShapeBase<E, T>
    {
      public:
        static ShapeType shape_type();

        ShapeType type() const;
    };

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros undef

# undef MMLM_exact



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/shape_base.hxx"



#endif /* !MML_SHAPE_BASE_HH_ */
