/* UserPreference.h */
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
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_UserPreference_h
#define CCore_inc_video_UserPreference_h

#include <CCore/inc/video/ConfigBinder.h>

#include <CCore/inc/video/WindowLib.h>

#include <CCore/inc/video/WindowReport.h>
#include <CCore/inc/video/ToolFrame.h>
#include <CCore/inc/video/Menu.h>

#include <CCore/inc/video/MessageFrame.h>
#include <CCore/inc/video/FileFrame.h>
#include <CCore/inc/video/DirFrame.h>
#include <CCore/inc/video/ConfigEditor.h>
#include <CCore/inc/video/ExceptionFrame.h>
#include <CCore/inc/video/FontReplace.h>
#include <CCore/inc/video/FavFrame.h>

namespace CCore {
namespace Video {

/* classes */

struct UserPreferenceBag;

class UserPreference;

/* struct UserPreferenceBag */

struct UserPreferenceBag
 {
  // common

  Ratio frame_pos_ry = Div(5,12) ;
  Fraction width = Fraction(6,2) ;
  Coord space_dxy = 10 ;

  Coord check_dxy   = 20 ;
  Coord knob_dxy    = 30 ;
  Coord radio_dxy   = 20 ;
  Coord switch_dxy  = 30 ;
  Coord light_dxy   = 20 ;
  Coord scroll_dxy  = 20 ;
  Coord progress_dy = 24 ;
  Coord shift_len   = 30 ;

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
  VColor warning  =    Yellow ;

  String text_Yes    = "Yes"_str ;
  String text_No     = "No"_str ;

  String text_Ok     = "Ok"_str ;
  String text_Cancel = "Cancel"_str ;

  String text_LoadFile = "Select a file to load from"_str ;
  String text_SaveFile = "Select a file to save to"_str ;

  String text_Alert   = "Alert"_str ;
  String text_AskSave = "Save modifications?"_str ;

  String text_Error   = "Error"_str ;
  String text_Warning = "Warning"_str ;

  String text_Close   = "Close"_str ;
  String text_Insert  = "Insert"_str ;

  String text_Select  = "Select"_str ;
  String text_Find    = "Find"_str ;
  String text_Replace = "Replace"_str ;
  String text_Save    = "Save"_str ;
  String text_Apply   = "Apply"_str ;
  String text_Section = "Section"_str ;

  String title_UserPref = "User preferences"_str ;
  String title_AppPref  = "Application preferences"_str ;
  String title_BookPref = "Book preferences"_str ;

  String text_none = "<none>"_str ;

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
  Point fav_space       = Point(8,8) ;

  FontCouple label_font;
  FontCouple contour_font;

  FontCouple button_font;
  FontCouple message_font;
  FontCouple info_font;
  FontCouple line_edit_font;
  FontCouple list_font;
  FontCouple menu_font;
  FontCouple spinor_font;
  FontCouple fav_font;

  FontCouple code_font;

  // switch

  VColor switch_on  = Green ;
  VColor switch_off =   Red ;

  // shift switch

  VColor shift_shift =    Black ;
  VColor shift_on    =    Green ;
  VColor shift_off   = DarkGray ;

  // progress

  unsigned progress_time   = 3_sectick ;
  unsigned progress_period =    2_tick ;

  VColor progress_border    =     Black ;
  VColor progress_grayUp    = DarkGreen ;
  VColor progress_snowUp    =     Green ;
  VColor progress_grayPing  =     Black ;
  VColor progress_snowPing  =      Snow ;
  VColor progress_grayArrow =      Blue ;
  VColor progress_snowArrow =   SkyBlue ;

  // scroll

  unsigned scroll_speedUpPeriod = 12_tick ;

  // line_edit

  unsigned line_edit_period = 10_tick ;

  Coord line_edit_ex = 3 ;

  // list

  VColor list_net = Black ;

  // scroll_list

  VColor scroll_list_title       = Navy ;
  VColor scroll_list_titleTop    = Aqua ;
  VColor scroll_list_titleBottom = Gray ;

  // slider

  Coord slider_dxy = 32 ;

  // spinor

  unsigned spinor_period = 1_sectick/2 ;

