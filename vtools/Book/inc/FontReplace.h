/* FontReplace.h */
//----------------------------------------------------------------------------------------
//
//  Project: Book 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef FontReplace_h
#define FontReplace_h

#include <inc/Book.h>

#include <CCore/inc/CompactMap.h>
#include <CCore/inc/StrKey.h>

namespace App {

/* classes */

class FontReplace;

/* class FontReplace */

class FontReplace : NoCopy
 {
   CompactRBTreeMap<StringKey,String,StrKey> map;

  private:

   static StrLen ReplaceFile();

   static StrLen Pretext();

   void loadDDL(StrLen file_name);

   void saveDDL(StrLen file_name) const;

   void load(StrLen dir,StrLen file);

   void save(StrLen dir,StrLen file) const;

   void add(StrLen face,StrLen replace);

  public:

   FontReplace();

   ~FontReplace();

   StrLen operator () (StrLen face) const;

   void addNotFound(StrLen face);

   void load() noexcept;

   void save() const noexcept;
 };

} // namespace App

#endif

