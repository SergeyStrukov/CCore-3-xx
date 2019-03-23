/* SpawnProcess.h */
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

#ifndef App_SpawnProcess_h
#define App_SpawnProcess_h

#include <CCore/inc/String.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Cmp.h>

namespace App {

/* using */

using namespace CCore;

namespace VMake {

/* classes */

class CmdLineParser;

class SpawnProcess;

/* class CmdLineParser */

class CmdLineParser
 {
   StrLen text;

  public:

   explicit CmdLineParser(StrLen text_) : text(text_) {}

   StrLen next();
 };

/* class SpawnProcess */

class SpawnProcess : NoCopy
 {
   class Pool : NoCopy
    {
      struct Node
       {
        SLink<Node> link;
       };

      static constexpr ulen Delta = Align(sizeof (Node)) ;
      static constexpr ulen MaxLen = AlignDown(MaxULen)-Delta ;

      using Algo = SLink<Node>::LinearAlgo<&Node::link> ;

     private:

      ulen block_len;

      Algo::Top list;

      Place<void> block;
      Place<void> cur;
      ulen avail;

     private:

      Place<void> allocBlock(ulen alloc_len);

      void newBlock();

     private:

      void * allocMem(ulen len);

      struct Out
       {
        char *ptr;

        explicit Out(char *ptr_) : ptr(ptr_) {}

        Out & operator += (StrLen str)
         {
          str.copyTo(ptr);

          ptr+=str.len;

          return *this;
         }
       };

      template <class ... TT>
      char * catStrLen(TT ... tt)
       {
        ulen len=LenAdd( tt.len ... );
        char *base=alloc<char>(len);

        Out out(base);

        ( out += ... += tt );

        return base;
       }

     public:

      Pool();

      ~Pool();

      template <PODType T>
      T * alloc(ulen len)
       {
        return static_cast<T *>(allocMem(LenOf(len,sizeof (T))));
       }

      template <class ... TT>
      char * cat(TT ... tt)
       {
        return catStrLen( StrLen(tt)... ,"\0"_c);
       }
    };

  private:

   Pool pool;

   char *wdir = 0 ;
   char *exe_name;

   DynArray<char *> args;

   struct EnvRec
    {
     char *str;
     ulen name_len;
     ulen ind;

     EnvRec(char *str_,ulen name_len_,ulen ind_) : str(str_),name_len(name_len_),ind(ind_) {}

     StrLen getName() const { return StrLen(str,name_len); }

     bool operator < (const EnvRec &obj) const
      {
       if( CmpResult cmp=StrCmp(getName(),obj.getName()) ) return cmp<0;

       return ind<obj.ind;
      }

     bool operator != (const EnvRec &obj) const { return StrCmp(getName(),obj.getName())!=0; }
    };

   DynArray<EnvRec> envs;

   int pid = 0 ;

  public:

   SpawnProcess(StrLen wdir,StrLen exe_name);

   ~SpawnProcess();

   void addArg(StrLen str);

   void addCmdline(StrLen cmdline);

   void addEnv(StrLen name,StrLen value);

   void addEnv(StrLen str);

   void spawn();

   int wait();
 };

} // namespace VMake

} // namespace App

#endif
