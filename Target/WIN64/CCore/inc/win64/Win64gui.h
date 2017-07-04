/* Win64gui.h */
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
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_win64_Win64gui_h
#define CCore_inc_win64_Win64gui_h

#include <CCore/inc/win64/Win64.h>

namespace Win64 {

/*--------------------------------------------------------------------------------------*/
/* types                                                                                */
/*--------------------------------------------------------------------------------------*/

/* type UPtrType */

using UPtrType  = unsigned long ;

/* type Atom */

using Atom      = unsigned short ;

/* type IntRes */

using IntRes    = unsigned short ;

/* type MsgCode */

using MsgCode   = unsigned ;

/* type MsgWParam */

using MsgWParam = unsigned long ;

/* type MsgLParam */

using MsgLParam = unsigned long ;

/* type MsgResult */

using MsgResult = long ;

/* type Intensity */

using Intensity = unsigned char ;

/* type Color32 */

using Color32   = unsigned ;

/*--------------------------------------------------------------------------------------*/
/* handles                                                                              */
/*--------------------------------------------------------------------------------------*/

/* handle HModule */

struct ModuleData;

using HModule = ModuleData * ;

/* handle HWindow */

struct WindowData;

using HWindow = WindowData * ;

/* handle HControl */

struct ControlData;

using HControl = ControlData * ;

/* handle HRegion */

struct RegionData;

using HRegion = RegionData * ;

/* handle HAccelerator */

struct AcceleratorData;

using HAccelerator = AcceleratorData * ;

/* handle HMenu */

struct MenuData;

using HMenu = MenuData * ;

/* handle HCursor */

struct CursorData;

using HCursor = CursorData * ;

/* handle HIcon */

struct IconData;

using HIcon = IconData * ;

/* handle HGDevice */

struct GDeviceData;

using HGDevice = GDeviceData * ;

/* handle HGDObject */

struct HGDObjectData;

using HGDObject = HGDObjectData * ;

/* handle HPen */

struct PenData;

using HPen = PenData * ;

/* handle HBrush */

struct BrushData;

using HBrush = BrushData * ;

/* handle HFont */

struct FontData;

using HFont = FontData * ;

/* handle HBitmap */

struct BitmapData;

using HBitmap = BitmapData * ;

/*--------------------------------------------------------------------------------------*/
/* callbacks                                                                            */
/*--------------------------------------------------------------------------------------*/

using WindowProc = MsgResult (*)(HWindow,MsgCode,MsgWParam,MsgLParam) ;

using DialogProc = UPtrType (*)(HWindow,MsgCode,MsgWParam,MsgLParam) ;

/*--------------------------------------------------------------------------------------*/
/* constants                                                                            */
/*--------------------------------------------------------------------------------------*/

/* enum VirtualKey */

enum VirtualKey : unsigned
 {
  VK_Cancel    =   3,
  VK_Back      =   8,
  VK_Tab       =   9,
  VK_Clear     =  12,
  VK_Return    =  13,
  VK_Shift     =  16,
  VK_Control   =  17,
  VK_Alt       =  18,
  VK_Pause     =  19,
  VK_CapsLock  =  20,
  VK_Escape    =  27,
  VK_Space     =  32,
  VK_PgUp      =  33,
  VK_PgDown    =  34,
  VK_End       =  35,
  VK_Home      =  36,
  VK_Left      =  37,
  VK_Up        =  38,
  VK_Right     =  39,
  VK_Down      =  40,
  VK_Select    =  41,
  VK_Print     =  42,
  VK_Execute   =  43,
  VK_Snapshot  =  44,
  VK_Insert    =  45,
  VK_Delete    =  46,
  VK_Help      =  47,
  VK_LeftWin   =  91,
  VK_RightWin  =  92,
  VK_Apps      =  93,
  VK_Sleep     =  95,
  VK_Numpad0   =  96,
  VK_Numpad1   =  97,
  VK_Numpad2   =  98,
  VK_Numpad3   =  99,
  VK_Numpad4   = 100,
  VK_Numpad5   = 101,
  VK_Numpad6   = 102,
  VK_Numpad7   = 103,
  VK_Numpad8   = 104,
  VK_Numpad9   = 105,
  VK_Mul       = 106,
  VK_Add       = 107,
  VK_Separator = 108,
  VK_Sub       = 109,
  VK_Decimal   = 110,
  VK_Div       = 111,
  VK_F1        = 112,
  VK_F2        = 113,
  VK_F3        = 114,
  VK_F4        = 115,
  VK_F5        = 116,
  VK_F6        = 117,
  VK_F7        = 118,
  VK_F8        = 119,
  VK_F9        = 120,
  VK_F10       = 121,
  VK_F11       = 122,
  VK_F12       = 123,
  VK_NumLock   = 144,
  VK_Scroll    = 145,

