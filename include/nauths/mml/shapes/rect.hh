//
// Copyright Antoine Leblanc 2010 - 2015
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_RECT_HH_
# define MML_RECT_HH_



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

    template <typename T>
    class Rect : public TypedShapeBase<Rect<T>, T, shape::RECT>
    {
      public:
        // types

        typedef ShapeBase<Rect<T>, T> ExactShapeBase;
        typedef typename ExactShapeBase::ValueType    ValueType;
        typedef typename ExactShapeBase::PrmValueType PrmValueType;
        typedef typename ExactShapeBase::RefValueType RefValueType;
        typedef typename ExactShapeBase::ExactVector  ExactVector;
        typedef typename ExactShapeBase::ExactPoint   ExactPoint;
        typedef typename ExactShapeBase::ExactRect    ExactRect;


        // constructors

        Rect() throw();
        Rect(const ExactPoint& min, const ExactPoint& max) throw();
        Rect(PrmValueType xmin, PrmValueType ymin, PrmValueType xmax, PrmValueType ymax) throw();

        template <typename T2>
        Rect(const Rect<T2>&);

        static Rect absolute(const ExactPoint& min, const ExactPoint& max);
        static Rect absolute(PrmValueType xmin, PrmValueType ymin, PrmValueType xmax, PrmValueType ymax);
        static Rect relative(const ExactPoint& min, const ExactVector& delta);
        static Rect relative(PrmValueType xmin, PrmValueType ymin, PrmValueType dx , PrmValueType dy);


        // accessors

        const ExactPoint& min() const;
        const ExactPoint& max() const;

        PrmValueType x_min() const;
        PrmValueType x_max() const;
        PrmValueType y_min() const;
        PrmValueType y_max() const;


        // state

        bool valid() const;


        // geometry

        ExactVector delta() const;

        ValueType width() const;
        ValueType height() const;

        ExactRect bounding_rect() const;
        ExactPoint center() const;
        Real area() const;
        Real perimeter() const;


        // mutators

        void set_min(const ExactPoint&);
        void set_max(const ExactPoint&);
        void set_x_min(PrmValueType);
        void set_x_max(PrmValueType);
        void set_y_min(PrmValueType);
        void set_y_max(PrmValueType);


        // modifiers

        Rect expanded(PrmValueType) const;
        Rect expanded(PrmValueType, PrmValueType) const;
        Rect expanded(PrmValueType, PrmValueType, PrmValueType, PrmValueType) const;
        Rect expanded(const ExactPoint&) const;
        Rect expanded(const ExactRect&) const;
        Rect shrinked(PrmValueType) const;
        Rect shrinked(PrmValueType, PrmValueType) const;
        Rect shrinked(PrmValueType, PrmValueType, PrmValueType, PrmValueType) const;
        Rect shrinked(const ExactPoint&) const;
        Rect shrinked(const ExactRect&) const;


        // in-place modifiers

        using ExactShapeBase::move_of;
        using ExactShapeBase::move_to;
        void move_of(const ExactVector&);
        void move_to(const ExactPoint&);

        void resize_of(PrmValueType, PrmValueType);
        void resize_to(PrmValueType, PrmValueType);
        void resize_of(const ExactVector&);
        void resize_to(const ExactVector&);

        void scale(PrmReal);

        void expand(PrmValueType);
        void expand(PrmValueType, PrmValueType);
        void expand(PrmValueType, PrmValueType, PrmValueType, PrmValueType);
        void expand(const ExactPoint&);
        void expand(const ExactRect&);
        void shrink(PrmValueType);
        void shrink(PrmValueType, PrmValueType);
        void shrink(PrmValueType, PrmValueType, PrmValueType, PrmValueType);
        void shrink(const ExactPoint&);
        void shrink(const ExactRect&);


      private:
        // data

        ExactPoint min_;
        ExactPoint max_;
    };


    // comparison operators

    template <typename T1, typename T2>
    bool operator==(const Rect<T1>& r1, const Rect<T2>& r2);
    template <typename T1, typename T2>
    bool operator!=(const Rect<T1>& r1, const Rect<T2>& r2);

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/rect.hxx"



#endif /* !MML_RECT_HH_ */
