//
// Copyright Antoine Leblanc 2010 - 2013
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


    template <typename E, typename T>
    inline bool
    ShapeBase<E, T>::empty() const
    {
      return static_cast<const ExactType*>(this)->type() == shape::EMPTY;
    }


    template <typename E, typename T>
    inline typename ShapeBase<E, T>::ExactType
    ShapeBase<E, T>::moved_of(PrmValueType x, PrmValueType y) const
    {
      return moved_of(ExactVector(x, y));
    }

    template <typename E, typename T>
    inline typename ShapeBase<E, T>::ExactType
    ShapeBase<E, T>::moved_to(PrmValueType x, PrmValueType y) const
    {
      return moved_to(ExactPoint(x, y));
    }


    template <typename E, typename T>
    inline typename ShapeBase<E, T>::ExactType
    ShapeBase<E, T>::moved_of(const ExactVector& v) const
    {
      ExactType res = *static_cast<const ExactType*>(this);
      res.move_of(v);
      return res;
    }

    template <typename E, typename T>
    inline typename ShapeBase<E, T>::ExactType
    ShapeBase<E, T>::moved_to(const ExactPoint& p) const
    {
      ExactType res = *static_cast<const ExactType*>(this);
      res.move_to(p);
      return res;
    }


    template <typename E, typename T>
    inline typename ShapeBase<E, T>::ExactType
    ShapeBase<E, T>::scaled(PrmReal r) const
    {
      ExactType res = *static_cast<const ExactType*>(this);
      res.scale(r);
      return res;
    }


    template <typename E, typename T>
    inline void
    ShapeBase<E, T>::move_of(PrmValueType x, PrmValueType y)
    {
      static_cast<ExactType*>(this)->move_of(ExactVector(x, y));
    }

    template <typename E, typename T>
    inline void
    ShapeBase<E, T>::move_to(PrmValueType x, PrmValueType y)
    {
      static_cast<ExactType*>(this)->move_to(ExactPoint(x, y));
    }


    template <typename E, typename T, ShapeType Type>
    inline ShapeType
    TypedShapeBase<E, T, Type>::shape_type()
    {
      return Type;
    }

    template <typename E, typename T, ShapeType Type>
    inline ShapeType
    TypedShapeBase<E, T, Type>::type() const
    {
      return Type;
    }


  }

}



#endif /* !MML_SHAPE_BASE_HXX_ */
