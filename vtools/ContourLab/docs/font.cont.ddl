//#include <Contour.ddl>

Contour Data=
 {
  {
   { { 'A' , True , True , True } , 0 , &Pad0 },
   { { 'B' , True , True , True } , 1 , &Pad1 },
   { { 'len1' , True , True , True } , 2 , &Pad2 },
   { { 'mid' , True , True , True } , 3 , &Pad3 },
   { { 'short' , True , True , True } , 4 , &Pad4 },
   { { 'extx' , True , True , True } , 5 , &Pad5 },
   { { 'exty' , True , True , True } , 6 , &Pad6 }
  },
  {
  { { 'C' , True , True , True } , 0 , &F0 },
  { { 'D' , True , True , True } , 1 , &F1 },
  { { 'E' , True , True , True } , 2 , &F2 },
  { { 'lenx' , True , True , True } , 3 , &F3 },
  { { 'leny' , True , True , True } , 4 , &F4 },
  { { 'l1' , True , True , False } , 5 , &F5 },
  { { 'l2' , True , True , False } , 6 , &F6 },
  { { 'l3' , True , True , False } , 7 , &F7 },
  { { 'l4' , True , True , False } , 8 , &F8 },
  { { 'h1' , True , True , False } , 9 , &F9 },
  { { 'h2' , True , True , False } , 10 , &F10 },
  { { 'h3' , True , True , False } , 11 , &F11 },
  { { 'h4' , True , True , False } , 12 , &F12 },
  { { 'h5' , True , True , False } , 13 , &F13 },
  { { 'S' , True , True , True } , 14 , &F14 },
  { { 'B0_5' , True , True , True } , 15 , &F15 },
  { { 'B1' , True , True , False } , 16 , &F16 },
  { { 'B1_5' , True , True , False } , 17 , &F17 },
  { { 'B2' , True , True , False } , 18 , &F18 },
  { { 'B3' , True , True , False } , 19 , &F19 },
  { { 'B4' , True , True , False } , 20 , &F20 },
  { { 'B4_5' , True , True , False } , 21 , &F21 },
  { { 'B5' , True , True , False } , 22 , &F22 },
  { { 'B5_5' , True , True , True } , 23 , &F23 },
  { { 'test' , True , True , False } , 24 , &F24 },
  { { 'T' , True , True , True } , 25 , &F25 }
  }
 };

Point Pad0 = { {7380000000000000h,-55} , {41C0000000000000h,-53} , 0 };

Point Pad1 = { {7B00000000000000h,-55} , {4800000000000000h,-55} , 0 };

Length Pad2 = { {44C0000000000000h,-54} , 0 };

Ratio Pad3 = { {4CCCCCCCCCCCCC00h,-63} , 0 };

Ratio Pad4 = { {5999999999999800h,-63} , 0 };

Ratio Pad5 = { {6666666666666800h,-66} , 0 };

Ratio Pad6 = { {6666666666666800h,-66} , 0 };

Right F0 = { Data.pads+2 , Data.pads+1 };

Part F1 = { Data.pads+0 , Data.pads+1 , Data.pads+3 };

Right F2 = { &F31 , Data.formulas+1 };

Mul F31 = { Data.pads+4 , Data.pads+2 };

Mul F3 = { Data.pads+5 , Data.pads+2 };

Mul F4 = { Data.pads+6 , Data.pads+2 };

LineOf F5 = { &F39 , &F40 };

Left F39 = { Data.formulas+3 , Data.pads+0 };

Left F40 = { Data.formulas+3 , Data.pads+1 };

LineOf F6 = { &F45 , &F46 };

Right F45 = { Data.formulas+3 , Data.pads+0 };

Right F46 = { Data.formulas+3 , Data.pads+1 };

LineOf F7 = { Data.formulas+0 , &F52 };

Move F52 = { Data.pads+1 , Data.pads+0 , Data.formulas+0 };

LineOf F8 = { Data.formulas+2 , &F57 };

Move F57 = { Data.pads+1 , Data.pads+0 , Data.formulas+2 };

LineOf F9 = { &F61 , &F62 };

Up F61 = { Data.formulas+4 , Data.pads+1 };

Up F62 = { Data.formulas+4 , Data.formulas+0 };

LineOf F10 = { &F67 , &F68 };

Down F67 = { Data.formulas+4 , Data.pads+1 };

Down F68 = { Data.formulas+4 , Data.formulas+0 };

LineOf F11 = { &F73 , &F74 };

Up F73 = { Data.formulas+4 , Data.formulas+1 };

