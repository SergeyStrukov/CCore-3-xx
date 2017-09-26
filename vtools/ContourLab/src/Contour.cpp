/* Contour.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: ContourLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Contour.h>
#include <inc/Parser.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/PrintStem.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>

#include <CCore/inc/StrMap.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>

namespace App {

/* functions */

void GuardTypeMismatch()
 {
  Printf(Exception,"App::GuardType(...) : type mismatch");
 }

/* struct Formula */

Formular::Object::Base Formular::Object::Base::Default;

/* class Contour::ItemInfo */

class Contour::ItemInfo::Base : public ComboInfoBase
 {
   const DynArray<Item> &data;

  public:

   explicit Base(const DynArray<Item> &data_) : data(data_) {}

   virtual ~Base() {}

   // AbstractComboInfo

   ulen getLineCount() const
    {
     return data.getLen();
    }

   ComboInfoItem getLine(ulen index) const
    {
     return {ComboInfoText,Range(data.at(index).label.name)};
    }
 };

Contour::ItemInfo::ItemInfo(const DynArray<Item> &data)
 : ComboInfo(new Base(data))
 {
 }

Contour::ItemInfo::~ItemInfo()
 {
 }

/* class Contour */

bool Contour::UpItem(DynArray<Item> &a,ulen index)
 {
  auto r=Range(a);

  if( index>0 && index<r.len )
    {
     Swap(r[index],r[index-1]);

     r[index].obj.updateIndex(index);
     r[index-1].obj.updateIndex(index-1);

     return true;
    }

  return false;
 }

bool Contour::DownItem(DynArray<Item> &a,ulen index)
 {
  auto r=Range(a);

  if( r.len && index<r.len-1 )
    {
     Swap(r[index],r[index+1]);

     r[index].obj.updateIndex(index);
     r[index+1].obj.updateIndex(index+1);

     return true;
    }

  return false;
 }

void Contour::UpdateIndexes(DynArray<Item> &a,ulen index)
 {
  for(ulen i=index,len=a.getLen(); i<len ;i++) a[i].obj.updateIndex(i);
 }

bool Contour::addPad(ulen index,PtrLen<const Char> name,Object obj)
 {
  if( index>pads.getLen() )
    {
     Printf(Exception,"App::Contour::addPad(#;,...) : out of range",index);
    }

  pads.reserve(1);

  NameKey k(name);

  auto result=map.find_or_add(k,obj);

  if( !result.new_flag ) return false;

  Label label(result.key->name);

  Item item{label,obj};

  ArrayCopyIns(pads,index,item);

  obj.setIndex({IndexPad,index});

  UpdateIndexes(pads,index+1);

  return true;
 }

#ifdef CCORE_UTF8

bool Contour::addPad(ulen index,StrLen name,Object obj)
 {
  if( index>pads.getLen() )
    {
     Printf(Exception,"App::Contour::addPad(#;,...) : out of range",index);
    }

  pads.reserve(1);

  StrKey k(name);

  auto result=map.find_or_add(k,obj);

  if( !result.new_flag ) return false;

  Label label(result.key->name);

  Item item{label,obj};

  ArrayCopyIns(pads,index,item);

  obj.setIndex({IndexPad,index});

  UpdateIndexes(pads,index+1);

  return true;
 }

#endif

bool Contour::addFormula(ulen index,PtrLen<const Char> name,Object obj)
 {
  if( index>formulas.getLen() )
    {
     Printf(Exception,"App::Contour::addFormula(#;,...) : out of range",index);
    }

  formulas.reserve(1);

  NameKey k(name);

  auto result=map.find_or_add(k,obj);

  if( !result.new_flag ) return false;

  Label label(result.key->name);

  Item item{label,obj};

  ArrayCopyIns(formulas,index,item);

  obj.setIndex({IndexFormula,index});

  UpdateIndexes(formulas,index+1);

  return true;
 }

bool Contour::setFormula(ulen index,PtrLen<const Char> name,Object obj)
 {
  NameKey k(name);

  auto result=map.find_or_add(k,obj);

  if( !result.new_flag ) return false;

  Label label(result.key->name);

  Item item{label,obj};

  formulas[index]=item;

  obj.setIndex({IndexFormula,index});

  return true;
 }

#ifdef CCORE_UTF8

