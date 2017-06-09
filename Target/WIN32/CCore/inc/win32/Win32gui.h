/* Win32gui.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_win32_Win32gui_h
#define CCore_inc_win32_Win32gui_h

#include <CCore/inc/win32/Win32.h>

//#define WIN32GUI_EXTRA_CONTENT

namespace Win32 {

/*--------------------------------------------------------------------------------------*/
/* types                                                                                */
/*--------------------------------------------------------------------------------------*/

/* type UPtrType */

using UPtrType  = unsigned ;

/* type Atom */

using Atom      = unsigned short ;

/* type IntRes */

using IntRes    = unsigned short ;

/* type MsgCode */

using MsgCode   = unsigned ;

/* type MsgWParam */

using MsgWParam = unsigned ;

/* type MsgLParam */

using MsgLParam = unsigned ;

/* type MsgResult */

using MsgResult = int ;

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

using WindowProc = MsgResult (WIN32_CALLTYPE *)(HWindow,MsgCode,MsgWParam,MsgLParam) ;

using DialogProc = UPtrType (WIN32_CALLTYPE *)(HWindow,MsgCode,MsgWParam,MsgLParam) ;

/*--------------------------------------------------------------------------------------*/
/* constants                                                                            */
/*--------------------------------------------------------------------------------------*/

/* enum VirtualKey */

enum VirtualKey
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

enum WMCode
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

inline constexpr int HWND_Bottom    =  1 ;
inline constexpr int HWND_NoTopMost = -2 ;
inline constexpr int HWND_Top       =  0 ;
inline constexpr int HWND_TopMost   = -1 ;

/* const InvalidColor */

inline constexpr Color32 InvalidColor = 0xFFFF'FFFF ;

#ifdef WIN32GUI_EXTRA_CONTENT

/* const GDIError */

inline constexpr unsigned GDIError = 0xFFFF'FFFF ;

#endif

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

#ifdef WIN32GUI_EXTRA_CONTENT

/* enum ShowReason */

enum ShowReason
 {
  ShowReason_ShowWindow    = 0,
  ShowReason_ParentClosing = 1,
  ShowReason_OtherZoom     = 2,
  ShowReason_ParentOpening = 3,
  ShowReason_OtherUnzoom   = 4
 };

/* enum SizeType */

enum SizeType
 {
  Size_Restored  = 0,
  Size_Minimized = 1,
  Size_Maximized = 2,
  Size_MaxShow   = 3,
  Size_MaxHide   = 4
 };

/* enum SizingType */

enum SizingType
 {
  Sizing_Left        = 1,
  Sizing_Right       = 2,
  Sizing_Top         = 3,
  Sizing_TopLeft     = 4,
  Sizing_TopRight    = 5,
  Sizing_Bottom      = 6,
  Sizing_BottomLeft  = 7,
  Sizing_BottomRight = 8
 };

/* enum ActivityType */

enum ActivityType
 {
  Activity_Inactive    = 0,
  Activity_Active      = 1,
  Activity_ClickActive = 2
 };

/* enum SysCommand */

enum SysCommand
 {
  SysCommand_Size         = 0xF000,
  SysCommand_Separator    = 0xF00F,
  SysCommand_Move         = 0xF010,
  SysCommand_Minimize     = 0xF020,
  SysCommand_Maximize     = 0xF030,
  SysCommand_NextWindow   = 0xF040,
  SysCommand_PrevWindow   = 0xF050,
  SysCommand_Close        = 0xF060,
  SysCommand_VScroll      = 0xF070,
  SysCommand_HScroll      = 0xF080,
  SysCommand_MouseMenu    = 0xF090,
  SysCommand_KeyMenu      = 0xF100,
  SysCommand_Arrange      = 0xF110,
  SysCommand_Restore      = 0xF120,
  SysCommand_TaskList     = 0xF130,
  SysCommand_ScreenSave   = 0xF140,
  SysCommand_HotKey       = 0xF150,
  SysCommand_Default      = 0xF160,
  SysCommand_MonitorPower = 0xF170,
  SysCommand_ContextHelp  = 0xF180
 };

/* enum MsgFrom */

enum MsgFrom
 {
  MsgFrom_DialogBox  =    0,
  MsgFrom_MessageBox =    1,
  MsgFrom_Menu       =    2,
  MsgFrom_ScrollBar  =    5,
  MsgFrom_NextWindow =    6,
  MsgFrom_Max        =    8,

  MsgFrom_User       = 4096
 };

/* enum MenuFlags */

