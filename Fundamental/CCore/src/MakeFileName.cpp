/* MakeFileName.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/MakeFileName.h>

#include <CCore/inc/Path.h>
#include <CCore/inc/Exception.h>

namespace CCore {

/* class MakeFileName */

bool MakeFileName::HasNoExt(StrLen file_name)
 {
  SplitExt split(file_name);

  return !split;
 }

void MakeFileName::make(StrLen dir_name,StrLen file_name)
 {
  if( +dir_name )
    {
     char ch=dir_name.back(1);

     if( PathBase::IsColon(ch) || PathBase::IsSlash(ch) )
       {
        add(dir_name,file_name);
       }
     else
       {
        add(dir_name,'/',file_name);
       }
    }
  else
    {
     add(file_name);
    }

  if( !(*this) )
    {
     Printf(Exception,"CCore::MakeFileName::make(#.q;,#.q;) : too long path",dir_name,file_name);
    }
 }

void MakeFileName::make(StrLen dir_name,StrLen file_name,StrLen auto_ext)
 {
  make(dir_name,file_name);

  if( +auto_ext && HasNoExt(file_name) ) add(auto_ext);

  if( !(*this) )
    {
     Printf(Exception,"CCore::MakeFileName::make(#.q;,#.q;,#.q;) : too long path",dir_name,file_name,auto_ext);
    }
 }

/* class WDirFileName */

WDirFileName::WDirFileName(StrLen wdir,StrLen file)
 {
  if( !wdir )
    {
     result=file;
    }
  else
    {
     if( PathIsRel(file) )
       {
        result=buf(wdir,file);
       }
     else
       {
        result=file;
       }
    }
 }

} // namespace CCore

