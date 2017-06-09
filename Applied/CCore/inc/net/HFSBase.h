/* HFSBase.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_net_HFSBase_h
#define CCore_inc_net_HFSBase_h

#include <CCore/inc/net/PTPExtra.h>

namespace CCore {
namespace Net {
namespace HFS {

/* using */

using namespace PTP;

/* types */

using FileLenType = uint64 ;

using CmpFileTimeType = uint64 ;

/* consts */

inline constexpr ulen MaxPathLen    =  512 ;
inline constexpr ulen DeltaReadLen  =   24 ;
inline constexpr ulen MaxReadLen    = 1416 ;
inline constexpr ulen DeltaWriteLen =   40 ;
inline constexpr ulen MaxWriteLen   = 1400 ;

inline constexpr ServiceIdType ServiceId = 2 ;

inline constexpr FunctionIdType FunctionId_Open        =  1 ;
inline constexpr FunctionIdType FunctionId_Read        =  2 ;
inline constexpr FunctionIdType FunctionId_Write       =  3 ;
inline constexpr FunctionIdType FunctionId_Close       =  4 ;
inline constexpr FunctionIdType FunctionId_GetFileType =  5 ;
inline constexpr FunctionIdType FunctionId_GetFileList =  6 ;
inline constexpr FunctionIdType FunctionId_CreateFile  =  7 ;
inline constexpr FunctionIdType FunctionId_DeleteFile  =  8 ;
inline constexpr FunctionIdType FunctionId_CreateDir   =  9 ;
inline constexpr FunctionIdType FunctionId_DeleteDir   = 10 ;
inline constexpr FunctionIdType FunctionId_Rename      = 11 ;
inline constexpr FunctionIdType FunctionId_Remove      = 12 ;
inline constexpr FunctionIdType FunctionId_Exec        = 13 ;
inline constexpr FunctionIdType FunctionId_Exec2       = 14 ;
inline constexpr FunctionIdType FunctionId_GetFileUpdateTime = 15 ;

inline constexpr FlagType OpenFlag_Read       = 0x01 ;
inline constexpr FlagType OpenFlag_Write      = 0x02 ;
inline constexpr FlagType OpenFlag_Create     = 0x10 ;
inline constexpr FlagType OpenFlag_Erase      = 0x20 ;
inline constexpr FlagType OpenFlag_New        = 0x40 ;
inline constexpr FlagType OpenFlag_AutoDelete = 0x80 ;

inline constexpr FlagType FileType_none = 0 ;
inline constexpr FlagType FileType_file = 1 ;
inline constexpr FlagType FileType_dir  = 2 ;

inline constexpr ErrorIdType ErrorBase = 100 ;

/* classes */

struct FileId;

struct OpenInput;
struct OpenOutput;

struct ReadInput;
struct ReadOutput;

struct WriteInput;
struct WriteOutput;

struct CloseInput;
using CloseOutput = Empty ;

struct PathInput;

using GetFileTypeInput = PathInput ;
struct GetFileTypeOutput;

using GetFileListInput = PathInput ;
struct GetFileListOutput;

using CreateFileInput = PathInput ;
using CreateFileOutput = Empty ;

using DeleteFileInput = PathInput ;
using DeleteFileOutput = Empty ;

using CreateDirInput = PathInput ;
using CreateDirOutput = Empty ;

struct DeleteDirInput;
using DeleteDirOutput = Empty ;

struct SaveLoadPath;

struct RenameInput;
using RenameOutput = Empty ;

using RemoveInput = PathInput ;
using RemoveOutput = Empty ;

struct ExecInput;
using ExecOutput = Empty ;

struct Exec2Input;
struct Exec2Output;

using GetFileUpdateTimeInput = PathInput ;
struct GetFileUpdateTimeOutput;

/* struct FileId */

