//
// Copyright Antoine Leblanc 2010 - 2014
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_POINT_HH_
# define MML_POINT_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/array.hpp>
# include "nauths/mml/lib/utils.hh"
# include "nauths/mml/shapes/shape_base.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  namespace il
  {

    // Point class

    template <typename T>
    class Point : public TypedShapeBase<Point<T>, T, shape::POINT>
    {
      public:
        // types

        typedef ShapeBase<Point<T>, T> ExactShapeBase;
        typedef typename ExactShapeBase::ValueType    ValueType;
        typedef typename ExactShapeBase::PrmValueType PrmValueType;
        typedef typename ExactShapeBase::RefValueType RefValueType;
        typedef typename ExactShapeBase::ExactVector  ExactVector;
        typedef typename ExactShapeBase::ExactPoint   ExactPoint;
        typedef typename ExactShapeBase::ExactRect    ExactRect;

        typedef boost::array<ValueType, 2> DataType;


        // constructors

        Point() throw();
        Point(PrmValueType x, PrmValueType y) throw();
        Point(const Point& p) throw();

        template <typename T2>
        Point(T2 const& x, T2 const& y);
        template <typename T2>
        Point(const Point<T2>& p2);


        // accessors

        DataType const& data() const;

        PrmValueType x() const;
        PrmValueType y() const;
        RefValueType rx();
        RefValueType ry();


        // access operators

        operator const DataType& () const;
        operator DataType& ();

        PrmValueType operator[](std::size_t i) const;
        RefValueType operator[](std::size_t i);


        // state

        bool valid() const;


        // geometry

        Real length() const;
        ValueType sqr_length() const;

        ExactRect bounding_rect() const;
        ExactPoint center() const;
        Real perimeter() const;
        Real area() const;


        // modifiers

        Point normalized() const;
        Point normal() const;


        // modification operators

        Point operator-() const;


        // in-place modifiers

        void normalize();

        using ExactShapeBase::move_of;
        using ExactShapeBase::move_to;
        void move_of(const ExactVector&);
        void move_to(const ExactPoint&);

        void scale(PrmReal);


        // in-place modification operators

        template <typename T2>
        Point& operator+=(const Point<T2>& p);
        template <typename T2>
        Point& operator-=(const Point<T2>& p);
        template <typename S>
        Point& operator*=(S const& s);
        template <typename S>
        Point& operator/=(S const& s);
        template <typename S>
        Point& operator%=(S const& s);


      private:
        // data

        DataType c_;
    };


    // C++11 only

    // template <typename T>
    // using Vector = Point<T>;


    // comparison operators

    template <typename T1, typename T2>
    bool operator==(const Point<T1>& p1, const Point<T2>& p2);
    template <typename T1, typename T2>
    bool operator!=(const Point<T1>& p1, const Point<T2>& p2);


    // basic operations

    template <typename T1, typename T2>
    Point<MML_RESULT(MML_ADD, T1, T2)>
    operator+(const Point<T1>& p1, const Point<T2>& p2);
    template <typename T1, typename T2>
    Point<MML_RESULT(MML_SUB, T1, T2)>
    operator-(const Point<T1>& p1, const Point<T2>& p2);
    template <typename T, typename S>
    MML_ENABLE_IF(MML_ISNT_SHAPE(S), Point<MML_RESULT(MML_MUL, T, S)>)
    operator*(const Point<T>& p, S const& s);
    template <typename T, typename S>
    MML_ENABLE_IF(MML_ISNT_SHAPE(S), Point<MML_RESULT(MML_MUL, T, S)>)
    operator*(S const& s, const Point<T>& p);
    template <typename T, typename S>
    MML_ENABLE_IF(MML_ISNT_SHAPE(S), Point<MML_RESULT(MML_DIV, T, S)>)
    operator/(const Point<T>& p, S const& s);
    template <typename T, typename S>
    MML_ENABLE_IF(MML_ISNT_SHAPE(S), Point<MML_RESULT(MML_MOD, T, S)>)
    operator%(const Point<T>& p, S const& s);


    // misc mathematical tools

    template <typename T1, typename T2>
    MML_RESULT(MML_MUL, T1, T2)
    operator*(const Point<T1>& p1, const Point<T2>& p2);
    template <typename T1, typename T2>
    MML_RESULT(MML_MUL, T1, T2)
    dot_product(const Point<T1>& p1, const Point<T2>& p2);

  }

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/point.hxx"



#endif /* !MML_POINT_HH_ */