  VK_Colon     = 186,
  VK_Plus      = 187,
  VK_Comma     = 188,
  VK_Minus     = 189,
  VK_Period    = 190,
  VK_Slash     = 191,
  VK_Tilda     = 192,

  VK_OBracket  = 219,
  VK_BackSlash = 220,
  VK_CBracket  = 221,
  VK_Quote     = 222
 };

/* enum WMCode */

enum WMCode : unsigned
 {
  WM_Create            =   1,
  WM_Destroy           =   2,
  WM_Move              =   3,
  WM_Size              =   5,
  WM_Activate          =   6,
  WM_SetFocus          =   7,
  WM_KillFocus         =   8,
  WM_Enable            =  10,
  WM_Paint             =  15,
  WM_Close             =  16,
  WM_Quit              =  18,
  WM_QueryOpen         =  19,
  WM_EraseBackground   =  20,
  WM_EndSession        =  22,
  WM_ShowWindow        =  24,
  WM_ActivateApp       =  28,
  WM_CancelMode        =  31,
  WM_SetCursor         =  32,
  WM_MouseActivate     =  33,
  WM_GetMinMaxInfo     =  36,
  WM_WindowPosChanging =  70,
  WM_WindowPosChanged  =  71,
  WM_ContextMenu       = 123,
  WM_NcCreate          = 129,
  WM_NcDestroy         = 130,
  WM_NcHitTest         = 132,
  WM_NcPaint           = 133,
  WM_NcActivate        = 134,
  WM_SyncPaint         = 136,
  WM_NcMouseMove       = 160,
  WM_NcLButtonDown     = 161,
  WM_NcLButtonUp       = 162,
  WM_NcLButtonDClick   = 163,
  WM_NcRButtonDown     = 164,
  WM_NcRButtonUp       = 165,
  WM_NcRButtonDClick   = 166,
  WM_NcMButtonDown     = 167,
  WM_NcMButtonUp       = 168,
  WM_NcMButtonDClick   = 169,
  WM_KeyDown           = 256,
  WM_KeyUp             = 257,
  WM_Char              = 258,
  WM_DeadChar          = 259,
  WM_SysKeyDown        = 260,
  WM_SysKeyUp          = 261,
  WM_SysChar           = 262,
  WM_SysDeadChar       = 263,
  WM_InitDialog        = 272,
  WM_Command           = 273,
  WM_SysCommand        = 274,
  WM_InitMenu          = 278,
  WM_InitMenuPopup     = 279,
  WM_MenuSelect        = 287,
  WM_EnterIdle         = 289,
  WM_UninitMenuPopup   = 293,
  WM_MouseMove         = 512,
  WM_LButtonDown       = 513,
  WM_LButtonUp         = 514,
  WM_LButtonDClick     = 515,
  WM_RButtonDown       = 516,
  WM_RButtonUp         = 517,
  WM_RButtonDClick     = 518,
  WM_MButtonDown       = 519,
  WM_MButtonUp         = 520,
  WM_MButtonDClick     = 521,
  WM_MouseWheel        = 522,
  WM_EnterMenuLoop     = 529,
  WM_ExitMenuLoop      = 530,
  WM_Sizing            = 532,
  WM_CaptureChanged    = 533,
  WM_Moving            = 534,
  WM_EnterSizeMove     = 561,
  WM_ExitSizeMove      = 562,
  WM_NcMouseHover      = 672,
  WM_MouseHover        = 673,
  WM_NcMouseLeave      = 674,
  WM_MouseLeave        = 675,

  WM_Lim
 };

/* const HWND_... */

inline constexpr long HWND_Bottom    =  1 ;
inline constexpr long HWND_NoTopMost = -2 ;
inline constexpr long HWND_Top       =  0 ;
inline constexpr long HWND_TopMost   = -1 ;

/* InvalidColor */

inline constexpr Color32 InvalidColor = 0xFFFF'FFFF ;

/*--------------------------------------------------------------------------------------*/
/* message constants                                                                    */
/*--------------------------------------------------------------------------------------*/

/* enum MouseKey */

enum MouseKey
 {
  MouseKey_Left    = 0x0001,
  MouseKey_Right   = 0x0002,
  MouseKey_Shift   = 0x0004,
  MouseKey_Control = 0x0008,