bool Contour::setFormula(ulen index,StrLen name,Object obj)
 {
  StrKey k(name);

  auto result=map.find_or_add(k,obj);

  if( !result.new_flag ) return false;

  Label label(result.key->name);

  Item item{label,obj};

  formulas[index]=item;

  obj.setIndex({IndexFormula,index});

  return true;
 }

#endif

bool Contour::testName(PtrLen<const Char> name) const
 {
  NameKey k(name);

  return !map.find(k);
 }

bool Contour::delItem(DynArray<Item> &a,ulen index)
 {
  if( index<a.getLen() )
    {
     StrKey key(Range(a[index].label.name));

     map.del(key);

     a[index].obj.setIndex({IndexNone});

     ArrayCopyDel(a,index);

     UpdateIndexes(a,index);

     return true;
    }

  return false;
 }

Contour::Contour()
 {
 }

Contour::~Contour()
 {
 }

 // pad list

ComboInfo Contour::getPadInfo()
 {
  return ItemInfo(pads);
 }

bool Contour::padUp(ulen index)
 {
  return UpItem(pads,index);
 }

bool Contour::padDown(ulen index)
 {
  return DownItem(pads,index);
 }

bool Contour::padDel(ulen index)
 {
  return delItem(pads,index);
 }

class Contour::PadTestParser : public PadTextParser
 {
   const Contour *obj;

  private:

   virtual bool point(PtrLen<const Char> name,PtrLen<const Char>,PtrLen<const Char>) { return obj->testName(name); }

   virtual bool length(PtrLen<const Char> name,StrLen) { return obj->testName(name); }

   virtual bool angle(PtrLen<const Char> name,StrLen) { return obj->testName(name); }

   virtual bool ratio(PtrLen<const Char> name,StrLen) { return obj->testName(name); }

  public:

   PadTestParser(const Contour *obj_,PtrLen<const Char> text,CharAccent *accent) : PadTextParser(text,accent),obj(obj_) {}
 };

bool Contour::padAddTest(PtrLen<const Char> text,CharAccent *accent) const
 {
  PadTestParser parser(this,text,accent);

  parser.run();

  return parser;
 }

class Contour::PadAddParser : public PadTextParser
 {
   Contour *obj;
   ulen index;

  private:

   virtual bool point(PtrLen<const Char> name,PtrLen<const Char> x,PtrLen<const Char> y)
    {
     return obj->addPad<Point>(index,name,{StrToReal(x),StrToReal(y)});
    }

   virtual bool length(PtrLen<const Char> name,PtrLen<const Char> x)
    {
     return obj->addPad<Length>(index,name,StrToReal(x));
    }

   virtual bool angle(PtrLen<const Char> name,PtrLen<const Char> x)
    {
     return obj->addPad<Angle>(index,name,GradToRadian(StrToReal(x)));
    }

   virtual bool ratio(PtrLen<const Char> name,PtrLen<const Char> x)
    {
     return obj->addPad<Ratio>(index,name,StrToReal(x));
    }

  public:

   PadAddParser(Contour *obj_,ulen index_,PtrLen<const Char> text) : PadTextParser(text),obj(obj_),index(index_) {}
 };

bool Contour::padAdd(ulen index,PtrLen<const Char> text)
 {
  PadAddParser parser(this,index,text);

  parser.run();

  return parser;
 }

 // formula list

ComboInfo Contour::getFormulaInfo()
 {
  return ItemInfo(formulas);
 }

bool Contour::formulaUp(ulen index)
 {
  return UpItem(formulas,index);
 }

bool Contour::formulaDown(ulen index)
 {
  return DownItem(formulas,index);
 }

bool Contour::formulaDel(ulen index)
 {
  return delItem(formulas,index);
 }

