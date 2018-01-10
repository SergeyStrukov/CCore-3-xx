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

namespace App {
namespace Book {

#include "Book.TypeSet.gen.h"

/* class BookMap */

StrLen BookMap::Pretext()
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
" };\r\n"
"\r\n"
"VColor DefaultBack = NoColor ;\r\n"
"VColor DefaultFore = NoColor ;\r\n"
"\r\n"
"struct Format\r\n"
" {\r\n"
"  Font *font = null ;\r\n"
"  \r\n"
"  VColor back = ?DefaultBack ;\r\n"
"  VColor fore = ?DefaultFore ;\r\n"
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
"  text[] list;\r\n"
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
"struct Line\r\n"
" {\r\n"
"  FixedSpan[] list;\r\n"
" }; \r\n"
" \r\n"
"struct FixedText\r\n"
" {\r\n"
"  Line[] list;\r\n"
" \r\n"
"  Format *fmt = & ?DefaultFormat ;\r\n"
" }; \r\n"
"\r\n"
"\r\n"
"struct Bitmap\r\n"
" {\r\n"
"  VColor[][] map;\r\n"
" };\r\n"
"\r\n"
"\r\n"
"struct Frame\r\n"
" {\r\n"
"  {Text,FixedText,Bitmap} *body;\r\n"
"  \r\n"
"  type LineType = uint8 ;\r\n"
"  \r\n"
"  const LineType None = 0 ;\r\n"
"  const LineType Single = 1 ;\r\n"
"  const LineType Double = 2 ;\r\n"
"  \r\n"
"  LineType line_type = None ; \r\n"
" \r\n"
"  Point inner = { 0 , 0 } ;\r\n"
"  Point outer = { 0 , 0 } ;\r\n"
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
" };\r\n"
" \r\n"
"struct Book\r\n"
" {\r\n"
"  text title;\r\n"
"  \r\n"
"  Page * [] list;\r\n"
"  \r\n"
"  VColor back = NoColor ;\r\n"
"  VColor fore = NoColor ;\r\n"
" }; \r\n"
"\r\n"
"struct Link\r\n"
" {\r\n"
"  ulen page_index;\r\n"
"  ulen frame_index = 0 ;\r\n"
" };\r\n"
"\r\n"
"\r\n"
""_c;
 }

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

auto BookMap::load(StrLen file_name,PtrLen<char> ebuf) -> Result
 {
  blank();

  PrintBuf eout(ebuf);

  ReportExceptionTo<PrintBuf> report(eout);

  try
    {
     DDL::FileEngine<FileName,FileToMem> engine(eout);

     auto result=engine.process(file_name,Pretext());

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

           return {};
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
