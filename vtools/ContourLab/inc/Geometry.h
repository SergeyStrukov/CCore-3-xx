/* Geometry.h */
//----------------------------------------------------------------------------------------
//
//  Project: ContourLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef Geometry_h
#define Geometry_h

#include <inc/Application.h>

namespace App {

/* concept ArgCursorType<R,A> */

template <NothrowCopyableType R,class A>
concept bool ArgCursorType = NullableType<R> && requires(R &obj,Meta::ToConst<R> &cobj)
 {
  { cobj.getLen() } -> ulen ;

  { *cobj } -> A ;

  ++obj;
 };

/* classes */

struct Geometry;

/* struct Geometry */

struct Geometry
 {
  // Real

  enum RealException
   {
    RealOk = 0,

    RealBlank,

    RealTooBig,
    RealTooSmall,
    RealOutOfDomain
   };

  friend const char * GetTextDesc(RealException rex);

  class Real
   {
     double val;

    private:

     static double Guard(double x);

     static void GuardDiv(double y);

    public:

     struct Bin
      {
       sint64 mantissa;
       sint16 exp;

       void print(PrinterType &out) const
        {
         Printf(out,"{#.h;,#;}",mantissa,exp);
        }
      };

     Real(double val_=0) : val(val_) {}

     Real(Bin);

     Real operator - () const { return -val; }

     friend Real operator + (Real a,Real b) { return Guard(a.val+b.val); }

     friend Real operator - (Real a,Real b) { return Guard(a.val-b.val); }

     friend Real operator * (Real a,Real b) { return Guard(a.val*b.val); }

     friend Real operator / (Real a,Real b) { GuardDiv(b.val); return Guard(a.val/b.val); }

     friend bool operator == (Real a,Real b) { return a.val==b.val; }

     friend bool operator != (Real a,Real b) { return a.val!=b.val; }

     friend bool operator < (Real a,Real b) { return a.val<b.val; }

     friend bool operator <= (Real a,Real b) { return a.val<=b.val; }

     friend bool operator > (Real a,Real b) { return a.val>b.val; }

     friend bool operator >= (Real a,Real b) { return a.val>=b.val; }

     static Real Pi() { return 3.1415926535897932384626433832; }

     static Real Abs(Real x) { return (x<0)?-x:x; }

     static Real Norm(Real x,Real y);

     static Real Arg(Real x,Real y);

     static Real Sin(Real x);

     static Real Cos(Real x);

     static Real ArcCos(Real x);

     static Real Sqrt(Real x);

     static Real Mod(Real x,Real y);

     static RealException BoundedDiv(Real x,Real y); // x/y in [0,1]

     static Real Pow(Real x,ulen deg);

     static Real Den(Real x,Real cap);

     static Real RoundMul(Real x,Real den);

     // map

     double map(int prec) const;

     Bin toBin() const;

     // print object

     struct PrintOptType
      {
       ulen width;
       ulen prec;
       IntAlign align;
       IntShowSign show_sign;

       static const ulen DefaultPrec = 6 ;

       void setDefault()
        {
         width=0;
         prec=DefaultPrec;
         align=IntAlignDefault;
         show_sign=IntShowSignDefault;
        }

       PrintOptType() { setDefault(); }

       PrintOptType(const char *ptr,const char *lim);

       //
       // [+][width=0][.prec=.6][l|L|r|R|i|I=R]
       //
      };

     struct ToStr : NoCopy
      {
        char int_buf[10];
        char fract_buf[10];

        StrLen int_part;
        StrLen fract_part;
        bool is_neg;
        bool is_pos;

       private:

        static char Digit(double d);

        static StrLen Format(PtrLen<char> buf,double val);

        static StrLen Format(PtrLen<char> buf,double val,ulen prec);

       public:

        ToStr(double val,ulen prec);

        bool isNeg() const { return is_neg; }

        bool isPos() const { return is_pos; }

        StrLen intPart() const { return int_part; }

        StrLen fractPart() const { return fract_part; }
      };

     void print(PrinterType &out,PrintOptType opt) const
      {
       ToStr temp(val,opt.prec);

       ulen extra=0;

       if( opt.width )
         {
          ulen len=0;

          if( temp.isNeg() )
            len++;
          else if( temp.isPos() && opt.show_sign==IntShowPlus )
            len++;

          len+=temp.intPart().len;

          if( +temp.fractPart() )
            {
             len++;

             len+=temp.fractPart().len;
            }

          extra=PosSub(opt.width,len);
         }

       if( extra && opt.align==IntAlignLeft ) out.put(' ',extra);

       if( temp.isNeg() )
         out.put('-');
       else if( temp.isPos() && opt.show_sign==IntShowPlus )
         out.put('+');

       if( extra && opt.align==IntAlignInternal ) out.put(' ',extra);

       Putobj(out,temp.intPart());

       if( +temp.fractPart() )
         {
          out.put('.');

          Putobj(out,temp.fractPart());
         }

       if( extra && opt.align==IntAlignRight ) out.put(' ',extra);
      }
   };