  // run button

  VColor run = Red ;

  unsigned run_period = 2_tick ;
  unsigned run_steps  =     10 ;

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

  Fraction hintWidth = Fraction(3) ;

  FontCouple title_font;
  FontCouple hint_font;

  VColor shadeColor = Violet ;
  Clr    shadeAlpha =     64 ;

  String text_Fatal_error = "Fatal error"_str ;
  String text_No_hint     = "<No hint available>"_str ;

  String hint_ResizeTopLeft     = "Resize top-left"_str ;
  String hint_ResizeLeft        = "Resize left"_str ;
  String hint_ResizeBottomLeft  = "Resize bottom-left"_str ;
  String hint_ResizeBottom      = "Resize bottom"_str ;
  String hint_ResizeBottomRight = "Resize bottom-right"_str ;
  String hint_ResizeRight       = "Resize right"_str ;
  String hint_ResizeTopRight    = "Resize top-right"_str ;

  String hint_Alert    = "Open/close alert view"_str ;
  String hint_Help     = "Help on/off"_str ;
  String hint_Minimize = "Minimize"_str ;
  String hint_Maximize = "Maximize"_str ;
  String hint_Restore  = "Restore"_str ;
  String hint_Close    = "Close"_str ;

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

  String text_New_file = "New file"_str ;

  String hint_FileHitList   = "Open/close the hit directory list"_str ;
  String hint_FileAddHit    = "Add the current directory to the hit list"_str ;
  String hint_FileUpdir     = "Goto the parent directory"_str ;
  String hint_FileCurdir    = "Current directory"_str ;
  String hint_FileDirList   = "Subdirectory list"_str ;
  String hint_FileList      = "File list"_str ;
  String hint_FileMakeDir   = "Create a new directory"_str ;
  String hint_FileRemoveDir = "Delete the selected directory"_str ;
  String hint_FileAlt       = "Choose between a new file or an existing file"_str ;

  String hint_FileEnableFilter = "Enable/disable this filter"_str ;
  String hint_FileDelFilter    = "Delete this filter"_str ;
  String hint_FileFilter       = "Filename filter, use * or ?"_str ;

  String hint_FileAddFilter = "Add a filter"_str ;

  // ConfigEditor

  Fraction cfg_edit_width = Fraction(1) ;
  Coord cfg_edit_mark_dy = 3 ;
  VColor cfg_edit_line = Black ;

  Fraction cfg_width = Fraction(8,2) ;
  Coord cfg_radius    =  15 ;
  Coord cfg_mix_len   = 350 ;
  Coord cfg_mix_width =  30 ;
  Coord cfg_white_len = 250 ;
  unsigned cfg_pal_len = 10 ;

  String text_cfg_all      =         "All"_str ;
  String text_cfg_Coord    =        "size"_str ;
  String text_cfg_MCoord   =  "milli-size"_str ;
  String text_cfg_VColor   =       "color"_str ;
  String text_cfg_Clr      = "color pitch"_str ;
  String text_cfg_unsigned =       "count"_str ;
  String text_cfg_String   =        "text"_str ;
  String text_cfg_Point    =       "point"_str ;
  String text_cfg_Font     =        "font"_str ;
  String text_cfg_bool     =        "bool"_str ;
  String text_cfg_Ratio    =       "ratio"_str ;

  String text_cfg_Set  =           "Set"_str ;
  String text_cfg_Back =          "Back"_str ;
  String text_cfg_Save =          "Save"_str ;
  String text_cfg_Self = "Apply to self"_str ;

  String hint_cfg_list = "Configuration parameters list"_str ;

  String hint_cfg_Set  = "Set the parameter"_str ;
  String hint_cfg_Back = "Revert back the parameter"_str ;
  String hint_cfg_Save = "Save the current settings"_str ;
  String hint_cfg_Self = "Apply parameters to this window"_str ;

  String hint_cfg_x = "Select x coordinate"_str ;
  String hint_cfg_y = "Select y coordinate"_str ;
  String hint_cfg_a = "Select divisible"_str ;
  String hint_cfg_b = "Select divider"_str ;

