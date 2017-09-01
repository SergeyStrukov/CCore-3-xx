/* NXP.HDMI.gen.h */

/* struct Type_CECEnable */

enum Bits_CECEnable : uint8
 {
  CECEnable_EnCEC     = 0x01u,
  CECEnable_EnHDMI    = 0x02u,
  CECEnable_EnRxSense = 0x04u,
  CECEnable_DisCCLK   = 0x20u,
  CECEnable_DisFRO    = 0x40u
 };
 
inline Bits_CECEnable operator | (Bits_CECEnable a,Bits_CECEnable b)
 { return Bits_CECEnable(uint8(a)|uint8(b)); }
 
struct Type_CECEnable
 {
  using Type = uint8 ;

  Type value;


  explicit Type_CECEnable(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CECEnable & setTo(Bar &bar) { bar.set_CECEnable(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_CECEnable & setTo(Bar &bar,AddressType ind) { bar.set_CECEnable(ind,*this); return *this; }
 

  template <class T>
  Type_CECEnable & set(T to) { to(*this); return *this; }
 

  Type_CECEnable & setbit(Bits_CECEnable bits) { value|=Type(bits); return *this; }
 
  Type_CECEnable & setbitIf(bool cond,Bits_CECEnable bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CECEnable & clearbit(Bits_CECEnable bits) { value&=~Type(bits); return *this; }
 
  Type_CECEnable & clearbitIf(bool cond,Bits_CECEnable bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CECEnable bits) const { return value&bits; }
 
  bool testbit(Bits_CECEnable bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CECEnable_EnCEC )
      {
       if( first )
         {
          Putobj(out,"EnCEC");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EnCEC");
         }
      }

    if( value&CECEnable_EnHDMI )
      {
       if( first )
         {
          Putobj(out,"EnHDMI");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EnHDMI");
         }
      }

    if( value&CECEnable_EnRxSense )
      {
       if( first )
         {
          Putobj(out,"EnRxSense");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EnRxSense");
         }
      }

    if( value&CECEnable_DisCCLK )
      {
       if( first )
         {
          Putobj(out,"DisCCLK");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DisCCLK");
         }
      }

    if( value&CECEnable_DisFRO )
      {
       if( first )
         {
          Putobj(out,"DisFRO");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DisFRO");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_CECStatus */

enum Bits_CECStatus : uint8
 {
  CECStatus_RxSense = 0x01u,
  CECStatus_Plug    = 0x02u
 };
 
inline Bits_CECStatus operator | (Bits_CECStatus a,Bits_CECStatus b)
 { return Bits_CECStatus(uint8(a)|uint8(b)); }
 
struct Type_CECStatus
 {
  using Type = uint8 ;

  Type value;


  explicit Type_CECStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CECStatus & setTo(Bar &bar) { bar.set_CECStatus(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_CECStatus & setTo(Bar &bar,AddressType ind) { bar.set_CECStatus(ind,*this); return *this; }
 

  template <class T>
  Type_CECStatus & set(T to) { to(*this); return *this; }
 

  Type_CECStatus & setbit(Bits_CECStatus bits) { value|=Type(bits); return *this; }
 
  Type_CECStatus & setbitIf(bool cond,Bits_CECStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CECStatus & clearbit(Bits_CECStatus bits) { value&=~Type(bits); return *this; }
 
  Type_CECStatus & clearbitIf(bool cond,Bits_CECStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CECStatus bits) const { return value&bits; }
 
  bool testbit(Bits_CECStatus bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CECStatus_RxSense )
      {
       if( first )
         {
          Putobj(out,"RxSense");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxSense");
         }
      }

    if( value&CECStatus_Plug )
      {
       if( first )
         {
          Putobj(out,"Plug");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Plug");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_CECIntStatus */

enum Bits_CECIntStatus : uint8
 {
  CECIntStatus_RxSense = 0x01u,
  CECIntStatus_Plug    = 0x02u
 };
 
inline Bits_CECIntStatus operator | (Bits_CECIntStatus a,Bits_CECIntStatus b)
 { return Bits_CECIntStatus(uint8(a)|uint8(b)); }
 
struct Type_CECIntStatus
 {
  using Type = uint8 ;

  Type value;


  explicit Type_CECIntStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CECIntStatus & setTo(Bar &bar) { bar.set_CECIntStatus(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_CECIntStatus & setTo(Bar &bar,AddressType ind) { bar.set_CECIntStatus(ind,*this); return *this; }
 

  template <class T>
  Type_CECIntStatus & set(T to) { to(*this); return *this; }
 

  Type_CECIntStatus & setbit(Bits_CECIntStatus bits) { value|=Type(bits); return *this; }
 
  Type_CECIntStatus & setbitIf(bool cond,Bits_CECIntStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CECIntStatus & clearbit(Bits_CECIntStatus bits) { value&=~Type(bits); return *this; }
 
  Type_CECIntStatus & clearbitIf(bool cond,Bits_CECIntStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CECIntStatus bits) const { return value&bits; }
 
  bool testbit(Bits_CECIntStatus bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CECIntStatus_RxSense )
      {
       if( first )
         {
          Putobj(out,"RxSense");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxSense");
         }
      }

    if( value&CECIntStatus_Plug )
      {
       if( first )
         {
          Putobj(out,"Plug");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Plug");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_CECIntEnable */

enum Bits_CECIntEnable : uint8
 {
  CECIntEnable_RxSense = 0x01u,
  CECIntEnable_Plug    = 0x02u
 };
 
inline Bits_CECIntEnable operator | (Bits_CECIntEnable a,Bits_CECIntEnable b)
 { return Bits_CECIntEnable(uint8(a)|uint8(b)); }
 
struct Type_CECIntEnable
 {
  using Type = uint8 ;

  Type value;


  explicit Type_CECIntEnable(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CECIntEnable & setTo(Bar &bar) { bar.set_CECIntEnable(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_CECIntEnable & setTo(Bar &bar,AddressType ind) { bar.set_CECIntEnable(ind,*this); return *this; }
 

  template <class T>
  Type_CECIntEnable & set(T to) { to(*this); return *this; }
 

  Type_CECIntEnable & setbit(Bits_CECIntEnable bits) { value|=Type(bits); return *this; }
 
  Type_CECIntEnable & setbitIf(bool cond,Bits_CECIntEnable bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CECIntEnable & clearbit(Bits_CECIntEnable bits) { value&=~Type(bits); return *this; }
 
  Type_CECIntEnable & clearbitIf(bool cond,Bits_CECIntEnable bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CECIntEnable bits) const { return value&bits; }
 
  bool testbit(Bits_CECIntEnable bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CECIntEnable_RxSense )
      {
       if( first )
         {
          Putobj(out,"RxSense");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxSense");
         }
      }

    if( value&CECIntEnable_Plug )
      {
       if( first )
         {
          Putobj(out,"Plug");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Plug");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_CECIntSource */

enum Bits_CECIntSource : uint8
 {
  CECIntSource_CEC  = 0x01u,
  CECIntSource_HDMI = 0x02u
 };
 
inline Bits_CECIntSource operator | (Bits_CECIntSource a,Bits_CECIntSource b)
 { return Bits_CECIntSource(uint8(a)|uint8(b)); }
 
struct Type_CECIntSource
 {
  using Type = uint8 ;

  Type value;


  explicit Type_CECIntSource(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CECIntSource & setTo(Bar &bar) { bar.set_CECIntSource(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_CECIntSource & setTo(Bar &bar,AddressType ind) { bar.set_CECIntSource(ind,*this); return *this; }
 

  template <class T>
  Type_CECIntSource & set(T to) { to(*this); return *this; }
 

  Type_CECIntSource & setbit(Bits_CECIntSource bits) { value|=Type(bits); return *this; }
 
  Type_CECIntSource & setbitIf(bool cond,Bits_CECIntSource bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CECIntSource & clearbit(Bits_CECIntSource bits) { value&=~Type(bits); return *this; }
 
  Type_CECIntSource & clearbitIf(bool cond,Bits_CECIntSource bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CECIntSource bits) const { return value&bits; }
 
  bool testbit(Bits_CECIntSource bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CECIntSource_CEC )
      {
       if( first )
         {
          Putobj(out,"CEC");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CEC");
         }
      }

    if( value&CECIntSource_HDMI )
      {
       if( first )
         {
          Putobj(out,"HDMI");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"HDMI");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_CEC_FRO_IMCLK */

enum Bits_CEC_FRO_IMCLK : uint8
 {
  CEC_FRO_IMCLK_FRODiv   = 0x01u,
  CEC_FRO_IMCLK_IMCLK    = 0x02u,
  CEC_FRO_IMCLK_EnOTP    = 0x40u,
  CEC_FRO_IMCLK_DisGhost = 0x80u
 };
 
inline Bits_CEC_FRO_IMCLK operator | (Bits_CEC_FRO_IMCLK a,Bits_CEC_FRO_IMCLK b)
 { return Bits_CEC_FRO_IMCLK(uint8(a)|uint8(b)); }
 
struct Type_CEC_FRO_IMCLK
 {
  using Type = uint8 ;

  Type value;


  explicit Type_CEC_FRO_IMCLK(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CEC_FRO_IMCLK & setTo(Bar &bar) { bar.set_CEC_FRO_IMCLK(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_CEC_FRO_IMCLK & setTo(Bar &bar,AddressType ind) { bar.set_CEC_FRO_IMCLK(ind,*this); return *this; }
 

  template <class T>
  Type_CEC_FRO_IMCLK & set(T to) { to(*this); return *this; }
 

  Type_CEC_FRO_IMCLK & setbit(Bits_CEC_FRO_IMCLK bits) { value|=Type(bits); return *this; }
 
  Type_CEC_FRO_IMCLK & setbitIf(bool cond,Bits_CEC_FRO_IMCLK bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CEC_FRO_IMCLK & clearbit(Bits_CEC_FRO_IMCLK bits) { value&=~Type(bits); return *this; }
 
  Type_CEC_FRO_IMCLK & clearbitIf(bool cond,Bits_CEC_FRO_IMCLK bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CEC_FRO_IMCLK bits) const { return value&bits; }
 
  bool testbit(Bits_CEC_FRO_IMCLK bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CEC_FRO_IMCLK_FRODiv )
      {
       if( first )
         {
          Putobj(out,"FRODiv");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FRODiv");
         }
      }

    if( value&CEC_FRO_IMCLK_IMCLK )
      {
       if( first )
         {
          Putobj(out,"IMCLK");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"IMCLK");
         }
      }

    if( value&CEC_FRO_IMCLK_EnOTP )
      {
       if( first )
         {
          Putobj(out,"EnOTP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EnOTP");
         }
      }

    if( value&CEC_FRO_IMCLK_DisGhost )
      {
       if( first )
         {
          Putobj(out,"DisGhost");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DisGhost");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_VersionLSB */

enum Bits_VersionLSB : uint8
 {
  VersionLSB_NotS = 0x10u,
  VersionLSB_NotH = 0x20u
 };
 
inline Bits_VersionLSB operator | (Bits_VersionLSB a,Bits_VersionLSB b)
 { return Bits_VersionLSB(uint8(a)|uint8(b)); }
 
struct Type_VersionLSB
 {
  using Type = uint8 ;

  Type value;


  explicit Type_VersionLSB(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_VersionLSB & setTo(Bar &bar) { bar.set_VersionLSB(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_VersionLSB & setTo(Bar &bar,AddressType ind) { bar.set_VersionLSB(ind,*this); return *this; }
 

  template <class T>
  Type_VersionLSB & set(T to) { to(*this); return *this; }
 

  Type_VersionLSB & setbit(Bits_VersionLSB bits) { value|=Type(bits); return *this; }
 
  Type_VersionLSB & setbitIf(bool cond,Bits_VersionLSB bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_VersionLSB & clearbit(Bits_VersionLSB bits) { value&=~Type(bits); return *this; }
 
  Type_VersionLSB & clearbitIf(bool cond,Bits_VersionLSB bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_VersionLSB bits) const { return value&bits; }
 
  bool testbit(Bits_VersionLSB bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&VersionLSB_NotS )
      {
       if( first )
         {
          Putobj(out,"NotS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NotS");
         }
      }

    if( value&VersionLSB_NotH )
      {
       if( first )
         {
          Putobj(out,"NotH");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NotH");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_VersionMSB */

using Type_VersionMSB = uint8 ;

/* struct Type_MainControl0 */

enum Bits_MainControl0 : uint8
 {
  MainControl0_SoftReset = 0x01u
 };
 
inline Bits_MainControl0 operator | (Bits_MainControl0 a,Bits_MainControl0 b)
 { return Bits_MainControl0(uint8(a)|uint8(b)); }
 
struct Type_MainControl0
 {
  using Type = uint8 ;

  Type value;


  explicit Type_MainControl0(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MainControl0 & setTo(Bar &bar) { bar.set_MainControl0(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_MainControl0 & setTo(Bar &bar,AddressType ind) { bar.set_MainControl0(ind,*this); return *this; }
 

  template <class T>
  Type_MainControl0 & set(T to) { to(*this); return *this; }
 

  Type_MainControl0 & setbit(Bits_MainControl0 bits) { value|=Type(bits); return *this; }
 
  Type_MainControl0 & setbitIf(bool cond,Bits_MainControl0 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MainControl0 & clearbit(Bits_MainControl0 bits) { value&=~Type(bits); return *this; }
 
  Type_MainControl0 & clearbitIf(bool cond,Bits_MainControl0 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MainControl0 bits) const { return value&bits; }
 
  bool testbit(Bits_MainControl0 bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MainControl0_SoftReset )
      {
       if( first )
         {
          Putobj(out,"SoftReset");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SoftReset");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SoftReset */

enum Bits_SoftReset : uint8
 {
  SoftReset_Audio = 0x01u,
  SoftReset_I2C   = 0x02u
 };
 
inline Bits_SoftReset operator | (Bits_SoftReset a,Bits_SoftReset b)
 { return Bits_SoftReset(uint8(a)|uint8(b)); }
 
struct Type_SoftReset
 {
  using Type = uint8 ;

  Type value;


  explicit Type_SoftReset(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SoftReset & setTo(Bar &bar) { bar.set_SoftReset(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SoftReset & setTo(Bar &bar,AddressType ind) { bar.set_SoftReset(ind,*this); return *this; }
 

  template <class T>
  Type_SoftReset & set(T to) { to(*this); return *this; }
 

  Type_SoftReset & setbit(Bits_SoftReset bits) { value|=Type(bits); return *this; }
 
  Type_SoftReset & setbitIf(bool cond,Bits_SoftReset bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SoftReset & clearbit(Bits_SoftReset bits) { value&=~Type(bits); return *this; }
 
  Type_SoftReset & clearbitIf(bool cond,Bits_SoftReset bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SoftReset bits) const { return value&bits; }
 
  bool testbit(Bits_SoftReset bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SoftReset_Audio )
      {
       if( first )
         {
          Putobj(out,"Audio");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Audio");
         }
      }

    if( value&SoftReset_I2C )
      {
       if( first )
         {
          Putobj(out,"I2C");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"I2C");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DDCDisable */

enum Bits_DDCDisable : uint8
 {
  DDCDisable_Dis = 0x01u
 };
 
inline Bits_DDCDisable operator | (Bits_DDCDisable a,Bits_DDCDisable b)
 { return Bits_DDCDisable(uint8(a)|uint8(b)); }
 
struct Type_DDCDisable
 {
  using Type = uint8 ;

  Type value;


  explicit Type_DDCDisable(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DDCDisable & setTo(Bar &bar) { bar.set_DDCDisable(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DDCDisable & setTo(Bar &bar,AddressType ind) { bar.set_DDCDisable(ind,*this); return *this; }
 

  template <class T>
  Type_DDCDisable & set(T to) { to(*this); return *this; }
 

  Type_DDCDisable & setbit(Bits_DDCDisable bits) { value|=Type(bits); return *this; }
 
  Type_DDCDisable & setbitIf(bool cond,Bits_DDCDisable bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_DDCDisable & clearbit(Bits_DDCDisable bits) { value&=~Type(bits); return *this; }
 
  Type_DDCDisable & clearbitIf(bool cond,Bits_DDCDisable bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_DDCDisable bits) const { return value&bits; }
 
  bool testbit(Bits_DDCDisable bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&DDCDisable_Dis )
      {
       if( first )
         {
          Putobj(out,"Dis");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Dis");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_IntFlags0 */

using Type_IntFlags0 = uint8 ;

/* type Type_IntFlags1 */

using Type_IntFlags1 = uint8 ;

/* struct Type_IntFlags2 */

enum Bits_IntFlags2 : uint8
 {
  IntFlags2_RxSense = 0x01u,
  IntFlags2_EDID    = 0x02u
 };
 
inline Bits_IntFlags2 operator | (Bits_IntFlags2 a,Bits_IntFlags2 b)
 { return Bits_IntFlags2(uint8(a)|uint8(b)); }
 
struct Type_IntFlags2
 {
  using Type = uint8 ;

  Type value;


  explicit Type_IntFlags2(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_IntFlags2 & setTo(Bar &bar) { bar.set_IntFlags2(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_IntFlags2 & setTo(Bar &bar,AddressType ind) { bar.set_IntFlags2(ind,*this); return *this; }
 

  template <class T>
  Type_IntFlags2 & set(T to) { to(*this); return *this; }
 

  Type_IntFlags2 & setbit(Bits_IntFlags2 bits) { value|=Type(bits); return *this; }
 
  Type_IntFlags2 & setbitIf(bool cond,Bits_IntFlags2 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_IntFlags2 & clearbit(Bits_IntFlags2 bits) { value&=~Type(bits); return *this; }
 
  Type_IntFlags2 & clearbitIf(bool cond,Bits_IntFlags2 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_IntFlags2 bits) const { return value&bits; }
 
  bool testbit(Bits_IntFlags2 bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&IntFlags2_RxSense )
      {
       if( first )
         {
          Putobj(out,"RxSense");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxSense");
         }
      }

    if( value&IntFlags2_EDID )
      {
       if( first )
         {
          Putobj(out,"EDID");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EDID");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_VP0Enable */

using Type_VP0Enable = uint8 ;

/* type Type_VP1Enable */

using Type_VP1Enable = uint8 ;

/* type Type_VP2Enable */

using Type_VP2Enable = uint8 ;

/* struct Type_VP0Control */

enum Bits_VP0Control : uint8
 {
  VP0Control_MirrB = 0x08u,
  VP0Control_MirrA = 0x80u
 };
 
inline Bits_VP0Control operator | (Bits_VP0Control a,Bits_VP0Control b)
 { return Bits_VP0Control(uint8(a)|uint8(b)); }
 
struct Type_VP0Control
 {
  using Type = uint8 ;

  Type value;


  explicit Type_VP0Control(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_VP0Control & setTo(Bar &bar) { bar.set_VP0Control(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_VP0Control & setTo(Bar &bar,AddressType ind) { bar.set_VP0Control(ind,*this); return *this; }
 

  template <class T>
  Type_VP0Control & set(T to) { to(*this); return *this; }
 

  Type_VP0Control & setbit(Bits_VP0Control bits) { value|=Type(bits); return *this; }
 
  Type_VP0Control & setbitIf(bool cond,Bits_VP0Control bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_VP0Control & clearbit(Bits_VP0Control bits) { value&=~Type(bits); return *this; }
 
  Type_VP0Control & clearbitIf(bool cond,Bits_VP0Control bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_VP0Control bits) const { return value&bits; }
 
  bool testbit(Bits_VP0Control bits) const { return (value&bits)==Type(bits); }
 

  Type get_SwapB() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_VP0Control & set_SwapB(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  Type get_SwapA() const
   {
    return (value>>4)&0x7u;
   }
 
  Type_VP0Control & set_SwapA(Type field)
   {
    value=((field&0x7u)<<4)|(value&0xFFFFFF8Fu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&VP0Control_MirrB )
      {
       if( first )
         {
          Putobj(out,"MirrB");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MirrB");
         }
      }

    if( value&VP0Control_MirrA )
      {
       if( first )
         {
          Putobj(out,"MirrA");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MirrA");
         }
      }

    if( first )
      {
       Printf(out,"SwapB(#;)",get_SwapB());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SwapB(#;)",get_SwapB());
      }

    if( first )
      {
       Printf(out,"SwapA(#;)",get_SwapA());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SwapA(#;)",get_SwapA());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_VP1Control */

enum Bits_VP1Control : uint8
 {
  VP1Control_MirrD = 0x08u,
  VP1Control_MirrC = 0x80u
 };
 
inline Bits_VP1Control operator | (Bits_VP1Control a,Bits_VP1Control b)
 { return Bits_VP1Control(uint8(a)|uint8(b)); }
 
struct Type_VP1Control
 {
  using Type = uint8 ;

  Type value;


  explicit Type_VP1Control(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_VP1Control & setTo(Bar &bar) { bar.set_VP1Control(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_VP1Control & setTo(Bar &bar,AddressType ind) { bar.set_VP1Control(ind,*this); return *this; }
 

  template <class T>
  Type_VP1Control & set(T to) { to(*this); return *this; }
 

  Type_VP1Control & setbit(Bits_VP1Control bits) { value|=Type(bits); return *this; }
 
  Type_VP1Control & setbitIf(bool cond,Bits_VP1Control bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_VP1Control & clearbit(Bits_VP1Control bits) { value&=~Type(bits); return *this; }
 
  Type_VP1Control & clearbitIf(bool cond,Bits_VP1Control bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_VP1Control bits) const { return value&bits; }
 
  bool testbit(Bits_VP1Control bits) const { return (value&bits)==Type(bits); }
 

  Type get_SwapD() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_VP1Control & set_SwapD(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  Type get_SwapC() const
   {
    return (value>>4)&0x7u;
   }
 
  Type_VP1Control & set_SwapC(Type field)
   {
    value=((field&0x7u)<<4)|(value&0xFFFFFF8Fu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&VP1Control_MirrD )
      {
       if( first )
         {
          Putobj(out,"MirrD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MirrD");
         }
      }

    if( value&VP1Control_MirrC )
      {
       if( first )
         {
          Putobj(out,"MirrC");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MirrC");
         }
      }

    if( first )
      {
       Printf(out,"SwapD(#;)",get_SwapD());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SwapD(#;)",get_SwapD());
      }

    if( first )
      {
       Printf(out,"SwapC(#;)",get_SwapC());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SwapC(#;)",get_SwapC());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_VP2Control */

enum Bits_VP2Control : uint8
 {
  VP2Control_MirrF = 0x08u,
  VP2Control_MirrE = 0x80u
 };
 
inline Bits_VP2Control operator | (Bits_VP2Control a,Bits_VP2Control b)
 { return Bits_VP2Control(uint8(a)|uint8(b)); }
 
struct Type_VP2Control
 {
  using Type = uint8 ;

  Type value;


  explicit Type_VP2Control(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_VP2Control & setTo(Bar &bar) { bar.set_VP2Control(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_VP2Control & setTo(Bar &bar,AddressType ind) { bar.set_VP2Control(ind,*this); return *this; }
 

  template <class T>
  Type_VP2Control & set(T to) { to(*this); return *this; }
 

  Type_VP2Control & setbit(Bits_VP2Control bits) { value|=Type(bits); return *this; }
 
  Type_VP2Control & setbitIf(bool cond,Bits_VP2Control bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_VP2Control & clearbit(Bits_VP2Control bits) { value&=~Type(bits); return *this; }
 
  Type_VP2Control & clearbitIf(bool cond,Bits_VP2Control bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_VP2Control bits) const { return value&bits; }
 
  bool testbit(Bits_VP2Control bits) const { return (value&bits)==Type(bits); }
 

  Type get_SwapF() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_VP2Control & set_SwapF(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  Type get_SwapE() const
   {
    return (value>>4)&0x7u;
   }
 
  Type_VP2Control & set_SwapE(Type field)
   {
    value=((field&0x7u)<<4)|(value&0xFFFFFF8Fu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&VP2Control_MirrF )
      {
       if( first )
         {
          Putobj(out,"MirrF");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MirrF");
         }
      }

    if( value&VP2Control_MirrE )
      {
       if( first )
         {
          Putobj(out,"MirrE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MirrE");
         }
      }

    if( first )
      {
       Printf(out,"SwapF(#;)",get_SwapF());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SwapF(#;)",get_SwapF());
      }

    if( first )
      {
       Printf(out,"SwapE(#;)",get_SwapE());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SwapE(#;)",get_SwapE());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_VP3Control */

enum Bits_VP3Control : uint8
 {
  VP3Control_XTgl  = 0x01u,
  VP3Control_HTgl  = 0x02u,
  VP3Control_VTgl  = 0x04u,
  VP3Control_EMB   = 0x08u,
  VP3Control_DEInt = 0x40u,
  VP3Control_Edge  = 0x80u
 };
 
inline Bits_VP3Control operator | (Bits_VP3Control a,Bits_VP3Control b)
 { return Bits_VP3Control(uint8(a)|uint8(b)); }
 
struct Type_VP3Control
 {
  using Type = uint8 ;

  Type value;


  explicit Type_VP3Control(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_VP3Control & setTo(Bar &bar) { bar.set_VP3Control(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_VP3Control & setTo(Bar &bar,AddressType ind) { bar.set_VP3Control(ind,*this); return *this; }
 

  template <class T>
  Type_VP3Control & set(T to) { to(*this); return *this; }
 

  Type_VP3Control & setbit(Bits_VP3Control bits) { value|=Type(bits); return *this; }
 
  Type_VP3Control & setbitIf(bool cond,Bits_VP3Control bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_VP3Control & clearbit(Bits_VP3Control bits) { value&=~Type(bits); return *this; }
 
  Type_VP3Control & clearbitIf(bool cond,Bits_VP3Control bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_VP3Control bits) const { return value&bits; }
 
  bool testbit(Bits_VP3Control bits) const { return (value&bits)==Type(bits); }
 

  Type get_SpSync() const
   {
    return (value>>4)&0x3u;
   }
 
  Type_VP3Control & set_SpSync(Type field)
   {
    value=((field&0x3u)<<4)|(value&0xFFFFFFCFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&VP3Control_XTgl )
      {
       if( first )
         {
          Putobj(out,"XTgl");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"XTgl");
         }
      }

    if( value&VP3Control_HTgl )
      {
       if( first )
         {
          Putobj(out,"HTgl");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"HTgl");
         }
      }

    if( value&VP3Control_VTgl )
      {
       if( first )
         {
          Putobj(out,"VTgl");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VTgl");
         }
      }

    if( value&VP3Control_EMB )
      {
       if( first )
         {
          Putobj(out,"EMB");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EMB");
         }
      }

    if( value&VP3Control_DEInt )
      {
       if( first )
         {
          Putobj(out,"DEInt");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DEInt");
         }
      }

    if( value&VP3Control_Edge )
      {
       if( first )
         {
          Putobj(out,"Edge");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Edge");
         }
      }

    if( first )
      {
       Printf(out,"SpSync(#;)",get_SpSync());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SpSync(#;)",get_SpSync());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_VP4Control */

enum Bits_VP4Control : uint8
 {
  VP4Control_CCIR656 = 0x10u,
  VP4Control_Alt656  = 0x20u,
  VP4Control_Tst656  = 0x40u,
  VP4Control_TstPat  = 0x80u
 };
 
inline Bits_VP4Control operator | (Bits_VP4Control a,Bits_VP4Control b)
 { return Bits_VP4Control(uint8(a)|uint8(b)); }
 
struct Type_VP4Control
 {
  using Type = uint8 ;

  Type value;


  explicit Type_VP4Control(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_VP4Control & setTo(Bar &bar) { bar.set_VP4Control(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_VP4Control & setTo(Bar &bar,AddressType ind) { bar.set_VP4Control(ind,*this); return *this; }
 

  template <class T>
  Type_VP4Control & set(T to) { to(*this); return *this; }
 

  Type_VP4Control & setbit(Bits_VP4Control bits) { value|=Type(bits); return *this; }
 
  Type_VP4Control & setbitIf(bool cond,Bits_VP4Control bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_VP4Control & clearbit(Bits_VP4Control bits) { value&=~Type(bits); return *this; }
 
  Type_VP4Control & clearbitIf(bool cond,Bits_VP4Control bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_VP4Control bits) const { return value&bits; }
 
  bool testbit(Bits_VP4Control bits) const { return (value&bits)==Type(bits); }
 

  Type get_BLC() const
   {
    return (value>>0)&0x3u;
   }
 
  Type_VP4Control & set_BLC(Type field)
   {
    value=((field&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  Type get_BlankIt() const
   {
    return (value>>2)&0x3u;
   }
 
  Type_VP4Control & set_BlankIt(Type field)
   {
    value=((field&0x3u)<<2)|(value&0xFFFFFFF3u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&VP4Control_CCIR656 )
      {
       if( first )
         {
          Putobj(out,"CCIR656");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CCIR656");
         }
      }

    if( value&VP4Control_Alt656 )
      {
       if( first )
         {
          Putobj(out,"Alt656");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Alt656");
         }
      }

    if( value&VP4Control_Tst656 )
      {
       if( first )
         {
          Putobj(out,"Tst656");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Tst656");
         }
      }

    if( value&VP4Control_TstPat )
      {
       if( first )
         {
          Putobj(out,"TstPat");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TstPat");
         }
      }

    if( first )
      {
       Printf(out,"BLC(#;)",get_BLC());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"BLC(#;)",get_BLC());
      }

    if( first )
      {
       Printf(out,"BlankIt(#;)",get_BlankIt());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"BlankIt(#;)",get_BlankIt());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_VP5Control */

enum Bits_VP5Control : uint8
 {
  VP5Control_CKCase = 0x01u
 };
 
inline Bits_VP5Control operator | (Bits_VP5Control a,Bits_VP5Control b)
 { return Bits_VP5Control(uint8(a)|uint8(b)); }
 
struct Type_VP5Control
 {
  using Type = uint8 ;

  Type value;


  explicit Type_VP5Control(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_VP5Control & setTo(Bar &bar) { bar.set_VP5Control(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_VP5Control & setTo(Bar &bar,AddressType ind) { bar.set_VP5Control(ind,*this); return *this; }
 

  template <class T>
  Type_VP5Control & set(T to) { to(*this); return *this; }
 

  Type_VP5Control & setbit(Bits_VP5Control bits) { value|=Type(bits); return *this; }
 
  Type_VP5Control & setbitIf(bool cond,Bits_VP5Control bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_VP5Control & clearbit(Bits_VP5Control bits) { value&=~Type(bits); return *this; }
 
  Type_VP5Control & clearbitIf(bool cond,Bits_VP5Control bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_VP5Control bits) const { return value&bits; }
 
  bool testbit(Bits_VP5Control bits) const { return (value&bits)==Type(bits); }
 

  Type get_SPCnt() const
   {
    return (value>>1)&0x3u;
   }
 
  Type_VP5Control & set_SPCnt(Type field)
   {
    value=((field&0x3u)<<1)|(value&0xFFFFFFF9u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&VP5Control_CKCase )
      {
       if( first )
         {
          Putobj(out,"CKCase");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CKCase");
         }
      }

    if( first )
      {
       Printf(out,"SPCnt(#;)",get_SPCnt());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SPCnt(#;)",get_SPCnt());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MuxVPVIPOut */

struct Type_MuxVPVIPOut
 {
  using Type = uint8 ;

  Type value;


  explicit Type_MuxVPVIPOut(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MuxVPVIPOut & setTo(Bar &bar) { bar.set_MuxVPVIPOut(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_MuxVPVIPOut & setTo(Bar &bar,AddressType ind) { bar.set_MuxVPVIPOut(ind,*this); return *this; }
 

  template <class T>
  Type_MuxVPVIPOut & set(T to) { to(*this); return *this; }
 

  Type get_Blue() const
   {
    return (value>>0)&0x3u;
   }
 
  Type_MuxVPVIPOut & set_Blue(Type field)
   {
    value=((field&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  Type get_Green() const
   {
    return (value>>2)&0x3u;
   }
 
  Type_MuxVPVIPOut & set_Green(Type field)
   {
    value=((field&0x3u)<<2)|(value&0xFFFFFFF3u);

    return *this;
   }
 

  Type get_Red() const
   {
    return (value>>4)&0x3u;
   }
 
  Type_MuxVPVIPOut & set_Red(Type field)
   {
    value=((field&0x3u)<<4)|(value&0xFFFFFFCFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Blue(#;)",get_Blue());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Blue(#;)",get_Blue());
      }

    if( first )
      {
       Printf(out,"Green(#;)",get_Green());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Green(#;)",get_Green());
      }

    if( first )
      {
       Printf(out,"Red(#;)",get_Red());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Red(#;)",get_Red());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MatControl */

enum Bits_MatControl : uint8
 {
  MatControl_BP = 0x04u
 };
 
inline Bits_MatControl operator | (Bits_MatControl a,Bits_MatControl b)
 { return Bits_MatControl(uint8(a)|uint8(b)); }
 
struct Type_MatControl
 {
  using Type = uint8 ;

  Type value;


  explicit Type_MatControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MatControl & setTo(Bar &bar) { bar.set_MatControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_MatControl & setTo(Bar &bar,AddressType ind) { bar.set_MatControl(ind,*this); return *this; }
 

  template <class T>
  Type_MatControl & set(T to) { to(*this); return *this; }
 

  Type_MatControl & setbit(Bits_MatControl bits) { value|=Type(bits); return *this; }
 
  Type_MatControl & setbitIf(bool cond,Bits_MatControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MatControl & clearbit(Bits_MatControl bits) { value&=~Type(bits); return *this; }
 
  Type_MatControl & clearbitIf(bool cond,Bits_MatControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MatControl bits) const { return value&bits; }
 
  bool testbit(Bits_MatControl bits) const { return (value&bits)==Type(bits); }
 

  Type get_SC() const
   {
    return (value>>0)&0x3u;
   }
 
  Type_MatControl & set_SC(Type field)
   {
    value=((field&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MatControl_BP )
      {
       if( first )
         {
          Putobj(out,"BP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BP");
         }
      }

    if( first )
      {
       Printf(out,"SC(#;)",get_SC());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SC(#;)",get_SC());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_VIDFormat */

enum Bits_VIDFormat : uint8
 {
  VIDFormat_D3NegVS = 0x40u,
  VIDFormat_D3      = 0x80u
 };
 
inline Bits_VIDFormat operator | (Bits_VIDFormat a,Bits_VIDFormat b)
 { return Bits_VIDFormat(uint8(a)|uint8(b)); }
 
struct Type_VIDFormat
 {
  using Type = uint8 ;

  Type value;


  explicit Type_VIDFormat(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_VIDFormat & setTo(Bar &bar) { bar.set_VIDFormat(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_VIDFormat & setTo(Bar &bar,AddressType ind) { bar.set_VIDFormat(ind,*this); return *this; }
 

  template <class T>
  Type_VIDFormat & set(T to) { to(*this); return *this; }
 

  Type_VIDFormat & setbit(Bits_VIDFormat bits) { value|=Type(bits); return *this; }
 
  Type_VIDFormat & setbitIf(bool cond,Bits_VIDFormat bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_VIDFormat & clearbit(Bits_VIDFormat bits) { value&=~Type(bits); return *this; }
 
  Type_VIDFormat & clearbitIf(bool cond,Bits_VIDFormat bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_VIDFormat bits) const { return value&bits; }
 
  bool testbit(Bits_VIDFormat bits) const { return (value&bits)==Type(bits); }
 

  Type get_Format() const
   {
    return (value>>0)&0x1Fu;
   }
 
  Type_VIDFormat & set_Format(Type field)
   {
    value=((field&0x1Fu)<<0)|(value&0xFFFFFFE0u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&VIDFormat_D3NegVS )
      {
       if( first )
         {
          Putobj(out,"D3NegVS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"D3NegVS");
         }
      }

    if( value&VIDFormat_D3 )
      {
       if( first )
         {
          Putobj(out,"D3");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"D3");
         }
      }

    if( first )
      {
       Printf(out,"Format(#;)",get_Format());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Format(#;)",get_Format());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_TBGControl0 */

enum Bits_TBGControl0 : uint8
 {
  TBGControl0_DisFrame = 0x20u,
  TBGControl0_SyncMeth = 0x40u,
  TBGControl0_SyncOnce = 0x80u
 };
 
inline Bits_TBGControl0 operator | (Bits_TBGControl0 a,Bits_TBGControl0 b)
 { return Bits_TBGControl0(uint8(a)|uint8(b)); }
 
struct Type_TBGControl0
 {
  using Type = uint8 ;

  Type value;


  explicit Type_TBGControl0(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TBGControl0 & setTo(Bar &bar) { bar.set_TBGControl0(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_TBGControl0 & setTo(Bar &bar,AddressType ind) { bar.set_TBGControl0(ind,*this); return *this; }
 

  template <class T>
  Type_TBGControl0 & set(T to) { to(*this); return *this; }
 

  Type_TBGControl0 & setbit(Bits_TBGControl0 bits) { value|=Type(bits); return *this; }
 
  Type_TBGControl0 & setbitIf(bool cond,Bits_TBGControl0 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TBGControl0 & clearbit(Bits_TBGControl0 bits) { value&=~Type(bits); return *this; }
 
  Type_TBGControl0 & clearbitIf(bool cond,Bits_TBGControl0 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TBGControl0 bits) const { return value&bits; }
 
  bool testbit(Bits_TBGControl0 bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TBGControl0_DisFrame )
      {
       if( first )
         {
          Putobj(out,"DisFrame");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DisFrame");
         }
      }

    if( value&TBGControl0_SyncMeth )
      {
       if( first )
         {
          Putobj(out,"SyncMeth");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SyncMeth");
         }
      }

    if( value&TBGControl0_SyncOnce )
      {
       if( first )
         {
          Putobj(out,"SyncOnce");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SyncOnce");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_TBGControl1 */

enum Bits_TBGControl1 : uint8
 {
  TBGControl1_HTgl    = 0x01u,
  TBGControl1_VTgl    = 0x02u,
  TBGControl1_EnTgl   = 0x04u,
  TBGControl1_DisDWIN = 0x40u
 };
 
inline Bits_TBGControl1 operator | (Bits_TBGControl1 a,Bits_TBGControl1 b)
 { return Bits_TBGControl1(uint8(a)|uint8(b)); }
 
struct Type_TBGControl1
 {
  using Type = uint8 ;

  Type value;


  explicit Type_TBGControl1(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TBGControl1 & setTo(Bar &bar) { bar.set_TBGControl1(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_TBGControl1 & setTo(Bar &bar,AddressType ind) { bar.set_TBGControl1(ind,*this); return *this; }
 

  template <class T>
  Type_TBGControl1 & set(T to) { to(*this); return *this; }
 

  Type_TBGControl1 & setbit(Bits_TBGControl1 bits) { value|=Type(bits); return *this; }
 
  Type_TBGControl1 & setbitIf(bool cond,Bits_TBGControl1 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TBGControl1 & clearbit(Bits_TBGControl1 bits) { value&=~Type(bits); return *this; }
 
  Type_TBGControl1 & clearbitIf(bool cond,Bits_TBGControl1 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TBGControl1 bits) const { return value&bits; }
 
  bool testbit(Bits_TBGControl1 bits) const { return (value&bits)==Type(bits); }
 

  Type get_VHXExt() const
   {
    return (value>>3)&0x7u;
   }
 
  Type_TBGControl1 & set_VHXExt(Type field)
   {
    value=((field&0x7u)<<3)|(value&0xFFFFFFC7u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TBGControl1_HTgl )
      {
       if( first )
         {
          Putobj(out,"HTgl");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"HTgl");
         }
      }

    if( value&TBGControl1_VTgl )
      {
       if( first )
         {
          Putobj(out,"VTgl");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VTgl");
         }
      }

    if( value&TBGControl1_EnTgl )
      {
       if( first )
         {
          Putobj(out,"EnTgl");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EnTgl");
         }
      }

    if( value&TBGControl1_DisDWIN )
      {
       if( first )
         {
          Putobj(out,"DisDWIN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DisDWIN");
         }
      }

    if( first )
      {
       Printf(out,"VHXExt(#;)",get_VHXExt());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"VHXExt(#;)",get_VHXExt());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_EnSpace */

using Type_EnSpace = uint8 ;

/* struct Type_HVFControl0 */

enum Bits_HVFControl0 : uint8
 {
  HVFControl0_RWB = 0x40u,
  HVFControl0_SM  = 0x80u
 };
 
inline Bits_HVFControl0 operator | (Bits_HVFControl0 a,Bits_HVFControl0 b)
 { return Bits_HVFControl0(uint8(a)|uint8(b)); }
 
struct Type_HVFControl0
 {
  using Type = uint8 ;

  Type value;


  explicit Type_HVFControl0(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_HVFControl0 & setTo(Bar &bar) { bar.set_HVFControl0(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_HVFControl0 & setTo(Bar &bar,AddressType ind) { bar.set_HVFControl0(ind,*this); return *this; }
 

  template <class T>
  Type_HVFControl0 & set(T to) { to(*this); return *this; }
 

  Type_HVFControl0 & setbit(Bits_HVFControl0 bits) { value|=Type(bits); return *this; }
 
  Type_HVFControl0 & setbitIf(bool cond,Bits_HVFControl0 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_HVFControl0 & clearbit(Bits_HVFControl0 bits) { value&=~Type(bits); return *this; }
 
  Type_HVFControl0 & clearbitIf(bool cond,Bits_HVFControl0 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_HVFControl0 bits) const { return value&bits; }
 
  bool testbit(Bits_HVFControl0 bits) const { return (value&bits)==Type(bits); }
 

  Type get_IntPol() const
   {
    return (value>>0)&0x3u;
   }
 
  Type_HVFControl0 & set_IntPol(Type field)
   {
    value=((field&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  Type get_Prefil() const
   {
    return (value>>2)&0x3u;
   }
 
  Type_HVFControl0 & set_Prefil(Type field)
   {
    value=((field&0x3u)<<2)|(value&0xFFFFFFF3u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&HVFControl0_RWB )
      {
       if( first )
         {
          Putobj(out,"RWB");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RWB");
         }
      }

    if( value&HVFControl0_SM )
      {
       if( first )
         {
          Putobj(out,"SM");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SM");
         }
      }

    if( first )
      {
       Printf(out,"IntPol(#;)",get_IntPol());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"IntPol(#;)",get_IntPol());
      }

    if( first )
      {
       Printf(out,"Prefil(#;)",get_Prefil());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Prefil(#;)",get_Prefil());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_HVFControl1 */

enum Bits_HVFControl1 : uint8
 {
  HVFControl1_FOR        = 0x01u,
  HVFControl1_YUV        = 0x02u,
  HVFControl1_SemiPlanar = 0x40u
 };
 
inline Bits_HVFControl1 operator | (Bits_HVFControl1 a,Bits_HVFControl1 b)
 { return Bits_HVFControl1(uint8(a)|uint8(b)); }
 
struct Type_HVFControl1
 {
  using Type = uint8 ;

  Type value;


  explicit Type_HVFControl1(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_HVFControl1 & setTo(Bar &bar) { bar.set_HVFControl1(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_HVFControl1 & setTo(Bar &bar,AddressType ind) { bar.set_HVFControl1(ind,*this); return *this; }
 

  template <class T>
  Type_HVFControl1 & set(T to) { to(*this); return *this; }
 

  Type_HVFControl1 & setbit(Bits_HVFControl1 bits) { value|=Type(bits); return *this; }
 
  Type_HVFControl1 & setbitIf(bool cond,Bits_HVFControl1 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_HVFControl1 & clearbit(Bits_HVFControl1 bits) { value&=~Type(bits); return *this; }
 
  Type_HVFControl1 & clearbitIf(bool cond,Bits_HVFControl1 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_HVFControl1 bits) const { return value&bits; }
 
  bool testbit(Bits_HVFControl1 bits) const { return (value&bits)==Type(bits); }
 

  Type get_VQR() const
   {
    return (value>>2)&0x3u;
   }
 
  Type_HVFControl1 & set_VQR(Type field)
   {
    value=((field&0x3u)<<2)|(value&0xFFFFFFF3u);

    return *this;
   }
 

  Type get_PAD() const
   {
    return (value>>4)&0x3u;
   }
 
  Type_HVFControl1 & set_PAD(Type field)
   {
    value=((field&0x3u)<<4)|(value&0xFFFFFFCFu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&HVFControl1_FOR )
      {
       if( first )
         {
          Putobj(out,"FOR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FOR");
         }
      }

    if( value&HVFControl1_YUV )
      {
       if( first )
         {
          Putobj(out,"YUV");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"YUV");
         }
      }

    if( value&HVFControl1_SemiPlanar )
      {
       if( first )
         {
          Putobj(out,"SemiPlanar");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SemiPlanar");
         }
      }

    if( first )
      {
       Printf(out,"VQR(#;)",get_VQR());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"VQR(#;)",get_VQR());
      }

    if( first )
      {
       Printf(out,"PAD(#;)",get_PAD());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"PAD(#;)",get_PAD());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_RepControl */

using Type_RepControl = uint8 ;

/* struct Type_PLLSerial1 */

enum Bits_PLLSerial1 : uint8
 {
  PLLSerial1_FDN   = 0x01u,
  PLLSerial1_ManIZ = 0x40u
 };
 
inline Bits_PLLSerial1 operator | (Bits_PLLSerial1 a,Bits_PLLSerial1 b)
 { return Bits_PLLSerial1(uint8(a)|uint8(b)); }
 
struct Type_PLLSerial1
 {
  using Type = uint8 ;

  Type value;


  explicit Type_PLLSerial1(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PLLSerial1 & setTo(Bar &bar) { bar.set_PLLSerial1(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PLLSerial1 & setTo(Bar &bar,AddressType ind) { bar.set_PLLSerial1(ind,*this); return *this; }
 

  template <class T>
  Type_PLLSerial1 & set(T to) { to(*this); return *this; }
 

  Type_PLLSerial1 & setbit(Bits_PLLSerial1 bits) { value|=Type(bits); return *this; }
 
  Type_PLLSerial1 & setbitIf(bool cond,Bits_PLLSerial1 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_PLLSerial1 & clearbit(Bits_PLLSerial1 bits) { value&=~Type(bits); return *this; }
 
  Type_PLLSerial1 & clearbitIf(bool cond,Bits_PLLSerial1 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_PLLSerial1 bits) const { return value&bits; }
 
  bool testbit(Bits_PLLSerial1 bits) const { return (value&bits)==Type(bits); }
 

  Type get_IZ() const
   {
    return (value>>1)&0x3u;
   }
 
  Type_PLLSerial1 & set_IZ(Type field)
   {
    value=((field&0x3u)<<1)|(value&0xFFFFFFF9u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&PLLSerial1_FDN )
      {
       if( first )
         {
          Putobj(out,"FDN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FDN");
         }
      }

    if( value&PLLSerial1_ManIZ )
      {
       if( first )
         {
          Putobj(out,"ManIZ");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ManIZ");
         }
      }

    if( first )
      {
       Printf(out,"IZ(#;)",get_IZ());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"IZ(#;)",get_IZ());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PLLSerial2 */

struct Type_PLLSerial2
 {
  using Type = uint8 ;

  Type value;


  explicit Type_PLLSerial2(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PLLSerial2 & setTo(Bar &bar) { bar.set_PLLSerial2(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PLLSerial2 & setTo(Bar &bar,AddressType ind) { bar.set_PLLSerial2(ind,*this); return *this; }
 

  template <class T>
  Type_PLLSerial2 & set(T to) { to(*this); return *this; }
 

  Type get_NOSC() const
   {
    return (value>>0)&0x3u;
   }
 
  Type_PLLSerial2 & set_NOSC(Type field)
   {
    value=((field&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  Type get_PR() const
   {
    return (value>>4)&0xFu;
   }
 
  Type_PLLSerial2 & set_PR(Type field)
   {
    value=((field&0xFu)<<4)|(value&0xFFFFFF0Fu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"NOSC(#;)",get_NOSC());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"NOSC(#;)",get_NOSC());
      }

    if( first )
      {
       Printf(out,"PR(#;)",get_PR());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"PR(#;)",get_PR());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PLLSerial3 */

enum Bits_PLLSerial3 : uint8
 {
  PLLSerial3_CCIR     = 0x01u,
  PLLSerial3_DE       = 0x02u,
  PLLSerial3_PXIN_SEL = 0x10u
 };
 
inline Bits_PLLSerial3 operator | (Bits_PLLSerial3 a,Bits_PLLSerial3 b)
 { return Bits_PLLSerial3(uint8(a)|uint8(b)); }
 
struct Type_PLLSerial3
 {
  using Type = uint8 ;

  Type value;


  explicit Type_PLLSerial3(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PLLSerial3 & setTo(Bar &bar) { bar.set_PLLSerial3(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PLLSerial3 & setTo(Bar &bar,AddressType ind) { bar.set_PLLSerial3(ind,*this); return *this; }
 

  template <class T>
  Type_PLLSerial3 & set(T to) { to(*this); return *this; }
 

  Type_PLLSerial3 & setbit(Bits_PLLSerial3 bits) { value|=Type(bits); return *this; }
 
  Type_PLLSerial3 & setbitIf(bool cond,Bits_PLLSerial3 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_PLLSerial3 & clearbit(Bits_PLLSerial3 bits) { value&=~Type(bits); return *this; }
 
  Type_PLLSerial3 & clearbitIf(bool cond,Bits_PLLSerial3 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_PLLSerial3 bits) const { return value&bits; }
 
  bool testbit(Bits_PLLSerial3 bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&PLLSerial3_CCIR )
      {
       if( first )
         {
          Putobj(out,"CCIR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CCIR");
         }
      }

    if( value&PLLSerial3_DE )
      {
       if( first )
         {
          Putobj(out,"DE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DE");
         }
      }

    if( value&PLLSerial3_PXIN_SEL )
      {
       if( first )
         {
          Putobj(out,"PXIN_SEL");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PXIN_SEL");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Serializer */

struct Type_Serializer
 {
  using Type = uint8 ;

  Type value;


  explicit Type_Serializer(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Serializer & setTo(Bar &bar) { bar.set_Serializer(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_Serializer & setTo(Bar &bar,AddressType ind) { bar.set_Serializer(ind,*this); return *this; }
 

  template <class T>
  Type_Serializer & set(T to) { to(*this); return *this; }
 

  Type get_Phase2() const
   {
    return (value>>0)&0xFu;
   }
 
  Type_Serializer & set_Phase2(Type field)
   {
    value=((field&0xFu)<<0)|(value&0xFFFFFFF0u);

    return *this;
   }
 

  Type get_Phase3() const
   {
    return (value>>4)&0xFu;
   }
 
  Type_Serializer & set_Phase3(Type field)
   {
    value=((field&0xFu)<<4)|(value&0xFFFFFF0Fu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Phase2(#;)",get_Phase2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Phase2(#;)",get_Phase2());
      }

    if( first )
      {
       Printf(out,"Phase3(#;)",get_Phase3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Phase3(#;)",get_Phase3());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_BufferOut */

struct Type_BufferOut
 {
  using Type = uint8 ;

  Type value;


  explicit Type_BufferOut(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_BufferOut & setTo(Bar &bar) { bar.set_BufferOut(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_BufferOut & setTo(Bar &bar,AddressType ind) { bar.set_BufferOut(ind,*this); return *this; }
 

  template <class T>
  Type_BufferOut & set(T to) { to(*this); return *this; }
 

  Type get_CLK() const
   {
    return (value>>0)&0x3u;
   }
 
  Type_BufferOut & set_CLK(Type field)
   {
    value=((field&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  Type get_Force() const
   {
    return (value>>2)&0x3u;
   }
 
  Type_BufferOut & set_Force(Type field)
   {
    value=((field&0x3u)<<2)|(value&0xFFFFFFF3u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"CLK(#;)",get_CLK());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CLK(#;)",get_CLK());
      }

    if( first )
      {
       Printf(out,"Force(#;)",get_Force());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Force(#;)",get_Force());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PLLSCG1 */

enum Bits_PLLSCG1 : uint8
 {
  PLLSCG1_FDN = 0x01u
 };
 
inline Bits_PLLSCG1 operator | (Bits_PLLSCG1 a,Bits_PLLSCG1 b)
 { return Bits_PLLSCG1(uint8(a)|uint8(b)); }
 
struct Type_PLLSCG1
 {
  using Type = uint8 ;

  Type value;


  explicit Type_PLLSCG1(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PLLSCG1 & setTo(Bar &bar) { bar.set_PLLSCG1(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PLLSCG1 & setTo(Bar &bar,AddressType ind) { bar.set_PLLSCG1(ind,*this); return *this; }
 

  template <class T>
  Type_PLLSCG1 & set(T to) { to(*this); return *this; }
 

  Type_PLLSCG1 & setbit(Bits_PLLSCG1 bits) { value|=Type(bits); return *this; }
 
  Type_PLLSCG1 & setbitIf(bool cond,Bits_PLLSCG1 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_PLLSCG1 & clearbit(Bits_PLLSCG1 bits) { value&=~Type(bits); return *this; }
 
  Type_PLLSCG1 & clearbitIf(bool cond,Bits_PLLSCG1 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_PLLSCG1 bits) const { return value&bits; }
 
  bool testbit(Bits_PLLSCG1 bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&PLLSCG1_FDN )
      {
       if( first )
         {
          Putobj(out,"FDN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FDN");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PLLSCG2 */

enum Bits_PLLSCG2 : uint8
 {
  PLLSCG2_SelCLKIN = 0x10u,
  PLLSCG2_Bypass   = 0x80u
 };
 
inline Bits_PLLSCG2 operator | (Bits_PLLSCG2 a,Bits_PLLSCG2 b)
 { return Bits_PLLSCG2(uint8(a)|uint8(b)); }
 
struct Type_PLLSCG2
 {
  using Type = uint8 ;

  Type value;


  explicit Type_PLLSCG2(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PLLSCG2 & setTo(Bar &bar) { bar.set_PLLSCG2(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PLLSCG2 & setTo(Bar &bar,AddressType ind) { bar.set_PLLSCG2(ind,*this); return *this; }
 

  template <class T>
  Type_PLLSCG2 & set(T to) { to(*this); return *this; }
 

  Type_PLLSCG2 & setbit(Bits_PLLSCG2 bits) { value|=Type(bits); return *this; }
 
  Type_PLLSCG2 & setbitIf(bool cond,Bits_PLLSCG2 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_PLLSCG2 & clearbit(Bits_PLLSCG2 bits) { value&=~Type(bits); return *this; }
 
  Type_PLLSCG2 & clearbitIf(bool cond,Bits_PLLSCG2 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_PLLSCG2 bits) const { return value&bits; }
 
  bool testbit(Bits_PLLSCG2 bits) const { return (value&bits)==Type(bits); }
 

  Type get_NOSC() const
   {
    return (value>>0)&0x3u;
   }
 
  Type_PLLSCG2 & set_NOSC(Type field)
   {
    value=((field&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&PLLSCG2_SelCLKIN )
      {
       if( first )
         {
          Putobj(out,"SelCLKIN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SelCLKIN");
         }
      }

    if( value&PLLSCG2_Bypass )
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

    if( first )
      {
       Printf(out,"NOSC(#;)",get_NOSC());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"NOSC(#;)",get_NOSC());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_PLLSCGN1 */

using Type_PLLSCGN1 = uint8 ;

/* type Type_PLLSCGN2 */

using Type_PLLSCGN2 = uint8 ;

/* type Type_PLLSCGR1 */

using Type_PLLSCGR1 = uint8 ;

/* type Type_PLLSCGR2 */

using Type_PLLSCGR2 = uint8 ;

/* struct Type_AudioDiv */

struct Type_AudioDiv
 {
  using Type = uint8 ;

  Type value;


  explicit Type_AudioDiv(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_AudioDiv & setTo(Bar &bar) { bar.set_AudioDiv(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_AudioDiv & setTo(Bar &bar,AddressType ind) { bar.set_AudioDiv(ind,*this); return *this; }
 

  template <class T>
  Type_AudioDiv & set(T to) { to(*this); return *this; }
 

  Type get_Div() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_AudioDiv & set_Div(Type field)
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
 
/* struct Type_SelectCLK */

enum Bits_SelectCLK : uint8
 {
  SelectCLK_CLK1 = 0x01u,
  SelectCLK_EnSC = 0x08u
 };
 
inline Bits_SelectCLK operator | (Bits_SelectCLK a,Bits_SelectCLK b)
 { return Bits_SelectCLK(uint8(a)|uint8(b)); }
 
struct Type_SelectCLK
 {
  using Type = uint8 ;

  Type value;


  explicit Type_SelectCLK(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SelectCLK & setTo(Bar &bar) { bar.set_SelectCLK(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_SelectCLK & setTo(Bar &bar,AddressType ind) { bar.set_SelectCLK(ind,*this); return *this; }
 

  template <class T>
  Type_SelectCLK & set(T to) { to(*this); return *this; }
 

  Type_SelectCLK & setbit(Bits_SelectCLK bits) { value|=Type(bits); return *this; }
 
  Type_SelectCLK & setbitIf(bool cond,Bits_SelectCLK bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SelectCLK & clearbit(Bits_SelectCLK bits) { value&=~Type(bits); return *this; }
 
  Type_SelectCLK & clearbitIf(bool cond,Bits_SelectCLK bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SelectCLK bits) const { return value&bits; }
 
  bool testbit(Bits_SelectCLK bits) const { return (value&bits)==Type(bits); }
 

  Type get_VRFCLK() const
   {
    return (value>>1)&0x3u;
   }
 
  Type_SelectCLK & set_VRFCLK(Type field)
   {
    value=((field&0x3u)<<1)|(value&0xFFFFFFF9u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SelectCLK_CLK1 )
      {
       if( first )
         {
          Putobj(out,"CLK1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CLK1");
         }
      }

    if( value&SelectCLK_EnSC )
      {
       if( first )
         {
          Putobj(out,"EnSC");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EnSC");
         }
      }

    if( first )
      {
       Printf(out,"VRFCLK(#;)",get_VRFCLK());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"VRFCLK(#;)",get_VRFCLK());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_ANAGeneral */

using Type_ANAGeneral = uint8 ;

/* type Type_EDIDBlock */

using Type_EDIDBlock = uint8 ;

/* struct Type_DDCControl */

enum Bits_DDCControl : uint8
 {
  DDCControl_Read = 0x01u
 };
 
inline Bits_DDCControl operator | (Bits_DDCControl a,Bits_DDCControl b)
 { return Bits_DDCControl(uint8(a)|uint8(b)); }
 
struct Type_DDCControl
 {
  using Type = uint8 ;

  Type value;


  explicit Type_DDCControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DDCControl & setTo(Bar &bar) { bar.set_DDCControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_DDCControl & setTo(Bar &bar,AddressType ind) { bar.set_DDCControl(ind,*this); return *this; }
 

  template <class T>
  Type_DDCControl & set(T to) { to(*this); return *this; }
 

  Type_DDCControl & setbit(Bits_DDCControl bits) { value|=Type(bits); return *this; }
 
  Type_DDCControl & setbitIf(bool cond,Bits_DDCControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_DDCControl & clearbit(Bits_DDCControl bits) { value&=~Type(bits); return *this; }
 
  Type_DDCControl & clearbitIf(bool cond,Bits_DDCControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_DDCControl bits) const { return value&bits; }
 
  bool testbit(Bits_DDCControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&DDCControl_Read )
      {
       if( first )
         {
          Putobj(out,"Read");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Read");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_DDCAddress */

using Type_DDCAddress = uint8 ;

/* type Type_DDCOff */

using Type_DDCOff = uint8 ;

/* type Type_DDCSegAddr */

using Type_DDCSegAddr = uint8 ;

/* type Type_DDCSeg */

using Type_DDCSeg = uint8 ;

/* struct Type_AIPControl0 */

enum Bits_AIPControl0 : uint8
 {
  AIPControl0_ResetFIFO = 0x01u,
  AIPControl0_Swap      = 0x02u,
  AIPControl0_Layout    = 0x04u,
  AIPControl0_AcrMan    = 0x20u,
  AIPControl0_ResetCTS  = 0x40u
 };
 
inline Bits_AIPControl0 operator | (Bits_AIPControl0 a,Bits_AIPControl0 b)
 { return Bits_AIPControl0(uint8(a)|uint8(b)); }
 
struct Type_AIPControl0
 {
  using Type = uint8 ;

  Type value;


  explicit Type_AIPControl0(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_AIPControl0 & setTo(Bar &bar) { bar.set_AIPControl0(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_AIPControl0 & setTo(Bar &bar,AddressType ind) { bar.set_AIPControl0(ind,*this); return *this; }
 

  template <class T>
  Type_AIPControl0 & set(T to) { to(*this); return *this; }
 

  Type_AIPControl0 & setbit(Bits_AIPControl0 bits) { value|=Type(bits); return *this; }
 
  Type_AIPControl0 & setbitIf(bool cond,Bits_AIPControl0 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_AIPControl0 & clearbit(Bits_AIPControl0 bits) { value&=~Type(bits); return *this; }
 
  Type_AIPControl0 & clearbitIf(bool cond,Bits_AIPControl0 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_AIPControl0 bits) const { return value&bits; }
 
  bool testbit(Bits_AIPControl0 bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&AIPControl0_ResetFIFO )
      {
       if( first )
         {
          Putobj(out,"ResetFIFO");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ResetFIFO");
         }
      }

    if( value&AIPControl0_Swap )
      {
       if( first )
         {
          Putobj(out,"Swap");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Swap");
         }
      }

    if( value&AIPControl0_Layout )
      {
       if( first )
         {
          Putobj(out,"Layout");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Layout");
         }
      }

    if( value&AIPControl0_AcrMan )
      {
       if( first )
         {
          Putobj(out,"AcrMan");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AcrMan");
         }
      }

    if( value&AIPControl0_ResetCTS )
      {
       if( first )
         {
          Putobj(out,"ResetCTS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ResetCTS");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_ENCControl */

enum Bits_ENCControl : uint8
 {
  ENCControl_ResetEnc = 0x01u,
  ENCControl_ResetSel = 0x02u
 };
 
inline Bits_ENCControl operator | (Bits_ENCControl a,Bits_ENCControl b)
 { return Bits_ENCControl(uint8(a)|uint8(b)); }
 
struct Type_ENCControl
 {
  using Type = uint8 ;

  Type value;


  explicit Type_ENCControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ENCControl & setTo(Bar &bar) { bar.set_ENCControl(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_ENCControl & setTo(Bar &bar,AddressType ind) { bar.set_ENCControl(ind,*this); return *this; }
 

  template <class T>
  Type_ENCControl & set(T to) { to(*this); return *this; }
 

  Type_ENCControl & setbit(Bits_ENCControl bits) { value|=Type(bits); return *this; }
 
  Type_ENCControl & setbitIf(bool cond,Bits_ENCControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_ENCControl & clearbit(Bits_ENCControl bits) { value&=~Type(bits); return *this; }
 
  Type_ENCControl & clearbitIf(bool cond,Bits_ENCControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_ENCControl bits) const { return value&bits; }
 
  bool testbit(Bits_ENCControl bits) const { return (value&bits)==Type(bits); }
 

  Type get_Code() const
   {
    return (value>>2)&0x3u;
   }
 
  Type_ENCControl & set_Code(Type field)
   {
    value=((field&0x3u)<<2)|(value&0xFFFFFFF3u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&ENCControl_ResetEnc )
      {
       if( first )
         {
          Putobj(out,"ResetEnc");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ResetEnc");
         }
      }

    if( value&ENCControl_ResetSel )
      {
       if( first )
         {
          Putobj(out,"ResetSel");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ResetSel");
         }
      }

    if( first )
      {
       Printf(out,"Code(#;)",get_Code());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Code(#;)",get_Code());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_TX3 */

using Type_TX3 = uint8 ;

/* struct Type_TX33 */

enum Bits_TX33 : uint8
 {
  TX33_HDMI = 0x02u
 };
 
inline Bits_TX33 operator | (Bits_TX33 a,Bits_TX33 b)
 { return Bits_TX33(uint8(a)|uint8(b)); }
 
struct Type_TX33
 {
  using Type = uint8 ;

  Type value;


  explicit Type_TX33(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TX33 & setTo(Bar &bar) { bar.set_TX33(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_TX33 & setTo(Bar &bar,AddressType ind) { bar.set_TX33(ind,*this); return *this; }
 

  template <class T>
  Type_TX33 & set(T to) { to(*this); return *this; }
 

  Type_TX33 & setbit(Bits_TX33 bits) { value|=Type(bits); return *this; }
 
  Type_TX33 & setbitIf(bool cond,Bits_TX33 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TX33 & clearbit(Bits_TX33 bits) { value&=~Type(bits); return *this; }
 
  Type_TX33 & clearbitIf(bool cond,Bits_TX33 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TX33 bits) const { return value&bits; }
 
  bool testbit(Bits_TX33 bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TX33_HDMI )
      {
       if( first )
         {
          Putobj(out,"HDMI");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"HDMI");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_TX4 */

enum Bits_TX4 : uint8
 {
  TX4_HDCP = 0x01u,
  TX4_RAM  = 0x02u,
  TX4_RG   = 0x04u
 };
 
inline Bits_TX4 operator | (Bits_TX4 a,Bits_TX4 b)
 { return Bits_TX4(uint8(a)|uint8(b)); }
 
struct Type_TX4
 {
  using Type = uint8 ;

  Type value;


  explicit Type_TX4(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TX4 & setTo(Bar &bar) { bar.set_TX4(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_TX4 & setTo(Bar &bar,AddressType ind) { bar.set_TX4(ind,*this); return *this; }
 

  template <class T>
  Type_TX4 & set(T to) { to(*this); return *this; }
 

  Type_TX4 & setbit(Bits_TX4 bits) { value|=Type(bits); return *this; }
 
  Type_TX4 & setbitIf(bool cond,Bits_TX4 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TX4 & clearbit(Bits_TX4 bits) { value&=~Type(bits); return *this; }
 
  Type_TX4 & clearbitIf(bool cond,Bits_TX4 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TX4 bits) const { return value&bits; }
 
  bool testbit(Bits_TX4 bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TX4_HDCP )
      {
       if( first )
         {
          Putobj(out,"HDCP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"HDCP");
         }
      }

    if( value&TX4_RAM )
      {
       if( first )
         {
          Putobj(out,"RAM");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RAM");
         }
      }

    if( value&TX4_RG )
      {
       if( first )
         {
          Putobj(out,"RG");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RG");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_Geom */

using Type_Geom = uint16 ;

/* struct CECBar<RW> */

template <class RW>
struct CECBar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit CECBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- CEC_FRO_IMCLK

  Type_CEC_FRO_IMCLK get_CEC_FRO_IMCLK() { return Type_CEC_FRO_IMCLK(rw.template get<uint8>(0xFBu)); }
 
  void set_CEC_FRO_IMCLK(Type_CEC_FRO_IMCLK value) { rw.set(0xFBu,value.value); }
 
  Setter<Type_CEC_FRO_IMCLK> to_CEC_FRO_IMCLK() { return Setter<Type_CEC_FRO_IMCLK>(rw,0xFBu); }
 
  static Type_CEC_FRO_IMCLK null_CEC_FRO_IMCLK() { return Type_CEC_FRO_IMCLK(0); }
 
  static Type_CEC_FRO_IMCLK ones_CEC_FRO_IMCLK() { return Type_CEC_FRO_IMCLK(Type_CEC_FRO_IMCLK::Type(-1)); }
 
  //--- CECStatus

  Type_CECStatus get_CECStatus() { return Type_CECStatus(rw.template get<uint8>(0xFEu)); }
 
  static Type_CECStatus null_CECStatus() { return Type_CECStatus(0); }
 
  static Type_CECStatus ones_CECStatus() { return Type_CECStatus(Type_CECStatus::Type(-1)); }
 
  //--- CECIntStatus

  Type_CECIntStatus get_CECIntStatus() { return Type_CECIntStatus(rw.template get<uint8>(0xFDu)); }
 
  static Type_CECIntStatus null_CECIntStatus() { return Type_CECIntStatus(0); }
 
  static Type_CECIntStatus ones_CECIntStatus() { return Type_CECIntStatus(Type_CECIntStatus::Type(-1)); }
 
  //--- CECIntEnable

  Type_CECIntEnable get_CECIntEnable() { return Type_CECIntEnable(rw.template get<uint8>(0xFCu)); }
 
  void set_CECIntEnable(Type_CECIntEnable value) { rw.set(0xFCu,value.value); }
 
  Setter<Type_CECIntEnable> to_CECIntEnable() { return Setter<Type_CECIntEnable>(rw,0xFCu); }
 
  static Type_CECIntEnable null_CECIntEnable() { return Type_CECIntEnable(0); }
 
  static Type_CECIntEnable ones_CECIntEnable() { return Type_CECIntEnable(Type_CECIntEnable::Type(-1)); }
 
  //--- CECEnable

  Type_CECEnable get_CECEnable() { return Type_CECEnable(rw.template get<uint8>(0xFFu)); }
 
  void set_CECEnable(Type_CECEnable value) { rw.set(0xFFu,value.value); }
 
  Setter<Type_CECEnable> to_CECEnable() { return Setter<Type_CECEnable>(rw,0xFFu); }
 
  static Type_CECEnable null_CECEnable() { return Type_CECEnable(0); }
 
  static Type_CECEnable ones_CECEnable() { return Type_CECEnable(Type_CECEnable::Type(-1)); }
 
  //--- CECIntSource

  Type_CECIntSource get_CECIntSource() { return Type_CECIntSource(rw.template get<uint8>(0xEEu)); }
 
  static Type_CECIntSource null_CECIntSource() { return Type_CECIntSource(0); }
 
  static Type_CECIntSource ones_CECIntSource() { return Type_CECIntSource(Type_CECIntSource::Type(-1)); }
 
 };
 
/* struct HDMIBar<RW> */

template <class RW>
struct HDMIBar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit HDMIBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- VersionLSB

  Type_VersionLSB get_VersionLSB() { return Type_VersionLSB(rw.template get<uint8>(0x0u)); }
 
  static Type_VersionLSB null_VersionLSB() { return Type_VersionLSB(0); }
 
  static Type_VersionLSB ones_VersionLSB() { return Type_VersionLSB(Type_VersionLSB::Type(-1)); }
 
  //--- VersionMSB

  Type_VersionMSB get_VersionMSB() { return Type_VersionMSB(rw.template get<uint8>(0x2u)); }
 
  //--- MainControl0

  Type_MainControl0 get_MainControl0() { return Type_MainControl0(rw.template get<uint8>(0x1u)); }
 
  void set_MainControl0(Type_MainControl0 value) { rw.set(0x1u,value.value); }
 
  Setter<Type_MainControl0> to_MainControl0() { return Setter<Type_MainControl0>(rw,0x1u); }
 
  static Type_MainControl0 null_MainControl0() { return Type_MainControl0(0); }
 
  static Type_MainControl0 ones_MainControl0() { return Type_MainControl0(Type_MainControl0::Type(-1)); }
 
  //--- SoftReset

  void set_SoftReset(Type_SoftReset value) { rw.set(0xAu,value.value); }
 
  Setter<Type_SoftReset> to_SoftReset() { return Setter<Type_SoftReset>(rw,0xAu); }
 
  static Type_SoftReset null_SoftReset() { return Type_SoftReset(0); }
 
  static Type_SoftReset ones_SoftReset() { return Type_SoftReset(Type_SoftReset::Type(-1)); }
 
  //--- DDCDisable

  Type_DDCDisable get_DDCDisable() { return Type_DDCDisable(rw.template get<uint8>(0xBu)); }
 
  void set_DDCDisable(Type_DDCDisable value) { rw.set(0xBu,value.value); }
 
  Setter<Type_DDCDisable> to_DDCDisable() { return Setter<Type_DDCDisable>(rw,0xBu); }
 
  static Type_DDCDisable null_DDCDisable() { return Type_DDCDisable(0); }
 
  static Type_DDCDisable ones_DDCDisable() { return Type_DDCDisable(Type_DDCDisable::Type(-1)); }
 
  //--- IntFlags0

  Type_IntFlags0 get_IntFlags0() { return Type_IntFlags0(rw.template get<uint8>(0xFu)); }
 
  void set_IntFlags0(Type_IntFlags0 value) { rw.set(0xFu,value); }
 
  void set_IntFlags0_null() { rw.set(0xFu,Type_IntFlags0(0)); }
 
  void set_IntFlags0_ones() { rw.set(0xFu,Type_IntFlags0(-1)); }
 
  //--- IntFlags1

  Type_IntFlags1 get_IntFlags1() { return Type_IntFlags1(rw.template get<uint8>(0x10u)); }
 
  void set_IntFlags1(Type_IntFlags1 value) { rw.set(0x10u,value); }
 
  void set_IntFlags1_null() { rw.set(0x10u,Type_IntFlags1(0)); }
 
  void set_IntFlags1_ones() { rw.set(0x10u,Type_IntFlags1(-1)); }
 
  //--- IntFlags2

  Type_IntFlags2 get_IntFlags2() { return Type_IntFlags2(rw.template get<uint8>(0x11u)); }
 
  void set_IntFlags2(Type_IntFlags2 value) { rw.set(0x11u,value.value); }
 
  Setter<Type_IntFlags2> to_IntFlags2() { return Setter<Type_IntFlags2>(rw,0x11u); }
 
  static Type_IntFlags2 null_IntFlags2() { return Type_IntFlags2(0); }
 
  static Type_IntFlags2 ones_IntFlags2() { return Type_IntFlags2(Type_IntFlags2::Type(-1)); }
 
  //--- VP0Enable

  Type_VP0Enable get_VP0Enable() { return Type_VP0Enable(rw.template get<uint8>(0x18u)); }
 
  void set_VP0Enable(Type_VP0Enable value) { rw.set(0x18u,value); }
 
  void set_VP0Enable_null() { rw.set(0x18u,Type_VP0Enable(0)); }
 
  void set_VP0Enable_ones() { rw.set(0x18u,Type_VP0Enable(-1)); }
 
  //--- VP1Enable

  Type_VP1Enable get_VP1Enable() { return Type_VP1Enable(rw.template get<uint8>(0x19u)); }
 
  void set_VP1Enable(Type_VP1Enable value) { rw.set(0x19u,value); }
 
  void set_VP1Enable_null() { rw.set(0x19u,Type_VP1Enable(0)); }
 
  void set_VP1Enable_ones() { rw.set(0x19u,Type_VP1Enable(-1)); }
 
  //--- VP2Enable

  Type_VP2Enable get_VP2Enable() { return Type_VP2Enable(rw.template get<uint8>(0x1Au)); }
 
  void set_VP2Enable(Type_VP2Enable value) { rw.set(0x1Au,value); }
 
  void set_VP2Enable_null() { rw.set(0x1Au,Type_VP2Enable(0)); }
 
  void set_VP2Enable_ones() { rw.set(0x1Au,Type_VP2Enable(-1)); }
 
  //--- VP0Control

  void set_VP0Control(Type_VP0Control value) { rw.set(0x20u,value.value); }
 
  Setter<Type_VP0Control> to_VP0Control() { return Setter<Type_VP0Control>(rw,0x20u); }
 
  static Type_VP0Control null_VP0Control() { return Type_VP0Control(0); }
 
  static Type_VP0Control ones_VP0Control() { return Type_VP0Control(Type_VP0Control::Type(-1)); }
 
  //--- VP1Control

  void set_VP1Control(Type_VP1Control value) { rw.set(0x21u,value.value); }
 
  Setter<Type_VP1Control> to_VP1Control() { return Setter<Type_VP1Control>(rw,0x21u); }
 
  static Type_VP1Control null_VP1Control() { return Type_VP1Control(0); }
 
  static Type_VP1Control ones_VP1Control() { return Type_VP1Control(Type_VP1Control::Type(-1)); }
 
  //--- VP2Control

  void set_VP2Control(Type_VP2Control value) { rw.set(0x22u,value.value); }
 
  Setter<Type_VP2Control> to_VP2Control() { return Setter<Type_VP2Control>(rw,0x22u); }
 
  static Type_VP2Control null_VP2Control() { return Type_VP2Control(0); }
 
  static Type_VP2Control ones_VP2Control() { return Type_VP2Control(Type_VP2Control::Type(-1)); }
 
  //--- VP3Control

  void set_VP3Control(Type_VP3Control value) { rw.set(0x23u,value.value); }
 
  Setter<Type_VP3Control> to_VP3Control() { return Setter<Type_VP3Control>(rw,0x23u); }
 
  static Type_VP3Control null_VP3Control() { return Type_VP3Control(0); }
 
  static Type_VP3Control ones_VP3Control() { return Type_VP3Control(Type_VP3Control::Type(-1)); }
 
  //--- VP4Control

  void set_VP4Control(Type_VP4Control value) { rw.set(0x24u,value.value); }
 
  Setter<Type_VP4Control> to_VP4Control() { return Setter<Type_VP4Control>(rw,0x24u); }
 
  static Type_VP4Control null_VP4Control() { return Type_VP4Control(0); }
 
  static Type_VP4Control ones_VP4Control() { return Type_VP4Control(Type_VP4Control::Type(-1)); }
 
  //--- VP5Control

  void set_VP5Control(Type_VP5Control value) { rw.set(0x25u,value.value); }
 
  Setter<Type_VP5Control> to_VP5Control() { return Setter<Type_VP5Control>(rw,0x25u); }
 
  static Type_VP5Control null_VP5Control() { return Type_VP5Control(0); }
 
  static Type_VP5Control ones_VP5Control() { return Type_VP5Control(Type_VP5Control::Type(-1)); }
 
  //--- MuxVPVIPOut

  Type_MuxVPVIPOut get_MuxVPVIPOut() { return Type_MuxVPVIPOut(rw.template get<uint8>(0x27u)); }
 
  void set_MuxVPVIPOut(Type_MuxVPVIPOut value) { rw.set(0x27u,value.value); }
 
  Setter<Type_MuxVPVIPOut> to_MuxVPVIPOut() { return Setter<Type_MuxVPVIPOut>(rw,0x27u); }
 
  static Type_MuxVPVIPOut null_MuxVPVIPOut() { return Type_MuxVPVIPOut(0); }
 
  static Type_MuxVPVIPOut ones_MuxVPVIPOut() { return Type_MuxVPVIPOut(Type_MuxVPVIPOut::Type(-1)); }
 
  //--- MatControl

  void set_MatControl(Type_MatControl value) { rw.set(0x80u,value.value); }
 
  Setter<Type_MatControl> to_MatControl() { return Setter<Type_MatControl>(rw,0x80u); }
 
  static Type_MatControl null_MatControl() { return Type_MatControl(0); }
 
  static Type_MatControl ones_MatControl() { return Type_MatControl(Type_MatControl::Type(-1)); }
 
  //--- VIDFormat

  void set_VIDFormat(Type_VIDFormat value) { rw.set(0xA0u,value.value); }
 
  Setter<Type_VIDFormat> to_VIDFormat() { return Setter<Type_VIDFormat>(rw,0xA0u); }
 
  static Type_VIDFormat null_VIDFormat() { return Type_VIDFormat(0); }
 
  static Type_VIDFormat ones_VIDFormat() { return Type_VIDFormat(Type_VIDFormat::Type(-1)); }
 
  //--- RefPix

  void set_RefPix(Type_Geom value) { rw.set(0xA1u,value); }
 
  void set_RefPix_null() { rw.set(0xA1u,Type_Geom(0)); }
 
  void set_RefPix_ones() { rw.set(0xA1u,Type_Geom(-1)); }
 
  //--- RefLine

  void set_RefLine(Type_Geom value) { rw.set(0xA3u,value); }
 
  void set_RefLine_null() { rw.set(0xA3u,Type_Geom(0)); }
 
  void set_RefLine_ones() { rw.set(0xA3u,Type_Geom(-1)); }
 
  //--- NumPix

  void set_NumPix(Type_Geom value) { rw.set(0xA5u,value); }
 
  void set_NumPix_null() { rw.set(0xA5u,Type_Geom(0)); }
 
  void set_NumPix_ones() { rw.set(0xA5u,Type_Geom(-1)); }
 
  //--- NumLine

  void set_NumLine(Type_Geom value) { rw.set(0xA7u,value); }
 
  void set_NumLine_null() { rw.set(0xA7u,Type_Geom(0)); }
 
  void set_NumLine_ones() { rw.set(0xA7u,Type_Geom(-1)); }
 
  //--- VS1LineS

  void set_VS1LineS(Type_Geom value) { rw.set(0xA9u,value); }
 
  void set_VS1LineS_null() { rw.set(0xA9u,Type_Geom(0)); }
 
  void set_VS1LineS_ones() { rw.set(0xA9u,Type_Geom(-1)); }
 
  //--- VS1PixS

  void set_VS1PixS(Type_Geom value) { rw.set(0xABu,value); }
 
  void set_VS1PixS_null() { rw.set(0xABu,Type_Geom(0)); }
 
  void set_VS1PixS_ones() { rw.set(0xABu,Type_Geom(-1)); }
 
  //--- VS1LineE

  void set_VS1LineE(Type_Geom value) { rw.set(0xADu,value); }
 
  void set_VS1LineE_null() { rw.set(0xADu,Type_Geom(0)); }
 
  void set_VS1LineE_ones() { rw.set(0xADu,Type_Geom(-1)); }
 
  //--- VS1PixE

  void set_VS1PixE(Type_Geom value) { rw.set(0xAFu,value); }
 
  void set_VS1PixE_null() { rw.set(0xAFu,Type_Geom(0)); }
 
  void set_VS1PixE_ones() { rw.set(0xAFu,Type_Geom(-1)); }
 
  //--- VS2LineS

  void set_VS2LineS(Type_Geom value) { rw.set(0xB1u,value); }
 
  void set_VS2LineS_null() { rw.set(0xB1u,Type_Geom(0)); }
 
  void set_VS2LineS_ones() { rw.set(0xB1u,Type_Geom(-1)); }
 
  //--- VS2PixS

  void set_VS2PixS(Type_Geom value) { rw.set(0xB3u,value); }
 
  void set_VS2PixS_null() { rw.set(0xB3u,Type_Geom(0)); }
 
  void set_VS2PixS_ones() { rw.set(0xB3u,Type_Geom(-1)); }
 
  //--- VS2LineE

  void set_VS2LineE(Type_Geom value) { rw.set(0xB5u,value); }
 
  void set_VS2LineE_null() { rw.set(0xB5u,Type_Geom(0)); }
 
  void set_VS2LineE_ones() { rw.set(0xB5u,Type_Geom(-1)); }
 
  //--- VS2PixE

  void set_VS2PixE(Type_Geom value) { rw.set(0xB7u,value); }
 
  void set_VS2PixE_null() { rw.set(0xB7u,Type_Geom(0)); }
 
  void set_VS2PixE_ones() { rw.set(0xB7u,Type_Geom(-1)); }
 
  //--- HSPixS

  void set_HSPixS(Type_Geom value) { rw.set(0xB9u,value); }
 
  void set_HSPixS_null() { rw.set(0xB9u,Type_Geom(0)); }
 
  void set_HSPixS_ones() { rw.set(0xB9u,Type_Geom(-1)); }
 
  //--- HSPixE

  void set_HSPixE(Type_Geom value) { rw.set(0xBBu,value); }
 
  void set_HSPixE_null() { rw.set(0xBBu,Type_Geom(0)); }
 
  void set_HSPixE_ones() { rw.set(0xBBu,Type_Geom(-1)); }
 
  //--- VWin1LineS

  void set_VWin1LineS(Type_Geom value) { rw.set(0xBDu,value); }
 
  void set_VWin1LineS_null() { rw.set(0xBDu,Type_Geom(0)); }
 
  void set_VWin1LineS_ones() { rw.set(0xBDu,Type_Geom(-1)); }
 
  //--- VWin1LineE

  void set_VWin1LineE(Type_Geom value) { rw.set(0xBFu,value); }
 
  void set_VWin1LineE_null() { rw.set(0xBFu,Type_Geom(0)); }
 
  void set_VWin1LineE_ones() { rw.set(0xBFu,Type_Geom(-1)); }
 
  //--- VWin2LineS

  void set_VWin2LineS(Type_Geom value) { rw.set(0xC1u,value); }
 
  void set_VWin2LineS_null() { rw.set(0xC1u,Type_Geom(0)); }
 
  void set_VWin2LineS_ones() { rw.set(0xC1u,Type_Geom(-1)); }
 
  //--- VWin2LineE

  void set_VWin2LineE(Type_Geom value) { rw.set(0xC3u,value); }
 
  void set_VWin2LineE_null() { rw.set(0xC3u,Type_Geom(0)); }
 
  void set_VWin2LineE_ones() { rw.set(0xC3u,Type_Geom(-1)); }
 
  //--- DEPixS

  void set_DEPixS(Type_Geom value) { rw.set(0xC5u,value); }
 
  void set_DEPixS_null() { rw.set(0xC5u,Type_Geom(0)); }
 
  void set_DEPixS_ones() { rw.set(0xC5u,Type_Geom(-1)); }
 
  //--- DEPixE

  void set_DEPixE(Type_Geom value) { rw.set(0xC7u,value); }
 
  void set_DEPixE_null() { rw.set(0xC7u,Type_Geom(0)); }
 
  void set_DEPixE_ones() { rw.set(0xC7u,Type_Geom(-1)); }
 
  //--- TBGControl0

  void set_TBGControl0(Type_TBGControl0 value) { rw.set(0xCAu,value.value); }
 
  Setter<Type_TBGControl0> to_TBGControl0() { return Setter<Type_TBGControl0>(rw,0xCAu); }
 
  static Type_TBGControl0 null_TBGControl0() { return Type_TBGControl0(0); }
 
  static Type_TBGControl0 ones_TBGControl0() { return Type_TBGControl0(Type_TBGControl0::Type(-1)); }
 
  //--- TBGControl1

  void set_TBGControl1(Type_TBGControl1 value) { rw.set(0xCBu,value.value); }
 
  Setter<Type_TBGControl1> to_TBGControl1() { return Setter<Type_TBGControl1>(rw,0xCBu); }
 
  static Type_TBGControl1 null_TBGControl1() { return Type_TBGControl1(0); }
 
  static Type_TBGControl1 ones_TBGControl1() { return Type_TBGControl1(Type_TBGControl1::Type(-1)); }
 
  //--- EnSpace

  void set_EnSpace(Type_EnSpace value) { rw.set(0xD6u,value); }
 
  void set_EnSpace_null() { rw.set(0xD6u,Type_EnSpace(0)); }
 
  void set_EnSpace_ones() { rw.set(0xD6u,Type_EnSpace(-1)); }
 
  //--- HVFControl0

  void set_HVFControl0(Type_HVFControl0 value) { rw.set(0xE4u,value.value); }
 
  Setter<Type_HVFControl0> to_HVFControl0() { return Setter<Type_HVFControl0>(rw,0xE4u); }
 
  static Type_HVFControl0 null_HVFControl0() { return Type_HVFControl0(0); }
 
  static Type_HVFControl0 ones_HVFControl0() { return Type_HVFControl0(Type_HVFControl0::Type(-1)); }
 
  //--- HVFControl1

  void set_HVFControl1(Type_HVFControl1 value) { rw.set(0xE5u,value.value); }
 
  Setter<Type_HVFControl1> to_HVFControl1() { return Setter<Type_HVFControl1>(rw,0xE5u); }
 
  static Type_HVFControl1 null_HVFControl1() { return Type_HVFControl1(0); }
 
  static Type_HVFControl1 ones_HVFControl1() { return Type_HVFControl1(Type_HVFControl1::Type(-1)); }
 
  //--- RepControl

  void set_RepControl(Type_RepControl value) { rw.set(0xF0u,value); }
 
  void set_RepControl_null() { rw.set(0xF0u,Type_RepControl(0)); }
 
  void set_RepControl_ones() { rw.set(0xF0u,Type_RepControl(-1)); }
 
  //--- PLLSerial1

  Type_PLLSerial1 get_PLLSerial1() { return Type_PLLSerial1(rw.template get<uint8>(0x200u)); }
 
  void set_PLLSerial1(Type_PLLSerial1 value) { rw.set(0x200u,value.value); }
 
  Setter<Type_PLLSerial1> to_PLLSerial1() { return Setter<Type_PLLSerial1>(rw,0x200u); }
 
  static Type_PLLSerial1 null_PLLSerial1() { return Type_PLLSerial1(0); }
 
  static Type_PLLSerial1 ones_PLLSerial1() { return Type_PLLSerial1(Type_PLLSerial1::Type(-1)); }
 
  //--- PLLSerial2

  Type_PLLSerial2 get_PLLSerial2() { return Type_PLLSerial2(rw.template get<uint8>(0x201u)); }
 
  void set_PLLSerial2(Type_PLLSerial2 value) { rw.set(0x201u,value.value); }
 
  Setter<Type_PLLSerial2> to_PLLSerial2() { return Setter<Type_PLLSerial2>(rw,0x201u); }
 
  static Type_PLLSerial2 null_PLLSerial2() { return Type_PLLSerial2(0); }
 
  static Type_PLLSerial2 ones_PLLSerial2() { return Type_PLLSerial2(Type_PLLSerial2::Type(-1)); }
 
  //--- PLLSerial3

  Type_PLLSerial3 get_PLLSerial3() { return Type_PLLSerial3(rw.template get<uint8>(0x202u)); }
 
  void set_PLLSerial3(Type_PLLSerial3 value) { rw.set(0x202u,value.value); }
 
  Setter<Type_PLLSerial3> to_PLLSerial3() { return Setter<Type_PLLSerial3>(rw,0x202u); }
 
  static Type_PLLSerial3 null_PLLSerial3() { return Type_PLLSerial3(0); }
 
  static Type_PLLSerial3 ones_PLLSerial3() { return Type_PLLSerial3(Type_PLLSerial3::Type(-1)); }
 
  //--- Serializer

  Type_Serializer get_Serializer() { return Type_Serializer(rw.template get<uint8>(0x203u)); }
 
  void set_Serializer(Type_Serializer value) { rw.set(0x203u,value.value); }
 
  Setter<Type_Serializer> to_Serializer() { return Setter<Type_Serializer>(rw,0x203u); }
 
  static Type_Serializer null_Serializer() { return Type_Serializer(0); }
 
  static Type_Serializer ones_Serializer() { return Type_Serializer(Type_Serializer::Type(-1)); }
 
  //--- BufferOut

  Type_BufferOut get_BufferOut() { return Type_BufferOut(rw.template get<uint8>(0x204u)); }
 
  void set_BufferOut(Type_BufferOut value) { rw.set(0x204u,value.value); }
 
  Setter<Type_BufferOut> to_BufferOut() { return Setter<Type_BufferOut>(rw,0x204u); }
 
  static Type_BufferOut null_BufferOut() { return Type_BufferOut(0); }
 
  static Type_BufferOut ones_BufferOut() { return Type_BufferOut(Type_BufferOut::Type(-1)); }
 
  //--- PLLSCG1

  Type_PLLSCG1 get_PLLSCG1() { return Type_PLLSCG1(rw.template get<uint8>(0x205u)); }
 
  void set_PLLSCG1(Type_PLLSCG1 value) { rw.set(0x205u,value.value); }
 
  Setter<Type_PLLSCG1> to_PLLSCG1() { return Setter<Type_PLLSCG1>(rw,0x205u); }
 
  static Type_PLLSCG1 null_PLLSCG1() { return Type_PLLSCG1(0); }
 
  static Type_PLLSCG1 ones_PLLSCG1() { return Type_PLLSCG1(Type_PLLSCG1::Type(-1)); }
 
  //--- PLLSCG2

  Type_PLLSCG2 get_PLLSCG2() { return Type_PLLSCG2(rw.template get<uint8>(0x206u)); }
 
  void set_PLLSCG2(Type_PLLSCG2 value) { rw.set(0x206u,value.value); }
 
  Setter<Type_PLLSCG2> to_PLLSCG2() { return Setter<Type_PLLSCG2>(rw,0x206u); }
 
  static Type_PLLSCG2 null_PLLSCG2() { return Type_PLLSCG2(0); }
 
  static Type_PLLSCG2 ones_PLLSCG2() { return Type_PLLSCG2(Type_PLLSCG2::Type(-1)); }
 
  //--- PLLSCGN1

  Type_PLLSCGN1 get_PLLSCGN1() { return Type_PLLSCGN1(rw.template get<uint8>(0x207u)); }
 
  void set_PLLSCGN1(Type_PLLSCGN1 value) { rw.set(0x207u,value); }
 
  void set_PLLSCGN1_null() { rw.set(0x207u,Type_PLLSCGN1(0)); }
 
  void set_PLLSCGN1_ones() { rw.set(0x207u,Type_PLLSCGN1(-1)); }
 
  //--- PLLSCGN2

  Type_PLLSCGN2 get_PLLSCGN2() { return Type_PLLSCGN2(rw.template get<uint8>(0x208u)); }
 
  void set_PLLSCGN2(Type_PLLSCGN2 value) { rw.set(0x208u,value); }
 
  void set_PLLSCGN2_null() { rw.set(0x208u,Type_PLLSCGN2(0)); }
 
  void set_PLLSCGN2_ones() { rw.set(0x208u,Type_PLLSCGN2(-1)); }
 
  //--- PLLSCGR1

  Type_PLLSCGR1 get_PLLSCGR1() { return Type_PLLSCGR1(rw.template get<uint8>(0x209u)); }
 
  void set_PLLSCGR1(Type_PLLSCGR1 value) { rw.set(0x209u,value); }
 
  void set_PLLSCGR1_null() { rw.set(0x209u,Type_PLLSCGR1(0)); }
 
  void set_PLLSCGR1_ones() { rw.set(0x209u,Type_PLLSCGR1(-1)); }
 
  //--- PLLSCGR2

  Type_PLLSCGR2 get_PLLSCGR2() { return Type_PLLSCGR2(rw.template get<uint8>(0x20Au)); }
 
  void set_PLLSCGR2(Type_PLLSCGR2 value) { rw.set(0x20Au,value); }
 
  void set_PLLSCGR2_null() { rw.set(0x20Au,Type_PLLSCGR2(0)); }
 
  void set_PLLSCGR2_ones() { rw.set(0x20Au,Type_PLLSCGR2(-1)); }
 
  //--- AudioDiv

  Type_AudioDiv get_AudioDiv() { return Type_AudioDiv(rw.template get<uint8>(0x20Eu)); }
 
  void set_AudioDiv(Type_AudioDiv value) { rw.set(0x20Eu,value.value); }
 
  Setter<Type_AudioDiv> to_AudioDiv() { return Setter<Type_AudioDiv>(rw,0x20Eu); }
 
  static Type_AudioDiv null_AudioDiv() { return Type_AudioDiv(0); }
 
  static Type_AudioDiv ones_AudioDiv() { return Type_AudioDiv(Type_AudioDiv::Type(-1)); }
 
  //--- SelectCLK

  Type_SelectCLK get_SelectCLK() { return Type_SelectCLK(rw.template get<uint8>(0x211u)); }
 
  void set_SelectCLK(Type_SelectCLK value) { rw.set(0x211u,value.value); }
 
  Setter<Type_SelectCLK> to_SelectCLK() { return Setter<Type_SelectCLK>(rw,0x211u); }
 
  static Type_SelectCLK null_SelectCLK() { return Type_SelectCLK(0); }
 
  static Type_SelectCLK ones_SelectCLK() { return Type_SelectCLK(Type_SelectCLK::Type(-1)); }
 
  //--- ANAGeneral

  Type_ANAGeneral get_ANAGeneral() { return Type_ANAGeneral(rw.template get<uint8>(0x212u)); }
 
  void set_ANAGeneral(Type_ANAGeneral value) { rw.set(0x212u,value); }
 
  void set_ANAGeneral_null() { rw.set(0x212u,Type_ANAGeneral(0)); }
 
  void set_ANAGeneral_ones() { rw.set(0x212u,Type_ANAGeneral(-1)); }
 
  //--- EDIDBlock

  Type_EDIDBlock get_EDIDBlock(AddressType ind) { return Type_EDIDBlock(rw.template get<uint8>(0x900u + ind*1u)); }
 
  void set_EDIDBlock(AddressType ind,Type_EDIDBlock value) { rw.set(0x900u + ind*1u,value); }
 
  void set_EDIDBlock_null(AddressType ind) { rw.set(0x900u + ind*1u,Type_EDIDBlock(0)); }
 
  void set_EDIDBlock_ones(AddressType ind) { rw.set(0x900u + ind*1u,Type_EDIDBlock(-1)); }
 
  //--- DDCControl

  Type_DDCControl get_DDCControl() { return Type_DDCControl(rw.template get<uint8>(0x9FAu)); }
 
  void set_DDCControl(Type_DDCControl value) { rw.set(0x9FAu,value.value); }
 
  Setter<Type_DDCControl> to_DDCControl() { return Setter<Type_DDCControl>(rw,0x9FAu); }
 
  static Type_DDCControl null_DDCControl() { return Type_DDCControl(0); }
 
  static Type_DDCControl ones_DDCControl() { return Type_DDCControl(Type_DDCControl::Type(-1)); }
 
  //--- DDCAddress

  Type_DDCAddress get_DDCAddress() { return Type_DDCAddress(rw.template get<uint8>(0x9FBu)); }
 
  void set_DDCAddress(Type_DDCAddress value) { rw.set(0x9FBu,value); }
 
  void set_DDCAddress_null() { rw.set(0x9FBu,Type_DDCAddress(0)); }
 
  void set_DDCAddress_ones() { rw.set(0x9FBu,Type_DDCAddress(-1)); }
 
  //--- DDCOff

  Type_DDCOff get_DDCOff() { return Type_DDCOff(rw.template get<uint8>(0x9FCu)); }
 
  void set_DDCOff(Type_DDCOff value) { rw.set(0x9FCu,value); }
 
  void set_DDCOff_null() { rw.set(0x9FCu,Type_DDCOff(0)); }
 
  void set_DDCOff_ones() { rw.set(0x9FCu,Type_DDCOff(-1)); }
 
  //--- DDCSegAddr

  Type_DDCSegAddr get_DDCSegAddr() { return Type_DDCSegAddr(rw.template get<uint8>(0x9FDu)); }
 
  void set_DDCSegAddr(Type_DDCSegAddr value) { rw.set(0x9FDu,value); }
 
  void set_DDCSegAddr_null() { rw.set(0x9FDu,Type_DDCSegAddr(0)); }
 
  void set_DDCSegAddr_ones() { rw.set(0x9FDu,Type_DDCSegAddr(-1)); }
 
  //--- DDCSeg

  Type_DDCSeg get_DDCSeg() { return Type_DDCSeg(rw.template get<uint8>(0x9FEu)); }
 
  void set_DDCSeg(Type_DDCSeg value) { rw.set(0x9FEu,value); }
 
  void set_DDCSeg_null() { rw.set(0x9FEu,Type_DDCSeg(0)); }
 
  void set_DDCSeg_ones() { rw.set(0x9FEu,Type_DDCSeg(-1)); }
 
  //--- AIPControl0

  Type_AIPControl0 get_AIPControl0() { return Type_AIPControl0(rw.template get<uint8>(0x1100u)); }
 
  void set_AIPControl0(Type_AIPControl0 value) { rw.set(0x1100u,value.value); }
 
  Setter<Type_AIPControl0> to_AIPControl0() { return Setter<Type_AIPControl0>(rw,0x1100u); }
 
  static Type_AIPControl0 null_AIPControl0() { return Type_AIPControl0(0); }
 
  static Type_AIPControl0 ones_AIPControl0() { return Type_AIPControl0(Type_AIPControl0::Type(-1)); }
 
  //--- ENCControl

  Type_ENCControl get_ENCControl() { return Type_ENCControl(rw.template get<uint8>(0x110Du)); }
 
  void set_ENCControl(Type_ENCControl value) { rw.set(0x110Du,value.value); }
 
  Setter<Type_ENCControl> to_ENCControl() { return Setter<Type_ENCControl>(rw,0x110Du); }
 
  static Type_ENCControl null_ENCControl() { return Type_ENCControl(0); }
 
  static Type_ENCControl ones_ENCControl() { return Type_ENCControl(Type_ENCControl::Type(-1)); }
 
  //--- TX3

  Type_TX3 get_TX3() { return Type_TX3(rw.template get<uint8>(0x129Au)); }
 
  void set_TX3(Type_TX3 value) { rw.set(0x129Au,value); }
 
  void set_TX3_null() { rw.set(0x129Au,Type_TX3(0)); }
 
  void set_TX3_ones() { rw.set(0x129Au,Type_TX3(-1)); }
 
  //--- TX4

  Type_TX4 get_TX4() { return Type_TX4(rw.template get<uint8>(0x129Bu)); }
 
  void set_TX4(Type_TX4 value) { rw.set(0x129Bu,value.value); }
 
  Setter<Type_TX4> to_TX4() { return Setter<Type_TX4>(rw,0x129Bu); }
 
  static Type_TX4 null_TX4() { return Type_TX4(0); }
 
  static Type_TX4 ones_TX4() { return Type_TX4(Type_TX4::Type(-1)); }
 
  //--- TX33

  Type_TX33 get_TX33() { return Type_TX33(rw.template get<uint8>(0x12B8u)); }
 
  void set_TX33(Type_TX33 value) { rw.set(0x12B8u,value.value); }
 
  Setter<Type_TX33> to_TX33() { return Setter<Type_TX33>(rw,0x12B8u); }
 
  static Type_TX33 null_TX33() { return Type_TX33(0); }
 
  static Type_TX33 ones_TX33() { return Type_TX33(Type_TX33::Type(-1)); }
 
 };
 