struct Contour::CreateOp
 {
  struct NegFunc
   {
    Object &ret;
    Object a;

    bool operator () () { return false; }

    bool operator () (auto) { return false; }

    template <OneOfTypes<Ratio,Length,Angle> S>
    bool operator () (S)
     {
      ret=Formula<S (S)>::template Create<Neg>("Neg"_c,a);

      return true;
     }
   };

  struct AddFunc
   {
    Object &ret;
    Object a;
    Object b;

    bool operator () () { return false; }

    bool operator () (auto) { return false; }

    template <OneOfTypes<Ratio,Length,Angle> S>
    bool operator () (S)
     {
      if( b.getTypeId()!=S::TypeId ) return false;

      ret=Formula<S (S,S)>::template Create<Add>("Add"_c,a,b);

      return true;
     }
   };

  struct SubFunc
   {
    Object &ret;
    Object a;
    Object b;

    bool operator () () { return false; }

    bool operator () (auto) { return false; }

    template <OneOfTypes<Ratio,Length,Angle> S>
    bool operator () (S)
     {
      if( b.getTypeId()!=S::TypeId ) return false;

      ret=Formula<S (S,S)>::template Create<Sub>("Sub"_c,a,b);

      return true;
     }
   };

  struct MulFunc
   {
    Object &ret;
    Object a;
    Object b;

    bool operator () () { return false; }

    bool operator () (auto) { return false; }

    template <OneOfTypes<Ratio,Length,Angle> S>
    bool operator () (S)
     {
      if( a.getTypeId()!=Ratio::TypeId ) return false;

      ret=Formula<S (Ratio,S)>::template Create<Mul>("Mul"_c,a,b);

      return true;
     }
   };

  struct DivFunc
   {
    Object &ret;
    Object a;
    Object b;

    bool operator () () { return false; }

    bool operator () (auto) { return false; }

    template <OneOfTypes<Ratio,Angle> S>
    bool operator () (S)
     {
      if( b.getTypeId()!=Ratio::TypeId ) return false;

      ret=Formula<S (S,Ratio)>::template Create<Div>("Div"_c,a,b);

      return true;
     }

    bool operator () (Length)
     {
      switch( b.getTypeId() )
        {
         case Length::TypeId :
           ret=Formula<Ratio (Length,Length)>::Create<Div>("Div"_c,a,b);
         return true;

         case Ratio::TypeId :
           ret=Formula<Length (Length,Ratio)>::Create<Div>("Div"_c,a,b);
         return true;
        }

      return false;
     }
   };

  using ExprType = Object ;

  static bool neg(ExprType &ret,ExprType a)
   {
    return a.call(NegFunc{ret,a});
   }

  static bool add(ExprType &ret,ExprType a,ExprType b)
   {
    return a.call(AddFunc{ret,a,b});
   }

  static bool sub(ExprType &ret,ExprType a,ExprType b)
   {
    return a.call(SubFunc{ret,a,b});
   }

  static bool mul(ExprType &ret,ExprType a,ExprType b)
   {
    return b.call(MulFunc{ret,a,b});
   }

  static bool div(ExprType &ret,ExprType a,ExprType b)
   {
    return a.call(DivFunc{ret,a,b});
   }
 };

class Contour::FormulaTestContext : public NoCopyBase<CreateOp>
 {
  protected:

   const Contour *obj;

   struct CreateFunc
    {
     StrLen text_name;

     using FuncType = bool (*)(StrLen text_name,ExprType &ret,PtrLen<const ExprType> list) ;

     FuncType func = 0 ;

     CreateFunc() noexcept {}

     CreateFunc(StrLen text_name_,FuncType func_) : text_name(text_name_),func(func_) {}

     bool create(ExprType &ret,PtrLen<const ExprType> list)
      {
       return func(text_name,ret,list);
      }
    };

   class Map : public StrMap<CreateFunc>
    {
      struct AddFunc
       {
        Map *obj;

        template <class FormulaType,typename Formula<FormulaType>::FuncType F>
        void doIt(StrLen name,StrLen text_name)
         {
          obj->add(name,text_name,Formula<FormulaType>::template SafeCreate<F>);
         }
       };

     public:

      Map()
       {
        FunctionList(AddFunc{this});

        complete();
       }
    };

   Map map;

  public:

   explicit FormulaTestContext(const Contour *obj_) : obj(obj_) {}

   bool set(PtrLen<const Char> name,ExprType value)
    {
     if( value.getIndex().type!=IndexNone ) return false;

     return obj->testName(name);
    }

   // functions

   bool func(ExprType &ret,PtrLen<const Char> name,PtrLen<const ExprType> list)
    {
     NameKey key(name);

     if( auto *obj=map[key] ) return obj->create(ret,list);

     return false;
    }

   // args

   bool arg(ExprType &ret,PtrLen<const Char> name)
    {
     NameKey key(name);

     if( const Object *res=obj->map.find(key) )
       {
        ret=*res;

        return true;
       }

     return false;
    }

   bool number(ExprType &ret,PtrLen<const Char> number)
    {
     ret=Pad<Ratio>::Create(StrToReal(number));

     return true;
    }

   bool angle(ExprType &ret,PtrLen<const Char> number)
    {
     ret=Pad<Angle>::Create(StrToReal(number));

     return true;
    }

   bool length(ExprType &ret,PtrLen<const Char> number)
    {
     ret=Pad<Length>::Create(StrToReal(number));

     return true;
    }

   bool point(ExprType &ret,PtrLen<const Char> number_x,PtrLen<const Char> number_y)
    {
     ret=Pad<Point>::Create({StrToReal(number_x),StrToReal(number_y)});

     return true;
    }
 };

