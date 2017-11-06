/* UserPreference.cpp */
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

#include <CCore/inc/video/UserPreference.h>

#include <CCore/inc/video/DesktopKey.h>
#include <CCore/inc/video/FontLookup.h>

namespace CCore {
namespace Video {

/* struct UserPreferenceBag */

template <class Ptr,class Func>
void UserPreferenceBag::Members(Ptr ptr,Func func) // Update here
 {
  func("frame_pos_ry"_c,ptr->frame_pos_ry);

  func("width"_c,ptr->width);

  func("space_dxy"_c,ptr->space_dxy);

  func("check_dxy"_c,ptr->check_dxy);
  func("knob_dxy"_c,ptr->knob_dxy);
  func("radio_dxy"_c,ptr->radio_dxy);
  func("switch_dxy"_c,ptr->switch_dxy);
  func("light_dxy"_c,ptr->light_dxy);
  func("scroll_dxy"_c,ptr->scroll_dxy);
  func("progress_dy"_c,ptr->progress_dy);

  func("gray"_c,ptr->gray);
  func("grayUp"_c,ptr->grayUp);
  func("snow"_c,ptr->snow);
  func("snowUp"_c,ptr->snowUp);

  func("back"_c,ptr->back);
  func("line"_c,ptr->line);
  func("inactive"_c,ptr->inactive);

  func("border"_c,ptr->border);
  func("focus"_c,ptr->focus);

  func("face"_c,ptr->face);
  func("faceUp"_c,ptr->faceUp);
  func("mark"_c,ptr->mark);
  func("alert"_c,ptr->alert);

  func("text_Yes"_c,ptr->text_Yes);
  func("text_No"_c,ptr->text_No);

  func("text_Ok"_c,ptr->text_Ok);
  func("text_Cancel"_c,ptr->text_Cancel);

  func("text_LoadFile"_c,ptr->text_LoadFile);
  func("text_SaveFile"_c,ptr->text_SaveFile);

  func("text_Alert"_c,ptr->text_Alert);
  func("text_AskSave"_c,ptr->text_AskSave);

  func("text_Error"_c,ptr->text_Error);
  func("text_Warning"_c,ptr->text_Warning);

  func("text_Close"_c,ptr->text_Close);
  func("text_Insert"_c,ptr->text_Insert);

  func("title_UserPref"_c,ptr->title_UserPref);
  func("title_AppPref"_c,ptr->title_AppPref);

  func("text_none"_c,ptr->text_none);

  func("text_cursor_dx"_c,ptr->text_cursor_dx);

  func("text_select"_c,ptr->text_select);
  func("text_cursor"_c,ptr->text_cursor);

  func("label_text"_c,ptr->label_text);
  func("contour_text"_c,ptr->contour_text);

  func("button_text"_c,ptr->button_text);
  func("message_text"_c,ptr->message_text);
  func("info_text"_c,ptr->info_text);
  func("line_edit_text"_c,ptr->line_edit_text);
  func("list_text"_c,ptr->list_text);
  func("spinor_text"_c,ptr->spinor_text);

  func("button_space"_c,ptr->button_space);
  func("message_space"_c,ptr->message_space);
  func("line_edit_space"_c,ptr->line_edit_space);
  func("info_space"_c,ptr->info_space);
  func("list_space"_c,ptr->list_space);
  func("menu_space"_c,ptr->menu_space);

  func("label_font"_c,ptr->label_font.param);
  func("contour_font"_c,ptr->contour_font.param);

  func("button_font"_c,ptr->button_font.param);
  func("message_font"_c,ptr->message_font.param);
  func("info_font"_c,ptr->info_font.param);
  func("line_edit_font"_c,ptr->line_edit_font.param);
  func("list_font"_c,ptr->list_font.param);
  func("menu_font"_c,ptr->menu_font.param);
  func("spinor_font"_c,ptr->spinor_font.param);

  func("code_font"_c,ptr->code_font.param);

  func("switch_on"_c,ptr->switch_on);
  func("switch_off"_c,ptr->switch_off);

  func("progress_time"_c,ptr->progress_time);
  func("progress_period"_c,ptr->progress_period);

  func("progress_border"_c,ptr->progress_border);
  func("progress_grayUp"_c,ptr->progress_grayUp);
  func("progress_snowUp"_c,ptr->progress_snowUp);
  func("progress_grayPing"_c,ptr->progress_grayPing);
  func("progress_snowPing"_c,ptr->progress_snowPing);
  func("progress_grayArrow"_c,ptr->progress_grayArrow);
  func("progress_snowArrow"_c,ptr->progress_snowArrow);

  func("scroll_speedUpPeriod"_c,ptr->scroll_speedUpPeriod);

  func("line_edit_period"_c,ptr->line_edit_period);

  func("line_edit_ex"_c,ptr->line_edit_ex);

  func("scroll_list_title"_c,ptr->scroll_list_title);
  func("scroll_list_titleTop"_c,ptr->scroll_list_titleTop);
  func("scroll_list_titleBottom"_c,ptr->scroll_list_titleBottom);

  func("spinor_period"_c,ptr->spinor_period);

  func("menu_back"_c,ptr->menu_back);
  func("menu_text"_c,ptr->menu_text);
  func("menu_hilight"_c,ptr->menu_hilight);
  func("menu_select"_c,ptr->menu_select);
  func("menu_hot"_c,ptr->menu_hot);
  func("menu_hotcolor"_c,ptr->menu_hotcolor);

  func("blinkTime"_c,ptr->blinkTime);
  func("blinkPeriod"_c,ptr->blinkPeriod);

  func("frame_dxy"_c,ptr->frame_dxy);
  func("title_dy"_c,ptr->title_dy);
  func("btn_dx"_c,ptr->btn_dx);
  func("btn_dy"_c,ptr->btn_dy);

  func("frame"_c,ptr->frame);
  func("frameHilight"_c,ptr->frameHilight);
  func("frameDrag"_c,ptr->frameDrag);

  func("title"_c,ptr->title);
  func("titleActive"_c,ptr->titleActive);
  func("titleInactive"_c,ptr->titleInactive);

  func("drag"_c,ptr->drag);
  func("dragHilight"_c,ptr->dragHilight);
  func("dragActive"_c,ptr->dragActive);
  func("dragSmall"_c,ptr->dragSmall);

  func("btnFace"_c,ptr->btnFace);
  func("btnFaceHilight"_c,ptr->btnFaceHilight);
  func("btnPict"_c,ptr->btnPict);
  func("btnPictClose"_c,ptr->btnPictClose);
  func("btnPictAlert"_c,ptr->btnPictAlert);
  func("btnPictNoAlert"_c,ptr->btnPictNoAlert);
  func("btnPictCloseAlert"_c,ptr->btnPictCloseAlert);

  func("hintBack"_c,ptr->hintBack);
  func("hintText"_c,ptr->hintText);
  func("hintBorder"_c,ptr->hintBorder);

  func("hintWidth"_c,ptr->hintWidth);

  func("title_font"_c,ptr->title_font.param);
  func("hint_font"_c,ptr->hint_font.param);

  func("shadeColor"_c,ptr->shadeColor);
  func("shadeAlpha"_c,ptr->shadeAlpha);

  func("text_Fatal_error"_c,ptr->text_Fatal_error);
  func("text_No_hint"_c,ptr->text_No_hint);

  func("hint_ResizeTopLeft"_c,ptr->hint_ResizeTopLeft);
  func("hint_ResizeLeft"_c,ptr->hint_ResizeLeft);
  func("hint_ResizeBottomLeft"_c,ptr->hint_ResizeBottomLeft);
  func("hint_ResizeBottom"_c,ptr->hint_ResizeBottom);
  func("hint_ResizeBottomRight"_c,ptr->hint_ResizeBottomRight);
  func("hint_ResizeRight"_c,ptr->hint_ResizeRight);
  func("hint_ResizeTopRight"_c,ptr->hint_ResizeTopRight);

  func("hint_Alert"_c,ptr->hint_Alert);
  func("hint_Help"_c,ptr->hint_Help);
  func("hint_Minimize"_c,ptr->hint_Minimize);
  func("hint_Maximize"_c,ptr->hint_Maximize);
  func("hint_Restore"_c,ptr->hint_Restore);
  func("hint_Close"_c,ptr->hint_Close);

  func("exception_back"_c,ptr->exception_back);
  func("exception_text"_c,ptr->exception_text);
  func("exception_divider"_c,ptr->exception_divider);

  func("message_knob_dxy"_c,ptr->message_knob_dxy);

  func("file_alt_dxy"_c,ptr->file_alt_dxy);

  func("file_accent"_c,ptr->file_accent);
  func("file_filter_text"_c,ptr->file_filter_text);

  func("file_faceRight"_c,ptr->file_faceRight);
  func("file_faceDown"_c,ptr->file_faceDown);

  func("file_filter_font"_c,ptr->file_filter_font.param);

  func("text_New_file"_c,ptr->text_New_file);

  func("hint_FileHitList"_c,ptr->hint_FileHitList);
  func("hint_FileAddHit"_c,ptr->hint_FileAddHit);
  func("hint_FileUpdir"_c,ptr->hint_FileUpdir);
  func("hint_FileCurdir"_c,ptr->hint_FileCurdir);
  func("hint_FileDirList"_c,ptr->hint_FileDirList);
  func("hint_FileList"_c,ptr->hint_FileList);
  func("hint_FileMakeDir"_c,ptr->hint_FileMakeDir);
  func("hint_FileRemoveDir"_c,ptr->hint_FileRemoveDir);
  func("hint_FileAlt"_c,ptr->hint_FileAlt);

  func("hint_FileEnableFilter"_c,ptr->hint_FileEnableFilter);
  func("hint_FileDelFilter"_c,ptr->hint_FileDelFilter);
  func("hint_FileFilter"_c,ptr->hint_FileFilter);

  func("hint_FileAddFilter"_c,ptr->hint_FileAddFilter);

  func("cfg_edit_width"_c,ptr->cfg_edit_width);
  func("cfg_edit_mark_dy"_c,ptr->cfg_edit_mark_dy);
  func("cfg_edit_line"_c,ptr->cfg_edit_line);

  func("cfg_width"_c,ptr->cfg_width);
  func("cfg_radius"_c,ptr->cfg_radius);
  func("cfg_mix_len"_c,ptr->cfg_mix_len);
  func("cfg_mix_width"_c,ptr->cfg_mix_width);
  func("cfg_white_len"_c,ptr->cfg_white_len);
  func("cfg_pal_len"_c,ptr->cfg_pal_len);

  func("text_cfg_all"_c,ptr->text_cfg_all);
  func("text_cfg_Coord"_c,ptr->text_cfg_Coord);
  func("text_cfg_MCoord"_c,ptr->text_cfg_MCoord);
  func("text_cfg_VColor"_c,ptr->text_cfg_VColor);
  func("text_cfg_Clr"_c,ptr->text_cfg_Clr);
  func("text_cfg_unsigned"_c,ptr->text_cfg_unsigned);
  func("text_cfg_String"_c,ptr->text_cfg_String);
  func("text_cfg_Point"_c,ptr->text_cfg_Point);
  func("text_cfg_Font"_c,ptr->text_cfg_Font);
  func("text_cfg_bool"_c,ptr->text_cfg_bool);
  func("text_cfg_Ratio"_c,ptr->text_cfg_Ratio);

  func("text_cfg_Set"_c,ptr->text_cfg_Set);
  func("text_cfg_Back"_c,ptr->text_cfg_Back);
  func("text_cfg_Save"_c,ptr->text_cfg_Save);
  func("text_cfg_Self"_c,ptr->text_cfg_Self);

  func("hint_cfg_list"_c,ptr->hint_cfg_list);
  func("hint_cfg_Set"_c,ptr->hint_cfg_Set);
  func("hint_cfg_Back"_c,ptr->hint_cfg_Back);
  func("hint_cfg_Save"_c,ptr->hint_cfg_Save);
  func("hint_cfg_Self"_c,ptr->hint_cfg_Self);

  func("hint_cfg_x"_c,ptr->hint_cfg_x);
  func("hint_cfg_y"_c,ptr->hint_cfg_y);
  func("hint_cfg_a"_c,ptr->hint_cfg_a);
  func("hint_cfg_b"_c,ptr->hint_cfg_b);

  func("text_cfg_scalable"_c,ptr->text_cfg_scalable);
  func("text_cfg_monospace"_c,ptr->text_cfg_monospace);
  func("text_cfg_bold"_c,ptr->text_cfg_bold);
  func("text_cfg_italic"_c,ptr->text_cfg_italic);

  func("text_cfg_Hint"_c,ptr->text_cfg_Hint);

  func("text_cfg_no_hint"_c,ptr->text_cfg_no_hint);
  func("text_cfg_native_hint"_c,ptr->text_cfg_native_hint);
  func("text_cfg_auto_hint"_c,ptr->text_cfg_auto_hint);

  func("text_cfg_Smooth"_c,ptr->text_cfg_Smooth);

  func("text_cfg_no_smooth"_c,ptr->text_cfg_no_smooth);
  func("text_cfg_smooth"_c,ptr->text_cfg_smooth);
  func("text_cfg_RGB"_c,ptr->text_cfg_RGB);
  func("text_cfg_BGR"_c,ptr->text_cfg_BGR);

  func("text_cfg_kerning"_c,ptr->text_cfg_kerning);
  func("text_cfg_strength"_c,ptr->text_cfg_strength);
  func("text_cfg_sample"_c,ptr->text_cfg_sample);
  func("text_cfg_table"_c,ptr->text_cfg_table);

  func("hint_cfg_font_list"_c,ptr->hint_cfg_font_list);
  func("hint_cfg_height"_c,ptr->hint_cfg_height);
  func("hint_cfg_length_enable"_c,ptr->hint_cfg_length_enable);
  func("hint_cfg_length"_c,ptr->hint_cfg_length);

  func("hint_cfg_color"_c,ptr->hint_cfg_color);
 }

void UserPreferenceBag::bind(ConfigItemBind &binder) // Update here
 {
  binder.group("Common"_def);

   binder.item("Y-position ratio"_def,frame_pos_ry);
   binder.item("line width"_def,width);
   binder.item("space"_def,space_dxy);
   binder.space();
   binder.item("check box"_def,check_dxy);
   binder.item("knob box"_def,knob_dxy);
   binder.item("radio box"_def,radio_dxy);
   binder.item("switch box"_def,switch_dxy);
   binder.item("light box"_def,light_dxy);
   binder.item("scroll width"_def,scroll_dxy);
   binder.item("progress height"_def,progress_dy);
   binder.space();
   binder.item("gray"_def,gray);
   binder.item("grayUp"_def,grayUp);
   binder.item("snow"_def,snow);
   binder.item("snowUp"_def,snowUp);
   binder.space();
   binder.item("back"_def,back);
   binder.item("line"_def,line);
   binder.item("inactive"_def,inactive);
   binder.space();
   binder.item("border"_def,border);
   binder.item("focus"_def,focus);
   binder.space();
   binder.item("face"_def,face);
   binder.item("faceUp"_def,faceUp);
   binder.item("mark"_def,mark);
   binder.item("alert"_def,alert);
   binder.space();
   binder.item("'Yes'"_def,text_Yes);
   binder.item("'No'"_def,text_No);
   binder.item("'Ok'"_def,text_Ok);
   binder.item("'Cancel'"_def,text_Cancel);
   binder.item("'LoadFile'"_def,text_LoadFile);
   binder.item("'SaveFile'"_def,text_SaveFile);
   binder.item("'Alert'"_def,text_Alert);
   binder.item("'AskSave'"_def,text_AskSave);
   binder.item("'Error'"_def,text_Error);
   binder.item("'Warning'"_def,text_Warning);
   binder.item("'Close'"_def,text_Close);
   binder.item("'Insert'"_def,text_Insert);
   binder.item("'UserPref'"_def,title_UserPref);
   binder.item("'AppPref'"_def,title_AppPref);
   binder.item("'<none>'"_def,text_none);

  binder.group("Text"_def);

   binder.item("cursor width"_def,text_cursor_dx);
   binder.space();
   binder.item("select"_def,text_select);
   binder.item("cursor"_def,text_cursor);
   binder.space();
   binder.item("label text"_def,label_text);
   binder.item("contour text"_def,contour_text);
   binder.space();
   binder.item("button text"_def,button_text);
   binder.item("message text"_def,message_text);
   binder.item("info text"_def,info_text);
   binder.item("editor text"_def,line_edit_text);
   binder.item("list text"_def,list_text);
   binder.item("spinor text"_def,spinor_text);
   binder.space();
   binder.item("button space"_def,button_space);
   binder.item("message space"_def,message_space);
   binder.item("editor space"_def,line_edit_space);
   binder.item("info space"_def,info_space);
   binder.item("list space"_def,list_space);
   binder.item("menu space"_def,menu_space);
   binder.space();
   binder.item("label font"_def,label_font);
   binder.item("contour font"_def,contour_font);
   binder.space();
   binder.item("button font"_def,button_font);
   binder.item("message font"_def,message_font);
   binder.item("info font"_def,info_font);
   binder.item("editor font"_def,line_edit_font);
   binder.item("list font"_def,list_font);
   binder.item("menu font"_def,menu_font);
   binder.item("spinor font"_def,spinor_font);
   binder.space();
   binder.item("code font"_def,code_font);

  binder.group("Switch"_def);

   binder.item("on"_def,switch_on);
   binder.item("off"_def,switch_off);

  binder.group("Progress"_def);

   binder.item("ping time"_def,progress_time);
   binder.item("ping period"_def,progress_period);
   binder.space();
   binder.item("border"_def,progress_border);
   binder.item("grayUp"_def,progress_grayUp);
   binder.item("snowUp"_def,progress_snowUp);
   binder.item("grayPing"_def,progress_grayPing);
   binder.item("snowPing"_def,progress_snowPing);
   binder.item("grayArrow"_def,progress_grayArrow);
   binder.item("snowArrow"_def,progress_snowArrow);

  binder.group("Scroll"_def);

   binder.item("speedUp period"_def,scroll_speedUpPeriod);

  binder.group("Line editor"_def);

   binder.item("cursor blink period"_def,line_edit_period);
   binder.space();
   binder.item("round ext"_def,line_edit_ex);

  binder.group("Scroll list"_def);

   binder.item("title"_def,scroll_list_title);
   binder.item("title top"_def,scroll_list_titleTop);
   binder.item("title bottom"_def,scroll_list_titleBottom);

  binder.group("Spinor"_def);

   binder.item("spinor period"_def,spinor_period);

  binder.group("Menu"_def);

   binder.item("back"_def,menu_back);
   binder.item("text"_def,menu_text);
   binder.item("hilight"_def,menu_hilight);
   binder.item("select"_def,menu_select);
   binder.item("hot"_def,menu_hot);
   binder.space();
   binder.item("use hotcolor"_def,menu_hotcolor);

  binder.group("Frames"_def);

   binder.item("alert blink time"_def,blinkTime);
   binder.item("alert blink period"_def,blinkPeriod);
   binder.space();
   binder.item("'Fatal error'"_def,text_Fatal_error);
   binder.item("'<No hint available>'"_def,text_No_hint);
   binder.space();
   binder.item("?'Resize top-left'"_def,hint_ResizeTopLeft);
   binder.item("?'Resize left'"_def,hint_ResizeLeft);
   binder.item("?'Resize bottom-left'"_def,hint_ResizeBottomLeft);
   binder.item("?'Resize bottom'"_def,hint_ResizeBottom);
   binder.item("?'Resize bottom-right'"_def,hint_ResizeBottomRight);
   binder.item("?'Resize right'"_def,hint_ResizeRight);
   binder.item("?'Resize top-right'"_def,hint_ResizeTopRight);
   binder.space();
   binder.item("?'Open/close alert view'"_def,hint_Alert);
   binder.item("?'Help on/off'"_def,hint_Help);
   binder.item("?'Minimize'"_def,hint_Minimize);
   binder.item("?'Maximize'"_def,hint_Maximize);
   binder.item("?'Restore'"_def,hint_Restore);
   binder.item("?'Close'"_def,hint_Close);
   binder.space();
   binder.item("frame width"_def,frame_dxy);
   binder.item("title height"_def,title_dy);
   binder.item("frame button width"_def,btn_dx);
   binder.item("frame button height"_def,btn_dy);
   binder.space();
   binder.item("frame"_def,frame);
   binder.item("hilight frame"_def,frameHilight);
   binder.item("drag frame"_def,frameDrag);
   binder.item("title"_def,title);
   binder.item("active title"_def,titleActive);
   binder.item("inactive title"_def,titleInactive);
   binder.space();
   binder.item("drag"_def,drag);
   binder.item("hilight drag"_def,dragHilight);
   binder.item("active drag"_def,dragActive);
   binder.item("small size indicator"_def,dragSmall);
   binder.space();
   binder.item("button face"_def,btnFace);
   binder.item("button hilight"_def,btnFaceHilight);
   binder.item("button picture"_def,btnPict);
   binder.item("button close picture"_def,btnPictClose);
   binder.item("button alert picture"_def,btnPictAlert);
   binder.item("button no-alert picture"_def,btnPictNoAlert);
   binder.item("button close-alert picture"_def,btnPictCloseAlert);
   binder.space();
   binder.item("hint back"_def,hintBack);
   binder.item("hint text"_def,hintText);
   binder.item("hint border"_def,hintBorder);
   binder.item("hint line width"_def,hintWidth);
   binder.space();
   binder.item("title font"_def,title_font);
   binder.item("hint font"_def,hint_font);
   binder.space();
   binder.item("shade color"_def,shadeColor);
   binder.item("shade alpha"_def,shadeAlpha);

  binder.group("Exception window"_def);

   binder.item("back"_def,exception_back);
   binder.item("text"_def,exception_text);
   binder.item("divider"_def,exception_divider);

  binder.group("Message window"_def);

   binder.item("knob box"_def,message_knob_dxy);

  binder.group("File window"_def);

   binder.item("alt box"_def,file_alt_dxy);
   binder.space();
   binder.item("slash accent"_def,file_accent);
   binder.space();
   binder.item("alt right"_def,file_faceRight);
   binder.item("alt down"_def,file_faceDown);
   binder.space();
   binder.item("filter text"_def,file_filter_text);
   binder.item("filter font"_def,file_filter_font);
   binder.space();
   binder.item("'New file'"_def,text_New_file);
   binder.space();
   binder.item("?'Hit list'"_def,hint_FileHitList);
   binder.item("?'Add hit'"_def,hint_FileAddHit);
   binder.item("?'Goto the parent'"_def,hint_FileUpdir);
   binder.item("?'Current directory'"_def,hint_FileCurdir);
   binder.item("?'Subdirectory list'"_def,hint_FileDirList);
   binder.item("?'File list'"_def,hint_FileList);
   binder.item("?'Make directory'"_def,hint_FileMakeDir);
   binder.item("?'Remove directory'"_def,hint_FileRemoveDir);
   binder.item("?'Alt new/existing file'"_def,hint_FileAlt);
   binder.item("?'Enable filter'"_def,hint_FileEnableFilter);
   binder.item("?'Delete filter'"_def,hint_FileDelFilter);
   binder.item("?'Filename filter'"_def,hint_FileFilter);
   binder.item("?'Add filter'"_def,hint_FileAddFilter);

  binder.group("ConfigEditor window"_def);

   binder.item("line width"_def,cfg_edit_width);
   binder.item("mark height"_def,cfg_edit_mark_dy);
   binder.item("line"_def,cfg_edit_line);
   binder.space();
   binder.item("width"_def,cfg_width);
   binder.item("radius"_def,cfg_radius);
   binder.item("mix length"_def,cfg_mix_len);
   binder.item("mix width"_def,cfg_mix_width);
   binder.item("white length"_def,cfg_white_len);
   binder.item("palette row count"_def,cfg_pal_len);
   binder.space();
   binder.item("'all'"_def,text_cfg_all);
   binder.item("'Coord'"_def,text_cfg_Coord);
   binder.item("'MCoord'"_def,text_cfg_MCoord);
   binder.item("'VColor'"_def,text_cfg_VColor);
   binder.item("'Clr'"_def,text_cfg_Clr);
   binder.item("'unsigned'"_def,text_cfg_unsigned);
   binder.item("'String'"_def,text_cfg_String);
   binder.item("'Point'"_def,text_cfg_Point);
   binder.item("'Font'"_def,text_cfg_Font);
   binder.item("'bool'"_def,text_cfg_bool);
   binder.item("'Ratio'"_def,text_cfg_Ratio);
   binder.space();
   binder.item("'Set'"_def,text_cfg_Set);
   binder.item("'Back'"_def,text_cfg_Back);
   binder.item("'Save'"_def,text_cfg_Save);
   binder.item("'Self'"_def,text_cfg_Self);
   binder.space();
   binder.item("?'item list'"_def,hint_cfg_list);
   binder.item("?'Set'"_def,hint_cfg_Set);
   binder.item("?'Back'"_def,hint_cfg_Back);
   binder.item("?'Save'"_def,hint_cfg_Save);
   binder.item("?'Self'"_def,hint_cfg_Self);
   binder.space();
   binder.item("?'x-coord'"_def,hint_cfg_x);
   binder.item("?'y-coord'"_def,hint_cfg_y);
   binder.item("?'divisible'"_def,hint_cfg_a);
   binder.item("?'divider'"_def,hint_cfg_b);
   binder.space();
   binder.item("'scalable'"_def,text_cfg_scalable);
   binder.item("'monospace'"_def,text_cfg_monospace);
   binder.item("'bold'"_def,text_cfg_bold);
   binder.item("'italic'"_def,text_cfg_italic);
   binder.space();
   binder.item("'Hint'"_def,text_cfg_Hint);
   binder.space();
   binder.item("'No hint'"_def,text_cfg_no_hint);
   binder.item("'Native hint'"_def,text_cfg_native_hint);
   binder.item("'Auto hint'"_def,text_cfg_auto_hint);
   binder.space();
   binder.item("'Smooth'"_def,text_cfg_Smooth);
   binder.space();
   binder.item("'No smooth'"_def,text_cfg_no_smooth);
   binder.item("'Smooth'"_def,text_cfg_smooth);
   binder.item("'LCD RGB'"_def,text_cfg_RGB);
   binder.item("'LCD BGR'"_def,text_cfg_BGR);
   binder.space();
   binder.item("'Kerning'"_def,text_cfg_kerning);
   binder.item("'Strength'"_def,text_cfg_strength);
   binder.item("'sample'"_def,text_cfg_sample);
   binder.item("'table'"_def,text_cfg_table);
   binder.space();
   binder.item("?'Font file list'"_def,hint_cfg_font_list);
   binder.item("?'Font height'"_def,hint_cfg_height);
   binder.item("?'Enable font length'"_def,hint_cfg_length_enable);
   binder.item("?'Font length'"_def,hint_cfg_length);
   binder.space();
   binder.item("?'Color hint'"_def,hint_cfg_color);
 }

void UserPreferenceBag::createFonts() // Update fonts here
 {
  label_font.create();
  contour_font.create();
  button_font.create();
  message_font.create();
  info_font.create();
  line_edit_font.create();
  list_font.create();
  menu_font.create();
  spinor_font.create();

  code_font.create();

  title_font.create();
  hint_font.create();

  file_filter_font.create();
 }

void UserPreferenceBag::findFonts() // Update fonts here
 {
  FontLookup dev;

  struct Bolder : FreeTypeFont::Config
   {
    explicit Bolder(int strength_) { strength=strength_; }
   };

  label_font=dev.build("Georgia"_c,false,true,18);
  contour_font=dev.build("Microsoft Sans Serif"_c,false,false,20);
  button_font=dev.build("Tahoma"_c,false,false,20,Bolder(20));
  message_font=dev.build("Bookman Old Style"_c,false,false,20);
  info_font=dev.build("Bookman Old Style"_c,false,false,18);
  line_edit_font=dev.build("Segoe UI"_c,false,true,20);
  list_font=dev.build("Bookman Old Style"_c,false,true,18);
  menu_font=dev.build("Georgia"_c,false,true,17);
  spinor_font=dev.build("Anonymous Pro"_c,false,false,22,Bolder(20));
  code_font=dev.build("Anonymous Pro"_c,false,false,20,Bolder(20));
  title_font=dev.build("Times New Roman"_c,false,false,28);
  hint_font=dev.build("Bookman Old Style"_c,true,true,17);
  file_filter_font=dev.build("Anonymous Pro"_c,false,false,20,Bolder(20));
 }

/* class UserPreference */

StrLen UserPreference::PrefFile() { return "/UserPreference.ddl"_c; }

UserPreference::UserPreference() noexcept
 {
 }

UserPreference::~UserPreference()
 {
 }

void UserPreference::sync() noexcept
 {
  if( !syncHome(HomeKey(),PrefFile()) )
    {
     ref().findFonts();

     update();
    }
 }

void UserPreference::update() noexcept
 {
  updateHome(HomeKey(),PrefFile());
 }

} // namespace Video
} // namespace CCore

