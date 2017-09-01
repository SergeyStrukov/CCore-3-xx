/* AM3359.PRCM.gen.h */

/* struct Type_ClockControl */

enum Field_ClockControl_Mode : uint32
 {
  ClockControl_Mode_Disable = 0x00u,
  ClockControl_Mode_Enable  = 0x02u
 };
 
struct PrintField_ClockControl_Mode
 {
  Field_ClockControl_Mode field;

  explicit PrintField_ClockControl_Mode(Field_ClockControl_Mode field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"Disable"); break;
       case 0x02u : Putobj(out,"Enable"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_ClockControl_Mode GetTextDesc(Field_ClockControl_Mode field)
 {
  return PrintField_ClockControl_Mode(field);
 }
 
enum Field_ClockControl_IdleStatus : uint32
 {
  ClockControl_IdleStatus_Running    = 0x00u,
  ClockControl_IdleStatus_Transition = 0x01u,
  ClockControl_IdleStatus_Idle       = 0x02u,
  ClockControl_IdleStatus_Disabled   = 0x03u
 };
 
struct PrintField_ClockControl_IdleStatus
 {
  Field_ClockControl_IdleStatus field;

  explicit PrintField_ClockControl_IdleStatus(Field_ClockControl_IdleStatus field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"Running"); break;
       case 0x01u : Putobj(out,"Transition"); break;
       case 0x02u : Putobj(out,"Idle"); break;
       case 0x03u : Putobj(out,"Disabled"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_ClockControl_IdleStatus GetTextDesc(Field_ClockControl_IdleStatus field)
 {
  return PrintField_ClockControl_IdleStatus(field);
 }
 
struct Type_ClockControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_ClockControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ClockControl & setTo(Bar &bar) { bar.set_ClockControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_ClockControl & setTo(Bar &bar,AddressType ind) { bar.set_ClockControl(ind,*this); return *this; }
 

  template <class T>
  Type_ClockControl & set(T to) { to(*this); return *this; }
 

  Field_ClockControl_Mode get_Mode() const
   {
    return Field_ClockControl_Mode((value>>0)&0x3u);
   }
 
  Type_ClockControl & set_Mode(Field_ClockControl_Mode field)
   {
    value=((Type(field)&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  Field_ClockControl_IdleStatus get_IdleStatus() const
   {
    return Field_ClockControl_IdleStatus((value>>16)&0x3u);
   }
 
  Type_ClockControl & set_IdleStatus(Field_ClockControl_IdleStatus field)
   {
    value=((Type(field)&0x3u)<<16)|(value&0xFFFCFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Mode(#;)",get_Mode());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Mode(#;)",get_Mode());
      }

    if( first )
      {
       Printf(out,"IdleStatus(#;)",get_IdleStatus());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"IdleStatus(#;)",get_IdleStatus());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_ClockStandbyControl */

enum Bits_ClockStandbyControl : uint32
 {
  ClockStandbyControl_StandbyStatus = 0x00040000u
 };
 
inline Bits_ClockStandbyControl operator | (Bits_ClockStandbyControl a,Bits_ClockStandbyControl b)
 { return Bits_ClockStandbyControl(uint32(a)|uint32(b)); }
 
enum Field_ClockStandbyControl_Mode : uint32
 {
  ClockStandbyControl_Mode_Disable = 0x00u,
  ClockStandbyControl_Mode_Enable  = 0x02u
 };
 
struct PrintField_ClockStandbyControl_Mode
 {
  Field_ClockStandbyControl_Mode field;

  explicit PrintField_ClockStandbyControl_Mode(Field_ClockStandbyControl_Mode field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"Disable"); break;
       case 0x02u : Putobj(out,"Enable"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_ClockStandbyControl_Mode GetTextDesc(Field_ClockStandbyControl_Mode field)
 {
  return PrintField_ClockStandbyControl_Mode(field);
 }
 
enum Field_ClockStandbyControl_IdleStatus : uint32
 {
  ClockStandbyControl_IdleStatus_Running    = 0x00u,
  ClockStandbyControl_IdleStatus_Transition = 0x01u,
  ClockStandbyControl_IdleStatus_Idle       = 0x02u,
  ClockStandbyControl_IdleStatus_Disabled   = 0x03u
 };
 
struct PrintField_ClockStandbyControl_IdleStatus
 {
  Field_ClockStandbyControl_IdleStatus field;

  explicit PrintField_ClockStandbyControl_IdleStatus(Field_ClockStandbyControl_IdleStatus field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"Running"); break;
       case 0x01u : Putobj(out,"Transition"); break;
       case 0x02u : Putobj(out,"Idle"); break;
       case 0x03u : Putobj(out,"Disabled"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_ClockStandbyControl_IdleStatus GetTextDesc(Field_ClockStandbyControl_IdleStatus field)
 {
  return PrintField_ClockStandbyControl_IdleStatus(field);
 }
 
struct Type_ClockStandbyControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_ClockStandbyControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ClockStandbyControl & setTo(Bar &bar) { bar.set_ClockStandbyControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_ClockStandbyControl & setTo(Bar &bar,AddressType ind) { bar.set_ClockStandbyControl(ind,*this); return *this; }
 

  template <class T>
  Type_ClockStandbyControl & set(T to) { to(*this); return *this; }
 

  Type_ClockStandbyControl & setbit(Bits_ClockStandbyControl bits) { value|=Type(bits); return *this; }
 
  Type_ClockStandbyControl & setbitIf(bool cond,Bits_ClockStandbyControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_ClockStandbyControl & clearbit(Bits_ClockStandbyControl bits) { value&=~Type(bits); return *this; }
 
  Type_ClockStandbyControl & clearbitIf(bool cond,Bits_ClockStandbyControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_ClockStandbyControl bits) const { return value&bits; }
 
  bool testbit(Bits_ClockStandbyControl bits) const { return (value&bits)==Type(bits); }
 

  Field_ClockStandbyControl_Mode get_Mode() const
   {
    return Field_ClockStandbyControl_Mode((value>>0)&0x3u);
   }
 
  Type_ClockStandbyControl & set_Mode(Field_ClockStandbyControl_Mode field)
   {
    value=((Type(field)&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  Field_ClockStandbyControl_IdleStatus get_IdleStatus() const
   {
    return Field_ClockStandbyControl_IdleStatus((value>>16)&0x3u);
   }
 
  Type_ClockStandbyControl & set_IdleStatus(Field_ClockStandbyControl_IdleStatus field)
   {
    value=((Type(field)&0x3u)<<16)|(value&0xFFFCFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&ClockStandbyControl_StandbyStatus )
      {
       if( first )
         {
          Putobj(out,"StandbyStatus");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"StandbyStatus");
         }
      }

    if( first )
      {
       Printf(out,"Mode(#;)",get_Mode());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Mode(#;)",get_Mode());
      }

    if( first )
      {
       Printf(out,"IdleStatus(#;)",get_IdleStatus());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"IdleStatus(#;)",get_IdleStatus());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_EthClockControl */

enum Bits_EthClockControl : uint32
 {
  EthClockControl_Active = 0x00000010u
 };
 
inline Bits_EthClockControl operator | (Bits_EthClockControl a,Bits_EthClockControl b)
 { return Bits_EthClockControl(uint32(a)|uint32(b)); }
 
enum Field_EthClockControl_Control : uint32
 {
  EthClockControl_Control_NoSleep     = 0x00u,
  EthClockControl_Control_ForceSleep  = 0x01u,
  EthClockControl_Control_ForceWakeup = 0x02u
 };
 
struct PrintField_EthClockControl_Control
 {
  Field_EthClockControl_Control field;

  explicit PrintField_EthClockControl_Control(Field_EthClockControl_Control field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"NoSleep"); break;
       case 0x01u : Putobj(out,"ForceSleep"); break;
       case 0x02u : Putobj(out,"ForceWakeup"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_EthClockControl_Control GetTextDesc(Field_EthClockControl_Control field)
 {
  return PrintField_EthClockControl_Control(field);
 }
 
struct Type_EthClockControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_EthClockControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_EthClockControl & setTo(Bar &bar) { bar.set_EthClockControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_EthClockControl & setTo(Bar &bar,AddressType ind) { bar.set_EthClockControl(ind,*this); return *this; }
 

  template <class T>
  Type_EthClockControl & set(T to) { to(*this); return *this; }
 

  Type_EthClockControl & setbit(Bits_EthClockControl bits) { value|=Type(bits); return *this; }
 
  Type_EthClockControl & setbitIf(bool cond,Bits_EthClockControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_EthClockControl & clearbit(Bits_EthClockControl bits) { value&=~Type(bits); return *this; }
 
  Type_EthClockControl & clearbitIf(bool cond,Bits_EthClockControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_EthClockControl bits) const { return value&bits; }
 
  bool testbit(Bits_EthClockControl bits) const { return (value&bits)==Type(bits); }
 

  Field_EthClockControl_Control get_Control() const
   {
    return Field_EthClockControl_Control((value>>0)&0x3u);
   }
 
  Type_EthClockControl & set_Control(Field_EthClockControl_Control field)
   {
    value=((Type(field)&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&EthClockControl_Active )
      {
       if( first )
         {
          Putobj(out,"Active");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Active");
         }
      }

    if( first )
      {
       Printf(out,"Control(#;)",get_Control());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Control(#;)",get_Control());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_TimerClockSelect */

enum Field_TimerClockSelect_Source : uint32
 {
  TimerClockSelect_Source_TCLKIN    = 0x00u,
  TimerClockSelect_Source_CLK_M_OSC = 0x01u,
  TimerClockSelect_Source_CLK_32KHZ = 0x02u
 };
 
struct PrintField_TimerClockSelect_Source
 {
  Field_TimerClockSelect_Source field;

  explicit PrintField_TimerClockSelect_Source(Field_TimerClockSelect_Source field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"TCLKIN"); break;
       case 0x01u : Putobj(out,"CLK_M_OSC"); break;
       case 0x02u : Putobj(out,"CLK_32KHZ"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_TimerClockSelect_Source GetTextDesc(Field_TimerClockSelect_Source field)
 {
  return PrintField_TimerClockSelect_Source(field);
 }
 
struct Type_TimerClockSelect
 {
  using Type = uint32 ;

  Type value;


  explicit Type_TimerClockSelect(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TimerClockSelect & setTo(Bar &bar) { bar.set_TimerClockSelect(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_TimerClockSelect & setTo(Bar &bar,AddressType ind) { bar.set_TimerClockSelect(ind,*this); return *this; }
 

  template <class T>
  Type_TimerClockSelect & set(T to) { to(*this); return *this; }
 

  Field_TimerClockSelect_Source get_Source() const
   {
    return Field_TimerClockSelect_Source((value>>0)&0x3u);
   }
 
  Type_TimerClockSelect & set_Source(Field_TimerClockSelect_Source field)
   {
    value=((Type(field)&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Source(#;)",get_Source());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Source(#;)",get_Source());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_LCDClockSelect */

enum Field_LCDClockSelect_Source : uint32
 {
  LCDClockSelect_Source_DISP_PLL_CLKOUTM2 = 0x00u,
  LCDClockSelect_Source_CORE_PLL_CLKOUTM5 = 0x01u,
  LCDClockSelect_Source_PER_PLL_CLKOUTM2  = 0x02u
 };
 
struct PrintField_LCDClockSelect_Source
 {
  Field_LCDClockSelect_Source field;

  explicit PrintField_LCDClockSelect_Source(Field_LCDClockSelect_Source field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"DISP_PLL_CLKOUTM2"); break;
       case 0x01u : Putobj(out,"CORE_PLL_CLKOUTM5"); break;
       case 0x02u : Putobj(out,"PER_PLL_CLKOUTM2"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_LCDClockSelect_Source GetTextDesc(Field_LCDClockSelect_Source field)
 {
  return PrintField_LCDClockSelect_Source(field);
 }
 
struct Type_LCDClockSelect
 {
  using Type = uint32 ;

  Type value;


  explicit Type_LCDClockSelect(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_LCDClockSelect & setTo(Bar &bar) { bar.set_LCDClockSelect(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_LCDClockSelect & setTo(Bar &bar,AddressType ind) { bar.set_LCDClockSelect(ind,*this); return *this; }
 

  template <class T>
  Type_LCDClockSelect & set(T to) { to(*this); return *this; }
 

  Field_LCDClockSelect_Source get_Source() const
   {
    return Field_LCDClockSelect_Source((value>>0)&0x3u);
   }
 
  Type_LCDClockSelect & set_Source(Field_LCDClockSelect_Source field)
   {
    value=((Type(field)&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Source(#;)",get_Source());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Source(#;)",get_Source());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_CPTSClockSelect */

enum Bits_CPTSClockSelect : uint32
 {
  CPTSClockSelect_M4 = 0x00000001u
 };
 
inline Bits_CPTSClockSelect operator | (Bits_CPTSClockSelect a,Bits_CPTSClockSelect b)
 { return Bits_CPTSClockSelect(uint32(a)|uint32(b)); }
 
struct Type_CPTSClockSelect
 {
  using Type = uint32 ;

  Type value;


  explicit Type_CPTSClockSelect(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CPTSClockSelect & setTo(Bar &bar) { bar.set_CPTSClockSelect(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_CPTSClockSelect & setTo(Bar &bar,AddressType ind) { bar.set_CPTSClockSelect(ind,*this); return *this; }
 

  template <class T>
  Type_CPTSClockSelect & set(T to) { to(*this); return *this; }
 

  Type_CPTSClockSelect & setbit(Bits_CPTSClockSelect bits) { value|=Type(bits); return *this; }
 
  Type_CPTSClockSelect & setbitIf(bool cond,Bits_CPTSClockSelect bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CPTSClockSelect & clearbit(Bits_CPTSClockSelect bits) { value&=~Type(bits); return *this; }
 
  Type_CPTSClockSelect & clearbitIf(bool cond,Bits_CPTSClockSelect bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CPTSClockSelect bits) const { return value&bits; }
 
  bool testbit(Bits_CPTSClockSelect bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CPTSClockSelect_M4 )
      {
       if( first )
         {
          Putobj(out,"M4");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"M4");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PLLIdleStatus */

enum Bits_PLLIdleStatus : uint32
 {
  PLLIdleStatus_Locked = 0x00000001u,
  PLLIdleStatus_Bypass = 0x00000100u
 };
 
inline Bits_PLLIdleStatus operator | (Bits_PLLIdleStatus a,Bits_PLLIdleStatus b)
 { return Bits_PLLIdleStatus(uint32(a)|uint32(b)); }
 
struct Type_PLLIdleStatus
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PLLIdleStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PLLIdleStatus & setTo(Bar &bar) { bar.set_PLLIdleStatus(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PLLIdleStatus & setTo(Bar &bar,AddressType ind) { bar.set_PLLIdleStatus(ind,*this); return *this; }
 

  template <class T>
  Type_PLLIdleStatus & set(T to) { to(*this); return *this; }
 

  Type_PLLIdleStatus & setbit(Bits_PLLIdleStatus bits) { value|=Type(bits); return *this; }
 
  Type_PLLIdleStatus & setbitIf(bool cond,Bits_PLLIdleStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_PLLIdleStatus & clearbit(Bits_PLLIdleStatus bits) { value&=~Type(bits); return *this; }
 
  Type_PLLIdleStatus & clearbitIf(bool cond,Bits_PLLIdleStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_PLLIdleStatus bits) const { return value&bits; }
 
  bool testbit(Bits_PLLIdleStatus bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&PLLIdleStatus_Locked )
      {
       if( first )
         {
          Putobj(out,"Locked");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Locked");
         }
      }

    if( value&PLLIdleStatus_Bypass )
      {
       if( first )
         {
          Putobj(out,"Bypass");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Bypass");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PLLClockSelect */

enum Bits_PLLClockSelect : uint32
 {
  PLLClockSelect_BypassSelect = 0x00800000u
 };
 
inline Bits_PLLClockSelect operator | (Bits_PLLClockSelect a,Bits_PLLClockSelect b)
 { return Bits_PLLClockSelect(uint32(a)|uint32(b)); }
 
struct Type_PLLClockSelect
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PLLClockSelect(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PLLClockSelect & setTo(Bar &bar) { bar.set_PLLClockSelect(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PLLClockSelect & setTo(Bar &bar,AddressType ind) { bar.set_PLLClockSelect(ind,*this); return *this; }
 

  template <class T>
  Type_PLLClockSelect & set(T to) { to(*this); return *this; }
 

  Type_PLLClockSelect & setbit(Bits_PLLClockSelect bits) { value|=Type(bits); return *this; }
 
  Type_PLLClockSelect & setbitIf(bool cond,Bits_PLLClockSelect bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_PLLClockSelect & clearbit(Bits_PLLClockSelect bits) { value&=~Type(bits); return *this; }
 
  Type_PLLClockSelect & clearbitIf(bool cond,Bits_PLLClockSelect bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_PLLClockSelect bits) const { return value&bits; }
 
  bool testbit(Bits_PLLClockSelect bits) const { return (value&bits)==Type(bits); }
 

  Type get_Div() const
   {
    return (value>>0)&0x7Fu;
   }
 
  Type_PLLClockSelect & set_Div(Type field)
   {
    value=((field&0x7Fu)<<0)|(value&0xFFFFFF80u);

    return *this;
   }
 

  Type get_Mul() const
   {
    return (value>>8)&0x7FFu;
   }
 
  Type_PLLClockSelect & set_Mul(Type field)
   {
    value=((field&0x7FFu)<<8)|(value&0xFFF800FFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&PLLClockSelect_BypassSelect )
      {
       if( first )
         {
          Putobj(out,"BypassSelect");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BypassSelect");
         }
      }

    if( first )
      {
       Printf(out,"Div(#;)",get_Div());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Div(#;)",get_Div());
      }

    if( first )
      {
       Printf(out,"Mul(#;)",get_Mul());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Mul(#;)",get_Mul());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PLLDivM2 */

enum Bits_PLLDivM2 : uint32
 {
  PLLDivM2_M2Ack      = 0x00000020u,
  PLLDivM2_NoAutoGate = 0x00000100u,
  PLLDivM2_Running    = 0x00000200u
 };
 
inline Bits_PLLDivM2 operator | (Bits_PLLDivM2 a,Bits_PLLDivM2 b)
 { return Bits_PLLDivM2(uint32(a)|uint32(b)); }
 
struct Type_PLLDivM2
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PLLDivM2(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PLLDivM2 & setTo(Bar &bar) { bar.set_PLLDivM2(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PLLDivM2 & setTo(Bar &bar,AddressType ind) { bar.set_PLLDivM2(ind,*this); return *this; }
 

  template <class T>
  Type_PLLDivM2 & set(T to) { to(*this); return *this; }
 

  Type_PLLDivM2 & setbit(Bits_PLLDivM2 bits) { value|=Type(bits); return *this; }
 
  Type_PLLDivM2 & setbitIf(bool cond,Bits_PLLDivM2 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_PLLDivM2 & clearbit(Bits_PLLDivM2 bits) { value&=~Type(bits); return *this; }
 
  Type_PLLDivM2 & clearbitIf(bool cond,Bits_PLLDivM2 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_PLLDivM2 bits) const { return value&bits; }
 
  bool testbit(Bits_PLLDivM2 bits) const { return (value&bits)==Type(bits); }
 

  Type get_M2() const
   {
    return (value>>0)&0x1Fu;
   }
 
  Type_PLLDivM2 & set_M2(Type field)
   {
    value=((field&0x1Fu)<<0)|(value&0xFFFFFFE0u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&PLLDivM2_M2Ack )
      {
       if( first )
         {
          Putobj(out,"M2Ack");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"M2Ack");
         }
      }

    if( value&PLLDivM2_NoAutoGate )
      {
       if( first )
         {
          Putobj(out,"NoAutoGate");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NoAutoGate");
         }
      }

    if( value&PLLDivM2_Running )
      {
       if( first )
         {
          Putobj(out,"Running");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Running");
         }
      }

    if( first )
      {
       Printf(out,"M2(#;)",get_M2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"M2(#;)",get_M2());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PLLClockMode */

enum Bits_PLLClockMode : uint32
 {
  PLLClockMode_DriftGuard   = 0x00000100u,
  PLLClockMode_RelockRamp   = 0x00000200u,
  PLLClockMode_LPMode       = 0x00000400u,
  PLLClockMode_REGM4X       = 0x00000800u,
  PLLClockMode_SSC          = 0x00001000u,
  PLLClockMode_SSCAck       = 0x00002000u,
  PLLClockMode_SSCLowSpread = 0x00004000u,
  PLLClockMode_SSCType      = 0x00008000u
 };
 
inline Bits_PLLClockMode operator | (Bits_PLLClockMode a,Bits_PLLClockMode b)
 { return Bits_PLLClockMode(uint32(a)|uint32(b)); }
 
enum Field_PLLClockMode_En : uint32
 {
  PLLClockMode_En_MNBypass = 0x04u,
  PLLClockMode_En_LPBypass = 0x05u,
  PLLClockMode_En_FRBypass = 0x06u,
  PLLClockMode_En_Lock     = 0x07u
 };
 
struct PrintField_PLLClockMode_En
 {
  Field_PLLClockMode_En field;

  explicit PrintField_PLLClockMode_En(Field_PLLClockMode_En field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x04u : Putobj(out,"MNBypass"); break;
       case 0x05u : Putobj(out,"LPBypass"); break;
       case 0x06u : Putobj(out,"FRBypass"); break;
       case 0x07u : Putobj(out,"Lock"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_PLLClockMode_En GetTextDesc(Field_PLLClockMode_En field)
 {
  return PrintField_PLLClockMode_En(field);
 }
 
enum Field_PLLClockMode_RampLevel : uint32
 {
  PLLClockMode_RampLevel_No = 0x00u,
  PLLClockMode_RampLevel_Lo = 0x01u,
  PLLClockMode_RampLevel_Hi = 0x02u
 };
 
struct PrintField_PLLClockMode_RampLevel
 {
  Field_PLLClockMode_RampLevel field;

  explicit PrintField_PLLClockMode_RampLevel(Field_PLLClockMode_RampLevel field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"No"); break;
       case 0x01u : Putobj(out,"Lo"); break;
       case 0x02u : Putobj(out,"Hi"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_PLLClockMode_RampLevel GetTextDesc(Field_PLLClockMode_RampLevel field)
 {
  return PrintField_PLLClockMode_RampLevel(field);
 }
 
struct Type_PLLClockMode
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PLLClockMode(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PLLClockMode & setTo(Bar &bar) { bar.set_PLLClockMode(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PLLClockMode & setTo(Bar &bar,AddressType ind) { bar.set_PLLClockMode(ind,*this); return *this; }
 

  template <class T>
  Type_PLLClockMode & set(T to) { to(*this); return *this; }
 

  Type_PLLClockMode & setbit(Bits_PLLClockMode bits) { value|=Type(bits); return *this; }
 
  Type_PLLClockMode & setbitIf(bool cond,Bits_PLLClockMode bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_PLLClockMode & clearbit(Bits_PLLClockMode bits) { value&=~Type(bits); return *this; }
 
  Type_PLLClockMode & clearbitIf(bool cond,Bits_PLLClockMode bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_PLLClockMode bits) const { return value&bits; }
 
  bool testbit(Bits_PLLClockMode bits) const { return (value&bits)==Type(bits); }
 

  Field_PLLClockMode_En get_En() const
   {
    return Field_PLLClockMode_En((value>>0)&0x7u);
   }
 
  Type_PLLClockMode & set_En(Field_PLLClockMode_En field)
   {
    value=((Type(field)&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  Field_PLLClockMode_RampLevel get_RampLevel() const
   {
    return Field_PLLClockMode_RampLevel((value>>3)&0x3u);
   }
 
  Type_PLLClockMode & set_RampLevel(Field_PLLClockMode_RampLevel field)
   {
    value=((Type(field)&0x3u)<<3)|(value&0xFFFFFFE7u);

    return *this;
   }
 

  Type get_RampRate() const
   {
    return (value>>5)&0x7u;
   }
 
  Type_PLLClockMode & set_RampRate(Type field)
   {
    value=((field&0x7u)<<5)|(value&0xFFFFFF1Fu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&PLLClockMode_DriftGuard )
      {
       if( first )
         {
          Putobj(out,"DriftGuard");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DriftGuard");
         }
      }

    if( value&PLLClockMode_RelockRamp )
      {
       if( first )
         {
          Putobj(out,"RelockRamp");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RelockRamp");
         }
      }

    if( value&PLLClockMode_LPMode )
      {
       if( first )
         {
          Putobj(out,"LPMode");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LPMode");
         }
      }

    if( value&PLLClockMode_REGM4X )
      {
       if( first )
         {
          Putobj(out,"REGM4X");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"REGM4X");
         }
      }

    if( value&PLLClockMode_SSC )
      {
       if( first )
         {
          Putobj(out,"SSC");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SSC");
         }
      }

    if( value&PLLClockMode_SSCAck )
      {
       if( first )
         {
          Putobj(out,"SSCAck");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SSCAck");
         }
      }

    if( value&PLLClockMode_SSCLowSpread )
      {
       if( first )
         {
          Putobj(out,"SSCLowSpread");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SSCLowSpread");
         }
      }

    if( value&PLLClockMode_SSCType )
      {
       if( first )
         {
          Putobj(out,"SSCType");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SSCType");
         }
      }

    if( first )
      {
       Printf(out,"En(#;)",get_En());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"En(#;)",get_En());
      }

    if( first )
      {
       Printf(out,"RampLevel(#;)",get_RampLevel());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RampLevel(#;)",get_RampLevel());
      }

    if( first )
      {
       Printf(out,"RampRate(#;)",get_RampRate());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RampRate(#;)",get_RampRate());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_COREDivControl */

enum Bits_COREDivControl : uint32
 {
  COREDivControl_Ack        = 0x00000020u,
  COREDivControl_NoAutoGate = 0x00000100u,
  COREDivControl_Gated      = 0x00000200u,
  COREDivControl_AutoOff    = 0x00001000u
 };
 
inline Bits_COREDivControl operator | (Bits_COREDivControl a,Bits_COREDivControl b)
 { return Bits_COREDivControl(uint32(a)|uint32(b)); }
 
struct Type_COREDivControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_COREDivControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_COREDivControl & setTo(Bar &bar) { bar.set_COREDivControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_COREDivControl & setTo(Bar &bar,AddressType ind) { bar.set_COREDivControl(ind,*this); return *this; }
 

  template <class T>
  Type_COREDivControl & set(T to) { to(*this); return *this; }
 

  Type_COREDivControl & setbit(Bits_COREDivControl bits) { value|=Type(bits); return *this; }
 
  Type_COREDivControl & setbitIf(bool cond,Bits_COREDivControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_COREDivControl & clearbit(Bits_COREDivControl bits) { value&=~Type(bits); return *this; }
 
  Type_COREDivControl & clearbitIf(bool cond,Bits_COREDivControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_COREDivControl bits) const { return value&bits; }
 
  bool testbit(Bits_COREDivControl bits) const { return (value&bits)==Type(bits); }
 

  Type get_Div() const
   {
    return (value>>0)&0x1Fu;
   }
 
  Type_COREDivControl & set_Div(Type field)
   {
    value=((field&0x1Fu)<<0)|(value&0xFFFFFFE0u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&COREDivControl_Ack )
      {
       if( first )
         {
          Putobj(out,"Ack");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Ack");
         }
      }

    if( value&COREDivControl_NoAutoGate )
      {
       if( first )
         {
          Putobj(out,"NoAutoGate");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NoAutoGate");
         }
      }

    if( value&COREDivControl_Gated )
      {
       if( first )
         {
          Putobj(out,"Gated");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Gated");
         }
      }

    if( value&COREDivControl_AutoOff )
      {
       if( first )
         {
          Putobj(out,"AutoOff");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AutoOff");
         }
      }

    if( first )
      {
       Printf(out,"Div(#;)",get_Div());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Div(#;)",get_Div());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct PERBar<RW> */

template <class RW>
struct PERBar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit PERBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- ClockControl

  static Type_ClockControl null_ClockControl() { return Type_ClockControl(0); }
 
  static Type_ClockControl ones_ClockControl() { return Type_ClockControl(Type_ClockControl::Type(-1)); }
 
  //--- ClockStandbyControl

  static Type_ClockStandbyControl null_ClockStandbyControl() { return Type_ClockStandbyControl(0); }
 
  static Type_ClockStandbyControl ones_ClockStandbyControl() { return Type_ClockStandbyControl(Type_ClockStandbyControl::Type(-1)); }
 
  //--- Eth

  Type_ClockStandbyControl get_Eth() { return Type_ClockStandbyControl(rw.template get<uint32>(0x14u)); }
 
  void set_Eth(Type_ClockStandbyControl value) { rw.set(0x14u,value.value); }
 
  Setter<Type_ClockStandbyControl> to_Eth() { return Setter<Type_ClockStandbyControl>(rw,0x14u); }
 
  //--- EthClockControl

  Type_EthClockControl get_EthClockControl() { return Type_EthClockControl(rw.template get<uint32>(0x144u)); }
 
  void set_EthClockControl(Type_EthClockControl value) { rw.set(0x144u,value.value); }
 
  Setter<Type_EthClockControl> to_EthClockControl() { return Setter<Type_EthClockControl>(rw,0x144u); }
 
  static Type_EthClockControl null_EthClockControl() { return Type_EthClockControl(0); }
 
  static Type_EthClockControl ones_EthClockControl() { return Type_EthClockControl(Type_EthClockControl::Type(-1)); }
 
  //--- Timer2

  Type_ClockControl get_Timer2() { return Type_ClockControl(rw.template get<uint32>(0x80u)); }
 
  void set_Timer2(Type_ClockControl value) { rw.set(0x80u,value.value); }
 
  Setter<Type_ClockControl> to_Timer2() { return Setter<Type_ClockControl>(rw,0x80u); }
 
  //--- Timer4

  Type_ClockControl get_Timer4() { return Type_ClockControl(rw.template get<uint32>(0x88u)); }
 
  void set_Timer4(Type_ClockControl value) { rw.set(0x88u,value.value); }
 
  Setter<Type_ClockControl> to_Timer4() { return Setter<Type_ClockControl>(rw,0x88u); }
 
  //--- I2C1

  Type_ClockControl get_I2C1() { return Type_ClockControl(rw.template get<uint32>(0x48u)); }
 
  void set_I2C1(Type_ClockControl value) { rw.set(0x48u,value.value); }
 
  Setter<Type_ClockControl> to_I2C1() { return Setter<Type_ClockControl>(rw,0x48u); }
 
  //--- I2C2

  Type_ClockControl get_I2C2() { return Type_ClockControl(rw.template get<uint32>(0x44u)); }
 
  void set_I2C2(Type_ClockControl value) { rw.set(0x44u,value.value); }
 
  Setter<Type_ClockControl> to_I2C2() { return Setter<Type_ClockControl>(rw,0x44u); }
 
  //--- LCD

  Type_ClockStandbyControl get_LCD() { return Type_ClockStandbyControl(rw.template get<uint32>(0x18u)); }
 
  void set_LCD(Type_ClockStandbyControl value) { rw.set(0x18u,value.value); }
 
  Setter<Type_ClockStandbyControl> to_LCD() { return Setter<Type_ClockStandbyControl>(rw,0x18u); }
 
 };
 
/* struct DPLLBar<RW> */

template <class RW>
struct DPLLBar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit DPLLBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- TimerClockSelect

  static Type_TimerClockSelect null_TimerClockSelect() { return Type_TimerClockSelect(0); }
 
  static Type_TimerClockSelect ones_TimerClockSelect() { return Type_TimerClockSelect(Type_TimerClockSelect::Type(-1)); }
 
  //--- Timer2

  Type_TimerClockSelect get_Timer2() { return Type_TimerClockSelect(rw.template get<uint32>(0x8u)); }
 
  void set_Timer2(Type_TimerClockSelect value) { rw.set(0x8u,value.value); }
 
  Setter<Type_TimerClockSelect> to_Timer2() { return Setter<Type_TimerClockSelect>(rw,0x8u); }
 
  //--- Timer4

  Type_TimerClockSelect get_Timer4() { return Type_TimerClockSelect(rw.template get<uint32>(0x10u)); }
 
  void set_Timer4(Type_TimerClockSelect value) { rw.set(0x10u,value.value); }
 
  Setter<Type_TimerClockSelect> to_Timer4() { return Setter<Type_TimerClockSelect>(rw,0x10u); }
 
  //--- LCDClockSelect

  Type_LCDClockSelect get_LCDClockSelect() { return Type_LCDClockSelect(rw.template get<uint32>(0x34u)); }
 
  void set_LCDClockSelect(Type_LCDClockSelect value) { rw.set(0x34u,value.value); }
 
  Setter<Type_LCDClockSelect> to_LCDClockSelect() { return Setter<Type_LCDClockSelect>(rw,0x34u); }
 
  static Type_LCDClockSelect null_LCDClockSelect() { return Type_LCDClockSelect(0); }
 
  static Type_LCDClockSelect ones_LCDClockSelect() { return Type_LCDClockSelect(Type_LCDClockSelect::Type(-1)); }
 
  //--- CPTSClockSelect

  Type_CPTSClockSelect get_CPTSClockSelect() { return Type_CPTSClockSelect(rw.template get<uint32>(0x20u)); }
 
  void set_CPTSClockSelect(Type_CPTSClockSelect value) { rw.set(0x20u,value.value); }
 
  Setter<Type_CPTSClockSelect> to_CPTSClockSelect() { return Setter<Type_CPTSClockSelect>(rw,0x20u); }
 
  static Type_CPTSClockSelect null_CPTSClockSelect() { return Type_CPTSClockSelect(0); }
 
  static Type_CPTSClockSelect ones_CPTSClockSelect() { return Type_CPTSClockSelect(Type_CPTSClockSelect::Type(-1)); }
 
 };
 
/* struct WKUPBar<RW> */

template <class RW>
struct WKUPBar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit WKUPBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- ClockControl

  static Type_ClockControl null_ClockControl() { return Type_ClockControl(0); }
 
  static Type_ClockControl ones_ClockControl() { return Type_ClockControl(Type_ClockControl::Type(-1)); }
 
  //--- I2C0

  Type_ClockControl get_I2C0() { return Type_ClockControl(rw.template get<uint32>(0xB8u)); }
 
  void set_I2C0(Type_ClockControl value) { rw.set(0xB8u,value.value); }
 
  Setter<Type_ClockControl> to_I2C0() { return Setter<Type_ClockControl>(rw,0xB8u); }
 
  //--- PLLIdleStatus

  static Type_PLLIdleStatus null_PLLIdleStatus() { return Type_PLLIdleStatus(0); }
 
  static Type_PLLIdleStatus ones_PLLIdleStatus() { return Type_PLLIdleStatus(Type_PLLIdleStatus::Type(-1)); }
 
  //--- PLLClockSelect

  static Type_PLLClockSelect null_PLLClockSelect() { return Type_PLLClockSelect(0); }
 
  static Type_PLLClockSelect ones_PLLClockSelect() { return Type_PLLClockSelect(Type_PLLClockSelect::Type(-1)); }
 
  //--- PLLDivM2

  static Type_PLLDivM2 null_PLLDivM2() { return Type_PLLDivM2(0); }
 
  static Type_PLLDivM2 ones_PLLDivM2() { return Type_PLLDivM2(Type_PLLDivM2::Type(-1)); }
 
  //--- PLLClockMode

  static Type_PLLClockMode null_PLLClockMode() { return Type_PLLClockMode(0); }
 
  static Type_PLLClockMode ones_PLLClockMode() { return Type_PLLClockMode(Type_PLLClockMode::Type(-1)); }
 
  //--- COREDivControl

  static Type_COREDivControl null_COREDivControl() { return Type_COREDivControl(0); }
 
  static Type_COREDivControl ones_COREDivControl() { return Type_COREDivControl(Type_COREDivControl::Type(-1)); }
 
  //--- MPUIdleStatus

  Type_PLLIdleStatus get_MPUIdleStatus() { return Type_PLLIdleStatus(rw.template get<uint32>(0x20u)); }
 
  //--- MPUClockSelect

  Type_PLLClockSelect get_MPUClockSelect() { return Type_PLLClockSelect(rw.template get<uint32>(0x2Cu)); }
 
  void set_MPUClockSelect(Type_PLLClockSelect value) { rw.set(0x2Cu,value.value); }
 
  Setter<Type_PLLClockSelect> to_MPUClockSelect() { return Setter<Type_PLLClockSelect>(rw,0x2Cu); }
 
  //--- MPUDivM2

  Type_PLLDivM2 get_MPUDivM2() { return Type_PLLDivM2(rw.template get<uint32>(0xA8u)); }
 
  void set_MPUDivM2(Type_PLLDivM2 value) { rw.set(0xA8u,value.value); }
 
  Setter<Type_PLLDivM2> to_MPUDivM2() { return Setter<Type_PLLDivM2>(rw,0xA8u); }
 
  //--- MPUClockMode

  Type_PLLClockMode get_MPUClockMode() { return Type_PLLClockMode(rw.template get<uint32>(0x88u)); }
 
  void set_MPUClockMode(Type_PLLClockMode value) { rw.set(0x88u,value.value); }
 
  Setter<Type_PLLClockMode> to_MPUClockMode() { return Setter<Type_PLLClockMode>(rw,0x88u); }
 
  //--- DISPIdleStatus

  Type_PLLIdleStatus get_DISPIdleStatus() { return Type_PLLIdleStatus(rw.template get<uint32>(0x48u)); }
 
  //--- DISPClockSelect

  Type_PLLClockSelect get_DISPClockSelect() { return Type_PLLClockSelect(rw.template get<uint32>(0x54u)); }
 
  void set_DISPClockSelect(Type_PLLClockSelect value) { rw.set(0x54u,value.value); }
 
  Setter<Type_PLLClockSelect> to_DISPClockSelect() { return Setter<Type_PLLClockSelect>(rw,0x54u); }
 
  //--- DISPDivM2

  Type_PLLDivM2 get_DISPDivM2() { return Type_PLLDivM2(rw.template get<uint32>(0xA4u)); }
 
  void set_DISPDivM2(Type_PLLDivM2 value) { rw.set(0xA4u,value.value); }
 
  Setter<Type_PLLDivM2> to_DISPDivM2() { return Setter<Type_PLLDivM2>(rw,0xA4u); }
 
  //--- DISPClockMode

  Type_PLLClockMode get_DISPClockMode() { return Type_PLLClockMode(rw.template get<uint32>(0x98u)); }
 
  void set_DISPClockMode(Type_PLLClockMode value) { rw.set(0x98u,value.value); }
 
  Setter<Type_PLLClockMode> to_DISPClockMode() { return Setter<Type_PLLClockMode>(rw,0x98u); }
 
  //--- COREIdleStatus

  Type_PLLIdleStatus get_COREIdleStatus() { return Type_PLLIdleStatus(rw.template get<uint32>(0x5Cu)); }
 
  //--- COREClockSelect

  Type_PLLClockSelect get_COREClockSelect() { return Type_PLLClockSelect(rw.template get<uint32>(0x68u)); }
 
  void set_COREClockSelect(Type_PLLClockSelect value) { rw.set(0x68u,value.value); }
 
  Setter<Type_PLLClockSelect> to_COREClockSelect() { return Setter<Type_PLLClockSelect>(rw,0x68u); }
 
  //--- COREClockMode

  Type_PLLClockMode get_COREClockMode() { return Type_PLLClockMode(rw.template get<uint32>(0x90u)); }
 
  void set_COREClockMode(Type_PLLClockMode value) { rw.set(0x90u,value.value); }
 
  Setter<Type_PLLClockMode> to_COREClockMode() { return Setter<Type_PLLClockMode>(rw,0x90u); }
 
  //--- CORE_M4Div

  Type_COREDivControl get_CORE_M4Div() { return Type_COREDivControl(rw.template get<uint32>(0x80u)); }
 
  void set_CORE_M4Div(Type_COREDivControl value) { rw.set(0x80u,value.value); }
 
  Setter<Type_COREDivControl> to_CORE_M4Div() { return Setter<Type_COREDivControl>(rw,0x80u); }
 
  //--- CORE_M5Div

  Type_COREDivControl get_CORE_M5Div() { return Type_COREDivControl(rw.template get<uint32>(0x84u)); }
 
  void set_CORE_M5Div(Type_COREDivControl value) { rw.set(0x84u,value.value); }
 
  Setter<Type_COREDivControl> to_CORE_M5Div() { return Setter<Type_COREDivControl>(rw,0x84u); }
 
  //--- CORE_M6Div

  Type_COREDivControl get_CORE_M6Div() { return Type_COREDivControl(rw.template get<uint32>(0xD8u)); }
 
  void set_CORE_M6Div(Type_COREDivControl value) { rw.set(0xD8u,value.value); }
 
  Setter<Type_COREDivControl> to_CORE_M6Div() { return Setter<Type_COREDivControl>(rw,0xD8u); }
 
 };
 