bool Contour::formulaAddTest(PtrLen<const Char> text,CharAccent *accent) const
 {
  FormulaTestContext ctx(this);
  FormulaTextParser<FormulaTestContext> parser(ctx,text,accent);

  parser.run();

  return parser;
 }

class Contour::FormulaAddContext : public FormulaTestContext
 {
   ulen index;

  public:

   FormulaAddContext(Contour *obj,ulen index_) : FormulaTestContext(obj),index(index_) {}

   bool set(PtrLen<const Char> name,ExprType value)
    {
     if( value.getIndex().type!=IndexNone ) return false;

     return const_cast<Contour *>(obj)->addFormula(index,name,value);
    }
 };

bool Contour::formulaAdd(ulen index,PtrLen<const Char> text)
 {
  FormulaAddContext ctx(this,index);
  FormulaTextParser<FormulaAddContext> parser(ctx,text);

  parser.run();

  return parser;
 }

 // save/load

void Contour::erase()
 {
  pads.erase();
  formulas.erase();
  map.erase();
 }

struct Contour::PrintPad
 {
  PrintBase &out;
  StrLen name;
  ulen ind;

  void operator () () {}

  void operator () (auto) {}

  void operator () (Ratio s)
   {
    Printf(out,"Ratio #;#; = { #; , #; };\n\n",name,ind,s.val.toBin(),(uint8)s.rex);
   }

  void operator () (Angle s)
   {
    Printf(out,"Angle #;#; = { #; , #; };\n\n",name,ind,s.val.toBin(),(uint8)s.rex);
   }

  void operator () (Length s)
   {
    Printf(out,"Length #;#; = { #; , #; };\n\n",name,ind,s.val.toBin(),(uint8)s.rex);
   }

  void operator () (Point s)
   {
    Printf(out,"Point #;#; = { #; , #; , #; };\n\n",name,ind,s.x.toBin(),s.y.toBin(),(uint8)s.rex);
   }
 };

struct Contour::PrintArg
 {
  PrintBase &out;
  ulen free_ind;

  void printTop(Object o,ulen ind)
   {
    auto t=o.getText();

    print(o,ind,t);
   }

  void print(Object o,ulen ind)
   {
    auto t=o.getText();

    if( t.index.type==IndexNone ) print(o,ind,t);
   }

  void print(Object o,ulen ind,Text t)
   {
    switch( t.type )
      {
       case TextFormulaFixed :
       case TextFormulaVariable :
        {
         Printf(out,"#; F#; = { ",t.name,ind);

         if( t.type==TextFormulaVariable ) Putch(out,'{',' ');

         ulen base_ind=free_ind;

         free_ind+=t.args.len;

         PrintFirst stem(""_c," , "_c);

         for(ulen i=0; i<t.args.len ;i++)
           {
            auto ta=t.args[i].getText();

            switch( ta.index.type )
              {
               case IndexNone :
                {
                 Printf(out,"#;&F#;",stem,base_ind+i);
                }
               break;

               case IndexPad :
                {
                 Printf(out,"#;Data.pads+#;",stem,ta.index.index);
                }
               break;

               case IndexFormula :
                {
                 Printf(out,"#;Data.formulas+#;",stem,ta.index.index);
                }
               break;
              }
           }

         if( t.type==TextFormulaVariable ) Putch(out,' ','}');

         Printf(out," };\n\n");

         for(ulen i=0; i<t.args.len ;i++) print(t.args[i],base_ind+i);
        }
       break;

       case TextPad :
        {
         o.call(PrintPad{out,"F"_c,ind});
        }
       break;
      }
   }
 };