enum MenuFlags
 {
  Menu_Grayed          = 0x0001,
  Menu_Disabled        = 0x0002,
  Menu_Bitmap          = 0x0004,
  Menu_Checked         = 0x0008,

  Menu_Popup           = 0x0010,
  Menu_BarBreak        = 0x0020,
  Menu_Break           = 0x0040,
  Menu_Highlight       = 0x0080,

  Menu_Ownerdraw       = 0x0100,
  Menu_Separator       = 0x0800,

  Menu_Default         = 0x1000,
  Menu_Sysmenu         = 0x2000,
  Menu_Help            = 0x4000,
  Menu_MouseSelect     = 0x8000,

  Menu_Change          = Menu_Highlight,
  Menu_End             = Menu_Highlight,
  Menu_Append          = Menu_Ownerdraw,
  Menu_Delete          = 0x0200,
  Menu_Remove          = Menu_Default,
  Menu_ByPosition      = 0x0400,
  Menu_UseCheckBitmaps = Menu_Delete,
  Menu_RightJustify    = Menu_Help
 };

/* enum MouseActivate */

enum MouseActivate
 {
  Mouse_Activate         = 1,
  Mouse_ActivateAndEat   = 2,
  Mouse_NoActivate       = 3,
  Mouse_NoActivateAndEat = 4
 };

#endif

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

#ifdef WIN32GUI_EXTRA_CONTENT

/* struct WindowPos */

struct WindowPos
 {
  HWindow hWnd;
  HWindow hWndInsertAfter;
  int x;
  int y;
  int dx;
  int dy;
  flags_t flags;
 };

#endif

/*--------------------------------------------------------------------------------------*/
/* helper functions                                                                     */
/*--------------------------------------------------------------------------------------*/

inline unsigned short HiWord(unsigned val) { return (unsigned short)(val>>16); }

inline unsigned short LoWord(unsigned val) { return (unsigned short)(val    ); }

inline short SHiWord(unsigned val) { return (short)HiWord(val); }

inline short SLoWord(unsigned val) { return (short)LoWord(val); }

inline const char * MakeIntResource(IntRes res) { return (const char *)(unsigned)res; }

inline const char * MakeIntAtom(Atom atom) { return (const char *)(unsigned)atom; }

inline Color32 MakeColor32(Intensity R,Intensity G,Intensity B) { return R|(Color32(G)<<8)|(Color32(B)<<16); }

inline HGDObject ToGDObject(HPen hPen) { return (HGDObject)(void *)hPen; }

inline HGDObject ToGDObject(HBrush hBrush) { return (HGDObject)(void *)hBrush; }

inline HGDObject ToGDObject(HFont hFont) { return (HGDObject)(void *)hFont; }

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

int WIN32_API GetSystemMetrics(options_t sys_metric);

bool_t WIN32_API GetCursorPos(Point *pos);

unsigned short WIN32_API GetKeyState(unsigned vkey);

HCursor WIN32_API SetCursor(HCursor hCursor);

HCursor WIN32_API LoadCursorA(HModule module, const char *res);

HIcon WIN32_API LoadIconA(HModule module, const char *res);

HAccelerator WIN32_API LoadAcceleratorsA(HModule module, const char *res);

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

bool_t WIN32_API PeekMessageA(Msg *msg,
                              HWindow hWnd,
                              MsgCode filter_min,
                              MsgCode filter_max,
                              flags_t peek_message_flags);

bool_t WIN32_API WaitMessage(void);

options_t WIN32_API MsgWaitForMultipleObjects(ulen_t hcount,
                                              handle_t hlist[/* hcount */],
                                              bool_t wait_all,
                                              timeout_t timeout,
                                              flags_t wake_flags);

bool_t WIN32_API TranslateMessage(const Msg *msg);

MsgResult WIN32_API DispatchMessageA(const Msg *msg);

void WIN32_API PostQuitMessage(int exit_code);

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

enum MouseTrackFlags
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
  ulen_t cb;
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
  ulen_t cb;
  flags_t flags;
  HWindow hWnd;
  timeout_t hover_time;
 };

/*--------------------------------------------------------------------------------------*/
/* Window functions                                                                     */
/*--------------------------------------------------------------------------------------*/

Atom WIN32_API RegisterClassExA(const WindowClass *wclass);

HWindow WIN32_API CreateWindowExA(flags_t ex_window_style,
                                  const char *class_name,
                                  const char *window_name,
                                  flags_t window_style,
                                  int x,int y,int dx,int dy,
                                  HWindow hParent,
                                  HMenu hMenu,
                                  HModule hModule,
                                  void *arg);

