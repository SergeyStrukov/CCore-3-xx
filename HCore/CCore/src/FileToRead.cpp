/* FileToRead.cpp */
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

#include <CCore/inc/FileToRead.h>

#include <CCore/inc/RawFileToRead.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* class DefBinFileToRead::Base */

class DefBinFileToRead::Base : public BinFileToReadBase
 {
   InitExitObject<AltFileToRead> file;

  public:

   Base() : file() {}

   ~Base()
    {
     if( is_opened ) file.exit();
    }

   virtual void open(StrLen file_name,FileOpenFlags oflags)
    {
     if( is_opened )
       {
        Printf(Exception,"CCore::DefBinFileToRead::Base::open(#.q;,#;) : file is already opened",file_name,oflags);
       }
     else
       {
        file.init(file_name,oflags);

        is_opened=true;

        file_len=file->getLen();
       }
    }

   virtual void close()
    {
     if( is_opened )
       {
        reset();

        file.exit();
       }
     else
       {
        Printf(NoException,"CCore::DefBinFileToRead::Base::close(...) : file is not opened");
       }
    }

   virtual ulen read(FilePosType off,uint8 *buf,ulen len)
    {
     if( !is_opened )
       {
        Printf(Exception,"CCore::DefBinFileToRead::Base::read(...) : file is not opened");
       }

     return file->read(off,buf,len);
    }

   virtual void read_all(FilePosType off,uint8 *buf,ulen len)
    {
     if( !is_opened )
       {
        Printf(Exception,"CCore::DefBinFileToRead::Base::read_all(...) : file is not opened");
       }

     file->read_all(off,buf,len);
    }
 };

/* class DefBinFileToRead */

DefBinFileToRead::DefBinFileToRead()
 : BinFileToRead(new Base())
 {
 }

DefBinFileToRead::~DefBinFileToRead()
 {
 }

/* class VolumeBinFileToRead::Base */

class VolumeBinFileToRead::Base : public BinFileToReadBase
 {
   Volume<AltFileToRead> vol;

   InitExitObject<VolumeFile<AltFileToRead> > file;

  public:

   Base(StrLen file_name,FileOpenFlags oflags) : vol(file_name,oflags),file() {}

   ~Base()
    {
     if( is_opened ) file.exit();
    }

   virtual void open(StrLen file_name,FileOpenFlags oflags)
    {
     if( is_opened )
       {
        Printf(Exception,"CCore::DefBinFileToRead::Base::open(#.q;,#;) : file is already opened",file_name,oflags);
       }
     else
       {
        file.init(vol,file_name);

        is_opened=true;

        file_len=file->getLen();
       }
    }

   virtual void close()
    {
     if( is_opened )
       {
        reset();

        file.exit();
       }
     else
       {
        Printf(NoException,"CCore::VolumeBinFileToRead::Base::close(...) : file is not opened");
       }
    }

   virtual ulen read(FilePosType off,uint8 *buf,ulen len)
    {
     if( !is_opened )
       {
        Printf(Exception,"CCore::VolumeBinFileToRead::Base::read(...) : file is not opened");
       }

     return file->read(off,buf,len);
    }

   virtual void read_all(FilePosType off,uint8 *buf,ulen len)
    {
     if( !is_opened )
       {
        Printf(Exception,"CCore::VolumeBinFileToRead::Base::read_all(...) : file is not opened");
       }

     file->read_all(off,buf,len);
    }
 };

/* class VolumeBinFileToRead */

VolumeBinFileToRead::VolumeBinFileToRead(StrLen file_name,FileOpenFlags oflags)
 : BinFileToRead(new Base(file_name,oflags))
 {
 }

VolumeBinFileToRead::~VolumeBinFileToRead()
 {
 }

} // namespace CCore

