/* HFSClientDevice.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
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

#ifndef CCore_inc_net_HFSClientDevice_h
#define CCore_inc_net_HFSClientDevice_h

#include <CCore/inc/net/PTPClientDevice.h>

#include <CCore/inc/net/HFSBase.h>

namespace CCore {
namespace Net {
namespace HFS {

/* classes */

struct OpenExt;

struct ReadExt;

struct WriteExt;

struct CloseExt;

struct GetFileTypeExt;

struct GetFileUpdateTimeExt;

struct GetFileListExt;

struct CreateFileExt;

struct DeleteFileExt;

struct CreateDirExt;

struct DeleteDirExt;

struct RenameExt;

struct RemoveExt;

struct ExecExt;

struct Exec2Ext;

class ClientDevice;

/* struct OpenExt */

struct OpenExt : ExtBase<ServiceId,FunctionId_Open>
 {
  using InputType = OpenInput ;
  using OutputType = OpenOutput ;

  FileId file_id;
  FileLenType file_len;

  void done(const OutputType &output)
   {
    file_id=output.file_id;
    file_len=output.file_len;
   }
 };

/* struct ReadExt */

struct ReadExt : ExtBase<ServiceId,FunctionId_Read,MovePacketBufByRequest>
 {
  using InputType = ReadInput ;
  using OutputType = Tailed<ReadOutput> ;

  FileLenType off;
  PtrLen<const uint8> data;

  explicit ReadExt(MoveFlagType move_flag) : ExtBase<ServiceId,FunctionId_Read,MovePacketBufByRequest>(move_flag) {}

  void done(const OutputType &output)
   {
    off=output.output.off;
    data=output.tail;
   }
 };

/* struct WriteExt */

struct WriteExt : ExtBase<ServiceId,FunctionId_Write>
 {
  using InputType = WriteInput ;
  using OutputType = WriteOutput ;

  FileLenType file_len;

  void done(const OutputType &output)
   {
    file_len=output.file_len;
   }
 };

/* struct CloseExt */

struct CloseExt : ExtBase<ServiceId,FunctionId_Close>
 {
  using InputType = CloseInput ;
  using OutputType = CloseOutput ;

  void done(const OutputType &)
   {
   }
 };

/* struct GetFileTypeExt */

struct GetFileTypeExt : ExtBase<ServiceId,FunctionId_GetFileType>
 {
  using InputType = GetFileTypeInput ;
  using OutputType = GetFileTypeOutput ;

  FlagType type;

  void done(const OutputType &output)
   {
    type=output.type;
   }
 };

/* struct GetFileUpdateTimeExt */

struct GetFileUpdateTimeExt : ExtBase<ServiceId,FunctionId_GetFileUpdateTime>
 {
  using InputType = GetFileUpdateTimeInput ;
  using OutputType = GetFileUpdateTimeOutput ;

  CmpFileTimeType file_time;

  void done(const OutputType &output)
   {
    file_time=output.file_time;
   }
 };

/* struct GetFileListExt */

struct GetFileListExt : ExtBase<ServiceId,FunctionId_GetFileList>
 {
  using InputType = GetFileListInput ;
  using OutputType = GetFileListOutput ;

  FileId file_id;
  FileLenType file_len;

  void done(const OutputType &output)
   {
    file_id=output.file_id;
    file_len=output.file_len;
   }
 };

/* struct CreateFileExt */

struct CreateFileExt : ExtBase<ServiceId,FunctionId_CreateFile>
 {
  using InputType = CreateFileInput ;
  using OutputType = CreateFileOutput ;

  void done(const OutputType &)
   {
   }
 };

/* struct DeleteFileExt */

struct DeleteFileExt : ExtBase<ServiceId,FunctionId_DeleteFile>
 {
  using InputType = DeleteFileInput ;
  using OutputType = DeleteFileOutput ;

  void done(const OutputType &)
   {
   }
 };

/* struct CreateDirExt */

struct CreateDirExt : ExtBase<ServiceId,FunctionId_CreateDir>
 {
  using InputType = CreateDirInput ;
  using OutputType = CreateDirOutput ;

  void done(const OutputType &)
   {
   }
 };

/* struct DeleteDirExt */

