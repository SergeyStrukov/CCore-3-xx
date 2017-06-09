/* FileName.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/FileName.h>

namespace CCore {

/* class FileName */

struct FileName::PathUp : PathBase
 {
  StrLen path;
  ulen up;
  bool ok;

  PathUp(StrLen path,ulen up)
   : ok(false)
   {
    SplitPath split_dev(path);

    ulen len=split_dev.path.len;

    for(; len && up ;up--)
      {
       SplitName split({split_dev.path.ptr,len-1});

       switch( split.getNameType() )
         {
          case Name :
           {
            len=split.path.len;
           }
          break;

          case DotDotName :
           {
            set(path.prefix(split_dev.dev.len+len),up);
           }
          return;

          default: return;
         }
      }

    set(path.prefix(split_dev.dev.len+len),up);
   }

  bool operator ! () const { return !ok; }

  void set(StrLen path_,ulen up_)
   {
    path=path_;
    up=up_;
    ok=true;
   }
 };

class FileName::Out : NoCopy
 {
   char *out;

  public:

   Out(DynArray<char> &buf,ulen len)
    {
     out=buf.extend_raw(len).ptr;
    }

   void put(char ch)
    {
     *(out++)=ch;
    }

   void put(StrLen str)
    {
     str.copyTo(out);

     out+=str.len;
    }

   template <class T>
   Out & operator << (T t)
    {
     put(t);

     return *this;
    }

   template <class ... TT>
   void operator () (TT ... tt)
    {
     ( (*this) << ... << tt );
    }
 };

void FileName::setAbs(StrLen file_name,SplitPath split_dev,SplitPathName split_file)
 {
  if( split_file.no_path )
    {
     buf.extend_copy(file_name);

     off=split_dev.dev.len;
    }
  else
    {
     DynArray<StrLen> list(DoReserve,10);
     ulen up=0;
     bool root=false;

     list.append_copy(split_file.name);

     StrLen p=split_file.path;

     for(;;)
       {
        SplitPathName split_path(p);

        switch( split_path.getNameType() )
          {
           case SplitPathName::Name :
            {
             if( up )
               up--;
             else
               list.append_copy(split_path.name);
            }
           break;

           case SplitPathName::EmptyName :
            {
             if( !split_path.no_path || up ) return;

             root=true;
            }
           break;

           case SplitPathName::DotName :
            {
             // skip
            }
           break;

           case SplitPathName::DotDotName :
            {
             up++;
            }
           break;
          }

        if( split_path.no_path ) break;

        p=split_path.path;
       }

     // count length

     ulen len=split_dev.dev.len;

     if( root ) len++;

     len+=3*up;

     for(ulen i=list.getLen()-1; i ;i--) len+=list[i].len+1;

     off=len;

     len+=list[0].len;

     // build

     Out out(buf,len);

     out(split_dev.dev);

     if( root ) out('/');

     for(; up ;up--) out('.','.','/');

     for(ulen i=list.getLen()-1; i ;i--) out(list[i],'/');

     out(list[0]);
    }

  ok=true;
 }

void FileName::setRel(StrLen path,SplitPathName split_file)
 {
  if( split_file.no_path )
    {
     ulen len=LenAdd(path.len,split_file.name.len);

     Out out(buf,len);

     out(path,split_file.name);

     off=path.len;
    }
  else
    {
     DynArray<StrLen> list(DoReserve,10);
     ulen up=0;

     list.append_copy(split_file.name);

     StrLen p=split_file.path;

     for(;;)
       {
        SplitPathName split_path(p);

        switch( split_path.getNameType() )
          {
           case SplitPathName::Name :
            {
             if( up )
               up--;
             else
               list.append_copy(split_path.name);
            }
           break;

           case SplitPathName::EmptyName :
            {
             return;
            }
           break;

           case SplitPathName::DotName :
            {
             // skip
            }
           break;

           case SplitPathName::DotDotName :
            {
             up++;
            }
           break;
          }

        if( split_path.no_path ) break;

        p=split_path.path;
       }

     if( up )
       {
        PathUp path_up(path,up);

        if( !path_up ) return;

        path=path_up.path;
        up=path_up.up;
       }

     // count length

     ULenSat len=path.len;

     len+=3*up;

     for(ulen i=list.getLen()-1; i ;i--) len+=list[i].len+1;

     ulen off_=len.value;

     len+=list[0].len;

     if( !len ) return;

     off=off_;

     // build

     Out out(buf,len.value);

     out(path);

     for(; up ;up--) out('.','.','/');

     for(ulen i=list.getLen()-1; i ;i--) out(list[i],'/');

     out(list[0]);
    }

  ok=true;
 }

FileName::FileName(StrLen file_name)
 : FileName()
 {
  SplitPath split_dev(file_name);

  SplitPathName split_file(split_dev.path);

  if( split_file.getNameType()==SplitPathName::Name )
    {
     setAbs(file_name,split_dev,split_file);
    }
 }

FileName::FileName(StrLen path,StrLen file_name)
 : FileName()
 {
  SplitPath split_dev(file_name);

  SplitPathName split_file(split_dev.path);

  if( split_file.getNameType()==SplitPathName::Name )
    {
     if( split_dev.no_dev && !IsRooted(file_name) )
       {
        setRel(path,split_file);
       }
     else
       {
        setAbs(file_name,split_dev,split_file);
       }
    }
 }

} // namespace CCore


