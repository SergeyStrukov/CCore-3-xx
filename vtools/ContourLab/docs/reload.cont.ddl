//#include <Contour.ddl>

Contour Data=
 {
  {
   { { 'O' , True , True , True } , 0 , &Pad0 },
   { { 'radius1' , True , True , True } , 1 , &Pad1 },
   { { 'radius2' , True , True , True } , 2 , &Pad2 }
  },
  {
  { { 'cir1' , True , True , False } , 0 , &F0 },
  { { 'cir2' , True , True , False } , 1 , &F1 },
  { { 'A' , True , True , False } , 2 , &F2 },
  { { 'B' , True , True , False } , 3 , &F3 },
  { { 'C' , True , True , False } , 4 , &F4 },
  { { 'D' , True , True , False } , 5 , &F5 },
  { { 'alpha' , True , True , True } , 6 , &F6 },
  { { 'A1' , True , True , False } , 7 , &F7 },
  { { 'A2' , True , True , False } , 8 , &F8 },
  { { 'A3' , True , True , False } , 9 , &F9 },
  { { 'A4' , True , True , False } , 10 , &F10 },
  { { 'A5' , True , True , False } , 11 , &F11 },
  { { 'A6' , True , True , False } , 12 , &F12 },
  { { 'A7' , True , True , False } , 13 , &F13 },
  { { 'A8' , True , True , False } , 14 , &F14 },
  { { 'A9' , True , True , False } , 15 , &F15 },
  { { 'A10' , True , True , False } , 16 , &F16 },
  { { 'A11' , True , True , False } , 17 , &F17 },
  { { 'A12' , True , True , False } , 18 , &F18 },
  { { 'A13' , True , True , False } , 19 , &F19 },
  { { 'A14' , True , True , False } , 20 , &F20 },
  { { 'A15' , True , True , False } , 21 , &F21 },
  { { 'step1' , True , True , True } , 22 , &F22 },
  { { 'test' , True , True , True } , 23 , &F23 }
  }
 };

Point Pad0 = { {5B40000000000000h,-54} , {4F80000000000000h,-54} , 0 };

Length Pad1 = { {6400000000000000h,-56} , 0 };

Length Pad2 = { {4600000000000000h,-55} , 0 };

CircleOf F0 = { Data.pads+0 , Data.pads+1 };

CircleOf F1 = { Data.pads+0 , Data.pads+2 };

Right F2 = { Data.pads+1 , Data.pads+0 };

Right F3 = { Data.pads+2 , Data.pads+0 };

Up F4 = { Data.pads+1 , Data.pads+0 };

Up F5 = { Data.pads+2 , Data.pads+0 };

Angle F6 = { {4B65F1FCCC874800h,-64} , 0 };

Rotate F7 = { Data.pads+0 , &F37 , Data.formulas+2 };

Mul F37 = { &F39 , Data.formulas+6 };

Neg F39 = { &F41 };

Ratio F41 = { {4000000000000000h,-62} , 0 };

Rotate F8 = { Data.pads+0 , &F43 , Data.formulas+2 };

Mul F43 = { &F45 , Data.formulas+6 };

Neg F45 = { &F47 };

Ratio F47 = { {4000000000000000h,-61} , 0 };

Rotate F9 = { Data.pads+0 , &F49 , Data.formulas+2 };

Mul F49 = { &F51 , Data.formulas+6 };

Neg F51 = { &F53 };

Ratio F53 = { {6000000000000000h,-61} , 0 };

Rotate F10 = { Data.pads+0 , &F55 , Data.formulas+2 };

Mul F55 = { &F57 , Data.formulas+6 };

Neg F57 = { &F59 };

Ratio F59 = { {4000000000000000h,-60} , 0 };

Rotate F11 = { Data.pads+0 , &F61 , Data.formulas+2 };

Mul F61 = { &F63 , Data.formulas+6 };

Neg F63 = { &F65 };

Ratio F65 = { {5000000000000000h,-60} , 0 };

Rotate F12 = { Data.pads+0 , &F67 , Data.formulas+2 };

Mul F67 = { &F69 , Data.formulas+6 };

Neg F69 = { &F71 };

Ratio F71 = { {6000000000000000h,-60} , 0 };

Rotate F13 = { Data.pads+0 , &F73 , Data.formulas+2 };

Mul F73 = { &F75 , Data.formulas+6 };

Neg F75 = { &F77 };

Ratio F77 = { {7000000000000000h,-60} , 0 };

Rotate F14 = { Data.pads+0 , &F79 , Data.formulas+2 };

Mul F79 = { &F81 , Data.formulas+6 };

Neg F81 = { &F83 };

Ratio F83 = { {4000000000000000h,-59} , 0 };

Rotate F15 = { Data.pads+0 , &F85 , Data.formulas+2 };

Mul F85 = { &F87 , Data.formulas+6 };

Neg F87 = { &F89 };

Ratio F89 = { {4800000000000000h,-59} , 0 };

Rotate F16 = { Data.pads+0 , &F91 , Data.formulas+2 };

