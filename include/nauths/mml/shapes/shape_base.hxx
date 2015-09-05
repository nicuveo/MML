//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_SHAPE_BASE_HXX_
# define MML_SHAPE_BASE_HXX_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/shape_base.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Implementation

namespace mml
{

  namespace il
  {


    /// Checks whether this shape is the empty shape.
    template <typename E, typename T>
    inline bool
    ShapeBase<E, T>::empty() const
    {
      return static_cast<const ExactType*>(this)->type() == shape::EMPTY;
    }


    /// Duplicates the shape and translates it of the given vector values.
    template <typename E, typename T>
    inline typename ShapeBase<E, T>::ExactType
    ShapeBase<E, T>::moved_of(PrmValueType x, PrmValueType y) const
    {
      return moved_of(ExactVector(x, y));
    }

    /// Duplicates the shape and moves it to the given point.
    template <typename E, typename T>
    inline typename ShapeBase<E, T>::ExactType
    ShapeBase<E, T>::moved_to(PrmValueType x, PrmValueType y) const
    {
      return moved_to(ExactPoint(x, y));
    }


    /// Duplicates the shape and translates it of the given vector.
    template <typename E, typename T>
    inline typename ShapeBase<E, T>::ExactType
    ShapeBase<E, T>::moved_of(const ExactVector& v) const
    {
      ExactType res = *static_cast<const ExactType*>(this);
      res.move_of(v);
      return res;
    }

    /// Duplicates the shape and moves it to the given point.
    template <typename E, typename T>
    inline typename ShapeBase<E, T>::ExactType
    ShapeBase<E, T>::moved_to(const ExactPoint& p) const
    {
      ExactType res = *static_cast<const ExactType*>(this);
      res.move_to(p);
      return res;
    }


    /// Duplicates the shape and scales it of the given ratio.
    template <typename E, typename T>
    inline typename ShapeBase<E, T>::ExactType
    ShapeBase<E, T>::scaled(PrmReal r) const
    {
      ExactType res = *static_cast<const ExactType*>(this);
      res.scale(r);
      return res;
    }


    /// Translates the shape of the given vector (in-place).
    template <typename E, typename T>
    inline void
    ShapeBase<E, T>::move_of(PrmValueType x, PrmValueType y)
    {
      static_cast<ExactType*>(this)->move_of(ExactVector(x, y));
    }

    /// Moves the shape to the given point (in-place).
    template <typename E, typename T>
    inline void
    ShapeBase<E, T>::move_to(PrmValueType x, PrmValueType y)
    {
      static_cast<ExactType*>(this)->move_to(ExactPoint(x, y));
    }


    /// Returns the shape's exact type (CRTP).
    template <typename E, typename T, ShapeType Type>
    inline ShapeType
    TypedShapeBase<E, T, Type>::shape_type()
    {
      return Type;
    }

    /// Returns this shape's exact type (CRTP).
    template <typename E, typename T, ShapeType Type>
    inline ShapeType
    TypedShapeBase<E, T, Type>::type() const
    {
      return Type;
    }


  }

}



#endif /* !MML_SHAPE_BASE_HXX_ */