bool_t WIN32_API DestroyWindow(HWindow hWnd);

UPtrType WIN32_API GetWindowLongA(HWindow hWnd, int index);

UPtrType WIN32_API SetWindowLongA(HWindow hWnd, int index, UPtrType value);

MsgResult WIN32_API DefWindowProcA(HWindow hWnd,
                                   MsgCode message,
                                   MsgWParam wParam,
                                   MsgLParam lParam);

bool_t WIN32_API EnableWindow(HWindow hWnd, bool_t en);

bool_t WIN32_API SetWindowTextA(HWindow hWnd, const char *text);

HGDevice WIN32_API BeginPaint(HWindow hWnd, PaintData *pd);

bool_t WIN32_API EndPaint(HWindow hWnd, const PaintData *pd);

HGDevice WIN32_API GetDC(HWindow hWnd);

bool_t WIN32_API ReleaseDC(HWindow hWnd, HGDevice hGD);

bool_t WIN32_API ShowWindow(HWindow hWnd, options_t cmd_show);

bool_t WIN32_API UpdateWindow(HWindow hWnd);

bool_t WIN32_API InvalidateRect(HWindow hWnd, const Rectangle *rect, bool_t erase_flag);

HWindow WIN32_API SetCapture(HWindow hWnd);

bool_t WIN32_API ReleaseCapture(void);

HWindow WIN32_API SetFocus(HWindow hWnd);

bool_t WIN32_API GetWindowRect(HWindow hWnd, Rectangle *rect);

bool_t WIN32_API MoveWindow(HWindow hWnd,
                            int x,int y,int dx,int dy,
                            bool_t repaint);

bool_t WIN32_API SetWindowPos(HWindow hWnd,
                              HWindow ins_after,
                              int x,int y,int dx,int dy,
                              flags_t window_pos_flags);

bool_t WIN32_API TrackMouseEvent(TrackMouseDesc *track);

#ifdef WIN32GUI_EXTRA_CONTENT

bool_t WIN32_API TranslateAcceleratorA(HWindow hWnd, HAccelerator hAccel, Msg *msg);

#endif

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

options_t WIN32_API MessageBoxA(HWindow hParent,
                                const char *text,
                                const char *caption,
                                flags_t message_box_flags);

#ifdef WIN32GUI_EXTRA_CONTENT

UPtrType WIN32_API DialogBoxParamA(HModule hModule,
                                   const char *res,
                                   HWindow hParent,
                                   DialogProc dialog_proc,
                                   MsgLParam lParam);

HWindow WIN32_API GetDlgItem(HWindow hWnd, int dialog_item_id);

bool_t WIN32_API EndDialog(HWindow hWnd, UPtrType result);

#endif

/*--------------------------------------------------------------------------------------*/
/* Graphics object functions                                                            */
/*--------------------------------------------------------------------------------------*/

HGDevice WIN32_API CreateCompatibleDC(HGDevice hGD);

bool_t WIN32_API DeleteDC(HGDevice hGD);

HGDObject WIN32_API SelectObject(HGDevice hGD, HGDObject hObj);

bool_t WIN32_API DeleteObject(HGDObject hObj);

/*--------------------------------------------------------------------------------------*/
/* Pen options                                                                          */
/*--------------------------------------------------------------------------------------*/

#ifdef WIN32GUI_EXTRA_CONTENT

/* enum PenStyleOptions */

enum PenStyleOptions
 {
  Pen_Solid       = 0,
  Pen_Dash        = 1,
  Pen_Dot         = 2,
  Pen_DashDot     = 3,
  Pen_DasdDotDot  = 4,
  Pen_Null        = 5,
  Pen_InsideFrame = 6
 };

#endif

/*--------------------------------------------------------------------------------------*/
/* Pen functions                                                                        */
/*--------------------------------------------------------------------------------------*/

#ifdef WIN32GUI_EXTRA_CONTENT

HPen WIN32_API CreatePen(options_t pen_style, int width, Color32 color);

#endif

/*--------------------------------------------------------------------------------------*/
/* Brush functions                                                                      */
/*--------------------------------------------------------------------------------------*/

#ifdef WIN32GUI_EXTRA_CONTENT

HBrush WIN32_API GetSysColorBrush(options_t sys_color_index);

HBrush WIN32_API CreateSolidBrush(Color32 color);

#endif

/*--------------------------------------------------------------------------------------*/
/* Font flags and options                                                               */
/*--------------------------------------------------------------------------------------*/