  // AssertValid

  template <class S>
  static void AssertValid(S s)
   {
    if( s.rex ) throw s.rex;
   }

  template <class ... SS>
  static void AssertValid(SS ... ss)
   {
    ( ... , AssertValid(ss) );
   }

  // Ratio

  struct Ratio
   {
    static const int TypeId = 1 ;

    static StrLen TypeName() { return "Ratio"_c ; }

    Real val;
    RealException rex;

    Ratio(RealException rex_=RealBlank) : rex(rex_) {}

    Ratio(Real val_) : val(val_),rex(RealOk) {}

    // print object

    void print(PrinterType &out) const
     {
      Printf(out,"#.3;",val);
     }
   };

  static Ratio Inv(Ratio a) { return 1/a.val; }

  static Ratio Neg(Ratio a) { return -a.val; }

  static Ratio Add(Ratio a,Ratio b) { return a.val+b.val; }

  static Ratio Sub(Ratio a,Ratio b) { return a.val-b.val; }

  static Ratio Mul(Ratio a,Ratio b) { return a.val*b.val; }

  static Ratio Div(Ratio a,Ratio b) { return a.val/b.val; }

  // Length

  struct Length
   {
    static const int TypeId = 2 ;

    static StrLen TypeName() { return "Length"_c ; }

    Real val;
    RealException rex;

    Length(RealException rex_=RealBlank) : rex(rex_) {}

    Length(Real val_) : val(val_),rex(RealOk) {}

    // print object

    void print(PrinterType &out) const
     {
      Printf(out,"#.3;",val);
     }
   };

  static Length Neg(Length a) { return -a.val; }

  static Length Add(Length a,Length b) { return a.val+b.val; }

  static Length Sub(Length a,Length b) { return a.val-b.val; }

  static Length Mul(Ratio mul,Length a) { return mul.val*a.val; }

  static Length Div(Length a,Ratio div) { return a.val/div.val; }

  static Ratio Div(Length a,Length b) { return a.val/b.val; }

  // Angle

  struct Angle
   {
    static const int TypeId = 3 ;

    static StrLen TypeName() { return "Angle"_c ; }

    Real val;
    RealException rex;

    Angle(RealException rex_=RealBlank) : rex(rex_) {}

    Angle(Real val_,Real Func(Real)=Mod) : val( Func(val_) ),rex(RealOk) {}

    Angle operator - () const { return {-val,Pos}; }

    friend Angle operator + (Angle a,Angle b) { return a.val+b.val; }

    friend Angle operator - (Angle a,Angle b) { return a.val-b.val; }

    friend Angle operator * (Ratio mul,Angle a) { return mul.val*a.val; }

    friend Angle operator / (Angle a,Ratio div) { return a.val/div.val; }

    static Angle Pi() { return {Real::Pi(),Scoped}; }

    static Angle ArcCos(Real t) { return {Real::ArcCos(t),Scoped}; }

    static Angle Arg(Real x,Real y) { return {Real::Arg(x,y),Pos}; }

    // mods

    static Real Scoped(Real a) { return a; }

    static Real Pos(Real a)
     {
      if( a <= -Real::Pi() ) return a+2*Real::Pi();

      return a;
     }

    static Real Mod(Real a) { return Pos( Real::Mod( a , 2*Real::Pi() ) ); }

    // print object

    void print(PrinterType &out) const
     {
      Printf(out,"#+.2;",val*(180/Real::Pi()));
     }
   };

  static Angle Pi() { return Angle::Pi(); }

  static Angle Neg(Angle a) { return -a; }

  static Angle Add(Angle a,Angle b) { return a+b; }

  static Angle Sub(Angle a,Angle b) { return a-b; }

  static Angle Mul(Ratio mul,Angle a) { return mul*a; }

  static Angle Div(Angle a,Ratio div) { return a/div; }

  // Point

  struct Point
   {
    static const int TypeId = 4 ;

    static StrLen TypeName() { return "Point"_c ; }

    Real x;
    Real y;
    RealException rex;