struct Contour::PrintContour
 {
  PrintBase &out;
  String name;

  void print(StrLen type,StrLen name,PtrLen<const Dot> dots)
   {
    // 1

    {
     Printf(out,"#; Contour_#;=\n {\n",type,name);

     Printf(out,"  {");

     PrintFirst stem("\n   ",",\n   ");

     for(Dot dot : dots )
       {
        Printf(out,"#;{ { #; , #; , #; } , #; }",stem,dot.point.x.toBin(),dot.point.y.toBin(),(uint8)dot.point.rex,DDLBool(dot.break_flag));
       }

     Printf(out,"\n  },\n");
     Printf(out,"  0\n");

     Printf(out," };\n\n");
    }

    // 2

    {
     Printf(out,"/*\n\n");

     Printf(out,"SmoothDot Contour_#;[]=\n {",name);

     PrintFirst stem("\n  ",",\n  ");

     for(Dot dot : dots )
       {
        MPoint p=Map(dot.point);

        Printf(out,"#;{ { #; , #; } , #; }",stem,p.x,p.y, dot.break_flag?"Smooth::DotBreak"_c:"Smooth::DotSimple"_c );
       }

     Printf(out,"\n };\n\n");

     Printf(out,"*/\n\n");
    }
   }

  void operator () () {}

  void operator () (auto) {}

  void operator () (Path s)
   {
    if( s.rex ) return;

    print("Path"_c,Range(name),Range(s.dots));
   }

  void operator () (Loop s)
   {
    if( s.rex ) return;

    print("Loop"_c,Range(name),Range(s.dots));
   }
 };

void Contour::save(StrLen file_name,ErrorText &etext) const
 {
  PrintBuf eout(etext.getBuf());

  ReportExceptionTo<PrintBuf> report(eout);

  try
    {
     PrintFile out(file_name);

     Printf(out,"//##include <Contour.ddl>\n\n");

     Printf(out,"Contour Data=\n {\n");

     // pads

     Printf(out,"  {");

     {
      auto r=Range(pads);

      PrintFirst stem("\n   "_c,",\n   "_c);

      for(ulen i=0; i<r.len ;i++)
        {
         Printf(out,"#;{ #; , #; , &Pad#; }",stem,r[i].label,i,i);
        }
     }

     Printf(out,"\n  },\n");

     // formulas

     Printf(out,"  {");

     {
      auto r=Range(formulas);

      PrintFirst stem("\n  "_c,",\n  "_c);

      for(ulen i=0; i<r.len ;i++)
        {
         Printf(out,"#;{ #; , #; , &F#; }",stem,r[i].label,i,i);
        }
     }

     Printf(out,"\n  }\n");

     Printf(out," };\n\n");

     // pads

     {
      auto r=Range(pads);

      for(ulen i=0; i<r.len ;i++)
        {
         r[i].obj.call(PrintPad{out,"Pad"_c,i});
        }
     }

     // formulas

     {
      auto r=Range(formulas);

      PrintArg parg{out,r.len};

      for(ulen i=0; i<r.len ;i++)
        {
         parg.printTop(r[i].obj,i);
        }
     }

     // contours

     {
      auto r=Range(formulas);

      for(ulen i=0; i<r.len ;i++)
        {
         const Item &item=r[i];

         item.obj.call(PrintContour{out,item.label.name});
        }
     }
    }
  catch(CatchType)
    {
     Printf(eout,"\n@ #.q;",file_name);

     etext.setTextLen(eout.close().len);
    }
 }

#include "Contour.TypeDef.gen.h"
#include "Contour.TypeSet.gen.h"

