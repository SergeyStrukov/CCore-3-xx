/* Volume.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_Volume_h
#define CCore_inc_Volume_h

#include <CCore/inc/GenFile.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/algon/BinarySearch.h>
#include <CCore/inc/SaveLoad.h>

namespace CCore {

/* guard functions */

void GuardReadOutOfBound();

/* classes */

class VolumeDir;

template <class AltFile> class Volume;

template <class AltFile> class VolumeFile;

/* class VolumeDir */

class VolumeDir : NoCopy
 {
  public:

   struct Rec
    {
     StrLen file_name;
     FilePosType file_off;
     FilePosType file_len;

     bool operator < (const Rec &obj) const { return StrLess(file_name,obj.file_name); }
    };

  private:

   DynArray<Rec> list;

   DynArray<char> names;

  private:

   void add(StrLen file_name,FilePosType file_off,FilePosType file_len)
    {
     list.append_copy({file_name,file_off,file_len});
    }

   struct Header
    {
     uint32 count;
     uint32 names_off;
     uint32 names_len;

     // save/load object

     enum { SaveLoadLen = SaveLenCounter<uint32,uint32,uint32>::SaveLoadLen };

     template <LoadDevType Dev>
     void load(Dev &dev)
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

     template <LoadDevType Dev>
     void load(Dev &dev)
      {
       dev.template use<BeOrder>(name_off,name_len,body_off,body_len);
      }
    };

   template <class AltFile>
   static Header ReadHeader(AltFile &file)
    {
     uint8 temp[Header::SaveLoadLen];

     file.read_all(0,temp,Header::SaveLoadLen);

     BufGetDev dev(temp);

     Header ret;

     dev(ret);

     return ret;
    }

   template <UIntType UInt,UIntType UInt1>
   static void CheckBounds(UInt off,UInt len,UInt1 total);

   Rec makeRec(Entry entry,FilePosType file_len);

   template <class AltFile>
   void fill(AltFile &file)
    {
     Header header=ReadHeader(file);

     list.erase();
     list.extend_default(header.count);

     names.erase();
     names.extend_raw(header.names_len);

     DynArray<uint8> dir(DoRaw(LenOf(header.count,Entry::SaveLoadLen)));

     file.read_all(Header::SaveLoadLen,dir.getPtr(),dir.getLen());

     file.read_all(header.names_off,MutatePtr<uint8>(names.getPtr()),names.getLen());

     BufGetDev dev(dir.getPtr());

     FilePosType file_len=file.getLen();

     for(Rec &rec : list )
       {
        Entry entry;

        dev(entry);

        rec=makeRec(entry,file_len);
       }
    }

  public:

   VolumeDir();

   ~VolumeDir();

   template <class AltFile>
   void prepare(AltFile &file)
    {
     fill(file);

     Sort(Range(list));
    }

   Rec find(StrLen file_name) const;
 };

/* class Volume<AltFile> */

template <class AltFile>
class Volume : NoCopy
 {
   AltFile file;

   VolumeDir dir;

  public:

   Volume(StrLen file_name,FileOpenFlags oflags=Open_Read)
    : file(file_name,oflags)
    {
     dir.prepare(file);
    }

   ~Volume()
    {
    }

   struct Result
    {
     AltFile &file;
     FilePosType file_off;
     FilePosType file_len;
    };

   Result open(StrLen file_name)
    {
     auto rec=dir.find(file_name);

     return {file,rec.file_off,rec.file_len};
    }
 };

/* class VolumeFile<AltFile> */

template <class AltFile>
class VolumeFile : NoCopy
 {
   AltFile &file;
   FilePosType file_off;
   FilePosType file_len;

  private:

   template <class Result>
   VolumeFile(Result result) : file(result.file),file_off(result.file_off),file_len(result.file_len) {}

   FilePosType getCap(FilePosType off) const { return (off>file_len)?0:(file_len-off); }

   void do_read(FilePosType off,uint8 *buf,ulen len)
    {
     file.read_all(file_off+off,buf,len);
    }

  public:

   VolumeFile(Volume<AltFile> &vol,StrLen file_name)
    : VolumeFile(vol.open(file_name))
    {
    }

   ~VolumeFile()
    {
    }

   FilePosType getLen() const { return file_len; }

   ulen read(FilePosType off,uint8 *buf,ulen len)
    {
     CapDown(len,getCap(off));

     if( !len ) return 0;

     do_read(off,buf,len);

     return len;
    }

   void read_all(FilePosType off,uint8 *buf,ulen len)
    {
     if( len>getCap(off) ) GuardReadOutOfBound();

     if( !len ) return;

     do_read(off,buf,len);
    }
 };

} // namespace CCore

#endif

