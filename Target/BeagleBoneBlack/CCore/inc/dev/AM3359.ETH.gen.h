/* AM3359.ETH.gen.h */

/* struct Type_SwitchControl */

enum Bits_SwitchControl : uint32
 {
  SwitchControl_FIFOLoopback = 0x00000001u,
  SwitchControl_VLANAware    = 0x00000002u,
  SwitchControl_Port0VLAN    = 0x00000004u,
  SwitchControl_DLREnable    = 0x00000008u
 };
 
inline Bits_SwitchControl operator | (Bits_SwitchControl a,Bits_SwitchControl b)
 { return Bits_SwitchControl(uint32(a)|uint32(b)); }
 
struct Type_SwitchControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SwitchControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchControl & setTo(Bar &bar) { bar.set_SwitchControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SwitchControl & setTo(Bar &bar,AddressType ind) { bar.set_SwitchControl(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchControl & set(T to) { to(*this); return *this; }
 

  Type_SwitchControl & setbit(Bits_SwitchControl bits) { value|=Type(bits); return *this; }
 
  Type_SwitchControl & setbitIf(bool cond,Bits_SwitchControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SwitchControl & clearbit(Bits_SwitchControl bits) { value&=~Type(bits); return *this; }
 
  Type_SwitchControl & clearbitIf(bool cond,Bits_SwitchControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SwitchControl bits) const { return value&bits; }
 
  bool testbit(Bits_SwitchControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SwitchControl_FIFOLoopback )
      {
       if( first )
         {
          Putobj(out,"FIFOLoopback");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FIFOLoopback");
         }
      }

    if( value&SwitchControl_VLANAware )
      {
       if( first )
         {
          Putobj(out,"VLANAware");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VLANAware");
         }
      }

    if( value&SwitchControl_Port0VLAN )
      {
       if( first )
         {
          Putobj(out,"Port0VLAN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port0VLAN");
         }
      }

    if( value&SwitchControl_DLREnable )
      {
       if( first )
         {
          Putobj(out,"DLREnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DLREnable");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchSoftReset */

enum Bits_SwitchSoftReset : uint32
 {
  SwitchSoftReset_Reset = 0x00000001u
 };
 
inline Bits_SwitchSoftReset operator | (Bits_SwitchSoftReset a,Bits_SwitchSoftReset b)
 { return Bits_SwitchSoftReset(uint32(a)|uint32(b)); }
 
struct Type_SwitchSoftReset
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SwitchSoftReset(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchSoftReset & setTo(Bar &bar) { bar.set_SwitchSoftReset(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SwitchSoftReset & setTo(Bar &bar,AddressType ind) { bar.set_SwitchSoftReset(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchSoftReset & set(T to) { to(*this); return *this; }
 

  Type_SwitchSoftReset & setbit(Bits_SwitchSoftReset bits) { value|=Type(bits); return *this; }
 
  Type_SwitchSoftReset & setbitIf(bool cond,Bits_SwitchSoftReset bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SwitchSoftReset & clearbit(Bits_SwitchSoftReset bits) { value&=~Type(bits); return *this; }
 
  Type_SwitchSoftReset & clearbitIf(bool cond,Bits_SwitchSoftReset bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SwitchSoftReset bits) const { return value&bits; }
 
  bool testbit(Bits_SwitchSoftReset bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SwitchSoftReset_Reset )
      {
       if( first )
         {
          Putobj(out,"Reset");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Reset");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchStatPort */

enum Bits_SwitchStatPort : uint32
 {
  SwitchStatPort_Port0Enable = 0x00000001u,
  SwitchStatPort_Port1Enable = 0x00000002u,
  SwitchStatPort_Port2Enable = 0x00000004u
 };
 
inline Bits_SwitchStatPort operator | (Bits_SwitchStatPort a,Bits_SwitchStatPort b)
 { return Bits_SwitchStatPort(uint32(a)|uint32(b)); }
 
struct Type_SwitchStatPort
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SwitchStatPort(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchStatPort & setTo(Bar &bar) { bar.set_SwitchStatPort(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SwitchStatPort & setTo(Bar &bar,AddressType ind) { bar.set_SwitchStatPort(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchStatPort & set(T to) { to(*this); return *this; }
 

  Type_SwitchStatPort & setbit(Bits_SwitchStatPort bits) { value|=Type(bits); return *this; }
 
  Type_SwitchStatPort & setbitIf(bool cond,Bits_SwitchStatPort bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SwitchStatPort & clearbit(Bits_SwitchStatPort bits) { value&=~Type(bits); return *this; }
 
  Type_SwitchStatPort & clearbitIf(bool cond,Bits_SwitchStatPort bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SwitchStatPort bits) const { return value&bits; }
 
  bool testbit(Bits_SwitchStatPort bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SwitchStatPort_Port0Enable )
      {
       if( first )
         {
          Putobj(out,"Port0Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port0Enable");
         }
      }

    if( value&SwitchStatPort_Port1Enable )
      {
       if( first )
         {
          Putobj(out,"Port1Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port1Enable");
         }
      }

    if( value&SwitchStatPort_Port2Enable )
      {
       if( first )
         {
          Putobj(out,"Port2Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port2Enable");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchTxPriType */

enum Bits_SwitchTxPriType : uint32
 {
  SwitchTxPriType_Port0Escalate  = 0x00000100u,
  SwitchTxPriType_Port1Escalate  = 0x00000200u,
  SwitchTxPriType_Port2Escalate  = 0x00000400u,
  SwitchTxPriType_Port1Pri1Shape = 0x00010000u,
  SwitchTxPriType_Port1Pri2Shape = 0x00020000u,
  SwitchTxPriType_Port1Pri3Shape = 0x00040000u,
  SwitchTxPriType_Port2Pri1Shape = 0x00080000u,
  SwitchTxPriType_Port2Pri2Shape = 0x00100000u,
  SwitchTxPriType_Port2Pri3Shape = 0x00200000u
 };
 
inline Bits_SwitchTxPriType operator | (Bits_SwitchTxPriType a,Bits_SwitchTxPriType b)
 { return Bits_SwitchTxPriType(uint32(a)|uint32(b)); }
 
struct Type_SwitchTxPriType
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SwitchTxPriType(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchTxPriType & setTo(Bar &bar) { bar.set_SwitchTxPriType(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SwitchTxPriType & setTo(Bar &bar,AddressType ind) { bar.set_SwitchTxPriType(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchTxPriType & set(T to) { to(*this); return *this; }
 

  Type_SwitchTxPriType & setbit(Bits_SwitchTxPriType bits) { value|=Type(bits); return *this; }
 
  Type_SwitchTxPriType & setbitIf(bool cond,Bits_SwitchTxPriType bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SwitchTxPriType & clearbit(Bits_SwitchTxPriType bits) { value&=~Type(bits); return *this; }
 
  Type_SwitchTxPriType & clearbitIf(bool cond,Bits_SwitchTxPriType bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SwitchTxPriType bits) const { return value&bits; }
 
  bool testbit(Bits_SwitchTxPriType bits) const { return (value&bits)==Type(bits); }
 

  Type get_EscalateCount() const
   {
    return (value>>0)&0x1Fu;
   }
 
  Type_SwitchTxPriType & set_EscalateCount(Type field)
   {
    value=((field&0x1Fu)<<0)|(value&0xFFFFFFE0u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SwitchTxPriType_Port0Escalate )
      {
       if( first )
         {
          Putobj(out,"Port0Escalate");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port0Escalate");
         }
      }

    if( value&SwitchTxPriType_Port1Escalate )
      {
       if( first )
         {
          Putobj(out,"Port1Escalate");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port1Escalate");
         }
      }

    if( value&SwitchTxPriType_Port2Escalate )
      {
       if( first )
         {
          Putobj(out,"Port2Escalate");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port2Escalate");
         }
      }

    if( value&SwitchTxPriType_Port1Pri1Shape )
      {
       if( first )
         {
          Putobj(out,"Port1Pri1Shape");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port1Pri1Shape");
         }
      }

    if( value&SwitchTxPriType_Port1Pri2Shape )
      {
       if( first )
         {
          Putobj(out,"Port1Pri2Shape");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port1Pri2Shape");
         }
      }

    if( value&SwitchTxPriType_Port1Pri3Shape )
      {
       if( first )
         {
          Putobj(out,"Port1Pri3Shape");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port1Pri3Shape");
         }
      }

    if( value&SwitchTxPriType_Port2Pri1Shape )
      {
       if( first )
         {
          Putobj(out,"Port2Pri1Shape");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port2Pri1Shape");
         }
      }

    if( value&SwitchTxPriType_Port2Pri2Shape )
      {
       if( first )
         {
          Putobj(out,"Port2Pri2Shape");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port2Pri2Shape");
         }
      }

    if( value&SwitchTxPriType_Port2Pri3Shape )
      {
       if( first )
         {
          Putobj(out,"Port2Pri3Shape");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port2Pri3Shape");
         }
      }

    if( first )
      {
       Printf(out,"EscalateCount(#;)",get_EscalateCount());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"EscalateCount(#;)",get_EscalateCount());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchCmdIdle */

enum Bits_SwitchCmdIdle : uint32
 {
  SwitchCmdIdle_CmdIdle = 0x00000001u
 };
 
inline Bits_SwitchCmdIdle operator | (Bits_SwitchCmdIdle a,Bits_SwitchCmdIdle b)
 { return Bits_SwitchCmdIdle(uint32(a)|uint32(b)); }
 
struct Type_SwitchCmdIdle
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SwitchCmdIdle(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchCmdIdle & setTo(Bar &bar) { bar.set_SwitchCmdIdle(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SwitchCmdIdle & setTo(Bar &bar,AddressType ind) { bar.set_SwitchCmdIdle(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchCmdIdle & set(T to) { to(*this); return *this; }
 

  Type_SwitchCmdIdle & setbit(Bits_SwitchCmdIdle bits) { value|=Type(bits); return *this; }
 
  Type_SwitchCmdIdle & setbitIf(bool cond,Bits_SwitchCmdIdle bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SwitchCmdIdle & clearbit(Bits_SwitchCmdIdle bits) { value&=~Type(bits); return *this; }
 
  Type_SwitchCmdIdle & clearbitIf(bool cond,Bits_SwitchCmdIdle bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SwitchCmdIdle bits) const { return value&bits; }
 
  bool testbit(Bits_SwitchCmdIdle bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SwitchCmdIdle_CmdIdle )
      {
       if( first )
         {
          Putobj(out,"CmdIdle");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CmdIdle");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchRate */

struct Type_SwitchRate
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SwitchRate(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchRate & setTo(Bar &bar) { bar.set_SwitchRate(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SwitchRate & setTo(Bar &bar,AddressType ind) { bar.set_SwitchRate(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchRate & set(T to) { to(*this); return *this; }
 

  Type get_Host() const
   {
    return (value>>0)&0xFu;
   }
 
  Type_SwitchRate & set_Host(Type field)
   {
    value=((field&0xFu)<<0)|(value&0xFFFFFFF0u);

    return *this;
   }
 

  Type get_Sliver() const
   {
    return (value>>12)&0xFu;
   }
 
  Type_SwitchRate & set_Sliver(Type field)
   {
    value=((field&0xFu)<<12)|(value&0xFFFF0FFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Host(#;)",get_Host());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Host(#;)",get_Host());
      }

    if( first )
      {
       Printf(out,"Sliver(#;)",get_Sliver());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Sliver(#;)",get_Sliver());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchTxShortGap */

struct Type_SwitchTxShortGap
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SwitchTxShortGap(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchTxShortGap & setTo(Bar &bar) { bar.set_SwitchTxShortGap(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SwitchTxShortGap & setTo(Bar &bar,AddressType ind) { bar.set_SwitchTxShortGap(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchTxShortGap & set(T to) { to(*this); return *this; }
 

  Type get_Thresh() const
   {
    return (value>>0)&0x1Fu;
   }
 
  Type_SwitchTxShortGap & set_Thresh(Type field)
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
       Printf(out,"Thresh(#;)",get_Thresh());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Thresh(#;)",get_Thresh());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchTxStart */

struct Type_SwitchTxStart
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SwitchTxStart(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchTxStart & setTo(Bar &bar) { bar.set_SwitchTxStart(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SwitchTxStart & setTo(Bar &bar,AddressType ind) { bar.set_SwitchTxStart(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchTxStart & set(T to) { to(*this); return *this; }
 

  Type get_Len() const
   {
    return (value>>0)&0x7FFu;
   }
 
  Type_SwitchTxStart & set_Len(Type field)
   {
    value=((field&0x7FFu)<<0)|(value&0xFFFFF800u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Len(#;)",get_Len());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Len(#;)",get_Len());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchRxFlowControl */

enum Bits_SwitchRxFlowControl : uint32
 {
  SwitchRxFlowControl_Port0Enable = 0x00000001u,
  SwitchRxFlowControl_Port1Enable = 0x00000002u,
  SwitchRxFlowControl_Port2Enable = 0x00000004u
 };
 
inline Bits_SwitchRxFlowControl operator | (Bits_SwitchRxFlowControl a,Bits_SwitchRxFlowControl b)
 { return Bits_SwitchRxFlowControl(uint32(a)|uint32(b)); }
 
struct Type_SwitchRxFlowControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SwitchRxFlowControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchRxFlowControl & setTo(Bar &bar) { bar.set_SwitchRxFlowControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SwitchRxFlowControl & setTo(Bar &bar,AddressType ind) { bar.set_SwitchRxFlowControl(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchRxFlowControl & set(T to) { to(*this); return *this; }
 

  Type_SwitchRxFlowControl & setbit(Bits_SwitchRxFlowControl bits) { value|=Type(bits); return *this; }
 
  Type_SwitchRxFlowControl & setbitIf(bool cond,Bits_SwitchRxFlowControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SwitchRxFlowControl & clearbit(Bits_SwitchRxFlowControl bits) { value&=~Type(bits); return *this; }
 
  Type_SwitchRxFlowControl & clearbitIf(bool cond,Bits_SwitchRxFlowControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SwitchRxFlowControl bits) const { return value&bits; }
 
  bool testbit(Bits_SwitchRxFlowControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SwitchRxFlowControl_Port0Enable )
      {
       if( first )
         {
          Putobj(out,"Port0Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port0Enable");
         }
      }

    if( value&SwitchRxFlowControl_Port1Enable )
      {
       if( first )
         {
          Putobj(out,"Port1Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port1Enable");
         }
      }

    if( value&SwitchRxFlowControl_Port2Enable )
      {
       if( first )
         {
          Putobj(out,"Port2Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port2Enable");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchLType */

struct Type_SwitchLType
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SwitchLType(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchLType & setTo(Bar &bar) { bar.set_SwitchLType(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SwitchLType & setTo(Bar &bar,AddressType ind) { bar.set_SwitchLType(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchLType & set(T to) { to(*this); return *this; }
 

  Type get_LType1() const
   {
    return (value>>0)&0xFFFFu;
   }
 
  Type_SwitchLType & set_LType1(Type field)
   {
    value=((field&0xFFFFu)<<0)|(value&0xFFFF0000u);

    return *this;
   }
 

  Type get_LType2() const
   {
    return (value>>16)&0xFFFFu;
   }
 
  Type_SwitchLType & set_LType2(Type field)
   {
    value=((field&0xFFFFu)<<16)|(value&0xFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"LType1(#;)",get_LType1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"LType1(#;)",get_LType1());
      }

    if( first )
      {
       Printf(out,"LType2(#;)",get_LType2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"LType2(#;)",get_LType2());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchTSLType */

struct Type_SwitchTSLType
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SwitchTSLType(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchTSLType & setTo(Bar &bar) { bar.set_SwitchTSLType(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SwitchTSLType & setTo(Bar &bar,AddressType ind) { bar.set_SwitchTSLType(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchTSLType & set(T to) { to(*this); return *this; }
 

  Type get_LType1() const
   {
    return (value>>0)&0xFFFFu;
   }
 
  Type_SwitchTSLType & set_LType1(Type field)
   {
    value=((field&0xFFFFu)<<0)|(value&0xFFFF0000u);

    return *this;
   }
 

  Type get_LType2() const
   {
    return (value>>16)&0x3Fu;
   }
 
  Type_SwitchTSLType & set_LType2(Type field)
   {
    value=((field&0x3Fu)<<16)|(value&0xFFC0FFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"LType1(#;)",get_LType1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"LType1(#;)",get_LType1());
      }

    if( first )
      {
       Printf(out,"LType2(#;)",get_LType2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"LType2(#;)",get_LType2());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchDLRLType */

struct Type_SwitchDLRLType
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SwitchDLRLType(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchDLRLType & setTo(Bar &bar) { bar.set_SwitchDLRLType(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SwitchDLRLType & setTo(Bar &bar,AddressType ind) { bar.set_SwitchDLRLType(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchDLRLType & set(T to) { to(*this); return *this; }
 

  Type get_LType() const
   {
    return (value>>0)&0xFFFFu;
   }
 
  Type_SwitchDLRLType & set_LType(Type field)
   {
    value=((field&0xFFFFu)<<0)|(value&0xFFFF0000u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"LType(#;)",get_LType());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"LType(#;)",get_LType());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortControl */

enum Bits_PortControl : uint32
 {
  PortControl_RxTimeSyncEnable     = 0x00000001u,
  PortControl_TxTimeSyncEnable     = 0x00000002u,
  PortControl_LType1TimeSyncEnable = 0x00000004u,
  PortControl_LType2TimeSyncEnable = 0x00000008u,
  PortControl_AnnexDTimeSyncEnable = 0x00000010u,
  PortControl_TTLTimeSyncEnable    = 0x00000100u,
  PortControl_UDP129TimeSyncEnable = 0x00000200u,
  PortControl_UDP130TimeSyncEnable = 0x00000400u,
  PortControl_UDP131TimeSyncEnable = 0x00000800u,
  PortControl_UDP132TimeSyncEnable = 0x00001000u,
  PortControl_UDP319TimeSyncEnable = 0x00002000u,
  PortControl_UDP320TimeSyncEnable = 0x00004000u,
  PortControl_TOSPriEnable         = 0x00010000u,
  PortControl_VLAN_LType1Enable    = 0x00100000u,
  PortControl_VLAN_LType2Enable    = 0x00200000u,
  PortControl_VLAN_PassPri         = 0x01000000u
 };
 
inline Bits_PortControl operator | (Bits_PortControl a,Bits_PortControl b)
 { return Bits_PortControl(uint32(a)|uint32(b)); }
 
struct Type_PortControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortControl & setTo(Bar &bar) { bar.set_PortControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortControl & setTo(Bar &bar,AddressType ind) { bar.set_PortControl(ind,*this); return *this; }
 

  template <class T>
  Type_PortControl & set(T to) { to(*this); return *this; }
 

  Type_PortControl & setbit(Bits_PortControl bits) { value|=Type(bits); return *this; }
 
  Type_PortControl & setbitIf(bool cond,Bits_PortControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_PortControl & clearbit(Bits_PortControl bits) { value&=~Type(bits); return *this; }
 
  Type_PortControl & clearbitIf(bool cond,Bits_PortControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_PortControl bits) const { return value&bits; }
 
  bool testbit(Bits_PortControl bits) const { return (value&bits)==Type(bits); }
 

  Type get_DLRChan() const
   {
    return (value>>28)&0x7u;
   }
 
  Type_PortControl & set_DLRChan(Type field)
   {
    value=((field&0x7u)<<28)|(value&0x8FFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&PortControl_RxTimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"RxTimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxTimeSyncEnable");
         }
      }

    if( value&PortControl_TxTimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"TxTimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TxTimeSyncEnable");
         }
      }

    if( value&PortControl_LType1TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"LType1TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LType1TimeSyncEnable");
         }
      }

    if( value&PortControl_LType2TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"LType2TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LType2TimeSyncEnable");
         }
      }

    if( value&PortControl_AnnexDTimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"AnnexDTimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AnnexDTimeSyncEnable");
         }
      }

    if( value&PortControl_TTLTimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"TTLTimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TTLTimeSyncEnable");
         }
      }

    if( value&PortControl_UDP129TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"UDP129TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDP129TimeSyncEnable");
         }
      }

    if( value&PortControl_UDP130TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"UDP130TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDP130TimeSyncEnable");
         }
      }

    if( value&PortControl_UDP131TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"UDP131TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDP131TimeSyncEnable");
         }
      }

    if( value&PortControl_UDP132TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"UDP132TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDP132TimeSyncEnable");
         }
      }

    if( value&PortControl_UDP319TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"UDP319TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDP319TimeSyncEnable");
         }
      }

    if( value&PortControl_UDP320TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"UDP320TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDP320TimeSyncEnable");
         }
      }

    if( value&PortControl_TOSPriEnable )
      {
       if( first )
         {
          Putobj(out,"TOSPriEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TOSPriEnable");
         }
      }

    if( value&PortControl_VLAN_LType1Enable )
      {
       if( first )
         {
          Putobj(out,"VLAN_LType1Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VLAN_LType1Enable");
         }
      }

    if( value&PortControl_VLAN_LType2Enable )
      {
       if( first )
         {
          Putobj(out,"VLAN_LType2Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VLAN_LType2Enable");
         }
      }

    if( value&PortControl_VLAN_PassPri )
      {
       if( first )
         {
          Putobj(out,"VLAN_PassPri");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VLAN_PassPri");
         }
      }

    if( first )
      {
       Printf(out,"DLRChan(#;)",get_DLRChan());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"DLRChan(#;)",get_DLRChan());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortFIFOLen */

enum Field_PortFIFOLen_RxLen : uint32
 {
  PortFIFOLen_RxLen_Default0 = 0x04u,
  PortFIFOLen_RxLen_Default  = 0x03u
 };
 
struct PrintField_PortFIFOLen_RxLen
 {
  Field_PortFIFOLen_RxLen field;

  explicit PrintField_PortFIFOLen_RxLen(Field_PortFIFOLen_RxLen field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x04u : Putobj(out,"Default0"); break;
       case 0x03u : Putobj(out,"Default"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_PortFIFOLen_RxLen GetTextDesc(Field_PortFIFOLen_RxLen field)
 {
  return PrintField_PortFIFOLen_RxLen(field);
 }
 
enum Field_PortFIFOLen_TxLen : uint32
 {
  PortFIFOLen_TxLen_Default0 = 0x10u,
  PortFIFOLen_TxLen_Default  = 0x11u
 };
 
struct PrintField_PortFIFOLen_TxLen
 {
  Field_PortFIFOLen_TxLen field;

  explicit PrintField_PortFIFOLen_TxLen(Field_PortFIFOLen_TxLen field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x10u : Putobj(out,"Default0"); break;
       case 0x11u : Putobj(out,"Default"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_PortFIFOLen_TxLen GetTextDesc(Field_PortFIFOLen_TxLen field)
 {
  return PrintField_PortFIFOLen_TxLen(field);
 }
 
struct Type_PortFIFOLen
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortFIFOLen(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortFIFOLen & setTo(Bar &bar) { bar.set_PortFIFOLen(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortFIFOLen & setTo(Bar &bar,AddressType ind) { bar.set_PortFIFOLen(ind,*this); return *this; }
 

  template <class T>
  Type_PortFIFOLen & set(T to) { to(*this); return *this; }
 

  Field_PortFIFOLen_RxLen get_RxLen() const
   {
    return Field_PortFIFOLen_RxLen((value>>0)&0xFu);
   }
 
  Type_PortFIFOLen & set_RxLen(Field_PortFIFOLen_RxLen field)
   {
    value=((Type(field)&0xFu)<<0)|(value&0xFFFFFFF0u);

    return *this;
   }
 

  Field_PortFIFOLen_TxLen get_TxLen() const
   {
    return Field_PortFIFOLen_TxLen((value>>4)&0x1Fu);
   }
 
  Type_PortFIFOLen & set_TxLen(Field_PortFIFOLen_TxLen field)
   {
    value=((Type(field)&0x1Fu)<<4)|(value&0xFFFFFE0Fu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"RxLen(#;)",get_RxLen());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RxLen(#;)",get_RxLen());
      }

    if( first )
      {
       Printf(out,"TxLen(#;)",get_TxLen());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"TxLen(#;)",get_TxLen());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortFIFOUse */

struct Type_PortFIFOUse
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortFIFOUse(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortFIFOUse & setTo(Bar &bar) { bar.set_PortFIFOUse(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortFIFOUse & setTo(Bar &bar,AddressType ind) { bar.set_PortFIFOUse(ind,*this); return *this; }
 

  template <class T>
  Type_PortFIFOUse & set(T to) { to(*this); return *this; }
 

  Type get_RxUse() const
   {
    return (value>>0)&0xFu;
   }
 
  Type_PortFIFOUse & set_RxUse(Type field)
   {
    value=((field&0xFu)<<0)|(value&0xFFFFFFF0u);

    return *this;
   }
 

  Type get_TxUse() const
   {
    return (value>>4)&0x1Fu;
   }
 
  Type_PortFIFOUse & set_TxUse(Type field)
   {
    value=((field&0x1Fu)<<4)|(value&0xFFFFFE0Fu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"RxUse(#;)",get_RxUse());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RxUse(#;)",get_RxUse());
      }

    if( first )
      {
       Printf(out,"TxUse(#;)",get_TxUse());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"TxUse(#;)",get_TxUse());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortTxFIFOControl */

enum Field_PortTxFIFOControl_Mode : uint32
 {
  PortTxFIFOControl_Mode_Normal  = 0x00u,
  PortTxFIFOControl_Mode_DualMAC = 0x01u,
  PortTxFIFOControl_Mode_RateLim = 0x02u
 };
 
struct PrintField_PortTxFIFOControl_Mode
 {
  Field_PortTxFIFOControl_Mode field;

  explicit PrintField_PortTxFIFOControl_Mode(Field_PortTxFIFOControl_Mode field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"Normal"); break;
       case 0x01u : Putobj(out,"DualMAC"); break;
       case 0x02u : Putobj(out,"RateLim"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_PortTxFIFOControl_Mode GetTextDesc(Field_PortTxFIFOControl_Mode field)
 {
  return PrintField_PortTxFIFOControl_Mode(field);
 }
 
struct Type_PortTxFIFOControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortTxFIFOControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortTxFIFOControl & setTo(Bar &bar) { bar.set_PortTxFIFOControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortTxFIFOControl & setTo(Bar &bar,AddressType ind) { bar.set_PortTxFIFOControl(ind,*this); return *this; }
 

  template <class T>
  Type_PortTxFIFOControl & set(T to) { to(*this); return *this; }
 

  Type get_WordLen() const
   {
    return (value>>0)&0x3FFu;
   }
 
  Type_PortTxFIFOControl & set_WordLen(Type field)
   {
    value=((field&0x3FFu)<<0)|(value&0xFFFFFC00u);

    return *this;
   }
 

  Type get_Rem() const
   {
    return (value>>12)&0xFu;
   }
 
  Type_PortTxFIFOControl & set_Rem(Type field)
   {
    value=((field&0xFu)<<12)|(value&0xFFFF0FFFu);

    return *this;
   }
 

  Field_PortTxFIFOControl_Mode get_Mode() const
   {
    return Field_PortTxFIFOControl_Mode((value>>16)&0x3u);
   }
 
  Type_PortTxFIFOControl & set_Mode(Field_PortTxFIFOControl_Mode field)
   {
    value=((Type(field)&0x3u)<<16)|(value&0xFFFCFFFFu);

    return *this;
   }
 

  Type get_Rate() const
   {
    return (value>>20)&0xFu;
   }
 
  Type_PortTxFIFOControl & set_Rate(Type field)
   {
    value=((field&0xFu)<<20)|(value&0xFF0FFFFFu);

    return *this;
   }
 

  Type get_HostRem() const
   {
    return (value>>24)&0xFu;
   }
 
  Type_PortTxFIFOControl & set_HostRem(Type field)
   {
    value=((field&0xFu)<<24)|(value&0xF0FFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"WordLen(#;)",get_WordLen());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"WordLen(#;)",get_WordLen());
      }

    if( first )
      {
       Printf(out,"Rem(#;)",get_Rem());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Rem(#;)",get_Rem());
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
       Printf(out,"Rate(#;)",get_Rate());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Rate(#;)",get_Rate());
      }

    if( first )
      {
       Printf(out,"HostRem(#;)",get_HostRem());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"HostRem(#;)",get_HostRem());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortVLANControl */

enum Bits_PortVLANControl : uint32
 {
  PortVLANControl_CFI = 0x00001000u
 };
 
inline Bits_PortVLANControl operator | (Bits_PortVLANControl a,Bits_PortVLANControl b)
 { return Bits_PortVLANControl(uint32(a)|uint32(b)); }
 
struct Type_PortVLANControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortVLANControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortVLANControl & setTo(Bar &bar) { bar.set_PortVLANControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortVLANControl & setTo(Bar &bar,AddressType ind) { bar.set_PortVLANControl(ind,*this); return *this; }
 

  template <class T>
  Type_PortVLANControl & set(T to) { to(*this); return *this; }
 

  Type_PortVLANControl & setbit(Bits_PortVLANControl bits) { value|=Type(bits); return *this; }
 
  Type_PortVLANControl & setbitIf(bool cond,Bits_PortVLANControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_PortVLANControl & clearbit(Bits_PortVLANControl bits) { value&=~Type(bits); return *this; }
 
  Type_PortVLANControl & clearbitIf(bool cond,Bits_PortVLANControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_PortVLANControl bits) const { return value&bits; }
 
  bool testbit(Bits_PortVLANControl bits) const { return (value&bits)==Type(bits); }
 

  Type get_VID() const
   {
    return (value>>0)&0xFFFu;
   }
 
  Type_PortVLANControl & set_VID(Type field)
   {
    value=((field&0xFFFu)<<0)|(value&0xFFFFF000u);

    return *this;
   }
 

  Type get_Pri() const
   {
    return (value>>13)&0x7u;
   }
 
  Type_PortVLANControl & set_Pri(Type field)
   {
    value=((field&0x7u)<<13)|(value&0xFFFF1FFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&PortVLANControl_CFI )
      {
       if( first )
         {
          Putobj(out,"CFI");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CFI");
         }
      }

    if( first )
      {
       Printf(out,"VID(#;)",get_VID());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"VID(#;)",get_VID());
      }

    if( first )
      {
       Printf(out,"Pri(#;)",get_Pri());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri(#;)",get_Pri());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortTxPriMap */

struct Type_PortTxPriMap
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortTxPriMap(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortTxPriMap & setTo(Bar &bar) { bar.set_PortTxPriMap(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortTxPriMap & setTo(Bar &bar,AddressType ind) { bar.set_PortTxPriMap(ind,*this); return *this; }
 

  template <class T>
  Type_PortTxPriMap & set(T to) { to(*this); return *this; }
 

  Type get_Pri0() const
   {
    return (value>>0)&0x3u;
   }
 
  Type_PortTxPriMap & set_Pri0(Type field)
   {
    value=((field&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  Type get_Pri1() const
   {
    return (value>>4)&0x3u;
   }
 
  Type_PortTxPriMap & set_Pri1(Type field)
   {
    value=((field&0x3u)<<4)|(value&0xFFFFFFCFu);

    return *this;
   }
 

  Type get_Pri2() const
   {
    return (value>>8)&0x3u;
   }
 
  Type_PortTxPriMap & set_Pri2(Type field)
   {
    value=((field&0x3u)<<8)|(value&0xFFFFFCFFu);

    return *this;
   }
 

  Type get_Pri3() const
   {
    return (value>>12)&0x3u;
   }
 
  Type_PortTxPriMap & set_Pri3(Type field)
   {
    value=((field&0x3u)<<12)|(value&0xFFFFCFFFu);

    return *this;
   }
 

  Type get_Pri4() const
   {
    return (value>>16)&0x3u;
   }
 
  Type_PortTxPriMap & set_Pri4(Type field)
   {
    value=((field&0x3u)<<16)|(value&0xFFFCFFFFu);

    return *this;
   }
 

  Type get_Pri5() const
   {
    return (value>>20)&0x3u;
   }
 
  Type_PortTxPriMap & set_Pri5(Type field)
   {
    value=((field&0x3u)<<20)|(value&0xFFCFFFFFu);

    return *this;
   }
 

  Type get_Pri6() const
   {
    return (value>>24)&0x3u;
   }
 
  Type_PortTxPriMap & set_Pri6(Type field)
   {
    value=((field&0x3u)<<24)|(value&0xFCFFFFFFu);

    return *this;
   }
 

  Type get_Pri7() const
   {
    return (value>>28)&0x3u;
   }
 
  Type_PortTxPriMap & set_Pri7(Type field)
   {
    value=((field&0x3u)<<28)|(value&0xCFFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Pri0(#;)",get_Pri0());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri0(#;)",get_Pri0());
      }

    if( first )
      {
       Printf(out,"Pri1(#;)",get_Pri1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri1(#;)",get_Pri1());
      }

    if( first )
      {
       Printf(out,"Pri2(#;)",get_Pri2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri2(#;)",get_Pri2());
      }

    if( first )
      {
       Printf(out,"Pri3(#;)",get_Pri3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri3(#;)",get_Pri3());
      }

    if( first )
      {
       Printf(out,"Pri4(#;)",get_Pri4());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri4(#;)",get_Pri4());
      }

    if( first )
      {
       Printf(out,"Pri5(#;)",get_Pri5());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri5(#;)",get_Pri5());
      }

    if( first )
      {
       Printf(out,"Pri6(#;)",get_Pri6());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri6(#;)",get_Pri6());
      }

    if( first )
      {
       Printf(out,"Pri7(#;)",get_Pri7());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri7(#;)",get_Pri7());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortTxDMAPriMap */

struct Type_PortTxDMAPriMap
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortTxDMAPriMap(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortTxDMAPriMap & setTo(Bar &bar) { bar.set_PortTxDMAPriMap(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortTxDMAPriMap & setTo(Bar &bar,AddressType ind) { bar.set_PortTxDMAPriMap(ind,*this); return *this; }
 

  template <class T>
  Type_PortTxDMAPriMap & set(T to) { to(*this); return *this; }
 

  Type get_Pri0() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_PortTxDMAPriMap & set_Pri0(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  Type get_Pri1() const
   {
    return (value>>4)&0x7u;
   }
 
  Type_PortTxDMAPriMap & set_Pri1(Type field)
   {
    value=((field&0x7u)<<4)|(value&0xFFFFFF8Fu);

    return *this;
   }
 

  Type get_Pri2() const
   {
    return (value>>8)&0x7u;
   }
 
  Type_PortTxDMAPriMap & set_Pri2(Type field)
   {
    value=((field&0x7u)<<8)|(value&0xFFFFF8FFu);

    return *this;
   }
 

  Type get_Pri3() const
   {
    return (value>>12)&0x7u;
   }
 
  Type_PortTxDMAPriMap & set_Pri3(Type field)
   {
    value=((field&0x7u)<<12)|(value&0xFFFF8FFFu);

    return *this;
   }
 

  Type get_Pri4() const
   {
    return (value>>16)&0x7u;
   }
 
  Type_PortTxDMAPriMap & set_Pri4(Type field)
   {
    value=((field&0x7u)<<16)|(value&0xFFF8FFFFu);

    return *this;
   }
 

  Type get_Pri5() const
   {
    return (value>>20)&0x7u;
   }
 
  Type_PortTxDMAPriMap & set_Pri5(Type field)
   {
    value=((field&0x7u)<<20)|(value&0xFF8FFFFFu);

    return *this;
   }
 

  Type get_Pri6() const
   {
    return (value>>24)&0x7u;
   }
 
  Type_PortTxDMAPriMap & set_Pri6(Type field)
   {
    value=((field&0x7u)<<24)|(value&0xF8FFFFFFu);

    return *this;
   }
 

  Type get_Pri7() const
   {
    return (value>>28)&0x7u;
   }
 
  Type_PortTxDMAPriMap & set_Pri7(Type field)
   {
    value=((field&0x7u)<<28)|(value&0x8FFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Pri0(#;)",get_Pri0());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri0(#;)",get_Pri0());
      }

    if( first )
      {
       Printf(out,"Pri1(#;)",get_Pri1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri1(#;)",get_Pri1());
      }

    if( first )
      {
       Printf(out,"Pri2(#;)",get_Pri2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri2(#;)",get_Pri2());
      }

    if( first )
      {
       Printf(out,"Pri3(#;)",get_Pri3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri3(#;)",get_Pri3());
      }

    if( first )
      {
       Printf(out,"Pri4(#;)",get_Pri4());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri4(#;)",get_Pri4());
      }

    if( first )
      {
       Printf(out,"Pri5(#;)",get_Pri5());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri5(#;)",get_Pri5());
      }

    if( first )
      {
       Printf(out,"Pri6(#;)",get_Pri6());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri6(#;)",get_Pri6());
      }

    if( first )
      {
       Printf(out,"Pri7(#;)",get_Pri7());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri7(#;)",get_Pri7());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortRxDMAPriMap */

struct Type_PortRxDMAPriMap
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortRxDMAPriMap(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortRxDMAPriMap & setTo(Bar &bar) { bar.set_PortRxDMAPriMap(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortRxDMAPriMap & setTo(Bar &bar,AddressType ind) { bar.set_PortRxDMAPriMap(ind,*this); return *this; }
 

  template <class T>
  Type_PortRxDMAPriMap & set(T to) { to(*this); return *this; }
 

  Type get_P1Pri0() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_PortRxDMAPriMap & set_P1Pri0(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  Type get_P1Pri1() const
   {
    return (value>>4)&0x7u;
   }
 
  Type_PortRxDMAPriMap & set_P1Pri1(Type field)
   {
    value=((field&0x7u)<<4)|(value&0xFFFFFF8Fu);

    return *this;
   }
 

  Type get_P1Pri2() const
   {
    return (value>>8)&0x7u;
   }
 
  Type_PortRxDMAPriMap & set_P1Pri2(Type field)
   {
    value=((field&0x7u)<<8)|(value&0xFFFFF8FFu);

    return *this;
   }
 

  Type get_P1Pri3() const
   {
    return (value>>12)&0x7u;
   }
 
  Type_PortRxDMAPriMap & set_P1Pri3(Type field)
   {
    value=((field&0x7u)<<12)|(value&0xFFFF8FFFu);

    return *this;
   }
 

  Type get_P2Pri0() const
   {
    return (value>>16)&0x7u;
   }
 
  Type_PortRxDMAPriMap & set_P2Pri0(Type field)
   {
    value=((field&0x7u)<<16)|(value&0xFFF8FFFFu);

    return *this;
   }
 

  Type get_P2Pri1() const
   {
    return (value>>20)&0x7u;
   }
 
  Type_PortRxDMAPriMap & set_P2Pri1(Type field)
   {
    value=((field&0x7u)<<20)|(value&0xFF8FFFFFu);

    return *this;
   }
 

  Type get_P2Pri2() const
   {
    return (value>>24)&0x7u;
   }
 
  Type_PortRxDMAPriMap & set_P2Pri2(Type field)
   {
    value=((field&0x7u)<<24)|(value&0xF8FFFFFFu);

    return *this;
   }
 

  Type get_P2Pri3() const
   {
    return (value>>28)&0x7u;
   }
 
  Type_PortRxDMAPriMap & set_P2Pri3(Type field)
   {
    value=((field&0x7u)<<28)|(value&0x8FFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"P1Pri0(#;)",get_P1Pri0());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"P1Pri0(#;)",get_P1Pri0());
      }

    if( first )
      {
       Printf(out,"P1Pri1(#;)",get_P1Pri1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"P1Pri1(#;)",get_P1Pri1());
      }

    if( first )
      {
       Printf(out,"P1Pri2(#;)",get_P1Pri2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"P1Pri2(#;)",get_P1Pri2());
      }

    if( first )
      {
       Printf(out,"P1Pri3(#;)",get_P1Pri3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"P1Pri3(#;)",get_P1Pri3());
      }

    if( first )
      {
       Printf(out,"P2Pri0(#;)",get_P2Pri0());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"P2Pri0(#;)",get_P2Pri0());
      }

    if( first )
      {
       Printf(out,"P2Pri1(#;)",get_P2Pri1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"P2Pri1(#;)",get_P2Pri1());
      }

    if( first )
      {
       Printf(out,"P2Pri2(#;)",get_P2Pri2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"P2Pri2(#;)",get_P2Pri2());
      }

    if( first )
      {
       Printf(out,"P2Pri3(#;)",get_P2Pri3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"P2Pri3(#;)",get_P2Pri3());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortTOSPriMap0 */

struct Type_PortTOSPriMap0
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortTOSPriMap0(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortTOSPriMap0 & setTo(Bar &bar) { bar.set_PortTOSPriMap0(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortTOSPriMap0 & setTo(Bar &bar,AddressType ind) { bar.set_PortTOSPriMap0(ind,*this); return *this; }
 

  template <class T>
  Type_PortTOSPriMap0 & set(T to) { to(*this); return *this; }
 

  Type get_Pri0() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_PortTOSPriMap0 & set_Pri0(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  Type get_Pri1() const
   {
    return (value>>4)&0x7u;
   }
 
  Type_PortTOSPriMap0 & set_Pri1(Type field)
   {
    value=((field&0x7u)<<4)|(value&0xFFFFFF8Fu);

    return *this;
   }
 

  Type get_Pri2() const
   {
    return (value>>8)&0x7u;
   }
 
  Type_PortTOSPriMap0 & set_Pri2(Type field)
   {
    value=((field&0x7u)<<8)|(value&0xFFFFF8FFu);

    return *this;
   }
 

  Type get_Pri3() const
   {
    return (value>>12)&0x7u;
   }
 
  Type_PortTOSPriMap0 & set_Pri3(Type field)
   {
    value=((field&0x7u)<<12)|(value&0xFFFF8FFFu);

    return *this;
   }
 

  Type get_Pri4() const
   {
    return (value>>16)&0x7u;
   }
 
  Type_PortTOSPriMap0 & set_Pri4(Type field)
   {
    value=((field&0x7u)<<16)|(value&0xFFF8FFFFu);

    return *this;
   }
 

  Type get_Pri5() const
   {
    return (value>>20)&0x7u;
   }
 
  Type_PortTOSPriMap0 & set_Pri5(Type field)
   {
    value=((field&0x7u)<<20)|(value&0xFF8FFFFFu);

    return *this;
   }
 

  Type get_Pri6() const
   {
    return (value>>24)&0x7u;
   }
 
  Type_PortTOSPriMap0 & set_Pri6(Type field)
   {
    value=((field&0x7u)<<24)|(value&0xF8FFFFFFu);

    return *this;
   }
 

  Type get_Pri7() const
   {
    return (value>>28)&0x7u;
   }
 
  Type_PortTOSPriMap0 & set_Pri7(Type field)
   {
    value=((field&0x7u)<<28)|(value&0x8FFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Pri0(#;)",get_Pri0());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri0(#;)",get_Pri0());
      }

    if( first )
      {
       Printf(out,"Pri1(#;)",get_Pri1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri1(#;)",get_Pri1());
      }

    if( first )
      {
       Printf(out,"Pri2(#;)",get_Pri2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri2(#;)",get_Pri2());
      }

    if( first )
      {
       Printf(out,"Pri3(#;)",get_Pri3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri3(#;)",get_Pri3());
      }

    if( first )
      {
       Printf(out,"Pri4(#;)",get_Pri4());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri4(#;)",get_Pri4());
      }

    if( first )
      {
       Printf(out,"Pri5(#;)",get_Pri5());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri5(#;)",get_Pri5());
      }

    if( first )
      {
       Printf(out,"Pri6(#;)",get_Pri6());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri6(#;)",get_Pri6());
      }

    if( first )
      {
       Printf(out,"Pri7(#;)",get_Pri7());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri7(#;)",get_Pri7());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortTOSPriMap1 */

struct Type_PortTOSPriMap1
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortTOSPriMap1(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortTOSPriMap1 & setTo(Bar &bar) { bar.set_PortTOSPriMap1(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortTOSPriMap1 & setTo(Bar &bar,AddressType ind) { bar.set_PortTOSPriMap1(ind,*this); return *this; }
 

  template <class T>
  Type_PortTOSPriMap1 & set(T to) { to(*this); return *this; }
 

  Type get_Pri8() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_PortTOSPriMap1 & set_Pri8(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  Type get_Pri9() const
   {
    return (value>>4)&0x7u;
   }
 
  Type_PortTOSPriMap1 & set_Pri9(Type field)
   {
    value=((field&0x7u)<<4)|(value&0xFFFFFF8Fu);

    return *this;
   }
 

  Type get_Pri10() const
   {
    return (value>>8)&0x7u;
   }
 
  Type_PortTOSPriMap1 & set_Pri10(Type field)
   {
    value=((field&0x7u)<<8)|(value&0xFFFFF8FFu);

    return *this;
   }
 

  Type get_Pri11() const
   {
    return (value>>12)&0x7u;
   }
 
  Type_PortTOSPriMap1 & set_Pri11(Type field)
   {
    value=((field&0x7u)<<12)|(value&0xFFFF8FFFu);

    return *this;
   }
 

  Type get_Pri12() const
   {
    return (value>>16)&0x7u;
   }
 
  Type_PortTOSPriMap1 & set_Pri12(Type field)
   {
    value=((field&0x7u)<<16)|(value&0xFFF8FFFFu);

    return *this;
   }
 

  Type get_Pri13() const
   {
    return (value>>20)&0x7u;
   }
 
  Type_PortTOSPriMap1 & set_Pri13(Type field)
   {
    value=((field&0x7u)<<20)|(value&0xFF8FFFFFu);

    return *this;
   }
 

  Type get_Pri14() const
   {
    return (value>>24)&0x7u;
   }
 
  Type_PortTOSPriMap1 & set_Pri14(Type field)
   {
    value=((field&0x7u)<<24)|(value&0xF8FFFFFFu);

    return *this;
   }
 

  Type get_Pri15() const
   {
    return (value>>28)&0x7u;
   }
 
  Type_PortTOSPriMap1 & set_Pri15(Type field)
   {
    value=((field&0x7u)<<28)|(value&0x8FFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Pri8(#;)",get_Pri8());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri8(#;)",get_Pri8());
      }

    if( first )
      {
       Printf(out,"Pri9(#;)",get_Pri9());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri9(#;)",get_Pri9());
      }

    if( first )
      {
       Printf(out,"Pri10(#;)",get_Pri10());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri10(#;)",get_Pri10());
      }

    if( first )
      {
       Printf(out,"Pri11(#;)",get_Pri11());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri11(#;)",get_Pri11());
      }

    if( first )
      {
       Printf(out,"Pri12(#;)",get_Pri12());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri12(#;)",get_Pri12());
      }

    if( first )
      {
       Printf(out,"Pri13(#;)",get_Pri13());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri13(#;)",get_Pri13());
      }

    if( first )
      {
       Printf(out,"Pri14(#;)",get_Pri14());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri14(#;)",get_Pri14());
      }

    if( first )
      {
       Printf(out,"Pri15(#;)",get_Pri15());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri15(#;)",get_Pri15());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortTOSPriMap2 */

struct Type_PortTOSPriMap2
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortTOSPriMap2(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortTOSPriMap2 & setTo(Bar &bar) { bar.set_PortTOSPriMap2(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortTOSPriMap2 & setTo(Bar &bar,AddressType ind) { bar.set_PortTOSPriMap2(ind,*this); return *this; }
 

  template <class T>
  Type_PortTOSPriMap2 & set(T to) { to(*this); return *this; }
 

  Type get_Pri16() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_PortTOSPriMap2 & set_Pri16(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  Type get_Pri17() const
   {
    return (value>>4)&0x7u;
   }
 
  Type_PortTOSPriMap2 & set_Pri17(Type field)
   {
    value=((field&0x7u)<<4)|(value&0xFFFFFF8Fu);

    return *this;
   }
 

  Type get_Pri18() const
   {
    return (value>>8)&0x7u;
   }
 
  Type_PortTOSPriMap2 & set_Pri18(Type field)
   {
    value=((field&0x7u)<<8)|(value&0xFFFFF8FFu);

    return *this;
   }
 

  Type get_Pri19() const
   {
    return (value>>12)&0x7u;
   }
 
  Type_PortTOSPriMap2 & set_Pri19(Type field)
   {
    value=((field&0x7u)<<12)|(value&0xFFFF8FFFu);

    return *this;
   }
 

  Type get_Pri20() const
   {
    return (value>>16)&0x7u;
   }
 
  Type_PortTOSPriMap2 & set_Pri20(Type field)
   {
    value=((field&0x7u)<<16)|(value&0xFFF8FFFFu);

    return *this;
   }
 

  Type get_Pri21() const
   {
    return (value>>20)&0x7u;
   }
 
  Type_PortTOSPriMap2 & set_Pri21(Type field)
   {
    value=((field&0x7u)<<20)|(value&0xFF8FFFFFu);

    return *this;
   }
 

  Type get_Pri22() const
   {
    return (value>>24)&0x7u;
   }
 
  Type_PortTOSPriMap2 & set_Pri22(Type field)
   {
    value=((field&0x7u)<<24)|(value&0xF8FFFFFFu);

    return *this;
   }
 

  Type get_Pri23() const
   {
    return (value>>28)&0x7u;
   }
 
  Type_PortTOSPriMap2 & set_Pri23(Type field)
   {
    value=((field&0x7u)<<28)|(value&0x8FFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Pri16(#;)",get_Pri16());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri16(#;)",get_Pri16());
      }

    if( first )
      {
       Printf(out,"Pri17(#;)",get_Pri17());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri17(#;)",get_Pri17());
      }

    if( first )
      {
       Printf(out,"Pri18(#;)",get_Pri18());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri18(#;)",get_Pri18());
      }

    if( first )
      {
       Printf(out,"Pri19(#;)",get_Pri19());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri19(#;)",get_Pri19());
      }

    if( first )
      {
       Printf(out,"Pri20(#;)",get_Pri20());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri20(#;)",get_Pri20());
      }

    if( first )
      {
       Printf(out,"Pri21(#;)",get_Pri21());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri21(#;)",get_Pri21());
      }

    if( first )
      {
       Printf(out,"Pri22(#;)",get_Pri22());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri22(#;)",get_Pri22());
      }

    if( first )
      {
       Printf(out,"Pri23(#;)",get_Pri23());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri23(#;)",get_Pri23());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortTOSPriMap3 */

struct Type_PortTOSPriMap3
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortTOSPriMap3(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortTOSPriMap3 & setTo(Bar &bar) { bar.set_PortTOSPriMap3(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortTOSPriMap3 & setTo(Bar &bar,AddressType ind) { bar.set_PortTOSPriMap3(ind,*this); return *this; }
 

  template <class T>
  Type_PortTOSPriMap3 & set(T to) { to(*this); return *this; }
 

  Type get_Pri24() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_PortTOSPriMap3 & set_Pri24(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  Type get_Pri25() const
   {
    return (value>>4)&0x7u;
   }
 
  Type_PortTOSPriMap3 & set_Pri25(Type field)
   {
    value=((field&0x7u)<<4)|(value&0xFFFFFF8Fu);

    return *this;
   }
 

  Type get_Pri26() const
   {
    return (value>>8)&0x7u;
   }
 
  Type_PortTOSPriMap3 & set_Pri26(Type field)
   {
    value=((field&0x7u)<<8)|(value&0xFFFFF8FFu);

    return *this;
   }
 

  Type get_Pri27() const
   {
    return (value>>12)&0x7u;
   }
 
  Type_PortTOSPriMap3 & set_Pri27(Type field)
   {
    value=((field&0x7u)<<12)|(value&0xFFFF8FFFu);

    return *this;
   }
 

  Type get_Pri28() const
   {
    return (value>>16)&0x7u;
   }
 
  Type_PortTOSPriMap3 & set_Pri28(Type field)
   {
    value=((field&0x7u)<<16)|(value&0xFFF8FFFFu);

    return *this;
   }
 

  Type get_Pri29() const
   {
    return (value>>20)&0x7u;
   }
 
  Type_PortTOSPriMap3 & set_Pri29(Type field)
   {
    value=((field&0x7u)<<20)|(value&0xFF8FFFFFu);

    return *this;
   }
 

  Type get_Pri30() const
   {
    return (value>>24)&0x7u;
   }
 
  Type_PortTOSPriMap3 & set_Pri30(Type field)
   {
    value=((field&0x7u)<<24)|(value&0xF8FFFFFFu);

    return *this;
   }
 

  Type get_Pri31() const
   {
    return (value>>28)&0x7u;
   }
 
  Type_PortTOSPriMap3 & set_Pri31(Type field)
   {
    value=((field&0x7u)<<28)|(value&0x8FFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Pri24(#;)",get_Pri24());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri24(#;)",get_Pri24());
      }

    if( first )
      {
       Printf(out,"Pri25(#;)",get_Pri25());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri25(#;)",get_Pri25());
      }

    if( first )
      {
       Printf(out,"Pri26(#;)",get_Pri26());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri26(#;)",get_Pri26());
      }

    if( first )
      {
       Printf(out,"Pri27(#;)",get_Pri27());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri27(#;)",get_Pri27());
      }

    if( first )
      {
       Printf(out,"Pri28(#;)",get_Pri28());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri28(#;)",get_Pri28());
      }

    if( first )
      {
       Printf(out,"Pri29(#;)",get_Pri29());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri29(#;)",get_Pri29());
      }

    if( first )
      {
       Printf(out,"Pri30(#;)",get_Pri30());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri30(#;)",get_Pri30());
      }

    if( first )
      {
       Printf(out,"Pri31(#;)",get_Pri31());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri31(#;)",get_Pri31());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortTOSPriMap4 */

struct Type_PortTOSPriMap4
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortTOSPriMap4(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortTOSPriMap4 & setTo(Bar &bar) { bar.set_PortTOSPriMap4(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortTOSPriMap4 & setTo(Bar &bar,AddressType ind) { bar.set_PortTOSPriMap4(ind,*this); return *this; }
 

  template <class T>
  Type_PortTOSPriMap4 & set(T to) { to(*this); return *this; }
 

  Type get_Pri32() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_PortTOSPriMap4 & set_Pri32(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  Type get_Pri33() const
   {
    return (value>>4)&0x7u;
   }
 
  Type_PortTOSPriMap4 & set_Pri33(Type field)
   {
    value=((field&0x7u)<<4)|(value&0xFFFFFF8Fu);

    return *this;
   }
 

  Type get_Pri34() const
   {
    return (value>>8)&0x7u;
   }
 
  Type_PortTOSPriMap4 & set_Pri34(Type field)
   {
    value=((field&0x7u)<<8)|(value&0xFFFFF8FFu);

    return *this;
   }
 

  Type get_Pri35() const
   {
    return (value>>12)&0x7u;
   }
 
  Type_PortTOSPriMap4 & set_Pri35(Type field)
   {
    value=((field&0x7u)<<12)|(value&0xFFFF8FFFu);

    return *this;
   }
 

  Type get_Pri36() const
   {
    return (value>>16)&0x7u;
   }
 
  Type_PortTOSPriMap4 & set_Pri36(Type field)
   {
    value=((field&0x7u)<<16)|(value&0xFFF8FFFFu);

    return *this;
   }
 

  Type get_Pri37() const
   {
    return (value>>20)&0x7u;
   }
 
  Type_PortTOSPriMap4 & set_Pri37(Type field)
   {
    value=((field&0x7u)<<20)|(value&0xFF8FFFFFu);

    return *this;
   }
 

  Type get_Pri38() const
   {
    return (value>>24)&0x7u;
   }
 
  Type_PortTOSPriMap4 & set_Pri38(Type field)
   {
    value=((field&0x7u)<<24)|(value&0xF8FFFFFFu);

    return *this;
   }
 

  Type get_Pri39() const
   {
    return (value>>28)&0x7u;
   }
 
  Type_PortTOSPriMap4 & set_Pri39(Type field)
   {
    value=((field&0x7u)<<28)|(value&0x8FFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Pri32(#;)",get_Pri32());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri32(#;)",get_Pri32());
      }

    if( first )
      {
       Printf(out,"Pri33(#;)",get_Pri33());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri33(#;)",get_Pri33());
      }

    if( first )
      {
       Printf(out,"Pri34(#;)",get_Pri34());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri34(#;)",get_Pri34());
      }

    if( first )
      {
       Printf(out,"Pri35(#;)",get_Pri35());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri35(#;)",get_Pri35());
      }

    if( first )
      {
       Printf(out,"Pri36(#;)",get_Pri36());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri36(#;)",get_Pri36());
      }

    if( first )
      {
       Printf(out,"Pri37(#;)",get_Pri37());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri37(#;)",get_Pri37());
      }

    if( first )
      {
       Printf(out,"Pri38(#;)",get_Pri38());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri38(#;)",get_Pri38());
      }

    if( first )
      {
       Printf(out,"Pri39(#;)",get_Pri39());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri39(#;)",get_Pri39());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortTOSPriMap5 */

struct Type_PortTOSPriMap5
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortTOSPriMap5(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortTOSPriMap5 & setTo(Bar &bar) { bar.set_PortTOSPriMap5(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortTOSPriMap5 & setTo(Bar &bar,AddressType ind) { bar.set_PortTOSPriMap5(ind,*this); return *this; }
 

  template <class T>
  Type_PortTOSPriMap5 & set(T to) { to(*this); return *this; }
 

  Type get_Pri40() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_PortTOSPriMap5 & set_Pri40(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  Type get_Pri41() const
   {
    return (value>>4)&0x7u;
   }
 
  Type_PortTOSPriMap5 & set_Pri41(Type field)
   {
    value=((field&0x7u)<<4)|(value&0xFFFFFF8Fu);

    return *this;
   }
 

  Type get_Pri42() const
   {
    return (value>>8)&0x7u;
   }
 
  Type_PortTOSPriMap5 & set_Pri42(Type field)
   {
    value=((field&0x7u)<<8)|(value&0xFFFFF8FFu);

    return *this;
   }
 

  Type get_Pri43() const
   {
    return (value>>12)&0x7u;
   }
 
  Type_PortTOSPriMap5 & set_Pri43(Type field)
   {
    value=((field&0x7u)<<12)|(value&0xFFFF8FFFu);

    return *this;
   }
 

  Type get_Pri44() const
   {
    return (value>>16)&0x7u;
   }
 
  Type_PortTOSPriMap5 & set_Pri44(Type field)
   {
    value=((field&0x7u)<<16)|(value&0xFFF8FFFFu);

    return *this;
   }
 

  Type get_Pri45() const
   {
    return (value>>20)&0x7u;
   }
 
  Type_PortTOSPriMap5 & set_Pri45(Type field)
   {
    value=((field&0x7u)<<20)|(value&0xFF8FFFFFu);

    return *this;
   }
 

  Type get_Pri46() const
   {
    return (value>>24)&0x7u;
   }
 
  Type_PortTOSPriMap5 & set_Pri46(Type field)
   {
    value=((field&0x7u)<<24)|(value&0xF8FFFFFFu);

    return *this;
   }
 

  Type get_Pri47() const
   {
    return (value>>28)&0x7u;
   }
 
  Type_PortTOSPriMap5 & set_Pri47(Type field)
   {
    value=((field&0x7u)<<28)|(value&0x8FFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Pri40(#;)",get_Pri40());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri40(#;)",get_Pri40());
      }

    if( first )
      {
       Printf(out,"Pri41(#;)",get_Pri41());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri41(#;)",get_Pri41());
      }

    if( first )
      {
       Printf(out,"Pri42(#;)",get_Pri42());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri42(#;)",get_Pri42());
      }

    if( first )
      {
       Printf(out,"Pri43(#;)",get_Pri43());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri43(#;)",get_Pri43());
      }

    if( first )
      {
       Printf(out,"Pri44(#;)",get_Pri44());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri44(#;)",get_Pri44());
      }

    if( first )
      {
       Printf(out,"Pri45(#;)",get_Pri45());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri45(#;)",get_Pri45());
      }

    if( first )
      {
       Printf(out,"Pri46(#;)",get_Pri46());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri46(#;)",get_Pri46());
      }

    if( first )
      {
       Printf(out,"Pri47(#;)",get_Pri47());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri47(#;)",get_Pri47());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortTOSPriMap6 */

struct Type_PortTOSPriMap6
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortTOSPriMap6(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortTOSPriMap6 & setTo(Bar &bar) { bar.set_PortTOSPriMap6(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortTOSPriMap6 & setTo(Bar &bar,AddressType ind) { bar.set_PortTOSPriMap6(ind,*this); return *this; }
 

  template <class T>
  Type_PortTOSPriMap6 & set(T to) { to(*this); return *this; }
 

  Type get_Pri48() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_PortTOSPriMap6 & set_Pri48(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  Type get_Pri49() const
   {
    return (value>>4)&0x7u;
   }
 
  Type_PortTOSPriMap6 & set_Pri49(Type field)
   {
    value=((field&0x7u)<<4)|(value&0xFFFFFF8Fu);

    return *this;
   }
 

  Type get_Pri50() const
   {
    return (value>>8)&0x7u;
   }
 
  Type_PortTOSPriMap6 & set_Pri50(Type field)
   {
    value=((field&0x7u)<<8)|(value&0xFFFFF8FFu);

    return *this;
   }
 

  Type get_Pri51() const
   {
    return (value>>12)&0x7u;
   }
 
  Type_PortTOSPriMap6 & set_Pri51(Type field)
   {
    value=((field&0x7u)<<12)|(value&0xFFFF8FFFu);

    return *this;
   }
 

  Type get_Pri52() const
   {
    return (value>>16)&0x7u;
   }
 
  Type_PortTOSPriMap6 & set_Pri52(Type field)
   {
    value=((field&0x7u)<<16)|(value&0xFFF8FFFFu);

    return *this;
   }
 

  Type get_Pri53() const
   {
    return (value>>20)&0x7u;
   }
 
  Type_PortTOSPriMap6 & set_Pri53(Type field)
   {
    value=((field&0x7u)<<20)|(value&0xFF8FFFFFu);

    return *this;
   }
 

  Type get_Pri54() const
   {
    return (value>>24)&0x7u;
   }
 
  Type_PortTOSPriMap6 & set_Pri54(Type field)
   {
    value=((field&0x7u)<<24)|(value&0xF8FFFFFFu);

    return *this;
   }
 

  Type get_Pri55() const
   {
    return (value>>28)&0x7u;
   }
 
  Type_PortTOSPriMap6 & set_Pri55(Type field)
   {
    value=((field&0x7u)<<28)|(value&0x8FFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Pri48(#;)",get_Pri48());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri48(#;)",get_Pri48());
      }

    if( first )
      {
       Printf(out,"Pri49(#;)",get_Pri49());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri49(#;)",get_Pri49());
      }

    if( first )
      {
       Printf(out,"Pri50(#;)",get_Pri50());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri50(#;)",get_Pri50());
      }

    if( first )
      {
       Printf(out,"Pri51(#;)",get_Pri51());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri51(#;)",get_Pri51());
      }

    if( first )
      {
       Printf(out,"Pri52(#;)",get_Pri52());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri52(#;)",get_Pri52());
      }

    if( first )
      {
       Printf(out,"Pri53(#;)",get_Pri53());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri53(#;)",get_Pri53());
      }

    if( first )
      {
       Printf(out,"Pri54(#;)",get_Pri54());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri54(#;)",get_Pri54());
      }

    if( first )
      {
       Printf(out,"Pri55(#;)",get_Pri55());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri55(#;)",get_Pri55());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortTOSPriMap7 */

struct Type_PortTOSPriMap7
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortTOSPriMap7(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortTOSPriMap7 & setTo(Bar &bar) { bar.set_PortTOSPriMap7(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortTOSPriMap7 & setTo(Bar &bar,AddressType ind) { bar.set_PortTOSPriMap7(ind,*this); return *this; }
 

  template <class T>
  Type_PortTOSPriMap7 & set(T to) { to(*this); return *this; }
 

  Type get_Pri56() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_PortTOSPriMap7 & set_Pri56(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  Type get_Pri57() const
   {
    return (value>>4)&0x7u;
   }
 
  Type_PortTOSPriMap7 & set_Pri57(Type field)
   {
    value=((field&0x7u)<<4)|(value&0xFFFFFF8Fu);

    return *this;
   }
 

  Type get_Pri58() const
   {
    return (value>>8)&0x7u;
   }
 
  Type_PortTOSPriMap7 & set_Pri58(Type field)
   {
    value=((field&0x7u)<<8)|(value&0xFFFFF8FFu);

    return *this;
   }
 

  Type get_Pri59() const
   {
    return (value>>12)&0x7u;
   }
 
  Type_PortTOSPriMap7 & set_Pri59(Type field)
   {
    value=((field&0x7u)<<12)|(value&0xFFFF8FFFu);

    return *this;
   }
 

  Type get_Pri60() const
   {
    return (value>>16)&0x7u;
   }
 
  Type_PortTOSPriMap7 & set_Pri60(Type field)
   {
    value=((field&0x7u)<<16)|(value&0xFFF8FFFFu);

    return *this;
   }
 

  Type get_Pri61() const
   {
    return (value>>20)&0x7u;
   }
 
  Type_PortTOSPriMap7 & set_Pri61(Type field)
   {
    value=((field&0x7u)<<20)|(value&0xFF8FFFFFu);

    return *this;
   }
 

  Type get_Pri62() const
   {
    return (value>>24)&0x7u;
   }
 
  Type_PortTOSPriMap7 & set_Pri62(Type field)
   {
    value=((field&0x7u)<<24)|(value&0xF8FFFFFFu);

    return *this;
   }
 

  Type get_Pri63() const
   {
    return (value>>28)&0x7u;
   }
 
  Type_PortTOSPriMap7 & set_Pri63(Type field)
   {
    value=((field&0x7u)<<28)|(value&0x8FFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Pri56(#;)",get_Pri56());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri56(#;)",get_Pri56());
      }

    if( first )
      {
       Printf(out,"Pri57(#;)",get_Pri57());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri57(#;)",get_Pri57());
      }

    if( first )
      {
       Printf(out,"Pri58(#;)",get_Pri58());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri58(#;)",get_Pri58());
      }

    if( first )
      {
       Printf(out,"Pri59(#;)",get_Pri59());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri59(#;)",get_Pri59());
      }

    if( first )
      {
       Printf(out,"Pri60(#;)",get_Pri60());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri60(#;)",get_Pri60());
      }

    if( first )
      {
       Printf(out,"Pri61(#;)",get_Pri61());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri61(#;)",get_Pri61());
      }

    if( first )
      {
       Printf(out,"Pri62(#;)",get_Pri62());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri62(#;)",get_Pri62());
      }

    if( first )
      {
       Printf(out,"Pri63(#;)",get_Pri63());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri63(#;)",get_Pri63());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortTimeSync */

struct Type_PortTimeSync
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortTimeSync(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortTimeSync & setTo(Bar &bar) { bar.set_PortTimeSync(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortTimeSync & setTo(Bar &bar,AddressType ind) { bar.set_PortTimeSync(ind,*this); return *this; }
 

  template <class T>
  Type_PortTimeSync & set(T to) { to(*this); return *this; }
 

  Type get_MsgTypeMask() const
   {
    return (value>>0)&0xFFFFu;
   }
 
  Type_PortTimeSync & set_MsgTypeMask(Type field)
   {
    value=((field&0xFFFFu)<<0)|(value&0xFFFF0000u);

    return *this;
   }
 

  Type get_SyncFieldOffset() const
   {
    return (value>>16)&0x3Fu;
   }
 
  Type_PortTimeSync & set_SyncFieldOffset(Type field)
   {
    value=((field&0x3Fu)<<16)|(value&0xFFC0FFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"MsgTypeMask(#;)",get_MsgTypeMask());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MsgTypeMask(#;)",get_MsgTypeMask());
      }

    if( first )
      {
       Printf(out,"SyncFieldOffset(#;)",get_SyncFieldOffset());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SyncFieldOffset(#;)",get_SyncFieldOffset());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortMACHi */

struct Type_PortMACHi
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortMACHi(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortMACHi & setTo(Bar &bar) { bar.set_PortMACHi(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortMACHi & setTo(Bar &bar,AddressType ind) { bar.set_PortMACHi(ind,*this); return *this; }
 

  template <class T>
  Type_PortMACHi & set(T to) { to(*this); return *this; }
 

  Type get_Byte1() const
   {
    return (value>>0)&0xFFu;
   }
 
  Type_PortMACHi & set_Byte1(Type field)
   {
    value=((field&0xFFu)<<0)|(value&0xFFFFFF00u);

    return *this;
   }
 

  Type get_Byte0() const
   {
    return (value>>8)&0xFFu;
   }
 
  Type_PortMACHi & set_Byte0(Type field)
   {
    value=((field&0xFFu)<<8)|(value&0xFFFF00FFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Byte1(#;)",get_Byte1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Byte1(#;)",get_Byte1());
      }

    if( first )
      {
       Printf(out,"Byte0(#;)",get_Byte0());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Byte0(#;)",get_Byte0());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortMACLo */

struct Type_PortMACLo
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortMACLo(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortMACLo & setTo(Bar &bar) { bar.set_PortMACLo(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortMACLo & setTo(Bar &bar,AddressType ind) { bar.set_PortMACLo(ind,*this); return *this; }
 

  template <class T>
  Type_PortMACLo & set(T to) { to(*this); return *this; }
 

  Type get_Byte5() const
   {
    return (value>>0)&0xFFu;
   }
 
  Type_PortMACLo & set_Byte5(Type field)
   {
    value=((field&0xFFu)<<0)|(value&0xFFFFFF00u);

    return *this;
   }
 

  Type get_Byte4() const
   {
    return (value>>8)&0xFFu;
   }
 
  Type_PortMACLo & set_Byte4(Type field)
   {
    value=((field&0xFFu)<<8)|(value&0xFFFF00FFu);

    return *this;
   }
 

  Type get_Byte3() const
   {
    return (value>>16)&0xFFu;
   }
 
  Type_PortMACLo & set_Byte3(Type field)
   {
    value=((field&0xFFu)<<16)|(value&0xFF00FFFFu);

    return *this;
   }
 

  Type get_Byte2() const
   {
    return (value>>24)&0xFFu;
   }
 
  Type_PortMACLo & set_Byte2(Type field)
   {
    value=((field&0xFFu)<<24)|(value&0xFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Byte5(#;)",get_Byte5());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Byte5(#;)",get_Byte5());
      }

    if( first )
      {
       Printf(out,"Byte4(#;)",get_Byte4());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Byte4(#;)",get_Byte4());
      }

    if( first )
      {
       Printf(out,"Byte3(#;)",get_Byte3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Byte3(#;)",get_Byte3());
      }

    if( first )
      {
       Printf(out,"Byte2(#;)",get_Byte2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Byte2(#;)",get_Byte2());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortSendPercent */

struct Type_PortSendPercent
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PortSendPercent(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortSendPercent & setTo(Bar &bar) { bar.set_PortSendPercent(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PortSendPercent & setTo(Bar &bar,AddressType ind) { bar.set_PortSendPercent(ind,*this); return *this; }
 

  template <class T>
  Type_PortSendPercent & set(T to) { to(*this); return *this; }
 

  Type get_Pri1() const
   {
    return (value>>0)&0x7Fu;
   }
 
  Type_PortSendPercent & set_Pri1(Type field)
   {
    value=((field&0x7Fu)<<0)|(value&0xFFFFFF80u);

    return *this;
   }
 

  Type get_Pri2() const
   {
    return (value>>8)&0x7Fu;
   }
 
  Type_PortSendPercent & set_Pri2(Type field)
   {
    value=((field&0x7Fu)<<8)|(value&0xFFFF80FFu);

    return *this;
   }
 

  Type get_Pri3() const
   {
    return (value>>16)&0x7Fu;
   }
 
  Type_PortSendPercent & set_Pri3(Type field)
   {
    value=((field&0x7Fu)<<16)|(value&0xFF80FFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Pri1(#;)",get_Pri1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri1(#;)",get_Pri1());
      }

    if( first )
      {
       Printf(out,"Pri2(#;)",get_Pri2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri2(#;)",get_Pri2());
      }

    if( first )
      {
       Printf(out,"Pri3(#;)",get_Pri3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri3(#;)",get_Pri3());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DMATxControl */

enum Bits_DMATxControl : uint32
 {
  DMATxControl_Enable = 0x00000001u
 };
 
inline Bits_DMATxControl operator | (Bits_DMATxControl a,Bits_DMATxControl b)
 { return Bits_DMATxControl(uint32(a)|uint32(b)); }
 
struct Type_DMATxControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_DMATxControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMATxControl & setTo(Bar &bar) { bar.set_DMATxControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DMATxControl & setTo(Bar &bar,AddressType ind) { bar.set_DMATxControl(ind,*this); return *this; }
 

  template <class T>
  Type_DMATxControl & set(T to) { to(*this); return *this; }
 

  Type_DMATxControl & setbit(Bits_DMATxControl bits) { value|=Type(bits); return *this; }
 
  Type_DMATxControl & setbitIf(bool cond,Bits_DMATxControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_DMATxControl & clearbit(Bits_DMATxControl bits) { value&=~Type(bits); return *this; }
 
  Type_DMATxControl & clearbitIf(bool cond,Bits_DMATxControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_DMATxControl bits) const { return value&bits; }
 
  bool testbit(Bits_DMATxControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&DMATxControl_Enable )
      {
       if( first )
         {
          Putobj(out,"Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Enable");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DMATxTeardown */

struct Type_DMATxTeardown
 {
  using Type = uint32 ;

  Type value;


  explicit Type_DMATxTeardown(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMATxTeardown & setTo(Bar &bar) { bar.set_DMATxTeardown(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DMATxTeardown & setTo(Bar &bar,AddressType ind) { bar.set_DMATxTeardown(ind,*this); return *this; }
 

  template <class T>
  Type_DMATxTeardown & set(T to) { to(*this); return *this; }
 

  Type get_Chan() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_DMATxTeardown & set_Chan(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Chan(#;)",get_Chan());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Chan(#;)",get_Chan());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DMARxControl */

enum Bits_DMARxControl : uint32
 {
  DMARxControl_Enable = 0x00000001u
 };
 
inline Bits_DMARxControl operator | (Bits_DMARxControl a,Bits_DMARxControl b)
 { return Bits_DMARxControl(uint32(a)|uint32(b)); }
 
struct Type_DMARxControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_DMARxControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMARxControl & setTo(Bar &bar) { bar.set_DMARxControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DMARxControl & setTo(Bar &bar,AddressType ind) { bar.set_DMARxControl(ind,*this); return *this; }
 

  template <class T>
  Type_DMARxControl & set(T to) { to(*this); return *this; }
 

  Type_DMARxControl & setbit(Bits_DMARxControl bits) { value|=Type(bits); return *this; }
 
  Type_DMARxControl & setbitIf(bool cond,Bits_DMARxControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_DMARxControl & clearbit(Bits_DMARxControl bits) { value&=~Type(bits); return *this; }
 
  Type_DMARxControl & clearbitIf(bool cond,Bits_DMARxControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_DMARxControl bits) const { return value&bits; }
 
  bool testbit(Bits_DMARxControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&DMARxControl_Enable )
      {
       if( first )
         {
          Putobj(out,"Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Enable");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DMARxTeardown */

struct Type_DMARxTeardown
 {
  using Type = uint32 ;

  Type value;


  explicit Type_DMARxTeardown(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMARxTeardown & setTo(Bar &bar) { bar.set_DMARxTeardown(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DMARxTeardown & setTo(Bar &bar,AddressType ind) { bar.set_DMARxTeardown(ind,*this); return *this; }
 

  template <class T>
  Type_DMARxTeardown & set(T to) { to(*this); return *this; }
 

  Type get_Chan() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_DMARxTeardown & set_Chan(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Chan(#;)",get_Chan());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Chan(#;)",get_Chan());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DMASoftReset */

enum Bits_DMASoftReset : uint32
 {
  DMASoftReset_Reset = 0x00000001u
 };
 
inline Bits_DMASoftReset operator | (Bits_DMASoftReset a,Bits_DMASoftReset b)
 { return Bits_DMASoftReset(uint32(a)|uint32(b)); }
 
struct Type_DMASoftReset
 {
  using Type = uint32 ;

  Type value;


  explicit Type_DMASoftReset(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMASoftReset & setTo(Bar &bar) { bar.set_DMASoftReset(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DMASoftReset & setTo(Bar &bar,AddressType ind) { bar.set_DMASoftReset(ind,*this); return *this; }
 

  template <class T>
  Type_DMASoftReset & set(T to) { to(*this); return *this; }
 

  Type_DMASoftReset & setbit(Bits_DMASoftReset bits) { value|=Type(bits); return *this; }
 
  Type_DMASoftReset & setbitIf(bool cond,Bits_DMASoftReset bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_DMASoftReset & clearbit(Bits_DMASoftReset bits) { value&=~Type(bits); return *this; }
 
  Type_DMASoftReset & clearbitIf(bool cond,Bits_DMASoftReset bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_DMASoftReset bits) const { return value&bits; }
 
  bool testbit(Bits_DMASoftReset bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&DMASoftReset_Reset )
      {
       if( first )
         {
          Putobj(out,"Reset");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Reset");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DMAControl */

enum Bits_DMAControl : uint32
 {
  DMAControl_UsePri        = 0x00000001u,
  DMAControl_RxSetOwnBit   = 0x00000002u,
  DMAControl_RxOfflenBlock = 0x00000004u,
  DMAControl_CmdIdle       = 0x00000008u,
  DMAControl_RxCopyOverrun = 0x00000010u,
  DMAControl_Tx0RateLim    = 0x00000100u,
  DMAControl_Tx1RateLim    = 0x00000200u,
  DMAControl_Tx2RateLim    = 0x00000400u,
  DMAControl_Tx3RateLim    = 0x00000800u,
  DMAControl_Tx4RateLim    = 0x00001000u,
  DMAControl_Tx5RateLim    = 0x00002000u,
  DMAControl_Tx6RateLim    = 0x00004000u,
  DMAControl_Tx7RateLim    = 0x00008000u
 };
 
inline Bits_DMAControl operator | (Bits_DMAControl a,Bits_DMAControl b)
 { return Bits_DMAControl(uint32(a)|uint32(b)); }
 
struct Type_DMAControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_DMAControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMAControl & setTo(Bar &bar) { bar.set_DMAControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DMAControl & setTo(Bar &bar,AddressType ind) { bar.set_DMAControl(ind,*this); return *this; }
 

  template <class T>
  Type_DMAControl & set(T to) { to(*this); return *this; }
 

  Type_DMAControl & setbit(Bits_DMAControl bits) { value|=Type(bits); return *this; }
 
  Type_DMAControl & setbitIf(bool cond,Bits_DMAControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_DMAControl & clearbit(Bits_DMAControl bits) { value&=~Type(bits); return *this; }
 
  Type_DMAControl & clearbitIf(bool cond,Bits_DMAControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_DMAControl bits) const { return value&bits; }
 
  bool testbit(Bits_DMAControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&DMAControl_UsePri )
      {
       if( first )
         {
          Putobj(out,"UsePri");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UsePri");
         }
      }

    if( value&DMAControl_RxSetOwnBit )
      {
       if( first )
         {
          Putobj(out,"RxSetOwnBit");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxSetOwnBit");
         }
      }

    if( value&DMAControl_RxOfflenBlock )
      {
       if( first )
         {
          Putobj(out,"RxOfflenBlock");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxOfflenBlock");
         }
      }

    if( value&DMAControl_CmdIdle )
      {
       if( first )
         {
          Putobj(out,"CmdIdle");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CmdIdle");
         }
      }

    if( value&DMAControl_RxCopyOverrun )
      {
       if( first )
         {
          Putobj(out,"RxCopyOverrun");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxCopyOverrun");
         }
      }

    if( value&DMAControl_Tx0RateLim )
      {
       if( first )
         {
          Putobj(out,"Tx0RateLim");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Tx0RateLim");
         }
      }

    if( value&DMAControl_Tx1RateLim )
      {
       if( first )
         {
          Putobj(out,"Tx1RateLim");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Tx1RateLim");
         }
      }

    if( value&DMAControl_Tx2RateLim )
      {
       if( first )
         {
          Putobj(out,"Tx2RateLim");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Tx2RateLim");
         }
      }

    if( value&DMAControl_Tx3RateLim )
      {
       if( first )
         {
          Putobj(out,"Tx3RateLim");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Tx3RateLim");
         }
      }

    if( value&DMAControl_Tx4RateLim )
      {
       if( first )
         {
          Putobj(out,"Tx4RateLim");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Tx4RateLim");
         }
      }

    if( value&DMAControl_Tx5RateLim )
      {
       if( first )
         {
          Putobj(out,"Tx5RateLim");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Tx5RateLim");
         }
      }

    if( value&DMAControl_Tx6RateLim )
      {
       if( first )
         {
          Putobj(out,"Tx6RateLim");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Tx6RateLim");
         }
      }

    if( value&DMAControl_Tx7RateLim )
      {
       if( first )
         {
          Putobj(out,"Tx7RateLim");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Tx7RateLim");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DMAStatus */

enum Bits_DMAStatus : uint32
 {
  DMAStatus_Idle = 0x80000000u
 };
 
inline Bits_DMAStatus operator | (Bits_DMAStatus a,Bits_DMAStatus b)
 { return Bits_DMAStatus(uint32(a)|uint32(b)); }
 
enum Field_DMAStatus_RxErrorCode : uint32
 {
  DMAStatus_RxErrorCode_NoError    = 0x00u,
  DMAStatus_RxErrorCode_NoOwnBit   = 0x02u,
  DMAStatus_RxErrorCode_NullBuf    = 0x04u,
  DMAStatus_RxErrorCode_NullBufLen = 0x05u,
  DMAStatus_RxErrorCode_BadOffset  = 0x06u
 };
 
struct PrintField_DMAStatus_RxErrorCode
 {
  Field_DMAStatus_RxErrorCode field;

  explicit PrintField_DMAStatus_RxErrorCode(Field_DMAStatus_RxErrorCode field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"NoError"); break;
       case 0x02u : Putobj(out,"NoOwnBit"); break;
       case 0x04u : Putobj(out,"NullBuf"); break;
       case 0x05u : Putobj(out,"NullBufLen"); break;
       case 0x06u : Putobj(out,"BadOffset"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DMAStatus_RxErrorCode GetTextDesc(Field_DMAStatus_RxErrorCode field)
 {
  return PrintField_DMAStatus_RxErrorCode(field);
 }
 
enum Field_DMAStatus_TxErrorCode : uint32
 {
  DMAStatus_TxErrorCode_NoError      = 0x00u,
  DMAStatus_TxErrorCode_SOPError     = 0x01u,
  DMAStatus_TxErrorCode_NoOwnBit     = 0x02u,
  DMAStatus_TxErrorCode_NullNextBuf  = 0x03u,
  DMAStatus_TxErrorCode_NullBuf      = 0x04u,
  DMAStatus_TxErrorCode_NullBufLen   = 0x05u,
  DMAStatus_TxErrorCode_BadPacketLen = 0x06u
 };
 
struct PrintField_DMAStatus_TxErrorCode
 {
  Field_DMAStatus_TxErrorCode field;

  explicit PrintField_DMAStatus_TxErrorCode(Field_DMAStatus_TxErrorCode field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"NoError"); break;
       case 0x01u : Putobj(out,"SOPError"); break;
       case 0x02u : Putobj(out,"NoOwnBit"); break;
       case 0x03u : Putobj(out,"NullNextBuf"); break;
       case 0x04u : Putobj(out,"NullBuf"); break;
       case 0x05u : Putobj(out,"NullBufLen"); break;
       case 0x06u : Putobj(out,"BadPacketLen"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DMAStatus_TxErrorCode GetTextDesc(Field_DMAStatus_TxErrorCode field)
 {
  return PrintField_DMAStatus_TxErrorCode(field);
 }
 
struct Type_DMAStatus
 {
  using Type = uint32 ;

  Type value;


  explicit Type_DMAStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMAStatus & setTo(Bar &bar) { bar.set_DMAStatus(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DMAStatus & setTo(Bar &bar,AddressType ind) { bar.set_DMAStatus(ind,*this); return *this; }
 

  template <class T>
  Type_DMAStatus & set(T to) { to(*this); return *this; }
 

  Type_DMAStatus & setbit(Bits_DMAStatus bits) { value|=Type(bits); return *this; }
 
  Type_DMAStatus & setbitIf(bool cond,Bits_DMAStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_DMAStatus & clearbit(Bits_DMAStatus bits) { value&=~Type(bits); return *this; }
 
  Type_DMAStatus & clearbitIf(bool cond,Bits_DMAStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_DMAStatus bits) const { return value&bits; }
 
  bool testbit(Bits_DMAStatus bits) const { return (value&bits)==Type(bits); }
 

  Type get_RxErrorChan() const
   {
    return (value>>8)&0x7u;
   }
 
  Type_DMAStatus & set_RxErrorChan(Type field)
   {
    value=((field&0x7u)<<8)|(value&0xFFFFF8FFu);

    return *this;
   }
 

  Field_DMAStatus_RxErrorCode get_RxErrorCode() const
   {
    return Field_DMAStatus_RxErrorCode((value>>12)&0xFu);
   }
 
  Type_DMAStatus & set_RxErrorCode(Field_DMAStatus_RxErrorCode field)
   {
    value=((Type(field)&0xFu)<<12)|(value&0xFFFF0FFFu);

    return *this;
   }
 

  Type get_TxErrorChan() const
   {
    return (value>>16)&0x7u;
   }
 
  Type_DMAStatus & set_TxErrorChan(Type field)
   {
    value=((field&0x7u)<<16)|(value&0xFFF8FFFFu);

    return *this;
   }
 

  Field_DMAStatus_TxErrorCode get_TxErrorCode() const
   {
    return Field_DMAStatus_TxErrorCode((value>>20)&0xFu);
   }
 
  Type_DMAStatus & set_TxErrorCode(Field_DMAStatus_TxErrorCode field)
   {
    value=((Type(field)&0xFu)<<20)|(value&0xFF0FFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&DMAStatus_Idle )
      {
       if( first )
         {
          Putobj(out,"Idle");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Idle");
         }
      }

    if( first )
      {
       Printf(out,"RxErrorChan(#;)",get_RxErrorChan());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RxErrorChan(#;)",get_RxErrorChan());
      }

    if( first )
      {
       Printf(out,"RxErrorCode(#;)",get_RxErrorCode());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RxErrorCode(#;)",get_RxErrorCode());
      }

    if( first )
      {
       Printf(out,"TxErrorChan(#;)",get_TxErrorChan());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"TxErrorChan(#;)",get_TxErrorChan());
      }

    if( first )
      {
       Printf(out,"TxErrorCode(#;)",get_TxErrorCode());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"TxErrorCode(#;)",get_TxErrorCode());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DMARxOffset */

struct Type_DMARxOffset
 {
  using Type = uint32 ;

  Type value;


  explicit Type_DMARxOffset(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMARxOffset & setTo(Bar &bar) { bar.set_DMARxOffset(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DMARxOffset & setTo(Bar &bar,AddressType ind) { bar.set_DMARxOffset(ind,*this); return *this; }
 

  template <class T>
  Type_DMARxOffset & set(T to) { to(*this); return *this; }
 

  Type get_Offset() const
   {
    return (value>>0)&0xFFFFu;
   }
 
  Type_DMARxOffset & set_Offset(Type field)
   {
    value=((field&0xFFFFu)<<0)|(value&0xFFFF0000u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Offset(#;)",get_Offset());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Offset(#;)",get_Offset());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DMAEMControl */

enum Bits_DMAEMControl : uint32
 {
  DMAEMControl_Free = 0x00000001u,
  DMAEMControl_Soft = 0x00000002u
 };
 
inline Bits_DMAEMControl operator | (Bits_DMAEMControl a,Bits_DMAEMControl b)
 { return Bits_DMAEMControl(uint32(a)|uint32(b)); }
 
struct Type_DMAEMControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_DMAEMControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMAEMControl & setTo(Bar &bar) { bar.set_DMAEMControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DMAEMControl & setTo(Bar &bar,AddressType ind) { bar.set_DMAEMControl(ind,*this); return *this; }
 

  template <class T>
  Type_DMAEMControl & set(T to) { to(*this); return *this; }
 

  Type_DMAEMControl & setbit(Bits_DMAEMControl bits) { value|=Type(bits); return *this; }
 
  Type_DMAEMControl & setbitIf(bool cond,Bits_DMAEMControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_DMAEMControl & clearbit(Bits_DMAEMControl bits) { value&=~Type(bits); return *this; }
 
  Type_DMAEMControl & clearbitIf(bool cond,Bits_DMAEMControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_DMAEMControl bits) const { return value&bits; }
 
  bool testbit(Bits_DMAEMControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&DMAEMControl_Free )
      {
       if( first )
         {
          Putobj(out,"Free");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Free");
         }
      }

    if( value&DMAEMControl_Soft )
      {
       if( first )
         {
          Putobj(out,"Soft");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Soft");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DMARateControl */

struct Type_DMARateControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_DMARateControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMARateControl & setTo(Bar &bar) { bar.set_DMARateControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DMARateControl & setTo(Bar &bar,AddressType ind) { bar.set_DMARateControl(ind,*this); return *this; }
 

  template <class T>
  Type_DMARateControl & set(T to) { to(*this); return *this; }
 

  Type get_SendCount() const
   {
    return (value>>0)&0x3FFFu;
   }
 
  Type_DMARateControl & set_SendCount(Type field)
   {
    value=((field&0x3FFFu)<<0)|(value&0xFFFFC000u);

    return *this;
   }
 

  Type get_IdleCount() const
   {
    return (value>>16)&0x3FFFu;
   }
 
  Type_DMARateControl & set_IdleCount(Type field)
   {
    value=((field&0x3FFFu)<<16)|(value&0xC000FFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"SendCount(#;)",get_SendCount());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SendCount(#;)",get_SendCount());
      }

    if( first )
      {
       Printf(out,"IdleCount(#;)",get_IdleCount());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"IdleCount(#;)",get_IdleCount());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DMATxIntStatus */

struct Type_DMATxIntStatus
 {
  using Type = uint32 ;

  Type value;


  explicit Type_DMATxIntStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMATxIntStatus & setTo(Bar &bar) { bar.set_DMATxIntStatus(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DMATxIntStatus & setTo(Bar &bar,AddressType ind) { bar.set_DMATxIntStatus(ind,*this); return *this; }
 

  template <class T>
  Type_DMATxIntStatus & set(T to) { to(*this); return *this; }
 

  Type get_TxDone() const
   {
    return (value>>0)&0xFFu;
   }
 
  Type_DMATxIntStatus & set_TxDone(Type field)
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
       Printf(out,"TxDone(#;)",get_TxDone());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"TxDone(#;)",get_TxDone());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_DMAInVector */

using Type_DMAInVector = uint32 ;

/* type Type_DMAEOIVector */

using Type_DMAEOIVector = uint32 ;

/* struct Type_DMARxIntStatus */

struct Type_DMARxIntStatus
 {
  using Type = uint32 ;

  Type value;


  explicit Type_DMARxIntStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMARxIntStatus & setTo(Bar &bar) { bar.set_DMARxIntStatus(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DMARxIntStatus & setTo(Bar &bar,AddressType ind) { bar.set_DMARxIntStatus(ind,*this); return *this; }
 

  template <class T>
  Type_DMARxIntStatus & set(T to) { to(*this); return *this; }
 

  Type get_RxDone() const
   {
    return (value>>0)&0xFFu;
   }
 
  Type_DMARxIntStatus & set_RxDone(Type field)
   {
    value=((field&0xFFu)<<0)|(value&0xFFFFFF00u);

    return *this;
   }
 

  Type get_RxThresh() const
   {
    return (value>>8)&0xFFu;
   }
 
  Type_DMARxIntStatus & set_RxThresh(Type field)
   {
    value=((field&0xFFu)<<8)|(value&0xFFFF00FFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"RxDone(#;)",get_RxDone());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RxDone(#;)",get_RxDone());
      }

    if( first )
      {
       Printf(out,"RxThresh(#;)",get_RxThresh());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RxThresh(#;)",get_RxThresh());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DMAIntStatus */

enum Bits_DMAIntStatus : uint32
 {
  DMAIntStatus_StatCounter = 0x00000001u,
  DMAIntStatus_Host        = 0x00000002u
 };
 
inline Bits_DMAIntStatus operator | (Bits_DMAIntStatus a,Bits_DMAIntStatus b)
 { return Bits_DMAIntStatus(uint32(a)|uint32(b)); }
 
struct Type_DMAIntStatus
 {
  using Type = uint32 ;

  Type value;


  explicit Type_DMAIntStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMAIntStatus & setTo(Bar &bar) { bar.set_DMAIntStatus(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DMAIntStatus & setTo(Bar &bar,AddressType ind) { bar.set_DMAIntStatus(ind,*this); return *this; }
 

  template <class T>
  Type_DMAIntStatus & set(T to) { to(*this); return *this; }
 

  Type_DMAIntStatus & setbit(Bits_DMAIntStatus bits) { value|=Type(bits); return *this; }
 
  Type_DMAIntStatus & setbitIf(bool cond,Bits_DMAIntStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_DMAIntStatus & clearbit(Bits_DMAIntStatus bits) { value&=~Type(bits); return *this; }
 
  Type_DMAIntStatus & clearbitIf(bool cond,Bits_DMAIntStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_DMAIntStatus bits) const { return value&bits; }
 
  bool testbit(Bits_DMAIntStatus bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&DMAIntStatus_StatCounter )
      {
       if( first )
         {
          Putobj(out,"StatCounter");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"StatCounter");
         }
      }

    if( value&DMAIntStatus_Host )
      {
       if( first )
         {
          Putobj(out,"Host");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Host");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DMARxThresh */

struct Type_DMARxThresh
 {
  using Type = uint32 ;

  Type value;


  explicit Type_DMARxThresh(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMARxThresh & setTo(Bar &bar) { bar.set_DMARxThresh(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DMARxThresh & setTo(Bar &bar,AddressType ind) { bar.set_DMARxThresh(ind,*this); return *this; }
 

  template <class T>
  Type_DMARxThresh & set(T to) { to(*this); return *this; }
 

  Type get_Thresh() const
   {
    return (value>>0)&0xFFu;
   }
 
  Type_DMARxThresh & set_Thresh(Type field)
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
       Printf(out,"Thresh(#;)",get_Thresh());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Thresh(#;)",get_Thresh());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DMARxFree */

struct Type_DMARxFree
 {
  using Type = uint32 ;

  Type value;


  explicit Type_DMARxFree(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMARxFree & setTo(Bar &bar) { bar.set_DMARxFree(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DMARxFree & setTo(Bar &bar,AddressType ind) { bar.set_DMARxFree(ind,*this); return *this; }
 

  template <class T>
  Type_DMARxFree & set(T to) { to(*this); return *this; }
 

  Type get_Count() const
   {
    return (value>>0)&0xFFFFu;
   }
 
  Type_DMARxFree & set_Count(Type field)
   {
    value=((field&0xFFFFu)<<0)|(value&0xFFFF0000u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Count(#;)",get_Count());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Count(#;)",get_Count());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_StatCounter */

using Type_StatCounter = uint32 ;

/* type Type_DescPtr */

using Type_DescPtr = uint32 ;

/* struct Type_TimeSyncControl */

enum Bits_TimeSyncControl : uint32
 {
  TimeSyncControl_Enable      = 0x00000001u,
  TimeSyncControl_IntTest     = 0x00000002u,
  TimeSyncControl_Push1Enable = 0x00000100u,
  TimeSyncControl_Push2Enable = 0x00000200u,
  TimeSyncControl_Push3Enable = 0x00000400u,
  TimeSyncControl_Push4Enable = 0x00000800u
 };
 
inline Bits_TimeSyncControl operator | (Bits_TimeSyncControl a,Bits_TimeSyncControl b)
 { return Bits_TimeSyncControl(uint32(a)|uint32(b)); }
 
struct Type_TimeSyncControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_TimeSyncControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TimeSyncControl & setTo(Bar &bar) { bar.set_TimeSyncControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_TimeSyncControl & setTo(Bar &bar,AddressType ind) { bar.set_TimeSyncControl(ind,*this); return *this; }
 

  template <class T>
  Type_TimeSyncControl & set(T to) { to(*this); return *this; }
 

  Type_TimeSyncControl & setbit(Bits_TimeSyncControl bits) { value|=Type(bits); return *this; }
 
  Type_TimeSyncControl & setbitIf(bool cond,Bits_TimeSyncControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TimeSyncControl & clearbit(Bits_TimeSyncControl bits) { value&=~Type(bits); return *this; }
 
  Type_TimeSyncControl & clearbitIf(bool cond,Bits_TimeSyncControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TimeSyncControl bits) const { return value&bits; }
 
  bool testbit(Bits_TimeSyncControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TimeSyncControl_Enable )
      {
       if( first )
         {
          Putobj(out,"Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Enable");
         }
      }

    if( value&TimeSyncControl_IntTest )
      {
       if( first )
         {
          Putobj(out,"IntTest");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"IntTest");
         }
      }

    if( value&TimeSyncControl_Push1Enable )
      {
       if( first )
         {
          Putobj(out,"Push1Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Push1Enable");
         }
      }

    if( value&TimeSyncControl_Push2Enable )
      {
       if( first )
         {
          Putobj(out,"Push2Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Push2Enable");
         }
      }

    if( value&TimeSyncControl_Push3Enable )
      {
       if( first )
         {
          Putobj(out,"Push3Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Push3Enable");
         }
      }

    if( value&TimeSyncControl_Push4Enable )
      {
       if( first )
         {
          Putobj(out,"Push4Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Push4Enable");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_TimeSyncTSPush */

enum Bits_TimeSyncTSPush : uint32
 {
  TimeSyncTSPush_CmdPush = 0x00000001u
 };
 
inline Bits_TimeSyncTSPush operator | (Bits_TimeSyncTSPush a,Bits_TimeSyncTSPush b)
 { return Bits_TimeSyncTSPush(uint32(a)|uint32(b)); }
 
struct Type_TimeSyncTSPush
 {
  using Type = uint32 ;

  Type value;


  explicit Type_TimeSyncTSPush(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TimeSyncTSPush & setTo(Bar &bar) { bar.set_TimeSyncTSPush(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_TimeSyncTSPush & setTo(Bar &bar,AddressType ind) { bar.set_TimeSyncTSPush(ind,*this); return *this; }
 

  template <class T>
  Type_TimeSyncTSPush & set(T to) { to(*this); return *this; }
 

  Type_TimeSyncTSPush & setbit(Bits_TimeSyncTSPush bits) { value|=Type(bits); return *this; }
 
  Type_TimeSyncTSPush & setbitIf(bool cond,Bits_TimeSyncTSPush bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TimeSyncTSPush & clearbit(Bits_TimeSyncTSPush bits) { value&=~Type(bits); return *this; }
 
  Type_TimeSyncTSPush & clearbitIf(bool cond,Bits_TimeSyncTSPush bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TimeSyncTSPush bits) const { return value&bits; }
 
  bool testbit(Bits_TimeSyncTSPush bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TimeSyncTSPush_CmdPush )
      {
       if( first )
         {
          Putobj(out,"CmdPush");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CmdPush");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_TimeSyncTSValue */

using Type_TimeSyncTSValue = uint32 ;

/* struct Type_TimeSyncTSLoad */

enum Bits_TimeSyncTSLoad : uint32
 {
  TimeSyncTSLoad_Enable = 0x00000001u
 };
 
inline Bits_TimeSyncTSLoad operator | (Bits_TimeSyncTSLoad a,Bits_TimeSyncTSLoad b)
 { return Bits_TimeSyncTSLoad(uint32(a)|uint32(b)); }
 
struct Type_TimeSyncTSLoad
 {
  using Type = uint32 ;

  Type value;


  explicit Type_TimeSyncTSLoad(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TimeSyncTSLoad & setTo(Bar &bar) { bar.set_TimeSyncTSLoad(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_TimeSyncTSLoad & setTo(Bar &bar,AddressType ind) { bar.set_TimeSyncTSLoad(ind,*this); return *this; }
 

  template <class T>
  Type_TimeSyncTSLoad & set(T to) { to(*this); return *this; }
 

  Type_TimeSyncTSLoad & setbit(Bits_TimeSyncTSLoad bits) { value|=Type(bits); return *this; }
 
  Type_TimeSyncTSLoad & setbitIf(bool cond,Bits_TimeSyncTSLoad bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TimeSyncTSLoad & clearbit(Bits_TimeSyncTSLoad bits) { value&=~Type(bits); return *this; }
 
  Type_TimeSyncTSLoad & clearbitIf(bool cond,Bits_TimeSyncTSLoad bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TimeSyncTSLoad bits) const { return value&bits; }
 
  bool testbit(Bits_TimeSyncTSLoad bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TimeSyncTSLoad_Enable )
      {
       if( first )
         {
          Putobj(out,"Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Enable");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_TimeSyncIntStatus */

enum Bits_TimeSyncIntStatus : uint32
 {
  TimeSyncIntStatus_Event = 0x00000001u
 };
 
inline Bits_TimeSyncIntStatus operator | (Bits_TimeSyncIntStatus a,Bits_TimeSyncIntStatus b)
 { return Bits_TimeSyncIntStatus(uint32(a)|uint32(b)); }
 
struct Type_TimeSyncIntStatus
 {
  using Type = uint32 ;

  Type value;


  explicit Type_TimeSyncIntStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TimeSyncIntStatus & setTo(Bar &bar) { bar.set_TimeSyncIntStatus(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_TimeSyncIntStatus & setTo(Bar &bar,AddressType ind) { bar.set_TimeSyncIntStatus(ind,*this); return *this; }
 

  template <class T>
  Type_TimeSyncIntStatus & set(T to) { to(*this); return *this; }
 

  Type_TimeSyncIntStatus & setbit(Bits_TimeSyncIntStatus bits) { value|=Type(bits); return *this; }
 
  Type_TimeSyncIntStatus & setbitIf(bool cond,Bits_TimeSyncIntStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TimeSyncIntStatus & clearbit(Bits_TimeSyncIntStatus bits) { value&=~Type(bits); return *this; }
 
  Type_TimeSyncIntStatus & clearbitIf(bool cond,Bits_TimeSyncIntStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TimeSyncIntStatus bits) const { return value&bits; }
 
  bool testbit(Bits_TimeSyncIntStatus bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TimeSyncIntStatus_Event )
      {
       if( first )
         {
          Putobj(out,"Event");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Event");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_TimeSyncEventPop */

enum Bits_TimeSyncEventPop : uint32
 {
  TimeSyncEventPop_CmdPop = 0x00000001u
 };
 
inline Bits_TimeSyncEventPop operator | (Bits_TimeSyncEventPop a,Bits_TimeSyncEventPop b)
 { return Bits_TimeSyncEventPop(uint32(a)|uint32(b)); }
 
struct Type_TimeSyncEventPop
 {
  using Type = uint32 ;

  Type value;


  explicit Type_TimeSyncEventPop(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TimeSyncEventPop & setTo(Bar &bar) { bar.set_TimeSyncEventPop(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_TimeSyncEventPop & setTo(Bar &bar,AddressType ind) { bar.set_TimeSyncEventPop(ind,*this); return *this; }
 

  template <class T>
  Type_TimeSyncEventPop & set(T to) { to(*this); return *this; }
 

  Type_TimeSyncEventPop & setbit(Bits_TimeSyncEventPop bits) { value|=Type(bits); return *this; }
 
  Type_TimeSyncEventPop & setbitIf(bool cond,Bits_TimeSyncEventPop bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TimeSyncEventPop & clearbit(Bits_TimeSyncEventPop bits) { value&=~Type(bits); return *this; }
 
  Type_TimeSyncEventPop & clearbitIf(bool cond,Bits_TimeSyncEventPop bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TimeSyncEventPop bits) const { return value&bits; }
 
  bool testbit(Bits_TimeSyncEventPop bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TimeSyncEventPop_CmdPop )
      {
       if( first )
         {
          Putobj(out,"CmdPop");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CmdPop");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_TimeSyncEventTS */

using Type_TimeSyncEventTS = uint32 ;

/* struct Type_TimeSyncEvent */

enum Field_TimeSyncEvent_EventType : uint32
 {
  TimeSyncEvent_EventType_TSPush         = 0x00u,
  TimeSyncEvent_EventType_TSRollover     = 0x01u,
  TimeSyncEvent_EventType_TSHalfRollover = 0x02u,
  TimeSyncEvent_EventType_HWTSPush       = 0x03u,
  TimeSyncEvent_EventType_EthRx          = 0x04u,
  TimeSyncEvent_EventType_EthTx          = 0x05u
 };
 
struct PrintField_TimeSyncEvent_EventType
 {
  Field_TimeSyncEvent_EventType field;

  explicit PrintField_TimeSyncEvent_EventType(Field_TimeSyncEvent_EventType field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"TSPush"); break;
       case 0x01u : Putobj(out,"TSRollover"); break;
       case 0x02u : Putobj(out,"TSHalfRollover"); break;
       case 0x03u : Putobj(out,"HWTSPush"); break;
       case 0x04u : Putobj(out,"EthRx"); break;
       case 0x05u : Putobj(out,"EthTx"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_TimeSyncEvent_EventType GetTextDesc(Field_TimeSyncEvent_EventType field)
 {
  return PrintField_TimeSyncEvent_EventType(field);
 }
 
struct Type_TimeSyncEvent
 {
  using Type = uint32 ;

  Type value;


  explicit Type_TimeSyncEvent(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TimeSyncEvent & setTo(Bar &bar) { bar.set_TimeSyncEvent(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_TimeSyncEvent & setTo(Bar &bar,AddressType ind) { bar.set_TimeSyncEvent(ind,*this); return *this; }
 

  template <class T>
  Type_TimeSyncEvent & set(T to) { to(*this); return *this; }
 

  Type get_EthSeq() const
   {
    return (value>>0)&0xFFFFu;
   }
 
  Type_TimeSyncEvent & set_EthSeq(Type field)
   {
    value=((field&0xFFFFu)<<0)|(value&0xFFFF0000u);

    return *this;
   }
 

  Type get_MsgType() const
   {
    return (value>>16)&0xFu;
   }
 
  Type_TimeSyncEvent & set_MsgType(Type field)
   {
    value=((field&0xFu)<<16)|(value&0xFFF0FFFFu);

    return *this;
   }
 

  Field_TimeSyncEvent_EventType get_EventType() const
   {
    return Field_TimeSyncEvent_EventType((value>>20)&0xFu);
   }
 
  Type_TimeSyncEvent & set_EventType(Field_TimeSyncEvent_EventType field)
   {
    value=((Type(field)&0xFu)<<20)|(value&0xFF0FFFFFu);

    return *this;
   }
 

  Type get_Port() const
   {
    return (value>>24)&0x1Fu;
   }
 
  Type_TimeSyncEvent & set_Port(Type field)
   {
    value=((field&0x1Fu)<<24)|(value&0xE0FFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"EthSeq(#;)",get_EthSeq());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"EthSeq(#;)",get_EthSeq());
      }

    if( first )
      {
       Printf(out,"MsgType(#;)",get_MsgType());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MsgType(#;)",get_MsgType());
      }

    if( first )
      {
       Printf(out,"EventType(#;)",get_EventType());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"EventType(#;)",get_EventType());
      }

    if( first )
      {
       Printf(out,"Port(#;)",get_Port());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Port(#;)",get_Port());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_ALEControl */

enum Bits_ALEControl : uint32
 {
  ALEControl_EnableRateLimit        = 0x00000001u,
  ALEControl_EnableAuthMode         = 0x00000002u,
  ALEControl_VLANAware              = 0x00000004u,
  ALEControl_TxRateLimit            = 0x00000008u,
  ALEControl_Bypass                 = 0x00000010u,
  ALEControl_EnableOUIDeny          = 0x00000020u,
  ALEControl_EnableVID0Mode         = 0x00000040u,
  ALEControl_LeanNoVID              = 0x00000080u,
  ALEControl_EnableHostUnicastFlood = 0x00000100u,
  ALEControl_AgeOutNow              = 0x20000000u,
  ALEControl_ClearTable             = 0x40000000u,
  ALEControl_EnableALE              = 0x80000000u
 };
 
inline Bits_ALEControl operator | (Bits_ALEControl a,Bits_ALEControl b)
 { return Bits_ALEControl(uint32(a)|uint32(b)); }
 
struct Type_ALEControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_ALEControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ALEControl & setTo(Bar &bar) { bar.set_ALEControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_ALEControl & setTo(Bar &bar,AddressType ind) { bar.set_ALEControl(ind,*this); return *this; }
 

  template <class T>
  Type_ALEControl & set(T to) { to(*this); return *this; }
 

  Type_ALEControl & setbit(Bits_ALEControl bits) { value|=Type(bits); return *this; }
 
  Type_ALEControl & setbitIf(bool cond,Bits_ALEControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_ALEControl & clearbit(Bits_ALEControl bits) { value&=~Type(bits); return *this; }
 
  Type_ALEControl & clearbitIf(bool cond,Bits_ALEControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_ALEControl bits) const { return value&bits; }
 
  bool testbit(Bits_ALEControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&ALEControl_EnableRateLimit )
      {
       if( first )
         {
          Putobj(out,"EnableRateLimit");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EnableRateLimit");
         }
      }

    if( value&ALEControl_EnableAuthMode )
      {
       if( first )
         {
          Putobj(out,"EnableAuthMode");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EnableAuthMode");
         }
      }

    if( value&ALEControl_VLANAware )
      {
       if( first )
         {
          Putobj(out,"VLANAware");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VLANAware");
         }
      }

    if( value&ALEControl_TxRateLimit )
      {
       if( first )
         {
          Putobj(out,"TxRateLimit");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TxRateLimit");
         }
      }

    if( value&ALEControl_Bypass )
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

    if( value&ALEControl_EnableOUIDeny )
      {
       if( first )
         {
          Putobj(out,"EnableOUIDeny");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EnableOUIDeny");
         }
      }

    if( value&ALEControl_EnableVID0Mode )
      {
       if( first )
         {
          Putobj(out,"EnableVID0Mode");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EnableVID0Mode");
         }
      }

    if( value&ALEControl_LeanNoVID )
      {
       if( first )
         {
          Putobj(out,"LeanNoVID");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LeanNoVID");
         }
      }

    if( value&ALEControl_EnableHostUnicastFlood )
      {
       if( first )
         {
          Putobj(out,"EnableHostUnicastFlood");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EnableHostUnicastFlood");
         }
      }

    if( value&ALEControl_AgeOutNow )
      {
       if( first )
         {
          Putobj(out,"AgeOutNow");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AgeOutNow");
         }
      }

    if( value&ALEControl_ClearTable )
      {
       if( first )
         {
          Putobj(out,"ClearTable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ClearTable");
         }
      }

    if( value&ALEControl_EnableALE )
      {
       if( first )
         {
          Putobj(out,"EnableALE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EnableALE");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_ALEPrescale */

struct Type_ALEPrescale
 {
  using Type = uint32 ;

  Type value;


  explicit Type_ALEPrescale(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ALEPrescale & setTo(Bar &bar) { bar.set_ALEPrescale(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_ALEPrescale & setTo(Bar &bar,AddressType ind) { bar.set_ALEPrescale(ind,*this); return *this; }
 

  template <class T>
  Type_ALEPrescale & set(T to) { to(*this); return *this; }
 

  Type get_Div() const
   {
    return (value>>0)&0xFFFFFu;
   }
 
  Type_ALEPrescale & set_Div(Type field)
   {
    value=((field&0xFFFFFu)<<0)|(value&0xFFF00000u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

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
 
/* struct Type_ALEUnknownVLAN */

struct Type_ALEUnknownVLAN
 {
  using Type = uint32 ;

  Type value;


  explicit Type_ALEUnknownVLAN(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ALEUnknownVLAN & setTo(Bar &bar) { bar.set_ALEUnknownVLAN(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_ALEUnknownVLAN & setTo(Bar &bar,AddressType ind) { bar.set_ALEUnknownVLAN(ind,*this); return *this; }
 

  template <class T>
  Type_ALEUnknownVLAN & set(T to) { to(*this); return *this; }
 

  Type get_MemberList() const
   {
    return (value>>0)&0x3Fu;
   }
 
  Type_ALEUnknownVLAN & set_MemberList(Type field)
   {
    value=((field&0x3Fu)<<0)|(value&0xFFFFFFC0u);

    return *this;
   }
 

  Type get_MuticastFloodMask() const
   {
    return (value>>8)&0x3Fu;
   }
 
  Type_ALEUnknownVLAN & set_MuticastFloodMask(Type field)
   {
    value=((field&0x3Fu)<<8)|(value&0xFFFFC0FFu);

    return *this;
   }
 

  Type get_RegMuticastFloodMask() const
   {
    return (value>>16)&0x3Fu;
   }
 
  Type_ALEUnknownVLAN & set_RegMuticastFloodMask(Type field)
   {
    value=((field&0x3Fu)<<16)|(value&0xFFC0FFFFu);

    return *this;
   }
 

  Type get_ForceUntaggedEgress() const
   {
    return (value>>24)&0x3Fu;
   }
 
  Type_ALEUnknownVLAN & set_ForceUntaggedEgress(Type field)
   {
    value=((field&0x3Fu)<<24)|(value&0xC0FFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"MemberList(#;)",get_MemberList());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MemberList(#;)",get_MemberList());
      }

    if( first )
      {
       Printf(out,"MuticastFloodMask(#;)",get_MuticastFloodMask());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MuticastFloodMask(#;)",get_MuticastFloodMask());
      }

    if( first )
      {
       Printf(out,"RegMuticastFloodMask(#;)",get_RegMuticastFloodMask());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RegMuticastFloodMask(#;)",get_RegMuticastFloodMask());
      }

    if( first )
      {
       Printf(out,"ForceUntaggedEgress(#;)",get_ForceUntaggedEgress());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ForceUntaggedEgress(#;)",get_ForceUntaggedEgress());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_ALETableControl */

enum Bits_ALETableControl : uint32
 {
  ALETableControl_Write = 0x80000000u
 };
 
inline Bits_ALETableControl operator | (Bits_ALETableControl a,Bits_ALETableControl b)
 { return Bits_ALETableControl(uint32(a)|uint32(b)); }
 
struct Type_ALETableControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_ALETableControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ALETableControl & setTo(Bar &bar) { bar.set_ALETableControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_ALETableControl & setTo(Bar &bar,AddressType ind) { bar.set_ALETableControl(ind,*this); return *this; }
 

  template <class T>
  Type_ALETableControl & set(T to) { to(*this); return *this; }
 

  Type_ALETableControl & setbit(Bits_ALETableControl bits) { value|=Type(bits); return *this; }
 
  Type_ALETableControl & setbitIf(bool cond,Bits_ALETableControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_ALETableControl & clearbit(Bits_ALETableControl bits) { value&=~Type(bits); return *this; }
 
  Type_ALETableControl & clearbitIf(bool cond,Bits_ALETableControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_ALETableControl bits) const { return value&bits; }
 
  bool testbit(Bits_ALETableControl bits) const { return (value&bits)==Type(bits); }
 

  Type get_Index() const
   {
    return (value>>0)&0x3FFu;
   }
 
  Type_ALETableControl & set_Index(Type field)
   {
    value=((field&0x3FFu)<<0)|(value&0xFFFFFC00u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&ALETableControl_Write )
      {
       if( first )
         {
          Putobj(out,"Write");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Write");
         }
      }

    if( first )
      {
       Printf(out,"Index(#;)",get_Index());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Index(#;)",get_Index());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_ALETableWord0 */

enum Bits_ALETableWord0 : uint32
 {
  ALETableWord0_Secure = 0x00000001u,
  ALETableWord0_Block  = 0x00000002u,
  ALETableWord0_DLR    = 0x00000020u
 };
 
inline Bits_ALETableWord0 operator | (Bits_ALETableWord0 a,Bits_ALETableWord0 b)
 { return Bits_ALETableWord0(uint32(a)|uint32(b)); }
 
struct Type_ALETableWord0
 {
  using Type = uint32 ;

  Type value;


  explicit Type_ALETableWord0(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ALETableWord0 & setTo(Bar &bar) { bar.set_ALETableWord0(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_ALETableWord0 & setTo(Bar &bar,AddressType ind) { bar.set_ALETableWord0(ind,*this); return *this; }
 

  template <class T>
  Type_ALETableWord0 & set(T to) { to(*this); return *this; }
 

  Type_ALETableWord0 & setbit(Bits_ALETableWord0 bits) { value|=Type(bits); return *this; }
 
  Type_ALETableWord0 & setbitIf(bool cond,Bits_ALETableWord0 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_ALETableWord0 & clearbit(Bits_ALETableWord0 bits) { value&=~Type(bits); return *this; }
 
  Type_ALETableWord0 & clearbitIf(bool cond,Bits_ALETableWord0 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_ALETableWord0 bits) const { return value&bits; }
 
  bool testbit(Bits_ALETableWord0 bits) const { return (value&bits)==Type(bits); }
 

  Type get_Port() const
   {
    return (value>>2)&0x3u;
   }
 
  Type_ALETableWord0 & set_Port(Type field)
   {
    value=((field&0x3u)<<2)|(value&0xFFFFFFF3u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&ALETableWord0_Secure )
      {
       if( first )
         {
          Putobj(out,"Secure");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Secure");
         }
      }

    if( value&ALETableWord0_Block )
      {
       if( first )
         {
          Putobj(out,"Block");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Block");
         }
      }

    if( value&ALETableWord0_DLR )
      {
       if( first )
         {
          Putobj(out,"DLR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DLR");
         }
      }

    if( first )
      {
       Printf(out,"Port(#;)",get_Port());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Port(#;)",get_Port());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_ALETableWord1 */

enum Field_ALETableWord1_EntryType : uint32
 {
  ALETableWord1_EntryType_Free        = 0x00u,
  ALETableWord1_EntryType_Address     = 0x01u,
  ALETableWord1_EntryType_VLAN        = 0x02u,
  ALETableWord1_EntryType_AddressVLAN = 0x03u
 };
 
struct PrintField_ALETableWord1_EntryType
 {
  Field_ALETableWord1_EntryType field;

  explicit PrintField_ALETableWord1_EntryType(Field_ALETableWord1_EntryType field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"Free"); break;
       case 0x01u : Putobj(out,"Address"); break;
       case 0x02u : Putobj(out,"VLAN"); break;
       case 0x03u : Putobj(out,"AddressVLAN"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_ALETableWord1_EntryType GetTextDesc(Field_ALETableWord1_EntryType field)
 {
  return PrintField_ALETableWord1_EntryType(field);
 }
 
struct Type_ALETableWord1
 {
  using Type = uint32 ;

  Type value;


  explicit Type_ALETableWord1(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ALETableWord1 & setTo(Bar &bar) { bar.set_ALETableWord1(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_ALETableWord1 & setTo(Bar &bar,AddressType ind) { bar.set_ALETableWord1(ind,*this); return *this; }
 

  template <class T>
  Type_ALETableWord1 & set(T to) { to(*this); return *this; }
 

  Type get_AddressByte1() const
   {
    return (value>>0)&0xFFu;
   }
 
  Type_ALETableWord1 & set_AddressByte1(Type field)
   {
    value=((field&0xFFu)<<0)|(value&0xFFFFFF00u);

    return *this;
   }
 

  Type get_AddressByte0() const
   {
    return (value>>8)&0xFFu;
   }
 
  Type_ALETableWord1 & set_AddressByte0(Type field)
   {
    value=((field&0xFFu)<<8)|(value&0xFFFF00FFu);

    return *this;
   }
 

  Field_ALETableWord1_EntryType get_EntryType() const
   {
    return Field_ALETableWord1_EntryType((value>>28)&0x3u);
   }
 
  Type_ALETableWord1 & set_EntryType(Field_ALETableWord1_EntryType field)
   {
    value=((Type(field)&0x3u)<<28)|(value&0xCFFFFFFFu);

    return *this;
   }
 

  Type get_SubType() const
   {
    return (value>>30)&0x3u;
   }
 
  Type_ALETableWord1 & set_SubType(Type field)
   {
    value=((field&0x3u)<<30)|(value&0x3FFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"AddressByte1(#;)",get_AddressByte1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"AddressByte1(#;)",get_AddressByte1());
      }

    if( first )
      {
       Printf(out,"AddressByte0(#;)",get_AddressByte0());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"AddressByte0(#;)",get_AddressByte0());
      }

    if( first )
      {
       Printf(out,"EntryType(#;)",get_EntryType());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"EntryType(#;)",get_EntryType());
      }

    if( first )
      {
       Printf(out,"SubType(#;)",get_SubType());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SubType(#;)",get_SubType());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_ALETableWord2 */

struct Type_ALETableWord2
 {
  using Type = uint32 ;

  Type value;


  explicit Type_ALETableWord2(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ALETableWord2 & setTo(Bar &bar) { bar.set_ALETableWord2(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_ALETableWord2 & setTo(Bar &bar,AddressType ind) { bar.set_ALETableWord2(ind,*this); return *this; }
 

  template <class T>
  Type_ALETableWord2 & set(T to) { to(*this); return *this; }
 

  Type get_AddressByte5() const
   {
    return (value>>0)&0xFFu;
   }
 
  Type_ALETableWord2 & set_AddressByte5(Type field)
   {
    value=((field&0xFFu)<<0)|(value&0xFFFFFF00u);

    return *this;
   }
 

  Type get_AddressByte4() const
   {
    return (value>>8)&0xFFu;
   }
 
  Type_ALETableWord2 & set_AddressByte4(Type field)
   {
    value=((field&0xFFu)<<8)|(value&0xFFFF00FFu);

    return *this;
   }
 

  Type get_AddressByte3() const
   {
    return (value>>16)&0xFFu;
   }
 
  Type_ALETableWord2 & set_AddressByte3(Type field)
   {
    value=((field&0xFFu)<<16)|(value&0xFF00FFFFu);

    return *this;
   }
 

  Type get_AddressByte2() const
   {
    return (value>>24)&0xFFu;
   }
 
  Type_ALETableWord2 & set_AddressByte2(Type field)
   {
    value=((field&0xFFu)<<24)|(value&0xFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"AddressByte5(#;)",get_AddressByte5());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"AddressByte5(#;)",get_AddressByte5());
      }

    if( first )
      {
       Printf(out,"AddressByte4(#;)",get_AddressByte4());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"AddressByte4(#;)",get_AddressByte4());
      }

    if( first )
      {
       Printf(out,"AddressByte3(#;)",get_AddressByte3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"AddressByte3(#;)",get_AddressByte3());
      }

    if( first )
      {
       Printf(out,"AddressByte2(#;)",get_AddressByte2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"AddressByte2(#;)",get_AddressByte2());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_ALEPortControl */

enum Bits_ALEPortControl : uint32
 {
  ALEPortControl_DropUntagged    = 0x00000004u,
  ALEPortControl_VIDIngressCheck = 0x00000008u,
  ALEPortControl_NoLearn         = 0x00000010u,
  ALEPortControl_NoSAUpdate      = 0x00000020u
 };
 
inline Bits_ALEPortControl operator | (Bits_ALEPortControl a,Bits_ALEPortControl b)
 { return Bits_ALEPortControl(uint32(a)|uint32(b)); }
 
enum Field_ALEPortControl_State : uint32
 {
  ALEPortControl_State_Disabled = 0x00u,
  ALEPortControl_State_Blocked  = 0x01u,
  ALEPortControl_State_Learn    = 0x02u,
  ALEPortControl_State_Forward  = 0x03u
 };
 
struct PrintField_ALEPortControl_State
 {
  Field_ALEPortControl_State field;

  explicit PrintField_ALEPortControl_State(Field_ALEPortControl_State field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"Disabled"); break;
       case 0x01u : Putobj(out,"Blocked"); break;
       case 0x02u : Putobj(out,"Learn"); break;
       case 0x03u : Putobj(out,"Forward"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_ALEPortControl_State GetTextDesc(Field_ALEPortControl_State field)
 {
  return PrintField_ALEPortControl_State(field);
 }
 
struct Type_ALEPortControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_ALEPortControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ALEPortControl & setTo(Bar &bar) { bar.set_ALEPortControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_ALEPortControl & setTo(Bar &bar,AddressType ind) { bar.set_ALEPortControl(ind,*this); return *this; }
 

  template <class T>
  Type_ALEPortControl & set(T to) { to(*this); return *this; }
 

  Type_ALEPortControl & setbit(Bits_ALEPortControl bits) { value|=Type(bits); return *this; }
 
  Type_ALEPortControl & setbitIf(bool cond,Bits_ALEPortControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_ALEPortControl & clearbit(Bits_ALEPortControl bits) { value&=~Type(bits); return *this; }
 
  Type_ALEPortControl & clearbitIf(bool cond,Bits_ALEPortControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_ALEPortControl bits) const { return value&bits; }
 
  bool testbit(Bits_ALEPortControl bits) const { return (value&bits)==Type(bits); }
 

  Field_ALEPortControl_State get_State() const
   {
    return Field_ALEPortControl_State((value>>0)&0x3u);
   }
 
  Type_ALEPortControl & set_State(Field_ALEPortControl_State field)
   {
    value=((Type(field)&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  Type get_MulticastLimit() const
   {
    return (value>>16)&0xFFu;
   }
 
  Type_ALEPortControl & set_MulticastLimit(Type field)
   {
    value=((field&0xFFu)<<16)|(value&0xFF00FFFFu);

    return *this;
   }
 

  Type get_BroadcastLimit() const
   {
    return (value>>24)&0xFFu;
   }
 
  Type_ALEPortControl & set_BroadcastLimit(Type field)
   {
    value=((field&0xFFu)<<24)|(value&0xFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&ALEPortControl_DropUntagged )
      {
       if( first )
         {
          Putobj(out,"DropUntagged");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DropUntagged");
         }
      }

    if( value&ALEPortControl_VIDIngressCheck )
      {
       if( first )
         {
          Putobj(out,"VIDIngressCheck");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VIDIngressCheck");
         }
      }

    if( value&ALEPortControl_NoLearn )
      {
       if( first )
         {
          Putobj(out,"NoLearn");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NoLearn");
         }
      }

    if( value&ALEPortControl_NoSAUpdate )
      {
       if( first )
         {
          Putobj(out,"NoSAUpdate");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NoSAUpdate");
         }
      }

    if( first )
      {
       Printf(out,"State(#;)",get_State());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"State(#;)",get_State());
      }

    if( first )
      {
       Printf(out,"MulticastLimit(#;)",get_MulticastLimit());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MulticastLimit(#;)",get_MulticastLimit());
      }

    if( first )
      {
       Printf(out,"BroadcastLimit(#;)",get_BroadcastLimit());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"BroadcastLimit(#;)",get_BroadcastLimit());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverControl */

enum Bits_SliverControl : uint32
 {
  SliverControl_FullDuplex          = 0x00000001u,
  SliverControl_Loopback            = 0x00000002u,
  SliverControl_MTest               = 0x00000004u,
  SliverControl_RxFlowControlEnable = 0x00000008u,
  SliverControl_TxFlowControlEnable = 0x00000010u,
  SliverControl_GMIIEnable          = 0x00000020u,
  SliverControl_TxPaceEnable        = 0x00000040u,
  SliverControl_GigMode             = 0x00000080u,
  SliverControl_TxShortGapEnable    = 0x00000400u,
  SliverControl_CmdIdle             = 0x00000800u,
  SliverControl_CtrlA               = 0x00008000u,
  SliverControl_CtrlB               = 0x00010000u,
  SliverControl_ForceGig            = 0x00020000u,
  SliverControl_ExtEnable           = 0x00040000u,
  SliverControl_LimitTxShortGap     = 0x00200000u,
  SliverControl_RxErrorPassEnable   = 0x00400000u,
  SliverControl_RxShortPassEnable   = 0x00800000u,
  SliverControl_RxCtrlPassEnable    = 0x01000000u
 };
 
inline Bits_SliverControl operator | (Bits_SliverControl a,Bits_SliverControl b)
 { return Bits_SliverControl(uint32(a)|uint32(b)); }
 
struct Type_SliverControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SliverControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverControl & setTo(Bar &bar) { bar.set_SliverControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SliverControl & setTo(Bar &bar,AddressType ind) { bar.set_SliverControl(ind,*this); return *this; }
 

  template <class T>
  Type_SliverControl & set(T to) { to(*this); return *this; }
 

  Type_SliverControl & setbit(Bits_SliverControl bits) { value|=Type(bits); return *this; }
 
  Type_SliverControl & setbitIf(bool cond,Bits_SliverControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SliverControl & clearbit(Bits_SliverControl bits) { value&=~Type(bits); return *this; }
 
  Type_SliverControl & clearbitIf(bool cond,Bits_SliverControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SliverControl bits) const { return value&bits; }
 
  bool testbit(Bits_SliverControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SliverControl_FullDuplex )
      {
       if( first )
         {
          Putobj(out,"FullDuplex");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FullDuplex");
         }
      }

    if( value&SliverControl_Loopback )
      {
       if( first )
         {
          Putobj(out,"Loopback");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Loopback");
         }
      }

    if( value&SliverControl_MTest )
      {
       if( first )
         {
          Putobj(out,"MTest");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MTest");
         }
      }

    if( value&SliverControl_RxFlowControlEnable )
      {
       if( first )
         {
          Putobj(out,"RxFlowControlEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxFlowControlEnable");
         }
      }

    if( value&SliverControl_TxFlowControlEnable )
      {
       if( first )
         {
          Putobj(out,"TxFlowControlEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TxFlowControlEnable");
         }
      }

    if( value&SliverControl_GMIIEnable )
      {
       if( first )
         {
          Putobj(out,"GMIIEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GMIIEnable");
         }
      }

    if( value&SliverControl_TxPaceEnable )
      {
       if( first )
         {
          Putobj(out,"TxPaceEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TxPaceEnable");
         }
      }

    if( value&SliverControl_GigMode )
      {
       if( first )
         {
          Putobj(out,"GigMode");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GigMode");
         }
      }

    if( value&SliverControl_TxShortGapEnable )
      {
       if( first )
         {
          Putobj(out,"TxShortGapEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TxShortGapEnable");
         }
      }

    if( value&SliverControl_CmdIdle )
      {
       if( first )
         {
          Putobj(out,"CmdIdle");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CmdIdle");
         }
      }

    if( value&SliverControl_CtrlA )
      {
       if( first )
         {
          Putobj(out,"CtrlA");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CtrlA");
         }
      }

    if( value&SliverControl_CtrlB )
      {
       if( first )
         {
          Putobj(out,"CtrlB");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CtrlB");
         }
      }

    if( value&SliverControl_ForceGig )
      {
       if( first )
         {
          Putobj(out,"ForceGig");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ForceGig");
         }
      }

    if( value&SliverControl_ExtEnable )
      {
       if( first )
         {
          Putobj(out,"ExtEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ExtEnable");
         }
      }

    if( value&SliverControl_LimitTxShortGap )
      {
       if( first )
         {
          Putobj(out,"LimitTxShortGap");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LimitTxShortGap");
         }
      }

    if( value&SliverControl_RxErrorPassEnable )
      {
       if( first )
         {
          Putobj(out,"RxErrorPassEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxErrorPassEnable");
         }
      }

    if( value&SliverControl_RxShortPassEnable )
      {
       if( first )
         {
          Putobj(out,"RxShortPassEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxShortPassEnable");
         }
      }

    if( value&SliverControl_RxCtrlPassEnable )
      {
       if( first )
         {
          Putobj(out,"RxCtrlPassEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxCtrlPassEnable");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverStatus */

enum Bits_SliverStatus : uint32
 {
  SliverStatus_TxFlowControlActive = 0x00000001u,
  SliverStatus_RxFlowControlActive = 0x00000002u,
  SliverStatus_ExtFullDuplex       = 0x00000008u,
  SliverStatus_ExtGig              = 0x00000010u,
  SliverStatus_Idle                = 0x80000000u
 };
 
inline Bits_SliverStatus operator | (Bits_SliverStatus a,Bits_SliverStatus b)
 { return Bits_SliverStatus(uint32(a)|uint32(b)); }
 
struct Type_SliverStatus
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SliverStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverStatus & setTo(Bar &bar) { bar.set_SliverStatus(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SliverStatus & setTo(Bar &bar,AddressType ind) { bar.set_SliverStatus(ind,*this); return *this; }
 

  template <class T>
  Type_SliverStatus & set(T to) { to(*this); return *this; }
 

  Type_SliverStatus & setbit(Bits_SliverStatus bits) { value|=Type(bits); return *this; }
 
  Type_SliverStatus & setbitIf(bool cond,Bits_SliverStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SliverStatus & clearbit(Bits_SliverStatus bits) { value&=~Type(bits); return *this; }
 
  Type_SliverStatus & clearbitIf(bool cond,Bits_SliverStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SliverStatus bits) const { return value&bits; }
 
  bool testbit(Bits_SliverStatus bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SliverStatus_TxFlowControlActive )
      {
       if( first )
         {
          Putobj(out,"TxFlowControlActive");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TxFlowControlActive");
         }
      }

    if( value&SliverStatus_RxFlowControlActive )
      {
       if( first )
         {
          Putobj(out,"RxFlowControlActive");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxFlowControlActive");
         }
      }

    if( value&SliverStatus_ExtFullDuplex )
      {
       if( first )
         {
          Putobj(out,"ExtFullDuplex");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ExtFullDuplex");
         }
      }

    if( value&SliverStatus_ExtGig )
      {
       if( first )
         {
          Putobj(out,"ExtGig");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ExtGig");
         }
      }

    if( value&SliverStatus_Idle )
      {
       if( first )
         {
          Putobj(out,"Idle");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Idle");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverSoftReset */

enum Bits_SliverSoftReset : uint32
 {
  SliverSoftReset_Reset = 0x00000001u
 };
 
inline Bits_SliverSoftReset operator | (Bits_SliverSoftReset a,Bits_SliverSoftReset b)
 { return Bits_SliverSoftReset(uint32(a)|uint32(b)); }
 
struct Type_SliverSoftReset
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SliverSoftReset(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverSoftReset & setTo(Bar &bar) { bar.set_SliverSoftReset(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SliverSoftReset & setTo(Bar &bar,AddressType ind) { bar.set_SliverSoftReset(ind,*this); return *this; }
 

  template <class T>
  Type_SliverSoftReset & set(T to) { to(*this); return *this; }
 

  Type_SliverSoftReset & setbit(Bits_SliverSoftReset bits) { value|=Type(bits); return *this; }
 
  Type_SliverSoftReset & setbitIf(bool cond,Bits_SliverSoftReset bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SliverSoftReset & clearbit(Bits_SliverSoftReset bits) { value&=~Type(bits); return *this; }
 
  Type_SliverSoftReset & clearbitIf(bool cond,Bits_SliverSoftReset bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SliverSoftReset bits) const { return value&bits; }
 
  bool testbit(Bits_SliverSoftReset bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SliverSoftReset_Reset )
      {
       if( first )
         {
          Putobj(out,"Reset");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Reset");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverRxMaxLen */

struct Type_SliverRxMaxLen
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SliverRxMaxLen(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverRxMaxLen & setTo(Bar &bar) { bar.set_SliverRxMaxLen(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SliverRxMaxLen & setTo(Bar &bar,AddressType ind) { bar.set_SliverRxMaxLen(ind,*this); return *this; }
 

  template <class T>
  Type_SliverRxMaxLen & set(T to) { to(*this); return *this; }
 

  Type get_Len() const
   {
    return (value>>0)&0x3FFFu;
   }
 
  Type_SliverRxMaxLen & set_Len(Type field)
   {
    value=((field&0x3FFFu)<<0)|(value&0xFFFFC000u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Len(#;)",get_Len());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Len(#;)",get_Len());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverBOFFTest */

struct Type_SliverBOFFTest
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SliverBOFFTest(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverBOFFTest & setTo(Bar &bar) { bar.set_SliverBOFFTest(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SliverBOFFTest & setTo(Bar &bar,AddressType ind) { bar.set_SliverBOFFTest(ind,*this); return *this; }
 

  template <class T>
  Type_SliverBOFFTest & set(T to) { to(*this); return *this; }
 

  Type get_Backoff() const
   {
    return (value>>0)&0x3FFu;
   }
 
  Type_SliverBOFFTest & set_Backoff(Type field)
   {
    value=((field&0x3FFu)<<0)|(value&0xFFFFFC00u);

    return *this;
   }
 

  Type get_CollisionCount() const
   {
    return (value>>12)&0xFu;
   }
 
  Type_SliverBOFFTest & set_CollisionCount(Type field)
   {
    value=((field&0xFu)<<12)|(value&0xFFFF0FFFu);

    return *this;
   }
 

  Type get_Random() const
   {
    return (value>>16)&0x3FFu;
   }
 
  Type_SliverBOFFTest & set_Random(Type field)
   {
    value=((field&0x3FFu)<<16)|(value&0xFC00FFFFu);

    return *this;
   }
 

  Type get_Pace() const
   {
    return (value>>26)&0x1Fu;
   }
 
  Type_SliverBOFFTest & set_Pace(Type field)
   {
    value=((field&0x1Fu)<<26)|(value&0x83FFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Backoff(#;)",get_Backoff());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Backoff(#;)",get_Backoff());
      }

    if( first )
      {
       Printf(out,"CollisionCount(#;)",get_CollisionCount());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CollisionCount(#;)",get_CollisionCount());
      }

    if( first )
      {
       Printf(out,"Random(#;)",get_Random());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Random(#;)",get_Random());
      }

    if( first )
      {
       Printf(out,"Pace(#;)",get_Pace());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pace(#;)",get_Pace());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverRxPause */

struct Type_SliverRxPause
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SliverRxPause(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverRxPause & setTo(Bar &bar) { bar.set_SliverRxPause(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SliverRxPause & setTo(Bar &bar,AddressType ind) { bar.set_SliverRxPause(ind,*this); return *this; }
 

  template <class T>
  Type_SliverRxPause & set(T to) { to(*this); return *this; }
 

  Type get_Timer() const
   {
    return (value>>16)&0xFFFFu;
   }
 
  Type_SliverRxPause & set_Timer(Type field)
   {
    value=((field&0xFFFFu)<<16)|(value&0xFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Timer(#;)",get_Timer());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Timer(#;)",get_Timer());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverTxPause */

struct Type_SliverTxPause
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SliverTxPause(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverTxPause & setTo(Bar &bar) { bar.set_SliverTxPause(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SliverTxPause & setTo(Bar &bar,AddressType ind) { bar.set_SliverTxPause(ind,*this); return *this; }
 

  template <class T>
  Type_SliverTxPause & set(T to) { to(*this); return *this; }
 

  Type get_Timer() const
   {
    return (value>>16)&0xFFFFu;
   }
 
  Type_SliverTxPause & set_Timer(Type field)
   {
    value=((field&0xFFFFu)<<16)|(value&0xFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Timer(#;)",get_Timer());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Timer(#;)",get_Timer());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverEMControl */

enum Bits_SliverEMControl : uint32
 {
  SliverEMControl_Free = 0x00000001u,
  SliverEMControl_Soft = 0x00000002u
 };
 
inline Bits_SliverEMControl operator | (Bits_SliverEMControl a,Bits_SliverEMControl b)
 { return Bits_SliverEMControl(uint32(a)|uint32(b)); }
 
struct Type_SliverEMControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SliverEMControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverEMControl & setTo(Bar &bar) { bar.set_SliverEMControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SliverEMControl & setTo(Bar &bar,AddressType ind) { bar.set_SliverEMControl(ind,*this); return *this; }
 

  template <class T>
  Type_SliverEMControl & set(T to) { to(*this); return *this; }
 

  Type_SliverEMControl & setbit(Bits_SliverEMControl bits) { value|=Type(bits); return *this; }
 
  Type_SliverEMControl & setbitIf(bool cond,Bits_SliverEMControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SliverEMControl & clearbit(Bits_SliverEMControl bits) { value&=~Type(bits); return *this; }
 
  Type_SliverEMControl & clearbitIf(bool cond,Bits_SliverEMControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SliverEMControl bits) const { return value&bits; }
 
  bool testbit(Bits_SliverEMControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SliverEMControl_Free )
      {
       if( first )
         {
          Putobj(out,"Free");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Free");
         }
      }

    if( value&SliverEMControl_Soft )
      {
       if( first )
         {
          Putobj(out,"Soft");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Soft");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverRxPriMap */

struct Type_SliverRxPriMap
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SliverRxPriMap(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverRxPriMap & setTo(Bar &bar) { bar.set_SliverRxPriMap(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SliverRxPriMap & setTo(Bar &bar,AddressType ind) { bar.set_SliverRxPriMap(ind,*this); return *this; }
 

  template <class T>
  Type_SliverRxPriMap & set(T to) { to(*this); return *this; }
 

  Type get_Pri0() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_SliverRxPriMap & set_Pri0(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  Type get_Pri1() const
   {
    return (value>>4)&0x7u;
   }
 
  Type_SliverRxPriMap & set_Pri1(Type field)
   {
    value=((field&0x7u)<<4)|(value&0xFFFFFF8Fu);

    return *this;
   }
 

  Type get_Pri2() const
   {
    return (value>>8)&0x7u;
   }
 
  Type_SliverRxPriMap & set_Pri2(Type field)
   {
    value=((field&0x7u)<<8)|(value&0xFFFFF8FFu);

    return *this;
   }
 

  Type get_Pri3() const
   {
    return (value>>12)&0x7u;
   }
 
  Type_SliverRxPriMap & set_Pri3(Type field)
   {
    value=((field&0x7u)<<12)|(value&0xFFFF8FFFu);

    return *this;
   }
 

  Type get_Pri4() const
   {
    return (value>>16)&0x7u;
   }
 
  Type_SliverRxPriMap & set_Pri4(Type field)
   {
    value=((field&0x7u)<<16)|(value&0xFFF8FFFFu);

    return *this;
   }
 

  Type get_Pri5() const
   {
    return (value>>20)&0x7u;
   }
 
  Type_SliverRxPriMap & set_Pri5(Type field)
   {
    value=((field&0x7u)<<20)|(value&0xFF8FFFFFu);

    return *this;
   }
 

  Type get_Pri6() const
   {
    return (value>>24)&0x7u;
   }
 
  Type_SliverRxPriMap & set_Pri6(Type field)
   {
    value=((field&0x7u)<<24)|(value&0xF8FFFFFFu);

    return *this;
   }
 

  Type get_Pri7() const
   {
    return (value>>28)&0x7u;
   }
 
  Type_SliverRxPriMap & set_Pri7(Type field)
   {
    value=((field&0x7u)<<28)|(value&0x8FFFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Pri0(#;)",get_Pri0());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri0(#;)",get_Pri0());
      }

    if( first )
      {
       Printf(out,"Pri1(#;)",get_Pri1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri1(#;)",get_Pri1());
      }

    if( first )
      {
       Printf(out,"Pri2(#;)",get_Pri2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri2(#;)",get_Pri2());
      }

    if( first )
      {
       Printf(out,"Pri3(#;)",get_Pri3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri3(#;)",get_Pri3());
      }

    if( first )
      {
       Printf(out,"Pri4(#;)",get_Pri4());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri4(#;)",get_Pri4());
      }

    if( first )
      {
       Printf(out,"Pri5(#;)",get_Pri5());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri5(#;)",get_Pri5());
      }

    if( first )
      {
       Printf(out,"Pri6(#;)",get_Pri6());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri6(#;)",get_Pri6());
      }

    if( first )
      {
       Printf(out,"Pri7(#;)",get_Pri7());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri7(#;)",get_Pri7());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverTxGap */

struct Type_SliverTxGap
 {
  using Type = uint32 ;

  Type value;


  explicit Type_SliverTxGap(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverTxGap & setTo(Bar &bar) { bar.set_SliverTxGap(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SliverTxGap & setTo(Bar &bar,AddressType ind) { bar.set_SliverTxGap(ind,*this); return *this; }
 

  template <class T>
  Type_SliverTxGap & set(T to) { to(*this); return *this; }
 

  Type get_Gap() const
   {
    return (value>>0)&0x1FFu;
   }
 
  Type_SliverTxGap & set_Gap(Type field)
   {
    value=((field&0x1FFu)<<0)|(value&0xFFFFFE00u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Gap(#;)",get_Gap());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Gap(#;)",get_Gap());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_WRSoftReset */

enum Bits_WRSoftReset : uint32
 {
  WRSoftReset_Reset = 0x00000001u
 };
 
inline Bits_WRSoftReset operator | (Bits_WRSoftReset a,Bits_WRSoftReset b)
 { return Bits_WRSoftReset(uint32(a)|uint32(b)); }
 
struct Type_WRSoftReset
 {
  using Type = uint32 ;

  Type value;


  explicit Type_WRSoftReset(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_WRSoftReset & setTo(Bar &bar) { bar.set_WRSoftReset(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_WRSoftReset & setTo(Bar &bar,AddressType ind) { bar.set_WRSoftReset(ind,*this); return *this; }
 

  template <class T>
  Type_WRSoftReset & set(T to) { to(*this); return *this; }
 

  Type_WRSoftReset & setbit(Bits_WRSoftReset bits) { value|=Type(bits); return *this; }
 
  Type_WRSoftReset & setbitIf(bool cond,Bits_WRSoftReset bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_WRSoftReset & clearbit(Bits_WRSoftReset bits) { value&=~Type(bits); return *this; }
 
  Type_WRSoftReset & clearbitIf(bool cond,Bits_WRSoftReset bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_WRSoftReset bits) const { return value&bits; }
 
  bool testbit(Bits_WRSoftReset bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&WRSoftReset_Reset )
      {
       if( first )
         {
          Putobj(out,"Reset");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Reset");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_WRControl */

enum Field_WRControl_IdleMode : uint32
 {
  WRControl_IdleMode_ForceIdle = 0x00u,
  WRControl_IdleMode_NoIdle    = 0x01u
 };
 
struct PrintField_WRControl_IdleMode
 {
  Field_WRControl_IdleMode field;

  explicit PrintField_WRControl_IdleMode(Field_WRControl_IdleMode field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"ForceIdle"); break;
       case 0x01u : Putobj(out,"NoIdle"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_WRControl_IdleMode GetTextDesc(Field_WRControl_IdleMode field)
 {
  return PrintField_WRControl_IdleMode(field);
 }
 
enum Field_WRControl_StandbyMode : uint32
 {
  WRControl_StandbyMode_ForceStandby = 0x00u,
  WRControl_StandbyMode_NoStandby    = 0x01u
 };
 
struct PrintField_WRControl_StandbyMode
 {
  Field_WRControl_StandbyMode field;

  explicit PrintField_WRControl_StandbyMode(Field_WRControl_StandbyMode field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"ForceStandby"); break;
       case 0x01u : Putobj(out,"NoStandby"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_WRControl_StandbyMode GetTextDesc(Field_WRControl_StandbyMode field)
 {
  return PrintField_WRControl_StandbyMode(field);
 }
 
struct Type_WRControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_WRControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_WRControl & setTo(Bar &bar) { bar.set_WRControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_WRControl & setTo(Bar &bar,AddressType ind) { bar.set_WRControl(ind,*this); return *this; }
 

  template <class T>
  Type_WRControl & set(T to) { to(*this); return *this; }
 

  Field_WRControl_IdleMode get_IdleMode() const
   {
    return Field_WRControl_IdleMode((value>>0)&0x3u);
   }
 
  Type_WRControl & set_IdleMode(Field_WRControl_IdleMode field)
   {
    value=((Type(field)&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  Field_WRControl_StandbyMode get_StandbyMode() const
   {
    return Field_WRControl_StandbyMode((value>>2)&0x3u);
   }
 
  Type_WRControl & set_StandbyMode(Field_WRControl_StandbyMode field)
   {
    value=((Type(field)&0x3u)<<2)|(value&0xFFFFFFF3u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"IdleMode(#;)",get_IdleMode());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"IdleMode(#;)",get_IdleMode());
      }

    if( first )
      {
       Printf(out,"StandbyMode(#;)",get_StandbyMode());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"StandbyMode(#;)",get_StandbyMode());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_WRIntControl */

enum Bits_WRIntControl : uint32
 {
  WRIntControl_C0RxPace = 0x00010000u,
  WRIntControl_C0TxPace = 0x00020000u,
  WRIntControl_C1RxPace = 0x00040000u,
  WRIntControl_C1TxPace = 0x00080000u,
  WRIntControl_C2RxPace = 0x00100000u,
  WRIntControl_C2Txpace = 0x00200000u,
  WRIntControl_IntTest  = 0x80000000u
 };
 
inline Bits_WRIntControl operator | (Bits_WRIntControl a,Bits_WRIntControl b)
 { return Bits_WRIntControl(uint32(a)|uint32(b)); }
 
struct Type_WRIntControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_WRIntControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_WRIntControl & setTo(Bar &bar) { bar.set_WRIntControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_WRIntControl & setTo(Bar &bar,AddressType ind) { bar.set_WRIntControl(ind,*this); return *this; }
 

  template <class T>
  Type_WRIntControl & set(T to) { to(*this); return *this; }
 

  Type_WRIntControl & setbit(Bits_WRIntControl bits) { value|=Type(bits); return *this; }
 
  Type_WRIntControl & setbitIf(bool cond,Bits_WRIntControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_WRIntControl & clearbit(Bits_WRIntControl bits) { value&=~Type(bits); return *this; }
 
  Type_WRIntControl & clearbitIf(bool cond,Bits_WRIntControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_WRIntControl bits) const { return value&bits; }
 
  bool testbit(Bits_WRIntControl bits) const { return (value&bits)==Type(bits); }
 

  Type get_Prescale() const
   {
    return (value>>0)&0xFFFu;
   }
 
  Type_WRIntControl & set_Prescale(Type field)
   {
    value=((field&0xFFFu)<<0)|(value&0xFFFFF000u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&WRIntControl_C0RxPace )
      {
       if( first )
         {
          Putobj(out,"C0RxPace");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"C0RxPace");
         }
      }

    if( value&WRIntControl_C0TxPace )
      {
       if( first )
         {
          Putobj(out,"C0TxPace");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"C0TxPace");
         }
      }

    if( value&WRIntControl_C1RxPace )
      {
       if( first )
         {
          Putobj(out,"C1RxPace");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"C1RxPace");
         }
      }

    if( value&WRIntControl_C1TxPace )
      {
       if( first )
         {
          Putobj(out,"C1TxPace");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"C1TxPace");
         }
      }

    if( value&WRIntControl_C2RxPace )
      {
       if( first )
         {
          Putobj(out,"C2RxPace");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"C2RxPace");
         }
      }

    if( value&WRIntControl_C2Txpace )
      {
       if( first )
         {
          Putobj(out,"C2Txpace");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"C2Txpace");
         }
      }

    if( value&WRIntControl_IntTest )
      {
       if( first )
         {
          Putobj(out,"IntTest");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"IntTest");
         }
      }

    if( first )
      {
       Printf(out,"Prescale(#;)",get_Prescale());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Prescale(#;)",get_Prescale());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_WRC0RxThreshEnable */

using Type_WRC0RxThreshEnable = uint32 ;

/* type Type_WRC0RxEnable */

using Type_WRC0RxEnable = uint32 ;

/* type Type_WRC0TxEnable */

using Type_WRC0TxEnable = uint32 ;

/* type Type_WRC0MiscEnable */

using Type_WRC0MiscEnable = uint32 ;

/* type Type_WRC0RxThreshStatus */

using Type_WRC0RxThreshStatus = uint32 ;

/* type Type_WRC0RxStatus */

using Type_WRC0RxStatus = uint32 ;

/* type Type_WRC0TxStatus */

using Type_WRC0TxStatus = uint32 ;

/* type Type_WRC0MiscStatus */

using Type_WRC0MiscStatus = uint32 ;

/* struct Type_WRC0RxIntLim */

struct Type_WRC0RxIntLim
 {
  using Type = uint32 ;

  Type value;


  explicit Type_WRC0RxIntLim(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_WRC0RxIntLim & setTo(Bar &bar) { bar.set_WRC0RxIntLim(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_WRC0RxIntLim & setTo(Bar &bar,AddressType ind) { bar.set_WRC0RxIntLim(ind,*this); return *this; }
 

  template <class T>
  Type_WRC0RxIntLim & set(T to) { to(*this); return *this; }
 

  Type get_Lim() const
   {
    return (value>>0)&0x3Fu;
   }
 
  Type_WRC0RxIntLim & set_Lim(Type field)
   {
    value=((field&0x3Fu)<<0)|(value&0xFFFFFFC0u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Lim(#;)",get_Lim());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Lim(#;)",get_Lim());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_WRC0TxIntLim */

struct Type_WRC0TxIntLim
 {
  using Type = uint32 ;

  Type value;


  explicit Type_WRC0TxIntLim(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_WRC0TxIntLim & setTo(Bar &bar) { bar.set_WRC0TxIntLim(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_WRC0TxIntLim & setTo(Bar &bar,AddressType ind) { bar.set_WRC0TxIntLim(ind,*this); return *this; }
 

  template <class T>
  Type_WRC0TxIntLim & set(T to) { to(*this); return *this; }
 

  Type get_Lim() const
   {
    return (value>>0)&0x3Fu;
   }
 
  Type_WRC0TxIntLim & set_Lim(Type field)
   {
    value=((field&0x3Fu)<<0)|(value&0xFFFFFFC0u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Lim(#;)",get_Lim());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Lim(#;)",get_Lim());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_WRRGMIIStatus */

enum Bits_WRRGMIIStatus : uint32
 {
  WRRGMIIStatus_Link1       = 0x00000001u,
  WRRGMIIStatus_FullDuplex1 = 0x00000008u,
  WRRGMIIStatus_Link2       = 0x00000010u,
  WRRGMIIStatus_FullDuplex2 = 0x00000080u
 };
 
inline Bits_WRRGMIIStatus operator | (Bits_WRRGMIIStatus a,Bits_WRRGMIIStatus b)
 { return Bits_WRRGMIIStatus(uint32(a)|uint32(b)); }
 
struct Type_WRRGMIIStatus
 {
  using Type = uint32 ;

  Type value;


  explicit Type_WRRGMIIStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_WRRGMIIStatus & setTo(Bar &bar) { bar.set_WRRGMIIStatus(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_WRRGMIIStatus & setTo(Bar &bar,AddressType ind) { bar.set_WRRGMIIStatus(ind,*this); return *this; }
 

  template <class T>
  Type_WRRGMIIStatus & set(T to) { to(*this); return *this; }
 

  Type_WRRGMIIStatus & setbit(Bits_WRRGMIIStatus bits) { value|=Type(bits); return *this; }
 
  Type_WRRGMIIStatus & setbitIf(bool cond,Bits_WRRGMIIStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_WRRGMIIStatus & clearbit(Bits_WRRGMIIStatus bits) { value&=~Type(bits); return *this; }
 
  Type_WRRGMIIStatus & clearbitIf(bool cond,Bits_WRRGMIIStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_WRRGMIIStatus bits) const { return value&bits; }
 
  bool testbit(Bits_WRRGMIIStatus bits) const { return (value&bits)==Type(bits); }
 

  Type get_Speed1() const
   {
    return (value>>1)&0x3u;
   }
 
  Type_WRRGMIIStatus & set_Speed1(Type field)
   {
    value=((field&0x3u)<<1)|(value&0xFFFFFFF9u);

    return *this;
   }
 

  Type get_Speed2() const
   {
    return (value>>5)&0x3u;
   }
 
  Type_WRRGMIIStatus & set_Speed2(Type field)
   {
    value=((field&0x3u)<<5)|(value&0xFFFFFF9Fu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&WRRGMIIStatus_Link1 )
      {
       if( first )
         {
          Putobj(out,"Link1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Link1");
         }
      }

    if( value&WRRGMIIStatus_FullDuplex1 )
      {
       if( first )
         {
          Putobj(out,"FullDuplex1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FullDuplex1");
         }
      }

    if( value&WRRGMIIStatus_Link2 )
      {
       if( first )
         {
          Putobj(out,"Link2");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Link2");
         }
      }

    if( value&WRRGMIIStatus_FullDuplex2 )
      {
       if( first )
         {
          Putobj(out,"FullDuplex2");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FullDuplex2");
         }
      }

    if( first )
      {
       Printf(out,"Speed1(#;)",get_Speed1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Speed1(#;)",get_Speed1());
      }

    if( first )
      {
       Printf(out,"Speed2(#;)",get_Speed2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Speed2(#;)",get_Speed2());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MDIOControl */

enum Bits_MDIOControl : uint32
 {
  MDIOControl_IntTestEnable   = 0x00020000u,
  MDIOControl_FaultEnable     = 0x00040000u,
  MDIOControl_FaultState      = 0x00080000u,
  MDIOControl_PreambleDisable = 0x00100000u,
  MDIOControl_Enable          = 0x40000000u,
  MDIOControl_Idle            = 0x80000000u
 };
 
inline Bits_MDIOControl operator | (Bits_MDIOControl a,Bits_MDIOControl b)
 { return Bits_MDIOControl(uint32(a)|uint32(b)); }
 
struct Type_MDIOControl
 {
  using Type = uint32 ;

  Type value;


  explicit Type_MDIOControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MDIOControl & setTo(Bar &bar) { bar.set_MDIOControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_MDIOControl & setTo(Bar &bar,AddressType ind) { bar.set_MDIOControl(ind,*this); return *this; }
 

  template <class T>
  Type_MDIOControl & set(T to) { to(*this); return *this; }
 

  Type_MDIOControl & setbit(Bits_MDIOControl bits) { value|=Type(bits); return *this; }
 
  Type_MDIOControl & setbitIf(bool cond,Bits_MDIOControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MDIOControl & clearbit(Bits_MDIOControl bits) { value&=~Type(bits); return *this; }
 
  Type_MDIOControl & clearbitIf(bool cond,Bits_MDIOControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MDIOControl bits) const { return value&bits; }
 
  bool testbit(Bits_MDIOControl bits) const { return (value&bits)==Type(bits); }
 

  Type get_ClockDiv() const
   {
    return (value>>0)&0xFFFFu;
   }
 
  Type_MDIOControl & set_ClockDiv(Type field)
   {
    value=((field&0xFFFFu)<<0)|(value&0xFFFF0000u);

    return *this;
   }
 

  Type get_LastChannel() const
   {
    return (value>>24)&0x1Fu;
   }
 
  Type_MDIOControl & set_LastChannel(Type field)
   {
    value=((field&0x1Fu)<<24)|(value&0xE0FFFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MDIOControl_IntTestEnable )
      {
       if( first )
         {
          Putobj(out,"IntTestEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"IntTestEnable");
         }
      }

    if( value&MDIOControl_FaultEnable )
      {
       if( first )
         {
          Putobj(out,"FaultEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FaultEnable");
         }
      }

    if( value&MDIOControl_FaultState )
      {
       if( first )
         {
          Putobj(out,"FaultState");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FaultState");
         }
      }

    if( value&MDIOControl_PreambleDisable )
      {
       if( first )
         {
          Putobj(out,"PreambleDisable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PreambleDisable");
         }
      }

    if( value&MDIOControl_Enable )
      {
       if( first )
         {
          Putobj(out,"Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Enable");
         }
      }

    if( value&MDIOControl_Idle )
      {
       if( first )
         {
          Putobj(out,"Idle");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Idle");
         }
      }

    if( first )
      {
       Printf(out,"ClockDiv(#;)",get_ClockDiv());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ClockDiv(#;)",get_ClockDiv());
      }

    if( first )
      {
       Printf(out,"LastChannel(#;)",get_LastChannel());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"LastChannel(#;)",get_LastChannel());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_MDIOAlive */

using Type_MDIOAlive = uint32 ;

/* type Type_MDIOLink */

using Type_MDIOLink = uint32 ;

/* type Type_MDIOLinkIntStatus */

using Type_MDIOLinkIntStatus = uint32 ;

/* type Type_MDIOUserIntStatus */

using Type_MDIOUserIntStatus = uint32 ;

/* struct Type_MDIOUserAccess */

enum Bits_MDIOUserAccess : uint32
 {
  MDIOUserAccess_Ack   = 0x20000000u,
  MDIOUserAccess_Write = 0x40000000u,
  MDIOUserAccess_Go    = 0x80000000u
 };
 
inline Bits_MDIOUserAccess operator | (Bits_MDIOUserAccess a,Bits_MDIOUserAccess b)
 { return Bits_MDIOUserAccess(uint32(a)|uint32(b)); }
 
struct Type_MDIOUserAccess
 {
  using Type = uint32 ;

  Type value;


  explicit Type_MDIOUserAccess(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MDIOUserAccess & setTo(Bar &bar) { bar.set_MDIOUserAccess(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_MDIOUserAccess & setTo(Bar &bar,AddressType ind) { bar.set_MDIOUserAccess(ind,*this); return *this; }
 

  template <class T>
  Type_MDIOUserAccess & set(T to) { to(*this); return *this; }
 

  Type_MDIOUserAccess & setbit(Bits_MDIOUserAccess bits) { value|=Type(bits); return *this; }
 
  Type_MDIOUserAccess & setbitIf(bool cond,Bits_MDIOUserAccess bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MDIOUserAccess & clearbit(Bits_MDIOUserAccess bits) { value&=~Type(bits); return *this; }
 
  Type_MDIOUserAccess & clearbitIf(bool cond,Bits_MDIOUserAccess bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MDIOUserAccess bits) const { return value&bits; }
 
  bool testbit(Bits_MDIOUserAccess bits) const { return (value&bits)==Type(bits); }
 

  Type get_Data() const
   {
    return (value>>0)&0xFFFFu;
   }
 
  Type_MDIOUserAccess & set_Data(Type field)
   {
    value=((field&0xFFFFu)<<0)|(value&0xFFFF0000u);

    return *this;
   }
 

  Type get_Phy() const
   {
    return (value>>16)&0x1Fu;
   }
 
  Type_MDIOUserAccess & set_Phy(Type field)
   {
    value=((field&0x1Fu)<<16)|(value&0xFFE0FFFFu);

    return *this;
   }
 

  Type get_Reg() const
   {
    return (value>>21)&0x1Fu;
   }
 
  Type_MDIOUserAccess & set_Reg(Type field)
   {
    value=((field&0x1Fu)<<21)|(value&0xFC1FFFFFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MDIOUserAccess_Ack )
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

    if( value&MDIOUserAccess_Write )
      {
       if( first )
         {
          Putobj(out,"Write");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Write");
         }
      }

    if( value&MDIOUserAccess_Go )
      {
       if( first )
         {
          Putobj(out,"Go");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Go");
         }
      }

    if( first )
      {
       Printf(out,"Data(#;)",get_Data());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Data(#;)",get_Data());
      }

    if( first )
      {
       Printf(out,"Phy(#;)",get_Phy());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Phy(#;)",get_Phy());
      }

    if( first )
      {
       Printf(out,"Reg(#;)",get_Reg());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Reg(#;)",get_Reg());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MDIOUserPhySel */

enum Bits_MDIOUserPhySel : uint32
 {
  MDIOUserPhySel_IntEnable = 0x00000040u,
  MDIOUserPhySel_ExtSource = 0x00000080u
 };
 
inline Bits_MDIOUserPhySel operator | (Bits_MDIOUserPhySel a,Bits_MDIOUserPhySel b)
 { return Bits_MDIOUserPhySel(uint32(a)|uint32(b)); }
 
struct Type_MDIOUserPhySel
 {
  using Type = uint32 ;

  Type value;


  explicit Type_MDIOUserPhySel(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MDIOUserPhySel & setTo(Bar &bar) { bar.set_MDIOUserPhySel(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_MDIOUserPhySel & setTo(Bar &bar,AddressType ind) { bar.set_MDIOUserPhySel(ind,*this); return *this; }
 

  template <class T>
  Type_MDIOUserPhySel & set(T to) { to(*this); return *this; }
 

  Type_MDIOUserPhySel & setbit(Bits_MDIOUserPhySel bits) { value|=Type(bits); return *this; }
 
  Type_MDIOUserPhySel & setbitIf(bool cond,Bits_MDIOUserPhySel bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MDIOUserPhySel & clearbit(Bits_MDIOUserPhySel bits) { value&=~Type(bits); return *this; }
 
  Type_MDIOUserPhySel & clearbitIf(bool cond,Bits_MDIOUserPhySel bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MDIOUserPhySel bits) const { return value&bits; }
 
  bool testbit(Bits_MDIOUserPhySel bits) const { return (value&bits)==Type(bits); }
 

  Type get_Phy() const
   {
    return (value>>0)&0x1Fu;
   }
 
  Type_MDIOUserPhySel & set_Phy(Type field)
   {
    value=((field&0x1Fu)<<0)|(value&0xFFFFFFE0u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MDIOUserPhySel_IntEnable )
      {
       if( first )
         {
          Putobj(out,"IntEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"IntEnable");
         }
      }

    if( value&MDIOUserPhySel_ExtSource )
      {
       if( first )
         {
          Putobj(out,"ExtSource");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ExtSource");
         }
      }

    if( first )
      {
       Printf(out,"Phy(#;)",get_Phy());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Phy(#;)",get_Phy());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct SwitchBar<RW> */

template <class RW>
struct SwitchBar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit SwitchBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- SwitchControl

  Type_SwitchControl get_SwitchControl() { return Type_SwitchControl(rw.template get<uint32>(0x4u)); }
 
  void set_SwitchControl(Type_SwitchControl value) { rw.set(0x4u,value.value); }
 
  Setter<Type_SwitchControl> to_SwitchControl() { return Setter<Type_SwitchControl>(rw,0x4u); }
 
  static Type_SwitchControl null_SwitchControl() { return Type_SwitchControl(0); }
 
  static Type_SwitchControl ones_SwitchControl() { return Type_SwitchControl(Type_SwitchControl::Type(-1)); }
 
  //--- SwitchSoftReset

  Type_SwitchSoftReset get_SwitchSoftReset() { return Type_SwitchSoftReset(rw.template get<uint32>(0x8u)); }
 
  void set_SwitchSoftReset(Type_SwitchSoftReset value) { rw.set(0x8u,value.value); }
 
  Setter<Type_SwitchSoftReset> to_SwitchSoftReset() { return Setter<Type_SwitchSoftReset>(rw,0x8u); }
 
  static Type_SwitchSoftReset null_SwitchSoftReset() { return Type_SwitchSoftReset(0); }
 
  static Type_SwitchSoftReset ones_SwitchSoftReset() { return Type_SwitchSoftReset(Type_SwitchSoftReset::Type(-1)); }
 
  //--- SwitchStatPort

  Type_SwitchStatPort get_SwitchStatPort() { return Type_SwitchStatPort(rw.template get<uint32>(0xCu)); }
 
  void set_SwitchStatPort(Type_SwitchStatPort value) { rw.set(0xCu,value.value); }
 
  Setter<Type_SwitchStatPort> to_SwitchStatPort() { return Setter<Type_SwitchStatPort>(rw,0xCu); }
 
  static Type_SwitchStatPort null_SwitchStatPort() { return Type_SwitchStatPort(0); }
 
  static Type_SwitchStatPort ones_SwitchStatPort() { return Type_SwitchStatPort(Type_SwitchStatPort::Type(-1)); }
 
  //--- SwitchTxPriType

  Type_SwitchTxPriType get_SwitchTxPriType() { return Type_SwitchTxPriType(rw.template get<uint32>(0x10u)); }
 
  void set_SwitchTxPriType(Type_SwitchTxPriType value) { rw.set(0x10u,value.value); }
 
  Setter<Type_SwitchTxPriType> to_SwitchTxPriType() { return Setter<Type_SwitchTxPriType>(rw,0x10u); }
 
  static Type_SwitchTxPriType null_SwitchTxPriType() { return Type_SwitchTxPriType(0); }
 
  static Type_SwitchTxPriType ones_SwitchTxPriType() { return Type_SwitchTxPriType(Type_SwitchTxPriType::Type(-1)); }
 
  //--- SwitchCmdIdle

  Type_SwitchCmdIdle get_SwitchCmdIdle() { return Type_SwitchCmdIdle(rw.template get<uint32>(0x14u)); }
 
  void set_SwitchCmdIdle(Type_SwitchCmdIdle value) { rw.set(0x14u,value.value); }
 
  Setter<Type_SwitchCmdIdle> to_SwitchCmdIdle() { return Setter<Type_SwitchCmdIdle>(rw,0x14u); }
 
  static Type_SwitchCmdIdle null_SwitchCmdIdle() { return Type_SwitchCmdIdle(0); }
 
  static Type_SwitchCmdIdle ones_SwitchCmdIdle() { return Type_SwitchCmdIdle(Type_SwitchCmdIdle::Type(-1)); }
 
  //--- SwitchRate

  Type_SwitchRate get_SwitchRate() { return Type_SwitchRate(rw.template get<uint32>(0x18u)); }
 
  void set_SwitchRate(Type_SwitchRate value) { rw.set(0x18u,value.value); }
 
  Setter<Type_SwitchRate> to_SwitchRate() { return Setter<Type_SwitchRate>(rw,0x18u); }
 
  static Type_SwitchRate null_SwitchRate() { return Type_SwitchRate(0); }
 
  static Type_SwitchRate ones_SwitchRate() { return Type_SwitchRate(Type_SwitchRate::Type(-1)); }
 
  //--- SwitchTxShortGap

  Type_SwitchTxShortGap get_SwitchTxShortGap() { return Type_SwitchTxShortGap(rw.template get<uint32>(0x1Cu)); }
 
  void set_SwitchTxShortGap(Type_SwitchTxShortGap value) { rw.set(0x1Cu,value.value); }
 
  Setter<Type_SwitchTxShortGap> to_SwitchTxShortGap() { return Setter<Type_SwitchTxShortGap>(rw,0x1Cu); }
 
  static Type_SwitchTxShortGap null_SwitchTxShortGap() { return Type_SwitchTxShortGap(0); }
 
  static Type_SwitchTxShortGap ones_SwitchTxShortGap() { return Type_SwitchTxShortGap(Type_SwitchTxShortGap::Type(-1)); }
 
  //--- SwitchTxStart

  Type_SwitchTxStart get_SwitchTxStart() { return Type_SwitchTxStart(rw.template get<uint32>(0x20u)); }
 
  void set_SwitchTxStart(Type_SwitchTxStart value) { rw.set(0x20u,value.value); }
 
  Setter<Type_SwitchTxStart> to_SwitchTxStart() { return Setter<Type_SwitchTxStart>(rw,0x20u); }
 
  static Type_SwitchTxStart null_SwitchTxStart() { return Type_SwitchTxStart(0); }
 
  static Type_SwitchTxStart ones_SwitchTxStart() { return Type_SwitchTxStart(Type_SwitchTxStart::Type(-1)); }
 
  //--- SwitchRxFlowControl

  Type_SwitchRxFlowControl get_SwitchRxFlowControl() { return Type_SwitchRxFlowControl(rw.template get<uint32>(0x24u)); }
 
  void set_SwitchRxFlowControl(Type_SwitchRxFlowControl value) { rw.set(0x24u,value.value); }
 
  Setter<Type_SwitchRxFlowControl> to_SwitchRxFlowControl() { return Setter<Type_SwitchRxFlowControl>(rw,0x24u); }
 
  static Type_SwitchRxFlowControl null_SwitchRxFlowControl() { return Type_SwitchRxFlowControl(0); }
 
  static Type_SwitchRxFlowControl ones_SwitchRxFlowControl() { return Type_SwitchRxFlowControl(Type_SwitchRxFlowControl::Type(-1)); }
 
  //--- SwitchLType

  Type_SwitchLType get_SwitchLType() { return Type_SwitchLType(rw.template get<uint32>(0x28u)); }
 
  void set_SwitchLType(Type_SwitchLType value) { rw.set(0x28u,value.value); }
 
  Setter<Type_SwitchLType> to_SwitchLType() { return Setter<Type_SwitchLType>(rw,0x28u); }
 
  static Type_SwitchLType null_SwitchLType() { return Type_SwitchLType(0); }
 
  static Type_SwitchLType ones_SwitchLType() { return Type_SwitchLType(Type_SwitchLType::Type(-1)); }
 
  //--- SwitchTSLType

  Type_SwitchTSLType get_SwitchTSLType() { return Type_SwitchTSLType(rw.template get<uint32>(0x2Cu)); }
 
  void set_SwitchTSLType(Type_SwitchTSLType value) { rw.set(0x2Cu,value.value); }
 
  Setter<Type_SwitchTSLType> to_SwitchTSLType() { return Setter<Type_SwitchTSLType>(rw,0x2Cu); }
 
  static Type_SwitchTSLType null_SwitchTSLType() { return Type_SwitchTSLType(0); }
 
  static Type_SwitchTSLType ones_SwitchTSLType() { return Type_SwitchTSLType(Type_SwitchTSLType::Type(-1)); }
 
  //--- SwitchDLRLType

  Type_SwitchDLRLType get_SwitchDLRLType() { return Type_SwitchDLRLType(rw.template get<uint32>(0x30u)); }
 
  void set_SwitchDLRLType(Type_SwitchDLRLType value) { rw.set(0x30u,value.value); }
 
  Setter<Type_SwitchDLRLType> to_SwitchDLRLType() { return Setter<Type_SwitchDLRLType>(rw,0x30u); }
 
  static Type_SwitchDLRLType null_SwitchDLRLType() { return Type_SwitchDLRLType(0); }
 
  static Type_SwitchDLRLType ones_SwitchDLRLType() { return Type_SwitchDLRLType(Type_SwitchDLRLType::Type(-1)); }
 
 };
 
/* struct Port0Bar<RW> */

template <class RW>
struct Port0Bar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit Port0Bar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- PortControl

  Type_PortControl get_PortControl() { return Type_PortControl(rw.template get<uint32>(0x0u)); }
 
  void set_PortControl(Type_PortControl value) { rw.set(0x0u,value.value); }
 
  Setter<Type_PortControl> to_PortControl() { return Setter<Type_PortControl>(rw,0x0u); }
 
  static Type_PortControl null_PortControl() { return Type_PortControl(0); }
 
  static Type_PortControl ones_PortControl() { return Type_PortControl(Type_PortControl::Type(-1)); }
 
  //--- PortFIFOLen

  Type_PortFIFOLen get_PortFIFOLen() { return Type_PortFIFOLen(rw.template get<uint32>(0x8u)); }
 
  void set_PortFIFOLen(Type_PortFIFOLen value) { rw.set(0x8u,value.value); }
 
  Setter<Type_PortFIFOLen> to_PortFIFOLen() { return Setter<Type_PortFIFOLen>(rw,0x8u); }
 
  static Type_PortFIFOLen null_PortFIFOLen() { return Type_PortFIFOLen(0); }
 
  static Type_PortFIFOLen ones_PortFIFOLen() { return Type_PortFIFOLen(Type_PortFIFOLen::Type(-1)); }
 
  //--- PortFIFOUse

  Type_PortFIFOUse get_PortFIFOUse() { return Type_PortFIFOUse(rw.template get<uint32>(0xCu)); }
 
  static Type_PortFIFOUse null_PortFIFOUse() { return Type_PortFIFOUse(0); }
 
  static Type_PortFIFOUse ones_PortFIFOUse() { return Type_PortFIFOUse(Type_PortFIFOUse::Type(-1)); }
 
  //--- PortTxFIFOControl

  Type_PortTxFIFOControl get_PortTxFIFOControl() { return Type_PortTxFIFOControl(rw.template get<uint32>(0x10u)); }
 
  void set_PortTxFIFOControl(Type_PortTxFIFOControl value) { rw.set(0x10u,value.value); }
 
  Setter<Type_PortTxFIFOControl> to_PortTxFIFOControl() { return Setter<Type_PortTxFIFOControl>(rw,0x10u); }
 
  static Type_PortTxFIFOControl null_PortTxFIFOControl() { return Type_PortTxFIFOControl(0); }
 
  static Type_PortTxFIFOControl ones_PortTxFIFOControl() { return Type_PortTxFIFOControl(Type_PortTxFIFOControl::Type(-1)); }
 
  //--- PortVLANControl

  Type_PortVLANControl get_PortVLANControl() { return Type_PortVLANControl(rw.template get<uint32>(0x14u)); }
 
  void set_PortVLANControl(Type_PortVLANControl value) { rw.set(0x14u,value.value); }
 
  Setter<Type_PortVLANControl> to_PortVLANControl() { return Setter<Type_PortVLANControl>(rw,0x14u); }
 
  static Type_PortVLANControl null_PortVLANControl() { return Type_PortVLANControl(0); }
 
  static Type_PortVLANControl ones_PortVLANControl() { return Type_PortVLANControl(Type_PortVLANControl::Type(-1)); }
 
  //--- PortTxPriMap

  Type_PortTxPriMap get_PortTxPriMap() { return Type_PortTxPriMap(rw.template get<uint32>(0x18u)); }
 
  void set_PortTxPriMap(Type_PortTxPriMap value) { rw.set(0x18u,value.value); }
 
  Setter<Type_PortTxPriMap> to_PortTxPriMap() { return Setter<Type_PortTxPriMap>(rw,0x18u); }
 
  static Type_PortTxPriMap null_PortTxPriMap() { return Type_PortTxPriMap(0); }
 
  static Type_PortTxPriMap ones_PortTxPriMap() { return Type_PortTxPriMap(Type_PortTxPriMap::Type(-1)); }
 
  //--- PortTxDMAPriMap

  Type_PortTxDMAPriMap get_PortTxDMAPriMap() { return Type_PortTxDMAPriMap(rw.template get<uint32>(0x1Cu)); }
 
  void set_PortTxDMAPriMap(Type_PortTxDMAPriMap value) { rw.set(0x1Cu,value.value); }
 
  Setter<Type_PortTxDMAPriMap> to_PortTxDMAPriMap() { return Setter<Type_PortTxDMAPriMap>(rw,0x1Cu); }
 
  static Type_PortTxDMAPriMap null_PortTxDMAPriMap() { return Type_PortTxDMAPriMap(0); }
 
  static Type_PortTxDMAPriMap ones_PortTxDMAPriMap() { return Type_PortTxDMAPriMap(Type_PortTxDMAPriMap::Type(-1)); }
 
  //--- PortRxDMAPriMap

  Type_PortRxDMAPriMap get_PortRxDMAPriMap() { return Type_PortRxDMAPriMap(rw.template get<uint32>(0x20u)); }
 
  void set_PortRxDMAPriMap(Type_PortRxDMAPriMap value) { rw.set(0x20u,value.value); }
 
  Setter<Type_PortRxDMAPriMap> to_PortRxDMAPriMap() { return Setter<Type_PortRxDMAPriMap>(rw,0x20u); }
 
  static Type_PortRxDMAPriMap null_PortRxDMAPriMap() { return Type_PortRxDMAPriMap(0); }
 
  static Type_PortRxDMAPriMap ones_PortRxDMAPriMap() { return Type_PortRxDMAPriMap(Type_PortRxDMAPriMap::Type(-1)); }
 
  //--- PortTOSPriMap0

  Type_PortTOSPriMap0 get_PortTOSPriMap0() { return Type_PortTOSPriMap0(rw.template get<uint32>(0x24u)); }
 
  void set_PortTOSPriMap0(Type_PortTOSPriMap0 value) { rw.set(0x24u,value.value); }
 
  Setter<Type_PortTOSPriMap0> to_PortTOSPriMap0() { return Setter<Type_PortTOSPriMap0>(rw,0x24u); }
 
  static Type_PortTOSPriMap0 null_PortTOSPriMap0() { return Type_PortTOSPriMap0(0); }
 
  static Type_PortTOSPriMap0 ones_PortTOSPriMap0() { return Type_PortTOSPriMap0(Type_PortTOSPriMap0::Type(-1)); }
 
  //--- PortTOSPriMap1

  Type_PortTOSPriMap1 get_PortTOSPriMap1() { return Type_PortTOSPriMap1(rw.template get<uint32>(0x28u)); }
 
  void set_PortTOSPriMap1(Type_PortTOSPriMap1 value) { rw.set(0x28u,value.value); }
 
  Setter<Type_PortTOSPriMap1> to_PortTOSPriMap1() { return Setter<Type_PortTOSPriMap1>(rw,0x28u); }
 
  static Type_PortTOSPriMap1 null_PortTOSPriMap1() { return Type_PortTOSPriMap1(0); }
 
  static Type_PortTOSPriMap1 ones_PortTOSPriMap1() { return Type_PortTOSPriMap1(Type_PortTOSPriMap1::Type(-1)); }
 
  //--- PortTOSPriMap2

  Type_PortTOSPriMap2 get_PortTOSPriMap2() { return Type_PortTOSPriMap2(rw.template get<uint32>(0x2Cu)); }
 
  void set_PortTOSPriMap2(Type_PortTOSPriMap2 value) { rw.set(0x2Cu,value.value); }
 
  Setter<Type_PortTOSPriMap2> to_PortTOSPriMap2() { return Setter<Type_PortTOSPriMap2>(rw,0x2Cu); }
 
  static Type_PortTOSPriMap2 null_PortTOSPriMap2() { return Type_PortTOSPriMap2(0); }
 
  static Type_PortTOSPriMap2 ones_PortTOSPriMap2() { return Type_PortTOSPriMap2(Type_PortTOSPriMap2::Type(-1)); }
 
  //--- PortTOSPriMap3

  Type_PortTOSPriMap3 get_PortTOSPriMap3() { return Type_PortTOSPriMap3(rw.template get<uint32>(0x30u)); }
 
  void set_PortTOSPriMap3(Type_PortTOSPriMap3 value) { rw.set(0x30u,value.value); }
 
  Setter<Type_PortTOSPriMap3> to_PortTOSPriMap3() { return Setter<Type_PortTOSPriMap3>(rw,0x30u); }
 
  static Type_PortTOSPriMap3 null_PortTOSPriMap3() { return Type_PortTOSPriMap3(0); }
 
  static Type_PortTOSPriMap3 ones_PortTOSPriMap3() { return Type_PortTOSPriMap3(Type_PortTOSPriMap3::Type(-1)); }
 
  //--- PortTOSPriMap4

  Type_PortTOSPriMap4 get_PortTOSPriMap4() { return Type_PortTOSPriMap4(rw.template get<uint32>(0x34u)); }
 
  void set_PortTOSPriMap4(Type_PortTOSPriMap4 value) { rw.set(0x34u,value.value); }
 
  Setter<Type_PortTOSPriMap4> to_PortTOSPriMap4() { return Setter<Type_PortTOSPriMap4>(rw,0x34u); }
 
  static Type_PortTOSPriMap4 null_PortTOSPriMap4() { return Type_PortTOSPriMap4(0); }
 
  static Type_PortTOSPriMap4 ones_PortTOSPriMap4() { return Type_PortTOSPriMap4(Type_PortTOSPriMap4::Type(-1)); }
 
  //--- PortTOSPriMap5

  Type_PortTOSPriMap5 get_PortTOSPriMap5() { return Type_PortTOSPriMap5(rw.template get<uint32>(0x38u)); }
 
  void set_PortTOSPriMap5(Type_PortTOSPriMap5 value) { rw.set(0x38u,value.value); }
 
  Setter<Type_PortTOSPriMap5> to_PortTOSPriMap5() { return Setter<Type_PortTOSPriMap5>(rw,0x38u); }
 
  static Type_PortTOSPriMap5 null_PortTOSPriMap5() { return Type_PortTOSPriMap5(0); }
 
  static Type_PortTOSPriMap5 ones_PortTOSPriMap5() { return Type_PortTOSPriMap5(Type_PortTOSPriMap5::Type(-1)); }
 
  //--- PortTOSPriMap6

  Type_PortTOSPriMap6 get_PortTOSPriMap6() { return Type_PortTOSPriMap6(rw.template get<uint32>(0x3Cu)); }
 
  void set_PortTOSPriMap6(Type_PortTOSPriMap6 value) { rw.set(0x3Cu,value.value); }
 
  Setter<Type_PortTOSPriMap6> to_PortTOSPriMap6() { return Setter<Type_PortTOSPriMap6>(rw,0x3Cu); }
 
  static Type_PortTOSPriMap6 null_PortTOSPriMap6() { return Type_PortTOSPriMap6(0); }
 
  static Type_PortTOSPriMap6 ones_PortTOSPriMap6() { return Type_PortTOSPriMap6(Type_PortTOSPriMap6::Type(-1)); }
 
  //--- PortTOSPriMap7

  Type_PortTOSPriMap7 get_PortTOSPriMap7() { return Type_PortTOSPriMap7(rw.template get<uint32>(0x40u)); }
 
  void set_PortTOSPriMap7(Type_PortTOSPriMap7 value) { rw.set(0x40u,value.value); }
 
  Setter<Type_PortTOSPriMap7> to_PortTOSPriMap7() { return Setter<Type_PortTOSPriMap7>(rw,0x40u); }
 
  static Type_PortTOSPriMap7 null_PortTOSPriMap7() { return Type_PortTOSPriMap7(0); }
 
  static Type_PortTOSPriMap7 ones_PortTOSPriMap7() { return Type_PortTOSPriMap7(Type_PortTOSPriMap7::Type(-1)); }
 
 };
 
/* struct Port1Bar<RW> */

template <class RW>
struct Port1Bar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit Port1Bar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- PortControl

  Type_PortControl get_PortControl() { return Type_PortControl(rw.template get<uint32>(0x0u)); }
 
  void set_PortControl(Type_PortControl value) { rw.set(0x0u,value.value); }
 
  Setter<Type_PortControl> to_PortControl() { return Setter<Type_PortControl>(rw,0x0u); }
 
  static Type_PortControl null_PortControl() { return Type_PortControl(0); }
 
  static Type_PortControl ones_PortControl() { return Type_PortControl(Type_PortControl::Type(-1)); }
 
  //--- PortFIFOLen

  Type_PortFIFOLen get_PortFIFOLen() { return Type_PortFIFOLen(rw.template get<uint32>(0x8u)); }
 
  void set_PortFIFOLen(Type_PortFIFOLen value) { rw.set(0x8u,value.value); }
 
  Setter<Type_PortFIFOLen> to_PortFIFOLen() { return Setter<Type_PortFIFOLen>(rw,0x8u); }
 
  static Type_PortFIFOLen null_PortFIFOLen() { return Type_PortFIFOLen(0); }
 
  static Type_PortFIFOLen ones_PortFIFOLen() { return Type_PortFIFOLen(Type_PortFIFOLen::Type(-1)); }
 
  //--- PortFIFOUse

  Type_PortFIFOUse get_PortFIFOUse() { return Type_PortFIFOUse(rw.template get<uint32>(0xCu)); }
 
  static Type_PortFIFOUse null_PortFIFOUse() { return Type_PortFIFOUse(0); }
 
  static Type_PortFIFOUse ones_PortFIFOUse() { return Type_PortFIFOUse(Type_PortFIFOUse::Type(-1)); }
 
  //--- PortTxFIFOControl

  Type_PortTxFIFOControl get_PortTxFIFOControl() { return Type_PortTxFIFOControl(rw.template get<uint32>(0x10u)); }
 
  void set_PortTxFIFOControl(Type_PortTxFIFOControl value) { rw.set(0x10u,value.value); }
 
  Setter<Type_PortTxFIFOControl> to_PortTxFIFOControl() { return Setter<Type_PortTxFIFOControl>(rw,0x10u); }
 
  static Type_PortTxFIFOControl null_PortTxFIFOControl() { return Type_PortTxFIFOControl(0); }
 
  static Type_PortTxFIFOControl ones_PortTxFIFOControl() { return Type_PortTxFIFOControl(Type_PortTxFIFOControl::Type(-1)); }
 
  //--- PortVLANControl

  Type_PortVLANControl get_PortVLANControl() { return Type_PortVLANControl(rw.template get<uint32>(0x14u)); }
 
  void set_PortVLANControl(Type_PortVLANControl value) { rw.set(0x14u,value.value); }
 
  Setter<Type_PortVLANControl> to_PortVLANControl() { return Setter<Type_PortVLANControl>(rw,0x14u); }
 
  static Type_PortVLANControl null_PortVLANControl() { return Type_PortVLANControl(0); }
 
  static Type_PortVLANControl ones_PortVLANControl() { return Type_PortVLANControl(Type_PortVLANControl::Type(-1)); }
 
  //--- PortTxPriMap

  Type_PortTxPriMap get_PortTxPriMap() { return Type_PortTxPriMap(rw.template get<uint32>(0x18u)); }
 
  void set_PortTxPriMap(Type_PortTxPriMap value) { rw.set(0x18u,value.value); }
 
  Setter<Type_PortTxPriMap> to_PortTxPriMap() { return Setter<Type_PortTxPriMap>(rw,0x18u); }
 
  static Type_PortTxPriMap null_PortTxPriMap() { return Type_PortTxPriMap(0); }
 
  static Type_PortTxPriMap ones_PortTxPriMap() { return Type_PortTxPriMap(Type_PortTxPriMap::Type(-1)); }
 
  //--- PortTimeSync

  Type_PortTimeSync get_PortTimeSync() { return Type_PortTimeSync(rw.template get<uint32>(0x1Cu)); }
 
  void set_PortTimeSync(Type_PortTimeSync value) { rw.set(0x1Cu,value.value); }
 
  Setter<Type_PortTimeSync> to_PortTimeSync() { return Setter<Type_PortTimeSync>(rw,0x1Cu); }
 
  static Type_PortTimeSync null_PortTimeSync() { return Type_PortTimeSync(0); }
 
  static Type_PortTimeSync ones_PortTimeSync() { return Type_PortTimeSync(Type_PortTimeSync::Type(-1)); }
 
  //--- PortMACHi

  Type_PortMACHi get_PortMACHi() { return Type_PortMACHi(rw.template get<uint32>(0x20u)); }
 
  void set_PortMACHi(Type_PortMACHi value) { rw.set(0x20u,value.value); }
 
  Setter<Type_PortMACHi> to_PortMACHi() { return Setter<Type_PortMACHi>(rw,0x20u); }
 
  static Type_PortMACHi null_PortMACHi() { return Type_PortMACHi(0); }
 
  static Type_PortMACHi ones_PortMACHi() { return Type_PortMACHi(Type_PortMACHi::Type(-1)); }
 
  //--- PortMACLo

  Type_PortMACLo get_PortMACLo() { return Type_PortMACLo(rw.template get<uint32>(0x24u)); }
 
  void set_PortMACLo(Type_PortMACLo value) { rw.set(0x24u,value.value); }
 
  Setter<Type_PortMACLo> to_PortMACLo() { return Setter<Type_PortMACLo>(rw,0x24u); }
 
  static Type_PortMACLo null_PortMACLo() { return Type_PortMACLo(0); }
 
  static Type_PortMACLo ones_PortMACLo() { return Type_PortMACLo(Type_PortMACLo::Type(-1)); }
 
  //--- PortSendPercent

  Type_PortSendPercent get_PortSendPercent() { return Type_PortSendPercent(rw.template get<uint32>(0x28u)); }
 
  void set_PortSendPercent(Type_PortSendPercent value) { rw.set(0x28u,value.value); }
 
  Setter<Type_PortSendPercent> to_PortSendPercent() { return Setter<Type_PortSendPercent>(rw,0x28u); }
 
  static Type_PortSendPercent null_PortSendPercent() { return Type_PortSendPercent(0); }
 
  static Type_PortSendPercent ones_PortSendPercent() { return Type_PortSendPercent(Type_PortSendPercent::Type(-1)); }
 
  //--- PortTOSPriMap0

  Type_PortTOSPriMap0 get_PortTOSPriMap0() { return Type_PortTOSPriMap0(rw.template get<uint32>(0x2Cu)); }
 
  void set_PortTOSPriMap0(Type_PortTOSPriMap0 value) { rw.set(0x2Cu,value.value); }
 
  Setter<Type_PortTOSPriMap0> to_PortTOSPriMap0() { return Setter<Type_PortTOSPriMap0>(rw,0x2Cu); }
 
  static Type_PortTOSPriMap0 null_PortTOSPriMap0() { return Type_PortTOSPriMap0(0); }
 
  static Type_PortTOSPriMap0 ones_PortTOSPriMap0() { return Type_PortTOSPriMap0(Type_PortTOSPriMap0::Type(-1)); }
 
  //--- PortTOSPriMap1

  Type_PortTOSPriMap1 get_PortTOSPriMap1() { return Type_PortTOSPriMap1(rw.template get<uint32>(0x30u)); }
 
  void set_PortTOSPriMap1(Type_PortTOSPriMap1 value) { rw.set(0x30u,value.value); }
 
  Setter<Type_PortTOSPriMap1> to_PortTOSPriMap1() { return Setter<Type_PortTOSPriMap1>(rw,0x30u); }
 
  static Type_PortTOSPriMap1 null_PortTOSPriMap1() { return Type_PortTOSPriMap1(0); }
 
  static Type_PortTOSPriMap1 ones_PortTOSPriMap1() { return Type_PortTOSPriMap1(Type_PortTOSPriMap1::Type(-1)); }
 
  //--- PortTOSPriMap2

  Type_PortTOSPriMap2 get_PortTOSPriMap2() { return Type_PortTOSPriMap2(rw.template get<uint32>(0x34u)); }
 
  void set_PortTOSPriMap2(Type_PortTOSPriMap2 value) { rw.set(0x34u,value.value); }
 
  Setter<Type_PortTOSPriMap2> to_PortTOSPriMap2() { return Setter<Type_PortTOSPriMap2>(rw,0x34u); }
 
  static Type_PortTOSPriMap2 null_PortTOSPriMap2() { return Type_PortTOSPriMap2(0); }
 
  static Type_PortTOSPriMap2 ones_PortTOSPriMap2() { return Type_PortTOSPriMap2(Type_PortTOSPriMap2::Type(-1)); }
 
  //--- PortTOSPriMap3

  Type_PortTOSPriMap3 get_PortTOSPriMap3() { return Type_PortTOSPriMap3(rw.template get<uint32>(0x38u)); }
 
  void set_PortTOSPriMap3(Type_PortTOSPriMap3 value) { rw.set(0x38u,value.value); }
 
  Setter<Type_PortTOSPriMap3> to_PortTOSPriMap3() { return Setter<Type_PortTOSPriMap3>(rw,0x38u); }
 
  static Type_PortTOSPriMap3 null_PortTOSPriMap3() { return Type_PortTOSPriMap3(0); }
 
  static Type_PortTOSPriMap3 ones_PortTOSPriMap3() { return Type_PortTOSPriMap3(Type_PortTOSPriMap3::Type(-1)); }
 
  //--- PortTOSPriMap4

  Type_PortTOSPriMap4 get_PortTOSPriMap4() { return Type_PortTOSPriMap4(rw.template get<uint32>(0x3Cu)); }
 
  void set_PortTOSPriMap4(Type_PortTOSPriMap4 value) { rw.set(0x3Cu,value.value); }
 
  Setter<Type_PortTOSPriMap4> to_PortTOSPriMap4() { return Setter<Type_PortTOSPriMap4>(rw,0x3Cu); }
 
  static Type_PortTOSPriMap4 null_PortTOSPriMap4() { return Type_PortTOSPriMap4(0); }
 
  static Type_PortTOSPriMap4 ones_PortTOSPriMap4() { return Type_PortTOSPriMap4(Type_PortTOSPriMap4::Type(-1)); }
 
  //--- PortTOSPriMap5

  Type_PortTOSPriMap5 get_PortTOSPriMap5() { return Type_PortTOSPriMap5(rw.template get<uint32>(0x40u)); }
 
  void set_PortTOSPriMap5(Type_PortTOSPriMap5 value) { rw.set(0x40u,value.value); }
 
  Setter<Type_PortTOSPriMap5> to_PortTOSPriMap5() { return Setter<Type_PortTOSPriMap5>(rw,0x40u); }
 
  static Type_PortTOSPriMap5 null_PortTOSPriMap5() { return Type_PortTOSPriMap5(0); }
 
  static Type_PortTOSPriMap5 ones_PortTOSPriMap5() { return Type_PortTOSPriMap5(Type_PortTOSPriMap5::Type(-1)); }
 
  //--- PortTOSPriMap6

  Type_PortTOSPriMap6 get_PortTOSPriMap6() { return Type_PortTOSPriMap6(rw.template get<uint32>(0x44u)); }
 
  void set_PortTOSPriMap6(Type_PortTOSPriMap6 value) { rw.set(0x44u,value.value); }
 
  Setter<Type_PortTOSPriMap6> to_PortTOSPriMap6() { return Setter<Type_PortTOSPriMap6>(rw,0x44u); }
 
  static Type_PortTOSPriMap6 null_PortTOSPriMap6() { return Type_PortTOSPriMap6(0); }
 
  static Type_PortTOSPriMap6 ones_PortTOSPriMap6() { return Type_PortTOSPriMap6(Type_PortTOSPriMap6::Type(-1)); }
 
  //--- PortTOSPriMap7

  Type_PortTOSPriMap7 get_PortTOSPriMap7() { return Type_PortTOSPriMap7(rw.template get<uint32>(0x48u)); }
 
  void set_PortTOSPriMap7(Type_PortTOSPriMap7 value) { rw.set(0x48u,value.value); }
 
  Setter<Type_PortTOSPriMap7> to_PortTOSPriMap7() { return Setter<Type_PortTOSPriMap7>(rw,0x48u); }
 
  static Type_PortTOSPriMap7 null_PortTOSPriMap7() { return Type_PortTOSPriMap7(0); }
 
  static Type_PortTOSPriMap7 ones_PortTOSPriMap7() { return Type_PortTOSPriMap7(Type_PortTOSPriMap7::Type(-1)); }
 
 };
 
/* struct Port2Bar<RW> */

template <class RW>
struct Port2Bar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit Port2Bar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- PortControl

  Type_PortControl get_PortControl() { return Type_PortControl(rw.template get<uint32>(0x0u)); }
 
  void set_PortControl(Type_PortControl value) { rw.set(0x0u,value.value); }
 
  Setter<Type_PortControl> to_PortControl() { return Setter<Type_PortControl>(rw,0x0u); }
 
  static Type_PortControl null_PortControl() { return Type_PortControl(0); }
 
  static Type_PortControl ones_PortControl() { return Type_PortControl(Type_PortControl::Type(-1)); }
 
  //--- PortFIFOLen

  Type_PortFIFOLen get_PortFIFOLen() { return Type_PortFIFOLen(rw.template get<uint32>(0x8u)); }
 
  void set_PortFIFOLen(Type_PortFIFOLen value) { rw.set(0x8u,value.value); }
 
  Setter<Type_PortFIFOLen> to_PortFIFOLen() { return Setter<Type_PortFIFOLen>(rw,0x8u); }
 
  static Type_PortFIFOLen null_PortFIFOLen() { return Type_PortFIFOLen(0); }
 
  static Type_PortFIFOLen ones_PortFIFOLen() { return Type_PortFIFOLen(Type_PortFIFOLen::Type(-1)); }
 
  //--- PortFIFOUse

  Type_PortFIFOUse get_PortFIFOUse() { return Type_PortFIFOUse(rw.template get<uint32>(0xCu)); }
 
  static Type_PortFIFOUse null_PortFIFOUse() { return Type_PortFIFOUse(0); }
 
  static Type_PortFIFOUse ones_PortFIFOUse() { return Type_PortFIFOUse(Type_PortFIFOUse::Type(-1)); }
 
  //--- PortTxFIFOControl

  Type_PortTxFIFOControl get_PortTxFIFOControl() { return Type_PortTxFIFOControl(rw.template get<uint32>(0x10u)); }
 
  void set_PortTxFIFOControl(Type_PortTxFIFOControl value) { rw.set(0x10u,value.value); }
 
  Setter<Type_PortTxFIFOControl> to_PortTxFIFOControl() { return Setter<Type_PortTxFIFOControl>(rw,0x10u); }
 
  static Type_PortTxFIFOControl null_PortTxFIFOControl() { return Type_PortTxFIFOControl(0); }
 
  static Type_PortTxFIFOControl ones_PortTxFIFOControl() { return Type_PortTxFIFOControl(Type_PortTxFIFOControl::Type(-1)); }
 
  //--- PortVLANControl

  Type_PortVLANControl get_PortVLANControl() { return Type_PortVLANControl(rw.template get<uint32>(0x14u)); }
 
  void set_PortVLANControl(Type_PortVLANControl value) { rw.set(0x14u,value.value); }
 
  Setter<Type_PortVLANControl> to_PortVLANControl() { return Setter<Type_PortVLANControl>(rw,0x14u); }
 
  static Type_PortVLANControl null_PortVLANControl() { return Type_PortVLANControl(0); }
 
  static Type_PortVLANControl ones_PortVLANControl() { return Type_PortVLANControl(Type_PortVLANControl::Type(-1)); }
 
  //--- PortTxPriMap

  Type_PortTxPriMap get_PortTxPriMap() { return Type_PortTxPriMap(rw.template get<uint32>(0x18u)); }
 
  void set_PortTxPriMap(Type_PortTxPriMap value) { rw.set(0x18u,value.value); }
 
  Setter<Type_PortTxPriMap> to_PortTxPriMap() { return Setter<Type_PortTxPriMap>(rw,0x18u); }
 
  static Type_PortTxPriMap null_PortTxPriMap() { return Type_PortTxPriMap(0); }
 
  static Type_PortTxPriMap ones_PortTxPriMap() { return Type_PortTxPriMap(Type_PortTxPriMap::Type(-1)); }
 
  //--- PortTimeSync

  Type_PortTimeSync get_PortTimeSync() { return Type_PortTimeSync(rw.template get<uint32>(0x1Cu)); }
 
  void set_PortTimeSync(Type_PortTimeSync value) { rw.set(0x1Cu,value.value); }
 
  Setter<Type_PortTimeSync> to_PortTimeSync() { return Setter<Type_PortTimeSync>(rw,0x1Cu); }
 
  static Type_PortTimeSync null_PortTimeSync() { return Type_PortTimeSync(0); }
 
  static Type_PortTimeSync ones_PortTimeSync() { return Type_PortTimeSync(Type_PortTimeSync::Type(-1)); }
 
  //--- PortMACHi

  Type_PortMACHi get_PortMACHi() { return Type_PortMACHi(rw.template get<uint32>(0x20u)); }
 
  void set_PortMACHi(Type_PortMACHi value) { rw.set(0x20u,value.value); }
 
  Setter<Type_PortMACHi> to_PortMACHi() { return Setter<Type_PortMACHi>(rw,0x20u); }
 
  static Type_PortMACHi null_PortMACHi() { return Type_PortMACHi(0); }
 
  static Type_PortMACHi ones_PortMACHi() { return Type_PortMACHi(Type_PortMACHi::Type(-1)); }
 
  //--- PortMACLo

  Type_PortMACLo get_PortMACLo() { return Type_PortMACLo(rw.template get<uint32>(0x24u)); }
 
  void set_PortMACLo(Type_PortMACLo value) { rw.set(0x24u,value.value); }
 
  Setter<Type_PortMACLo> to_PortMACLo() { return Setter<Type_PortMACLo>(rw,0x24u); }
 
  static Type_PortMACLo null_PortMACLo() { return Type_PortMACLo(0); }
 
  static Type_PortMACLo ones_PortMACLo() { return Type_PortMACLo(Type_PortMACLo::Type(-1)); }
 
  //--- PortSendPercent

  Type_PortSendPercent get_PortSendPercent() { return Type_PortSendPercent(rw.template get<uint32>(0x28u)); }
 
  void set_PortSendPercent(Type_PortSendPercent value) { rw.set(0x28u,value.value); }
 
  Setter<Type_PortSendPercent> to_PortSendPercent() { return Setter<Type_PortSendPercent>(rw,0x28u); }
 
  static Type_PortSendPercent null_PortSendPercent() { return Type_PortSendPercent(0); }
 
  static Type_PortSendPercent ones_PortSendPercent() { return Type_PortSendPercent(Type_PortSendPercent::Type(-1)); }
 
  //--- PortTOSPriMap0

  Type_PortTOSPriMap0 get_PortTOSPriMap0() { return Type_PortTOSPriMap0(rw.template get<uint32>(0x2Cu)); }
 
  void set_PortTOSPriMap0(Type_PortTOSPriMap0 value) { rw.set(0x2Cu,value.value); }
 
  Setter<Type_PortTOSPriMap0> to_PortTOSPriMap0() { return Setter<Type_PortTOSPriMap0>(rw,0x2Cu); }
 
  static Type_PortTOSPriMap0 null_PortTOSPriMap0() { return Type_PortTOSPriMap0(0); }
 
  static Type_PortTOSPriMap0 ones_PortTOSPriMap0() { return Type_PortTOSPriMap0(Type_PortTOSPriMap0::Type(-1)); }
 
  //--- PortTOSPriMap1

  Type_PortTOSPriMap1 get_PortTOSPriMap1() { return Type_PortTOSPriMap1(rw.template get<uint32>(0x30u)); }
 
  void set_PortTOSPriMap1(Type_PortTOSPriMap1 value) { rw.set(0x30u,value.value); }
 
  Setter<Type_PortTOSPriMap1> to_PortTOSPriMap1() { return Setter<Type_PortTOSPriMap1>(rw,0x30u); }
 
  static Type_PortTOSPriMap1 null_PortTOSPriMap1() { return Type_PortTOSPriMap1(0); }
 
  static Type_PortTOSPriMap1 ones_PortTOSPriMap1() { return Type_PortTOSPriMap1(Type_PortTOSPriMap1::Type(-1)); }
 
  //--- PortTOSPriMap2

  Type_PortTOSPriMap2 get_PortTOSPriMap2() { return Type_PortTOSPriMap2(rw.template get<uint32>(0x34u)); }
 
  void set_PortTOSPriMap2(Type_PortTOSPriMap2 value) { rw.set(0x34u,value.value); }
 
  Setter<Type_PortTOSPriMap2> to_PortTOSPriMap2() { return Setter<Type_PortTOSPriMap2>(rw,0x34u); }
 
  static Type_PortTOSPriMap2 null_PortTOSPriMap2() { return Type_PortTOSPriMap2(0); }
 
  static Type_PortTOSPriMap2 ones_PortTOSPriMap2() { return Type_PortTOSPriMap2(Type_PortTOSPriMap2::Type(-1)); }
 
  //--- PortTOSPriMap3

  Type_PortTOSPriMap3 get_PortTOSPriMap3() { return Type_PortTOSPriMap3(rw.template get<uint32>(0x38u)); }
 
  void set_PortTOSPriMap3(Type_PortTOSPriMap3 value) { rw.set(0x38u,value.value); }
 
  Setter<Type_PortTOSPriMap3> to_PortTOSPriMap3() { return Setter<Type_PortTOSPriMap3>(rw,0x38u); }
 
  static Type_PortTOSPriMap3 null_PortTOSPriMap3() { return Type_PortTOSPriMap3(0); }
 
  static Type_PortTOSPriMap3 ones_PortTOSPriMap3() { return Type_PortTOSPriMap3(Type_PortTOSPriMap3::Type(-1)); }
 
  //--- PortTOSPriMap4

  Type_PortTOSPriMap4 get_PortTOSPriMap4() { return Type_PortTOSPriMap4(rw.template get<uint32>(0x3Cu)); }
 
  void set_PortTOSPriMap4(Type_PortTOSPriMap4 value) { rw.set(0x3Cu,value.value); }
 
  Setter<Type_PortTOSPriMap4> to_PortTOSPriMap4() { return Setter<Type_PortTOSPriMap4>(rw,0x3Cu); }
 
  static Type_PortTOSPriMap4 null_PortTOSPriMap4() { return Type_PortTOSPriMap4(0); }
 
  static Type_PortTOSPriMap4 ones_PortTOSPriMap4() { return Type_PortTOSPriMap4(Type_PortTOSPriMap4::Type(-1)); }
 
  //--- PortTOSPriMap5

  Type_PortTOSPriMap5 get_PortTOSPriMap5() { return Type_PortTOSPriMap5(rw.template get<uint32>(0x40u)); }
 
  void set_PortTOSPriMap5(Type_PortTOSPriMap5 value) { rw.set(0x40u,value.value); }
 
  Setter<Type_PortTOSPriMap5> to_PortTOSPriMap5() { return Setter<Type_PortTOSPriMap5>(rw,0x40u); }
 
  static Type_PortTOSPriMap5 null_PortTOSPriMap5() { return Type_PortTOSPriMap5(0); }
 
  static Type_PortTOSPriMap5 ones_PortTOSPriMap5() { return Type_PortTOSPriMap5(Type_PortTOSPriMap5::Type(-1)); }
 
  //--- PortTOSPriMap6

  Type_PortTOSPriMap6 get_PortTOSPriMap6() { return Type_PortTOSPriMap6(rw.template get<uint32>(0x44u)); }
 
  void set_PortTOSPriMap6(Type_PortTOSPriMap6 value) { rw.set(0x44u,value.value); }
 
  Setter<Type_PortTOSPriMap6> to_PortTOSPriMap6() { return Setter<Type_PortTOSPriMap6>(rw,0x44u); }
 
  static Type_PortTOSPriMap6 null_PortTOSPriMap6() { return Type_PortTOSPriMap6(0); }
 
  static Type_PortTOSPriMap6 ones_PortTOSPriMap6() { return Type_PortTOSPriMap6(Type_PortTOSPriMap6::Type(-1)); }
 
  //--- PortTOSPriMap7

  Type_PortTOSPriMap7 get_PortTOSPriMap7() { return Type_PortTOSPriMap7(rw.template get<uint32>(0x48u)); }
 
  void set_PortTOSPriMap7(Type_PortTOSPriMap7 value) { rw.set(0x48u,value.value); }
 
  Setter<Type_PortTOSPriMap7> to_PortTOSPriMap7() { return Setter<Type_PortTOSPriMap7>(rw,0x48u); }
 
  static Type_PortTOSPriMap7 null_PortTOSPriMap7() { return Type_PortTOSPriMap7(0); }
 
  static Type_PortTOSPriMap7 ones_PortTOSPriMap7() { return Type_PortTOSPriMap7(Type_PortTOSPriMap7::Type(-1)); }
 
 };
 
/* struct DMABar<RW> */

template <class RW>
struct DMABar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit DMABar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- DMATxControl

  Type_DMATxControl get_DMATxControl() { return Type_DMATxControl(rw.template get<uint32>(0x4u)); }
 
  void set_DMATxControl(Type_DMATxControl value) { rw.set(0x4u,value.value); }
 
  Setter<Type_DMATxControl> to_DMATxControl() { return Setter<Type_DMATxControl>(rw,0x4u); }
 
  static Type_DMATxControl null_DMATxControl() { return Type_DMATxControl(0); }
 
  static Type_DMATxControl ones_DMATxControl() { return Type_DMATxControl(Type_DMATxControl::Type(-1)); }
 
  //--- DMATxTeardown

  Type_DMATxTeardown get_DMATxTeardown() { return Type_DMATxTeardown(rw.template get<uint32>(0x8u)); }
 
  void set_DMATxTeardown(Type_DMATxTeardown value) { rw.set(0x8u,value.value); }
 
  Setter<Type_DMATxTeardown> to_DMATxTeardown() { return Setter<Type_DMATxTeardown>(rw,0x8u); }
 
  static Type_DMATxTeardown null_DMATxTeardown() { return Type_DMATxTeardown(0); }
 
  static Type_DMATxTeardown ones_DMATxTeardown() { return Type_DMATxTeardown(Type_DMATxTeardown::Type(-1)); }
 
  //--- DMARxControl

  Type_DMARxControl get_DMARxControl() { return Type_DMARxControl(rw.template get<uint32>(0x14u)); }
 
  void set_DMARxControl(Type_DMARxControl value) { rw.set(0x14u,value.value); }
 
  Setter<Type_DMARxControl> to_DMARxControl() { return Setter<Type_DMARxControl>(rw,0x14u); }
 
  static Type_DMARxControl null_DMARxControl() { return Type_DMARxControl(0); }
 
  static Type_DMARxControl ones_DMARxControl() { return Type_DMARxControl(Type_DMARxControl::Type(-1)); }
 
  //--- DMARxTeardown

  Type_DMARxTeardown get_DMARxTeardown() { return Type_DMARxTeardown(rw.template get<uint32>(0x18u)); }
 
  void set_DMARxTeardown(Type_DMARxTeardown value) { rw.set(0x18u,value.value); }
 
  Setter<Type_DMARxTeardown> to_DMARxTeardown() { return Setter<Type_DMARxTeardown>(rw,0x18u); }
 
  static Type_DMARxTeardown null_DMARxTeardown() { return Type_DMARxTeardown(0); }
 
  static Type_DMARxTeardown ones_DMARxTeardown() { return Type_DMARxTeardown(Type_DMARxTeardown::Type(-1)); }
 
  //--- DMASoftReset

  Type_DMASoftReset get_DMASoftReset() { return Type_DMASoftReset(rw.template get<uint32>(0x1Cu)); }
 
  void set_DMASoftReset(Type_DMASoftReset value) { rw.set(0x1Cu,value.value); }
 
  Setter<Type_DMASoftReset> to_DMASoftReset() { return Setter<Type_DMASoftReset>(rw,0x1Cu); }
 
  static Type_DMASoftReset null_DMASoftReset() { return Type_DMASoftReset(0); }
 
  static Type_DMASoftReset ones_DMASoftReset() { return Type_DMASoftReset(Type_DMASoftReset::Type(-1)); }
 
  //--- DMAControl

  Type_DMAControl get_DMAControl() { return Type_DMAControl(rw.template get<uint32>(0x20u)); }
 
  void set_DMAControl(Type_DMAControl value) { rw.set(0x20u,value.value); }
 
  Setter<Type_DMAControl> to_DMAControl() { return Setter<Type_DMAControl>(rw,0x20u); }
 
  static Type_DMAControl null_DMAControl() { return Type_DMAControl(0); }
 
  static Type_DMAControl ones_DMAControl() { return Type_DMAControl(Type_DMAControl::Type(-1)); }
 
  //--- DMAStatus

  Type_DMAStatus get_DMAStatus() { return Type_DMAStatus(rw.template get<uint32>(0x24u)); }
 
  static Type_DMAStatus null_DMAStatus() { return Type_DMAStatus(0); }
 
  static Type_DMAStatus ones_DMAStatus() { return Type_DMAStatus(Type_DMAStatus::Type(-1)); }
 
  //--- DMARxOffset

  Type_DMARxOffset get_DMARxOffset() { return Type_DMARxOffset(rw.template get<uint32>(0x28u)); }
 
  void set_DMARxOffset(Type_DMARxOffset value) { rw.set(0x28u,value.value); }
 
  Setter<Type_DMARxOffset> to_DMARxOffset() { return Setter<Type_DMARxOffset>(rw,0x28u); }
 
  static Type_DMARxOffset null_DMARxOffset() { return Type_DMARxOffset(0); }
 
  static Type_DMARxOffset ones_DMARxOffset() { return Type_DMARxOffset(Type_DMARxOffset::Type(-1)); }
 
  //--- DMAEMControl

  Type_DMAEMControl get_DMAEMControl() { return Type_DMAEMControl(rw.template get<uint32>(0x2Cu)); }
 
  void set_DMAEMControl(Type_DMAEMControl value) { rw.set(0x2Cu,value.value); }
 
  Setter<Type_DMAEMControl> to_DMAEMControl() { return Setter<Type_DMAEMControl>(rw,0x2Cu); }
 
  static Type_DMAEMControl null_DMAEMControl() { return Type_DMAEMControl(0); }
 
  static Type_DMAEMControl ones_DMAEMControl() { return Type_DMAEMControl(Type_DMAEMControl::Type(-1)); }
 
  //--- DMARateControl

  static Type_DMARateControl null_DMARateControl() { return Type_DMARateControl(0); }
 
  static Type_DMARateControl ones_DMARateControl() { return Type_DMARateControl(Type_DMARateControl::Type(-1)); }
 
  //--- DMATx0RateControl

  Type_DMARateControl get_DMATx0RateControl() { return Type_DMARateControl(rw.template get<uint32>(0x30u)); }
 
  void set_DMATx0RateControl(Type_DMARateControl value) { rw.set(0x30u,value.value); }
 
  Setter<Type_DMARateControl> to_DMATx0RateControl() { return Setter<Type_DMARateControl>(rw,0x30u); }
 
  //--- DMATx1RateControl

  Type_DMARateControl get_DMATx1RateControl() { return Type_DMARateControl(rw.template get<uint32>(0x34u)); }
 
  void set_DMATx1RateControl(Type_DMARateControl value) { rw.set(0x34u,value.value); }
 
  Setter<Type_DMARateControl> to_DMATx1RateControl() { return Setter<Type_DMARateControl>(rw,0x34u); }
 
  //--- DMATx2RateControl

  Type_DMARateControl get_DMATx2RateControl() { return Type_DMARateControl(rw.template get<uint32>(0x38u)); }
 
  void set_DMATx2RateControl(Type_DMARateControl value) { rw.set(0x38u,value.value); }
 
  Setter<Type_DMARateControl> to_DMATx2RateControl() { return Setter<Type_DMARateControl>(rw,0x38u); }
 
  //--- DMATx3RateControl

  Type_DMARateControl get_DMATx3RateControl() { return Type_DMARateControl(rw.template get<uint32>(0x3Cu)); }
 
  void set_DMATx3RateControl(Type_DMARateControl value) { rw.set(0x3Cu,value.value); }
 
  Setter<Type_DMARateControl> to_DMATx3RateControl() { return Setter<Type_DMARateControl>(rw,0x3Cu); }
 
  //--- DMATx4RateControl

  Type_DMARateControl get_DMATx4RateControl() { return Type_DMARateControl(rw.template get<uint32>(0x40u)); }
 
  void set_DMATx4RateControl(Type_DMARateControl value) { rw.set(0x40u,value.value); }
 
  Setter<Type_DMARateControl> to_DMATx4RateControl() { return Setter<Type_DMARateControl>(rw,0x40u); }
 
  //--- DMATx5RateControl

  Type_DMARateControl get_DMATx5RateControl() { return Type_DMARateControl(rw.template get<uint32>(0x44u)); }
 
  void set_DMATx5RateControl(Type_DMARateControl value) { rw.set(0x44u,value.value); }
 
  Setter<Type_DMARateControl> to_DMATx5RateControl() { return Setter<Type_DMARateControl>(rw,0x44u); }
 
  //--- DMATx6RateControl

  Type_DMARateControl get_DMATx6RateControl() { return Type_DMARateControl(rw.template get<uint32>(0x48u)); }
 
  void set_DMATx6RateControl(Type_DMARateControl value) { rw.set(0x48u,value.value); }
 
  Setter<Type_DMARateControl> to_DMATx6RateControl() { return Setter<Type_DMARateControl>(rw,0x48u); }
 
  //--- DMATx7RateControl

  Type_DMARateControl get_DMATx7RateControl() { return Type_DMARateControl(rw.template get<uint32>(0x4Cu)); }
 
  void set_DMATx7RateControl(Type_DMARateControl value) { rw.set(0x4Cu,value.value); }
 
  Setter<Type_DMARateControl> to_DMATx7RateControl() { return Setter<Type_DMARateControl>(rw,0x4Cu); }
 
  //--- DMATxIntStatusRaw

  Type_DMATxIntStatus get_DMATxIntStatusRaw() { return Type_DMATxIntStatus(rw.template get<uint32>(0x80u)); }
 
  void set_DMATxIntStatusRaw(Type_DMATxIntStatus value) { rw.set(0x80u,value.value); }
 
  Setter<Type_DMATxIntStatus> to_DMATxIntStatusRaw() { return Setter<Type_DMATxIntStatus>(rw,0x80u); }
 
  //--- DMATxIntStatus

  Type_DMATxIntStatus get_DMATxIntStatus() { return Type_DMATxIntStatus(rw.template get<uint32>(0x84u)); }
 
  void set_DMATxIntStatus(Type_DMATxIntStatus value) { rw.set(0x84u,value.value); }
 
  Setter<Type_DMATxIntStatus> to_DMATxIntStatus() { return Setter<Type_DMATxIntStatus>(rw,0x84u); }
 
  static Type_DMATxIntStatus null_DMATxIntStatus() { return Type_DMATxIntStatus(0); }
 
  static Type_DMATxIntStatus ones_DMATxIntStatus() { return Type_DMATxIntStatus(Type_DMATxIntStatus::Type(-1)); }
 
  //--- DMATxIntEnableSet

  Type_DMATxIntStatus get_DMATxIntEnableSet() { return Type_DMATxIntStatus(rw.template get<uint32>(0x88u)); }
 
  void set_DMATxIntEnableSet(Type_DMATxIntStatus value) { rw.set(0x88u,value.value); }
 
  Setter<Type_DMATxIntStatus> to_DMATxIntEnableSet() { return Setter<Type_DMATxIntStatus>(rw,0x88u); }
 
  //--- DMATxIntEnableClear

  Type_DMATxIntStatus get_DMATxIntEnableClear() { return Type_DMATxIntStatus(rw.template get<uint32>(0x8Cu)); }
 
  void set_DMATxIntEnableClear(Type_DMATxIntStatus value) { rw.set(0x8Cu,value.value); }
 
  Setter<Type_DMATxIntStatus> to_DMATxIntEnableClear() { return Setter<Type_DMATxIntStatus>(rw,0x8Cu); }
 
  //--- DMAInVector

  Type_DMAInVector get_DMAInVector() { return Type_DMAInVector(rw.template get<uint32>(0x90u)); }
 
  //--- DMAEOIVector

  Type_DMAEOIVector get_DMAEOIVector() { return Type_DMAEOIVector(rw.template get<uint32>(0x94u)); }
 
  void set_DMAEOIVector(Type_DMAEOIVector value) { rw.set(0x94u,value); }
 
  void set_DMAEOIVector_null() { rw.set(0x94u,Type_DMAEOIVector(0)); }
 
  void set_DMAEOIVector_ones() { rw.set(0x94u,Type_DMAEOIVector(-1)); }
 
  //--- DMARxIntStatusRaw

  Type_DMARxIntStatus get_DMARxIntStatusRaw() { return Type_DMARxIntStatus(rw.template get<uint32>(0xA0u)); }
 
  void set_DMARxIntStatusRaw(Type_DMARxIntStatus value) { rw.set(0xA0u,value.value); }
 
  Setter<Type_DMARxIntStatus> to_DMARxIntStatusRaw() { return Setter<Type_DMARxIntStatus>(rw,0xA0u); }
 
  //--- DMARxIntStatus

  Type_DMARxIntStatus get_DMARxIntStatus() { return Type_DMARxIntStatus(rw.template get<uint32>(0xA4u)); }
 
  void set_DMARxIntStatus(Type_DMARxIntStatus value) { rw.set(0xA4u,value.value); }
 
  Setter<Type_DMARxIntStatus> to_DMARxIntStatus() { return Setter<Type_DMARxIntStatus>(rw,0xA4u); }
 
  static Type_DMARxIntStatus null_DMARxIntStatus() { return Type_DMARxIntStatus(0); }
 
  static Type_DMARxIntStatus ones_DMARxIntStatus() { return Type_DMARxIntStatus(Type_DMARxIntStatus::Type(-1)); }
 
  //--- DMARxIntEnableSet

  Type_DMARxIntStatus get_DMARxIntEnableSet() { return Type_DMARxIntStatus(rw.template get<uint32>(0xA8u)); }
 
  void set_DMARxIntEnableSet(Type_DMARxIntStatus value) { rw.set(0xA8u,value.value); }
 
  Setter<Type_DMARxIntStatus> to_DMARxIntEnableSet() { return Setter<Type_DMARxIntStatus>(rw,0xA8u); }
 
  //--- DMARxIntEnableClear

  Type_DMARxIntStatus get_DMARxIntEnableClear() { return Type_DMARxIntStatus(rw.template get<uint32>(0xACu)); }
 
  void set_DMARxIntEnableClear(Type_DMARxIntStatus value) { rw.set(0xACu,value.value); }
 
  Setter<Type_DMARxIntStatus> to_DMARxIntEnableClear() { return Setter<Type_DMARxIntStatus>(rw,0xACu); }
 
  //--- DMAIntStatusRaw

  Type_DMAIntStatus get_DMAIntStatusRaw() { return Type_DMAIntStatus(rw.template get<uint32>(0xB0u)); }
 
  void set_DMAIntStatusRaw(Type_DMAIntStatus value) { rw.set(0xB0u,value.value); }
 
  Setter<Type_DMAIntStatus> to_DMAIntStatusRaw() { return Setter<Type_DMAIntStatus>(rw,0xB0u); }
 
  //--- DMAIntStatus

  Type_DMAIntStatus get_DMAIntStatus() { return Type_DMAIntStatus(rw.template get<uint32>(0xB4u)); }
 
  void set_DMAIntStatus(Type_DMAIntStatus value) { rw.set(0xB4u,value.value); }
 
  Setter<Type_DMAIntStatus> to_DMAIntStatus() { return Setter<Type_DMAIntStatus>(rw,0xB4u); }
 
  static Type_DMAIntStatus null_DMAIntStatus() { return Type_DMAIntStatus(0); }
 
  static Type_DMAIntStatus ones_DMAIntStatus() { return Type_DMAIntStatus(Type_DMAIntStatus::Type(-1)); }
 
  //--- DMAIntEnableSet

  Type_DMAIntStatus get_DMAIntEnableSet() { return Type_DMAIntStatus(rw.template get<uint32>(0xB8u)); }
 
  void set_DMAIntEnableSet(Type_DMAIntStatus value) { rw.set(0xB8u,value.value); }
 
  Setter<Type_DMAIntStatus> to_DMAIntEnableSet() { return Setter<Type_DMAIntStatus>(rw,0xB8u); }
 
  //--- DMAIntEnableClear

  Type_DMAIntStatus get_DMAIntEnableClear() { return Type_DMAIntStatus(rw.template get<uint32>(0xBCu)); }
 
  void set_DMAIntEnableClear(Type_DMAIntStatus value) { rw.set(0xBCu,value.value); }
 
  Setter<Type_DMAIntStatus> to_DMAIntEnableClear() { return Setter<Type_DMAIntStatus>(rw,0xBCu); }
 
  //--- DMARxThresh

  static Type_DMARxThresh null_DMARxThresh() { return Type_DMARxThresh(0); }
 
  static Type_DMARxThresh ones_DMARxThresh() { return Type_DMARxThresh(Type_DMARxThresh::Type(-1)); }
 
  //--- DMARx0Thresh

  Type_DMARxThresh get_DMARx0Thresh() { return Type_DMARxThresh(rw.template get<uint32>(0xC0u)); }
 
  void set_DMARx0Thresh(Type_DMARxThresh value) { rw.set(0xC0u,value.value); }
 
  Setter<Type_DMARxThresh> to_DMARx0Thresh() { return Setter<Type_DMARxThresh>(rw,0xC0u); }
 
  //--- DMARx1Thresh

  Type_DMARxThresh get_DMARx1Thresh() { return Type_DMARxThresh(rw.template get<uint32>(0xC4u)); }
 
  void set_DMARx1Thresh(Type_DMARxThresh value) { rw.set(0xC4u,value.value); }
 
  Setter<Type_DMARxThresh> to_DMARx1Thresh() { return Setter<Type_DMARxThresh>(rw,0xC4u); }
 
  //--- DMARx2Thresh

  Type_DMARxThresh get_DMARx2Thresh() { return Type_DMARxThresh(rw.template get<uint32>(0xC8u)); }
 
  void set_DMARx2Thresh(Type_DMARxThresh value) { rw.set(0xC8u,value.value); }
 
  Setter<Type_DMARxThresh> to_DMARx2Thresh() { return Setter<Type_DMARxThresh>(rw,0xC8u); }
 
  //--- DMARx3Thresh

  Type_DMARxThresh get_DMARx3Thresh() { return Type_DMARxThresh(rw.template get<uint32>(0xCCu)); }
 
  void set_DMARx3Thresh(Type_DMARxThresh value) { rw.set(0xCCu,value.value); }
 
  Setter<Type_DMARxThresh> to_DMARx3Thresh() { return Setter<Type_DMARxThresh>(rw,0xCCu); }
 
  //--- DMARx4Thresh

  Type_DMARxThresh get_DMARx4Thresh() { return Type_DMARxThresh(rw.template get<uint32>(0xD0u)); }
 
  void set_DMARx4Thresh(Type_DMARxThresh value) { rw.set(0xD0u,value.value); }
 
  Setter<Type_DMARxThresh> to_DMARx4Thresh() { return Setter<Type_DMARxThresh>(rw,0xD0u); }
 
  //--- DMARx5Thresh

  Type_DMARxThresh get_DMARx5Thresh() { return Type_DMARxThresh(rw.template get<uint32>(0xD4u)); }
 
  void set_DMARx5Thresh(Type_DMARxThresh value) { rw.set(0xD4u,value.value); }
 
  Setter<Type_DMARxThresh> to_DMARx5Thresh() { return Setter<Type_DMARxThresh>(rw,0xD4u); }
 
  //--- DMARx6Thresh

  Type_DMARxThresh get_DMARx6Thresh() { return Type_DMARxThresh(rw.template get<uint32>(0xD8u)); }
 
  void set_DMARx6Thresh(Type_DMARxThresh value) { rw.set(0xD8u,value.value); }
 
  Setter<Type_DMARxThresh> to_DMARx6Thresh() { return Setter<Type_DMARxThresh>(rw,0xD8u); }
 
  //--- DMARx7Thresh

  Type_DMARxThresh get_DMARx7Thresh() { return Type_DMARxThresh(rw.template get<uint32>(0xDCu)); }
 
  void set_DMARx7Thresh(Type_DMARxThresh value) { rw.set(0xDCu,value.value); }
 
  Setter<Type_DMARxThresh> to_DMARx7Thresh() { return Setter<Type_DMARxThresh>(rw,0xDCu); }
 
  //--- DMARxFree

  static Type_DMARxFree null_DMARxFree() { return Type_DMARxFree(0); }
 
  static Type_DMARxFree ones_DMARxFree() { return Type_DMARxFree(Type_DMARxFree::Type(-1)); }
 
  //--- DMARx0Free

  Type_DMARxFree get_DMARx0Free() { return Type_DMARxFree(rw.template get<uint32>(0xE0u)); }
 
  void set_DMARx0Free(Type_DMARxFree value) { rw.set(0xE0u,value.value); }
 
  Setter<Type_DMARxFree> to_DMARx0Free() { return Setter<Type_DMARxFree>(rw,0xE0u); }
 
  //--- DMARx1Free

  Type_DMARxFree get_DMARx1Free() { return Type_DMARxFree(rw.template get<uint32>(0xE4u)); }
 
  void set_DMARx1Free(Type_DMARxFree value) { rw.set(0xE4u,value.value); }
 
  Setter<Type_DMARxFree> to_DMARx1Free() { return Setter<Type_DMARxFree>(rw,0xE4u); }
 
  //--- DMARx2Free

  Type_DMARxFree get_DMARx2Free() { return Type_DMARxFree(rw.template get<uint32>(0xE8u)); }
 
  void set_DMARx2Free(Type_DMARxFree value) { rw.set(0xE8u,value.value); }
 
  Setter<Type_DMARxFree> to_DMARx2Free() { return Setter<Type_DMARxFree>(rw,0xE8u); }
 
  //--- DMARx3Free

  Type_DMARxFree get_DMARx3Free() { return Type_DMARxFree(rw.template get<uint32>(0xECu)); }
 
  void set_DMARx3Free(Type_DMARxFree value) { rw.set(0xECu,value.value); }
 
  Setter<Type_DMARxFree> to_DMARx3Free() { return Setter<Type_DMARxFree>(rw,0xECu); }
 
  //--- DMARx4Free

  Type_DMARxFree get_DMARx4Free() { return Type_DMARxFree(rw.template get<uint32>(0xF0u)); }
 
  void set_DMARx4Free(Type_DMARxFree value) { rw.set(0xF0u,value.value); }
 
  Setter<Type_DMARxFree> to_DMARx4Free() { return Setter<Type_DMARxFree>(rw,0xF0u); }
 
  //--- DMARx5Free

  Type_DMARxFree get_DMARx5Free() { return Type_DMARxFree(rw.template get<uint32>(0xF4u)); }
 
  void set_DMARx5Free(Type_DMARxFree value) { rw.set(0xF4u,value.value); }
 
  Setter<Type_DMARxFree> to_DMARx5Free() { return Setter<Type_DMARxFree>(rw,0xF4u); }
 
  //--- DMARx6Free

  Type_DMARxFree get_DMARx6Free() { return Type_DMARxFree(rw.template get<uint32>(0xF8u)); }
 
  void set_DMARx6Free(Type_DMARxFree value) { rw.set(0xF8u,value.value); }
 
  Setter<Type_DMARxFree> to_DMARx6Free() { return Setter<Type_DMARxFree>(rw,0xF8u); }
 
  //--- DMARx7Free

  Type_DMARxFree get_DMARx7Free() { return Type_DMARxFree(rw.template get<uint32>(0xFCu)); }
 
  void set_DMARx7Free(Type_DMARxFree value) { rw.set(0xFCu,value.value); }
 
  Setter<Type_DMARxFree> to_DMARx7Free() { return Setter<Type_DMARxFree>(rw,0xFCu); }
 
 };
 
/* struct StatBar<RW> */

template <class RW>
struct StatBar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit StatBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- GoodRxFrames

  Type_StatCounter get_GoodRxFrames() { return Type_StatCounter(rw.template get<uint32>(0x0u)); }
 
  void set_GoodRxFrames(Type_StatCounter value) { rw.set(0x0u,value); }
 
  void set_GoodRxFrames_null() { rw.set(0x0u,Type_StatCounter(0)); }
 
  void set_GoodRxFrames_ones() { rw.set(0x0u,Type_StatCounter(-1)); }
 
  //--- BroadcastRxFrames

  Type_StatCounter get_BroadcastRxFrames() { return Type_StatCounter(rw.template get<uint32>(0x4u)); }
 
  void set_BroadcastRxFrames(Type_StatCounter value) { rw.set(0x4u,value); }
 
  void set_BroadcastRxFrames_null() { rw.set(0x4u,Type_StatCounter(0)); }
 
  void set_BroadcastRxFrames_ones() { rw.set(0x4u,Type_StatCounter(-1)); }
 
  //--- MulticastRxFrames

  Type_StatCounter get_MulticastRxFrames() { return Type_StatCounter(rw.template get<uint32>(0x8u)); }
 
  void set_MulticastRxFrames(Type_StatCounter value) { rw.set(0x8u,value); }
 
  void set_MulticastRxFrames_null() { rw.set(0x8u,Type_StatCounter(0)); }
 
  void set_MulticastRxFrames_ones() { rw.set(0x8u,Type_StatCounter(-1)); }
 
  //--- PauseRxFrames

  Type_StatCounter get_PauseRxFrames() { return Type_StatCounter(rw.template get<uint32>(0xCu)); }
 
  void set_PauseRxFrames(Type_StatCounter value) { rw.set(0xCu,value); }
 
  void set_PauseRxFrames_null() { rw.set(0xCu,Type_StatCounter(0)); }
 
  void set_PauseRxFrames_ones() { rw.set(0xCu,Type_StatCounter(-1)); }
 
  //--- RxCRCErrors

  Type_StatCounter get_RxCRCErrors() { return Type_StatCounter(rw.template get<uint32>(0x10u)); }
 
  void set_RxCRCErrors(Type_StatCounter value) { rw.set(0x10u,value); }
 
  void set_RxCRCErrors_null() { rw.set(0x10u,Type_StatCounter(0)); }
 
  void set_RxCRCErrors_ones() { rw.set(0x10u,Type_StatCounter(-1)); }
 
  //--- RxAlignCodeErrors

  Type_StatCounter get_RxAlignCodeErrors() { return Type_StatCounter(rw.template get<uint32>(0x14u)); }
 
  void set_RxAlignCodeErrors(Type_StatCounter value) { rw.set(0x14u,value); }
 
  void set_RxAlignCodeErrors_null() { rw.set(0x14u,Type_StatCounter(0)); }
 
  void set_RxAlignCodeErrors_ones() { rw.set(0x14u,Type_StatCounter(-1)); }
 
  //--- OversizeRxFrames

  Type_StatCounter get_OversizeRxFrames() { return Type_StatCounter(rw.template get<uint32>(0x18u)); }
 
  void set_OversizeRxFrames(Type_StatCounter value) { rw.set(0x18u,value); }
 
  void set_OversizeRxFrames_null() { rw.set(0x18u,Type_StatCounter(0)); }
 
  void set_OversizeRxFrames_ones() { rw.set(0x18u,Type_StatCounter(-1)); }
 
  //--- RxJabbers

  Type_StatCounter get_RxJabbers() { return Type_StatCounter(rw.template get<uint32>(0x1Cu)); }
 
  void set_RxJabbers(Type_StatCounter value) { rw.set(0x1Cu,value); }
 
  void set_RxJabbers_null() { rw.set(0x1Cu,Type_StatCounter(0)); }
 
  void set_RxJabbers_ones() { rw.set(0x1Cu,Type_StatCounter(-1)); }
 
  //--- ShortRxFrames

  Type_StatCounter get_ShortRxFrames() { return Type_StatCounter(rw.template get<uint32>(0x20u)); }
 
  void set_ShortRxFrames(Type_StatCounter value) { rw.set(0x20u,value); }
 
  void set_ShortRxFrames_null() { rw.set(0x20u,Type_StatCounter(0)); }
 
  void set_ShortRxFrames_ones() { rw.set(0x20u,Type_StatCounter(-1)); }
 
  //--- RxFragments

  Type_StatCounter get_RxFragments() { return Type_StatCounter(rw.template get<uint32>(0x24u)); }
 
  void set_RxFragments(Type_StatCounter value) { rw.set(0x24u,value); }
 
  void set_RxFragments_null() { rw.set(0x24u,Type_StatCounter(0)); }
 
  void set_RxFragments_ones() { rw.set(0x24u,Type_StatCounter(-1)); }
 
  //--- RxOctets

  Type_StatCounter get_RxOctets() { return Type_StatCounter(rw.template get<uint32>(0x28u)); }
 
  void set_RxOctets(Type_StatCounter value) { rw.set(0x28u,value); }
 
  void set_RxOctets_null() { rw.set(0x28u,Type_StatCounter(0)); }
 
  void set_RxOctets_ones() { rw.set(0x28u,Type_StatCounter(-1)); }
 
  //--- GoodTxFrames

  Type_StatCounter get_GoodTxFrames() { return Type_StatCounter(rw.template get<uint32>(0x2Cu)); }
 
  void set_GoodTxFrames(Type_StatCounter value) { rw.set(0x2Cu,value); }
 
  void set_GoodTxFrames_null() { rw.set(0x2Cu,Type_StatCounter(0)); }
 
  void set_GoodTxFrames_ones() { rw.set(0x2Cu,Type_StatCounter(-1)); }
 
  //--- BroadcastTxFrames

  Type_StatCounter get_BroadcastTxFrames() { return Type_StatCounter(rw.template get<uint32>(0x30u)); }
 
  void set_BroadcastTxFrames(Type_StatCounter value) { rw.set(0x30u,value); }
 
  void set_BroadcastTxFrames_null() { rw.set(0x30u,Type_StatCounter(0)); }
 
  void set_BroadcastTxFrames_ones() { rw.set(0x30u,Type_StatCounter(-1)); }
 
  //--- MulticastTxFrames

  Type_StatCounter get_MulticastTxFrames() { return Type_StatCounter(rw.template get<uint32>(0x34u)); }
 
  void set_MulticastTxFrames(Type_StatCounter value) { rw.set(0x34u,value); }
 
  void set_MulticastTxFrames_null() { rw.set(0x34u,Type_StatCounter(0)); }
 
  void set_MulticastTxFrames_ones() { rw.set(0x34u,Type_StatCounter(-1)); }
 
  //--- PauseTxFrames

  Type_StatCounter get_PauseTxFrames() { return Type_StatCounter(rw.template get<uint32>(0x38u)); }
 
  void set_PauseTxFrames(Type_StatCounter value) { rw.set(0x38u,value); }
 
  void set_PauseTxFrames_null() { rw.set(0x38u,Type_StatCounter(0)); }
 
  void set_PauseTxFrames_ones() { rw.set(0x38u,Type_StatCounter(-1)); }
 
  //--- DeferredTxFrames

  Type_StatCounter get_DeferredTxFrames() { return Type_StatCounter(rw.template get<uint32>(0x3Cu)); }
 
  void set_DeferredTxFrames(Type_StatCounter value) { rw.set(0x3Cu,value); }
 
  void set_DeferredTxFrames_null() { rw.set(0x3Cu,Type_StatCounter(0)); }
 
  void set_DeferredTxFrames_ones() { rw.set(0x3Cu,Type_StatCounter(-1)); }
 
  //--- Collisions

  Type_StatCounter get_Collisions() { return Type_StatCounter(rw.template get<uint32>(0x40u)); }
 
  void set_Collisions(Type_StatCounter value) { rw.set(0x40u,value); }
 
  void set_Collisions_null() { rw.set(0x40u,Type_StatCounter(0)); }
 
  void set_Collisions_ones() { rw.set(0x40u,Type_StatCounter(-1)); }
 
  //--- SingleCollisionTxFrames

  Type_StatCounter get_SingleCollisionTxFrames() { return Type_StatCounter(rw.template get<uint32>(0x44u)); }
 
  void set_SingleCollisionTxFrames(Type_StatCounter value) { rw.set(0x44u,value); }
 
  void set_SingleCollisionTxFrames_null() { rw.set(0x44u,Type_StatCounter(0)); }
 
  void set_SingleCollisionTxFrames_ones() { rw.set(0x44u,Type_StatCounter(-1)); }
 
  //--- MultipleCollisionTxFrames

  Type_StatCounter get_MultipleCollisionTxFrames() { return Type_StatCounter(rw.template get<uint32>(0x48u)); }
 
  void set_MultipleCollisionTxFrames(Type_StatCounter value) { rw.set(0x48u,value); }
 
  void set_MultipleCollisionTxFrames_null() { rw.set(0x48u,Type_StatCounter(0)); }
 
  void set_MultipleCollisionTxFrames_ones() { rw.set(0x48u,Type_StatCounter(-1)); }
 
  //--- ExcessiveCollisions

  Type_StatCounter get_ExcessiveCollisions() { return Type_StatCounter(rw.template get<uint32>(0x4Cu)); }
 
  void set_ExcessiveCollisions(Type_StatCounter value) { rw.set(0x4Cu,value); }
 
  void set_ExcessiveCollisions_null() { rw.set(0x4Cu,Type_StatCounter(0)); }
 
  void set_ExcessiveCollisions_ones() { rw.set(0x4Cu,Type_StatCounter(-1)); }
 
  //--- LateCollisions

  Type_StatCounter get_LateCollisions() { return Type_StatCounter(rw.template get<uint32>(0x50u)); }
 
  void set_LateCollisions(Type_StatCounter value) { rw.set(0x50u,value); }
 
  void set_LateCollisions_null() { rw.set(0x50u,Type_StatCounter(0)); }
 
  void set_LateCollisions_ones() { rw.set(0x50u,Type_StatCounter(-1)); }
 
  //--- TxUnderrun

  Type_StatCounter get_TxUnderrun() { return Type_StatCounter(rw.template get<uint32>(0x54u)); }
 
  void set_TxUnderrun(Type_StatCounter value) { rw.set(0x54u,value); }
 
  void set_TxUnderrun_null() { rw.set(0x54u,Type_StatCounter(0)); }
 
  void set_TxUnderrun_ones() { rw.set(0x54u,Type_StatCounter(-1)); }
 
  //--- CarrierSenseErrors

  Type_StatCounter get_CarrierSenseErrors() { return Type_StatCounter(rw.template get<uint32>(0x58u)); }
 
  void set_CarrierSenseErrors(Type_StatCounter value) { rw.set(0x58u,value); }
 
  void set_CarrierSenseErrors_null() { rw.set(0x58u,Type_StatCounter(0)); }
 
  void set_CarrierSenseErrors_ones() { rw.set(0x58u,Type_StatCounter(-1)); }
 
  //--- TxOctets

  Type_StatCounter get_TxOctets() { return Type_StatCounter(rw.template get<uint32>(0x5Cu)); }
 
  void set_TxOctets(Type_StatCounter value) { rw.set(0x5Cu,value); }
 
  void set_TxOctets_null() { rw.set(0x5Cu,Type_StatCounter(0)); }
 
  void set_TxOctets_ones() { rw.set(0x5Cu,Type_StatCounter(-1)); }
 
  //--- Frame64RxTx

  Type_StatCounter get_Frame64RxTx() { return Type_StatCounter(rw.template get<uint32>(0x60u)); }
 
  void set_Frame64RxTx(Type_StatCounter value) { rw.set(0x60u,value); }
 
  void set_Frame64RxTx_null() { rw.set(0x60u,Type_StatCounter(0)); }
 
  void set_Frame64RxTx_ones() { rw.set(0x60u,Type_StatCounter(-1)); }
 
  //--- Frame128RxTx

  Type_StatCounter get_Frame128RxTx() { return Type_StatCounter(rw.template get<uint32>(0x64u)); }
 
  void set_Frame128RxTx(Type_StatCounter value) { rw.set(0x64u,value); }
 
  void set_Frame128RxTx_null() { rw.set(0x64u,Type_StatCounter(0)); }
 
  void set_Frame128RxTx_ones() { rw.set(0x64u,Type_StatCounter(-1)); }
 
  //--- Frame256RxTx

  Type_StatCounter get_Frame256RxTx() { return Type_StatCounter(rw.template get<uint32>(0x68u)); }
 
  void set_Frame256RxTx(Type_StatCounter value) { rw.set(0x68u,value); }
 
  void set_Frame256RxTx_null() { rw.set(0x68u,Type_StatCounter(0)); }
 
  void set_Frame256RxTx_ones() { rw.set(0x68u,Type_StatCounter(-1)); }
 
  //--- Frame512RxTx

  Type_StatCounter get_Frame512RxTx() { return Type_StatCounter(rw.template get<uint32>(0x6Cu)); }
 
  void set_Frame512RxTx(Type_StatCounter value) { rw.set(0x6Cu,value); }
 
  void set_Frame512RxTx_null() { rw.set(0x6Cu,Type_StatCounter(0)); }
 
  void set_Frame512RxTx_ones() { rw.set(0x6Cu,Type_StatCounter(-1)); }
 
  //--- Frame1024RxTx

  Type_StatCounter get_Frame1024RxTx() { return Type_StatCounter(rw.template get<uint32>(0x70u)); }
 
  void set_Frame1024RxTx(Type_StatCounter value) { rw.set(0x70u,value); }
 
  void set_Frame1024RxTx_null() { rw.set(0x70u,Type_StatCounter(0)); }
 
  void set_Frame1024RxTx_ones() { rw.set(0x70u,Type_StatCounter(-1)); }
 
  //--- NetOctets

  Type_StatCounter get_NetOctets() { return Type_StatCounter(rw.template get<uint32>(0x74u)); }
 
  void set_NetOctets(Type_StatCounter value) { rw.set(0x74u,value); }
 
  void set_NetOctets_null() { rw.set(0x74u,Type_StatCounter(0)); }
 
  void set_NetOctets_ones() { rw.set(0x74u,Type_StatCounter(-1)); }
 
  //--- RxStartOfFrameOverruns

  Type_StatCounter get_RxStartOfFrameOverruns() { return Type_StatCounter(rw.template get<uint32>(0x78u)); }
 
  void set_RxStartOfFrameOverruns(Type_StatCounter value) { rw.set(0x78u,value); }
 
  void set_RxStartOfFrameOverruns_null() { rw.set(0x78u,Type_StatCounter(0)); }
 
  void set_RxStartOfFrameOverruns_ones() { rw.set(0x78u,Type_StatCounter(-1)); }
 
  //--- RxMiddleOfFrameOverruns

  Type_StatCounter get_RxMiddleOfFrameOverruns() { return Type_StatCounter(rw.template get<uint32>(0x7Cu)); }
 
  void set_RxMiddleOfFrameOverruns(Type_StatCounter value) { rw.set(0x7Cu,value); }
 
  void set_RxMiddleOfFrameOverruns_null() { rw.set(0x7Cu,Type_StatCounter(0)); }
 
  void set_RxMiddleOfFrameOverruns_ones() { rw.set(0x7Cu,Type_StatCounter(-1)); }
 
  //--- RxDMAOverruns

  Type_StatCounter get_RxDMAOverruns() { return Type_StatCounter(rw.template get<uint32>(0x80u)); }
 
  void set_RxDMAOverruns(Type_StatCounter value) { rw.set(0x80u,value); }
 
  void set_RxDMAOverruns_null() { rw.set(0x80u,Type_StatCounter(0)); }
 
  void set_RxDMAOverruns_ones() { rw.set(0x80u,Type_StatCounter(-1)); }
 
 };
 
/* struct DescBar<RW> */

template <class RW>
struct DescBar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit DescBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- HeadTx

  Type_DescPtr get_HeadTx(AddressType ind) { return Type_DescPtr(rw.template get<uint32>(0x0u + ind*4u)); }
 
  void set_HeadTx(AddressType ind,Type_DescPtr value) { rw.set(0x0u + ind*4u,value); }
 
  void set_HeadTx_null(AddressType ind) { rw.set(0x0u + ind*4u,Type_DescPtr(0)); }
 
  void set_HeadTx_ones(AddressType ind) { rw.set(0x0u + ind*4u,Type_DescPtr(-1)); }
 
  //--- HeadRx

  Type_DescPtr get_HeadRx(AddressType ind) { return Type_DescPtr(rw.template get<uint32>(0x20u + ind*4u)); }
 
  void set_HeadRx(AddressType ind,Type_DescPtr value) { rw.set(0x20u + ind*4u,value); }
 
  void set_HeadRx_null(AddressType ind) { rw.set(0x20u + ind*4u,Type_DescPtr(0)); }
 
  void set_HeadRx_ones(AddressType ind) { rw.set(0x20u + ind*4u,Type_DescPtr(-1)); }
 
  //--- CompleteTx

  Type_DescPtr get_CompleteTx(AddressType ind) { return Type_DescPtr(rw.template get<uint32>(0x40u + ind*4u)); }
 
  void set_CompleteTx(AddressType ind,Type_DescPtr value) { rw.set(0x40u + ind*4u,value); }
 
  void set_CompleteTx_null(AddressType ind) { rw.set(0x40u + ind*4u,Type_DescPtr(0)); }
 
  void set_CompleteTx_ones(AddressType ind) { rw.set(0x40u + ind*4u,Type_DescPtr(-1)); }
 
  //--- CompleteRx

  Type_DescPtr get_CompleteRx(AddressType ind) { return Type_DescPtr(rw.template get<uint32>(0x60u + ind*4u)); }
 
  void set_CompleteRx(AddressType ind,Type_DescPtr value) { rw.set(0x60u + ind*4u,value); }
 
  void set_CompleteRx_null(AddressType ind) { rw.set(0x60u + ind*4u,Type_DescPtr(0)); }
 
  void set_CompleteRx_ones(AddressType ind) { rw.set(0x60u + ind*4u,Type_DescPtr(-1)); }
 
  //--- DescPtr

 };
 
/* struct TimeSyncBar<RW> */

template <class RW>
struct TimeSyncBar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit TimeSyncBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- TimeSyncControl

  Type_TimeSyncControl get_TimeSyncControl() { return Type_TimeSyncControl(rw.template get<uint32>(0x4u)); }
 
  void set_TimeSyncControl(Type_TimeSyncControl value) { rw.set(0x4u,value.value); }
 
  Setter<Type_TimeSyncControl> to_TimeSyncControl() { return Setter<Type_TimeSyncControl>(rw,0x4u); }
 
  static Type_TimeSyncControl null_TimeSyncControl() { return Type_TimeSyncControl(0); }
 
  static Type_TimeSyncControl ones_TimeSyncControl() { return Type_TimeSyncControl(Type_TimeSyncControl::Type(-1)); }
 
  //--- TimeSyncTSPush

  Type_TimeSyncTSPush get_TimeSyncTSPush() { return Type_TimeSyncTSPush(rw.template get<uint32>(0xCu)); }
 
  void set_TimeSyncTSPush(Type_TimeSyncTSPush value) { rw.set(0xCu,value.value); }
 
  Setter<Type_TimeSyncTSPush> to_TimeSyncTSPush() { return Setter<Type_TimeSyncTSPush>(rw,0xCu); }
 
  static Type_TimeSyncTSPush null_TimeSyncTSPush() { return Type_TimeSyncTSPush(0); }
 
  static Type_TimeSyncTSPush ones_TimeSyncTSPush() { return Type_TimeSyncTSPush(Type_TimeSyncTSPush::Type(-1)); }
 
  //--- TimeSyncTSValue

  Type_TimeSyncTSValue get_TimeSyncTSValue() { return Type_TimeSyncTSValue(rw.template get<uint32>(0x10u)); }
 
  void set_TimeSyncTSValue(Type_TimeSyncTSValue value) { rw.set(0x10u,value); }
 
  void set_TimeSyncTSValue_null() { rw.set(0x10u,Type_TimeSyncTSValue(0)); }
 
  void set_TimeSyncTSValue_ones() { rw.set(0x10u,Type_TimeSyncTSValue(-1)); }
 
  //--- TimeSyncTSLoad

  Type_TimeSyncTSLoad get_TimeSyncTSLoad() { return Type_TimeSyncTSLoad(rw.template get<uint32>(0x14u)); }
 
  void set_TimeSyncTSLoad(Type_TimeSyncTSLoad value) { rw.set(0x14u,value.value); }
 
  Setter<Type_TimeSyncTSLoad> to_TimeSyncTSLoad() { return Setter<Type_TimeSyncTSLoad>(rw,0x14u); }
 
  static Type_TimeSyncTSLoad null_TimeSyncTSLoad() { return Type_TimeSyncTSLoad(0); }
 
  static Type_TimeSyncTSLoad ones_TimeSyncTSLoad() { return Type_TimeSyncTSLoad(Type_TimeSyncTSLoad::Type(-1)); }
 
  //--- TimeSyncIntStatusRaw

  Type_TimeSyncIntStatus get_TimeSyncIntStatusRaw() { return Type_TimeSyncIntStatus(rw.template get<uint32>(0x20u)); }
 
  void set_TimeSyncIntStatusRaw(Type_TimeSyncIntStatus value) { rw.set(0x20u,value.value); }
 
  Setter<Type_TimeSyncIntStatus> to_TimeSyncIntStatusRaw() { return Setter<Type_TimeSyncIntStatus>(rw,0x20u); }
 
  //--- TimeSyncIntStatus

  Type_TimeSyncIntStatus get_TimeSyncIntStatus() { return Type_TimeSyncIntStatus(rw.template get<uint32>(0x24u)); }
 
  static Type_TimeSyncIntStatus null_TimeSyncIntStatus() { return Type_TimeSyncIntStatus(0); }
 
  static Type_TimeSyncIntStatus ones_TimeSyncIntStatus() { return Type_TimeSyncIntStatus(Type_TimeSyncIntStatus::Type(-1)); }
 
  //--- TimeSyncIntEnable

  Type_TimeSyncIntStatus get_TimeSyncIntEnable() { return Type_TimeSyncIntStatus(rw.template get<uint32>(0x28u)); }
 
  void set_TimeSyncIntEnable(Type_TimeSyncIntStatus value) { rw.set(0x28u,value.value); }
 
  Setter<Type_TimeSyncIntStatus> to_TimeSyncIntEnable() { return Setter<Type_TimeSyncIntStatus>(rw,0x28u); }
 
  //--- TimeSyncEventPop

  Type_TimeSyncEventPop get_TimeSyncEventPop() { return Type_TimeSyncEventPop(rw.template get<uint32>(0x30u)); }
 
  void set_TimeSyncEventPop(Type_TimeSyncEventPop value) { rw.set(0x30u,value.value); }
 
  Setter<Type_TimeSyncEventPop> to_TimeSyncEventPop() { return Setter<Type_TimeSyncEventPop>(rw,0x30u); }
 
  static Type_TimeSyncEventPop null_TimeSyncEventPop() { return Type_TimeSyncEventPop(0); }
 
  static Type_TimeSyncEventPop ones_TimeSyncEventPop() { return Type_TimeSyncEventPop(Type_TimeSyncEventPop::Type(-1)); }
 
  //--- TimeSyncEventTS

  Type_TimeSyncEventTS get_TimeSyncEventTS() { return Type_TimeSyncEventTS(rw.template get<uint32>(0x34u)); }
 
  //--- TimeSyncEvent

  Type_TimeSyncEvent get_TimeSyncEvent() { return Type_TimeSyncEvent(rw.template get<uint32>(0x38u)); }
 
  static Type_TimeSyncEvent null_TimeSyncEvent() { return Type_TimeSyncEvent(0); }
 
  static Type_TimeSyncEvent ones_TimeSyncEvent() { return Type_TimeSyncEvent(Type_TimeSyncEvent::Type(-1)); }
 
 };
 
/* struct ALEBar<RW> */

template <class RW>
struct ALEBar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit ALEBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- ALEControl

  Type_ALEControl get_ALEControl() { return Type_ALEControl(rw.template get<uint32>(0x8u)); }
 
  void set_ALEControl(Type_ALEControl value) { rw.set(0x8u,value.value); }
 
  Setter<Type_ALEControl> to_ALEControl() { return Setter<Type_ALEControl>(rw,0x8u); }
 
  static Type_ALEControl null_ALEControl() { return Type_ALEControl(0); }
 
  static Type_ALEControl ones_ALEControl() { return Type_ALEControl(Type_ALEControl::Type(-1)); }
 
  //--- ALEPrescale

  Type_ALEPrescale get_ALEPrescale() { return Type_ALEPrescale(rw.template get<uint32>(0x10u)); }
 
  void set_ALEPrescale(Type_ALEPrescale value) { rw.set(0x10u,value.value); }
 
  Setter<Type_ALEPrescale> to_ALEPrescale() { return Setter<Type_ALEPrescale>(rw,0x10u); }
 
  static Type_ALEPrescale null_ALEPrescale() { return Type_ALEPrescale(0); }
 
  static Type_ALEPrescale ones_ALEPrescale() { return Type_ALEPrescale(Type_ALEPrescale::Type(-1)); }
 
  //--- ALEUnknownVLAN

  Type_ALEUnknownVLAN get_ALEUnknownVLAN() { return Type_ALEUnknownVLAN(rw.template get<uint32>(0x18u)); }
 
  void set_ALEUnknownVLAN(Type_ALEUnknownVLAN value) { rw.set(0x18u,value.value); }
 
  Setter<Type_ALEUnknownVLAN> to_ALEUnknownVLAN() { return Setter<Type_ALEUnknownVLAN>(rw,0x18u); }
 
  static Type_ALEUnknownVLAN null_ALEUnknownVLAN() { return Type_ALEUnknownVLAN(0); }
 
  static Type_ALEUnknownVLAN ones_ALEUnknownVLAN() { return Type_ALEUnknownVLAN(Type_ALEUnknownVLAN::Type(-1)); }
 
  //--- ALETableControl

  Type_ALETableControl get_ALETableControl() { return Type_ALETableControl(rw.template get<uint32>(0x20u)); }
 
  void set_ALETableControl(Type_ALETableControl value) { rw.set(0x20u,value.value); }
 
  Setter<Type_ALETableControl> to_ALETableControl() { return Setter<Type_ALETableControl>(rw,0x20u); }
 
  static Type_ALETableControl null_ALETableControl() { return Type_ALETableControl(0); }
 
  static Type_ALETableControl ones_ALETableControl() { return Type_ALETableControl(Type_ALETableControl::Type(-1)); }
 
  //--- ALETableWord2

  Type_ALETableWord2 get_ALETableWord2() { return Type_ALETableWord2(rw.template get<uint32>(0x34u)); }
 
  void set_ALETableWord2(Type_ALETableWord2 value) { rw.set(0x34u,value.value); }
 
  Setter<Type_ALETableWord2> to_ALETableWord2() { return Setter<Type_ALETableWord2>(rw,0x34u); }
 
  static Type_ALETableWord2 null_ALETableWord2() { return Type_ALETableWord2(0); }
 
  static Type_ALETableWord2 ones_ALETableWord2() { return Type_ALETableWord2(Type_ALETableWord2::Type(-1)); }
 
  //--- ALETableWord1

  Type_ALETableWord1 get_ALETableWord1() { return Type_ALETableWord1(rw.template get<uint32>(0x38u)); }
 
  void set_ALETableWord1(Type_ALETableWord1 value) { rw.set(0x38u,value.value); }
 
  Setter<Type_ALETableWord1> to_ALETableWord1() { return Setter<Type_ALETableWord1>(rw,0x38u); }
 
  static Type_ALETableWord1 null_ALETableWord1() { return Type_ALETableWord1(0); }
 
  static Type_ALETableWord1 ones_ALETableWord1() { return Type_ALETableWord1(Type_ALETableWord1::Type(-1)); }
 
  //--- ALETableWord0

  Type_ALETableWord0 get_ALETableWord0() { return Type_ALETableWord0(rw.template get<uint32>(0x3Cu)); }
 
  void set_ALETableWord0(Type_ALETableWord0 value) { rw.set(0x3Cu,value.value); }
 
  Setter<Type_ALETableWord0> to_ALETableWord0() { return Setter<Type_ALETableWord0>(rw,0x3Cu); }
 
  static Type_ALETableWord0 null_ALETableWord0() { return Type_ALETableWord0(0); }
 
  static Type_ALETableWord0 ones_ALETableWord0() { return Type_ALETableWord0(Type_ALETableWord0::Type(-1)); }
 
  //--- ALEPortControl

  static Type_ALEPortControl null_ALEPortControl() { return Type_ALEPortControl(0); }
 
  static Type_ALEPortControl ones_ALEPortControl() { return Type_ALEPortControl(Type_ALEPortControl::Type(-1)); }
 
  //--- ALEPort0Control

  Type_ALEPortControl get_ALEPort0Control() { return Type_ALEPortControl(rw.template get<uint32>(0x40u)); }
 
  void set_ALEPort0Control(Type_ALEPortControl value) { rw.set(0x40u,value.value); }
 
  Setter<Type_ALEPortControl> to_ALEPort0Control() { return Setter<Type_ALEPortControl>(rw,0x40u); }
 
  //--- ALEPort1Control

  Type_ALEPortControl get_ALEPort1Control() { return Type_ALEPortControl(rw.template get<uint32>(0x44u)); }
 
  void set_ALEPort1Control(Type_ALEPortControl value) { rw.set(0x44u,value.value); }
 
  Setter<Type_ALEPortControl> to_ALEPort1Control() { return Setter<Type_ALEPortControl>(rw,0x44u); }
 
  //--- ALEPort2Control

  Type_ALEPortControl get_ALEPort2Control() { return Type_ALEPortControl(rw.template get<uint32>(0x48u)); }
 
  void set_ALEPort2Control(Type_ALEPortControl value) { rw.set(0x48u,value.value); }
 
  Setter<Type_ALEPortControl> to_ALEPort2Control() { return Setter<Type_ALEPortControl>(rw,0x48u); }
 
  //--- ALEPort3Control

  Type_ALEPortControl get_ALEPort3Control() { return Type_ALEPortControl(rw.template get<uint32>(0x4Cu)); }
 
  void set_ALEPort3Control(Type_ALEPortControl value) { rw.set(0x4Cu,value.value); }
 
  Setter<Type_ALEPortControl> to_ALEPort3Control() { return Setter<Type_ALEPortControl>(rw,0x4Cu); }
 
  //--- ALEPort4Control

  Type_ALEPortControl get_ALEPort4Control() { return Type_ALEPortControl(rw.template get<uint32>(0x50u)); }
 
  void set_ALEPort4Control(Type_ALEPortControl value) { rw.set(0x50u,value.value); }
 
  Setter<Type_ALEPortControl> to_ALEPort4Control() { return Setter<Type_ALEPortControl>(rw,0x50u); }
 
  //--- ALEPort5Control

  Type_ALEPortControl get_ALEPort5Control() { return Type_ALEPortControl(rw.template get<uint32>(0x54u)); }
 
  void set_ALEPort5Control(Type_ALEPortControl value) { rw.set(0x54u,value.value); }
 
  Setter<Type_ALEPortControl> to_ALEPort5Control() { return Setter<Type_ALEPortControl>(rw,0x54u); }
 
 };
 
/* struct SliverBar<RW> */

template <class RW>
struct SliverBar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit SliverBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- SliverControl

  Type_SliverControl get_SliverControl() { return Type_SliverControl(rw.template get<uint32>(0x4u)); }
 
  void set_SliverControl(Type_SliverControl value) { rw.set(0x4u,value.value); }
 
  Setter<Type_SliverControl> to_SliverControl() { return Setter<Type_SliverControl>(rw,0x4u); }
 
  static Type_SliverControl null_SliverControl() { return Type_SliverControl(0); }
 
  static Type_SliverControl ones_SliverControl() { return Type_SliverControl(Type_SliverControl::Type(-1)); }
 
  //--- SliverStatus

  Type_SliverStatus get_SliverStatus() { return Type_SliverStatus(rw.template get<uint32>(0x8u)); }
 
  static Type_SliverStatus null_SliverStatus() { return Type_SliverStatus(0); }
 
  static Type_SliverStatus ones_SliverStatus() { return Type_SliverStatus(Type_SliverStatus::Type(-1)); }
 
  //--- SliverSoftReset

  Type_SliverSoftReset get_SliverSoftReset() { return Type_SliverSoftReset(rw.template get<uint32>(0xCu)); }
 
  void set_SliverSoftReset(Type_SliverSoftReset value) { rw.set(0xCu,value.value); }
 
  Setter<Type_SliverSoftReset> to_SliverSoftReset() { return Setter<Type_SliverSoftReset>(rw,0xCu); }
 
  static Type_SliverSoftReset null_SliverSoftReset() { return Type_SliverSoftReset(0); }
 
  static Type_SliverSoftReset ones_SliverSoftReset() { return Type_SliverSoftReset(Type_SliverSoftReset::Type(-1)); }
 
  //--- SliverRxMaxLen

  Type_SliverRxMaxLen get_SliverRxMaxLen() { return Type_SliverRxMaxLen(rw.template get<uint32>(0x10u)); }
 
  void set_SliverRxMaxLen(Type_SliverRxMaxLen value) { rw.set(0x10u,value.value); }
 
  Setter<Type_SliverRxMaxLen> to_SliverRxMaxLen() { return Setter<Type_SliverRxMaxLen>(rw,0x10u); }
 
  static Type_SliverRxMaxLen null_SliverRxMaxLen() { return Type_SliverRxMaxLen(0); }
 
  static Type_SliverRxMaxLen ones_SliverRxMaxLen() { return Type_SliverRxMaxLen(Type_SliverRxMaxLen::Type(-1)); }
 
  //--- SliverBOFFTest

  Type_SliverBOFFTest get_SliverBOFFTest() { return Type_SliverBOFFTest(rw.template get<uint32>(0x14u)); }
 
  void set_SliverBOFFTest(Type_SliverBOFFTest value) { rw.set(0x14u,value.value); }
 
  Setter<Type_SliverBOFFTest> to_SliverBOFFTest() { return Setter<Type_SliverBOFFTest>(rw,0x14u); }
 
  static Type_SliverBOFFTest null_SliverBOFFTest() { return Type_SliverBOFFTest(0); }
 
  static Type_SliverBOFFTest ones_SliverBOFFTest() { return Type_SliverBOFFTest(Type_SliverBOFFTest::Type(-1)); }
 
  //--- SliverRxPause

  Type_SliverRxPause get_SliverRxPause() { return Type_SliverRxPause(rw.template get<uint32>(0x18u)); }
 
  void set_SliverRxPause(Type_SliverRxPause value) { rw.set(0x18u,value.value); }
 
  Setter<Type_SliverRxPause> to_SliverRxPause() { return Setter<Type_SliverRxPause>(rw,0x18u); }
 
  static Type_SliverRxPause null_SliverRxPause() { return Type_SliverRxPause(0); }
 
  static Type_SliverRxPause ones_SliverRxPause() { return Type_SliverRxPause(Type_SliverRxPause::Type(-1)); }
 
  //--- SliverTxPause

  Type_SliverTxPause get_SliverTxPause() { return Type_SliverTxPause(rw.template get<uint32>(0x1Cu)); }
 
  void set_SliverTxPause(Type_SliverTxPause value) { rw.set(0x1Cu,value.value); }
 
  Setter<Type_SliverTxPause> to_SliverTxPause() { return Setter<Type_SliverTxPause>(rw,0x1Cu); }
 
  static Type_SliverTxPause null_SliverTxPause() { return Type_SliverTxPause(0); }
 
  static Type_SliverTxPause ones_SliverTxPause() { return Type_SliverTxPause(Type_SliverTxPause::Type(-1)); }
 
  //--- SliverEMControl

  Type_SliverEMControl get_SliverEMControl() { return Type_SliverEMControl(rw.template get<uint32>(0x20u)); }
 
  void set_SliverEMControl(Type_SliverEMControl value) { rw.set(0x20u,value.value); }
 
  Setter<Type_SliverEMControl> to_SliverEMControl() { return Setter<Type_SliverEMControl>(rw,0x20u); }
 
  static Type_SliverEMControl null_SliverEMControl() { return Type_SliverEMControl(0); }
 
  static Type_SliverEMControl ones_SliverEMControl() { return Type_SliverEMControl(Type_SliverEMControl::Type(-1)); }
 
  //--- SliverRxPriMap

  Type_SliverRxPriMap get_SliverRxPriMap() { return Type_SliverRxPriMap(rw.template get<uint32>(0x24u)); }
 
  void set_SliverRxPriMap(Type_SliverRxPriMap value) { rw.set(0x24u,value.value); }
 
  Setter<Type_SliverRxPriMap> to_SliverRxPriMap() { return Setter<Type_SliverRxPriMap>(rw,0x24u); }
 
  static Type_SliverRxPriMap null_SliverRxPriMap() { return Type_SliverRxPriMap(0); }
 
  static Type_SliverRxPriMap ones_SliverRxPriMap() { return Type_SliverRxPriMap(Type_SliverRxPriMap::Type(-1)); }
 
  //--- SliverTxGap

  Type_SliverTxGap get_SliverTxGap() { return Type_SliverTxGap(rw.template get<uint32>(0x28u)); }
 
  void set_SliverTxGap(Type_SliverTxGap value) { rw.set(0x28u,value.value); }
 
  Setter<Type_SliverTxGap> to_SliverTxGap() { return Setter<Type_SliverTxGap>(rw,0x28u); }
 
  static Type_SliverTxGap null_SliverTxGap() { return Type_SliverTxGap(0); }
 
  static Type_SliverTxGap ones_SliverTxGap() { return Type_SliverTxGap(Type_SliverTxGap::Type(-1)); }
 
 };
 
/* struct WRBar<RW> */

template <class RW>
struct WRBar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit WRBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- WRSoftReset

  Type_WRSoftReset get_WRSoftReset() { return Type_WRSoftReset(rw.template get<uint32>(0x4u)); }
 
  void set_WRSoftReset(Type_WRSoftReset value) { rw.set(0x4u,value.value); }
 
  Setter<Type_WRSoftReset> to_WRSoftReset() { return Setter<Type_WRSoftReset>(rw,0x4u); }
 
  static Type_WRSoftReset null_WRSoftReset() { return Type_WRSoftReset(0); }
 
  static Type_WRSoftReset ones_WRSoftReset() { return Type_WRSoftReset(Type_WRSoftReset::Type(-1)); }
 
  //--- WRControl

  Type_WRControl get_WRControl() { return Type_WRControl(rw.template get<uint32>(0x8u)); }
 
  void set_WRControl(Type_WRControl value) { rw.set(0x8u,value.value); }
 
  Setter<Type_WRControl> to_WRControl() { return Setter<Type_WRControl>(rw,0x8u); }
 
  static Type_WRControl null_WRControl() { return Type_WRControl(0); }
 
  static Type_WRControl ones_WRControl() { return Type_WRControl(Type_WRControl::Type(-1)); }
 
  //--- WRIntControl

  Type_WRIntControl get_WRIntControl() { return Type_WRIntControl(rw.template get<uint32>(0xCu)); }
 
  void set_WRIntControl(Type_WRIntControl value) { rw.set(0xCu,value.value); }
 
  Setter<Type_WRIntControl> to_WRIntControl() { return Setter<Type_WRIntControl>(rw,0xCu); }
 
  static Type_WRIntControl null_WRIntControl() { return Type_WRIntControl(0); }
 
  static Type_WRIntControl ones_WRIntControl() { return Type_WRIntControl(Type_WRIntControl::Type(-1)); }
 
  //--- WRC0RxThreshEnable

  Type_WRC0RxThreshEnable get_WRC0RxThreshEnable() { return Type_WRC0RxThreshEnable(rw.template get<uint32>(0x10u)); }
 
  void set_WRC0RxThreshEnable(Type_WRC0RxThreshEnable value) { rw.set(0x10u,value); }
 
  void set_WRC0RxThreshEnable_null() { rw.set(0x10u,Type_WRC0RxThreshEnable(0)); }
 
  void set_WRC0RxThreshEnable_ones() { rw.set(0x10u,Type_WRC0RxThreshEnable(-1)); }
 
  //--- WRC0RxEnable

  Type_WRC0RxEnable get_WRC0RxEnable() { return Type_WRC0RxEnable(rw.template get<uint32>(0x14u)); }
 
  void set_WRC0RxEnable(Type_WRC0RxEnable value) { rw.set(0x14u,value); }
 
  void set_WRC0RxEnable_null() { rw.set(0x14u,Type_WRC0RxEnable(0)); }
 
  void set_WRC0RxEnable_ones() { rw.set(0x14u,Type_WRC0RxEnable(-1)); }
 
  //--- WRC0TxEnable

  Type_WRC0TxEnable get_WRC0TxEnable() { return Type_WRC0TxEnable(rw.template get<uint32>(0x18u)); }
 
  void set_WRC0TxEnable(Type_WRC0TxEnable value) { rw.set(0x18u,value); }
 
  void set_WRC0TxEnable_null() { rw.set(0x18u,Type_WRC0TxEnable(0)); }
 
  void set_WRC0TxEnable_ones() { rw.set(0x18u,Type_WRC0TxEnable(-1)); }
 
  //--- WRC0MiscEnable

  Type_WRC0MiscEnable get_WRC0MiscEnable() { return Type_WRC0MiscEnable(rw.template get<uint32>(0x1Cu)); }
 
  void set_WRC0MiscEnable(Type_WRC0MiscEnable value) { rw.set(0x1Cu,value); }
 
  void set_WRC0MiscEnable_null() { rw.set(0x1Cu,Type_WRC0MiscEnable(0)); }
 
  void set_WRC0MiscEnable_ones() { rw.set(0x1Cu,Type_WRC0MiscEnable(-1)); }
 
  //--- WRC1RxThreshEnable

  Type_WRC0RxThreshEnable get_WRC1RxThreshEnable() { return Type_WRC0RxThreshEnable(rw.template get<uint32>(0x20u)); }
 
  void set_WRC1RxThreshEnable(Type_WRC0RxThreshEnable value) { rw.set(0x20u,value); }
 
  void set_WRC1RxThreshEnable_null() { rw.set(0x20u,Type_WRC0RxThreshEnable(0)); }
 
  void set_WRC1RxThreshEnable_ones() { rw.set(0x20u,Type_WRC0RxThreshEnable(-1)); }
 
  //--- WRC1RxEnable

  Type_WRC0RxEnable get_WRC1RxEnable() { return Type_WRC0RxEnable(rw.template get<uint32>(0x24u)); }
 
  void set_WRC1RxEnable(Type_WRC0RxEnable value) { rw.set(0x24u,value); }
 
  void set_WRC1RxEnable_null() { rw.set(0x24u,Type_WRC0RxEnable(0)); }
 
  void set_WRC1RxEnable_ones() { rw.set(0x24u,Type_WRC0RxEnable(-1)); }
 
  //--- WRC1TxEnable

  Type_WRC0TxEnable get_WRC1TxEnable() { return Type_WRC0TxEnable(rw.template get<uint32>(0x28u)); }
 
  void set_WRC1TxEnable(Type_WRC0TxEnable value) { rw.set(0x28u,value); }
 
  void set_WRC1TxEnable_null() { rw.set(0x28u,Type_WRC0TxEnable(0)); }
 
  void set_WRC1TxEnable_ones() { rw.set(0x28u,Type_WRC0TxEnable(-1)); }
 
  //--- WRC1MiscEnable

  Type_WRC0MiscEnable get_WRC1MiscEnable() { return Type_WRC0MiscEnable(rw.template get<uint32>(0x2Cu)); }
 
  void set_WRC1MiscEnable(Type_WRC0MiscEnable value) { rw.set(0x2Cu,value); }
 
  void set_WRC1MiscEnable_null() { rw.set(0x2Cu,Type_WRC0MiscEnable(0)); }
 
  void set_WRC1MiscEnable_ones() { rw.set(0x2Cu,Type_WRC0MiscEnable(-1)); }
 
  //--- WRC2RxThreshEnable

  Type_WRC0RxThreshEnable get_WRC2RxThreshEnable() { return Type_WRC0RxThreshEnable(rw.template get<uint32>(0x30u)); }
 
  void set_WRC2RxThreshEnable(Type_WRC0RxThreshEnable value) { rw.set(0x30u,value); }
 
  void set_WRC2RxThreshEnable_null() { rw.set(0x30u,Type_WRC0RxThreshEnable(0)); }
 
  void set_WRC2RxThreshEnable_ones() { rw.set(0x30u,Type_WRC0RxThreshEnable(-1)); }
 
  //--- WRC2RxEnable

  Type_WRC0RxEnable get_WRC2RxEnable() { return Type_WRC0RxEnable(rw.template get<uint32>(0x34u)); }
 
  void set_WRC2RxEnable(Type_WRC0RxEnable value) { rw.set(0x34u,value); }
 
  void set_WRC2RxEnable_null() { rw.set(0x34u,Type_WRC0RxEnable(0)); }
 
  void set_WRC2RxEnable_ones() { rw.set(0x34u,Type_WRC0RxEnable(-1)); }
 
  //--- WRC2TxEnable

  Type_WRC0TxEnable get_WRC2TxEnable() { return Type_WRC0TxEnable(rw.template get<uint32>(0x38u)); }
 
  void set_WRC2TxEnable(Type_WRC0TxEnable value) { rw.set(0x38u,value); }
 
  void set_WRC2TxEnable_null() { rw.set(0x38u,Type_WRC0TxEnable(0)); }
 
  void set_WRC2TxEnable_ones() { rw.set(0x38u,Type_WRC0TxEnable(-1)); }
 
  //--- WRC2MiscEnable

  Type_WRC0MiscEnable get_WRC2MiscEnable() { return Type_WRC0MiscEnable(rw.template get<uint32>(0x3Cu)); }
 
  void set_WRC2MiscEnable(Type_WRC0MiscEnable value) { rw.set(0x3Cu,value); }
 
  void set_WRC2MiscEnable_null() { rw.set(0x3Cu,Type_WRC0MiscEnable(0)); }
 
  void set_WRC2MiscEnable_ones() { rw.set(0x3Cu,Type_WRC0MiscEnable(-1)); }
 
  //--- WRC0RxThreshStatus

  Type_WRC0RxThreshStatus get_WRC0RxThreshStatus() { return Type_WRC0RxThreshStatus(rw.template get<uint32>(0x40u)); }
 
  void set_WRC0RxThreshStatus(Type_WRC0RxThreshStatus value) { rw.set(0x40u,value); }
 
  void set_WRC0RxThreshStatus_null() { rw.set(0x40u,Type_WRC0RxThreshStatus(0)); }
 
  void set_WRC0RxThreshStatus_ones() { rw.set(0x40u,Type_WRC0RxThreshStatus(-1)); }
 
  //--- WRC0RxStatus

  Type_WRC0RxStatus get_WRC0RxStatus() { return Type_WRC0RxStatus(rw.template get<uint32>(0x44u)); }
 
  void set_WRC0RxStatus(Type_WRC0RxStatus value) { rw.set(0x44u,value); }
 
  void set_WRC0RxStatus_null() { rw.set(0x44u,Type_WRC0RxStatus(0)); }
 
  void set_WRC0RxStatus_ones() { rw.set(0x44u,Type_WRC0RxStatus(-1)); }
 
  //--- WRC0TxStatus

  Type_WRC0TxStatus get_WRC0TxStatus() { return Type_WRC0TxStatus(rw.template get<uint32>(0x48u)); }
 
  void set_WRC0TxStatus(Type_WRC0TxStatus value) { rw.set(0x48u,value); }
 
  void set_WRC0TxStatus_null() { rw.set(0x48u,Type_WRC0TxStatus(0)); }
 
  void set_WRC0TxStatus_ones() { rw.set(0x48u,Type_WRC0TxStatus(-1)); }
 
  //--- WRC0MiscStatus

  Type_WRC0MiscStatus get_WRC0MiscStatus() { return Type_WRC0MiscStatus(rw.template get<uint32>(0x4Cu)); }
 
  void set_WRC0MiscStatus(Type_WRC0MiscStatus value) { rw.set(0x4Cu,value); }
 
  void set_WRC0MiscStatus_null() { rw.set(0x4Cu,Type_WRC0MiscStatus(0)); }
 
  void set_WRC0MiscStatus_ones() { rw.set(0x4Cu,Type_WRC0MiscStatus(-1)); }
 
  //--- WRC1RxThreshStatus

  Type_WRC0RxThreshStatus get_WRC1RxThreshStatus() { return Type_WRC0RxThreshStatus(rw.template get<uint32>(0x50u)); }
 
  void set_WRC1RxThreshStatus(Type_WRC0RxThreshStatus value) { rw.set(0x50u,value); }
 
  void set_WRC1RxThreshStatus_null() { rw.set(0x50u,Type_WRC0RxThreshStatus(0)); }
 
  void set_WRC1RxThreshStatus_ones() { rw.set(0x50u,Type_WRC0RxThreshStatus(-1)); }
 
  //--- WRC1RxStatus

  Type_WRC0RxStatus get_WRC1RxStatus() { return Type_WRC0RxStatus(rw.template get<uint32>(0x54u)); }
 
  void set_WRC1RxStatus(Type_WRC0RxStatus value) { rw.set(0x54u,value); }
 
  void set_WRC1RxStatus_null() { rw.set(0x54u,Type_WRC0RxStatus(0)); }
 
  void set_WRC1RxStatus_ones() { rw.set(0x54u,Type_WRC0RxStatus(-1)); }
 
  //--- WRC1TxStatus

  Type_WRC0TxStatus get_WRC1TxStatus() { return Type_WRC0TxStatus(rw.template get<uint32>(0x58u)); }
 
  void set_WRC1TxStatus(Type_WRC0TxStatus value) { rw.set(0x58u,value); }
 
  void set_WRC1TxStatus_null() { rw.set(0x58u,Type_WRC0TxStatus(0)); }
 
  void set_WRC1TxStatus_ones() { rw.set(0x58u,Type_WRC0TxStatus(-1)); }
 
  //--- WRC1MiscStatus

  Type_WRC0MiscStatus get_WRC1MiscStatus() { return Type_WRC0MiscStatus(rw.template get<uint32>(0x5Cu)); }
 
  void set_WRC1MiscStatus(Type_WRC0MiscStatus value) { rw.set(0x5Cu,value); }
 
  void set_WRC1MiscStatus_null() { rw.set(0x5Cu,Type_WRC0MiscStatus(0)); }
 
  void set_WRC1MiscStatus_ones() { rw.set(0x5Cu,Type_WRC0MiscStatus(-1)); }
 
  //--- WRC2RxThreshStatus

  Type_WRC0RxThreshStatus get_WRC2RxThreshStatus() { return Type_WRC0RxThreshStatus(rw.template get<uint32>(0x60u)); }
 
  void set_WRC2RxThreshStatus(Type_WRC0RxThreshStatus value) { rw.set(0x60u,value); }
 
  void set_WRC2RxThreshStatus_null() { rw.set(0x60u,Type_WRC0RxThreshStatus(0)); }
 
  void set_WRC2RxThreshStatus_ones() { rw.set(0x60u,Type_WRC0RxThreshStatus(-1)); }
 
  //--- WRC2RxStatus

  Type_WRC0RxStatus get_WRC2RxStatus() { return Type_WRC0RxStatus(rw.template get<uint32>(0x64u)); }
 
  void set_WRC2RxStatus(Type_WRC0RxStatus value) { rw.set(0x64u,value); }
 
  void set_WRC2RxStatus_null() { rw.set(0x64u,Type_WRC0RxStatus(0)); }
 
  void set_WRC2RxStatus_ones() { rw.set(0x64u,Type_WRC0RxStatus(-1)); }
 
  //--- WRC2TxStatus

  Type_WRC0TxStatus get_WRC2TxStatus() { return Type_WRC0TxStatus(rw.template get<uint32>(0x68u)); }
 
  void set_WRC2TxStatus(Type_WRC0TxStatus value) { rw.set(0x68u,value); }
 
  void set_WRC2TxStatus_null() { rw.set(0x68u,Type_WRC0TxStatus(0)); }
 
  void set_WRC2TxStatus_ones() { rw.set(0x68u,Type_WRC0TxStatus(-1)); }
 
  //--- WRC2MiscStatus

  Type_WRC0MiscStatus get_WRC2MiscStatus() { return Type_WRC0MiscStatus(rw.template get<uint32>(0x6Cu)); }
 
  void set_WRC2MiscStatus(Type_WRC0MiscStatus value) { rw.set(0x6Cu,value); }
 
  void set_WRC2MiscStatus_null() { rw.set(0x6Cu,Type_WRC0MiscStatus(0)); }
 
  void set_WRC2MiscStatus_ones() { rw.set(0x6Cu,Type_WRC0MiscStatus(-1)); }
 
  //--- WRC0RxIntLim

  Type_WRC0RxIntLim get_WRC0RxIntLim() { return Type_WRC0RxIntLim(rw.template get<uint32>(0x70u)); }
 
  void set_WRC0RxIntLim(Type_WRC0RxIntLim value) { rw.set(0x70u,value.value); }
 
  Setter<Type_WRC0RxIntLim> to_WRC0RxIntLim() { return Setter<Type_WRC0RxIntLim>(rw,0x70u); }
 
  static Type_WRC0RxIntLim null_WRC0RxIntLim() { return Type_WRC0RxIntLim(0); }
 
  static Type_WRC0RxIntLim ones_WRC0RxIntLim() { return Type_WRC0RxIntLim(Type_WRC0RxIntLim::Type(-1)); }
 
  //--- WRC0TxIntLim

  Type_WRC0TxIntLim get_WRC0TxIntLim() { return Type_WRC0TxIntLim(rw.template get<uint32>(0x74u)); }
 
  void set_WRC0TxIntLim(Type_WRC0TxIntLim value) { rw.set(0x74u,value.value); }
 
  Setter<Type_WRC0TxIntLim> to_WRC0TxIntLim() { return Setter<Type_WRC0TxIntLim>(rw,0x74u); }
 
  static Type_WRC0TxIntLim null_WRC0TxIntLim() { return Type_WRC0TxIntLim(0); }
 
  static Type_WRC0TxIntLim ones_WRC0TxIntLim() { return Type_WRC0TxIntLim(Type_WRC0TxIntLim::Type(-1)); }
 
  //--- WRC1RxIntLim

  Type_WRC0RxIntLim get_WRC1RxIntLim() { return Type_WRC0RxIntLim(rw.template get<uint32>(0x78u)); }
 
  void set_WRC1RxIntLim(Type_WRC0RxIntLim value) { rw.set(0x78u,value.value); }
 
  Setter<Type_WRC0RxIntLim> to_WRC1RxIntLim() { return Setter<Type_WRC0RxIntLim>(rw,0x78u); }
 
  //--- WRC1TxIntLim

  Type_WRC0TxIntLim get_WRC1TxIntLim() { return Type_WRC0TxIntLim(rw.template get<uint32>(0x7Cu)); }
 
  void set_WRC1TxIntLim(Type_WRC0TxIntLim value) { rw.set(0x7Cu,value.value); }
 
  Setter<Type_WRC0TxIntLim> to_WRC1TxIntLim() { return Setter<Type_WRC0TxIntLim>(rw,0x7Cu); }
 
  //--- WRC2RxIntLim

  Type_WRC0RxIntLim get_WRC2RxIntLim() { return Type_WRC0RxIntLim(rw.template get<uint32>(0x80u)); }
 
  void set_WRC2RxIntLim(Type_WRC0RxIntLim value) { rw.set(0x80u,value.value); }
 
  Setter<Type_WRC0RxIntLim> to_WRC2RxIntLim() { return Setter<Type_WRC0RxIntLim>(rw,0x80u); }
 
  //--- WRC2TxIntLim

  Type_WRC0TxIntLim get_WRC2TxIntLim() { return Type_WRC0TxIntLim(rw.template get<uint32>(0x84u)); }
 
  void set_WRC2TxIntLim(Type_WRC0TxIntLim value) { rw.set(0x84u,value.value); }
 
  Setter<Type_WRC0TxIntLim> to_WRC2TxIntLim() { return Setter<Type_WRC0TxIntLim>(rw,0x84u); }
 
  //--- WRRGMIIStatus

  Type_WRRGMIIStatus get_WRRGMIIStatus() { return Type_WRRGMIIStatus(rw.template get<uint32>(0x88u)); }
 
  static Type_WRRGMIIStatus null_WRRGMIIStatus() { return Type_WRRGMIIStatus(0); }
 
  static Type_WRRGMIIStatus ones_WRRGMIIStatus() { return Type_WRRGMIIStatus(Type_WRRGMIIStatus::Type(-1)); }
 
 };
 
/* struct MDIOBar<RW> */

template <class RW>
struct MDIOBar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit MDIOBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- MDIOControl

  Type_MDIOControl get_MDIOControl() { return Type_MDIOControl(rw.template get<uint32>(0x4u)); }
 
  void set_MDIOControl(Type_MDIOControl value) { rw.set(0x4u,value.value); }
 
  Setter<Type_MDIOControl> to_MDIOControl() { return Setter<Type_MDIOControl>(rw,0x4u); }
 
  static Type_MDIOControl null_MDIOControl() { return Type_MDIOControl(0); }
 
  static Type_MDIOControl ones_MDIOControl() { return Type_MDIOControl(Type_MDIOControl::Type(-1)); }
 
  //--- MDIOAlive

  Type_MDIOAlive get_MDIOAlive() { return Type_MDIOAlive(rw.template get<uint32>(0x8u)); }
 
  void set_MDIOAlive(Type_MDIOAlive value) { rw.set(0x8u,value); }
 
  void set_MDIOAlive_null() { rw.set(0x8u,Type_MDIOAlive(0)); }
 
  void set_MDIOAlive_ones() { rw.set(0x8u,Type_MDIOAlive(-1)); }
 
  //--- MDIOLink

  Type_MDIOLink get_MDIOLink() { return Type_MDIOLink(rw.template get<uint32>(0xCu)); }
 
  void set_MDIOLink(Type_MDIOLink value) { rw.set(0xCu,value); }
 
  void set_MDIOLink_null() { rw.set(0xCu,Type_MDIOLink(0)); }
 
  void set_MDIOLink_ones() { rw.set(0xCu,Type_MDIOLink(-1)); }
 
  //--- MDIOLinkIntStatusRaw

  Type_MDIOLinkIntStatus get_MDIOLinkIntStatusRaw() { return Type_MDIOLinkIntStatus(rw.template get<uint32>(0x10u)); }
 
  void set_MDIOLinkIntStatusRaw(Type_MDIOLinkIntStatus value) { rw.set(0x10u,value); }
 
  void set_MDIOLinkIntStatusRaw_null() { rw.set(0x10u,Type_MDIOLinkIntStatus(0)); }
 
  void set_MDIOLinkIntStatusRaw_ones() { rw.set(0x10u,Type_MDIOLinkIntStatus(-1)); }
 
  //--- MDIOLinkIntStatus

  Type_MDIOLinkIntStatus get_MDIOLinkIntStatus() { return Type_MDIOLinkIntStatus(rw.template get<uint32>(0x14u)); }
 
  void set_MDIOLinkIntStatus(Type_MDIOLinkIntStatus value) { rw.set(0x14u,value); }
 
  void set_MDIOLinkIntStatus_null() { rw.set(0x14u,Type_MDIOLinkIntStatus(0)); }
 
  void set_MDIOLinkIntStatus_ones() { rw.set(0x14u,Type_MDIOLinkIntStatus(-1)); }
 
  //--- MDIOUserIntStatusRaw

  Type_MDIOUserIntStatus get_MDIOUserIntStatusRaw() { return Type_MDIOUserIntStatus(rw.template get<uint32>(0x18u)); }
 
  void set_MDIOUserIntStatusRaw(Type_MDIOUserIntStatus value) { rw.set(0x18u,value); }
 
  void set_MDIOUserIntStatusRaw_null() { rw.set(0x18u,Type_MDIOUserIntStatus(0)); }
 
  void set_MDIOUserIntStatusRaw_ones() { rw.set(0x18u,Type_MDIOUserIntStatus(-1)); }
 
  //--- MDIOUserIntStatus

  Type_MDIOUserIntStatus get_MDIOUserIntStatus() { return Type_MDIOUserIntStatus(rw.template get<uint32>(0x1Cu)); }
 
  void set_MDIOUserIntStatus(Type_MDIOUserIntStatus value) { rw.set(0x1Cu,value); }
 
  void set_MDIOUserIntStatus_null() { rw.set(0x1Cu,Type_MDIOUserIntStatus(0)); }
 
  void set_MDIOUserIntStatus_ones() { rw.set(0x1Cu,Type_MDIOUserIntStatus(-1)); }
 
  //--- MDIOUserIntEnableSet

  Type_MDIOUserIntStatus get_MDIOUserIntEnableSet() { return Type_MDIOUserIntStatus(rw.template get<uint32>(0x20u)); }
 
  void set_MDIOUserIntEnableSet(Type_MDIOUserIntStatus value) { rw.set(0x20u,value); }
 
  void set_MDIOUserIntEnableSet_null() { rw.set(0x20u,Type_MDIOUserIntStatus(0)); }
 
  void set_MDIOUserIntEnableSet_ones() { rw.set(0x20u,Type_MDIOUserIntStatus(-1)); }
 
  //--- MDIOUserIntEnableClear

  Type_MDIOUserIntStatus get_MDIOUserIntEnableClear() { return Type_MDIOUserIntStatus(rw.template get<uint32>(0x24u)); }
 
  void set_MDIOUserIntEnableClear(Type_MDIOUserIntStatus value) { rw.set(0x24u,value); }
 
  void set_MDIOUserIntEnableClear_null() { rw.set(0x24u,Type_MDIOUserIntStatus(0)); }
 
  void set_MDIOUserIntEnableClear_ones() { rw.set(0x24u,Type_MDIOUserIntStatus(-1)); }
 
  //--- MDIOUserAccess

  static Type_MDIOUserAccess null_MDIOUserAccess() { return Type_MDIOUserAccess(0); }
 
  static Type_MDIOUserAccess ones_MDIOUserAccess() { return Type_MDIOUserAccess(Type_MDIOUserAccess::Type(-1)); }
 
  //--- MDIOUserPhySel

  static Type_MDIOUserPhySel null_MDIOUserPhySel() { return Type_MDIOUserPhySel(0); }
 
  static Type_MDIOUserPhySel ones_MDIOUserPhySel() { return Type_MDIOUserPhySel(Type_MDIOUserPhySel::Type(-1)); }
 
  //--- MDIOUserAccess0

  Type_MDIOUserAccess get_MDIOUserAccess0() { return Type_MDIOUserAccess(rw.template get<uint32>(0x80u)); }
 
  void set_MDIOUserAccess0(Type_MDIOUserAccess value) { rw.set(0x80u,value.value); }
 
  Setter<Type_MDIOUserAccess> to_MDIOUserAccess0() { return Setter<Type_MDIOUserAccess>(rw,0x80u); }
 
  //--- MDIOUserPhySel0

  Type_MDIOUserPhySel get_MDIOUserPhySel0() { return Type_MDIOUserPhySel(rw.template get<uint32>(0x84u)); }
 
  void set_MDIOUserPhySel0(Type_MDIOUserPhySel value) { rw.set(0x84u,value.value); }
 
  Setter<Type_MDIOUserPhySel> to_MDIOUserPhySel0() { return Setter<Type_MDIOUserPhySel>(rw,0x84u); }
 
  //--- MDIOUserAccess1

  Type_MDIOUserAccess get_MDIOUserAccess1() { return Type_MDIOUserAccess(rw.template get<uint32>(0x88u)); }
 
  void set_MDIOUserAccess1(Type_MDIOUserAccess value) { rw.set(0x88u,value.value); }
 
  Setter<Type_MDIOUserAccess> to_MDIOUserAccess1() { return Setter<Type_MDIOUserAccess>(rw,0x88u); }
 
  //--- MDIOUserPhySel1

  Type_MDIOUserPhySel get_MDIOUserPhySel1() { return Type_MDIOUserPhySel(rw.template get<uint32>(0x8Cu)); }
 
  void set_MDIOUserPhySel1(Type_MDIOUserPhySel value) { rw.set(0x8Cu,value.value); }
 
  Setter<Type_MDIOUserPhySel> to_MDIOUserPhySel1() { return Setter<Type_MDIOUserPhySel>(rw,0x8Cu); }
 
 };
 
