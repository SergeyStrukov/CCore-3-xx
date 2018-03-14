/* Path.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Path.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* functions */

StrLen PrefixPath(StrLen file_name)
 {
  SplitPath split1(file_name);
  SplitPathName split2(split1.path);

  ulen len=split2.path.len;

  if( !len && !!split2 ) len=1;

  return file_name.prefix(split1.dev.len+len);
 }

StrLen SuffixExt(StrLen file_name)
 {
  SplitPath split1(file_name);
  SplitName split2(split1.path);
  SplitExt split3(split2.name);

  return split3.ext;
 }

/* struct PathBase */

void PathBase::TurnSlash(PtrLen<char> name)
 {
  for(char &ch : name ) if( IsSlash(ch) ) ch='/';
 }

/* struct SplitDev */

SplitDev::SplitDev(StrLen dev_path_)
 {
  ForwardScan<IsColon,ToPrefix> scan(dev_path_);

  dev=scan.prefix;
  dev_path=scan.suffix;
  no_dev=scan.no;
 }

/* struct SplitPath */

SplitPath::SplitPath(StrLen dev_path)
 {
  BackwardScan<IsColon,ToPrefix> scan(dev_path);

  dev=scan.prefix;
  path=scan.suffix;
  no_dev=scan.no;
 }

/* struct SplitDir */

SplitDir::SplitDir(StrLen path_)
 {
  ForwardScan<IsSlash,ToPrefix> scan(path_);

  dir=scan.prefix;
  path=scan.suffix;
  no_path=scan.no;
 }

/* struct SplitName */

SplitName::SplitName(StrLen path_)
 {
  BackwardScan<IsSlash,ToPrefix> scan(path_);

  path=scan.prefix;
  name=scan.suffix;
  no_path=scan.no;
 }

/* struct SplitFullExt */

SplitFullExt::SplitFullExt(StrLen name_)
 {
  ForwardScan<IsDot,ToSuffix> scan(name_);

  name=scan.prefix;
  ext=scan.suffix;
  no_ext=scan.no;
 }

/* struct SplitExt */

SplitExt::SplitExt(StrLen name_)
 {
  BackwardScan<IsDot,ToSuffix> scan(name_);

  name=scan.prefix;
  ext=scan.suffix;
  no_ext=scan.no;
 }

/* struct SplitDevName */

SplitDevName::SplitDevName(StrLen dev_path_)
 {
  ForwardScan<IsColon,ToPrefixDel> scan(dev_path_);

  dev_name=scan.prefix;
  dev_path=scan.suffix;
  no_dev=scan.no;
 }

/* struct SplitDirName */

SplitDirName::SplitDirName(StrLen path_)
 {
  ForwardScan<IsSlash,ToPrefixDel> scan(path_);

  dir_name=scan.prefix;
  path=scan.suffix;
  no_path=scan.no;
 }

/* struct SplitPathName */

SplitPathName::SplitPathName(StrLen path_)
 {
  BackwardScan<IsSlash,ToPrefixDel> scan(path_);

  path=scan.prefix;
  name=scan.suffix;
  no_path=scan.no;
 }

/* class Path */

void Path::push(ulen len)
 {
  if( stack_len<StackLen )
    {
     stack[stack_len++]=len;
    }
  else
    {
     auto r=Range(stack);

     for(; r.len>=2 ;++r) r[0]=r[1];

     r[0]=len;
    }
 }

void Path::pop()
 {
  if( stack_len>1 )
    {
     stack_len--;
    }
  else
    {
     ulen len=stack[0];

     for(len-=2; buf[len]!='/' ;len--);

     stack[0]=len+1;
    }
 }

Path::Path(BeginType bt)
 {
  if( bt==BeginEmpty )
    {
     buf_len=0;
    }
  else
    {
     buf[0]='/';
     buf_len=1;
    }

  init(buf_len);
 }

Path::Path(StrLen dev_name)
 {
  if( dev_name.len>=MaxPathLen-2 )
    {
     Printf(Exception,"CCore::Path::Path(...) : too long dev_name");
    }

  dev_name.copyTo(buf);

  buf[dev_name.len]=':';
  buf[dev_name.len+1]='/';

  buf_len=dev_name.len+2;

  init(buf_len);
 }

void Path::root()
 {
  buf_len=root_len;

  init();
 }

void Path::rootDir()
 {
  buf_len=root_len+1;

  buf[root_len]='.';

  init();
 }

void Path::add(StrLen name)
 {
  if( !name )
    {
     Printf(Exception,"CCore::Path::add(...) : empty name");
    }

  if( IsDotDot(name) )
    {
     back();
    }
  else
    {
     ulen len=top();

     if( buf_len-len==1 && buf[len]=='.' )
       {
        if( name.len>MaxPathLen-len )
          {
           Printf(Exception,"CCore::Path::add(...) : too long path");
          }

        name.copyTo(buf+len);

        buf_len=len+name.len;
       }
     else if( buf_len>root_len )
       {
        if( name.len>=MaxPathLen-buf_len )
          {
           Printf(Exception,"CCore::Path::add(...) : too long path");
          }

        buf[buf_len]='/';

        push(buf_len+1);

        name.copyTo(buf+buf_len+1);

        buf_len+=name.len+1;
       }
     else
       {
        if( name.len>MaxPathLen-buf_len )
          {
           Printf(Exception,"CCore::Path::add(...) : too long path");
          }

        name.copyTo(buf+buf_len);

        buf_len+=name.len;
       }
    }
 }

void Path::back()
 {
  ulen len=top();

  if( len>root_len )
    {
     buf_len=len-1;

     pop();
    }
  else
    {
     if( isRoot() || isRootDir() )
       {
        Printf(Exception,"CCore::Path::back() : at root");
       }

     rootDir();
    }
 }

void Path::addPath(StrLen path)
 {
  if( !path ) return;

  if( IsSlash(*path) )
    {
     rootDir();

     ++path;
    }

  while( +path )
    {
     SplitDirName split(path);

     if( !split )
       {
        add(path);

        break;
       }
     else
       {
        add(split.dir_name);

        path=split.path;
       }
    }
 }

void Path::copyPath(const Path &path)
 {
  if( &path==this ) return;

  buf_len=path.buf_len;

  Range(buf,buf_len).copy(path.buf);

  root_len=path.root_len;

  stack_len=path.stack_len;

  Range(stack,stack_len).copy(path.stack);
 }

} // namespace CCore


