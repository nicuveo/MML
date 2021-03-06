//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_CIRCLE_HH_
# define MML_CIRCLE_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/shape_base.hh"
# include "nauths/mml/shapes/point.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  namespace il
  {

    /// A 2D circle.
    /// Being a shape, it is wrappable in a Shape instance.
    template <typename T>
    class Circle : public TypedShapeBase<Circle<T>, T, shape::CIRCLE>
    {
      public:
        // types

        typedef ShapeBase<Circle<T>, T> ExactShapeBase;
        typedef typename ExactShapeBase::ValueType    ValueType;
        typedef typename ExactShapeBase::PrmValueType PrmValueType;
        typedef typename ExactShapeBase::RefValueType RefValueType;
        typedef typename ExactShapeBase::ExactVector  ExactVector;
        typedef typename ExactShapeBase::ExactPoint   ExactPoint;
        typedef typename ExactShapeBase::ExactRect    ExactRect;
        typedef typename ExactShapeBase::ExactPolygon ExactPolygon;


        // constructors

        Circle() throw();
        explicit Circle(PrmValueType radius) throw();
        Circle(PrmValueType cx, PrmValueType cy, PrmValueType radius) throw();
        Circle(const ExactPoint& center, PrmValueType radius) throw();
        Circle(const Circle& c) throw();

        template <typename T2>
        Circle(const Circle<T2>&) throw();


        // accessors

        ExactPoint center() const;
        PrmValueType radius() const;


        // state

        bool valid() const;


        // geometry

        ExactPolygon polygonize(PrmNum points, PrmReal rad_angle = 0) const;

        ExactRect bounding_rect() const;
        Real perimeter() const;
        Real area() const;


        // mutators

        void set_center(const ExactPoint&);
        void set_radius(PrmValueType);


        // in-place modifiers

        using ExactShapeBase::move_of;
        using ExactShapeBase::move_to;
        void move_of(const ExactVector&);
        void move_to(const ExactPoint&);

        void scale(PrmReal);


      protected:
        // data

        ExactPoint center_;
        ValueType radius_;
    };


    // comparison operators

    template <typename T1, typename T2>
    bool operator==(const Circle<T1>& c1, const Circle<T2>& c2);
    template <typename T1, typename T2>
    bool operator!=(const Circle<T1>& c1, const Circle<T2>& c2);

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/circle.hxx"



#endif /* !MML_CIRCLE_HH_ */
