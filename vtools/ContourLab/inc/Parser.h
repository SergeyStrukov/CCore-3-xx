/* Parser.h */
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

#ifndef Parser_h
#define Parser_h

#include <inc/Application.h>

#include <CCore/inc/TextTools.h>
#include <CCore/inc/Array.h>

namespace App {

/* classes */

//enum CharClass;

class CharProp;

struct Token;

class Tokenizer;

class ParserBase;

class PadTextParser;

//enum AtomClass;

struct Atom;

struct FormulaParserData;

template <class Context> class FormulaTextParser;

/* enum CharClass */

enum CharClass
 {
  Char_Digit,
  Char_Letter,
  Char_Dot,
  Char_Punct,
  Char_Space,

  Char_Other
 };

inline bool IsLetterDigit(CharClass cc) { return cc<=Char_Letter; }

inline bool IsLetterDigitDot(CharClass cc) { return cc<=Char_Dot; }

/* class CharProp */

class CharProp : public CharPropTable<CharClass,Char_Other>
 {
  public:

   CharProp();

   static const CharProp Object;
 };

/* char functions */

#ifdef CCORE_UTF8

inline CharClass GetCharClass(Char ch) { return (ch<128)?CharProp::Object[(char)ch]:Char_Letter; }

#else

inline CharClass GetCharClass(Char ch) { return CharProp::Object[ch]; }

#endif

inline bool CharIsLetterDigit(Char ch) { return IsLetterDigit(GetCharClass(ch)); }

inline bool CharIsLetterDigitDot(Char ch) { return IsLetterDigitDot(GetCharClass(ch)); }

#ifdef CCORE_UTF8

inline bool CharIsSpace(Char ch) { return ch<128 && CharIsSpace((char)ch) ; }

#endif

//---------------------------------
//
// From CharProp.h and TextTools.h
//
//---------------------------------
//
// bool CharIsSpace(char ch);
//
//---------------------------------

/* enum TokenClass */

enum TokenClass
 {
  Token_Number,
  Token_Length,
  Token_Angle,

  Token_Word,
  Token_Punct,
  Token_Space,

  Token_Other
 };

/* struct Token */

struct Token
 {
  TokenClass tc;
  ulen pos;
  PtrLen<const Char> str;

  Token() : tc(Token_Other),pos(0) {}

  Token(TokenClass tc_,ulen pos_,PtrLen<const Char> str_) : tc(tc_),pos(pos_),str(str_) {}

  PtrLen<const Char> getNumber() const;

  bool isName() const
   {
    return tc==Token_Word && !is("angle"_c,"len"_c,"point"_c,"ratio"_c) ;
   }

  bool is(StrLen name) const { return str.equal(name); }

  bool is(TokenClass tc_) const { return tc==tc_; }

  bool is(char ch) const { return tc==Token_Punct && ch==str[0] ; }

  template <class ... TT>
  bool is(TT ... tt) const { return ( ... || is(tt) ); }
 };

/* class Tokenizer */

class Tokenizer : NoCopy
 {
   ulen pos = 0 ;
   PtrLen<const Char> text;

  private:

   static ulen ScanLetterDigit(PtrLen<const Char> text); // >=1

   static ulen ScanLetterDigitDot(PtrLen<const Char> text); // >=1

   static ulen ScanSpace(PtrLen<const Char> text); // >=1

   static TokenClass IsNumber(PtrLen<const Char> text); // >=1

  private:

   Token cut(TokenClass tc,ulen len);

   Token next_number();

   Token next_word();

   Token next_punct();

   Token next_space();

   Token next_other();

  public:

   explicit Tokenizer(PtrLen<const Char> text_) : text(text_) {}

   ulen operator + () const { return text.len; }

   bool operator ! () const { return !text.len; }

   Token next();
 };

/* class ParserBase */

class ParserBase : NoCopy
 {
   Tokenizer tok;
   CharAccent *accent;

  private:

   static CharAccent Map(TokenClass tc);

  protected:

   void paint(Token token,CharAccent acc);

   void paint(Token token);

   virtual void next(Token token);

   virtual void stop();

  public:

   ParserBase(PtrLen<const Char> text,CharAccent *accent_) : tok(text),accent(accent_) {}

   void run();
 };

/* class PadTextParser */

class PadTextParser : public ParserBase
 {
   int state = 0 ;

   Token name;
   Token value;
   Token value2;

  private:

   void paintError(Token token)
    {
     state=-1;

     paint(token,CharError);
    }

   virtual void next(Token token);

   virtual void stop();

  protected:

   virtual bool point(PtrLen<const Char> name,PtrLen<const Char> x,PtrLen<const Char> y);

   virtual bool length(PtrLen<const Char> name,PtrLen<const Char> x);

