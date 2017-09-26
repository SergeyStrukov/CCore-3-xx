/* Geometry.cpp */
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

#include <inc/Geometry.h>

#include <CCore/inc/Exception.h>

#include <math.h>

namespace App {

/* struct Geometry::Real */

const char * GetTextDesc(Geometry::RealException rex)
 {
  switch( rex )
    {
     case Geometry::RealOk : return "ok";

     case Geometry::RealBlank : return "uninitialized";

     case Geometry::RealTooBig : return "too big";

     case Geometry::RealTooSmall : return "too small";

     case Geometry::RealOutOfDomain : return "out of domain";

     default: return "???";
    }
 }

static const double Cap = 1.e+100 ;

double Geometry::Real::Guard(double x)
 {
  if( fabs(x)>Cap ) throw RealTooBig;

  return x;
 }

void Geometry::Real::GuardDiv(double y)
 {
  if( fabs(y)<1/Cap ) throw RealTooSmall;
 }

Geometry::Real::Real(Bin bin)
 {
  val=ldexp(bin.mantissa,bin.exp);

  if( fabs(val)>Cap )
    {
     Printf(Exception,"App::Geometry::Real::Real({#;,#;}) : too big",bin.mantissa,bin.exp);
    }
 }

Geometry::Real Geometry::Real::Norm(Real x,Real y)
 {
  return Guard( hypot(x.val,y.val) );
 }

Geometry::Real Geometry::Real::Arg(Real x,Real y)
 {
  GuardDiv( fabs(x.val)+fabs(y.val) );

  return atan2(y.val,x.val);
 }

Geometry::Real Geometry::Real::Sin(Real x)
 {
  return sin(x.val);
 }

Geometry::Real Geometry::Real::Cos(Real x)
 {
  return cos(x.val);
 }

Geometry::Real Geometry::Real::ArcCos(Real x)
 {
  if( x<-1 || x>1 ) throw RealOutOfDomain;

  return acos(x.val);
 }

Geometry::Real Geometry::Real::Sqrt(Real x)
 {
  if( x<0 ) throw RealOutOfDomain;

  return sqrt(x.val);
 }

Geometry::Real Geometry::Real::Mod(Real x,Real y)
 {
  GuardDiv(y.val);

  return remainder(x.val,y.val);
 }

Geometry::RealException Geometry::Real::BoundedDiv(Real x,Real y)
 {
  if( y<0 )
    {
     y=-y;
     x=-x;
    }

  if( y<1/Cap ) return RealTooSmall;

  if( x<0 || x>y ) return RealOutOfDomain;

  return RealOk;
 }

Geometry::Real Geometry::Real::Pow(Real x,ulen deg)
 {
  if( !deg ) return 1;

  BitScanner<ulen> scanner(deg);

  Real ret(x);

  for(++scanner; +scanner ;++scanner)
    if( *scanner )
      {
       ret=Sq(ret)*x;
      }
    else
      {
       ret=Sq(ret);
      }

  return ret;
 }

Geometry::Real Geometry::Real::Den(Real x_,Real cap)
 {
  double x=fabs(x_.val);

  x=x-floor(x);

  if( x>0 )
    {
     double a=1,b=0,c=0,d=1;
     double y=x;

     while( y>1/Cap && d<cap )
       {
        double Y=1/y;
        double t=floor(Y);
        double z=Y-t;

        double a1=b;
        double b1=a+b*t;
        double c1=d;
        double d1=c+d*t;

        if( d1>cap ) break;

        a=a1;
        b=b1;
        c=c1;
        d=d1;

        y=z;
       }

     return d;
    }
  else
    {
     return 1;
    }
 }

Geometry::Real Geometry::Real::RoundMul(Real x,Real den)
 {
  return round(x.val*den.val);
 }

 // map

double Geometry::Real::map(int prec) const
 {
  return round(ldexp(val,prec));
 }

Geometry::Real::Bin Geometry::Real::toBin() const
 {
  int exp;

  double x=frexp(val,&exp);

  double y=ldexp(x,63);

  return { sint64(y) , sint16(exp-63) };
 }