    Point(RealException rex_=RealBlank) noexcept : rex(rex_) {}

    Point(Real x_,Real y_) : x(x_),y(y_),rex(RealOk) {}

    friend Point operator + (Point a,Point b) { return {a.x+b.x,a.y+b.y}; }

    friend Point operator - (Point a,Point b) { return {a.x-b.x,a.y-b.y}; }

    friend Point operator * (Real mul,Point a) { return {mul*a.x,mul*a.y}; }

    friend Point operator / (Point a,Real div) { return {a.x/div,a.y/div}; }

    static Real Norm(Point p) { return Real::Norm(p.x,p.y); }

    static Point Ort(Point p) { return p/Norm(p); }

    static Point Orthogonal(Point p) { return {p.y,-p.x}; }

    static Real Prod(Point a,Point b) { return a.x*b.x+a.y*b.y; }

    static Angle Arg(Point p) { return Angle::Arg(p.x,-p.y); }

    static Point Rotate(Angle a,Point p)
     {
      Real Sin=Real::Sin(a.val);
      Real Cos=Real::Cos(a.val);

      return {Cos*p.x+Sin*p.y,Cos*p.y-Sin*p.x};
     }

    static Point Polar(Length r,Angle a)
     {
      Real Sin=Real::Sin(a.val);
      Real Cos=Real::Cos(a.val);

      return {Cos*r.val,-Sin*r.val};
     }

    // print object

    void print(PrinterType &out) const
     {
      Printf(out,"(#.3;,#.3;)",x,y);
     }
   };

  // Line

  struct Line
   {
    static const int TypeId = 5 ;

    static StrLen TypeName() { return "Line"_c ; }

    Point p;
    Point ort;
    RealException rex;

    Line(RealException rex_=RealBlank) : rex(rex_) {}

    Line(Point p_,Point dir) : p(p_),ort(Point::Ort(dir)),rex(RealOk) {}
   };

  // Circle

  struct Circle
   {
    static const int TypeId = 6 ;

    static StrLen TypeName() { return "Circle"_c ; }

    Point center;
    Length radius;
    RealException rex;

    Circle(RealException rex_=RealBlank) : rex(rex_) {}

    Circle(Point center_,Length radius_) : center(center_),radius(radius_),rex(RealOk) {}
   };

  // Couple

  struct Couple
   {
    static const int TypeId = 7 ;

    static StrLen TypeName() { return "Couple"_c ; }

    Point a;
    Point b;
    RealException rex;

    Couple(RealException rex_=RealBlank) : rex(rex_) {}

    Couple(Point a_,Point b_) : a(a_),b(b_),rex(RealOk) {}
   };

  // Dot

  struct Dot
   {
    Point point;
    bool break_flag = false ;
   };

  template <ArgCursorType<Point> Cur>
  struct PointBuilder
   {
    Cur cur;

    ulen getLen() const { return cur.getLen(); }

    PtrLen<Dot> operator () (Place<void> place) const
     {
      ulen len=cur.getLen();

      if( !len ) return Empty;

      Dot *base=place;

      for(Cur r=cur; +r ;++r,place+=sizeof (Dot)) new(place) Dot{*r};

      return Range(base,len);
     }
   };

  struct StepBuilder
   {
    PtrLen<const Point> cur;

    ulen getLen() const { return cur.len; }

    PtrLen<Dot> operator () (Place<void> place) const
     {
      if( !cur.len ) return Empty;

      Dot *base=place;

      auto r=cur;

      new(place) Dot{*r,true};

      for(++r,place+=sizeof (Dot); +r ;++r,place+=sizeof (Dot)) new(place) Dot{*r};

      return Range(base,cur.len);
     }
   };

  // Step

  struct Step
   {
    static const int TypeId = 8 ;

    static StrLen TypeName() { return "Step"_c ; }

    RefArray<Point> points;
    RealException rex;

    Step(RealException rex_=RealBlank) : rex(rex_) {}

    template <ArgCursorType<Point> Cur>
    struct PointBuilder
     {
      Cur cur;

      ulen getLen() const { return cur.getLen(); }

      PtrLen<Point> operator () (Place<void> place) const
       {
        ulen len=cur.getLen();

        if( !len ) return Empty;

        Point *base=place;

        for(Cur r=cur; +r ;++r,place+=sizeof (Point)) new(place) Point(*r);

        return Range(base,len);
       }
     };

    template <ArgCursorType<Point> Cur>
    Step(Cur cur)
     : points(DoBuild,PointBuilder<Cur>{cur}),
       rex(RealOk)
     {
     }
   };

