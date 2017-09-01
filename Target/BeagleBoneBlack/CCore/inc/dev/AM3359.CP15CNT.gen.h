/* AM3359.CP15CNT.gen.h */

/* struct Type_Control */

enum Bits_Control : uint32
 {
  Control_E  = 0x00000001u,
  Control_P  = 0x00000002u,
  Control_C  = 0x00000004u,
  Control_D  = 0x00000008u,
  Control_X  = 0x00000010u,
  Control_DP = 0x00000020u
 };
 
inline Bits_Control operator | (Bits_Control a,Bits_Control b)
 { return Bits_Control(uint32(a)|uint32(b)); }
 
struct Type_Control
 {
  using Type = uint32 ;

  Type value;


  explicit Type_Control(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Control & setTo(Bar &bar) { bar.set_Control(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_Control & setTo(Bar &bar,AddressType ind) { bar.set_Control(ind,*this); return *this; }
 

  template <class T>
  Type_Control & set(T to) { to(*this); return *this; }
 

  Type_Control & setbit(Bits_Control bits) { value|=Type(bits); return *this; }
 
  Type_Control & setbitIf(bool cond,Bits_Control bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_Control & clearbit(Bits_Control bits) { value&=~Type(bits); return *this; }
 
  Type_Control & clearbitIf(bool cond,Bits_Control bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_Control bits) const { return value&bits; }
 
  bool testbit(Bits_Control bits) const { return (value&bits)==Type(bits); }
 

  Type get_N() const
   {
    return (value>>11)&0x1Fu;
   }
 
  Type_Control & set_N(Type field)
   {
    value=((field&0x1Fu)<<11)|(value&0xFFFF07FFu);

    return *this;
   }
 

  Type get_ID() const
   {
    return (value>>16)&0xFFu;
   }
 
  Type_Control & set_ID(Type field)
   {
    value=((field&0xFFu)<<16)|(value&0xFF00FFFFu);

    return *this;
   }
 

  Type get_IMP() const
   {
    return (value>>24)&0xFFu;
   }
 
  Type_Control & set_IMP(Type field)
   {
    value=((field&0xFFu)<<24)|(value&0xFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&Control_E )
      {
       if( first )
         {
          Putobj(out,"E");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"E");
         }
      }

    if( value&Control_P )
      {
       if( first )
         {
          Putobj(out,"P");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"P");
         }
      }

    if( value&Control_C )
      {
       if( first )
         {
          Putobj(out,"C");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"C");
         }
      }

    if( value&Control_D )
      {
       if( first )
         {
          Putobj(out,"D");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"D");
         }
      }

    if( value&Control_X )
      {
       if( first )
         {
          Putobj(out,"X");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"X");
         }
      }

    if( value&Control_DP )
      {
       if( first )
         {
          Putobj(out,"DP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DP");
         }
      }

    if( first )
      {
       Printf(out,"N(#;)",get_N());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"N(#;)",get_N());
      }

    if( first )
      {
       Printf(out,"ID(#;)",get_ID());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ID(#;)",get_ID());
      }

    if( first )
      {
       Printf(out,"IMP(#;)",get_IMP());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"IMP(#;)",get_IMP());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_CounterBits */

enum Bits_CounterBits : uint32
 {
  CounterBits_C = 0x80000000u
 };
 
inline Bits_CounterBits operator | (Bits_CounterBits a,Bits_CounterBits b)
 { return Bits_CounterBits(uint32(a)|uint32(b)); }
 
struct Type_CounterBits
 {
  using Type = uint32 ;

  Type value;


  explicit Type_CounterBits(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CounterBits & setTo(Bar &bar) { bar.set_CounterBits(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_CounterBits & setTo(Bar &bar,AddressType ind) { bar.set_CounterBits(ind,*this); return *this; }
 

  template <class T>
  Type_CounterBits & set(T to) { to(*this); return *this; }
 

  Type_CounterBits & setbit(Bits_CounterBits bits) { value|=Type(bits); return *this; }
 
  Type_CounterBits & setbitIf(bool cond,Bits_CounterBits bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CounterBits & clearbit(Bits_CounterBits bits) { value&=~Type(bits); return *this; }
 
  Type_CounterBits & clearbitIf(bool cond,Bits_CounterBits bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CounterBits bits) const { return value&bits; }
 
  bool testbit(Bits_CounterBits bits) const { return (value&bits)==Type(bits); }
 

  Type get_P() const
   {
    return (value>>0)&0x7FFFFFFFu;
   }
 
  Type_CounterBits & set_P(Type field)
   {
    value=((field&0x7FFFFFFFu)<<0)|(value&0x80000000u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CounterBits_C )
      {
       if( first )
         {
          Putobj(out,"C");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"C");
         }
      }

    if( first )
      {
       Printf(out,"P(#;)",get_P());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"P(#;)",get_P());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_ClockCount */

using Type_ClockCount = uint32 ;

/* struct Type_CounterSelect */

struct Type_CounterSelect
 {
  using Type = uint32 ;

  Type value;


  explicit Type_CounterSelect(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CounterSelect & setTo(Bar &bar) { bar.set_CounterSelect(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_CounterSelect & setTo(Bar &bar,AddressType ind) { bar.set_CounterSelect(ind,*this); return *this; }
 

  template <class T>
  Type_CounterSelect & set(T to) { to(*this); return *this; }
 

  Type get_SEL() const
   {
    return (value>>0)&0x1Fu;
   }
 
  Type_CounterSelect & set_SEL(Type field)
   {
    value=((field&0x1Fu)<<0)|(value&0xFFFFFFE0u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"SEL(#;)",get_SEL());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SEL(#;)",get_SEL());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_EventSelect */

struct Type_EventSelect
 {
  using Type = uint32 ;

  Type value;


  explicit Type_EventSelect(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_EventSelect & setTo(Bar &bar) { bar.set_EventSelect(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_EventSelect & setTo(Bar &bar,AddressType ind) { bar.set_EventSelect(ind,*this); return *this; }
 

  template <class T>
  Type_EventSelect & set(T to) { to(*this); return *this; }
 

  Type get_SEL() const
   {
    return (value>>0)&0xFFu;
   }
 
  Type_EventSelect & set_SEL(Type field)
   {
    value=((field&0xFFu)<<0)|(value&0xFFFFFF00u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"SEL(#;)",get_SEL());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SEL(#;)",get_SEL());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_Count */

using Type_Count = uint32 ;

/* struct Type_UserCountEnable */

enum Bits_UserCountEnable : uint32
 {
  UserCountEnable_EN = 0x00000001u
 };
 
inline Bits_UserCountEnable operator | (Bits_UserCountEnable a,Bits_UserCountEnable b)
 { return Bits_UserCountEnable(uint32(a)|uint32(b)); }
 
struct Type_UserCountEnable
 {
  using Type = uint32 ;

  Type value;


  explicit Type_UserCountEnable(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_UserCountEnable & setTo(Bar &bar) { bar.set_UserCountEnable(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_UserCountEnable & setTo(Bar &bar,AddressType ind) { bar.set_UserCountEnable(ind,*this); return *this; }
 

  template <class T>
  Type_UserCountEnable & set(T to) { to(*this); return *this; }
 

  Type_UserCountEnable & setbit(Bits_UserCountEnable bits) { value|=Type(bits); return *this; }
 
  Type_UserCountEnable & setbitIf(bool cond,Bits_UserCountEnable bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_UserCountEnable & clearbit(Bits_UserCountEnable bits) { value&=~Type(bits); return *this; }
 
  Type_UserCountEnable & clearbitIf(bool cond,Bits_UserCountEnable bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_UserCountEnable bits) const { return value&bits; }
 
  bool testbit(Bits_UserCountEnable bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&UserCountEnable_EN )
      {
       if( first )
         {
          Putobj(out,"EN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EN");
         }
      }

    if( first ) out.put('0');
   }
 };
 