Mul F91 = { &F93 , Data.formulas+6 };

Neg F93 = { &F95 };

Ratio F95 = { {5000000000000000h,-59} , 0 };

Rotate F17 = { Data.pads+0 , &F97 , Data.formulas+2 };

Mul F97 = { &F99 , Data.formulas+6 };

Neg F99 = { &F101 };

Ratio F101 = { {5800000000000000h,-59} , 0 };

Rotate F18 = { Data.pads+0 , &F103 , Data.formulas+2 };

Mul F103 = { &F105 , Data.formulas+6 };

Neg F105 = { &F107 };

Ratio F107 = { {6000000000000000h,-59} , 0 };

Rotate F19 = { Data.pads+0 , &F109 , Data.formulas+2 };

Mul F109 = { &F111 , Data.formulas+6 };

Neg F111 = { &F113 };

Ratio F113 = { {6800000000000000h,-59} , 0 };

Rotate F20 = { Data.pads+0 , &F115 , Data.formulas+2 };

Mul F115 = { &F117 , Data.formulas+6 };

Neg F117 = { &F119 };

Ratio F119 = { {7000000000000000h,-59} , 0 };

Rotate F21 = { Data.pads+0 , &F121 , Data.formulas+2 };

Mul F121 = { &F123 , Data.formulas+6 };

Neg F123 = { &F125 };

Ratio F125 = { {7800000000000000h,-59} , 0 };

StepOf F22 = { { Data.formulas+2 , Data.formulas+7 , Data.formulas+8 , Data.formulas+9 , Data.formulas+10 , Data.formulas+11 , Data.formulas+12 , Data.formulas+13 , Data.formulas+14 , Data.formulas+15 , Data.formulas+16 , Data.formulas+17 , Data.formulas+18 , Data.formulas+19 , Data.formulas+20 , Data.formulas+21 , Data.formulas+4 } };

BPathOf F23 = { { Data.formulas+22 } };

Path Contour_test=
 {
  {
   { { {7440000000000000h,-54} , {4F80000000000000h,-54} , 0 } , True },
   { { {732C6B0BCAD3D000h,-54} , {56C1D26A4B722000h,-54} , 0 } , False },
   { { {700967D0136E4800h,-54} , {5D63A6451041DC00h,-54} , 0 } , False },
   { { {6B1C1DF4EF1F5000h,-54} , {62D34453A87A2800h,-54} , 0 } , False },
   { { {64D12C891C3A2C00h,-54} , {6698D439DF7E6000h,-54} , 0 } , False },
   { { {5DB34F4860129800h,-54} , {68612EA7FB650400h,-54} , 0 } , False },
   { { {565F6C04335D9400h,-54} , {6805069A79406800h,-54} , 0 } , False },
   { { {4F770F961D47D000h,-54} , {658C4BCCAC943000h,-54} , 0 } , False },
   { { {4992843FEC994800h,-54} , {612D7BC01366B800h,-54} , 0 } , False },
   { { {4533B433536BD000h,-54} , {5B48F069E2B83000h,-54} , 0 } , False },
   { { {42BAF96586BF9800h,-54} , {546093FBCCA27000h,-54} , 0 } , False },
   { { {425ED158049AFC00h,-54} , {4D0CB0B79FED6800h,-54} , 0 } , False },
   { { {44272BC62081A000h,-54} , {45EED376E3C5D400h,-54} , 0 } , False },
   { { {47ECBBAC5785D400h,-54} , {7F47C41621C16000h,-55} , 0 } , False },
   { { {4D5C59BAEFBE2400h,-54} , {756D305FD9237000h,-55} , 0 } , False },
   { { {53FE2D95B48DE400h,-54} , {6F2729E86A585800h,-55} , 0 } , False },
   { { {5B40000000000000h,-54} , {6D00000000000000h,-55} , 0 } , False }
  },
  0
 };

/*

SmoothDot Contour_test[]=
 {
  { { 476160 , 325632 } , Smooth::DotBreak },
  { { 471751 , 355357 } , Smooth::DotSimple },
  { { 458902 , 382522 } , Smooth::DotSimple },
  { { 438722 , 404788 } , Smooth::DotSimple },
  { { 412947 , 420237 } , Smooth::DotSimple },
  { { 383797 , 427539 } , Smooth::DotSimple },
  { { 353783 , 426064 } , Smooth::DotSimple },
  { { 325489 , 415941 } , Smooth::DotSimple },
  { { 301352 , 398040 } , Smooth::DotSimple },
  { { 283451 , 373903 } , Smooth::DotSimple },
  { { 273328 , 345609 } , Smooth::DotSimple },
  { { 271853 , 315595 } , Smooth::DotSimple },
  { { 279155 , 286445 } , Smooth::DotSimple },
  { { 294604 , 260670 } , Smooth::DotSimple },
  { { 316870 , 240490 } , Smooth::DotSimple },
  { { 344035 , 227641 } , Smooth::DotSimple },
  { { 373760 , 223232 } , Smooth::DotSimple }
 };

*/