  // Path

  struct Path
   {
    static const int TypeId = 9 ;

    static StrLen TypeName() { return "Path"_c ; }

    RefArray<Dot> dots;
    RealException rex;

    Path(RealException rex_=RealBlank) : rex(rex_) {}

    template <ArgCursorType<Point> Cur>
    Path(Cur cur)
     : dots(DoBuild,PointBuilder<Cur>{cur}),
       rex(RealOk)
     {
     }

    Path(ArgCursorType<Step> cur)
     : rex(RealOk)
     {
      for(; +cur ;++cur)
        {
         Step step=*cur;

         dots.extend(StepBuilder{Range(step.points)});
        }
     }
   };

  // Loop

  struct Loop
   {
    static const int TypeId = 10 ;

    static StrLen TypeName() { return "Loop"_c ; }

    RefArray<Dot> dots;
    RealException rex;

    Loop(RealException rex_=RealBlank) : rex(rex_) {}

    template <ArgCursorType<Point> Cur>
    Loop(Cur cur)
     : dots(DoBuild,PointBuilder<Cur>{cur}),
       rex(RealOk)
     {
     }

    Loop(ArgCursorType<Step> cur)
     : rex(RealOk)
     {
      for(; +cur ;++cur)
        {
         Step step=*cur;

         dots.extend(StepBuilder{Range(step.points)});
        }
     }
   };

  // Solid

  struct Solid
   {
    static const int TypeId = 11 ;

    static StrLen TypeName() { return "Solid"_c ; }

    RefArray<Dot> dots;
    RealException rex;

    Solid(RealException rex_=RealBlank) : rex(rex_) {}

    Solid(Loop loop) : dots(loop.dots),rex(loop.rex) {}
   };

  // type functions

  template <class Func>
  static auto TypeSwitch(int type_id,Func func)
   {
    switch( type_id )
      {
       case Ratio::TypeId : return func.template doIt<Ratio>();

       case Length::TypeId : return func.template doIt<Length>();

       case Angle::TypeId : return func.template doIt<Angle>();

       case Point::TypeId : return func.template doIt<Point>();

       case Line::TypeId : return func.template doIt<Line>();

       case Circle::TypeId : return func.template doIt<Circle>();

       case Couple::TypeId : return func.template doIt<Couple>();

       case Step::TypeId : return func.template doIt<Step>();

       case Path::TypeId : return func.template doIt<Path>();

       case Loop::TypeId : return func.template doIt<Loop>();

       case Solid::TypeId : return func.template doIt<Solid>();

       default: return func.doOther();
      }
   }

  struct TypeNameFunc
   {
    template <class S>
    static StrLen doIt() { return S::TypeName(); }

    static StrLen doOther() { return "???"_c; }
   };

  static StrLen TypeName(int type_id)
   {
    return TypeSwitch(type_id,TypeNameFunc());
   }

  // special functions

  static Point MeetIn(Line a,Point b,Point c);

  static Couple MeetCircleIn(Circle C,Point a,Point b); // Couple in a -> b direction

  // functions

  static Length LengthOf(Point a,Point b) { return Point::Norm(a-b); }

  static Angle AngleOf(Point a,Point o,Point b) { return Point::Arg(b-o)-Point::Arg(a-o); }

  static Line LineOf(Point a,Point b) { return {a,b-a}; }

  static Point Middle(Point a,Point b) { return (a+b)/2; }

  static Point Part(Point a,Point b,Ratio r) { return a+r.val*(b-a); }

  static Line MidOrt(Point a,Point b);

  static Circle CircleOf(Point center,Length radius) { return {center,radius}; }

  static Circle CircleOuter(Point a,Point b,Point c);

  static Point Proj(Line a,Point p);

  static Angle AngleC(Length a,Length b,Length c);

  static Point Meet(Line a,Line b);

  static Couple MeetCircle(Line a,Circle C); // Couple in a direction

  static Couple MeetCircles(Circle C,Circle D); // Couple in C direction

  static Point Rotate(Point o,Angle a,Point p) { return o+Point::Rotate(a,p-o); }

  static Point RotateOrt(Point o,Point p) { return o+Point::Orthogonal(p-o); }

  static Point Move(Point a,Point b,Point p) { return (b-a)+p; }

  static Point MoveLen(Line a,Length len,Point p) { return len.val*a.ort+p; }

  static Point Mirror(Line a,Point p);

  static Point First(Couple c) { return c.a; }

  static Point Second(Couple c) { return c.b; }

