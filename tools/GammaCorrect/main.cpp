/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: GammaCorrect 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <cmath>

#include <CCore/inc/Print.h>

using namespace std;
using namespace CCore;

/* main() */

double F1(double x)
 {
  return x/12.92;
 }

double F2(double x)
 {
  return pow( (x+0.055)/1.055 , 2.4 );
 }

const double X=0.04045;

double F(double x)
 {
  if( x<X ) return F1(x);

  return F2(x);
 }

double InvF1(double x)
 {
  return 12.92*x;
 }

double InvF2(double x)
 {
  return 1.055*pow(x,1/2.4)-0.055;
 }

const double InvX=0.00031308;

double InvF(double x)
 {
  if( x<InvX ) return InvF1(x);

  return InvF2(x);
 }

int main()
 {
  PrintFile out("test.txt");

#if 0 // 2.4

  // 1

  Printf(out," {");

  for(int i=0; i<256 ;i++)
    {
     double x=double(i)/255;
     double y=F(x);

     int val=(int)round(y*65535);

     if( (i%16)==0 ) Printf(out,"\n  ");

     Printf(out,"#;",val);

     if( i+1<256 ) Printf(out,",");
    }

  Printf(out,"\n };\n\n");

  // 2

  Printf(out," {");

  for(int i=0; i<65536 ;i++)
    {
     double x=double(i)/65535;
     double y=InvF(x);

     int val=(int)round(y*255);

     if( (i%16)==0 ) Printf(out,"\n  ");

     Printf(out,"#;",val);

     if( i+1<65536 ) Printf(out,",");
    }

#endif

#if 1 // 1.8

  // 1

  Printf(out," {");

  for(int i=0; i<256 ;i++)
    {
     double x=double(i)/255;
     double y=pow(x,1.8);

     int val=(int)round(y*65535);

     if( (i%16)==0 ) Printf(out,"\n  ");

     Printf(out,"#;",val);

     if( i+1<256 ) Printf(out,",");
    }

  Printf(out,"\n };\n\n");

  // 2

  Printf(out," {");

  for(int i=0; i<65536 ;i++)
    {
     double x=double(i)/65535;
     double y=pow(x,1/1.8);

     int val=(int)round(y*255);

     if( (i%16)==0 ) Printf(out,"\n  ");

     Printf(out,"#;",val);

     if( i+1<65536 ) Printf(out,",");
    }

#endif

  Printf(out,"\n };\n\n");

  return 0;
 }

 
