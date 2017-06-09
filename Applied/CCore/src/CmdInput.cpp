/* CmdInput.cpp */
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

#include <CCore/inc/CmdInput.h>

#include <CCore/inc/Sort.h>
#include <CCore/inc/Exception.h>

namespace CCore {

/* class CmdInput */

void CmdInput::add(StrLen cmd,TargetMethod method)
 {
  if( locked )
    {
     Printf(Exception,"CCore::CmdInput::add(...) : locked");
    }

  list.append_fill(cmd,method);
 }

auto CmdInput::getCur() const -> Frame
 {
  if( off>0 ) return frame_list[off-1];

  return Range(list);
 }

 // constructors

CmdInput::CmdInput(Target &target_)
 : target(target_),
   list(DoReserve,50)
 {
  locked=false;

  target_.buildCmdList(*this);

  locked=true;

  Sort(Range(list));

  ulen max_len=0;

  for(auto r=Range(list); +r ;++r) Replace_max(max_len,r->cmd.len);

  frame_list.extend_default(max_len);

  start();
 }

CmdInput::~CmdInput()
 {
 }

 // methods

bool CmdInput::put(char ch)
 {
  if( off>=frame_list.getLen() )
    {
     off++;

     return false;
    }

  Frame next=StrNextFrame(getCur(),off,ch, [] (const Rec &rec) { return rec.cmd; } );

  frame_list[off++]=next;

  return +next;
 }

auto CmdInput::complete() const -> CompleteResult
 {
  if( off>frame_list.getLen() ) return Nothing;

  Frame cur=getCur();

  if( !cur ) return Nothing;

  ulen count=cur.len;

  if( count>1 ) return count;

  StrLen rest=cur->cmd.part(off);

  return rest;
 }

auto CmdInput::finish() -> FinishResult
 {
  if( off>frame_list.getLen() ) return Nothing;

  Frame last=StrLastFrame(getCur(),off, [] (const Rec &rec) { return rec.cmd; } );

  if( !last ) return Nothing;

  return FinishResult(target,last->method);
 }

} // namespace CCore


