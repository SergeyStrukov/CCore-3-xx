/* enum AtomClass */

enum AtomClass
 {
  AtomNull = 0,

  Atom_XXX_1 = 1,  /*  (  */
  Atom_XXX_2 = 2,  /*  )  */
  Atom_XXX_3 = 3,  /*  *  */
  Atom_XXX_4 = 4,  /*  +  */
  Atom_XXX_5 = 5,  /*  ,  */
  Atom_XXX_6 = 6,  /*  -  */
  Atom_XXX_7 = 7,  /*  /  */
  Atom_XXX_8 = 8,  /*  =  */
  Atom_XXX_9 = 9,  /*  Angle  */
  Atom_XXX_10 = 10,  /*  Length  */
  Atom_XXX_11 = 11,  /*  Name  */
  Atom_XXX_12 = 12,  /*  Number  */
 };

const char * GetTextDesc(AtomClass ac);

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

  struct Element;

  struct ElementAtom;

  struct Element_FORMULA;
  struct Element_EXPR;
  struct Element_EXPR_LIST;

  static auto Apply(Rule rule,auto func);
 };

struct FormulaParserData::Element // TODO
 {
  using RetType = void ;

  using ContextType = int ;

 };

struct FormulaParserData::ElementAtom : Element // TODO
 {
  // TODO
 };

struct FormulaParserData::Element_FORMULA : Element
 {
  // TODO

  RetType set(ContextType,ElementAtom *,ElementAtom *,Element_EXPR *);

 };

struct FormulaParserData::Element_EXPR : Element
 {
  // TODO

  RetType add(ContextType,Element_EXPR *,ElementAtom *,Element_EXPR *);

  RetType sub(ContextType,Element_EXPR *,ElementAtom *,Element_EXPR *);

  RetType mul(ContextType,Element_EXPR *,ElementAtom *,Element_EXPR *);

  RetType div(ContextType,Element_EXPR *,ElementAtom *,Element_EXPR *);

  RetType neg(ContextType,ElementAtom *,Element_EXPR *);

  RetType brace(ContextType,ElementAtom *,Element_EXPR *,ElementAtom *);

  RetType func(ContextType,ElementAtom *,ElementAtom *,Element_EXPR_LIST *,ElementAtom *);

  RetType arg(ContextType,ElementAtom *);

  RetType number(ContextType,ElementAtom *);

  RetType angle(ContextType,ElementAtom *);

  RetType length(ContextType,ElementAtom *);

  RetType point(ContextType,ElementAtom *,ElementAtom *,ElementAtom *,ElementAtom *,ElementAtom *);

 };

struct FormulaParserData::Element_EXPR_LIST : Element
 {
  // TODO

  RetType empty(ContextType);

  RetType one(ContextType,Element_EXPR *);

  RetType ext(ContextType,Element_EXPR_LIST *,ElementAtom *,Element_EXPR *);

 };

auto FormulaParserData::Apply(Rule rule,auto func)
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