   virtual bool angle(PtrLen<const Char> name,PtrLen<const Char> x);

   virtual bool ratio(PtrLen<const Char> name,PtrLen<const Char> x);

  public:

   explicit PadTextParser(PtrLen<const Char> text,CharAccent *accent=0) : ParserBase(text,accent) {}

   operator bool() const { return state!=-1; }
 };

/* enum AtomClass */

enum AtomClass
 {
  AtomNull = 0,

  Atom_obr      =  1,  /*  (  */
  Atom_cbr      =  2,  /*  )  */
  Atom_asterisk =  3,  /*  *  */
  Atom_plus     =  4,  /*  +  */
  Atom_comma    =  5,  /*  ,  */
  Atom_minus    =  6,  /*  -  */
  Atom_div      =  7,  /*  /  */
  Atom_assign   =  8,  /*  =  */

  Atom_Angle    =  9,  /*  Angle   */
  Atom_Length   = 10,  /*  Length  */
  Atom_Name     = 11,  /*  Name    */
  Atom_Number   = 12   /*  Number  */
 };

/* struct Atom */

struct Atom : Token
 {
  AtomClass ac;

  Atom() noexcept : ac(AtomNull) {}

  Atom(const Token &token);
 };

/* struct FormulaParserData */

struct FormulaParserData
 {
  using Rule = int ;

  static const Rule NoRule = -1 ;

  static const Rule ShiftRule = 0 ;

  using ElementIndex = int ;

  using Property = Rule (*)(AtomClass) ;

  struct State;

  using Transition = const State * (*)(ElementIndex) ;

  static ElementIndex RuleOutput(Rule rule);

  static ElementIndex AtomToElement(AtomClass ac) { return ac; }

  struct State
   {
    Property prop;
    Transition trans;
   };

  static const State *Start;
 };

/* class FormulaTextParser<Context> */

template <class Context>
class FormulaTextParser : public ParserBase , FormulaParserData
 {
   struct Element : MemBase
    {
     virtual ~Element() {}
    };

   struct ElementAtom : Element
    {
     Atom atom;

     explicit ElementAtom(const Atom &atom_) : atom(atom_) {}
    };

   struct Element_EXPR;

   struct Element_FORMULA;

   struct Element_EXPR_LIST;

   struct Element_FORMULA : Element
    {
     bool set(Context &ctx,ElementAtom *name,ElementAtom *,Element_EXPR *expr)
      {
       return ctx.set(name->atom.str,expr->value);
      }
    };

   struct Element_EXPR : Element
    {
     typename Context::ExprType value;

     bool add(Context &ctx,Element_EXPR *a,ElementAtom *,Element_EXPR *b) { return ctx.add(value,a->value,b->value); }

     bool sub(Context &ctx,Element_EXPR *a,ElementAtom *,Element_EXPR *b) { return ctx.sub(value,a->value,b->value); }

     bool mul(Context &ctx,Element_EXPR *a,ElementAtom *,Element_EXPR *b) { return ctx.mul(value,a->value,b->value); }

     bool div(Context &ctx,Element_EXPR *a,ElementAtom *,Element_EXPR *b) { return ctx.div(value,a->value,b->value); }

     bool neg(Context &ctx,ElementAtom *,Element_EXPR *a) { return ctx.neg(value,a->value); }

     bool brace(Context &,ElementAtom *,Element_EXPR *a,ElementAtom *) { value=a->value; return true; }

     bool func(Context &ctx,ElementAtom *name,ElementAtom *,Element_EXPR_LIST *list,ElementAtom *)
      {
       return ctx.func(value,name->atom.str,Range(list->values));
      }

     bool arg(Context &ctx,ElementAtom *name) { return ctx.arg(value,name->atom.str); }

     bool number(Context &ctx,ElementAtom *number) { return ctx.number(value,number->atom.getNumber()); }

     bool angle(Context &ctx,ElementAtom *angle) { return ctx.angle(value,angle->atom.getNumber()); }

     bool length(Context &ctx,ElementAtom *length) { return ctx.angle(value,length->atom.getNumber()); }

     bool point(Context &ctx,ElementAtom *,ElementAtom *x,ElementAtom *,ElementAtom *y,ElementAtom *)
      {
       return ctx.point(value,x->atom.getNumber(),y->atom.getNumber());
      }
    };

   struct Element_EXPR_LIST : Element
    {
     RefArray<typename Context::ExprType> values;

     bool empty(Context &) { return true; }

     bool one(Context &,Element_EXPR *expr) { values.reserve(10); values.append_copy(expr->value); return true; }

     bool ext(Context &,Element_EXPR_LIST *list,ElementAtom *,Element_EXPR *expr)
      {
       values=list->values;

       values.append_copy(expr->value);

       return true;
      }
    };

