/* Contour.h */
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

#ifndef Contour_h
#define Contour_h

#include <inc/Geometry.h>

#include <CCore/inc/MemBase.h>
#include <CCore/inc/RefPtr.h>
#include <CCore/inc/String.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/CompactMap.h>
#include <CCore/inc/StrKey.h>
#include <CCore/inc/StrToChar.h>

#include <CCore/inc/video/PrintDDL.h>

namespace App {

/* classes */

template <class Func> struct ArgCount;

/* struct ArgCount<Func> */

template <class S,class ... SS>
struct ArgCount<S (SS...)>
 {
  enum RetType { Ret = sizeof ... (SS) };
 };

/* concept FuncArgCountType<Func,int Count> */

template <class Func,int Count>
concept bool FuncArgCountType = ( ArgCount<Func>::Ret == Count ) ;

//----------------------------------------------------------------------------------------

/* functions */

void GuardTypeMismatch();

inline void GuardType(int t1,int t2) { if( t1!=t2 ) GuardTypeMismatch(); }

/* classes */

template <class S> struct UnusedPad;

struct Formular;

struct Label;

class ErrorText;

class Contour;

/* struct UnusedPad<S> */

template <class S>
struct UnusedPad
 {
  static S pad;
 };

template <class S>
S UnusedPad<S>::pad{};

/* struct Formular */

struct Formular : Geometry
 {
  // Object

  static const int PadFlag = 1<<10 ;

  class Object;

  enum TextType
   {
    TextFormulaFixed,
    TextFormulaVariable,
    TextPad
   };

  enum IndexType
   {
    IndexNone = 0,

    IndexPad,
    IndexFormula
   };

  struct Index
   {
    IndexType type = IndexNone ;
    ulen index = MaxULen ;
   };

  struct Text
   {
    TextType type;
    Index index;
    StrLen name;
    PtrLen<const Object> args;
   };

  class Object
   {
    private:

     class Base : MemBase_nocopy
      {
        ulen ref_count = 1 ;

       public:

        Index index;

        Base() {}

        virtual ~Base() {}

        void incRef() { ref_count++; }

        bool decRef() { return !--ref_count; }

        void destroy() noexcept { delete this; }

        virtual Text getText() const { return {}; }

        // default object

        static Base * GetDefault()
         {
          Base *ret=&Default;

          ret->incRef();

          return ret;
         }

        static Base Default;
      };

     template <class S>
     struct NodeInterface : Base
      {
       virtual S get() const =0;

       virtual S & ref() =0;
      };

     template <class T,class S=typename T::RetType>
     struct Node : NodeInterface<S>
      {
       T obj;

       template <class ... SS>
       explicit Node(SS && ... ss) : obj( std::forward<SS>(ss)... ) {}

       virtual S get() const { return obj(); }

       virtual S & ref() { return obj.pad; }

       virtual Text getText() const { return obj.getText(this->index); }
      };

     RefPtr<Base> ptr;
     int type_id;

    private:

     template <class Func>
     struct CallFunc
      {
       Func &func;
       const Object &arg;

       CallFunc(Func &func_,const Object &arg_) : func(func_),arg(arg_) {}

       template <class S>
       auto doIt() { return func(arg.get<S>()); }

       auto doOther() { return func(); }
      };

     template <class Func>
     struct CallRefFunc
      {
       Func &func;
       const Object &arg;

       CallRefFunc(Func &func_,const Object &arg_) : func(func_),arg(arg_) {}

       template <class S>
       auto doIt() { return func(arg.ref<S>()); }

       auto doOther() { return func(); }
      };

    public:

     template <class T> struct Tag {};

     Object() noexcept : ptr(Base::GetDefault()),type_id(0) {}

     template <class T,class ... SS>
     Object(Tag<T>,SS && ... ss) : ptr(new Node<T>( std::forward<SS>(ss)... )),type_id(T::TypeId) {}

     ~Object() {}

     int getTypeId() const { return type_id&(PadFlag-1); }

