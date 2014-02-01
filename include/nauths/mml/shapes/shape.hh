//
// Copyright Antoine Leblanc 2010 - 2013
// Distributed under the MIT license.
//
// http://nauths.fr
// http://github.com/nicuveo
// mailto://antoine.jp.leblanc@gmail.com
//

#ifndef MML_SHAPE_HH_
# define MML_SHAPE_HH_



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include <boost/assign.hpp>
# include "nauths/mml/shapes/shape_union.hh"



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros

# define MMLM_exact(S) BOOST_PP_CAT(Exact, MMLM_Name(S))
# define MMLM_exact_def(_, T, S) typedef typename T::MMLM_exact(S) MMLM_exact(S);
# define MMLM_extractor(_, D, S)                        \
  inline MMLM_exact(S) const& MMLM_name(S)() const      \
  {                                                     \
    /* TODO debug::shape: check valid type? */          \
    return boost::get<MMLM_exact(S)>(D);                \
  }                                                     \



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Declarations

namespace mml
{

  namespace il
  {

    template <typename T>
    class Shape : public ShapeBase<Shape<T>, T>
    {
      public:
        // types

        typedef ShapeBase<Shape<T>, T> ExactShapeBase;
        typedef typename ShapeUnion<T>::Type ExactShapeUnion;
        typedef typename ExactShapeBase::ValueType    ValueType;
        typedef typename ExactShapeBase::PrmValueType PrmValueType;
        typedef typename ExactShapeBase::RefValueType RefValueType;
        typedef typename ExactShapeBase::ExactVector  ExactVector;
        BOOST_PP_SEQ_FOR_EACH(MMLM_exact_def, ExactShapeBase, MMLM_SHAPES)


        // constructors

        template <typename S>
        Shape(S const& shape) throw();
        Shape(const Shape& shape) throw();
        Shape() throw();

        template <typename S>
        Shape(const Shape<S>& shape);


        // creators

        static ExactRect rect(const ExactPoint& p1, const ExactPoint& p2);
        static ExactRect rect(PrmValueType xmin, PrmValueType ymin, PrmValueType xmax, PrmValueType ymax);

        static ExactCircle circle(PrmValueType radius);
        static ExactCircle circle(PrmValueType x, PrmValueType y, PrmValueType radius);
        static ExactCircle circle(const ExactPoint& p, PrmValueType radius);

        static ExactPolygon polygon(typename ExactPolygon::ExactPoints const& ps);
        static ExactPolygon triangle  (const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2);
        static ExactPolygon tetragon  (const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                                       const ExactPoint& p3);
        static ExactPolygon pentagon  (const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                                       const ExactPoint& p3, const ExactPoint& p4);
        static ExactPolygon hexagon   (const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                                       const ExactPoint& p3, const ExactPoint& p4, const ExactPoint& p5);
        static ExactPolygon heptagon  (const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                                       const ExactPoint& p3, const ExactPoint& p4, const ExactPoint& p5,
                                       const ExactPoint& p6);
        static ExactPolygon octagon   (const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                                       const ExactPoint& p3, const ExactPoint& p4, const ExactPoint& p5,
                                       const ExactPoint& p6, const ExactPoint& p7);
        static ExactPolygon nonagon   (const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                                       const ExactPoint& p3, const ExactPoint& p4, const ExactPoint& p5,
                                       const ExactPoint& p6, const ExactPoint& p7, const ExactPoint& p8);
        static ExactPolygon decagon   (const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                                       const ExactPoint& p3, const ExactPoint& p4, const ExactPoint& p5,
                                       const ExactPoint& p6, const ExactPoint& p7, const ExactPoint& p8,
                                       const ExactPoint& p9);
        static ExactPolygon hendecagon(const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                                       const ExactPoint& p3, const ExactPoint& p4, const ExactPoint& p5,
                                       const ExactPoint& p6, const ExactPoint& p7, const ExactPoint& p8,
                                       const ExactPoint& p9, const ExactPoint& pa);
        static ExactPolygon dodecagon (const ExactPoint& p0, const ExactPoint& p1, const ExactPoint& p2,
                                       const ExactPoint& p3, const ExactPoint& p4, const ExactPoint& p5,
                                       const ExactPoint& p6, const ExactPoint& p7, const ExactPoint& p8,
                                       const ExactPoint& p9, const ExactPoint& pa, const ExactPoint& pb);