  String text_cfg_scalable    = "scalable"_str ;
  String text_cfg_monospace   = "monospace"_str ;
  String text_cfg_bold        = "bold"_str ;
  String text_cfg_italic      = "italic"_str ;

  String text_cfg_Hint = "Hint"_str ;

  String text_cfg_no_hint     = "No hint"_str ;
  String text_cfg_native_hint = "Native hint"_str ;
  String text_cfg_auto_hint   = "Auto hint"_str ;

  String text_cfg_Smooth = "Smooth"_str ;

  String text_cfg_no_smooth   = "No smooth"_str ;
  String text_cfg_smooth      = "Smooth"_str ;
  String text_cfg_RGB         = "LCD RGB"_str ;
  String text_cfg_BGR         = "LCD BGR"_str ;

  String text_cfg_kerning     = "Kerning"_str ;
  String text_cfg_strength    = "Strength"_str ;
  String text_cfg_sample      = "sample"_str ;
  String text_cfg_table       = "table"_str ;

  String hint_cfg_font_list     = "Font file list"_str ;
  String hint_cfg_height        = "Font height"_str ;
  String hint_cfg_length_enable = "Enable font length"_str ;
  String hint_cfg_length        = "Font length"_str ;

  String hint_cfg_color = "Left click to select, right click to copy selected to"_str ;

  // FontSelect

  String font_select_title = "Font selection"_str ;

  // FontReplace

  String font_replace_title = "Font replace"_str ;

  // FavListWindow

  VColor fav_text        =  Black ;
  VColor fav_text_select = Yellow ;

  VColor fav_section_text = White ;
  VColor fav_section_back = Black ;

  // FavWindow

  String hint_Ins         = "Insert current book"_str ;
  String hint_MoveUp      = "Move selected item up"_str ;
  String hint_MoveDown    = "Move selected item down"_str ;
  String hint_OpenAll     = "Open all sections"_str ;
  String hint_CloseAll    = "Close all sections"_str ;
  String hint_Del         = "Delete selected item"_str ;
  String hint_SectionName = "Enter a section name here"_str ;
  String hint_Path        = "Path of the selected book"_str ;

  // constructors

  UserPreferenceBag() noexcept {}

  // methods

  template <class Ptr,class Func>
  static void Members(Ptr ptr,Func func);

  void bindItems(ConfigItemBind &binder);

  void findFonts();
 };

/* class UserPreference */

class UserPreference : public ConfigBinder<UserPreferenceBag, // Update here

                                           ButtonWindow::ConfigType,
                                           KnobWindow::ConfigType,
                                           MoveButtonWindow::ConfigType,
                                           AllButtonWindow::ConfigType,
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
                                           ArrowProgressWindow::ConfigType,
                                           RadioWindow::ConfigType,
                                           RunButtonWindow::ConfigType,
                                           XScrollWindow::ConfigType,
                                           SimpleTextListWindow::ConfigType,
                                           SwitchWindow::ConfigType,
                                           TextWindow::ConfigType,
                                           TextLineWindow::ConfigType,
                                           TextLineCodeWindow::ConfigType,
                                           ScrollListWindow::ConfigType,
                                           XSplitWindow::ConfigType,
                                           XSliderWindow::ConfigType,
                                           SpinorWindow::ConfigType,
                                           XShiftSwitchWindow::ConfigType,

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
                                           FileFrame::ConfigType,
                                           DirFrame::ConfigType,

                                           CoordEditWindow::ConfigType,
                                           MCoordEditWindow::ConfigType,
                                           PointEditWindow::ConfigType,
                                           MixColorWindow::ConfigType,
                                           ColorListWindow::ConfigType,
                                           ColorEditWindow::ConfigType,
                                           FontEditWindow::ConfigType,
                                           RatioEditWindow::ConfigType,
                                           CharTableWindow::ConfigType,
                                           ConfigEditorWindow::ConfigType,
                                           ConfigEditorFrame::ConfigType,

                                           ExceptionBuf::ConfigType,
                                           FontSelectFrame::ConfigType,
                                           FontReplaceFrame::ConfigType,
                                           FavListWindow::ConfigType,
                                           FavFrame::ConfigType
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