  static Point Up(Length len,Point p) { return {p.x,p.y-len.val}; }

  static Point Down(Length len,Point p) { return {p.x,p.y+len.val}; }

  static Point Left(Length len,Point p) { return {p.x-len.val,p.y}; }

  static Point Right(Length len,Point p) { return {p.x+len.val,p.y}; }

  static Step StepOf(ArgCursorType<Point> cur) { return Step(cur); }

  static Path PathOf(ArgCursorType<Point> cur) { return Path(cur); }

  static Path PathOf(ArgCursorType<Step> cur) { return Path(cur); }

  static Loop LoopOf(ArgCursorType<Point> cur) { return Loop(cur); }

  static Loop LoopOf(ArgCursorType<Step> cur) { return Loop(cur); }

  static Solid SolidOf(Loop loop) { return Solid(loop); }

  // function list

  template <class Func>
  static void FunctionList(Func func)
   {
    func.template doIt<decltype(LengthOf),LengthOf>( "Len"_c ,"LengthOf"_c );
    func.template doIt<decltype(AngleOf),AngleOf>( "Angle"_c , "AngleOf"_c );
    func.template doIt<decltype(LineOf),LineOf>( "Line"_c , "LineOf"_c );
    func.template doIt<decltype(Middle),Middle>( "Mid"_c , "Middle"_c );
    func.template doIt<decltype(Part),Part>( "Part"_c , "Part"_c );
    func.template doIt<decltype(MidOrt),MidOrt>( "MidOrt"_c , "MidOrt"_c );
    func.template doIt<decltype(CircleOf),CircleOf>( "Cir"_c , "CircleOf"_c );
    func.template doIt<decltype(CircleOuter),CircleOuter>( "OCir"_c , "CircleOuter"_c );
    func.template doIt<decltype(Proj),Proj>( "Proj"_c , "Proj"_c );
    func.template doIt<decltype(AngleC),AngleC>( "AngleC"_c , "AngleC"_c );
    func.template doIt<decltype(Meet),Meet>( "Meet"_c , "Meet"_c );
    func.template doIt<decltype(MeetCircle),MeetCircle>( "MeetCircle"_c , "MeetCircle"_c );
    func.template doIt<decltype(MeetCircles),MeetCircles>( "MeetCircles"_c , "MeetCircles"_c );
    func.template doIt<decltype(Rotate),Rotate>( "Rot"_c , "Rotate"_c );
    func.template doIt<decltype(RotateOrt),RotateOrt>( "RotOrt"_c , "RotateOrt"_c );
    func.template doIt<decltype(Move),Move>( "Move"_c , "Move"_c );
    func.template doIt<decltype(MoveLen),MoveLen>( "MoveLen"_c , "MoveLen"_c );
    func.template doIt<decltype(Mirror),Mirror>( "Mirror"_c , "Mirror"_c );
    func.template doIt<decltype(First),First>( "First"_c , "First"_c );
    func.template doIt<decltype(Second),Second>( "Second"_c , "Second"_c );
    func.template doIt<decltype(Up),Up>( "Up"_c , "Up"_c );
    func.template doIt<decltype(Down),Down>( "Down"_c , "Down"_c );
    func.template doIt<decltype(Left),Left>( "Left"_c , "Left"_c );
    func.template doIt<decltype(Right),Right>( "Right"_c , "Right"_c );
    func.template doIt<decltype(SolidOf),SolidOf>( "Solid"_c , "SolidOf"_c );

    func.template doIt<Step (Point[]),StepOf>( "Step"_c , "StepOf"_c );
    func.template doIt<Path (Point[]),PathOf>( "Path"_c , "PathOf"_c );
    func.template doIt<Loop (Point[]),LoopOf>( "Loop"_c , "LoopOf"_c );
    func.template doIt<Path (Step[]),PathOf>( "BPath"_c , "BPathOf"_c );
    func.template doIt<Loop (Step[]),LoopOf>( "BLoop"_c , "BLoopOf"_c );
   }

  // conversions

  static MCoord Map(Geometry::Real x) { return (MCoord)x.map(MPoint::Precision); }

  static MPoint Map(Geometry::Point point) { return MPoint(Map(point.x),Map(point.y)); }
 };

/* functions */

inline Geometry::Angle GradToRadian(Geometry::Real val) { return Geometry::Angle( (val/180)*Geometry::Real::Pi() ); }

inline Geometry::Point GPoint(Point point) { return Geometry::Point(point.x,point.y); }

Geometry::Real StrToReal(StrLen str);

} // namespace App

#endif