  MouseKey_Middle  = 0x0010
 };

/* enum HitCode */

enum HitCode
 {
  HitCode_Error       = -2,
  HitCode_Transparent = -1,
  HitCode_Nowhere     =  0,
  HitCode_Client      =  1,
  HitCode_Caption     =  2,
  HitCode_SysMenu     =  3,
  HitCode_Growbox     =  4,
  HitCode_Menu        =  5,
  HitCode_HScroll     =  6,
  HitCode_VScroll     =  7,
  HitCode_MinButton   =  8,
  HitCode_MaxButton   =  9,
  HitCode_Left        = 10,
  HitCode_Right       = 11,
  HitCode_Top         = 12,
  HitCode_TopLeft     = 13,
  HitCode_TopRight    = 14,
  HitCode_Bottom      = 15,
  HitCode_BottomLeft  = 16,
  HitCode_BottomRight = 17,
  HitCode_Border      = 18,
  HitCode_Object      = 19,
  HitCode_Close       = 20,
  HitCode_Help        = 21
 };

/* const WheelDelta */

inline constexpr int WheelDelta = 120 ;

/*--------------------------------------------------------------------------------------*/
/* common structures                                                                    */
/*--------------------------------------------------------------------------------------*/

/* struct Point */

struct Point
 {
  int x;
  int y;
 };

/* struct Size */

struct Size
 {
  int dx;
  int dy;
 };

/* struct Rectangle */

struct Rectangle
 {
  int left;
  int top;
  int right;
  int bottom;
 };

/* struct Msg */

struct Msg
 {
  HWindow hWnd;
  MsgCode message;
  MsgWParam wParam;
  MsgLParam lParam;
  timeout_t time;
  Point point;
 };

/*--------------------------------------------------------------------------------------*/
/* message structures                                                                   */
/*--------------------------------------------------------------------------------------*/

/* struct CreateData */

struct CreateData
 {
  void *arg;
  HModule hModule;
  HMenu hMenu;
  HWindow hParent;
  int dy;
  int dx;
  int y;
  int x;
  flags_t window_style;
  const char *window_name;
  const char *class_name;
  flags_t ex_window_style;
 };

/* struct MinMaxInfo */

struct MinMaxInfo
 {
  Point reserved;

  Point max_size;
  Point max_position;