 // print object

char Geometry::Real::ToStr::Digit(double d)
 {
  int ind=int(d);

  if( ind<10 ) return "0123456789"[ind];

  return '9';
 }

StrLen Geometry::Real::ToStr::Format(PtrLen<char> buf,double val)
 {
  PrintBuf out(buf);

  Putobj(out,int(val));

  return out.close();
 }

StrLen Geometry::Real::ToStr::Format(PtrLen<char> buf,double val,ulen prec)
 {
  Replace_min(prec,buf.len);

  auto out=Range(buf.ptr,prec);

  for(; +out ;++out)
    {
     double d;

     val=modf(10*val,&d);

     *out=Digit(d);
    }

  return Range(buf.ptr,prec);
 }

Geometry::Real::ToStr::ToStr(double val,ulen prec)
 {
  if( val<0 )
    {
     is_neg=true;
     is_pos=false;

     val=-val;
    }
  else
    {
     is_neg=false;

     is_pos = val>0 ;
    }

  if( val>0 )
    {
     if( val<1000000000 )
       {
        double ival;
        double fval=modf(val,&ival);

        int_part=Format(Range(int_buf),ival);

        fract_part=Format(Range(fract_buf),fval,prec);
       }
     else
       {
        int_part="HUGE"_c;
       }
    }
  else
    {
     int_part="0"_c;
    }
 }

Geometry::Real::PrintOptType::PrintOptType(const char *ptr,const char *lim)
 {
  StrParse dev(ptr,lim);

  Parse_empty(dev,show_sign);

  ParseUInt_empty(dev,width,0u);

  if( ParseChar_try(dev,'.') )
    {
     ParseUInt(dev,prec);
    }
  else
    {
     prec=DefaultPrec;
    }

  Parse_empty(dev,align);

  if( !dev.finish() ) setDefault();
 }

/* struct Geometry */

 // special functions

Geometry::Point Geometry::MeetIn(Line a,Point b,Point c)
 {
  Point dir=c-b;
  Point e=Point::Orthogonal(a.ort);

  Real s=Point::Prod(dir,e);
  Real t=Point::Prod(a.p-b,e);

  if( RealException rex=Real::BoundedDiv(t,s) ) return rex;

  return b+(t/s)*dir;
 }

Geometry::Couple Geometry::MeetCircleIn(Circle C,Point a,Point b)
 {
  Point dir=b-a;

  Real len=Point::Norm(dir);
  Point ort=dir/len;

  Real s=Point::Prod(C.center-a,ort);

  Point p=a+s*ort;

  Real x=Point::Norm(p-C.center);

  Real T=Sq(C.radius.val)-Sq(x);

  if( T<0 ) return RealOutOfDomain;

  Real t=Real::Sqrt(T);

  Real s1=s-t;
  Real s2=s+t;

  if( s1>len || s2<0 ) return RealOutOfDomain;

  if( s1<0 )
    {
     if( s2>len ) return RealOutOfDomain;

     return { a+s2*ort , RealOutOfDomain };
    }

  if( s2>len )
    {
     return { a+s1*ort , RealOutOfDomain };
    }

  return { a+s1*ort , a+s2*ort };
 }

 // functions

Geometry::Line Geometry::MidOrt(Point a,Point b)
 {
  Point c=Middle(a,b);

  return LineOf(c,RotateOrt(c,b));
 }

Geometry::Circle Geometry::CircleOuter(Point a,Point b,Point c)
 {
  Line p=MidOrt(a,b);

  Line q=MidOrt(a,c);

  Point center=Meet(p,q);

  Length radius=LengthOf(center,a);

  return CircleOf(center,radius);
 }

Geometry::Point Geometry::Proj(Line a,Point p)
 {
  Real t=Point::Prod(p-a.p,a.ort);

  return a.p+t*a.ort;
 }

Geometry::Angle Geometry::AngleC(Length a,Length b,Length c)
 {
  Real t=(Sq(a.val)+Sq(b.val)-Sq(c.val))/(2*a.val*Real::Abs(b.val));

  return Angle::ArcCos(t);
 }

Geometry::Point Geometry::Meet(Line a,Line b)
 {
  Point e=Point::Orthogonal(b.ort);

  Real t=Point::Prod(a.p-b.p,e)/Point::Prod(a.ort,e);

  return a.p-t*a.ort;
 }

Geometry::Couple Geometry::MeetCircle(Line a,Circle C)
 {
  Point p=Proj(a,C.center);

  Real x=Point::Norm(p-C.center);

  Real t=Real::Sqrt( Sq(C.radius.val)-Sq(x) );

  Point delta=t*a.ort;

  return {p-delta,p+delta};
 }

Geometry::Couple Geometry::MeetCircles(Circle C,Circle D)
 {
  Angle a=AngleC(C.radius,LengthOf(C.center,D.center),D.radius);

  Angle d=Point::Arg(D.center-C.center);

  return {C.center+Point::Polar(C.radius,d-a),C.center+Point::Polar(C.radius,d+a)};
 }

Geometry::Point Geometry::Mirror(Line a,Point p)
 {
  Point e=Point::Orthogonal(a.ort);

  return p-2*Point::Prod(p-a.p,e)*e;
 }

/* functions */

#ifdef CCORE_UTF8

inline bool CharDecValue(Char ch) { return (ch<128)?CharDecValue((char)ch):(-1); }

#endif

Geometry::Real StrToReal(PtrLen<const Char> str)
 {
  Geometry::Real ret(0);

  ulen deg=0;

  for(; +str ;++str)
    {
     int dig=CharDecValue(*str);

     if( dig<0 )
       {
        deg=str.len-1;
       }
     else
       {
        ret=10*ret+dig;
       }
    }

  return ret/Geometry::Real::Pow(10,deg);
 }

} // namespace App

