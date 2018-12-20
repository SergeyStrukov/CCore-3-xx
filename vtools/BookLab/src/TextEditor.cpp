/* TextEditor.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/TextEditor.h>

namespace App {

/* class TextEditor */

TextEditor::TextEditor(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_)
 {
 }

TextEditor::~TextEditor()
 {
 }

 // methods

Point TextEditor::getMinSize() const
 {
  return Point(100,100);
 }

void TextEditor::blank()
 {
 }

void TextEditor::load(PtrLen<BookLab::Span> text)
 {
 }

void TextEditor::load(PtrLen<BookLab::TextLine> text)
 {
 }

void TextEditor::save(DynArray<BookLab::Span> *pad)
 {
 }

void TextEditor::save(DynArray<BookLab::TextLine> *pad)
 {
 }

} // namespace App

