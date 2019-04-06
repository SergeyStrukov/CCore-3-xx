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
  SplitName split1(file_name);
  SplitExt split2(split1.name);

  return !split2;
 }

void MakeFileName::make(StrLen dir_name,StrLen file_name)
 {
  struct AddFunc
   {
    MakeFileName *obj;

    void operator () (StrLen file) { obj->add(file); }

    void operator () (StrLen dir,StrLen file) { obj->add(dir,file); }

    void operator () (StrLen dir,char ch,StrLen file) { obj->add(dir,ch,file); }

   } addfunc{this};

  DirPlusFile(dir_name,file_name,addfunc);

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

