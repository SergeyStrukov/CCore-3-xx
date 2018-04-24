/* FontDatabase.h */
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
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_FontDatabase_h
#define CCore_inc_video_FontDatabase_h

#include <CCore/inc/video/FreeTypeFont.h>
#include <CCore/inc/video/Incremental.h>
#include <CCore/inc/video/ProgressScale.h>
#include <CCore/inc/video/PrintDDL.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/String.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/algon/BinarySearch.h>

namespace CCore {
namespace Video {

/* words */

enum BoldType { Bold };

enum ItalicType { Italic };

/* classes */

struct FontInfo;

class FontDatabase;

class FontIndex;

struct FontId;

class FontBuilder;

/* struct FontInfo */

struct FontInfo
 {
  String file_name;

  String family;
  String style;

  FontClass font_class = FontHasNoClass ;
  bool scalable = false ;
  bool monospace = false ;
  bool italic = false ;
  bool bold = false ;

  // check

  static bool CheckName(StrLen name);

  static bool CheckName(const String &name) { return CheckName(Range(name)); }

  bool checkNames() const;

  template <class Font>
  void fill(Font &font,bool &is_font);

  // constructors

  FontInfo() noexcept {}

  FontInfo(const String &file_name,bool &is_font,bool use_probe=false);

  // methods

  void turnSlash();

  // print object

  void printDDL(PrinterType &out) const
   {
    Printf(out,"{ #; , #; , #; , #; , #; , #; , #; , #; }",
                  DDLPrintableString(file_name),
                  DDLString(family),
                  DDLString(style),
                  (unsigned)font_class,
                  DDLBool(scalable),
                  DDLBool(monospace),
                  DDLBool(italic),
                  DDLBool(bold));
   }

  void print(PrinterType &out) const
   {
    Printf(out,"File #.q;\n",file_name);
    Printf(out,"Font #; #; class = #;\n",family,style,font_class);
    Putobj(out,"Flags"_c);

    if( scalable ) Putobj(out," scalable"_c);
    if( monospace ) Putobj(out," monospace"_c);
    if( italic ) Putobj(out," italic"_c);
    if( bold ) Putobj(out," bold"_c);

    out.put('\n');
   }
 };

/* class FontDatabase */

class FontDatabase : NoCopy
 {
   DynArray<FontInfo> list;

  private:

   static StrLen CacheFile();

   static StrLen Pretext();

   static String CatPath(StrLen path,StrLen name);

   static void Append(Collector<FontInfo> &obj,StrLen path,StrLen name);

   static void Append(Collector<FontInfo> &obj,StrLen dir);

   void tryCache(StrLen file_name);

  public:

   FontDatabase() noexcept;

   ~FontDatabase();

   // methods

   void populate();

   void turnSlash();

   PtrLen<const FontInfo> getList() const { return Range(list); }

   // cache methods

   void loadDDL(StrLen file_name);

   void saveDDL(StrLen file_name) const;

   void cache();

   void tryCache();

   void saveCache() const;

   // incremental

   class Step : NoCopy
    {
      Collector<String> file_list;
      Collector<FontInfo> info_list;
      PtrLen<String> cur_file;
      ulen pos;
      ProgressScale<ulen> scale;

      StepResult (Step::*stage)(IncrementalProgress &progress,FontDatabase &obj);

     private:

      void append(StrLen dir);

      StepResult stepDir(IncrementalProgress &progress,FontDatabase &obj);

      StepResult stepInfo(IncrementalProgress &progress,FontDatabase &obj);

     public:

      Step();

      ~Step();

      StepResult start(FontDatabase &obj,bool use_cache=true);

      StepResult step(IncrementalProgress &progress,FontDatabase &obj)
       {
        return (this->*stage)(progress,obj);
       }

      void erase() noexcept;
    };

   using Incremental = IncrementalBuilder<FontDatabase,Step> ;

   void cache(Incremental &inc,bool use_cache=true) { inc.start(*this,use_cache); }
 };

/* class FontIndex */

class FontIndex : NoCopy
 {
   DynArray<const FontInfo *> list;

  public:

   FontIndex() noexcept;

   ~FontIndex();

   void build(const FontDatabase &fdb,FuncType<bool,const FontInfo &> filter,FuncType<CmpResult,const FontInfo &,const FontInfo &> cmp)
    {
     auto info_list=fdb.getList();

     list.erase();

     list.reserve(info_list.len);

     for(auto &obj : info_list ) if( filter(obj) ) list.append_fill(&obj);

     list.shrink_extra();

     IncrSort(Range(list), [=] (const FontInfo *a,const FontInfo *b) { return cmp(*a,*b)<0; } );
    }

   PtrLen<const FontInfo *const> getList() const { return Range(list); }

   const FontInfo * find(FuncType<CmpResult,const FontInfo &> func) const // func(list) monotonic
    {
     auto r=getList();

     Algon::BinarySearch_if(r, [=] (const FontInfo *obj) { return func(*obj)>=0; } );

     if( +r && func(**r)==0 ) return *r;

     return 0;
    }
 };

/* struct FontId */

struct FontId
 {
  StrLen family;
  bool bold;
  bool italic;

  FontId(StrLen family_) : family(family_),bold(false),italic(false) {}

  FontId(const char *family_) : family(family_),bold(false),italic(false) {}

  FontId(const ConstTypeRangeableType<char> &obj) : family(Range_const(obj)),bold(false),italic(false) {}
 };

inline FontId operator | (FontId id,BoldType) { id.bold=true; return id; }

inline FontId operator | (FontId id,ItalicType) { id.italic=true; return id; }

/* class FontBuilder */

class FontBuilder : NoCopy
 {
   FontDatabase fdb;
   FontIndex index;

  private:

   static FreeTypeFont Build(const FontInfo *info,Coord font_size,const FreeTypeFont::Config &font_config);

   void buildIndex();

  public:

   FontBuilder();

   ~FontBuilder();

   void prepare();

   // incremental

   class Step : NoCopy
    {
      FontDatabase::Step dbstep;

     private:

      StepResult finish(StepResult result,FontBuilder &obj);

     public:

      Step();

      ~Step();

      StepResult start(FontBuilder &obj,bool use_cache=true);

      StepResult step(IncrementalProgress &progress,FontBuilder &obj);

      void erase() noexcept;
    };

   using Incremental = IncrementalBuilder<FontBuilder,Step> ;

   void prepare(Incremental &inc,bool use_cache=true) { inc.start(*this,use_cache); }

   // methods

   const FontDatabase & getDatabase() const { return fdb; }

   const FontInfo * find(StrLen family,bool bold,bool italic) const;

   FreeTypeFont build(StrLen family,bool bold,bool italic,Coord font_size,const FreeTypeFont::Config &font_config={}) const;

   Font build_or_default(StrLen family,bool bold,bool italic,Coord font_size,const FreeTypeFont::Config &font_config={}) const;

   FreeTypeFont build(FontId id,Coord font_size,const FreeTypeFont::Config &font_config={}) const
    {
     return build(id.family,id.bold,id.italic,font_size,font_config);
    }

   Font build_or_default(FontId id,Coord font_size,const FreeTypeFont::Config &font_config={}) const
    {
     return build_or_default(id.family,id.bold,id.italic,font_size,font_config);
    }
 };

} // namespace Video
} // namespace CCore

#endif

