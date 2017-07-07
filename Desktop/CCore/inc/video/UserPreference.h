/* UserPreference.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_UserPreference_h
#define CCore_inc_video_UserPreference_h

#include <CCore/inc/video/ConfigBinder.h>

#include <CCore/inc/video/WindowLib.h>
#include <CCore/inc/video/ToolFrame.h>
#include <CCore/inc/video/WindowReport.h>
#include <CCore/inc/video/MessageFrame.h>
#include <CCore/inc/video/Menu.h>
#include <CCore/inc/video/FileFrame.h>
#include <CCore/inc/video/DirFrame.h>
#include <CCore/inc/video/ConfigEditor.h>

namespace CCore {
namespace Video {

/* classes */

struct UserPreferenceBag;

class UserPreference;

/* struct UserPreferenceBag */

struct UserPreferenceBag : ConfigItemHost
 {
  // common

  Ratio frame_pos_ry = Div(5,12) ;

  MCoord width = Fraction(6,2) ;

  Coord space_dxy = 10 ;

  Coord check_dxy   = 20 ;
  Coord knob_dxy    = 30 ;
  Coord radio_dxy   = 20 ;
  Coord switch_dxy  = 30 ;
  Coord light_dxy   = 20 ;
  Coord scroll_dxy  = 20 ;
  Coord progress_dy = 24 ;

  VColor gray    =       Gray ;
  VColor grayUp  =      Green ;
  VColor snow    =       Snow ;
  VColor snowUp  =  PaleGreen ;

  VColor back     =    Silver ;
  VColor line     =      Gray ;
  VColor inactive =      Gray ;

  VColor border   =      Blue ;
  VColor focus    = OrangeRed ;

  VColor face     =     Black ;
  VColor faceUp   =      Blue ;
  VColor mark     =     Black ;
  VColor alert    =      Pink ;

  DefString text_Yes    = "Yes"_def ;
  DefString text_No     = "No"_def ;

  DefString text_Ok     = "Ok"_def ;
  DefString text_Cancel = "Cancel"_def ;

  DefString text_LoadFile = "Select a file to load from"_def ;
  DefString text_SaveFile = "Select a file to save to"_def ;

  DefString text_Alert   = "Alert"_def ;
  DefString text_AskSave = "Save modifications?"_def ;

  DefString text_Error   = "Error"_def ;
  DefString text_Warning = "Warning"_def ;

  DefString text_Close   = "Close"_def ;
  DefString text_Insert  = "Insert"_def ;

  DefString title_UserPref = "User preferences"_def ;
  DefString title_AppPref = "Application preferences"_def ;

  DefString text_none = "<none>"_def ;

  // text

  Coord text_cursor_dx = 3 ;

  VColor text_select    = Yellow ;
  VColor text_cursor    =   Blue ;

  VColor label_text     =  Black ;
  VColor contour_text   =  Black ;

  VColor button_text    =  Black ;
  VColor message_text   =  Black ;
  VColor info_text      =  Black ;
  VColor line_edit_text =  Black ;
  VColor list_text      =  Black ;
  VColor spinor_text    =  Black ;

  Point button_space    = Point(6,4) ;
  Point message_space   = Point(6,4) ;
  Point line_edit_space = Point(6,4) ;
  Point info_space      = Point(8,8) ;
  Point list_space      = Point(8,8) ;
  Point menu_space      = Point(4,4) ;

  FontCouple label_font;
  FontCouple contour_font;

  FontCouple button_font;
  FontCouple message_font;
  FontCouple info_font;
  FontCouple line_edit_font;
  FontCouple list_font;
  FontCouple menu_font;
  FontCouple spinor_font;

  FontCouple code_font;

  // switch

  VColor switch_on  = Green ;
  VColor switch_off =   Red ;

  // progress

  unsigned progress_time   = 3_sectick ;
  unsigned progress_period =    2_tick ;

  VColor progress_border   =     Black ;
  VColor progress_grayUp   = DarkGreen ;
  VColor progress_snowUp   =     Green ;
  VColor progress_grayPing =     Black ;
  VColor progress_snowPing =      Snow ;

  // scroll

  unsigned scroll_speedUpPeriod = 12_tick ;

  // line_edit

  unsigned line_edit_period = 10_tick ;

  Coord line_edit_ex = 3 ;

  // scroll_list

  VColor scroll_list_title       = Navy ;
  VColor scroll_list_titleTop    = Aqua ;
  VColor scroll_list_titleBottom = Gray ;

  // spinor

  unsigned spinor_period = 1_sectick/2 ;

  // menu

  VColor menu_back      =    Silver ;
  VColor menu_text      =     Black ;
  VColor menu_hilight   =      Blue ;
  VColor menu_select    = OrangeRed ;
  VColor menu_hot       =       Red ;

  bool menu_hotcolor = true ;

  // Frame

  unsigned blinkTime   = 3_sectick ;
  unsigned blinkPeriod =    3_tick ;

  Coord frame_dxy = 12 ;
  Coord title_dy  = 32 ;
  Coord btn_dx    = 26 ;
  Coord btn_dy    = 24 ;

  VColor frame             =      Snow ;
  VColor frameHilight      = PaleGreen ;
  VColor frameDrag         =      Pink ;

  VColor title             =     Black ;
  VColor titleActive       = RoyalBlue ;
  VColor titleInactive     =    Silver ;

  VColor drag              =    Silver ;
  VColor dragHilight       =     Green ;
  VColor dragActive        =       Red ;
  VColor dragSmall         =     Wheat ;

  VColor btnFace           = SteelBlue ;
  VColor btnFaceHilight    =     Green ;
  VColor btnPict           =     White ;
  VColor btnPictClose      =       Red ;
  VColor btnPictAlert      =       Red ;
  VColor btnPictNoAlert    =      Gray ;
  VColor btnPictCloseAlert =    Orange ;

  VColor hintBack   = Wheat ;
  VColor hintText   =  Blue ;
  VColor hintBorder = Green ;

  MCoord hintWidth = Fraction(3) ;

  FontCouple title_font;
  FontCouple hint_font;

  VColor shadeColor = Violet ;
  Clr    shadeAlpha =     64 ;

  DefString text_Fatal_error = "Fatal error"_def ;
  DefString text_No_hint     = "<No hint available>"_def ;

  DefString hint_ResizeTopLeft     = "Resize top-left"_def ;
  DefString hint_ResizeLeft        = "Resize left"_def ;
  DefString hint_ResizeBottomLeft  = "Resize bottom-left"_def ;
  DefString hint_ResizeBottom      = "Resize bottom"_def ;
  DefString hint_ResizeBottomRight = "Resize bottom-right"_def ;
  DefString hint_ResizeRight       = "Resize right"_def ;
  DefString hint_ResizeTopRight    = "Resize top-right"_def ;

  DefString hint_Alert    = "Open/close alert view"_def ;
  DefString hint_Help     = "Help on/off"_def ;
  DefString hint_Minimize = "Minimize"_def ;
  DefString hint_Maximize = "Maximize"_def ;
  DefString hint_Restore  = "Restore"_def ;
  DefString hint_Close    = "Close"_def ;

  // Exception

  VColor exception_back    = Black ;
  VColor exception_text    = Green ;
  VColor exception_divider =   Red ;

  // Message

  Coord message_knob_dxy = 50 ;

  // File

  Coord file_alt_dxy = 40 ;

  VColor file_accent      = Black ;
  VColor file_filter_text = Black ;

  VColor file_faceRight = Green ;
  VColor file_faceDown  =   Red ;

  FontCouple file_filter_font;

  DefString text_New_file = "New file"_def ;

  DefString hint_FileHitList   = "Open/close the hit directory list"_def ;
  DefString hint_FileAddHit    = "Add the current directory to the hit list"_def ;
  DefString hint_FileUpdir     = "Goto the parent directory"_def ;
  DefString hint_FileCurdir    = "Current directory"_def ;
  DefString hint_FileDirList   = "Subdirectory list"_def ;
  DefString hint_FileList      = "File list"_def ;
  DefString hint_FileMakeDir   = "Create a new directory"_def ;
  DefString hint_FileRemoveDir = "Delete the selected directory"_def ;
  DefString hint_FileAlt       = "Choose between a new file or an existing file"_def ;

  DefString hint_FileEnableFilter = "Enable/disable this filter"_def ;
  DefString hint_FileDelFilter    = "Delete this filter"_def ;
  DefString hint_FileFilter       = "Filename filter, use * or ?"_def ;

  DefString hint_FileAddFilter = "Add a filter"_def ;

  // ConfigEditor

  MCoord cfg_edit_width = Fraction(1) ;

  Coord cfg_edit_mark_dy = 3 ;

  VColor cfg_edit_line = Black ;

  MCoord cfg_width = Fraction(8,2) ;

  Coord cfg_radius    =  15 ;

  Coord cfg_mix_len   = 350 ;
  Coord cfg_mix_width =  30 ;

  Coord cfg_white_len = 250 ;

  unsigned cfg_pal_len = 10 ;

  DefString text_cfg_all      =         "All"_def ;
  DefString text_cfg_Coord    =        "size"_def ;
  DefString text_cfg_MCoord   =  "milli-size"_def ;
  DefString text_cfg_VColor   =       "color"_def ;
  DefString text_cfg_Clr      = "color pitch"_def ;
  DefString text_cfg_unsigned =       "count"_def ;
  DefString text_cfg_String   =        "text"_def ;
  DefString text_cfg_Point    =       "point"_def ;
  DefString text_cfg_Font     =        "font"_def ;
  DefString text_cfg_bool     =        "bool"_def ;
  DefString text_cfg_Ratio    =       "ratio"_def ;

  DefString text_cfg_Set  =           "Set"_def ;
  DefString text_cfg_Back =          "Back"_def ;
  DefString text_cfg_Save =          "Save"_def ;
  DefString text_cfg_Self = "Apply to self"_def ;

  DefString hint_cfg_list = "Configuration parameters list"_def ;

  DefString hint_cfg_Set  = "Set the parameter"_def ;
  DefString hint_cfg_Back = "Revert back the parameter"_def ;
  DefString hint_cfg_Save = "Save the current settings"_def ;
  DefString hint_cfg_Self = "Apply parameters to this window"_def ;

  DefString hint_cfg_x = "Select x coordinate"_def ;
  DefString hint_cfg_y = "Select y coordinate"_def ;

  DefString hint_cfg_a = "Select divisible"_def ;
  DefString hint_cfg_b = "Select divider"_def ;

  DefString text_cfg_scalable    = "scalable"_def ;
  DefString text_cfg_monospace   = "monospace"_def ;
  DefString text_cfg_bold        = "bold"_def ;
  DefString text_cfg_italic      = "italic"_def ;

  DefString text_cfg_Hint = "Hint"_def ;

  DefString text_cfg_no_hint     = "No hint"_def ;
  DefString text_cfg_native_hint = "Native hint"_def ;
  DefString text_cfg_auto_hint   = "Auto hint"_def ;

  DefString text_cfg_Smooth = "Smooth"_def ;

  DefString text_cfg_no_smooth   = "No smooth"_def ;
  DefString text_cfg_smooth      = "Smooth"_def ;
  DefString text_cfg_RGB         = "LCD RGB"_def ;
  DefString text_cfg_BGR         = "LCD BGR"_def ;

  DefString text_cfg_kerning     = "Kerning"_def ;
  DefString text_cfg_strength    = "Strength"_def ;
  DefString text_cfg_sample      = "sample"_def ;
  DefString text_cfg_table       = "table"_def ;

  DefString hint_cfg_font_list     = "Font file list"_def ;
  DefString hint_cfg_height        = "Font height"_def ;
  DefString hint_cfg_length_enable = "Enable font length"_def ;
  DefString hint_cfg_length        = "Font length"_def ;

  // constructors

  UserPreferenceBag() noexcept {}

  // methods

  template <class Ptr,class Func>
  static void Members(Ptr ptr,Func func);

  virtual void bind(ConfigItemBind &binder);

  void createFonts();

  void findFonts();
 };