        static ExactPolygon square(PrmValueType h_side, PrmReal rad_angle = 0);
        static ExactPolygon square(PrmValueType x, PrmValueType y,
                                   PrmValueType h_side, PrmReal rad_angle = 0);
        static ExactPolygon square(const ExactPoint& p,
                                   PrmValueType h_side, PrmReal rad_angle = 0);

        static ExactPolygon reg_polygon(PrmValueType radius, PrmNum points, PrmReal rad_angle = 0);
        static ExactPolygon reg_polygon(PrmValueType x, PrmValueType y,
                                        PrmValueType radius, PrmNum points, PrmReal rad_angle = 0);
        static ExactPolygon reg_polygon(const ExactPoint& p,
                                        PrmValueType radius, PrmNum points, PrmReal rad_angle = 0);

        static ExactPolygon equilateral_triangle(PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon equilateral_triangle(PrmValueType x, PrmValueType y,
                                                 PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon equilateral_triangle(const ExactPoint& p,
                                                 PrmValueType radius, PrmReal rad_angle = 0);

        static ExactPolygon reg_pentagon(PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_pentagon(PrmValueType x, PrmValueType y,
                                         PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_pentagon(const ExactPoint& p,
                                         PrmValueType radius, PrmReal rad_angle = 0);

        static ExactPolygon reg_hexagon(PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_hexagon(PrmValueType x, PrmValueType y,
                                        PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_hexagon(const ExactPoint& p,
                                        PrmValueType radius, PrmReal rad_angle = 0);

        static ExactPolygon reg_heptagon(PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_heptagon(PrmValueType x, PrmValueType y,
                                         PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_heptagon(const ExactPoint& p,
                                         PrmValueType radius, PrmReal rad_angle = 0);

        static ExactPolygon reg_octagon(PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_octagon(PrmValueType x, PrmValueType y,
                                        PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_octagon(const ExactPoint& p,
                                        PrmValueType radius, PrmReal rad_angle = 0);

        static ExactPolygon reg_nonagon(PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_nonagon(PrmValueType x, PrmValueType y,
                                        PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_nonagon(const ExactPoint& p,
                                        PrmValueType radius, PrmReal rad_angle = 0);

        static ExactPolygon reg_decagon(PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_decagon(PrmValueType x, PrmValueType y,
                                        PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_decagon(const ExactPoint& p,
                                        PrmValueType radius, PrmReal rad_angle = 0);

        static ExactPolygon reg_hendecagon(PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_hendecagon(PrmValueType x, PrmValueType y,
                                           PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_hendecagon(const ExactPoint& p,
                                           PrmValueType radius, PrmReal rad_angle = 0);

        static ExactPolygon reg_dodecagon(PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_dodecagon(PrmValueType x, PrmValueType y,
                                          PrmValueType radius, PrmReal rad_angle = 0);
        static ExactPolygon reg_dodecagon(const ExactPoint& p,
                                          PrmValueType radius, PrmReal rad_angle = 0);


        // conversions

        operator bool() const;



        // accessors

        ShapeType type() const;
        BOOST_PP_SEQ_FOR_EACH(MMLM_extractor, data_, MMLM_SHAPES)


        // state

        bool valid() const;


        // geometry

        ExactRect bounding_rect() const;
        ExactPoint center() const;
        Real area() const;
        Real perimeter() const;

        // TODO dev::shapes: add "polygonize" methods(?)


        // modifiers

        template <typename F>
        typename F::result_type apply(F& visitor) const;
        template <typename F>
        typename F::result_type apply(F const& visitor) const;


        // in-place modifiers

        template <typename F>
        typename F::result_type apply(F& visitor);
        template <typename F>
        typename F::result_type apply(F const& visitor);

        using ExactShapeBase::move_of;
        using ExactShapeBase::move_to;
        void move_of(const ExactVector&);
        void move_to(const ExactPoint&);

        void scale(PrmReal);


      private:
        // data

        ExactShapeUnion data_;
    };


    // comparison operators

    template <typename T1, typename T2>
    bool operator==(const Shape<T1>& s1, const Shape<T2>& s2);
    template <typename T1, typename T2>
    bool operator!=(const Shape<T1>& s1, const Shape<T2>& s2);

  }


  // type extraction

  template <typename T>
  ShapeType type(const Shape<T>& s);

  template <typename T1, typename T2>
  ShapeType dual_type(const Shape<T1>& s1, const Shape<T2>& s2);

}



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Local macros undef

# undef MMLM_exact
# undef MMLM_exact_def
# undef MMLM_extractor



//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
// Includes

# include "nauths/mml/shapes/shape.hxx"



#endif /* !MML_SHAPE_HH_ */
