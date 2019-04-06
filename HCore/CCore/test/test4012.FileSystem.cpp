/* test4012.FileSystem.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: HCore Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/FileSystem.h>

namespace App {

namespace Private_4012 {

/* ShowDir() */

void ShowDir(FileSystem &fs,StrLen dir_name)
 {
  FileSystem::DirCursor cur(fs,dir_name);

  Printf(Con,"--- #; ---\n\n",dir_name);

#if 0

  while( cur.next() )
    {
     Printf(Con,"#; #;\n",cur.getFileName(),cur.getFileType());
    }

#else

  cur.apply( [] (StrLen file_name,FileType file_type) { Printf(Con,"#; #;\n",file_name,file_type); } );

#endif

  Printf(Con,"\n---\n\n");
 }

/* test1() */

void test1()
 {
  ReportException report;

  FileSystem fs;

  // getFileType()

  Printf(Con,". is #;\n",fs.getFileType("."));
  Printf(Con,".. is #;\n",fs.getFileType(".."));
  Printf(Con,"../.obj is #;\n",fs.getFileType("../.obj"));
  Printf(Con,"main.cpp is #;\n",fs.getFileType("main.cpp"));

  char temp[MaxPathLen+1];

  Printf(Con,"main.cpp is #;\n",fs.pathOf("main.cpp"_c,temp));

  Printf(Con,"nofile.txt is #;\n",fs.getFileType("nofile.txt"));

  // createFile()

  fs.createFile("new_file.txt");

  try { fs.createFile("new_file.txt"); } catch(CatchType) {}

  // deleteFile()

  fs.deleteFile("new_file.txt");

  // createDir()

  fs.createDir("new_dir");

  try { fs.createDir("new_dir"); } catch(CatchType) {}

  // deleteDir()

  fs.deleteDir("new_dir",false);

  // remove()

  fs.createFile("new_file.txt");
  fs.createDir("new_dir");

  fs.remove("new_file.txt");
  fs.remove("new_dir");

  try { fs.remove("../.obj"); } catch(CatchType) {}
  try { fs.remove("nodir"); } catch(CatchType) {}

  // rename()

  fs.createDir("new_dir");
  fs.createFile("new_dir/new_file.txt");

  fs.rename("new_dir","new_dir2",false);
  fs.rename("new_dir2/new_file.txt","new_file.txt",false);

  fs.createFile("new_file2.txt");
  fs.rename("new_file.txt","new_file2.txt",true);

  fs.remove("new_file2.txt");
  fs.remove("new_dir2");

  // DirCursor

  ShowDir(fs,".");
  ShowDir(fs,"..");

  // deleteDir() recursive

  fs.createDir("new_dir");
  fs.createFile("new_dir/new_file");

  fs.createDir("new_dir/new_dir1");
  fs.createFile("new_dir/new_dir1/new_file");

  fs.deleteDir("new_dir",true);
 }

/* test2() */

void test2()
 {
  FileSystem fs;

  ShowDir(fs,"E:/");
  ShowDir(fs,"E:.");
  ShowDir(fs,"E:");
 }

} // namespace Private_4012

using namespace Private_4012;

/* Testit<4012> */

template<>
const char *const Testit<4012>::Name="Test4012 FileSystem";

template<>
bool Testit<4012>::Main()
 {
  //test1();
  test2();

  return true;
 }

} // namespace App