  Point min_track_size;
  Point max_track_size;
 };

/*--------------------------------------------------------------------------------------*/
/* helper functions                                                                     */
/*--------------------------------------------------------------------------------------*/

inline unsigned short HiWord(unsigned long val) { return (unsigned short)(val>>16); }

inline unsigned short LoWord(unsigned long val) { return (unsigned short)(val    ); }

inline short SHiWord(unsigned long val) { return (short)HiWord(val); }

inline short SLoWord(unsigned long val) { return (short)LoWord(val); }

inline const char * MakeIntResource(IntRes res) { return (const char *)(unsigned long)res; }

inline const char * MakeIntAtom(Atom atom) { return (const char *)(unsigned long)atom; }

inline Color32 MakeColor32(Intensity R,Intensity G,Intensity B) { return R|(Color32(G)<<8)|(Color32(B)<<16); }

inline HGDObject ToGDObject(HPen hPen) { return (HGDObject)(void *)hPen; }

inline HGDObject ToGDObject(HFont hFont) { return (HGDObject)(void *)hFont; }

inline HGDObject ToGDObject(HBrush hBrush) { return (HGDObject)(void *)hBrush; }

inline HGDObject ToGDObject(HBitmap hBitmap) { return (HGDObject)(void *)hBitmap; }

/*--------------------------------------------------------------------------------------*/
/* functions                                                                            */
/*--------------------------------------------------------------------------------------*/

extern "C" {

/*--------------------------------------------------------------------------------------*/
/* Desktop flags and options                                                            */
/*--------------------------------------------------------------------------------------*/

/* enum SysMetricOptions */

enum SysMetricOptions // incomplete
 {
  SysMetric_DXScreen =  0,
  SysMetric_DYScreen =  1,

  SysMetric_DXIcon   = 11,
  SysMetric_DYIcon   = 12,

  SysMetric_DXIconSm = 49,
  SysMetric_DYIconSm = 50
 };

/* enum SysColorOptions */

enum SysColorOptions
 {
  SysColor_Scrollbar               =  0,
  SysColor_Background              =  1,
  SysColor_ActiveCaption           =  2,
  SysColor_InactiveCaption         =  3,
  SysColor_Menu                    =  4,
  SysColor_Window                  =  5,
  SysColor_WindowFrame             =  6,
  SysColor_MenuText                =  7,
  SysColor_WindowText              =  8,
  SysColor_CaptionText             =  9,
  SysColor_ActiveBorder            = 10,
  SysColor_InactiveBorder          = 11,
  SysColor_AppWorkspace            = 12,
  SysColor_Highlight               = 13,
  SysColor_HighlightText           = 14,
  SysColor_ButtonFace              = 15,
  SysColor_ButtonShadow            = 16,
  SysColor_GrayText                = 17,
  SysColor_ButtonText              = 18,
  SysColor_InactiveCaptionText     = 19,
  SysColor_ButtonHighlight         = 20,
  SysColor_3dDarkShadow            = 21,
  SysColor_3dLight                 = 22,
  SysColor_InfoText                = 23,
  SysColor_InfoBackground          = 24,
  SysColor_HotLight                = 26,
  SysColor_GradientActiveCaption   = 27,
  SysColor_GradientInactiveCaption = 28,
  SysColor_MenuHighlight           = 29,
  SysColor_MenuBar                 = 30,

  SysColor_Desktop                 = SysColor_Background,
  SysColor_3dFace                  = SysColor_ButtonFace,
  SysColor_3dShadow                = SysColor_ButtonShadow,
  SysColor_3dHighlight             = SysColor_ButtonHighlight
 };

/* enum SysCursor */

enum SysCursor : IntRes
 {
  SysCursor_Arrow         = 32512,
  SysCursor_IBeam         = 32513,
  SysCursor_Wait          = 32514,
  SysCursor_Cross         = 32515,
  SysCursor_UpArrow       = 32516,
  SysCursor_Size          = 32640,
  SysCursor_Icon          = 32641,
  SysCursor_SizeUpLeft    = 32642, // DownRight
  SysCursor_SizeUpRight   = 32643, // DownLeft
  SysCursor_SizeLeftRight = 32644,
  SysCursor_SizeUpDown    = 32645,
  SysCursor_SizeAll       = 32646,
  SysCursor_No            = 32648,
  SysCursor_Hand          = 32649,
  SysCursor_AppStarting   = 32650,
  SysCursor_Help          = 32651
 };

/* const KeyState... */

inline constexpr unsigned short KeyStateDown   = 0x8000 ;

inline constexpr unsigned short KeyStateToggle = 0x0001 ;

/*--------------------------------------------------------------------------------------*/
/* Desktop functions                                                                    */
/*--------------------------------------------------------------------------------------*/

int WIN64_API GetSystemMetrics(options_t sys_metric);

bool_t WIN64_API GetCursorPos(Point *pos);

unsigned short WIN64_API GetKeyState(unsigned vkey);

HCursor WIN64_API SetCursor(HCursor hCursor);

HCursor WIN64_API LoadCursorA(HModule module, const char *res);

HIcon WIN64_API LoadIconA(HModule module, const char *res);

HAccelerator WIN64_API LoadAcceleratorsA(HModule module, const char *res);

/*--------------------------------------------------------------------------------------*/
/* Message flags                                                                        */
/*--------------------------------------------------------------------------------------*/

/* enum WakeFlags */

enum WakeFlags
 {
  Wake_Key            = 0x0001,
  Wake_MouseMove      = 0x0002,
  Wake_MouseButton    = 0x0004,
  Wake_PostMessage    = 0x0008,

  Wake_Timer          = 0x0010,
  Wake_Paint          = 0x0020,
  Wake_SendMessage    = 0x0040,
  Wake_HotKey         = 0x0080,

  Wake_AllPostMessage = 0x0100,
  Wake_RawInput       = 0x0400,

  Wake_Mouse          = Wake_MouseMove|Wake_MouseButton,
  Wake_Input          = Wake_Mouse|Wake_Key|Wake_RawInput,
  Wake_AllEvents      = Wake_Input|Wake_PostMessage|Wake_Timer|Wake_Paint|Wake_HotKey,
  Wake_AllInput       = Wake_Input|Wake_PostMessage|Wake_Timer|Wake_Paint|Wake_HotKey|Wake_SendMessage
 };

/* enum PeekMessageFlags */

enum PeekMessageFlags
 {
  PeekMessage_NoRemove    = 0,
  PeekMessage_Remove      = 0x0001,
  PeekMessage_NoYield     = 0x0002,

  PeekMessage_Input       = Wake_Input<<16,
  PeekMessage_PostMessage = (Wake_PostMessage|Wake_HotKey|Wake_Timer)<<16,
  PeekMessage_Paint       = Wake_Paint<<16,
  PeekMessage_SendMessage = Wake_SendMessage<<16
 };

/*--------------------------------------------------------------------------------------*/
/* Message functions                                                                    */
/*--------------------------------------------------------------------------------------*/

bool_t WIN64_API PeekMessageA(Msg *msg,
                              HWindow hWnd,
                              MsgCode filter_min,
                              MsgCode filter_max,
                              flags_t peek_message_flags);

bool_t WIN64_API WaitMessage(void);

options_t WIN64_API MsgWaitForMultipleObjects(ushortlen_t hcount,
                                              handle_t hlist[/* hcount */],
                                              bool_t wait_all,
                                              timeout_t timeout,
                                              flags_t wake_flags);

bool_t WIN64_API TranslateMessage(const Msg *msg);

MsgResult WIN64_API DispatchMessageA(const Msg *msg);

void WIN64_API PostQuitMessage(int exit_code);

/*--------------------------------------------------------------------------------------*/
/* Window flags and options                                                             */
/*--------------------------------------------------------------------------------------*/

/* enum ClassStyleFlags */

enum ClassStyleFlags
 {
  ClassStyle_VRedraw         = 0x0000'0001,
  ClassStyle_HRedraw         = 0x0000'0002,
  ClassStyle_DClick          = 0x0000'0008,
  ClassStyle_OwnGD           = 0x0000'0020,
  ClassStyle_ClassGD         = 0x0000'0040,
  ClassStyle_ParentGD        = 0x0000'0080,
  ClassStyle_NoClose         = 0x0000'0200,
  ClassStyle_SaveBits        = 0x0000'0800,
  ClassStyle_ByteAlignClient = 0x0000'1000,
  ClassStyle_ByteAlignWindow = 0x0000'2000,
  ClassStyle_GlobalClass     = 0x0000'4000,
  ClassStyle_IME             = 0x0001'0000,
  ClassStyle_DropShadow      = 0x0002'0000
 };

/* enum WindowStyleFlags */

enum WindowStyleFlags : unsigned
 {
  WindowStyle_TabStop      = 0x0001'0000,
  WindowStyle_Group        = 0x0002'0000,
  WindowStyle_ThickFrame   = 0x0004'0000,
  WindowStyle_SysMenu      = 0x0008'0000,
  WindowStyle_HScroll      = 0x0010'0000,
  WindowStyle_VScroll      = 0x0020'0000,
  WindowStyle_DialogFrame  = 0x0040'0000,
  WindowStyle_Border       = 0x0080'0000,
  WindowStyle_Maximize     = 0x0100'0000,
  WindowStyle_ClipChildren = 0x0200'0000,
  WindowStyle_ClipSiblings = 0x0400'0000,
  WindowStyle_Disabled     = 0x0800'0000,
  WindowStyle_Visible      = 0x1000'0000,
  WindowStyle_Minimize     = 0x2000'0000,
  WindowStyle_Child        = 0x4000'0000,
  WindowStyle_Popup        = 0x8000'0000,

  WindowStyle_MaximizeBox  = WindowStyle_TabStop,
  WindowStyle_MinimizeBox  = WindowStyle_Group,

  WindowStyle_Caption      = WindowStyle_Border|WindowStyle_DialogFrame,

  WindowStyle_OverlappedWindow = WindowStyle_Caption|WindowStyle_SysMenu|WindowStyle_ThickFrame|WindowStyle_MinimizeBox|WindowStyle_MaximizeBox,
  WindowStyle_PopupWindow      = WindowStyle_Popup|WindowStyle_Border|WindowStyle_SysMenu
 };

/* enum WindowStyleExFlags */

enum WindowStyleExFlags
 {
  WindowStyleEx_DialogModalFrame = 0x0000'0001,
  WindowStyleEx_NoParentNotify   = 0x0000'0004,
  WindowStyleEx_TopMost          = 0x0000'0008,
  WindowStyleEx_AcceptFiles      = 0x0000'0010,
  WindowStyleEx_Transparent      = 0x0000'0020,
  WindowStyleEx_MDIChild         = 0x0000'0040,
  WindowStyleEx_ToolWindow       = 0x0000'0080,
  WindowStyleEx_WindowEdge       = 0x0000'0100,
  WindowStyleEx_ClientEdge       = 0x0000'0200,
  WindowStyleEx_ContextHelp      = 0x0000'0400,

  WindowStyleEx_Right            = 0x0000'1000,
  WindowStyleEx_RTLReading       = 0x0000'2000,
  WindowStyleEx_LeftScrollbar    = 0x0000'4000,

  WindowStyleEx_ControlParent    = 0x0001'0000,
  WindowStyleEx_StaticEdge       = 0x0002'0000,
  WindowStyleEx_AppWindow        = 0x0004'0000,
  WindowStyleEx_Layered          = 0x0008'0000,
  WindowStyleEx_NoInheritLayout  = 0x0010'0000,
  WindowStyleEx_LayoutRTL        = 0x0040'0000,
  WindowStyleEx_Composited       = 0x0200'0000,
  WindowStyleEx_NoActivate       = 0x0800'0000,

  WindowStyleEx_OverlappedWindow = WindowStyleEx_WindowEdge|WindowStyleEx_ClientEdge,
  WindowStyleEx_PaletteWindow    = WindowStyleEx_WindowEdge|WindowStyleEx_ToolWindow|WindowStyleEx_TopMost
 };

/* enum CmdShowOptions */

enum CmdShowOptions
 {
  CmdShow_Hide          =  0,
  CmdShow_Normal        =  1,
  CmdShow_Minimized     =  2,
  CmdShow_Maximized     =  3,
  CmdShow_NoActivate    =  4,
  CmdShow_Show          =  5,
  CmdShow_Minimize      =  6,
  CmdShow_MinNoActive   =  7,
  CmdShow_NA            =  8,
  CmdShow_Restore       =  9,
  CmdShow_Default       = 10,
  CmdShow_ForceMinimize = 11
 };

/* enum WindowPosFlags */

enum WindowPosFlags
 {
  WindowPos_NoSize         = 0x0001,
  WindowPos_NoMove         = 0x0002,
  WindowPos_NoZOrder       = 0x0004,
  WindowPos_NoRedraw       = 0x0008,

  WindowPos_NoActivate     = 0x0010,
  WindowPos_FrameChanged   = 0x0020,
  WindowPos_ShowWindow     = 0x0040,
  WindowPos_HideWindow     = 0x0080,

  WindowPos_NoCopyBits     = 0x0100,
  WindowPos_NoOwnerZOrder  = 0x0200,
  WindowPos_NoSendChanging = 0x0400,

  WindowPos_DeferErase     = 0x2000,
  WindowPos_AsyncWindowPos = 0x4000
 };

/* enum MouseTrackFlags */

enum MouseTrackFlags : unsigned
 {
  MouseTrack_Hover = 0x0001,
  MouseTrack_Leave = 0x0002
 };

/* const UserDefault */

inline constexpr int UserDefault = (int)0x8000'0000 ;

/* const HoverTimeDefault */

inline constexpr unsigned HoverTimeDefault = 0xFFFF'FFFF ;

/*--------------------------------------------------------------------------------------*/
/* Window structures                                                                    */
/*--------------------------------------------------------------------------------------*/

/* struct WindowClass */

struct WindowClass
 {
  ushortlen_t cb;
  flags_t style;

  WindowProc wnd_proc;

  unsigned class_extra;
  unsigned window_extra;

  HModule hModule;

  HIcon hIcon;
  HCursor hCursor;
  HBrush hBrush;
  const char *menu_res;
  const char *class_name;
  HIcon hIconSm;
 };

/* struct PaintData */

struct PaintData
 {
  HGDevice hGD;
  bool_t erase_flag;
  Rectangle rect;

  // system internal

  bool_t restore_flag;
  bool_t inc_update_flag;
  char rgb_reserved[32];
 };

/* struct TrackMouseDesc */

struct TrackMouseDesc
 {
  ushortlen_t cb;
  flags_t flags;
  HWindow hWnd;
  timeout_t hover_time;
 };

/*--------------------------------------------------------------------------------------*/
/* Window functions                                                                     */
/*--------------------------------------------------------------------------------------*/

Atom WIN64_API RegisterClassExA(const WindowClass *wclass);

HWindow WIN64_API CreateWindowExA(flags_t ex_window_style,
                                  const char *class_name,
                                  const char *window_name,
                                  flags_t window_style,
                                  int x,int y,int dx,int dy,
                                  HWindow hParent,
                                  HMenu hMenu,
                                  HModule hModule,
                                  void *arg);

bool_t WIN64_API DestroyWindow(HWindow hWnd);

UPtrType WIN64_API GetWindowLongA(HWindow hWnd, int index);

UPtrType WIN64_API SetWindowLongA(HWindow hWnd, int index, UPtrType value);

MsgResult WIN64_API DefWindowProcA(HWindow hWnd,
                                   MsgCode message,
                                   MsgWParam wParam,
                                   MsgLParam lParam);

bool_t WIN64_API EnableWindow(HWindow hWnd, bool_t en);

bool_t WIN64_API SetWindowTextA(HWindow hWnd, const char *text);

HGDevice WIN64_API BeginPaint(HWindow hWnd, PaintData *pd);

bool_t WIN64_API EndPaint(HWindow hWnd, const PaintData *pd);

HGDevice WIN64_API GetDC(HWindow hWnd);

bool_t WIN64_API ReleaseDC(HWindow hWnd, HGDevice hGD);

bool_t WIN64_API ShowWindow(HWindow hWnd, options_t cmd_show);

bool_t WIN64_API UpdateWindow(HWindow hWnd);

bool_t WIN64_API InvalidateRect(HWindow hWnd, const Rectangle *rect, bool_t erase_flag);

HWindow WIN64_API SetCapture(HWindow hWnd);

bool_t WIN64_API ReleaseCapture(void);

HWindow WIN64_API SetFocus(HWindow hWnd);

bool_t WIN64_API GetWindowRect(HWindow hWnd, Rectangle *rect);

bool_t WIN64_API MoveWindow(HWindow hWnd,
                            int x,int y,int dx,int dy,
                            bool_t repaint);

bool_t WIN64_API SetWindowPos(HWindow hWnd,
                              HWindow ins_after,
                              int x,int y,int dx,int dy,
                              flags_t pos_flags);

bool_t WIN64_API TrackMouseEvent(TrackMouseDesc *track);

/*--------------------------------------------------------------------------------------*/
/* Dialog flags                                                                         */
/*--------------------------------------------------------------------------------------*/

/* enum MessageBoxFlags */

enum MessageBoxFlags
 {
  MessageBox_Ok                = 0x0000'0000,
  MessageBox_OkCancel          = 0x0000'0001,
  MessageBox_AbortRetryIgnore  = 0x0000'0002,
  MessageBox_YesNoCancel       = 0x0000'0003,
  MessageBox_YesNo             = 0x0000'0004,
  MessageBox_RetryCancel       = 0x0000'0005,
  MessageBox_CancelTryContinue = 0x0000'0006,

  MessageBox_IconHand          = 0x0000'0010,
  MessageBox_IconQuestion      = 0x0000'0020,
  MessageBox_IconExclamation   = 0x0000'0030,
  MessageBox_IconAsterisk      = 0x0000'0040,

  MessageBox_IconError         = MessageBox_IconHand,
  MessageBox_IconWarning       = MessageBox_IconExclamation,
  MessageBox_IconInformation   = MessageBox_IconAsterisk,
  MessageBox_IconStop          = MessageBox_IconHand,

  MessageBox_UserIcon          = 0x0000'0080,

  MessageBox_DefButton1        = 0x0000'0000,
  MessageBox_DefButton2        = 0x0000'0100,
  MessageBox_DefButton3        = 0x0000'0200,
  MessageBox_DefButton4        = 0x0000'0300,

  MessageBox_SystemModal       = 0x0000'1000,
  MessageBox_TaskModal         = 0x0000'2000,
  MessageBox_Help              = 0x0000'4000,
  MessageBox_NoFocus           = 0x0000'8000,
  MessageBox_SetForeground     = 0x0001'0000,
  MessageBox_DefaultDesktop    = 0x0002'0000,
  MessageBox_TopMost           = 0x0004'0000,
  MessageBox_Right             = 0x0008'0000,
  MessageBox_RTLReading        = 0x0010'0000,
  MessageBox_ServiceNotify     = 0x0020'0000,
  MessageBox_ServiceNotifyNT   = 0x0040'0000,

  MessageBox_TypeMask          = 0x0000'000F,
  MessageBox_IconMask          = 0x0000'00F0,
  MessageBox_DefMask           = 0x0000'0F00,
  MessageBox_ModeMask          = 0x0000'3000,
  MessageBox_MiscMask          = 0x0000'C000
 };

/*--------------------------------------------------------------------------------------*/
/* Dialog functions                                                                     */
/*--------------------------------------------------------------------------------------*/

options_t WIN64_API MessageBoxA(HWindow hParent,
                                const char *text,
                                const char *caption,
                                flags_t message_box_flags);

/*--------------------------------------------------------------------------------------*/
/* Graphics object functions                                                            */
/*--------------------------------------------------------------------------------------*/

HGDevice WIN64_API CreateCompatibleDC(HGDevice hGD);

bool_t WIN64_API DeleteDC(HGDevice hGD);

HGDObject WIN64_API SelectObject(HGDevice hGD, HGDObject hObj);

bool_t WIN64_API DeleteObject(HGDObject hObj);

/*--------------------------------------------------------------------------------------*/
/* Bitmap options                                                                       */
/*--------------------------------------------------------------------------------------*/

/* enum DIBTypeOptions */

enum DIBTypeOptions
 {
  DIB_RGBColors = 0,
  DIB_PalColors = 1
 };

/* enum BitmapCompressionOptions */

enum BitmapCompressionOptions // incomplete
 {
  Bitmap_RGB = 0
 };

/*--------------------------------------------------------------------------------------*/
/* Bitmap structures                                                                    */
/*--------------------------------------------------------------------------------------*/

/* struct BitmapInfoHeader */

struct BitmapInfoHeader
 {
  ushortlen_t cb;
  int dx;
  int dy;
  unsigned short planes;
  unsigned short bpp;
  options_t compression;
  ushortlen_t image_size;
  int x_ppm; // pixel per meter
  int y_ppm;
  unsigned colors_used;
  unsigned colors_important;
 };

/* struct ARGBData */

struct ARGBData
 {
  Intensity blue;
  Intensity green;
  Intensity red;
  Intensity alpha;
 };

/* struct BitmapInfo */

struct BitmapInfo
 {
  BitmapInfoHeader header;
  ARGBData colors[1];
 };

/*--------------------------------------------------------------------------------------*/
/* Bitmap functions                                                                     */
/*--------------------------------------------------------------------------------------*/

HBitmap WIN64_API CreateDIBSection(HGDevice hGD,
                                   const BitmapInfo *bmpinfo,
                                   options_t dib_type,
                                   void **mem,
                                   handle_t hFileMap,
                                   ushortlen_t offset);

/*--------------------------------------------------------------------------------------*/
/* Icon structures                                                                      */
/*--------------------------------------------------------------------------------------*/

struct IconInfo
 {
  bool_t icon_flag;
  int hot_x;
  int hot_y;
  HBitmap bmpMask;
  HBitmap bmpColor;
 };

/*--------------------------------------------------------------------------------------*/
/* Icon functions                                                                       */
/*--------------------------------------------------------------------------------------*/

HIcon WIN64_API CreateIconIndirect(IconInfo *icon_info);

bool_t WIN64_API DestroyIcon(HIcon hIcon);

/*--------------------------------------------------------------------------------------*/
/* Draw options and flags                                                               */
/*--------------------------------------------------------------------------------------*/

/* enum RasterOptions */

enum RasterOptions // incomplete
 {
  RasterOp_Copy = 0x00CC'0020
 };

/*--------------------------------------------------------------------------------------*/
/* Draw functions                                                                       */
/*--------------------------------------------------------------------------------------*/

bool_t WIN64_API BitBlt(HGDevice hdstGD,
                        int x,int y,int dx,int dy,
                        HGDevice hsrcGD,
                        int x1,int y1,
                        options_t raster_op);

/*--------------------------------------------------------------------------------------*/
/* System parameters options                                                            */
/*--------------------------------------------------------------------------------------*/

/* enum SysParamActionOptions */

enum SysParamActionOptions // incomplete
 {
  SPA_getWorkArea = 0x0030
 };

/*--------------------------------------------------------------------------------------*/
/* System parameters functions                                                          */
/*--------------------------------------------------------------------------------------*/

bool_t WIN64_API SystemParametersInfoA(options_t action,
                                       flags_t param,
                                       void *data,
                                       flags_t winini_flag);

/*--------------------------------------------------------------------------------------*/
/* Clipboard options                                                                    */
/*--------------------------------------------------------------------------------------*/

/* enum ClipboardFormatOptions */

enum ClipboardFormatOptions // incomplete
 {
  ClipboardFormat_Text = 1
 };

/*--------------------------------------------------------------------------------------*/
/* Clipboard functions                                                                  */
/*--------------------------------------------------------------------------------------*/

bool_t WIN64_API OpenClipboard(HWindow hWnd);

bool_t WIN64_API CloseClipboard(void);

bool_t WIN64_API EmptyClipboard(void);

handle_t WIN64_API SetClipboardData(options_t format, handle_t h_mem);

handle_t /* h_mem */ WIN64_API GetClipboardData(options_t format);

/*--------------------------------------------------------------------------------------*/
/* Shell functions                                                                      */
/*--------------------------------------------------------------------------------------*/

handle_t /* h_instance */ WIN64_API ShellExecuteA(HWindow hWnd,
                                                  const char *operation,
                                                  const char *file,
                                                  const char *parameters,
                                                  const char *dir,
                                                  options_t show);

} // extern "C"

} // namespace Win64

#endif


