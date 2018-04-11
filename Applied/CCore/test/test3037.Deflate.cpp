/* test3037.Deflate.cpp */
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
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Deflate.h>
#include <CCore/inc/PlatformRandom.h>

#include <CCore/inc/FileToMem.h>
#include <CCore/inc/FileSystem.h>
#include <CCore/inc/MakeFileName.h>

namespace App {

namespace Private_3037 {

/* Rat() */

unsigned Rat(ulen a,ulen b)
 {
  if( !b ) return 100;

  return (a*100)/b;
 }

/* class Transform<T> */

template <class T>
class Transform : public Funchor_nocopy
 {
   PtrLen<const uint8> data;

   T work;

   DynArray<uint8> result;

  private:

   void out(PtrLen<const uint8> r)
    {
     result.extend_copy(r);
    }

   Function<void (PtrLen<const uint8>)> function_out() { return FunctionOf(this,&Transform::out); }

  public:

   template <class ... SS>
   Transform(PtrLen<const uint8> data_,SS && ... ss)
    : data(data_),
      work(function_out(), std::forward<SS>(ss)... )
    {
    }

   ~Transform()
    {
    }

   PtrLen<const uint8> getResult() const { return Range(result); }

   void run(PlatformRandom &random)
    {
     ulen off=0;

     while( off<data.len )
       {
        ulen len=Min<ulen>(data.len-off,random.select(1000));

        work.put(data.part(off,len));

        off+=len;
       }

     work.complete();
    }
 };

/* Test() */

void Test(StrLen dir,StrLen file_name)
 {
  PlatformRandom random;

  MakeFileName path(dir,file_name);
  FileToMem file(path.get());

  auto data=Range(file);

  // 1

  Deflate::Param param;

  //param.level=Deflate::MaxLevel;

  Transform<Deflate::Deflator> zip(data,param);

  zip.run(random);

  auto zipped=zip.getResult();

  // 2

  Transform<Deflate::Inflator> unzip(zipped);

  unzip.run(random);

  auto unzipped=unzip.getResult();

  // 3

  if( data.equal(unzipped) )
    {
     Printf(Con,"#; : #; -> #; (#; %)\n",file_name,data.len,zipped.len,Rat(zipped.len,data.len));
    }
  else
    {
     Printf(Exception,"#; : failed",file_name);
    }
 }

} // namespace Private_3037

using namespace Private_3037;

/* Testit<3037> */

template<>
const char *const Testit<3037>::Name="Test3037 Deflate";

template<>
bool Testit<3037>::Main()
 {
  //StrLen dir="../../../html";

  StrLen dir="../.test-obj";

  FileSystem fs;
  FileSystem::DirCursor cur(fs,dir);

  while( cur.next() )
    {
     if( cur.getFileType()==FileType_file )
       {
        StrLen file_name=cur.getFileName();

        Test(dir,file_name);
       }
    }

  return true;
 }

} // namespace App

