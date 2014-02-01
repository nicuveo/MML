//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef SHAPE_UTILS_HH_
# define SHAPE_UTILS_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/shape_union.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  namespace il
  {

    MML_SHAPE_UNION_VISITOR(TypeFunc, ShapeType, return x.type());
    MML_SHAPE_UNION_VISITOR(ValidFunc,     bool, return x.valid());
    MML_SHAPE_UNION_VISITOR(PerimeterFunc, Real, return x.perimeter());
    MML_SHAPE_UNION_VISITOR(AreaFunc,      Real, return x.area());

    template <typename T>
    MML_SHAPE_UNION_VISITOR(BoundingRectFunc, T, return x.bounding_rect());
    template <typename T>
    MML_SHAPE_UNION_VISITOR(CenterFunc,       T, return x.center());

    template <typename T>
    MML_SHAPE_UNION_VISITOR_WARG(MoveOfFunc, void, T, x.move_of(arg_));
    template <typename T>
    MML_SHAPE_UNION_VISITOR_WARG(MoveToFunc, void, T, x.move_to(arg_));
    MML_SHAPE_UNION_VISITOR_WARG(ScaleFunc,  void, Real, x.scale(arg_));

  }

}




#endif /* !SHAPE_UTILS_HH_ */
