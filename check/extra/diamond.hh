//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef TEST_DIAMOND_HH_
# define TEST_DIAMOND_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Predeclarations

namespace mml
{

  namespace il
  {

    template <typename T>
    class Diamond;

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

#include <nauths/mml/shapes/shape_base.hh>



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  namespace il
  {

    template <typename T>
    class Diamond : public TypedShapeBase<Diamond<T>, T, shape::DIAMOND>
    {
      public:
        // types

        typedef ShapeBase<Diamond<T>, T> ExactShapeBase;
        typedef typename ExactShapeBase::ValueType    ValueType;
        typedef typename ExactShapeBase::PrmValueType PrmValueType;
        typedef typename ExactShapeBase::ExactVector  ExactVector;
        typedef typename ExactShapeBase::ExactPoint   ExactPoint;
        typedef typename ExactShapeBase::ExactRect    ExactRect;


        // constructors

        Diamond() throw()
        {
        }

        Diamond(PrmValueType xradius, PrmValueType yradius) throw()
          : xradius_(xradius), yradius_(yradius)
        {
        }

        Diamond(const ExactPoint& center, PrmValueType xradius, PrmValueType yradius) throw()
          : center_(center), xradius_(xradius), yradius_(yradius)
        {
        }


        // accessors

        ExactPoint center() const
        {
          return center_;
        }

        PrmValueType x_radius() const
        {
          return xradius_;
        }

        PrmValueType y_radius() const
        {
          return yradius_;
        }


        // state

        bool valid() const
        {
          return gt(xradius_, ValueType(0)) and gt(yradius_, ValueType(0));
        }


        // geometry

        ExactRect bounding_rect() const
        {
          return ExactRect::absolute(-xradius_, -yradius_, xradius_, yradius_).moved_of(center_);
        }

        Real perimeter() const
        {
          return 4 * std::sqrt(xradius_ * xradius_ + yradius_ * yradius_);
        }

        Real area() const
        {
          return 2 * xradius_ * yradius_;
        }


        // in-place modifiers

        using ExactShapeBase::move_of;
        using ExactShapeBase::move_to;

        void move_of(const ExactVector& v)
        {
          center_ += v;
        }

        void move_to(const ExactPoint& p)
        {
          center_ = p;
        }

        void scale(PrmReal s)
        {
          xradius_ *= s;
          yradius_ *= s;
        }


      protected:
        // data

        ExactPoint center_;
        ValueType xradius_;
        ValueType yradius_;
    };

  }

}




#endif /* !TEST_DIAMOND_HH_ */
