/* Book.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Book.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/PretextFileToMem.h>

namespace App {
namespace Book {

#include "Book.TypeSet.gen.h"

/* class BookMap::Pretext */

class BookMap::Pretext : public PretextMap
 {
  private:

   static StrLen Pretext1()
    {
     return
       "\r\n"
       "type Bool = uint8 ;\r\n"
       "\r\n"
       "Bool True = 1 ;\r\n"
       "\r\n"
       "Bool False = 0 ;\r\n"
       "\r\n"
       "type VColor = uint32 ;\r\n"
       "\r\n"
       "VColor NoColor = 0FFFFFFFFh ;\r\n"
       "\r\n"
       "type Coord = sint16 ;\r\n"
       "\r\n"
       "struct Point\r\n"
       " {\r\n"
       "  Coord x;\r\n"
       "  Coord y;\r\n"
       " };\r\n"
       " \r\n"
       "struct Ratio\r\n"
       " {\r\n"
       "  Coord a;\r\n"
       "  Coord b;\r\n"
       " }; \r\n"
       "\r\n"
       "\r\n"
       "struct Font\r\n"
       " {\r\n"
       "  text face;\r\n"
       "  Coord size;\r\n"
       "  \r\n"
       "  Bool bold = False ;\r\n"
       "  Bool italic = False ;\r\n"
       "  \r\n"
       "  int strength = 0 ;\r\n"
       " };\r\n"
       "\r\n"
       "struct Format\r\n"
       " {\r\n"
       "  Font *font = null ;\r\n"
       "  \r\n"
       "  VColor back = NoColor ;\r\n"
       "  VColor fore = NoColor ;\r\n"
       "  \r\n"
       "  type Effect = uint8 ;\r\n"
       "  \r\n"
       "  const Effect None = 0 ;\r\n"
       "  const Effect Underline = 1 ;\r\n"
       "  const Effect Strikeout = 2 ;\r\n"
       "  \r\n"
       "  Effect effect = None ;\r\n"
       " };\r\n"
       "\r\n"
       "struct OneLine\r\n"
       " {\r\n"
       "  type Align = uint8 ;\r\n"
       "  \r\n"
       "  const Align Left   = 0 ;  \r\n"
       "  const Align Right  = 1 ;  \r\n"
       "  const Align Center = 2 ;\r\n"
       "  \r\n"
       "  Align align = Left ;\r\n"
       " };\r\n"
       " \r\n"
       "struct MultiLine\r\n"
       " {\r\n"
       "  Ratio line_space = {1,1} ;\r\n"
       "  Ratio first_line_space = {2,1} ;\r\n"
       " }; \r\n"
       "\r\n"
       "struct Span\r\n"
       " {\r\n"
       "  text body;\r\n"
       "  \r\n"
       "  Format *fmt = null ;\r\n"
       "  \r\n"
       "  {Link,Page} * ref = null ;\r\n"
       " };\r\n"
       "\r\n"
       "Format DefaultFormat = {} ;\r\n"
       "\r\n"
       "MultiLine DefaultPlacement = {} ;\r\n"
       "\r\n"
       "struct Text\r\n"
       " {\r\n"
       "  Span[] list;\r\n"
       "  \r\n"
       "  Format *fmt = & ?DefaultFormat ;\r\n"
       "  \r\n"
       "  {OneLine,MultiLine} *placement = & ?DefaultPlacement ;\r\n"
       " };\r\n"
       " \r\n"
       "struct FixedSpan\r\n"
       " {\r\n"
       "  text body;\r\n"
       "  \r\n"
       "  Format *fmt = null ;\r\n"
       "  \r\n"
       "  {Link,Page} * ref = null ;\r\n"
       " };\r\n"
       " \r\n"
       "type Line = FixedSpan[] ; \r\n"
       " \r\n"
       "Format DefaultFixedFormat = {} ;\r\n"
       "\r\n"
       "struct FixedText\r\n"
       " {\r\n"
       "  Line[] list;\r\n"
       " \r\n"
       "  Format *fmt = & ?DefaultFixedFormat ;\r\n"
       " }; \r\n"
       "\r\n"
       "\r\n"
       "struct Bitmap\r\n"
       " {\r\n"
       "  text file_name;\r\n"
       " };\r\n"
       "\r\n"
       "\r\n"
       "struct ListItem\r\n"
       " {\r\n"
       "  text bullet;\r\n"
       "  Frame[] list;\r\n"
       " };\r\n"
       "\r\n"
       "Format DefaultBulletFormat = {} ;\r\n"
       "\r\n"
       "Coord DefaultBulletSpace = 5 ;\r\n"
       "Coord DefaultItemSpace = 0 ;\r\n"
       "\r\n"
       "struct TextList\r\n"
       " {\r\n"
       "  ListItem[] list;\r\n"
       "  \r\n"
       "  Format *bullet_fmt = & ?DefaultBulletFormat ;\r\n"
       "  \r\n"
       "  Coord bullet_space = ?DefaultBulletSpace ;\r\n"
       "  Coord item_space = ?DefaultItemSpace ;\r\n"
       " };\r\n"
       "\r\n"
       "\r\n"
       "struct SingleLine\r\n"
       " {\r\n"
       "  Ratio width = {1,1} ; \r\n"
       "  VColor line = NoColor ;\r\n"
       " };\r\n"
       " \r\n"
       "struct DoubleLine\r\n"
       " {\r\n"
       "  Ratio width = {1,1} ;\r\n"
       "  VColor gray = NoColor ;\r\n"
       "  VColor snow = NoColor ; \r\n"
       " };\r\n"
       " \r\n"
       "SingleLine DefaultSingleLine = {} ;\r\n"
       "\r\n"
       "DoubleLine DefaultDoubleLine = {} ;  \r\n"
       "\r\n"
       "Point DefaultInner = { 0 , 0 } ;\r\n"
       "\r\n"
       "Point DefaultOuter = { 0 , 0 } ;\r\n"
       "\r\n"
       "struct Frame\r\n"
       " {\r\n"
       "  {Text,FixedText,Bitmap,TextList} *body;\r\n"
       "  \r\n"
       "  {SingleLine,DoubleLine} *line = null ;\r\n"
       "  \r\n"
       "  Point inner = ?DefaultInner ;\r\n"
       "  Point outer = ?DefaultOuter ;\r\n"
       "  \r\n"
       "  VColor col = NoColor ;\r\n"
       " };\r\n"
       " \r\n"
       "\r\n"
       "struct Page\r\n"
       " {\r\n"
       "  text name;\r\n"
       "  \r\n"
       "  Frame[] list;\r\n"
       "  \r\n"
       "  VColor back = NoColor ;\r\n"
       "  VColor fore = NoColor ;\r\n"
       "  \r\n"
       "  Page *up = null ;\r\n"
       "  Page *prev = null ;\r\n"
       "  Page *next = null ;\r\n"
       " };\r\n"
       " \r\n"
       "struct Book\r\n"
       " {\r\n"
       "  text title;\r\n"
       "  \r\n"
       "  Page *start;\r\n"
       "  \r\n"
       "  VColor back = NoColor ;\r\n"
       "  VColor fore = NoColor ;\r\n"
       " }; \r\n"
       "\r\n"
       "struct Link\r\n"
       " {\r\n"
       "  Page *page;\r\n"
       "  ulen frame_index = 0 ;\r\n"
       " };\r\n"
       "\r\n"
       "\r\n"
       ""_c;
    }

   virtual void prepare()
    {
     add("pretext:/Book1.ddl"_c,Pretext1());
    }

  public:

   Pretext() noexcept {}

   ~Pretext() {}

   static Pretext Object;
 };

