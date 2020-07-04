/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Volume 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/MakeString.h>
#include <CCore/inc/MakeFileName.h>
#include <CCore/inc/Path.h>

#include <CCore/inc/RawFileToRead.h>
#include <CCore/inc/Volume.h>

#include <CCore/inc/DirTreeRun.h>
#include <CCore/inc/ElementPool.h>

#include <CCore/inc/BinaryFile.h>
#include <CCore/inc/FileSystem.h>

namespace App {

/* using */

using namespace CCore;

/* List() */

void List(StrLen file_name)
 {
  Printf(Con,"list #.q;\n\n",file_name);

  Volume<AltFileToRead> vol(file_name);

  for(ulen i=0,count=vol.getCount(); i<count ;i++)
    {
     Printf(Con,"#;\n",vol.getName(i));
    }

  Putch(Con,'\n');
 }

/* Pack() */

class Proc : NoCopy
 {
   struct Rec
    {
     StrLen file_path;
     StrLen file_name;
    };

  private:

   ulen off = 0 ;

   ElementPool pool;

   DynArray<Rec> files;

  public:

   Proc() {}

   ~Proc() {}

   PtrLen<const Rec> getList() const { return Range(files); }

   // proc interface

   using DataType = StrLen ;

   DataType * dir(StrLen)
    {
     StrLen name=""_c;

     return pool.create<StrLen>(name);
    }

   DataType * dir(StrLen,StrLen name,DataType *data)
    {
     StrLen dir_name=pool.cat(*data,"/"_c,name);

     return pool.create<StrLen>(dir_name);
    }

   void file(StrLen path,StrLen name,DataType *data)
    {
     StrLen file_path=pool.cat(path,"/"_c,name);
     StrLen file_name=pool.cat(*data,"/"_c,name);

     files.append_copy({file_path,file_name});
    }

   void enddir(StrLen,StrLen,DataType *) {}
 };

struct Header
 {
  uint32 count;
  uint32 names_off;
  uint32 names_len;

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<uint32,uint32,uint32>::SaveLoadLen };

  template <SaveDevType Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(count,names_off,names_len);
   }
 };

struct Entry
 {
  uint32 name_off;
  uint32 name_len;
  FilePosType body_off;
  FilePosType body_len;

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<uint32,uint32,FilePosType,FilePosType>::SaveLoadLen };

  template <SaveDevType Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(name_off,name_len,body_off,body_len);
   }
 };

uint32 Add(uint32 a,ulen b)
 {
  if( b>MaxUInt<uint32>-a )
    {
     Printf(Exception,"App::Add(#;,#;) : overflow",a,b);
    }

  return a+(uint32)b;
 }

uint32 AddMul(uint32 a,uint32 b,ulen c)
 {
  if( b && c>(MaxUInt<uint32>-a)/b )
    {
     Printf(Exception,"App::AddMul(#;,#;,#;) : overflow",a,b,c);
    }

  return uint32( a+b*c );
 }

FilePosType GetFileLen(StrLen file_name)
 {
  AltFileToRead file(file_name);

  return file.getLen();
 }

template <class File>
void CopyFile(File &file,SaveDevType &dev)
 {
  static constexpr ulen BufLen = 64_KByte ;

  DynArray<uint8> buf(BufLen);

  FilePosType off=0;
  FilePosType file_len=file.getLen();

  uint8 *ptr=buf.getPtr();

  while( off<file_len )
    {
     ulen len=(ulen)Min<FilePosType>(BufLen,file_len-off);

     file.read_all(off,ptr,len);

     dev.put(ptr,len);

     off+=len;
    }
 }

void Pack(StrLen dir_name,StrLen file_name)
 {
  Printf(Con,"pack #.q; -> #.q;\n\n",dir_name,file_name);

  // scan

  Proc proc;
  DirTreeRun run(dir_name);

  run.apply(proc);

  // pack

  auto list=proc.getList();

  uint32 names_len=0;

  for(auto r : list )
    {
     Printf(Con,"#; : #;\n",r.file_path,r.file_name);

     names_len=Add(names_len,r.file_name.len);
    }

  BinaryFile dev(file_name,Open_ToWrite|Open_AutoDelete);

   // header

  Header header;

  header.count=(uint32)list.len;
  header.names_off=AddMul(Header::SaveLoadLen,Entry::SaveLoadLen,list.len);
  header.names_len=names_len;

  dev(header);

   // entry

  uint32 off=0;
  FilePosType file_off=(FilePosType)header.names_off+header.names_len;

  for(auto r : list )
    {
     FilePosType file_len=GetFileLen(r.file_path);

     Entry entry;

     entry.name_off=off;
     entry.name_len=(uint32)r.file_name.len;

     off+=entry.name_len;

     entry.body_off=file_off;
     entry.body_len=file_len;

     file_off+=file_len;

     dev(entry);
    }

   // name

  for(auto r : list )
    {
     SaveRange(Mutate<const uint8>(r.file_name),dev);
    }

   // body

  for(auto r : list )
    {
     AltFileToRead file(r.file_path);

     CopyFile(file,dev);
    }

  dev.preserveFile();

  Putch(Con,'\n');
 }