StrLen Contour::Pretext()
 {
  return
"type Bool = uint8 ;"

"Bool True = 1 ;"

"Bool False = 0 ;"

"struct Label"
" {"
"  text name;"

"  Bool show;"
"  Bool gray;"
"  Bool show_name;"
" };"

"type Exception = uint8 ;"

"struct Real"
" {"
"  sint64 mantissa;"
"  sint16 exp;"
" };"

"struct Ratio"
" {"
"  Real val;"
"  Exception rex;"
" };"

"struct Length"
" {"
"  Real val;"
"  Exception rex;"
" };"

"struct Angle"
" {"
"  Real val;"
"  Exception rex;"
" };"

"struct Point"
" {"
"  Real x;"
"  Real y;"
"  Exception rex;"
" };"

"struct Line"
" {"
"  Point a;"
"  Point ort;"
"  Exception rex;"
" };"

"struct Circle "
" {"
"  Point center;"
"  Length radius;"
"  Exception rex;"
" };"

"struct Couple"
" {"
"  Point a;"
"  Point b;"
"  Exception rex;"
" };"

"struct Dot "
" {"
"  Point point;"
"  Bool break_flag;"
" };"

"struct Step "
" {"
"  Point[] points;"
"  Exception rex;"
" };"

"struct Path"
" {"
"  Dot[] dots;"
"  Exception rex;"
" };"

"struct Loop"
" {"
"  Dot[] dots;"
"  Exception rex;"
" };"

"struct Solid"
" {"
"  Dot[] dots;"
"  Exception rex;"
" };"

"struct Pad"
" {"
"  Label label;"
"  ulen index;"

"  {Ratio,Length,Angle,Point} *object;"
" };"

"struct Neg"
" {"
"  Arg a;"
" };"

"struct Add"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct Sub"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct Mul"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct Div"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct LengthOf"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct AngleOf"
" {"
"  Arg a;"
"  Arg b;"
"  Arg c;"
" };"

"struct LineOf"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct Middle"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct Part"
" {"
"  Arg a;"
"  Arg b;"
"  Arg c;"
" };"

"struct MidOrt"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct CircleOf"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct CircleOuter"
" {"
"  Arg a;"
"  Arg b;"
"  Arg c;"
" };"

"struct Proj"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct AngleC"
" {"
"  Arg a;"
"  Arg b;"
"  Arg c;"
" };"

"struct Meet"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct MeetCircle"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct MeetCircles"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct Rotate"
" {"
"  Arg a;"
"  Arg b;"
"  Arg c;"
" };"

"struct RotateOrt"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct Move"
" {"
"  Arg a;"
"  Arg b;"
"  Arg c;"
" };"

"struct MoveLen"
" {"
"  Arg a;"
"  Arg b;"
"  Arg c;"
" };"

"struct Mirror"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct First"
" {"
"  Arg a;"
" };"

"struct Second"
" {"
"  Arg a;"
" };"

"struct Up"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct Down"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct Left"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct Right"
" {"
"  Arg a;"
"  Arg b;"
" };"

"struct StepOf"
" {"
"  Arg[] args;"
" };"

"struct PathOf"
" {"
"  Arg[] args;"
" };"

"struct BPathOf"
" {"
"  Arg[] args;"
" };"

"struct LoopOf"
" {"
"  Arg[] args;"
" };"

"struct BLoopOf"
" {"
"  Arg[] args;"
" };"

"struct SolidOf"
" {"
"  Arg a;"
" }; "

"type Arg = {"
"            Ratio,Length,Angle,Point,Pad,Formula,"
"            Neg,Add,Sub,Mul,Div,"
"            LengthOf,AngleOf,LineOf,Middle,Part,MidOrt,CircleOf,CircleOuter,"
"            Proj,AngleC,Meet,MeetCircle,MeetCircles,Rotate,RotateOrt,Move,MoveLen,"
"            Mirror,First,Second,Up,Down,Left,Right,"
"            StepOf,PathOf,BPathOf,LoopOf,BLoopOf,SolidOf"
"           } * ;"

"struct Formula"
" {"
"  Label label;"
"  ulen index;"

"  Arg object;"
" };"

"struct Contour"
" {"
"  Pad[] pads;"
"  Formula[] formulas;"
" };"_c;
 }

Geometry::Real Contour::ToReal(AnyType x)
 {
  return Real::Bin{x.mantissa,x.exp};
 }

void Contour::CopyFlags(Label &label,AnyType x)
 {
  label.show=x.show;
  label.gray=x.gray;
  label.show_name=x.show_name;
 }