#ifdef WIN32GUI_EXTRA_CONTENT

/* enum FontWeightOptions */

enum FontWeightOptions
 {
  FontWeight_DontCare   =   0,
  FontWeight_Thin       = 100,
  FontWeight_ExtraLight = 200,
  FontWeight_Light      = 300,
  FontWeight_Normal     = 400,
  FontWeight_Medium     = 500,
  FontWeight_SemiBold   = 600,
  FontWeight_Bold       = 700,
  FontWeight_ExtraBold  = 800,
  FontWeight_Heavy      = 900
 };

/* enum FontCharsetOptions */

enum FontCharsetOptions // incomplete
 {
  FontCharset_ANSI    =   0,
  FontCharset_Default =   1,
  FontCharset_Symbol  =   2,
  FontCharset_Russian = 204,
  FontCharset_OEM     = 255,
 };

/* enum FontOutPrecisionOptions */

enum FontOutPrecisionOptions // incomplete
 {
  FontOutPrecision_Default = 0
 };

/* enum FontClipPrecisionOptions */

enum FontClipPrecisionOptions // incomplete
 {
  FontClipPrecision_Default = 0
 };

/* enum FontQualityOptions */

enum FontQualityOptions
 {
  FontQuality_Default          = 0,
  FontQuality_Draft            = 1,
  FontQuality_Proof            = 2,
  FontQuality_NonAntiAliased   = 3,
  FontQuality_AntiAliased      = 4,
  FontQuality_Cleartype        = 5,
  FontQuality_NaturalCleartype = 6
 };

/* enum FontPitchFlags */

enum FontPitchFlags
 {
  FontPitch_Default  = 0x0000,
  FontPitch_Fixed    = 0x0001,
  FontPitch_Variable = 0x0002
 };

/* enum FontFamilyFlags */

enum FontFamilyFlags
 {
  FontFamily_DontCare   = 0x0000,
  FontFamily_Roman      = 0x0010,
  FontFamily_Swiss      = 0x0020,
  FontFamily_Modern     = 0x0030,
  FontFamily_Script     = 0x0040,
  FontFamily_Decorative = 0x0050
 };

/* enum FontTypeFlags */

enum FontTypeFlags
 {
  FontType_Raster   = 0x001,
  FontType_Device   = 0x002,
  FontType_TrueType = 0x004
 };

#endif

/*--------------------------------------------------------------------------------------*/
/* Font structures                                                                      */
/*--------------------------------------------------------------------------------------*/

#ifdef WIN32GUI_EXTRA_CONTENT

/* struct LogFont */

struct LogFont
 {
  int dy;
  int dx;

  int escapement;
  int orientation;
  int weight;

  unsigned char italic;
  unsigned char underline;
  unsigned char strikeout;

  unsigned char charset;
  unsigned char out_precision;
  unsigned char clip_precision;
  unsigned char quality;
  unsigned char pitch_and_family;

  char typeface[32];
 };

/* struct EnumLogFontEx */

struct EnumLogFontEx
 {
  LogFont logfont;
  char full_name[64];
  char style[32];
  char script[32];
 };

/* struct TextMetrics */

struct TextMetrics;

/* callback */

using FontEnumProc = int (WIN32_CALLTYPE *)(const EnumLogFontEx *logfont,
                                            const TextMetrics *metrics,
                                            flags_t font_type,
                                            MsgLParam lParam) ;

#endif

/*--------------------------------------------------------------------------------------*/
/* Font functions                                                                       */
/*--------------------------------------------------------------------------------------*/

#ifdef WIN32GUI_EXTRA_CONTENT

HFont WIN32_API CreateFontA(int dy,
                            int dx,

                            int escapement,
                            int orientation,
                            options_t font_weight,

                            bool_t italic,
                            bool_t underline,
                            bool_t strikeout,

                            options_t font_charset,
                            options_t font_out_precision,
                            options_t font_clip_precision,
                            options_t font_quality,
                            flags_t font_pitch_and_family_flags,

                            const char *typeface);

int WIN32_API EnumFontFamiliesExA(HGDevice hGD,
                                  LogFont *logfont,
                                  FontEnumProc enum_proc,
                                  MsgLParam lParam,
                                  flags_t flags);

#endif

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
  ulen_t cb;
  int dx;
  int dy;
  unsigned short planes;
  unsigned short bpp;
  options_t compression;
  ulen_t image_size;
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