struct DeleteDirExt : ExtBase<ServiceId,FunctionId_DeleteDir>
 {
  using InputType = DeleteDirInput ;
  using OutputType = DeleteDirOutput ;

  void done(const OutputType &)
   {
   }
 };

/* struct RenameExt */

struct RenameExt : ExtBase<ServiceId,FunctionId_Rename>
 {
  using InputType = RenameInput ;
  using OutputType = RenameOutput ;

  void done(const OutputType &)
   {
   }
 };

/* struct RemoveExt */

struct RemoveExt : ExtBase<ServiceId,FunctionId_Remove>
 {
  using InputType = RemoveInput ;
  using OutputType = RemoveOutput ;

  void done(const OutputType &)
   {
   }
 };

/* struct ExecExt */

struct ExecExt : ExtBase<ServiceId,FunctionId_Exec>
 {
  using InputType = ExecInput ;
  using OutputType = ExecOutput ;

  void done(const OutputType &)
   {
   }
 };

/* struct Exec2Ext */

struct Exec2Ext : ExtBase<ServiceId,FunctionId_Exec2>
 {
  using InputType = Exec2Input ;
  using OutputType = Exec2Output ;

  FileId file_id;

  void done(const OutputType &output)
   {
    file_id=output.file_id;
   }
 };

/* class ClientDevice */

class ClientDevice : public ObjBase
 {
   ObjHook hook;

   PTP::ClientDevice *ptp;

   ulen max_outbound_info_len;
   ulen max_inbound_info_len;
   ulen max_read_len;

   PacketFormat open_format;
   PacketFormat write_format;

   PacketFormat getFileType_format;
   PacketFormat getFileUpdateTime_format;
   PacketFormat getFileList_format;
   PacketFormat createFile_format;
   PacketFormat deleteFile_format;
   PacketFormat createDir_format;
   PacketFormat deleteDir_format;
   PacketFormat remove_format;

  public:

   static const Unid TypeUnid;

   // constructors

   explicit ClientDevice(StrLen ptp_dev_name);

   virtual ~ClientDevice();

   PTP::ClientDevice * getPTPDevice() const { return ptp; }

   // open

   PacketFormat getOpenFormat() const { return open_format; }

   void open(Packet<uint8,OpenExt> packet,FlagType open_flags);

   void open(Packet<uint8,OpenExt> packet,StrLen file_name,FlagType open_flags);

   // read

   ulen getMaxReadLen() const { return max_read_len; } // always > 0 , <= MaxReadLen

   void read(Packet<uint8,ReadExt> packet,const FileId &file_id,FileLenType off,ulen len);

   // write

   PacketFormat getWriteFormat() const { return write_format; } // always max_data <= MaxWriteLen

   void write(Packet<uint8,WriteExt> packet,const FileId &file_id,FileLenType off);

   // close

   void close(Packet<uint8,CloseExt> packet,const FileId &file_id,bool preserve_file=false);

   // getFileType

   void getFileType(Packet<uint8,GetFileTypeExt> packet,StrLen path);

   // getFileUpdateTime

   void getFileUpdateTime(Packet<uint8,GetFileUpdateTimeExt> packet,StrLen path);

   // getFileList

   void getFileList(Packet<uint8,GetFileListExt> packet,StrLen dir_name);

   // createFile

   void createFile(Packet<uint8,CreateFileExt> packet,StrLen file_name);

   // deleteFile

   void deleteFile(Packet<uint8,DeleteFileExt> packet,StrLen file_name);

   // createDir

   void createDir(Packet<uint8,CreateDirExt> packet,StrLen dir_name);

   // deleteDir

   void deleteDir(Packet<uint8,DeleteDirExt> packet,StrLen dir_name,bool recursive);

   // rename

   void rename(Packet<uint8,RenameExt> packet,StrLen old_path,StrLen new_path,bool allow_overwrite);

   // remove

   void remove(Packet<uint8,RemoveExt> packet,StrLen path);

   // exec

   void exec(Packet<uint8,ExecExt> packet,StrLen dir,StrLen program,StrLen arg);

   // exec2

   void exec2(Packet<uint8,Exec2Ext> packet,StrLen dir,StrLen program);
 };

} // namespace HFS
} // namespace Net
} // namespace CCore

#endif