     int isPad() const { return type_id&PadFlag; }

     StrLen getTypeName() const { return TypeName(getTypeId()); }

     template <class S>
     S get() const
      {
       GuardType(getTypeId(),S::TypeId);

       return static_cast<NodeInterface<S> *>(ptr.getPtr())->get();
      }

     template <class Func>
     auto call(Func func) const // func(S s)
      {
       return TypeSwitch(getTypeId(),CallFunc<Func>(func,*this));
      }

     template <class S>
     S & ref() const
      {
       GuardType(type_id,S::TypeId|PadFlag);

       return static_cast<NodeInterface<S> *>(ptr.getPtr())->ref();
      }

     template <class Func>
     auto callRef(Func func) const // func(S &s)
      {
       return TypeSwitch(getTypeId(),CallRefFunc<Func>(func,*this));
      }

     Text getText() const { return ptr->getText(); }

     Index getIndex() const { return ptr->index; }

     void setIndex(Index index) const { ptr->index=index; }

     void updateIndex(ulen index) const { ptr->index.index=index; }
   };

  template <class T,class ... SS>
  static Object CreateObject(SS && ... ss) { return Object(Object::Tag<T>(), std::forward<SS>(ss)... ); }

  // Function binder

  template <class S>
  using ToObject = Object ;

  template <class S,class IList,class ... SS> struct FormulaFactory;

  template <class S,class ... SS,int ... IList>
  struct FormulaFactory<S, Meta::IndexListBox<IList...> ,SS...>
   {
    template <S Func(SS...)>
    struct Pack : UnusedPad<S>
     {
      static const int TypeId = S::TypeId ;

      using RetType = S ;

      StrLen text_name;
      Object args[sizeof ... (SS)];

      explicit Pack(StrLen text_name_,const ToObject<SS> & ... ss) : text_name(text_name_),args{ss...} {}

      static S SafeCall(SS ... ss)
       {
        try
          {
           AssertValid(ss...);

           return Func(ss...);
          }
        catch(RealException rex)
          {
           return S(rex);
          }
       }

      S operator () () const { return SafeCall( args[IList].template get<SS>()... ); }

      Text getText(Index index) const { return {TextFormulaFixed,index,text_name,Range(args)}; }
     };

    template <S Func(SS...)>
    static Object Create(StrLen text_name,const ToObject<SS> & ... ss) { return CreateObject<Pack<Func> >(text_name,ss...); }

    static bool TestType(const Object *list,const int *type,int ind) { return list[ind].getTypeId()!=type[ind]; }

    using FuncType = S (*)(SS...) ;

    template <S Func(SS...)>
    static bool SafeCreate(StrLen text_name,Object &ret,PtrLen<const Object> list)
     {
      if( list.len!=sizeof ... (SS) ) return false;

      int temp[]={ SS::TypeId ... };

      if( ( TestType(list.ptr,temp,IList) || ... ) ) return false;

      ret=Create<Func>(text_name, list[IList]... );

      return true;
     }
   };

  template <class S,class ... SS>
  using FormulaAlias = FormulaFactory<S, Meta::IndexList<0,SS...> ,SS...> ;

  template <class T> struct Formula;

  template <class S,class ... SS>
  struct Formula<S (SS...)> : FormulaAlias<S,SS...> {};

  template <class A>
  class ArgCursor
   {
     PtrLen<const Object> list;

    public:

     ArgCursor(PtrLen<const Object> list_) : list(list_) {}

     ulen getLen() const { return list.len; }

     // object cursor

     bool operator + () const { return +list; }

     bool operator ! () const { return !list; }

     A operator * () const
      {
       A ret=list->get<A>();

       AssertValid(ret);

       return ret;
      }

     void operator ++ () { ++list; }
   };

  template <class S,class A>
  struct Formula<S (A[])>
   {
    template <S Func(ArgCursor<A>)>
    struct Pack : UnusedPad<S>
     {
      static const int TypeId = S::TypeId ;