/* class UserPreference */

class UserPreference : public ConfigBinder<UserPreferenceBag, // Update here

                                           ButtonWindow::ConfigType,
                                           KnobWindow::ConfigType,
                                           CheckWindow::ConfigType,
                                           ContourWindow::ConfigType,
                                           TextContourWindow::ConfigType,
                                           InfoWindow::ConfigType,
                                           LabelWindow::ConfigType,
                                           LightWindow::ConfigType,
                                           XSingleLineWindow::ConfigType,
                                           XDoubleLineWindow::ConfigType,
                                           LineEditWindow::ConfigType,
                                           ProgressWindow::ConfigType,
                                           RadioWindow::ConfigType,
                                           XScrollWindow::ConfigType,
                                           SimpleTextListWindow::ConfigType,
                                           SwitchWindow::ConfigType,
                                           TextWindow::ConfigType,
                                           TextLineWindow::ConfigType,
                                           ScrollListWindow::ConfigType,
                                           XSplitWindow::ConfigType,
                                           SpinorWindow::ConfigType,

                                           DragFrame::ConfigType,
                                           FixedFrame::ConfigType,
                                           ToolFrame::ConfigType,

                                           WindowReportConfig,
                                           ExceptionWindow::ConfigType,

                                           MessageWindow::ConfigType,
                                           MessageFrame::ConfigType,
                                           MessageWindow::AlertConfigType,
                                           MessageFrame::AlertConfigType,

                                           SimpleTopMenuWindow::ConfigType,
                                           SimpleCascadeMenu::ConfigType,

                                           DirEditWindow::ConfigType,
                                           FileFilterListWindow::ConfigType,
                                           FileCheckShape::Config,
                                           FileWindow::ConfigType,
                                           FileFrame::ConfigType,
                                           DirWindow::ConfigType,
                                           DirFrame::ConfigType,

                                           CoordEditWindow::ConfigType,
                                           MCoordEditWindow::ConfigType,
                                           PointEditWindow::ConfigType,
                                           ColorEditWindow::ConfigType,
                                           FontEditWindow::ConfigType,
                                           RatioEditWindow::ConfigType,
                                           CharTableWindow::ConfigType,
                                           ConfigEditorWindow::ConfigType,
                                           ConfigEditorFrame::ConfigType
                                          >
 {
   static StrLen PrefFile();

  public:

   // constructors

   UserPreference() noexcept;

   ~UserPreference();

   // methods

   void sync() noexcept;

   void update() noexcept;

   // signals

   mutable Signal<> updated;
 };

} // namespace Video
} // namespace CCore

#endif

