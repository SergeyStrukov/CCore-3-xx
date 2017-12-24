/* FileBoss.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/FileBoss.h>

#include <CCore/inc/FileSystem.h>
#include <CCore/inc/Path.h>

namespace CCore {
namespace Video {

namespace Private_FileBoss {

class DefBoss : public FileBossBase
 {
   FileSystem fs;

  public:

   DefBoss() {}

   virtual ~DefBoss() {}

   // AbstractFileBoss

   virtual FileType getFileType(StrLen path)
    {
     return fs.getFileType(path);
    }

   virtual StrLen pathOf(StrLen path,char buf[MaxPathLen+1])
    {
     return fs.pathOf(path,buf);
    }

   virtual void enumDir(StrLen dir_name,Function<void (StrLen name,FileType type)> func)
    {
     FileSystem::DirCursor cur(fs,dir_name);

     cur.apply( [func] (StrLen name,FileType type) { func(name,type); } );
    }

   virtual void createDir(StrLen dir_name)
    {
     char buf[MaxPathLen+1];

     StrLen path=fs.pathOf(dir_name,buf);

     WalkPath(path, [this] (StrLen dir)
                           {
                            if( fs.getFileType(dir)==FileType_none )
                              {
                               fs.createDir(dir);
                              }

                           } );
    }

   virtual void deleteDir(StrLen dir_name)
    {
     fs.deleteDir(dir_name,false);
    }

   virtual StrLen getHitDirFile() const
    {
     return "/HitDirs.ddl"_c;
    }
 };

DefBoss Object CCORE_INITPRI_3 ;

} // namespace Private_FileBoss

using namespace Private_FileBoss;

/* class FileBoss */

FileBoss::FileBoss() noexcept
 : ptr(&Object)
 {
  ptr->incRef();
 }

} // namespace Video
} // namespace CCore