      using RetType = S ;

      StrLen text_name;
      DynArray<Object> args;

      Pack(StrLen text_name_,PtrLen<const Object> list) : text_name(text_name_),args(DoCopy(list.len),list.ptr) {}

      static S SafeCall(ArgCursor<A> args)
       {
        try
          {
           return Func(args);
          }
        catch(RealException rex)
          {
           return S(rex);
          }
       }

      S operator () () const { return SafeCall(Range(args)); }

      Text getText(Index index) const { return {TextFormulaVariable,index,text_name,Range(args)}; }
     };

    using FuncType = S (*)(ArgCursor<A>) ;

    template <S Func(ArgCursor<A>)>
    static bool SafeCreate(StrLen text_name,Object &ret,PtrLen<const Object> list)
     {
      for(const Object &obj : list ) if( obj.getTypeId()!=A::TypeId ) return false;

      ret=CreateObject<Pack<Func> >(text_name,list);

      return true;
     }
   };

  // Pad

  template <class S>
  struct Pad
   {
    static const int TypeId = S::TypeId|PadFlag ;

    using RetType = S ;

    S pad;

    explicit Pad(const S &obj) : pad(obj) {}

    S operator () () const { return pad; }

    Text getText(Index index) const { return {TextPad,index}; }

    static Object Create(const S &obj) { return CreateObject<Pad>(obj); }
   };
 };

/* struct Label */

struct Label
 {
  // property

  String name;

  bool show = true ;
  bool gray = true ;
  bool show_name = true ;

  // work

  mutable MPoint pos;
  mutable bool pos_ok = false ;

  Label() noexcept {}

  explicit Label(const String &name_) noexcept : name(name_) {}

  bool test() const
   {
    pos_ok=false;

    return show;
   }

  void setPos(MPoint pos_) const
   {
    pos=pos_;
    pos_ok=true;
   }

  // print object

  void print(PrinterType &out) const
   {
    Printf(out,"{ '#;' , #; , #; , #; }",name,DDLBool(show),DDLBool(gray),DDLBool(show_name));
   }
 };

/* class ErrorText */

class ErrorText : NoCopy
 {
   SimpleArray<char> buf;
   ulen len = 0 ;

  public:

   ErrorText() : buf(64_KByte) {}

   // methods

   bool operator + () const { return len==0; }

   bool operator ! () const { return len!=0; }

   StrLen getText() const { return Range(buf.getPtr(),len); }

   PtrLen<char> getBuf() { return Range(buf); }

   void setTextLen(ulen len_)
    {
     len=Min(buf.getLen(),len_);
    }
 };

/* class Contour */

class Contour : public NoCopyBase<Formular>
 {
   struct Item
    {
     Label label;
     Object obj;
    };

   struct Key : CmpComparable<Key>
    {
     StrKey::HashType hash;
     String name;

     explicit Key(StrKey k) : hash(k.hash),name(k.str) {}

     CmpResult objCmp(const Key &obj) const
      {
       if( CmpResult ret=LessCmp(hash,obj.hash) ) return ret;

       return StrCmp(Range(name),Range(obj.name));
      }
    };

   friend CmpResult Cmp(StrKey a,const Key &b)
    {
     if( CmpResult ret=LessCmp(a.hash,b.hash) ) return ret;

     return StrCmp(a.str,Range(b.name));
    }

#ifdef CCORE_UTF8

   class NameKey : NoCopy
    {
      CharToStr str;
      StrKey key;

     public:

      explicit NameKey(PtrLen<const Char> name)
       : str(name),
         key(str)
       {
       }

      ~NameKey() {}

      operator StrKey() const { return key; }

      operator StrLen() const { return key.str; }
    };

#else

   using NameKey = StrKey ;

#endif

   DynArray<Item> pads;
   DynArray<Item> formulas;

   CompactRBTreeMap<Key,Object,StrKey> map;

  private:

   class ItemInfo : public ComboInfo
    {
      class Base;

     public:

      explicit ItemInfo(const DynArray<Item> &data);

      ~ItemInfo();
    };

   static bool UpItem(DynArray<Item> &a,ulen index);

   static bool DownItem(DynArray<Item> &a,ulen index);

   static void UpdateIndexes(DynArray<Item> &a,ulen index);

  private:

   template <class S>
   bool addPad(ulen index,PtrLen<const Char> name,S s)
    {
     Object obj=Pad<S>::Create(s);

     return addPad(index,name,obj);
    }

   bool addPad(ulen index,PtrLen<const Char> name,Object obj);

#ifdef CCORE_UTF8

   bool addPad(ulen index,StrLen name,Object obj);

#endif

   bool addFormula(ulen index,PtrLen<const Char> name,Object obj);

   bool setFormula(ulen index,PtrLen<const Char> name,Object obj);

#ifdef CCORE_UTF8

   bool setFormula(ulen index,StrLen name,Object obj);

#endif

   bool testName(PtrLen<const Char> name) const;

   bool delItem(DynArray<Item> &a,ulen index);

   class PadTestParser;

   class PadAddParser;

   struct CreateOp;

   class FormulaTestContext;

   class FormulaAddContext;

   template <class Func>
   struct Bind
    {
     Func func;
     const Label &label;
     bool selected;

     void operator () (AnyType s) { if( !s.rex ) func(label,selected,s); }

     void operator () () {}
    };

   template <class Func>
   struct BindRef
    {
     Func func;
     const Label &label;
     const Object &obj;

     void operator () (AnyType &s) { func(label,obj,s); }

     void operator () () {}
    };

   struct PrintPad;

   struct PrintArg;

   struct PrintContour;

   static StrLen Pretext();

   static Real ToReal(AnyType);

   static void CopyFlags(Label &label,AnyType);

   struct CreateDataPadObject;

   struct CreateDataFormulaObject;

  public:

   Contour();

   ~Contour();

   // pad list

   ComboInfo getPadInfo();

   bool padUp(ulen index);

   bool padDown(ulen index);

   bool padDel(ulen index);

   bool padAddTest(PtrLen<const Char> text,CharAccent *accent) const;

   bool padAdd(ulen index,PtrLen<const Char> text);

   // formula list

   ComboInfo getFormulaInfo();

   bool formulaUp(ulen index);

   bool formulaDown(ulen index);

   bool formulaDel(ulen index);

   bool formulaAddTest(PtrLen<const Char> text,CharAccent *accent) const;

   bool formulaAdd(ulen index,PtrLen<const Char> text);

   // elements

   Label & refPadLabel(ulen index) { return pads.at(index).label; }

   Label & refFormulaLabel(ulen index) { return formulas.at(index).label; }

   template <class Func>
   void pad(ulen index,Func func) // func(const Label &label,const Object &obj,S &s)
    {
     Item &item=pads.at(index);

     item.obj.callRef( BindRef<Func>{func,item.label,item.obj} );
    }

   template <class Func>
   void apply(ulen pad_ind,ulen formula_ind,Func func) const // func(const Label &label,bool selected,S s)
    {
     for(ulen i=0,len=pads.getLen(); i<len ;i++)
       {
        const Item &item=pads[i];

        item.obj.call( Bind<Func>{func,item.label,i==pad_ind} );
       }

     for(ulen i=0,len=formulas.getLen(); i<len ;i++)
       {
        const Item &item=formulas[i];

        item.obj.call( Bind<Func>{func,item.label,i==formula_ind} );
       }
    }

#if 0

   template <class Func>
   void applyRef(Func func) // func(const Label &label,const Object &obj,S &s)
    {
     auto temp = [=] (Item &item) { item.obj.callRef( BindRef<Func>{func,item.label,item.obj} ); } ;

     pads.apply(temp);
    }

#endif

   // save/load

   void erase();

   void save(StrLen file_name,ErrorText &etext) const;

   void load(StrLen file_name,ErrorText &etext);
 };

} // namespace App

#endif
