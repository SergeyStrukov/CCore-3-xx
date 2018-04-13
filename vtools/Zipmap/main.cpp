/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Zipmap 1.00
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

#include <CCore/inc/MakeString.h>
#include <CCore/inc/Path.h>
#include <CCore/inc/Deflate.h>
#include <CCore/inc/DecodeFile.h>
#include <CCore/inc/BinaryFile.h>
#include <CCore/inc/Array.h>

namespace App {

/* using */

using namespace CCore;

/* Next() */

template <class Dev>
uint32 Next(Dev &dev)
 {
  uint32 ret;

  dev.template use<BeOrder>(ret);

  return ret;
 }

/* Diff() */

void Diff(uint8 *base,ulen dx,ulen dy)
 {
  if( dx<=1 || dy<=1 ) return;

  uint8 *ptr=base+(dx*dy-1);

  for(dy--; dy-- ;)
    {
     for(ulen cnt=dx-1; cnt-- ;ptr--)
       {
        (*ptr) += *(ptr-dx-1) - *(ptr-1) - *(ptr-dx) ;
       }

     ptr--;
    }
 }

/* Zip() */

void Zip(StrLen src_file,StrLen dst_file)
 {
  Printf(Con,"zip #.q; -> #.q;\n\n",src_file,dst_file);

  DecodeFile src(src_file);
  BinaryFile dst(dst_file);

  auto temp=ToFunction<void (PtrLen<const uint8>)>( [&dst] (PtrLen<const uint8> data) { dst.put(data); } );

  Deflate::Deflator zip(temp.function());

  ulen dx=Next(src);
  ulen dy=Next(src);

  Printf(Con,"#; x #;\n\n",dx,dy);

  dst.use<BeOrder>(dx,dy);

  ulen len=LenOf(dy,dx);

  DynArray<uint32> map(DoRaw{len});

  for(uint32 &x : map ) x=Next(src);

  DynArray<uint8> plane(DoRaw{len});

  for(unsigned shift=0; shift<32u ;shift+=8)
    {
     for(ulen i=0; i<len ;i++) plane[i]=uint8(map[i]>>shift);

     Diff(plane.getPtr(),dx,dy);

     zip.put(Range(plane));

     zip.complete();
    }
 }

/* Undiff() */

void Undiff(uint8 *base,ulen dx,ulen dy)
 {
  if( dx<=1 || dy<=1 ) return;

  uint8 *ptr=base+(dx+1);

  for(dy--; dy-- ;)
    {
     for(ulen cnt=dx-1; cnt-- ;ptr++)
       {
        (*ptr) -= *(ptr-dx-1) - *(ptr-1) - *(ptr-dx) ;
       }

     ptr++;
    }
 }

/* Unzip() */

void Unzip(StrLen src_file,StrLen dst_file)
 {
  Printf(Con,"unzip #.q; -> #.q;\n\n",src_file,dst_file);

  DecodeFile src(src_file);
  BinaryFile dst(dst_file);

  ulen dx=Next(src);
  ulen dy=Next(src);

  Printf(Con,"#; x #;\n\n",dx,dy);

  dst.use<BeOrder>(dx,dy);

  ulen len=LenOf(dy,dx);

  DynArray<uint32> map(DoRaw{len});

  DynArray<uint8> plane(DoRaw{len});

  PtrLen<uint8> cur=Range(plane);
  unsigned shift=0;

  auto temp1=ToFunction<void (PtrLen<const uint8>)>( [&] (PtrLen<const uint8> data)
                                                   {
                                                    if( data.len>cur.len )
                                                      {
                                                       Printf(Exception,"App::Unzip(...) : plane data overflow");
                                                      }

                                                    if( shift>=32 )
                                                      {
                                                       Printf(Exception,"App::Unzip(...) : extra plane");
                                                      }

                                                    data.copyTo(cur.ptr);

                                                    cur+=data.len;

                                                   } );

  auto temp2=ToFunction<void (void)>( [&] ()
                                          {
                                           if( cur.len )
                                             {
                                              Printf(Exception,"App::Unzip(...) : plane data underflow");
                                             }

                                           if( shift>=32 )
                                             {
                                              Printf(Exception,"App::Unzip(...) : extra plane");
                                             }

                                           Undiff(plane.getPtr(),dx,dy);

                                           for(ulen i=0; i<len ;i++) map[i]|=uint32(plane[i])<<shift;

                                           cur=Range(plane);
                                           shift+=8;

                                          } );

  Deflate::Inflator unzip(temp1.function(),true);

  unzip.setTrigger(temp2.function());

  while( src.more() ) unzip.put(src.pump());

  unzip.complete();

  for(uint32 x : map ) dst.use<BeOrder>(x);
 }

/* Main() */

StrLen ChangeExt(MakeString<MaxPathLen> &buf,StrLen src_file,StrLen new_ext)
 {
  StrLen ext=SuffixExt(src_file);

  if( !buf.add(src_file.inner(0,ext.len),new_ext) )
    {
     Printf(Exception,"App::ChangeExt(...) : too long file name");
    }

  return buf.get();
 }

void Main(int argc,const char *argv[],StrLen cmd)
 {
  MakeString<MaxPathLen> temp;

  if( cmd.equal("-z"_c) )
    {
     StrLen src_file=argv[2];

     StrLen dst_file;

     if( argc==3 )
       {
        dst_file=ChangeExt(temp,src_file,".zipmap"_c);
       }
     else if( argc==4 )
       {
        dst_file=argv[3];
       }
     else
       {
        Printf(Exception,"App::Main(...) : bad arguments number");
       }

     Zip(src_file,dst_file);

     return;
    }

  if( cmd.equal("-x"_c) )
    {
     StrLen src_file=argv[2];

     StrLen dst_file;

     if( argc==3 )
       {
        dst_file=ChangeExt(temp,src_file,".bitmap"_c);
       }
     else if( argc==4 )
       {
        dst_file=argv[3];
       }
     else
       {
        Printf(Exception,"App::Main(...) : bad arguments number");
       }

     Unzip(src_file,dst_file);

     return;
    }

  Printf(Exception,"App::Main(...) : bad command");
 }

void Main(int argc,const char *argv[])
 {
  if( argc<3 )
    {
     Printf(Exception,"App::Main(...) : bad arguments number");
    }

  Main(argc,argv,argv[1]);
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
      Putobj(Con,"--- Zipmap 1.00 ---\n--- Copyright (c) 2018 Sergey Strukov. All rights reserved. ---\n\n");

      Main(argc,argv);
     }

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

