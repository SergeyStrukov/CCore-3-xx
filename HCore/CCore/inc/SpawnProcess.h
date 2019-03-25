/* SpawnProcess.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_SpawnProcess_h
#define CCore_inc_SpawnProcess_h

#include <CCore/inc/Array.h>
#include <CCore/inc/List.h>
#include <CCore/inc/Cmp.h>

#include <CCore/inc/sys/SysSpawn.h>

namespace CCore {

/* classes */

class CmdLineParser;

class SpawnSlot;

class SpawnProcess;

/* class CmdLineParser */

class CmdLineParser
 {
   StrLen text;

  public:

   explicit CmdLineParser(StrLen text_) : text(text_) {}

   StrLen next();
 };

/* class SpawnSlot */

class SpawnSlot : NoCopy
 {
   Sys::SpawnChild sys_spawn;

   int state = 0 ;

   friend class SpawnProcess;

  public:

   SpawnSlot() noexcept;

   ~SpawnSlot();

   int wait();

   bool clean()
    {
     if( state==2 ) return false;

     state=0;

     return true;
    }
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
   char *exe_name = 0 ;

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

   bool used = false ;

  private:

   char ** buildArgv();

   char ** buildEnvp();

  public:

   SpawnProcess(StrLen wdir,StrLen exe_name);

   ~SpawnProcess();

   void addArg(StrLen str);

   void addCmdline(StrLen cmdline);

   void addEnv(StrLen name,StrLen value);

   void addEnv(StrLen str);

   void spawn(SpawnSlot &slot);
 };

} // namespace CCore

#endif