HBitmap WIN32_API CreateDIBSection(HGDevice hGD,
                                   const BitmapInfo *bmpinfo,
                                   options_t dib_type,
                                   void **mem,
                                   handle_t hFileMap,
                                   ulen_t offset);

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

HIcon WIN32_API CreateIconIndirect(IconInfo *icon_info);

bool_t WIN32_API DestroyIcon(HIcon hIcon);

/*--------------------------------------------------------------------------------------*/
/* Draw options and flags                                                               */
/*--------------------------------------------------------------------------------------*/

/* enum RasterOptions */

enum RasterOptions // incomplete
 {
  RasterOp_Copy = 0x00CC'0020
 };

#ifdef WIN32GUI_EXTRA_CONTENT

/* enum BkModeOptions */

enum BkModeOptions
 {
  BkMode_Transparent = 1,
  BkMode_Opaque      = 2
 };

/* enum TextAlignFlags */

enum TextAlignFlags
 {
  TextAlign_Left       =   0,
  TextAlign_Right      =   2,
  TextAlign_Center     =   6,

  TextAlign_Top        =   0,
  TextAlign_Bottom     =   8,
  TextAlign_Baseline   =  24,

  TextAlign_UpdatePos  =   1,

  TextAlign_RTLReading = 256
 };

/* enum PatOptions */

enum PatOptions // incomplete
 {
  PatOp_Copy = 0x00F0'0021
 };

/* const MaxTextExtOutLen */

inline constexpr int MaxExtTextOutLen = 8192 ;

#endif

/*--------------------------------------------------------------------------------------*/
/* Draw structures                                                                      */
/*--------------------------------------------------------------------------------------*/

#ifdef WIN32GUI_EXTRA_CONTENT

/* struct CharPlacement */

struct CharPlacement
 {
  ulen_t cb;
  char *str;
  unsigned *order;
  int *dcell;
  int *caret_pos;
  char *class_name;
  wchar_t *glyphs;
  unsigned glyphs_count;
  int max_fit;
 };

#endif

/*--------------------------------------------------------------------------------------*/
/* Draw functions                                                                       */
/*--------------------------------------------------------------------------------------*/

bool_t WIN32_API BitBlt(HGDevice hdstGD,
                        int x,int y,int dx,int dy,
                        HGDevice hsrcGD,
                        int x1,int y1,
                        options_t raster_op);

#ifdef WIN32GUI_EXTRA_CONTENT

bool_t WIN32_API GdiFlush(void);

options_t WIN32_API SetBkMode(HGDevice hGD, options_t bk_mode);

flags_t WIN32_API SetTextAlign(HGDevice hGD, flags_t text_align_flags);

Color32 WIN32_API SetTextColor(HGDevice hGD, Color32 color);

bool_t WIN32_API MoveToEx(HGDevice hGD,
                          int x,int y,
                          Point *prev);

bool_t WIN32_API LineTo(HGDevice hGD,
                        int x,int y);

bool_t WIN32_API PatBlt(HGDevice hGD,
                        int x,int y,int dx,int dy,
                        options_t pat_op);

bool_t WIN32_API BeginPath(HGDevice hGD);

bool_t WIN32_API EndPath(HGDevice hGD);

bool_t WIN32_API CloseFigure(HGDevice hGD);

bool_t WIN32_API StrokePath(HGDevice hGD);

bool_t WIN32_API FillPath(HGDevice hGD);

bool_t WIN32_API StrokeAndFillPath(HGDevice hGD);

bool_t WIN32_API TextOutA(HGDevice hGD,
                          int x,int y,
                          const char *str,int len);

bool_t WIN32_API ExtTextOutA(HGDevice hGD,
                             int x,int y,
                             flags_t,
                             const Rectangle *rect,
                             const char *str,int len,
                             const int *dcell);

bool_t WIN32_API GetTextExtentPoint32A(HGDevice hGD,
                                       const char *str,int len,
                                       Size *size);

unsigned WIN32_API GetCharacterPlacementA(HGDevice hGD,
                                          const char *str,int len,
                                          int max_extent,
                                          CharPlacement *result,
                                          flags_t);

#endif

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

bool_t WIN32_API SystemParametersInfoA(options_t action,
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

bool_t WIN32_API OpenClipboard(HWindow hWnd);

bool_t WIN32_API CloseClipboard(void);

bool_t WIN32_API EmptyClipboard(void);

handle_t WIN32_API SetClipboardData(options_t format, handle_t h_mem);

handle_t /* h_mem */ WIN32_API GetClipboardData(options_t format);

} // extern "C"

} // namespace Win32

#endif


