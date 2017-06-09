/* Win64.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_win64_Win64_h
#define CCore_inc_win64_Win64_h

#define WIN64_API __attribute__((dllimport))

namespace Win64 {

/*--------------------------------------------------------------------------------------*/
/* basic types                                                                          */
/*--------------------------------------------------------------------------------------*/

/* type bool_t */

using bool_t = int ;

/* type negbool_t */

using negbool_t = int ;

/* type error_t */

using error_t = int ;

/* type ushortlen_t */

using ushortlen_t = unsigned ;

/* type ulen_t */

using ulen_t = unsigned long ;

/* type flags_t */

using flags_t = unsigned ;

/* type options_t */

using options_t = int ;

/* type timeout_t */

using timeout_t = unsigned ;

/* type void_ptr */

using void_ptr = void * ;

/* type const_void_ptr */

using const_void_ptr = const void * ;

/* type proc_t */

using proc_t = void (*)(void) ;

/* type handle_t */

using handle_t = long ;

/* type socket_t */

using socket_t = long ;

/* type numid_t */

using numid_t = unsigned ;

/* type file_time_t */

using file_time_t = unsigned long ;

/* type file_len_t */

using file_len_t = unsigned long ;

/* type codepage_t */

using codepage_t = unsigned ;

/* type lcid_t */

using lcid_t = unsigned ;

/* type sem_count_t */

using sem_count_t = int ;

/* type unicode_t */

using unicode_t = unsigned short ;

/*--------------------------------------------------------------------------------------*/
/* common structures                                                                    */
/*--------------------------------------------------------------------------------------*/

/* struct SecurityAttributes */

struct SecurityAttributes;

/* struct Overlapped */

struct Overlapped
 {
  ulen_t internal;
  ulen_t internal_hi;
  file_len_t offset;
  handle_t h_event;
 };

/* struct Coord */

struct Coord
 {
  short x;
  short y;
 };

/*--------------------------------------------------------------------------------------*/
/* functions                                                                            */
/*--------------------------------------------------------------------------------------*/