   static auto Apply(Rule rule,auto func)
    {
     switch( rule )
       {
        case 1 : return func(&Element_FORMULA::set,ElementIndex(13));
        case 2 : return func(&Element_EXPR::add,ElementIndex(14));
        case 3 : return func(&Element_EXPR::sub,ElementIndex(14));
        case 4 : return func(&Element_EXPR::mul,ElementIndex(15));
        case 5 : return func(&Element_EXPR::div,ElementIndex(15));
        case 6 : return func(&Element_EXPR::neg,ElementIndex(16));
        case 7 : return func(&Element_EXPR::brace,ElementIndex(17));
        case 8 : return func(&Element_EXPR::func,ElementIndex(17));
        case 9 : return func(&Element_EXPR::arg,ElementIndex(17));
        case 10 : return func(&Element_EXPR::number,ElementIndex(17));
        case 11 : return func(&Element_EXPR::angle,ElementIndex(17));
        case 12 : return func(&Element_EXPR::length,ElementIndex(17));
        case 13 : return func(&Element_EXPR::point,ElementIndex(17));
        case 14 : return func(&Element_EXPR_LIST::empty,ElementIndex(18));
        case 15 : return func(&Element_EXPR_LIST::one,ElementIndex(19));
        case 16 : return func(&Element_EXPR_LIST::ext,ElementIndex(19));

        default: return func();
       }
    };

  private:

   struct Prod
    {
     const State *state = Start ;
     Element *element = 0 ;

     Prod() noexcept {}

     Prod(const State *state_,Element *element_) : state(state_),element(element_) {}

     template <class E>
     operator E * () const { return static_cast<E *>(element); }
    };

   Context &ctx;

   DynArray<Prod> stack;
   bool ok = true ;

  private:

   void paintError(Token token)
    {
     ok=false;

     paint(token,CharError);
    }

   Prod & top()
    {
     ulen len=stack.getLen();

     return stack[len-1];
    }

   void push(const Atom &atom)
    {
     stack.reserve(1);

     const State *state=top().state;

     stack.append_fill(state->trans(AtomToElement(atom.ac)),new ElementAtom(atom));
    }

   void pop(ulen count)
    {
     for(Prod &prod : Range(stack).suffix(count) ) delete prod.element;

     stack.shrink(count);
    }

   template <class T>
   void paintAtom(T) {}

   void paintAtom(ElementAtom *element) { paintError(element->atom); }

   template <class ... TT>
   void paintAtoms(TT ... tt)
    {
     ( ... , paintAtom(tt) );
    }

   template <class E,class ... TT,int ... IList>
   bool applyRule(bool (E::*method)(Context &,TT...),ElementIndex ei,Meta::IndexListBox<IList...>)
    {
     stack.reserve(1);

     ulen len=stack.getLen();
     Prod *base=stack.getPtr()+(len-sizeof ... (TT));

     E *element=new E{};

     bool ok=(element->*method)(ctx,base[IList]...);

     if( !ok )
       {
        paintAtoms<TT...>(base[IList]...);

        delete element;

        return false;
       }

     pop(sizeof ... (TT));

     const State *state=top().state;

     stack.append_fill(state->trans(ei),element);

     return true;
    }

   struct RuleFunc
    {
     FormulaTextParser *obj;

     bool operator () () { return false; }

     template <class E,class ... TT>
     bool operator () (bool (E::*method)(Context &,TT...),ElementIndex ei)
      {
       return obj->applyRule(method,ei, Meta::IndexList<0,TT...>() );
      }
    };

   bool applyRule(Rule rule)
    {
     return Apply(rule,RuleFunc{this});
    }

   virtual void next(Token token)
    {
     paint(token);

     if( !ok ) return;

     if( token.is(Token_Space) ) return;

     if( token.is(Token_Other) )
       {
        ok=false;

        return;
       }

     Atom atom(token);

     for(;;)
       switch( Rule rule=top().state->prop(atom.ac) )
         {
          case -1 : paintError(token); return;

          case 0 : push(atom); return;

          default: if( !applyRule(rule) ) { ok=false; return; }
         }
    }

   virtual void stop()
    {
     if( !ok ) return;

     for(;;)
       switch( Rule rule=top().state->prop(AtomNull) )
         {
          case -1 : ok=false; return;

          case 0 : return;

          default: if( !applyRule(rule) ) { ok=false; return; }
         }
    }

  public:

   FormulaTextParser(Context &ctx_,PtrLen<const Char> text,CharAccent *accent=0)
    : ParserBase(text,accent),
      ctx(ctx_)
    {
     stack.append_default();
    }

   ~FormulaTextParser()
    {
     ulen len=stack.getLen();

     pop(len-1);
    }

   operator bool() const { return ok; }
 };

} // namespace App

#endif
