/* VMakeProc.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: vmake 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/VMakeProc.h>

#include <CCore/inc/Path.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

namespace App {

namespace VMake {

/* class DataProc */

DataProc::DataProc(StrLen file_name,StrLen target)
 : DataProc(file_name,target,PrefixPath(file_name))
 {
 }

DataProc::DataProc(StrLen file_name,StrLen target,StrLen wdir_)
 : data(file_name,target),
   wdir(wdir_)
 {
 }

DataProc::~DataProc()
 {
 }

int DataProc::make()
 {
  return 1;
 }

} // namespace VMake

} // namespace App