Up F74 = { Data.formulas+4 , Data.formulas+2 };

LineOf F12 = { &F79 , &F80 };

Down F79 = { Data.formulas+4 , Data.formulas+1 };

Down F80 = { Data.formulas+4 , Data.formulas+2 };

LineOf F13 = { Data.pads+0 , &F86 };

Right F86 = { Data.pads+2 , Data.pads+0 };

Meet F14 = { Data.formulas+7 , Data.formulas+9 };

MoveLen F15 = { Data.formulas+9 , &F92 , Data.formulas+16 };

Mul F92 = { &F94 , Data.formulas+3 };

Ratio F94 = { {4000000000000000h,-61} , 0 };

Meet F16 = { Data.formulas+6 , Data.formulas+9 };

MoveLen F17 = { &F98 , &F99 , Data.pads+1 };

LineOf F98 = { Data.pads+1 , &F102 };

Move F102 = { Data.pads+1 , Data.formulas+16 , Data.formulas+18 };

LengthOf F99 = { Data.pads+1 , Data.formulas+16 };

MoveLen F18 = { &F108 , &F109 , Data.pads+1 };

LineOf F108 = { Data.pads+0 , Data.pads+1 };

LengthOf F109 = { Data.pads+1 , Data.formulas+16 };

Meet F19 = { Data.formulas+5 , Data.formulas+9 };

MoveLen F20 = { &F117 , &F118 , Data.pads+1 };

LineOf F117 = { Data.formulas+0 , Data.pads+1 };

LengthOf F118 = { Data.pads+1 , Data.formulas+16 };

MoveLen F21 = { &F124 , &F125 , Data.pads+1 };

LineOf F124 = { Data.pads+1 , &F128 };

Move F128 = { Data.pads+1 , Data.formulas+22 , Data.formulas+20 };

LengthOf F125 = { Data.pads+1 , Data.formulas+22 };

Meet F22 = { Data.formulas+5 , Data.formulas+10 };

MoveLen F23 = { Data.formulas+5 , &F137 , Data.formulas+22 };

Neg F137 = { &F139 };

LengthOf F139 = { Data.formulas+22 , Data.formulas+19 };

PathOf F24 = { { Data.formulas+14 , Data.formulas+15 , Data.formulas+16 , Data.formulas+17 , Data.formulas+18 , Data.formulas+19 , Data.formulas+20 , Data.formulas+21 , Data.formulas+22 , Data.formulas+23 , Data.formulas+25 } };

Meet F25 = { Data.formulas+5 , Data.formulas+13 };

Path Contour_test=
 {
  {
   { { {41428E12C3AF9400h,-53} , {7480000000000000h,-56} , 0 } , False },
   { { {52651C25875F2800h,-54} , {7480000000000000h,-56} , 0 } , False },
   { { {44A51C25875F2800h,-54} , {7480000000000000h,-56} , 0 } , False },
   { { {418F8E54242A3800h,-54} , {6BD11D11D2589000h,-56} , 0 } , False },
   { { {7BC73196251C6000h,-55} , {685E66A9265AEC00h,-56} , 0 } , False },
   { { {6DCA384B0EBE5400h,-55} , {7480000000000000h,-56} , 0 } , False },
   { { {672B4A887432D800h,-55} , {4800000000000000h,-55} , 0 } , False },
   { { {689B3F7F355C2800h,-55} , {4F698831DE286800h,-55} , 0 } , False },
   { { {6CB5C7B4F141AC00h,-55} , {55C0000000000000h,-55} , 0 } , False },
   { { {6BA1571ED3C50400h,-55} , {7140000000000000h,-55} , 0 } , False },
   { { {65C0000000000000h,-55} , {41C0000000000000h,-53} , 0 } , False }
  },
  0
 };

/*

SmoothDot Contour_test[11]=
 {
  { { 534610 , 119296 } , Smooth::DotSimple },
  { { 337490 , 119296 } , Smooth::DotSimple },
  { { 281170 , 119296 } , Smooth::DotSimple },
  { { 268537 , 110404 } , Smooth::DotSimple },
  { { 253498 , 106874 } , Smooth::DotSimple },
  { { 224850 , 119296 } , Smooth::DotSimple },
  { { 211290 , 147456 } , Smooth::DotSimple },
  { { 214234 , 162636 } , Smooth::DotSimple },
  { { 222638 , 175616 } , Smooth::DotSimple },
  { { 220427 , 231936 } , Smooth::DotSimple },
  { { 208384 , 538624 } , Smooth::DotSimple }
 };

*/