BookMap::Pretext BookMap::Pretext::Object;

/* class BookMap */

BookMap::BookMap()
 {
  mem=0;
  book=0;
 }

BookMap::~BookMap()
 {
  blank();
 }

void BookMap::blank()
 {
  book=0;

  MemFree(Replace_null(mem));
 }

ErrorText BookMap::load(StrLen file_name,PtrLen<char> ebuf)
 {
  blank();

  PrintBuf eout(ebuf);

  ReportExceptionTo<PrintBuf> report(eout);

  try
    {
     DDL::FileEngine<FileName, PretextFileToMem<FileToMem,Pretext::Object> > engine(eout);

     auto result=engine.process(file_name);

     if( !result )
       {
        Printf(eout,"\n@ #.q;",file_name);

        return eout.close();
       }
     else
       {
        DDL::TypedMap<TypeSet> map(result);
        MemAllocGuard guard(map.getLen());

        map(guard);

        if( TypeDef::Book *data=map.findConst<TypeDef::Book>("Data"_c) )
          {
           mem=guard.disarm();
           book=data;

           return Success;
          }
        else
          {
           Printf(eout,"Error : No Data\n@ #.q;",file_name);

           return eout.close();
          }
       }
    }
  catch(CatchType)
    {
     Printf(eout,"\n@ #.q;",file_name);

     return eout.close();
    }
 }

} // namespace Book
} // namespace App
