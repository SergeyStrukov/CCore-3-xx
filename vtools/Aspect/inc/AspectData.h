/* AspectData.h */
//----------------------------------------------------------------------------------------
//
//  Project: Aspect 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef AspectData_h
#define AspectData_h

#include <inc/ErrorText.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/MakeString.h>

namespace App {

/* functions */

bool IsRelPath(StrLen path);

bool SkipDir(StrLen name);

bool SkipFile(StrLen name);

/* classes */

struct DiffPath;

class RelPath;

class NormalPath;

//enum ItemStatus;

struct Counts;

struct CommonData;

struct FileData;

struct DirData;

struct ItemData;

class AspectData;

/* struct DiffPath */

struct DiffPath
 {
  StrLen a;
  StrLen b;
  bool ok = false ;

  DiffPath(StrLen a,StrLen b);

  bool operator ! () const { return !ok; }
 };

/* class RelPath */

class RelPath : NoCopy
 {
   MakeString<MaxPathLen> out;
   bool ok = false ;

  private:

   static ulen Down(StrLen path);

   void relPath(ulen down,StrLen path);

  public:

   RelPath(StrLen base_path,StrLen path);

   ulen operator + () const { return ok; }

   bool operator ! () const { return !ok; }

   StrLen get() const { return out.get(); }
 };

/* class NormalPath */

class NormalPath : NoCopy
 {
   char buf[MaxPathLen+1];
   StrLen path;

  public:

   explicit NormalPath(StrLen path);

   StrLen get() const { return path; }
 };

/* enum ItemStatus */

enum ItemStatus
 {
  Item_New    = 0,
  Item_Ignore = 1,
  Item_Red    = 2,
  Item_Yellow = 3,
  Item_Green  = 4,

  ItemStatusLim
 };

const char * GetTextDesc(ItemStatus status);

/* struct Counts */

struct Counts
 {
  ulen count[ItemStatusLim] = {} ;
 };

/* struct CommonData */

struct CommonData
 {
  String name;
  mutable ItemStatus status = Item_New ;
 };

/* struct FileData */

struct FileData : CommonData
 {
  FileData() noexcept;

  ~FileData();
 };

/* struct DirData */

struct DirData : NoCopyBase<CommonData>
 {
  SimpleArray<DirData> dirs;
  SimpleArray<FileData> files;

  // work

  mutable ulen index = 0 ;

  DirData() noexcept;

  ~DirData();

  void erase();

  // swap objects

  void objSwap(DirData &obj)
   {
    Swap(name,obj.name);
    Swap(status,obj.status);
    Swap(dirs,obj.dirs);
    Swap(files,obj.files);
   }
 };

/* struct ItemData */

struct ItemData
 {
  const CommonData *ptr;
  ulen depth;
  bool is_dir;
  ulen next_index = 0 ;

  mutable bool is_open;

  ItemData(const DirData *dir,ulen depth_)
   : ptr(dir),
     depth(depth_),
     is_dir(true),
     is_open( (depth>0)?false:true )
   {
   }

  ItemData(const FileData *file,ulen depth_)
   : ptr(file),
     depth(depth_),
     is_dir(false),
     is_open(false)
   {
   }

  void open() const
   {
    if( is_dir ) is_open=true;
   }

  void close() const
   {
    if( is_dir ) is_open=false;
   }
 };

/* class AspectData */

class AspectData : NoCopy
 {
   String path; // abs
   DirData root;

   DynArray<ItemData> items;
   DynArray<ulen> visible;

   bool ok = false ;

  private:

   static void Collect(ItemStatus &result,ItemStatus status);

   static void Collect(DirData &dir);

   template <OneOfTypes<FileData,DirData> T>
   static void SortData(PtrLen<T> data);

   class DirProc;

   static void Build(DirData &root,StrLen path);

   template <class T,class Func>
   static bool CopyByName(PtrLen<T> dst,PtrLen<const T> src,Func copy);

   static bool CopyFiles(SimpleArray<FileData> &dst,const SimpleArray<FileData> &src);

   static bool CopyDirs(SimpleArray<DirData> &dst,const SimpleArray<DirData> &src);

   static bool Copy(DirData &root,const DirData &dir);

   static void Fill(DynArray<ItemData> &items,const DirData &dir,ulen depth=0);

   void buildItems();

   bool sync();

   static void PrintDir(PrinterType &out,ulen &index,const DirData &dir);

   static void PrintSub(PrinterType &out,ulen &index,const DirData &dir);

   static StrLen Pretext();

   template <class Dir>
   static void Load(DirData &dst,Dir src);

   void toAbs(StrLen file_name);

  public:

   AspectData() noexcept;

   ~AspectData();

   // methods

   bool operator ! () const { return !ok; }

   const String & getPath() const { return path; }

   void erase();

   Counts getCounts() const;

   PtrLen<const ItemData> getItems() const { return Range(items); }

   PtrLen<const ulen> getVisible() const { return Range(visible); }

   PtrLen<ulen> getVisible() { return Range(visible); }

   void collect();

   // save/load

   void blank(StrLen path);

   void save(StrLen file_name,ErrorText &etext) const;

   bool load(StrLen file_name,ErrorText &etext);
 };

} // namespace App

#endif


