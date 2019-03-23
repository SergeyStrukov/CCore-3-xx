/* SpawnProcess.cpp */
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

#include <inc/SpawnProcess.h>

#include <CCore/inc/Sort.h>
#include <CCore/inc/CharProp.h>

#include <CCore/inc/algon/SortUnique.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <ctype.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

namespace App {

namespace VMake {

/* class CmdLineParser */

StrLen CmdLineParser::next()
 {
  for(; +text && CharIsSpace(*text) ;++text);

  if( !text ) return Empty;

  switch( char ch=*text )
    {
     case '"' :
     case '\'' :
      {
       ++text;

       StrLen line=text;

       for(; +text && *text!=ch ;++text);

       StrLen ret=line.prefix(text);

       if( +text ) ++text;

       return ret;
      }
     break;

     default:
      {
       StrLen line=text;

       for(; +text && !CharIsSpace(*text) ;++text);

       return line.prefix(text);
      }
    }
 }

/* class SpawnProcess */

inline bool CharIsDev(char ch)
 {
  return ( ch>='a' && ch<='z' ) || ( ch>='A' && ch<='Z' ) ;
 }

inline char LowerDev(char ch)
 {
  return (char)tolower(ch);
 }

SpawnProcess::SpawnProcess(FileSystem &fs,StrLen wdir,StrLen exe_name_)
 : args(DoReserve,100),
   envs(DoReserve,100)
 {
  exe_name=StringSum(exe_name_,"\0"_c);

  if( +wdir )
    {
     char temp[MaxPathLen+1];

     StrLen path=fs.pathOf(wdir,temp);

     if( +path )
       {
        char ch=*path;

        if( ch=='/' )
          {
           addEnv("PWD"_c,path);
          }
        else if( CharIsDev(ch) && ( path.len>=2 && path[1]==':' ) )
          {
           char dev[3]={'!',ch,':'};

           addEnv(Range(dev),path);

           char cygdev[1]={LowerDev(ch)};

           String cygpath=StringSum("/cygdrive/"_c,Range(cygdev),path.part(2));

           addEnv("PWD"_c,Range(cygpath));
          }
       }
    }
 }

SpawnProcess::~SpawnProcess()
 {
 }

void SpawnProcess::addArg(StrLen str)
 {
  args.append_fill(StringSum(str,"\0"_c));
 }

void SpawnProcess::addCmdline(StrLen cmdline)
 {
  CmdLineParser parser(cmdline);

  for(;;)
    {
     StrLen str=parser.next();

     if( !str ) break;

     addArg(str);
    }
 }

void SpawnProcess::addEnv(StrLen name,StrLen value)
 {
  ulen ind=envs.getLen();

  envs.append_fill(StringSum(name,"="_c,value,"\0"_c),name.len,ind);
 }

void SpawnProcess::addEnv(StrLen str)
 {
  for(StrLen t=str; +t ;++t)
    if( *t=='=' )
      {
       ulen name_len=str.len-t.len;
       ulen ind=envs.getLen();

       envs.append_fill(StringSum(str,"\0"_c),name_len,ind);

       break;
      }
 }

void SpawnProcess::spawn()
 {
  DynArray<const char *> arglist;

  {
   arglist.reserve(arglist.getLen()+1);

   for(String &arg : args ) arglist.append_copy(arg.getPtr());

   arglist.append_copy(0);
  }

  DynArray<const char *> envlist;

  {
   for(auto e=environ; const char *zstr=(*e) ;e++) addEnv(zstr);

   auto list=Range(envs);

   envlist.reserve(list.len);

   Algon::SortThenApplyUnique(list, [&] (EnvRec &env) { envlist.append_copy(env.str.getPtr()); } );

   envlist.append_copy(0);
  }

  PrintFile out("spawn.txt");

  Printf(out,"#;\n\n",exe_name.getPtr());

  {
   auto p=(char *const *)arglist.getPtr();

   for(; auto s=(*p) ;p++) Printf(out,"#;\n",s);
  }

  Putch(out,'\n');

  {
   auto p=(char *const *)envlist.getPtr();

   for(; auto s=(*p) ;p++) Printf(out,"#;\n",s);
  }

  if( posix_spawnp(&pid,exe_name.getPtr(),0,0,(char *const *)arglist.getPtr(),environ/*(char *const *)envlist.getPtr()*/) )
    {
     Printf(Exception,"vmake : failed to spawn a process");
    }
  else
    {
     Printf(Con,"vmake : spawned #;\n",pid);
    }
 }

int SpawnProcess::wait()
 {
  int result=0;

  int ret=waitpid(pid,&result,0);

  Printf(Con,"pid = #; result = #;\n",ret,result);

  if( ret==-1 || ret!=pid ) return 1000;

  return result;
 }

} // namespace VMake

} // namespace App

