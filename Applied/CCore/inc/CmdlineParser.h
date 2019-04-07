/* CmdlineParser.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_CmdlineParser_h
#define CCore_inc_CmdlineParser_h

#include <CCore/inc/Gadget.h>

namespace CCore {

/* classes */

class CmdlineParser;

/* class CmdlineParser */

class CmdlineParser : NoCopy
 {
   StrLen text;

  private:

   struct ScanSpace;

   struct ScanFrame;

  public:

   explicit CmdlineParser(StrLen text_) : text(text_) {}

   class ArgBuilder
    {
      StrLen text;
      bool bsproc;
      bool ok;

     public:

      ArgBuilder() : bsproc(false),ok(false) {}

      ArgBuilder(StrLen text_,bool bsproc_=false) : text(text_),bsproc(bsproc_),ok(true) {}

      bool operator + () const { return ok; }

      bool operator ! () const { return !ok; }

      ulen getLen() const { return text.len; }

      PtrLen<char> operator () (char *buf) const;
    };

   ArgBuilder next();
 };

} // namespace CCore

#endif

