/* CmdInput.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_CmdInput_h
#define CCore_inc_CmdInput_h

#include <CCore/inc/Cmp.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/CharProp.h>
#include <CCore/inc/InputUtils.h>
#include <CCore/inc/StrMap.h>

namespace CCore {

/* classes */

class CmdInput;

template <ReadConType ReadCon,ulen MaxArgLen=80> class CmdInputCon;

/* class CmdInput */

class CmdInput : NoCopy
 {
  public:

   struct Target
    {
     virtual void buildCmdList(CmdInput &input)=0;

     template <class T>
     void addCommand(CmdInput &input,StrLen cmd,void (T::*method)(StrLen arg)) // cmd must be persistent for CmdInput life-time
      {
       input.add(cmd,static_cast<TargetMethod>(method));
      }
    };

   using TargetMethod = void (Target::*)(StrLen arg) ;

  private:

   Target &target;

   struct Rec
    {
     StrLen cmd;
     TargetMethod method;

     // constructors

     Rec(StrLen cmd_,TargetMethod method_) : cmd(cmd_),method(method_) {}

     // methods

     bool operator < (const Rec &obj) const { return StrLess(cmd,obj.cmd); }
    };

   DynArray<Rec> list;
   bool locked;

   using Frame = PtrLen<const Rec> ;

   DynArray<Frame> frame_list;
   ulen off;

#ifdef CCORE_UTF8

   DynArray<char> buf;

#endif

  private:

   void add(StrLen cmd,TargetMethod method);

   Frame getCur() const;

   bool putFrame(char ch);

#ifdef CCORE_UTF8

   void putBuf(StrLen str);

#endif

  public:

   // constructors

   explicit CmdInput(Target &target);

   ~CmdInput();

   // methods

   void start() { off=0; }

#ifdef CCORE_UTF8

   bool put(Utf8Code ch);

   bool back();

#else

   bool put(char ch) { return putFrame(ch); }

   bool back()
    {
     if( off )
       {
        off--;

        return true;
       }

     return false;
    }

#endif

   void put(StrLen str);

   struct CompleteResult
    {
     ulen count;
     StrLen str;

     // constructors

     CompleteResult(NothingType) : count(0) {}

     CompleteResult(ulen count_) : count(count_) {}

     CompleteResult(StrLen str_) : count(1),str(str_) {}
    };

   CompleteResult complete() const;

   struct FinishResult
    {
     Target *target;
     TargetMethod method;

     // constructors

     FinishResult(NothingType) : target(0),method(0) {}

     FinishResult(Target &target_,TargetMethod method_) : target(&target_),method(method_) {}

     // methods

     bool operator + () const { return target!=0; }

     bool operator ! () const { return target==0; }

     void operator () (StrLen arg) { (target->*method)(arg); }

     template <class Report>
     void operator () (StrLen arg,Report &report)
      {
       try
         {
          (target->*method)(arg);

          report.guard();
         }
       catch(CatchType)
         {
          report.clear();
         }
      }
    };

   FinishResult finish();
 };

/* class CmdInputCon<ReadCon,ulen MaxArgLen> */

template <ReadConType ReadCon,ulen MaxArgLen>
class CmdInputCon : NoCopy
 {
   CmdInput input;

   StrLen prompt_str;
   char bad_char;

   ReadCon con;

   char arg[MaxArgLen];
   ulen arg_len;

  private:

   bool inputArg();

  public:

   template <class ... SS>
   CmdInputCon(CmdInput::Target &target,StrLen prompt_str,SS && ... ss); // prompt_str must be persistent for CmdInputCon life-time

   ~CmdInputCon();

   void setBadChar(char bad_char_) { bad_char=bad_char_; }

   template <class ... SS>
   void command(SS && ... ss);
 };

template <ReadConType ReadCon,ulen MaxArgLen>
bool CmdInputCon<ReadCon,MaxArgLen>::inputArg()
 {
  arg_len=0;

  for(;;)
    {
     ReadConCode ch=con.get();

     switch( ToChar(ch) )
       {
        case '\n' :
        case '\r' :
         {
          con.put("\r\n"_c);

          return true;
         }
        break;

        case '\b' :
         {
          if( arg_len>0 )
            {
             arg_len=PopSymbol(arg,arg_len);

             con.put("\b \b"_c);
            }
          else
            {
             con.put('\b');

             return false;
            }
         }
        break;

        default:
         {
          if( arg_len+SymbolLen(ch)<=MaxArgLen && CharIsPrintable(ch) )
            {
             arg_len=PutSymbol(arg,arg_len,ch);

             con.put(ch);
            }
         }
       }
    }
 }

template <ReadConType ReadCon,ulen MaxArgLen>
template <class ... SS>
CmdInputCon<ReadCon,MaxArgLen>::CmdInputCon(CmdInput::Target &target,StrLen prompt_str_,SS && ... ss)
 : input(target),
   prompt_str(prompt_str_),
   bad_char('?'),
   con( std::forward<SS>(ss)... )
 {
 }

template <ReadConType ReadCon,ulen MaxArgLen>
CmdInputCon<ReadCon,MaxArgLen>::~CmdInputCon()
 {
 }

template <ReadConType ReadCon,ulen MaxArgLen>
template <class ... SS>
void CmdInputCon<ReadCon,MaxArgLen>::command(SS && ... ss)
 {
  con.put(prompt_str);

  input.start();

  for(;;)
    {
     ReadConCode ch=con.get();

     switch( ToChar(ch) )
       {
        case ' ' :
         {
          auto result=input.finish();

          if( +result )
            {
             con.put(' ');

             if( inputArg() )
               {
                result(StrLen(arg,arg_len), std::forward<SS>(ss)... );

                return;
               }
             else
               {
                // do nothing
               }
            }
          else
            {
             // do nothing
            }
         }
        break;

        case '\r' : case '\n' :
         {
          auto result=input.finish();

          if( +result )
            {
             con.put("\r\n"_c);

             result(StrLen(), std::forward<SS>(ss)... );

             return;
            }
          else
            {
             // do nothing
            }
         }
        break;

        case '\t' :
         {
          auto result=input.complete();

          if( result.count==1 )
            {
             con.put(result.str);
             input.put(result.str);
            }
         }
        break;

        case '\b' :
         {
          if( input.back() )
            {
             con.put("\b \b"_c);
            }
         }
        break;

        default:
         {
          if( input.put(ch) )
            con.put(ch);
          else
            con.put(bad_char);
         }
       }
    }
 }

} // namespace CCore

#endif