struct Contour::CreateDataPadObject : NoCopy
 {
  Object obj;

  void create(AnyType ptr)
   {
    if( !ptr )
      {
       Printf(Exception,"App::Contour::load(...) : null pad object");
      }

    ElaborateAnyPtr(*this,ptr);
   }

  void operator () (TypeDef::Ratio *ptr)
   {
    Ratio s;

    s.val=ToReal(ptr->val);
    s.rex=RealException(ptr->rex);

    obj=Pad<Ratio>::Create(s);
   }

  void operator () (TypeDef::Angle *ptr)
   {
    Angle s;

    s.val=ToReal(ptr->val);
    s.rex=RealException(ptr->rex);

    obj=Pad<Angle>::Create(s);
   }

  void operator () (TypeDef::Length *ptr)
   {
    Length s;

    s.val=ToReal(ptr->val);
    s.rex=RealException(ptr->rex);

    obj=Pad<Length>::Create(s);
   }

  void operator () (TypeDef::Point *ptr)
   {
    Point s;

    s.x=ToReal(ptr->x);
    s.y=ToReal(ptr->y);
    s.rex=RealException(ptr->rex);

    obj=Pad<Point>::Create(s);
   }
 };

struct Contour::CreateDataFormulaObject : CreateDataPadObject
 {
  Contour *cont;
  PtrLen<TypeDef::Formula> data_formulas;
  bool *lock;

  CreateDataFormulaObject(Contour *cont_,PtrLen<TypeDef::Formula> data_formulas_,bool *lock_)
   : cont(cont_),
     data_formulas(data_formulas_),
     lock(lock_)
   {
   }

  void set(ulen i)
   {
    Object o=cont->formulas[i].obj;

    if( o.getTypeId()!=0 )
      {
       obj=o;

       return;
      }

    if( !Change(lock[i],true) )
      {
       Printf(Exception,"App::Contour::load(...) : formula self-dependence");
      }

    TypeDef::Formula formula=data_formulas[i];

    create(formula.object.getPtr());

    if( !cont->setFormula(i,formula.label.name,obj) )
      {
       Printf(Exception,"App::Contour::load(...) : cannot create formula");
      }

    CopyFlags(cont->formulas[i].label,formula.label);
   }

  Object createArg(AnyType ptr)
   {
    CreateDataFormulaObject func(cont,data_formulas,lock);

    func.create(ptr);

    return func.obj;
   }

  static void Guard(bool ok)
   {
    if( !ok )
      {
       Printf(Exception,"App::Contour::load(...) : argument type mismatch");
      }
   }

  void create(AnyType ptr)
   {
    if( !ptr )
      {
       Printf(Exception,"App::Contour::load(...) : null formula object");
      }

    ElaborateAnyPtr(*this,ptr);
   }

  using CreateDataPadObject::operator ();

  void operator () (TypeDef::Pad *ptr)
   {
    obj=cont->pads.at(ptr->index).obj;
   }

  void operator () (TypeDef::Formula *ptr)
   {
    ulen index=ptr->index;

    GuardIndex(index,data_formulas.len);

    set(index);
   }

  void operator () (TypeDef::Neg *ptr)
   {
    Guard( CreateOp::neg(obj,createArg(ptr->a.getPtr())) );
   }

  void operator () (TypeDef::Add *ptr)
   {
    Guard( CreateOp::add(obj,createArg(ptr->a.getPtr()),createArg(ptr->b.getPtr())) );
   }

  void operator () (TypeDef::Sub *ptr)
   {
    Guard( CreateOp::sub(obj,createArg(ptr->a.getPtr()),createArg(ptr->b.getPtr())) );
   }

  void operator () (TypeDef::Mul *ptr)
   {
    Guard( CreateOp::mul(obj,createArg(ptr->a.getPtr()),createArg(ptr->b.getPtr())) );
   }

  void operator () (TypeDef::Div *ptr)
   {
    Guard( CreateOp::div(obj,createArg(ptr->a.getPtr()),createArg(ptr->b.getPtr())) );
   }

  template <FuncArgCountType<1> Func,Func *F,class T>
  void createFunc(T *ptr,StrLen name)
   {
    Object list[1]={createArg(ptr->a.getPtr())};

    Guard( Formula<Func>::template SafeCreate<F>(name,obj,Range(list)) );
   }

  template <FuncArgCountType<2> Func,Func *F,class T>
  void createFunc(T *ptr,StrLen name)
   {
    Object list[2]={createArg(ptr->a.getPtr()),createArg(ptr->b.getPtr())};

    Guard( Formula<Func>::template SafeCreate<F>(name,obj,Range(list)) );
   }

  template <FuncArgCountType<3> Func,Func *F,class T>
  void createFunc(T *ptr,StrLen name)
   {
    Object list[3]={createArg(ptr->a.getPtr()),createArg(ptr->b.getPtr()),createArg(ptr->c.getPtr())};

    Guard( Formula<Func>::template SafeCreate<F>(name,obj,Range(list)) );
   }

#define DEF(F) void operator () (TypeDef::F *ptr) { createFunc<decltype(F),F>(ptr, #F ## _c ); }                                                                    \

  DEF(LengthOf)
  DEF(AngleOf)
  DEF(LineOf)
  DEF(Middle)
  DEF(Part)
  DEF(MidOrt)
  DEF(CircleOf)
  DEF(CircleOuter)
  DEF(Proj)
  DEF(AngleC)
  DEF(Meet)
  DEF(MeetCircle)
  DEF(MeetCircles)
  DEF(Rotate)
  DEF(RotateOrt)
  DEF(Move)
  DEF(MoveLen)
  DEF(Mirror)
  DEF(First)
  DEF(Second)
  DEF(Up)
  DEF(Down)
  DEF(Left)
  DEF(Right)
  DEF(SolidOf)

#undef DEF

  void fill(DynArray<Object> &list,PtrLen<TypeDef::Arg> r)
   {
    list.extend_default(r.len);

    for(ulen i=0; i<r.len ;i++) list[i]=createArg(r[i].getPtr());
   }

  void operator () (TypeDef::StepOf *ptr)
   {
    DynArray<Object> list;

    fill(list,ptr->args.getRange());

    Guard( Formula<Step (Point[])>::SafeCreate<StepOf>("StepOf",obj,Range(list)) );
   }

  void operator () (TypeDef::PathOf *ptr)
   {
    DynArray<Object> list;

    fill(list,ptr->args.getRange());

    Guard( Formula<Path (Point[])>::SafeCreate<PathOf>("PathOf",obj,Range(list)) );
   }

  void operator () (TypeDef::BPathOf *ptr)
   {
    DynArray<Object> list;

    fill(list,ptr->args.getRange());

    Guard( Formula<Path (Step[])>::SafeCreate<PathOf>("BPathOf",obj,Range(list)) );
   }

  void operator () (TypeDef::LoopOf *ptr)
   {
    DynArray<Object> list;

    fill(list,ptr->args.getRange());

    Guard( Formula<Loop (Point[])>::SafeCreate<LoopOf>("LoopOf",obj,Range(list)) );
   }

  void operator () (TypeDef::BLoopOf *ptr)
   {
    DynArray<Object> list;

    fill(list,ptr->args.getRange());

    Guard( Formula<Loop (Step[])>::SafeCreate<LoopOf>("BLoopOf",obj,Range(list)) );
   }
 };

