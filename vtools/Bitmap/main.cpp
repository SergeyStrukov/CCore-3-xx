/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Bitmap Convertor 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/BinaryFile.h>

#include "Bitmap.h"

namespace App {

/* using */

using namespace CCore;

/* struct PrintBmp */

struct PrintBmp : BitmapProc
 {
  BinaryFile dev;

  explicit PrintBmp(StrLen output_file_name) : dev(output_file_name,Open_ToWrite|Open_AutoDelete) {}

  void line(const void *buf,int dx)
   {
    auto range=Range(static_cast<const uint32 *>(buf),dx);

    for(uint32 col : range )
      {
       col&=0xFFFFFFu;

       dev.use<BeOrder>(col);
      }
   }

  virtual void operator () (const void *buf,int dx,int dy,int dline)
   {
    if( dy<=0 || dx<=0 )
      {
       Printf(Exception,"App::PrintBmp::operator () : bad size #; #;",dx,dy);
      }

    uint32 dx_=dx;
    uint32 dy_=dy;

    dev.use<BeOrder>(dx_,dy_);

    if( dline>0 )
      {
       while( dy-- > 0 )
         {
          line(buf,dx);

          if( dy )
            {
             buf=PtrAdd(buf,dline);
            }
         }
      }
    else
      {
       Printf(Con,"dline = #;\n",dline);

       dline=-dline;

       while( dy-- > 0 )
         {
          line(buf,dx);

          if( dy )
            {
             buf=PtrSub(buf,dline);
            }
         }
      }
   }
 };

/* Main() */

void Main(StrLen input_file_name,StrLen output_file_name)
 {
  PrintBmp out(output_file_name);

  out.open(input_file_name.ptr,input_file_name.len);

  out.dev.preserveFile();
 }

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char *argv[])
 {
  try
    {
     ReportException report;

     {
      Putobj(Con,"--- Bitmap Convertor 1.00 ---\n--- Copyright (c) 2018 Sergey Strukov. All rights reserved. ---\n\n");

      if( argc<3 )
        {
         Putobj(Con,"Usage: CCore-Bitmap <input-file-name> <output-file-name>\n");

         return 1;
        }

      Main(argv[1],argv[2]);
     }

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