struct FileId
 {
  uint32 slot;
  uint64 number;
  uint64 clock;

  // constructors

  FileId() : slot(),number(),clock() {}

  // methods

  friend bool operator == (const FileId &a,const FileId &b)
   {
    return a.slot==b.slot && a.number==b.number && a.clock==b.clock ;
   }

  friend bool operator != (const FileId &a,const FileId &b) { return !(a==b); }

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<uint32,uint64,uint64>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(slot,number,clock);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(slot,number,clock);
   }
 };

/* struct OpenInput */

struct OpenInput // + uint8 path[len];
 {
  static constexpr ulen MaxLen = MaxPathLen ;

  FlagType open_flags;
  LenType len;

  // constructors

  OpenInput() : open_flags(),len() {}

  OpenInput(FlagType open_flags_,LenType len_) : open_flags(open_flags_),len(len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<FlagType,LenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(open_flags,len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(open_flags,len);
   }
 };

/* struct OpenOutput */

struct OpenOutput
 {
  FileId file_id;
  FileLenType file_len;

  // constructors

  OpenOutput() : file_id(),file_len() {}

  OpenOutput(const FileId &file_id_,FileLenType file_len_) : file_id(file_id_),file_len(file_len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<FileId,FileLenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(file_id,file_len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(file_id,file_len);
   }
 };

/* struct ReadInput */

struct ReadInput
 {
  FileId file_id;
  FileLenType off;
  LenType len;

  // constructors

  ReadInput() : file_id(),off(),len() {}

  ReadInput(const FileId &file_id_,FileLenType off_,LenType len_) : file_id(file_id_),off(off_),len(len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<FileId,FileLenType,LenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(file_id,off,len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(file_id,off,len);
   }
 };

/* struct ReadOutput */

struct ReadOutput // + uint8 data[len];
 {
  static constexpr ulen MaxLen = MaxReadLen ;

  FileLenType off;
  LenType len;

  // constructors

  ReadOutput() : off(),len() {}

  ReadOutput(FileLenType off_,LenType len_) : off(off_),len(len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<FileLenType,LenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(off,len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(off,len);
   }
 };

/* struct WriteInput */

struct WriteInput // + uint8 data[len];
 {
  static constexpr ulen MaxLen = MaxWriteLen ;

  FileId file_id;
  FileLenType off;
  LenType len;

  // constructors

  WriteInput() : file_id(),off(),len() {}

  WriteInput(const FileId &file_id_,FileLenType off_,LenType len_) : file_id(file_id_),off(off_),len(len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<FileId,FileLenType,LenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(file_id,off,len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(file_id,off,len);
   }
 };

/* struct WriteOutput */

struct WriteOutput
 {
  FileLenType file_len;

  // constructors

  WriteOutput() : file_len() {}

  explicit WriteOutput(FileLenType file_len_) : file_len(file_len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<FileLenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(file_len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(file_len);
   }
 };

/* struct CloseInput */

struct CloseInput
 {
  BoolType preserve_file;
  FileId file_id;

  // constructors

  CloseInput() : preserve_file(),file_id() {}

  CloseInput(BoolType preserve_file_,const FileId &file_id_) : preserve_file(preserve_file_),file_id(file_id_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<BoolType,FileId>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(preserve_file,file_id);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(preserve_file,file_id);
   }
 };

/* struct PathInput */

struct PathInput // + uint8 path[len];
 {
  static constexpr ulen MaxLen = MaxPathLen ;

  LenType len;

  // constructors

  PathInput() : len() {}

  explicit PathInput(LenType len_) : len(len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<LenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(len);
   }
 };

/* struct GetFileTypeOutput */

struct GetFileTypeOutput
 {
  FlagType type;

  // constructors

  GetFileTypeOutput() : type() {}

  explicit GetFileTypeOutput(FlagType type_) : type(type_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<FlagType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(type);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(type);
   }
 };

/* struct GetFileListOutput */

struct GetFileListOutput
 {
  FileId file_id;
  FileLenType file_len;

  // constructors

  GetFileListOutput() : file_id(),file_len() {}

  GetFileListOutput(const FileId &file_id_,FileLenType file_len_) : file_id(file_id_),file_len(file_len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<FileId,FileLenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(file_id,file_len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(file_id,file_len);
   }
 };

/* struct DeleteDirInput */

struct DeleteDirInput // + uint8 path[len];
 {
  static constexpr ulen MaxLen = MaxPathLen ;

  BoolType recursive;
  LenType len;

  // constructors

  DeleteDirInput() : recursive(),len() {}

  DeleteDirInput(BoolType recursive_,LenType len_) : recursive(recursive_),len(len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<BoolType,LenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(recursive,len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(recursive,len);
   }
 };

/* struct SaveLoadPath */

struct SaveLoadPath
 {
  PtrLen<const uint8> path;

  // constructors

  SaveLoadPath() : path() {}

  explicit SaveLoadPath(PtrLen<const uint8> path_) : path(path_) {}

  // save/load object

  void save(SaveDevType &dev) const
   {
    LenType len=LenType(path.len);

    dev.template use<BeOrder>(len);

    dev.put(path);
   }

  void load(RangeLoadDevType &dev)
   {
    LenType len=0;

    dev.template use<BeOrder>(len);

    if( len>MaxPathLen )
      dev.fail();
    else
      path=dev.getRange(len);
   }
 };

/* struct RenameInput */

struct RenameInput
 {
  BoolType allow_overwrite;
  SaveLoadPath old_path;
  SaveLoadPath new_path;

  // constructors

  RenameInput() : allow_overwrite(),old_path(),new_path() {}

  RenameInput(bool allow_overwrite_,PtrLen<const uint8> old_path_,PtrLen<const uint8> new_path_)
   : allow_overwrite(allow_overwrite_),old_path(old_path_),new_path(new_path_) {}

  // save/load object

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(allow_overwrite,old_path,new_path);
   }

  void load(RangeLoadDevType &dev)
   {
    dev.template use<BeOrder>(allow_overwrite,old_path,new_path);
   }
 };

/* struct ExecInput */

struct ExecInput
 {
  SaveLoadPath dir;
  SaveLoadPath program;
  SaveLoadPath arg;

  // constructors

  ExecInput() : dir(),program(),arg() {}

  ExecInput(PtrLen<const uint8> dir_,PtrLen<const uint8> program_,PtrLen<const uint8> arg_)
   : dir(dir_),program(program_),arg(arg_) {}

  // save/load object

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(dir,program,arg);
   }

  void load(RangeLoadDevType &dev)
   {
    dev.template use<BeOrder>(dir,program,arg);
   }
 };

/* struct Exec2Input */

struct Exec2Input
 {
  SaveLoadPath dir;
  SaveLoadPath program;

  // constructors

  Exec2Input() : dir(),program() {}

  Exec2Input(PtrLen<const uint8> dir_,PtrLen<const uint8> program_) : dir(dir_),program(program_) {}

  // save/load object

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(dir,program);
   }

  void load(RangeLoadDevType &dev)
   {
    dev.template use<BeOrder>(dir,program);
   }
 };

/* struct Exec2Output */

struct Exec2Output
 {
  FileId file_id;

  // constructors

  Exec2Output() : file_id() {}

  explicit Exec2Output(const FileId &file_id_) : file_id(file_id_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<FileId>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(file_id);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(file_id);
   }
 };

/* struct GetFileUpdateTimeOutput */

struct GetFileUpdateTimeOutput
 {
  CmpFileTimeType file_time;

  // constructors

  GetFileUpdateTimeOutput() : file_time() {}

  explicit GetFileUpdateTimeOutput(CmpFileTimeType file_time_) : file_time(file_time_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<CmpFileTimeType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(file_time);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(file_time);
   }
 };

} // namespace HFS
} // namespace Net
} // namespace CCore

#endif