/* Unpack() */

void CreateDir(StrLen path)
 {
  FileSystem fs;

  if( fs.getFileType(path)==FileType_none )
    {
     Printf(Con,"create dir #.q;\n",path);

     fs.createDir(path);
    }
 }

void CreatePath(StrLen path)
 {
  WalkPath(path, [path] (StrLen sub) { if( sub.len<path.len ) CreateDir(sub); } );
 }

void Unpack(StrLen file_name,StrLen dir_name)
 {
  Printf(Con,"unpack #.q; -> #.q;\n\n",file_name,dir_name);

  Volume<AltFileToRead> vol(file_name);

  for(ulen i=0,count=vol.getCount(); i<count ;i++)
    {
     StrLen file_name=vol.getName(i);

     MakeFileName temp(dir_name,file_name.part(1));

     StrLen file_path=temp.get();

     Printf(Con,"#; : #;\n",file_name,file_path);

     VolumeFile<AltFileToRead> file(vol,i);

     CreatePath(file_path);

     BinaryFile dev(file_path,Open_ToWrite|Open_AutoDelete);

     CopyFile(file,dev);

     dev.preserveFile();
    }

  Putch(Con,'\n');
 }

/* Main() */

void Main(int argc,const char *argv[],StrLen cmd)
 {
  if( cmd.equal("-l"_c) )
    {
     if( argc!=3 )
       {
        Printf(Exception,"App::Main(...) : bad arguments number");
       }

     StrLen file_name=argv[2];

     List(file_name);

     return;
    }

  if( cmd.equal("-a"_c) )
    {
     StrLen dir_name=argv[2];

     StrLen file_name;

     MakeString<MaxPathLen> temp;

     if( argc==3 )
       {
        if( !temp.add(dir_name,".vol"_c) )
          {
           Printf(Exception,"App::Main(...) : too long file name");
          }

        file_name=temp.get();
       }
     else if( argc==4 )
       {
        file_name=argv[3];
       }
     else
       {
        Printf(Exception,"App::Main(...) : bad arguments number");
       }

     Pack(dir_name,file_name);

     return;
    }

  if( cmd.equal("-x"_c) )
    {
     StrLen file_name=argv[2];

     StrLen dir_name;

     if( argc==3 )
       {
        StrLen ext=SuffixExt(file_name);

        if( !ext || ext.equal("."_c) )
          {
           Printf(Exception,"App::Main(...) : no file extension");
          }

        dir_name=file_name.inner(0,ext.len);
       }
     else if( argc==4 )
       {
        dir_name=argv[3];
       }
     else
       {
        Printf(Exception,"App::Main(...) : bad arguments number");
       }

     Unpack(file_name,dir_name);

     return;
    }

  Printf(Exception,"App::Main(...) : bad command");
 }

int Main(int argc,const char *argv[])
 {
  if( argc<3 )
    {
     if( argc==1 )
       {
        Putobj(Con,"Usage: CCore-Volume -a <src-dir> [<vol-file>]\n");
        Putobj(Con,"OR     CCore-Volume -x <vol-file> [<dst-dir>]\n");
        Putobj(Con,"OR     CCore-Volume -l <vol-file>\n\n");

        return 1;
       }

     Printf(Exception,"App::Main(...) : bad arguments number");
    }

  Main(argc,argv,argv[1]);

  return 0;
 }

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char *argv[])
 {
  try
    {
     ReportException report;
     int ret;

     {
      Putobj(Con,"--- Volume 1.00 ---\n--- Copyright (c) 2018 Sergey Strukov. All rights reserved. ---\n\n");

      ret=Main(argc,argv);
     }

     report.guard();

     return ret;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

