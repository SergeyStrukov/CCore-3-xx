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

  private:

   void add(StrLen file_name,FilePosType file_off,FilePosType file_len)
    {
     list.append_copy({file_name,file_off,file_len});
    }

   template <class AltFile>
   void fill(AltFile &file); // TODO

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

