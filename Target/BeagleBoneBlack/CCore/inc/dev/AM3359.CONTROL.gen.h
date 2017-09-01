/* AM3359.CONTROL.gen.h */

/* struct Type_PadMux */

enum Bits_PadMux : uint32
 {
  PadMux_NoPullUpDown = 0x00000008u,
  PadMux_PullUp       = 0x00000010u,
  PadMux_RXEn         = 0x00000020u,
  PadMux_SlowSlew     = 0x00000040u
 };
 
inline Bits_PadMux operator | (Bits_PadMux a,Bits_PadMux b)
 { return Bits_PadMux(uint32(a)|uint32(b)); }
 
struct Type_PadMux
 {
  using Type = uint32 ;

  Type value;


  explicit Type_PadMux(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PadMux & setTo(Bar &bar) { bar.set_PadMux(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_PadMux & setTo(Bar &bar,AddressType ind) { bar.set_PadMux(ind,*this); return *this; }
 

  template <class T>
  Type_PadMux & set(T to) { to(*this); return *this; }
 

  Type_PadMux & setbit(Bits_PadMux bits) { value|=Type(bits); return *this; }
 
  Type_PadMux & setbitIf(bool cond,Bits_PadMux bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_PadMux & clearbit(Bits_PadMux bits) { value&=~Type(bits); return *this; }
 
  Type_PadMux & clearbitIf(bool cond,Bits_PadMux bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_PadMux bits) const { return value&bits; }
 
  bool testbit(Bits_PadMux bits) const { return (value&bits)==Type(bits); }
 

  Type get_MuxMode() const
   {
    return (value>>0)&0x7u;
   }
 
  Type_PadMux & set_MuxMode(Type field)
   {
    value=((field&0x7u)<<0)|(value&0xFFFFFFF8u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&PadMux_NoPullUpDown )
      {
       if( first )
         {
          Putobj(out,"NoPullUpDown");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NoPullUpDown");
         }
      }

    if( value&PadMux_PullUp )
      {
       if( first )
         {
          Putobj(out,"PullUp");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PullUp");
         }
      }

    if( value&PadMux_RXEn )
      {
       if( first )
         {
          Putobj(out,"RXEn");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RXEn");
         }
      }

    if( value&PadMux_SlowSlew )
      {
       if( first )
         {
          Putobj(out,"SlowSlew");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SlowSlew");
         }
      }

    if( first )
      {
       Printf(out,"MuxMode(#;)",get_MuxMode());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MuxMode(#;)",get_MuxMode());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_EthResetIsolation */

enum Bits_EthResetIsolation : uint32
 {
  EthResetIsolation_Enable = 0x00000001u
 };
 
inline Bits_EthResetIsolation operator | (Bits_EthResetIsolation a,Bits_EthResetIsolation b)
 { return Bits_EthResetIsolation(uint32(a)|uint32(b)); }
 
struct Type_EthResetIsolation
 {
  using Type = uint32 ;

  Type value;


  explicit Type_EthResetIsolation(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_EthResetIsolation & setTo(Bar &bar) { bar.set_EthResetIsolation(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_EthResetIsolation & setTo(Bar &bar,AddressType ind) { bar.set_EthResetIsolation(ind,*this); return *this; }
 

  template <class T>
  Type_EthResetIsolation & set(T to) { to(*this); return *this; }
 

  Type_EthResetIsolation & setbit(Bits_EthResetIsolation bits) { value|=Type(bits); return *this; }
 
  Type_EthResetIsolation & setbitIf(bool cond,Bits_EthResetIsolation bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_EthResetIsolation & clearbit(Bits_EthResetIsolation bits) { value&=~Type(bits); return *this; }
 
  Type_EthResetIsolation & clearbitIf(bool cond,Bits_EthResetIsolation bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_EthResetIsolation bits) const { return value&bits; }
 
  bool testbit(Bits_EthResetIsolation bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&EthResetIsolation_Enable )
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
 
/* struct Type_GMIISelect */

enum Bits_GMIISelect : uint32
 {
  GMIISelect_Port1RMIIClockInput = 0x00000040u,
  GMIISelect_Port2RMIIClockInput = 0x00000080u
 };
 
inline Bits_GMIISelect operator | (Bits_GMIISelect a,Bits_GMIISelect b)
 { return Bits_GMIISelect(uint32(a)|uint32(b)); }
 
enum Field_GMIISelect_Port1 : uint32
 {
  GMIISelect_Port1_GMII  = 0x00u,
  GMIISelect_Port1_RMII  = 0x01u,
  GMIISelect_Port1_RGMII = 0x02u
 };
 
struct PrintField_GMIISelect_Port1
 {
  Field_GMIISelect_Port1 field;

  explicit PrintField_GMIISelect_Port1(Field_GMIISelect_Port1 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"GMII"); break;
       case 0x01u : Putobj(out,"RMII"); break;
       case 0x02u : Putobj(out,"RGMII"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_GMIISelect_Port1 GetTextDesc(Field_GMIISelect_Port1 field)
 {
  return PrintField_GMIISelect_Port1(field);
 }
 
enum Field_GMIISelect_Port2 : uint32
 {
  GMIISelect_Port2_GMII  = 0x00u,
  GMIISelect_Port2_RMII  = 0x01u,
  GMIISelect_Port2_RGMII = 0x02u
 };
 
struct PrintField_GMIISelect_Port2
 {
  Field_GMIISelect_Port2 field;

  explicit PrintField_GMIISelect_Port2(Field_GMIISelect_Port2 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00u : Putobj(out,"GMII"); break;
       case 0x01u : Putobj(out,"RMII"); break;
       case 0x02u : Putobj(out,"RGMII"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_GMIISelect_Port2 GetTextDesc(Field_GMIISelect_Port2 field)
 {
  return PrintField_GMIISelect_Port2(field);
 }
 
struct Type_GMIISelect
 {
  using Type = uint32 ;

  Type value;


  explicit Type_GMIISelect(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_GMIISelect & setTo(Bar &bar) { bar.set_GMIISelect(*this); return *this; }
 

  template <class Bar,class AddressType>
  Type_GMIISelect & setTo(Bar &bar,AddressType ind) { bar.set_GMIISelect(ind,*this); return *this; }
 

  template <class T>
  Type_GMIISelect & set(T to) { to(*this); return *this; }
 

  Type_GMIISelect & setbit(Bits_GMIISelect bits) { value|=Type(bits); return *this; }
 
  Type_GMIISelect & setbitIf(bool cond,Bits_GMIISelect bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_GMIISelect & clearbit(Bits_GMIISelect bits) { value&=~Type(bits); return *this; }
 
  Type_GMIISelect & clearbitIf(bool cond,Bits_GMIISelect bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_GMIISelect bits) const { return value&bits; }
 
  bool testbit(Bits_GMIISelect bits) const { return (value&bits)==Type(bits); }
 

  Field_GMIISelect_Port1 get_Port1() const
   {
    return Field_GMIISelect_Port1((value>>0)&0x3u);
   }
 
  Type_GMIISelect & set_Port1(Field_GMIISelect_Port1 field)
   {
    value=((Type(field)&0x3u)<<0)|(value&0xFFFFFFFCu);

    return *this;
   }
 

  Field_GMIISelect_Port2 get_Port2() const
   {
    return Field_GMIISelect_Port2((value>>2)&0x3u);
   }
 
  Type_GMIISelect & set_Port2(Field_GMIISelect_Port2 field)
   {
    value=((Type(field)&0x3u)<<2)|(value&0xFFFFFFF3u);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&GMIISelect_Port1RMIIClockInput )
      {
       if( first )
         {
          Putobj(out,"Port1RMIIClockInput");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port1RMIIClockInput");
         }
      }

    if( value&GMIISelect_Port2RMIIClockInput )
      {
       if( first )
         {
          Putobj(out,"Port2RMIIClockInput");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port2RMIIClockInput");
         }
      }

    if( first )
      {
       Printf(out,"Port1(#;)",get_Port1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Port1(#;)",get_Port1());
      }

    if( first )
      {
       Printf(out,"Port2(#;)",get_Port2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Port2(#;)",get_Port2());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_MAC0Hi */

using Type_MAC0Hi = uint32 ;

/* type Type_MAC0Lo */

using Type_MAC0Lo = uint32 ;

/* type Type_MAC1Hi */

using Type_MAC1Hi = uint32 ;

/* type Type_MAC1Lo */

using Type_MAC1Lo = uint32 ;

/* struct CONTROLBar<RW> */

template <class RW>
struct CONTROLBar
 {
  RW rw;

  using AddressType = typename RW::AddressType ;

  template <class ... TT>
  explicit CONTROLBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    AddressType address;

    Setter(RW &rw_,AddressType address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- EthResetIsolation

  Type_EthResetIsolation get_EthResetIsolation() { return Type_EthResetIsolation(rw.template get<uint32>(0x1000u)); }
 
  void set_EthResetIsolation(Type_EthResetIsolation value) { rw.set(0x1000u,value.value); }
 
  Setter<Type_EthResetIsolation> to_EthResetIsolation() { return Setter<Type_EthResetIsolation>(rw,0x1000u); }
 
  static Type_EthResetIsolation null_EthResetIsolation() { return Type_EthResetIsolation(0); }
 
  static Type_EthResetIsolation ones_EthResetIsolation() { return Type_EthResetIsolation(Type_EthResetIsolation::Type(-1)); }
 
  //--- GMIISelect

  Type_GMIISelect get_GMIISelect() { return Type_GMIISelect(rw.template get<uint32>(0x650u)); }
 
  void set_GMIISelect(Type_GMIISelect value) { rw.set(0x650u,value.value); }
 
  Setter<Type_GMIISelect> to_GMIISelect() { return Setter<Type_GMIISelect>(rw,0x650u); }
 
  static Type_GMIISelect null_GMIISelect() { return Type_GMIISelect(0); }
 
  static Type_GMIISelect ones_GMIISelect() { return Type_GMIISelect(Type_GMIISelect::Type(-1)); }
 
  //--- MAC0Hi

  Type_MAC0Hi get_MAC0Hi() { return Type_MAC0Hi(rw.template get<uint32>(0x630u)); }
 
  //--- MAC0Lo

  Type_MAC0Lo get_MAC0Lo() { return Type_MAC0Lo(rw.template get<uint32>(0x634u)); }
 
  //--- MAC1Hi

  Type_MAC1Hi get_MAC1Hi() { return Type_MAC1Hi(rw.template get<uint32>(0x638u)); }
 
  //--- MAC1Lo

  Type_MAC1Lo get_MAC1Lo() { return Type_MAC1Lo(rw.template get<uint32>(0x63Cu)); }
 
  //--- PadMux

  static Type_PadMux null_PadMux() { return Type_PadMux(0); }
 
  static Type_PadMux ones_PadMux() { return Type_PadMux(Type_PadMux::Type(-1)); }
 
  //--- Conf_I2C0_SDA

  Type_PadMux get_Conf_I2C0_SDA() { return Type_PadMux(rw.template get<uint32>(0x988u)); }
 
  void set_Conf_I2C0_SDA(Type_PadMux value) { rw.set(0x988u,value.value); }
 
  Setter<Type_PadMux> to_Conf_I2C0_SDA() { return Setter<Type_PadMux>(rw,0x988u); }
 
  //--- Conf_I2C0_SCL

  Type_PadMux get_Conf_I2C0_SCL() { return Type_PadMux(rw.template get<uint32>(0x98Cu)); }
 
  void set_Conf_I2C0_SCL(Type_PadMux value) { rw.set(0x98Cu,value.value); }
 
  Setter<Type_PadMux> to_Conf_I2C0_SCL() { return Setter<Type_PadMux>(rw,0x98Cu); }
 
  //--- Conf_LCD_DATA0

  Type_PadMux get_Conf_LCD_DATA0() { return Type_PadMux(rw.template get<uint32>(0x8A0u)); }
 
  void set_Conf_LCD_DATA0(Type_PadMux value) { rw.set(0x8A0u,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA0() { return Setter<Type_PadMux>(rw,0x8A0u); }
 
  //--- Conf_LCD_DATA1

  Type_PadMux get_Conf_LCD_DATA1() { return Type_PadMux(rw.template get<uint32>(0x8A4u)); }
 
  void set_Conf_LCD_DATA1(Type_PadMux value) { rw.set(0x8A4u,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA1() { return Setter<Type_PadMux>(rw,0x8A4u); }
 
  //--- Conf_LCD_DATA2

  Type_PadMux get_Conf_LCD_DATA2() { return Type_PadMux(rw.template get<uint32>(0x8A8u)); }
 
  void set_Conf_LCD_DATA2(Type_PadMux value) { rw.set(0x8A8u,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA2() { return Setter<Type_PadMux>(rw,0x8A8u); }
 
  //--- Conf_LCD_DATA3

  Type_PadMux get_Conf_LCD_DATA3() { return Type_PadMux(rw.template get<uint32>(0x8ACu)); }
 
  void set_Conf_LCD_DATA3(Type_PadMux value) { rw.set(0x8ACu,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA3() { return Setter<Type_PadMux>(rw,0x8ACu); }
 
  //--- Conf_LCD_DATA4

  Type_PadMux get_Conf_LCD_DATA4() { return Type_PadMux(rw.template get<uint32>(0x8B0u)); }
 
  void set_Conf_LCD_DATA4(Type_PadMux value) { rw.set(0x8B0u,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA4() { return Setter<Type_PadMux>(rw,0x8B0u); }
 
  //--- Conf_LCD_DATA5

  Type_PadMux get_Conf_LCD_DATA5() { return Type_PadMux(rw.template get<uint32>(0x8B4u)); }
 
  void set_Conf_LCD_DATA5(Type_PadMux value) { rw.set(0x8B4u,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA5() { return Setter<Type_PadMux>(rw,0x8B4u); }
 
  //--- Conf_LCD_DATA6

  Type_PadMux get_Conf_LCD_DATA6() { return Type_PadMux(rw.template get<uint32>(0x8B8u)); }
 
  void set_Conf_LCD_DATA6(Type_PadMux value) { rw.set(0x8B8u,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA6() { return Setter<Type_PadMux>(rw,0x8B8u); }
 
  //--- Conf_LCD_DATA7

  Type_PadMux get_Conf_LCD_DATA7() { return Type_PadMux(rw.template get<uint32>(0x8BCu)); }
 
  void set_Conf_LCD_DATA7(Type_PadMux value) { rw.set(0x8BCu,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA7() { return Setter<Type_PadMux>(rw,0x8BCu); }
 
  //--- Conf_LCD_DATA8

  Type_PadMux get_Conf_LCD_DATA8() { return Type_PadMux(rw.template get<uint32>(0x8C0u)); }
 
  void set_Conf_LCD_DATA8(Type_PadMux value) { rw.set(0x8C0u,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA8() { return Setter<Type_PadMux>(rw,0x8C0u); }
 
  //--- Conf_LCD_DATA9

  Type_PadMux get_Conf_LCD_DATA9() { return Type_PadMux(rw.template get<uint32>(0x8C4u)); }
 
  void set_Conf_LCD_DATA9(Type_PadMux value) { rw.set(0x8C4u,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA9() { return Setter<Type_PadMux>(rw,0x8C4u); }
 
  //--- Conf_LCD_DATA10

  Type_PadMux get_Conf_LCD_DATA10() { return Type_PadMux(rw.template get<uint32>(0x8C8u)); }
 
  void set_Conf_LCD_DATA10(Type_PadMux value) { rw.set(0x8C8u,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA10() { return Setter<Type_PadMux>(rw,0x8C8u); }
 
  //--- Conf_LCD_DATA11

  Type_PadMux get_Conf_LCD_DATA11() { return Type_PadMux(rw.template get<uint32>(0x8CCu)); }
 
  void set_Conf_LCD_DATA11(Type_PadMux value) { rw.set(0x8CCu,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA11() { return Setter<Type_PadMux>(rw,0x8CCu); }
 
  //--- Conf_LCD_DATA12

  Type_PadMux get_Conf_LCD_DATA12() { return Type_PadMux(rw.template get<uint32>(0x8D0u)); }
 
  void set_Conf_LCD_DATA12(Type_PadMux value) { rw.set(0x8D0u,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA12() { return Setter<Type_PadMux>(rw,0x8D0u); }
 
  //--- Conf_LCD_DATA13

  Type_PadMux get_Conf_LCD_DATA13() { return Type_PadMux(rw.template get<uint32>(0x8D4u)); }
 
  void set_Conf_LCD_DATA13(Type_PadMux value) { rw.set(0x8D4u,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA13() { return Setter<Type_PadMux>(rw,0x8D4u); }
 
  //--- Conf_LCD_DATA14

  Type_PadMux get_Conf_LCD_DATA14() { return Type_PadMux(rw.template get<uint32>(0x8D8u)); }
 
  void set_Conf_LCD_DATA14(Type_PadMux value) { rw.set(0x8D8u,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA14() { return Setter<Type_PadMux>(rw,0x8D8u); }
 
  //--- Conf_LCD_DATA15

  Type_PadMux get_Conf_LCD_DATA15() { return Type_PadMux(rw.template get<uint32>(0x8DCu)); }
 
  void set_Conf_LCD_DATA15(Type_PadMux value) { rw.set(0x8DCu,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA15() { return Setter<Type_PadMux>(rw,0x8DCu); }
 
  //--- Conf_LCD_VSYNC

  Type_PadMux get_Conf_LCD_VSYNC() { return Type_PadMux(rw.template get<uint32>(0x8E0u)); }
 
  void set_Conf_LCD_VSYNC(Type_PadMux value) { rw.set(0x8E0u,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_VSYNC() { return Setter<Type_PadMux>(rw,0x8E0u); }
 
  //--- Conf_LCD_HSYNC

  Type_PadMux get_Conf_LCD_HSYNC() { return Type_PadMux(rw.template get<uint32>(0x8E4u)); }
 
  void set_Conf_LCD_HSYNC(Type_PadMux value) { rw.set(0x8E4u,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_HSYNC() { return Setter<Type_PadMux>(rw,0x8E4u); }
 
  //--- Conf_LCD_PCLK

  Type_PadMux get_Conf_LCD_PCLK() { return Type_PadMux(rw.template get<uint32>(0x8E8u)); }
 
  void set_Conf_LCD_PCLK(Type_PadMux value) { rw.set(0x8E8u,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_PCLK() { return Setter<Type_PadMux>(rw,0x8E8u); }
 
  //--- Conf_LCD_AC_BIAS_EN

  Type_PadMux get_Conf_LCD_AC_BIAS_EN() { return Type_PadMux(rw.template get<uint32>(0x8ECu)); }
 
  void set_Conf_LCD_AC_BIAS_EN(Type_PadMux value) { rw.set(0x8ECu,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_AC_BIAS_EN() { return Setter<Type_PadMux>(rw,0x8ECu); }
 
  //--- Conf_GPMC_A9

  Type_PadMux get_Conf_GPMC_A9() { return Type_PadMux(rw.template get<uint32>(0x864u)); }
 
  void set_Conf_GPMC_A9(Type_PadMux value) { rw.set(0x864u,value.value); }
 
  Setter<Type_PadMux> to_Conf_GPMC_A9() { return Setter<Type_PadMux>(rw,0x864u); }
 
  //--- Conf_MII1_COL

  Type_PadMux get_Conf_MII1_COL() { return Type_PadMux(rw.template get<uint32>(0x908u)); }
 
  void set_Conf_MII1_COL(Type_PadMux value) { rw.set(0x908u,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_COL() { return Setter<Type_PadMux>(rw,0x908u); }
 
  //--- Conf_MII1_CRS

  Type_PadMux get_Conf_MII1_CRS() { return Type_PadMux(rw.template get<uint32>(0x90Cu)); }
 
  void set_Conf_MII1_CRS(Type_PadMux value) { rw.set(0x90Cu,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_CRS() { return Setter<Type_PadMux>(rw,0x90Cu); }
 
  //--- Conf_MII1_RX_ER

  Type_PadMux get_Conf_MII1_RX_ER() { return Type_PadMux(rw.template get<uint32>(0x910u)); }
 
  void set_Conf_MII1_RX_ER(Type_PadMux value) { rw.set(0x910u,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_RX_ER() { return Setter<Type_PadMux>(rw,0x910u); }
 
  //--- Conf_MII1_TX_EN

  Type_PadMux get_Conf_MII1_TX_EN() { return Type_PadMux(rw.template get<uint32>(0x914u)); }
 
  void set_Conf_MII1_TX_EN(Type_PadMux value) { rw.set(0x914u,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_TX_EN() { return Setter<Type_PadMux>(rw,0x914u); }
 
  //--- Conf_MII1_RX_DV

  Type_PadMux get_Conf_MII1_RX_DV() { return Type_PadMux(rw.template get<uint32>(0x918u)); }
 
  void set_Conf_MII1_RX_DV(Type_PadMux value) { rw.set(0x918u,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_RX_DV() { return Setter<Type_PadMux>(rw,0x918u); }
 
  //--- Conf_MII1_TXD3

  Type_PadMux get_Conf_MII1_TXD3() { return Type_PadMux(rw.template get<uint32>(0x91Cu)); }
 
  void set_Conf_MII1_TXD3(Type_PadMux value) { rw.set(0x91Cu,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_TXD3() { return Setter<Type_PadMux>(rw,0x91Cu); }
 
  //--- Conf_MII1_TXD2

  Type_PadMux get_Conf_MII1_TXD2() { return Type_PadMux(rw.template get<uint32>(0x920u)); }
 
  void set_Conf_MII1_TXD2(Type_PadMux value) { rw.set(0x920u,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_TXD2() { return Setter<Type_PadMux>(rw,0x920u); }
 
  //--- Conf_MII1_TXD1

  Type_PadMux get_Conf_MII1_TXD1() { return Type_PadMux(rw.template get<uint32>(0x924u)); }
 
  void set_Conf_MII1_TXD1(Type_PadMux value) { rw.set(0x924u,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_TXD1() { return Setter<Type_PadMux>(rw,0x924u); }
 
  //--- Conf_MII1_TXD0

  Type_PadMux get_Conf_MII1_TXD0() { return Type_PadMux(rw.template get<uint32>(0x928u)); }
 
  void set_Conf_MII1_TXD0(Type_PadMux value) { rw.set(0x928u,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_TXD0() { return Setter<Type_PadMux>(rw,0x928u); }
 
  //--- Conf_MII1_TX_CLK

  Type_PadMux get_Conf_MII1_TX_CLK() { return Type_PadMux(rw.template get<uint32>(0x92Cu)); }
 
  void set_Conf_MII1_TX_CLK(Type_PadMux value) { rw.set(0x92Cu,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_TX_CLK() { return Setter<Type_PadMux>(rw,0x92Cu); }
 
  //--- Conf_MII1_RX_CLK

  Type_PadMux get_Conf_MII1_RX_CLK() { return Type_PadMux(rw.template get<uint32>(0x930u)); }
 
  void set_Conf_MII1_RX_CLK(Type_PadMux value) { rw.set(0x930u,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_RX_CLK() { return Setter<Type_PadMux>(rw,0x930u); }
 
  //--- Conf_MII1_RXD3

  Type_PadMux get_Conf_MII1_RXD3() { return Type_PadMux(rw.template get<uint32>(0x934u)); }
 
  void set_Conf_MII1_RXD3(Type_PadMux value) { rw.set(0x934u,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_RXD3() { return Setter<Type_PadMux>(rw,0x934u); }
 
  //--- Conf_MII1_RXD2

  Type_PadMux get_Conf_MII1_RXD2() { return Type_PadMux(rw.template get<uint32>(0x938u)); }
 
  void set_Conf_MII1_RXD2(Type_PadMux value) { rw.set(0x938u,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_RXD2() { return Setter<Type_PadMux>(rw,0x938u); }
 
  //--- Conf_MII1_RXD1

  Type_PadMux get_Conf_MII1_RXD1() { return Type_PadMux(rw.template get<uint32>(0x93Cu)); }
 
  void set_Conf_MII1_RXD1(Type_PadMux value) { rw.set(0x93Cu,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_RXD1() { return Setter<Type_PadMux>(rw,0x93Cu); }
 
  //--- Conf_MII1_RXD0

  Type_PadMux get_Conf_MII1_RXD0() { return Type_PadMux(rw.template get<uint32>(0x940u)); }
 
  void set_Conf_MII1_RXD0(Type_PadMux value) { rw.set(0x940u,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_RXD0() { return Setter<Type_PadMux>(rw,0x940u); }
 
  //--- Conf_RMII1_REF_CLK

  Type_PadMux get_Conf_RMII1_REF_CLK() { return Type_PadMux(rw.template get<uint32>(0x944u)); }
 
  void set_Conf_RMII1_REF_CLK(Type_PadMux value) { rw.set(0x944u,value.value); }
 
  Setter<Type_PadMux> to_Conf_RMII1_REF_CLK() { return Setter<Type_PadMux>(rw,0x944u); }
 
  //--- Conf_MDIO

  Type_PadMux get_Conf_MDIO() { return Type_PadMux(rw.template get<uint32>(0x948u)); }
 
  void set_Conf_MDIO(Type_PadMux value) { rw.set(0x948u,value.value); }
 
  Setter<Type_PadMux> to_Conf_MDIO() { return Setter<Type_PadMux>(rw,0x948u); }
 
  //--- Conf_MDC

  Type_PadMux get_Conf_MDC() { return Type_PadMux(rw.template get<uint32>(0x94Cu)); }
 
  void set_Conf_MDC(Type_PadMux value) { rw.set(0x94Cu,value.value); }
 
  Setter<Type_PadMux> to_Conf_MDC() { return Setter<Type_PadMux>(rw,0x94Cu); }
 
 };
 