void Contour::load(StrLen file_name,ErrorText &etext)
 {
  erase();

  PrintBuf eout(etext.getBuf());

  ReportExceptionTo<PrintBuf> report(eout);

  try
    {
     DDL::FileEngine<FileName,FileToMem> engine(eout);

     auto result=engine.process(file_name,Pretext());

     if( !result )
       {
        Printf(eout,"\n@ #.q;",file_name);

        etext.setTextLen(eout.close().len);

        return;
       }
     else
       {
        DDL::TypedMap<TypeSet> map(result);
        MemAllocGuard guard(map.getLen());

        map(guard);

        // populate

        TypeDef::Contour data=map.takeConst<TypeDef::Contour>("Data");

        PtrLen<TypeDef::Pad> data_pads=data.pads.getRange();

        pads.reserve(data_pads.len);

        for(ulen i=0; i<data_pads.len ;i++)
          {
           TypeDef::Pad pad=data_pads[i];

           CreateDataPadObject func;

           func.create(pad.object.getPtr());

           if( !addPad(i,pad.label.name,func.obj) )
             {
              Printf(Exception,"App::Contour::load(...) : cannot create pad");
             }

           CopyFlags(pads[i].label,pad.label);
          }

        PtrLen<TypeDef::Formula> data_formulas=data.formulas.getRange();

        formulas.extend_default(data_formulas.len);

        DynArray<bool> lock(data_formulas.len);

        CreateDataFormulaObject func(this,data_formulas,lock.getPtr());

        for(ulen i=0; i<data_formulas.len ;i++) func.set(i);
       }
    }
  catch(CatchType)
    {
     erase();

     Printf(eout,"\n@ #.q;",file_name);

     etext.setTextLen(eout.close().len);
    }
 }

} // namespace App