extern "C" {

/*--------------------------------------------------------------------------------------*/
/* Error codes                                                                          */
/*--------------------------------------------------------------------------------------*/

/* enum ErrorCodes */

enum ErrorCodes
 {
  ErrorFileNotFound     =   2,
  ErrorPathNotFound     =   3,
  ErrorTooManyOpenFiles =   4,
  ErrorAccessDenied     =   5,
  ErrorInvalidHandle    =   6,
  ErrorNotEnoughMemory  =   8,
  ErrorOutOfMemory      =  14,
  ErrorInvalidDrive     =  15,
  ErrorNoMoreFiles      =  18,
  ErrorWriteProtect     =  19,
  ErrorSeek             =  25,
  ErrorWriteFault       =  29,
  ErrorReadFault        =  30,
  ErrorHandleEOF        =  38,
  ErrorFileExists       =  80,
  ErrorInvalidParameter =  87,
  ErrorDiskFull         = 112,
  ErrorInvalidName      = 123,
  ErrorDirNotEmpty      = 145,
  ErrorAlreadyExists    = 183,

  ErrorIOPending        = 997,
  WSAErrorIOPending     = ErrorIOPending
 };

/*--------------------------------------------------------------------------------------*/
/* Format error message flags                                                           */
/*--------------------------------------------------------------------------------------*/

/* enum FormatMessageFlags */

enum FormatMessageFlags
 {
  FormatMessageFromSystem    = 0x1000,
  FormatMessageIgnoreInserts = 0x0200,
  FormatMessageMaxWidthMask  = 0x00FF
 };

/*--------------------------------------------------------------------------------------*/
/* Character flags                                                                      */
/*--------------------------------------------------------------------------------------*/

/* enum CodePageId */

enum CodePageId
 {
  CodePageActive =     0,
  CodePageOEM    =     1,
  CodePageMAC    =     2,
  CodePageThread =     3,
  CodePageSymbol =    42,
  CodePageUTF7   = 65000,
  CodePageUTF8   = 65001
 };

/* enum MultiByteFlags */

enum MultiByteFlags
 {
  MultiBytePrecomposed       = 0x0001,
  MultiByteComposite         = 0x0002,
  MultiByteUseGlyphChars     = 0x0004,
  MultiByteErrorInvalidChars = 0x0008
 };

/* enum LCID */

enum LCID
 {
  LCID_UserDefault   = 0x0400,
  LCID_SystemDefault = 0x0800
 };

/*--------------------------------------------------------------------------------------*/
/* Character functions                                                                  */
/*--------------------------------------------------------------------------------------*/

/* MultiByteToWideChar() */

int WIN64_API MultiByteToWideChar(codepage_t codepage,
                                  flags_t flags,
                                  const char *str,
                                  int str_len,
                                  unicode_t *out,
                                  int out_len);

/* CharLowerA() */

char * WIN64_API CharLowerA(char *str);

/* CompareStringA() */

int WIN64_API CompareStringA(lcid_t lcid,
                             flags_t,
                             const char *a,int a_len,
                             const char *b,int b_len);

/*--------------------------------------------------------------------------------------*/
/* Error functions                                                                      */
/*--------------------------------------------------------------------------------------*/

/* GetLastError() */

error_t WIN64_API GetLastError(void);

/* FormatMessageA() */

ushortlen_t WIN64_API FormatMessageA(flags_t format_message_flags,
                                     handle_t,
                                     error_t code,
                                     unsigned,
                                     char *buf,
                                     ushortlen_t buf_len,
                                     void_ptr);

/*--------------------------------------------------------------------------------------*/
/* Time functions                                                                       */
/*--------------------------------------------------------------------------------------*/

/* GetTickCount() */

timeout_t WIN64_API GetTickCount(void);

/* GetSystemTimeAsFileTime() */

void WIN64_API GetSystemTimeAsFileTime(file_time_t *ret);

/*--------------------------------------------------------------------------------------*/
/* Virtual memory flags                                                                 */
/*--------------------------------------------------------------------------------------*/

/* enum AllocFlags */

enum AllocFlags
 {
  AllocReserve = 0x2000,
  AllocCommit  = 0x1000
 };

/* enum PageFlags */

enum PageFlags
 {
  PageReadWrite = 0x0004
 };

/* enum FreeFlags */

enum FreeFlags
 {
  FreeRelease  = 0x8000
 };

/*--------------------------------------------------------------------------------------*/
/* Virtual memory functions                                                             */
/*--------------------------------------------------------------------------------------*/

/* VirtualAlloc() */

void_ptr WIN64_API VirtualAlloc(void_ptr address,
                                ulen_t len,
                                flags_t alloc_flags,
                                flags_t page_flags);

/* VirtualFree() */

bool_t WIN64_API VirtualFree(void_ptr address,
                             ulen_t len,
                             flags_t free_flags);

/*--------------------------------------------------------------------------------------*/
/* Handle functions                                                                     */
/*--------------------------------------------------------------------------------------*/

/* CloseHandle() */

bool_t WIN64_API CloseHandle(handle_t h_any);

/*--------------------------------------------------------------------------------------*/
/* Global memory constants                                                              */
/*--------------------------------------------------------------------------------------*/

enum GMemFlags
 {
  GMemMovable  = 0x0002,
  GMemZeroInit = 0x0040
 };

/*--------------------------------------------------------------------------------------*/
/* Global memory functions                                                              */
/*--------------------------------------------------------------------------------------*/

handle_t WIN64_API GlobalAlloc(flags_t flags, ulen_t len);

handle_t WIN64_API GlobalFree(handle_t h_mem);

ulen_t WIN64_API GlobalSize(handle_t h_mem);

void_ptr WIN64_API GlobalLock(handle_t h_mem);

bool_t WIN64_API GlobalUnlock(handle_t h_mem);

/*--------------------------------------------------------------------------------------*/
/* Wait constants                                                                       */
/*--------------------------------------------------------------------------------------*/

/* const TryTimeout */

inline constexpr timeout_t TryTimeout = timeout_t(0) ;

/* const NoTimeout */

inline constexpr timeout_t NoTimeout = timeout_t(-1) ;

/* enum WaitOptions */

enum WaitOptions
 {
  WaitFailed     =  -1,
  WaitObject_0   =   0,
  WaitTimeout    = 258
 };

/*--------------------------------------------------------------------------------------*/
/* Wait functions                                                                       */
/*--------------------------------------------------------------------------------------*/

/* WaitForSingleObject() */

options_t WIN64_API WaitForSingleObject(handle_t h_any, timeout_t timeout);

/* WaitForMultipleObjects() */

options_t WIN64_API WaitForMultipleObjects(ushortlen_t hcount,
                                           handle_t hlist[/* hcount */],
                                           bool_t wait_all,
                                           timeout_t timeout);

/*--------------------------------------------------------------------------------------*/
/* DLL functions                                                                        */
/*--------------------------------------------------------------------------------------*/

/* GetModuleHandleA() */

handle_t WIN64_API GetModuleHandleA(const char *module_name);

/*--------------------------------------------------------------------------------------*/
/* Process flags                                                                        */
/*--------------------------------------------------------------------------------------*/

/* enum ProcessCreationFlags */

enum ProcessCreationFlags
 {
  CreateNewConsole = 0x0010
 };

/* enum StartupInfoFlags */

enum StartupInfoFlags
 {
  StartupInfo_show_window = 0x0001
 };

/*--------------------------------------------------------------------------------------*/
/* Process structures                                                                   */
/*--------------------------------------------------------------------------------------*/

/* struct StartupInfo */

struct StartupInfo
 {
  ushortlen_t cb;

  const char *reserved;
  const char *desktop;
  const char *title;

  int x;
  int y;
  int dx;
  int dy;

  unsigned dx_chars;
  unsigned dy_chars;

  flags_t fill_attr;
  flags_t flags;

  short show_window;
  short reserved2;

  void_ptr reserved3;

  handle_t h_stdin;
  handle_t h_stdout;
  handle_t h_stderr;
 };

/* struct ProcessInfo */

struct ProcessInfo
 {
  handle_t h_process;
  handle_t h_thread;
  numid_t process_id;
  numid_t thread_id;
 };

/*--------------------------------------------------------------------------------------*/
/* Process functions                                                                    */
/*--------------------------------------------------------------------------------------*/

/* GetStartupInfoA() */

void WIN64_API GetStartupInfoA(StartupInfo *info);

/* GetCurrentProcess() */

handle_t WIN64_API GetCurrentProcess(void);

/* TerminateProcess() */

bool_t WIN64_API TerminateProcess(handle_t h_process, unsigned exit_code);

/* Sleep() */

void WIN64_API Sleep(timeout_t timeout);

/* GetCurrentThreadId() */

numid_t WIN64_API GetCurrentThreadId(void);

/* CreateProcessA() */

bool_t WIN64_API CreateProcessA(const char *program,
                                const char *arg,
                                SecurityAttributes *,
                                SecurityAttributes *,
                                bool_t inherit_handles,
                                flags_t process_creation_flags,
                                void_ptr,
                                const char *dir,
                                StartupInfo *info,
                                ProcessInfo *pinfo);

/*--------------------------------------------------------------------------------------*/
/* System property functions                                                            */
/*--------------------------------------------------------------------------------------*/

/* GetACP() */

codepage_t WIN64_API GetACP(void);

/*--------------------------------------------------------------------------------------*/
/* System information structures                                                        */
/*--------------------------------------------------------------------------------------*/

/* struct SystemInfo */

struct SystemInfo
 {
  unsigned short cpu_arch;
  unsigned short reserved1;
  unsigned page_len;
  void_ptr min_address;
  void_ptr max_address;
  unsigned long cpu_mask;
  unsigned cpu_count;
  unsigned cpu_type;
  unsigned alloc_granularity;
  unsigned short cpu_level;
  unsigned short cpu_revision;
 };

/*--------------------------------------------------------------------------------------*/
/* System information functions                                                         */
/*--------------------------------------------------------------------------------------*/

/* GetSystemInfo() */

void WIN64_API GetSystemInfo(SystemInfo *info);

/*--------------------------------------------------------------------------------------*/
/* Console constants                                                                    */
/*--------------------------------------------------------------------------------------*/

/* enum ConsoleModes */

enum ConsoleModes
 {
  ConEcho      = 0x0004,
  ConIns       = 0x0020,
  ConLineInput = 0x0002
 };

/* enum ConEventType */

enum ConEventType
 {
  ConKeyEvent     =  1,
  ConMouse        =  2,
  ConBufsizeEvent =  4,
  ConMenuEvent    =  8,
  ConFocusEvent   = 16
 };

/*--------------------------------------------------------------------------------------*/
/* Console structures                                                                   */
/*--------------------------------------------------------------------------------------*/

/* struct ConKeyRecord */

struct ConKeyRecord
 {
  bool_t key_down;

  unsigned short repeat;
  unsigned short vkey;
  unsigned short vscan;

  union
   {
    unsigned short unicode;
    char ascii;
   } ch;

  flags_t control_state;
 };

/* struct ConMouseRecord */

struct ConMouseRecord
 {
  Coord pos;
  flags_t button_state;
  flags_t control_state;
  flags_t flags;
 };

/* struct ConMenuRecord */

struct ConMenuRecord
 {
  unsigned command_id;
 };

/* struct ConFocusRecord */

struct ConFocusRecord
 {
  bool_t set_focus;
 };

/* struct ConBufsizeRecord */

struct ConBufsizeRecord
 {
  Coord size;
 };

/* struct ConInputRecord */

struct ConInputRecord
 {
  unsigned short event_type;

  union
   {
    ConKeyRecord key;
    ConMouseRecord mouse;
    ConMenuRecord menu;
    ConFocusRecord focus;
    ConBufsizeRecord bufsize;
   } event;
 };

/*--------------------------------------------------------------------------------------*/
/* Console functions                                                                    */
/*--------------------------------------------------------------------------------------*/

/* SetConsoleOutputCP() */

bool_t WIN64_API SetConsoleOutputCP(codepage_t code_page);

/* GetConsoleOutputCP() */

codepage_t WIN64_API GetConsoleOutputCP(void);

/* SetConsoleMode() */

bool_t WIN64_API SetConsoleMode(handle_t h_con, flags_t modes);

/* GetConsoleMode() */

bool_t WIN64_API GetConsoleMode(handle_t h_con, flags_t *modes);

/* ReadConsoleInputA() */

bool_t WIN64_API ReadConsoleInputA(handle_t h_con,
                                   ConInputRecord *buf,
                                   ushortlen_t buf_len,
                                   ushortlen_t *ret_len);

/*--------------------------------------------------------------------------------------*/
/* File flags and options                                                               */
/*--------------------------------------------------------------------------------------*/

/* const InvalidFileHandle */

inline constexpr handle_t InvalidFileHandle = -1 ;

/* enum StdHandleOptions */

enum StdHandleOptions
 {
  StdInputHandle  = -10,
  StdOutputHandle = -11
 };

/* enum AccessFlags */

enum AccessFlags : unsigned
 {
  AccessRead   = 0x8000'0000,
  AccessWrite  = 0x4000'0000,
  AccessDelete = 0x0001'0000
 };

/* enum ShareFlags */

enum ShareFlags
 {
  ShareRead  = 0x0001,
  ShareWrite = 0x0002
 };

/* enum CreationOptions */

enum CreationOptions        // +-------------+----------+
 {                          // | file exists | no file  |
                            // +-------------+----------+
  CreateNew        = 1,     // |  failure    |  create  |
  CreateAlways     = 2,     // |  overwrite  |  create  |
  OpenExisting     = 3,     // |  open       |  failure |
  OpenAlways       = 4,     // |  open       |  create  |
  TruncateExisting = 5      // |  overwrite  |  failure |
 };                         // +-------------+----------+

/* enum FileFlags */

enum FileFlags
 {
  FileAttributeNormal = 0x0000'0080,
  FileBackupSemantic  = 0x0200'0000,
  FileDeleteOnClose   = 0x0400'0000,
  FileSequentialScan  = 0x0800'0000,
  FileAsyncIO         = 0x4000'0000
 };

/* enum FromOptions */

enum FromOptions
 {
  FromBegin   = 0,
  FromCurrent = 1,
  FromEnd     = 2
 };

/* enum FileInfoOptions */

enum FileInfoOptions
 {
  FileDispositionInfo = 4
 };

/* enum FileAttributes */

enum FileAttributes
 {
  FileAttributes_Directory = 0x0010
 };

/* const InvalidFileAttributes */

inline constexpr flags_t InvalidFileAttributes = flags_t(-1) ;

/* enum MoveFileExFlags */

enum MoveFileExFlags
 {
  MoveFileEx_AllowOverwrite = 0x0001
 };

/*--------------------------------------------------------------------------------------*/
/* File structures                                                                      */
/*--------------------------------------------------------------------------------------*/

/* struct FileDispositionInfoData */

struct FileDispositionInfoData
 {
  bool_t delete_file;
 };

/*--------------------------------------------------------------------------------------*/
/* File functions                                                                       */
/*--------------------------------------------------------------------------------------*/

/* GetStdHandle() */

handle_t WIN64_API GetStdHandle(options_t std_handle_options);

/* CreateFileA() */

handle_t WIN64_API CreateFileA(const char *file_name,
                               flags_t access_flags,
                               flags_t share_flags,
                               SecurityAttributes *,
                               options_t creation_options,
                               flags_t file_flags,
                               handle_t);

/* WriteFile() */

bool_t WIN64_API WriteFile(handle_t h_file,
                           const_void_ptr buf,
                           ushortlen_t buf_len,
                           ushortlen_t *ret_len,
                           Overlapped *olap);

/* ReadFile() */

bool_t WIN64_API ReadFile(handle_t h_file,
                          void_ptr buf,
                          ushortlen_t buf_len,
                          ushortlen_t *ret_len,
                          Overlapped *olap);

/* GetOverlappedResult() */

bool_t WIN64_API GetOverlappedResult(handle_t h_file,
                                     Overlapped *olap,
                                     ushortlen_t *ret_len,
                                     bool_t wait_flag);

/* GetFileSizeEx() */

bool_t WIN64_API GetFileSizeEx(handle_t h_file, file_len_t *ret);

/* SetFilePointerEx() */

bool_t WIN64_API SetFilePointerEx(handle_t h_file,
                                  file_len_t to,
                                  file_len_t *ret,
                                  options_t from_options);

/* FlushFileBuffers() */

bool_t WIN64_API FlushFileBuffers(handle_t h_file);

/* SetFileInformationByHandle() */

bool_t WIN64_API SetFileInformationByHandle(handle_t h_file,
                                            options_t file_info_options,
                                            void_ptr buf,
                                            ushortlen_t buf_len);

/*--------------------------------------------------------------------------------------*/
/* File system structures                                                               */
/*--------------------------------------------------------------------------------------*/

/* struct FileTime */

struct FileTime
 {
  unsigned lo;
  unsigned hi;
 };

/* struct FindFileData */

struct FindFileData
 {
  flags_t attr;

  FileTime creation_time;
  FileTime last_access_time;
  FileTime last_write_time;

  unsigned file_len_hi;
  unsigned file_len_lo;

  flags_t reserved0;
  flags_t reserved1;

  char file_name[260];
  char alt_file_name[16];
 };

/*--------------------------------------------------------------------------------------*/
/* File system functions                                                                */
/*--------------------------------------------------------------------------------------*/

/* GetFileTime() */

bool_t WIN64_API GetFileTime(handle_t h_file, FileTime *creation_time,
                                              FileTime *last_access_time,
                                              FileTime *last_write_time);

/* GetFileAttributesA() */

flags_t WIN64_API GetFileAttributesA(const char *path);

/* DeleteFileA() */

bool_t WIN64_API DeleteFileA(const char *path);

/* CreateDirectoryA() */

bool_t WIN64_API CreateDirectoryA(const char *path, SecurityAttributes *);

/* RemoveDirectoryA() */

bool_t WIN64_API RemoveDirectoryA(const char *path);

/* MoveFileExA() */

bool_t WIN64_API MoveFileExA(const char *old_path, const char *new_path, flags_t flags);

/* FindFirstFileA() */

handle_t WIN64_API FindFirstFileA(const char *path, FindFileData *find_data);

/* FindNextFileA() */

bool_t WIN64_API FindNextFileA(handle_t h_find, FindFileData *find_data);

/* FindClose() */

bool_t WIN64_API FindClose(handle_t h_find);

/* GetFullPathNameA() */

ushortlen_t WIN64_API GetFullPathNameA(const char *path,
                                       ushortlen_t buf_len,
                                       char *buf,
                                       char **file_part);

/*--------------------------------------------------------------------------------------*/
/* Socket flags and options                                                             */
/*--------------------------------------------------------------------------------------*/

/* const InvalidSocket */

inline constexpr socket_t InvalidSocket = -1 ;

/* const InvalidUShortLen */

inline constexpr ushortlen_t InvalidUShortLen = ushortlen_t(-1) ;

/* enum WSAVersions */

enum WSAVersions
 {
  WSAVersion_2_00 = 0x0002,
  WSAVersion_2_02 = 0x0202
 };

/* enum WSAAddressFamily */

enum WSAAddressFamily
 {
  WSA_IPv4 = 2
 };

/* enum WSASocketType */

enum WSASocketType
 {
  WSA_Datagram = 2
 };

/* enum WSAProtocol */

enum WSAProtocol
 {
  WSA_UDP = 17
 };

/* enum WSASocketFlags */

enum WSASocketFlags
 {
  WSA_AsyncIO = 0x0001
 };

/* enum WSAWaitOptions */

enum WSAWaitOptions
 {
  WSAWaitFailed     =  -1,
  WSAWaitObject_0   =   0,
  WSAWaitTimeout    = 258
 };

/*--------------------------------------------------------------------------------------*/
/* Socket structures                                                                    */
/*--------------------------------------------------------------------------------------*/

/* type WSAGroup */

using WSAGroup = unsigned ;

/* type WSAVersion */

using WSAVersion = unsigned short ;

/* struct WSAInfo */

struct WSAInfo
 {
  WSAVersion version;
  WSAVersion hi_version;

  unsigned short max_sockets;
  unsigned short max_UDP_data_len;

  char *vendor_info;

  char desc[257];
  char status[129];
 };

/* struct WSAProtocolInfo */

struct WSAProtocolInfo;

/* struct WSASockSet */

struct WSASockSet
 {
  ushortlen_t count;
  socket_t set[64];
 };

/* struct WSATimeout */

struct WSATimeout
 {
  unsigned sec;
  unsigned usec;
 };

/* struct WSAOverlapped */

struct WSAOverlapped
 {
  ulen_t internal;
  ulen_t internal_hi;
  file_len_t offset;
  handle_t h_event;
 };

/* struct WSABuf */

struct WSABuf
 {
  ulen_t len;
  void_ptr ptr;
 };

/*--------------------------------------------------------------------------------------*/
/* Socket functions                                                                     */
/*--------------------------------------------------------------------------------------*/

/* WSAStartup() */

error_t WIN64_API WSAStartup(WSAVersion version, WSAInfo *info);

/* WSACleanup() */

negbool_t WIN64_API WSACleanup(void);

/* WSAGetLastError() */

error_t WIN64_API WSAGetLastError(void);

/* WSASocket() */

socket_t WIN64_API WSASocketA(options_t address_family,
                              options_t type,
                              options_t protocol,
                              WSAProtocolInfo *,
                              WSAGroup,
                              flags_t flags);

/* bind() */

negbool_t WIN64_API bind(socket_t sock,
                         const_void_ptr address,
                         ushortlen_t address_len);

/* closesocket() */

negbool_t WIN64_API closesocket(socket_t sock);

/* sendto() */

ushortlen_t WIN64_API sendto(socket_t sock,
                             const_void_ptr data,
                             ushortlen_t data_len,
                             flags_t,
                             const_void_ptr address,
                             ushortlen_t address_len);

/* recvfrom() */

ushortlen_t WIN64_API recvfrom(socket_t sock,
                               void_ptr buf,
                               ushortlen_t buf_len,
                               flags_t,
                               void_ptr address,
                               ushortlen_t *address_len);

/* select() */

ushortlen_t WIN64_API select(int,
                             WSASockSet *read_set,
                             WSASockSet *write_set,
                             WSASockSet *error_set,
                             const WSATimeout *timeout);

/* WSASendTo() */

negbool_t WIN64_API WSASendTo(socket_t sock,
                              WSABuf *buf,
                              ushortlen_t buf_len,
                              ushortlen_t *ret_len,
                              flags_t,
                              const_void_ptr address,
                              ushortlen_t address_len,
                              WSAOverlapped *olap,
                              proc_t);

/* WSARecvFrom() */

negbool_t WIN64_API WSARecvFrom(socket_t sock,
                                WSABuf *buf,
                                ushortlen_t buf_len,
                                ushortlen_t *ret_len,
                                flags_t *ret_flags,
                                void_ptr address,
                                ushortlen_t *address_len,
                                WSAOverlapped *olap,
                                proc_t);

/* WSAGetOverlappedResult() */

bool_t WIN64_API WSAGetOverlappedResult(socket_t sock,
                                        WSAOverlapped *olap,
                                        ushortlen_t *ret_len,
                                        bool_t wait_flag,
                                        flags_t *ret_flags);

/* WSACreateEvent() */

handle_t WIN64_API WSACreateEvent(void);

/* WSACloseEvent() */

bool_t WIN64_API WSACloseEvent(handle_t h_event);

/* WSASetEvent() */

bool_t WIN64_API WSASetEvent(handle_t h_event);

/* WSAResetEvent() */

bool_t WIN64_API WSAResetEvent(handle_t h_event);

/* WSAWaitForMultipleEvents() */

options_t WIN64_API WSAWaitForMultipleEvents(ushortlen_t hcount,
                                             handle_t hlist[/* hcount */],
                                             bool_t wait_all,
                                             timeout_t timeout,
                                             bool_t);

/*--------------------------------------------------------------------------------------*/
/* TLS constants                                                                        */
/*--------------------------------------------------------------------------------------*/

/* const TlsNoIndex */

inline constexpr int TlsNoIndex = -1 ;

/*--------------------------------------------------------------------------------------*/
/* TLS functions                                                                        */
/*--------------------------------------------------------------------------------------*/

/* TlsAlloc() */

int WIN64_API TlsAlloc(void);

/* TlsFree() */

bool_t WIN64_API TlsFree(int index);

/* TlsGetValue() */

void_ptr WIN64_API TlsGetValue(int index);

/* TlsSetValue() */

bool_t WIN64_API TlsSetValue(int index, void_ptr value);

/*--------------------------------------------------------------------------------------*/
/* Event functions                                                                      */
/*--------------------------------------------------------------------------------------*/

/* CreateEventA() */

handle_t WIN64_API CreateEventA(SecurityAttributes *,
                                bool_t manual_reset,
                                bool_t initial_state,
                                const char *object_name);

/* SetEvent() */

bool_t WIN64_API SetEvent(handle_t h_event);

/*--------------------------------------------------------------------------------------*/
/* Semaphore constants                                                                  */
/*--------------------------------------------------------------------------------------*/

/* const MaxSemaphoreCount */

inline constexpr sem_count_t MaxSemaphoreCount = 0x7FFF'FFFF ;

/*--------------------------------------------------------------------------------------*/
/* Semaphore functions                                                                  */
/*--------------------------------------------------------------------------------------*/

/* CreateSemaphoreA() */

handle_t WIN64_API CreateSemaphoreA(SecurityAttributes *,
                                    sem_count_t initial_count,
                                    sem_count_t max_count,
                                    const char *object_name);

/* ReleaseSemaphore() */

bool_t WIN64_API ReleaseSemaphore(handle_t h_sem, sem_count_t delta, sem_count_t *prev_count);

} // extern "C"

/* adapters */

inline constexpr ushortlen_t MaxUShortLen = ushortlen_t(-1) ;

inline constexpr ushortlen_t SplitLen = 0x10'0000 ;

inline ushortlen_t CapLen(ulen_t len) { if( len>MaxUShortLen ) return MaxUShortLen; return (ushortlen_t)len; }

bool_t ExtWriteFile(handle_t h_file,
                    const_void_ptr buf,
                    ulen_t buf_len,
                    ulen_t *ret_len);

bool_t ExtReadFile(handle_t h_file,
                   void_ptr buf,
                   ulen_t buf_len,
                   ulen_t *ret_len);

} // namespace Win64

#endif

