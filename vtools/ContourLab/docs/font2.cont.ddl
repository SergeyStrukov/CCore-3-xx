//#include <Contour.ddl>

Contour Data=
 {
  {
   { { 'O' , True , True , True } , 0 , &Pad0 },
   { { 'knob_rad' , True , True , True } , 1 , &Pad1 },
   { { 'A' , True , True , True } , 2 , &Pad2 },
   { { 'top' , True , True , True } , 3 , &Pad3 },
   { { 'len1' , True , True , True } , 4 , &Pad4 },
   { { 'len2' , True , True , True } , 5 , &Pad5 },
   { { 'len3' , True , True , True } , 6 , &Pad6 }
  },
  {
  { { 'knob' , True , True , False } , 0 , &F0 },
  { { 'AA' , True , True , True } , 1 , &F1 },
  { { 'B' , True , True , True } , 2 , &F2 },
  { { 'BB' , True , True , True } , 3 , &F3 },
  { { 'l1' , True , True , False } , 4 , &F4 },
  { { 'h1' , True , True , False } , 5 , &F5 },
  { { 'l2' , True , True , False } , 6 , &F6 },
  { { 'h2' , True , True , False } , 7 , &F7 },
  { { 'B1' , True , True , True } , 8 , &F8 },
  { { 'C1' , True , True , True } , 9 , &F9 },
  { { 'B2' , True , True , True } , 10 , &F10 },
  { { 'C2' , True , True , True } , 11 , &F11 },
  { { 'C3' , True , True , True } , 12 , &F12 },
  { { 'A1' , True , True , True } , 13 , &F13 },
  { { 'B3' , True , True , True } , 14 , &F14 },
  { { 'l3' , True , True , False } , 15 , &F15 },
  { { 'h3' , True , True , False } , 16 , &F16 },
  { { 'h4' , True , True , False } , 17 , &F17 },
  { { 's1' , True , True , False } , 18 , &F18 },
  { { 's2' , True , True , False } , 19 , &F19 },
  { { 'path1' , False , True , False } , 20 , &F20 },
  { { 'D' , True , True , False } , 21 , &F21 },
  { { 'D1' , True , True , True } , 22 , &F22 },
  { { 'D2' , True , True , True } , 23 , &F23 },
  { { 'h5' , True , True , False } , 24 , &F24 },
  { { 'h6' , True , True , False } , 25 , &F25 },
  { { 'anchor' , False , True , False } , 26 , &F26 },
  { { 'path2' , True , True , False } , 27 , &F27 },
  { { 'E1' , True , True , True } , 28 , &F28 },
  { { 'E2' , True , True , True } , 29 , &F29 }
  }
 };

Point Pad0 = { {69C0000000000000h,-54} , {5C40000000000000h,-54} , 0 };

Length Pad1 = { {4B00000000000000h,-54} , 0 };

Point Pad2 = { {41C0000000000000h,-54} , {4A60000000000000h,-53} , 0 };

Length Pad3 = { {4400000000000000h,-54} , 0 };

Length Pad4 = { {7C00000000000000h,-58} , 0 };

Length Pad5 = { {5000000000000000h,-58} , 0 };

Length Pad6 = { {5000000000000000h,-56} , 0 };

CircleOf F0 = { Data.pads+0 , Data.pads+1 };

MoveLen F1 = { &F32 , &F33 , Data.pads+0 };

LineOf F32 = { Data.pads+2 , Data.pads+0 };

LengthOf F33 = { Data.pads+2 , Data.pads+0 };

Left F2 = { Data.pads+3 , Data.formulas+1 };

MoveLen F3 = { &F41 , &F42 , Data.pads+0 };

LineOf F41 = { Data.formulas+2 , Data.pads+0 };

LengthOf F42 = { Data.formulas+2 , Data.pads+0 };

LineOf F4 = { Data.pads+2 , Data.formulas+2 };

LineOf F5 = { Data.formulas+2 , Data.formulas+1 };

LineOf F6 = { Data.formulas+1 , Data.formulas+3 };

LineOf F7 = { Data.formulas+3 , Data.pads+2 };

MoveLen F8 = { &F56 , Data.pads+4 , Data.formulas+2 };

LineOf F56 = { Data.formulas+2 , Data.pads+2 };

Right F9 = { &F61 , Data.formulas+8 };

Sub F61 = { &F63 , Data.pads+5 };

LengthOf F63 = { Data.formulas+2 , Data.formulas+1 };

MoveLen F10 = { &F67 , Data.pads+6 , Data.formulas+8 };

LineOf F67 = { Data.formulas+2 , Data.pads+2 };

Right F11 = { &F72 , Data.formulas+10 };

LengthOf F72 = { Data.formulas+8 , Data.formulas+9 };

MoveLen F12 = { &F76 , &F77 , Data.formulas+1 };

LineOf F76 = { Data.formulas+1 , Data.formulas+3 };

Add F77 = { &F81 , &F82 };

LengthOf F81 = { Data.formulas+2 , Data.formulas+10 };

LengthOf F82 = { Data.formulas+2 , Data.formulas+8 };

MoveLen F13 = { &F87 , Data.pads+6 , Data.pads+2 };

LineOf F87 = { Data.pads+2 , Data.formulas+3 };

MoveLen F14 = { &F92 , Data.pads+6 , Data.formulas+2 };

LineOf F92 = { Data.formulas+2 , Data.formulas+1 };

LineOf F15 = { Data.formulas+13 , Data.formulas+14 };

LineOf F16 = { Data.formulas+8 , Data.formulas+9 };

LineOf F17 = { Data.formulas+10 , Data.formulas+11 };

LineOf F18 = { Data.formulas+9 , Data.formulas+1 };

LineOf F19 = { Data.formulas+11 , Data.formulas+12 };

BLoopOf F20 = { { &F107 , &F108 , &F109 , &F110 , &F111 , &F112 , &F113 , &F114 } };

StepOf F107 = { { Data.pads+2 } };

StepOf F108 = { { Data.formulas+8 } };

StepOf F109 = { { Data.formulas+9 } };

StepOf F110 = { { Data.formulas+1 } };

StepOf F111 = { { Data.formulas+12 } };

StepOf F112 = { { Data.formulas+11 } };

StepOf F113 = { { &F121 } };

Meet F121 = { Data.formulas+15 , Data.formulas+17 };

StepOf F114 = { { Data.formulas+13 } };

Middle F21 = { Data.pads+2 , Data.formulas+2 };

MoveLen F22 = { &F127 , &F128 , Data.formulas+21 };

LineOf F127 = { Data.formulas+21 , Data.formulas+2 };

Div F128 = { Data.pads+6 , &F133 };

Ratio F133 = { {4000000000000000h,-61} , 0 };

MoveLen F23 = { &F134 , &F135 , Data.formulas+21 };

LineOf F134 = { Data.formulas+21 , Data.pads+2 };

Div F135 = { Data.pads+6 , &F140 };

Ratio F140 = { {4000000000000000h,-61} , 0 };

LineOf F24 = { Data.formulas+22 , &F142 };

Right F142 = { Data.pads+3 , Data.formulas+22 };

LineOf F25 = { Data.formulas+23 , &F146 };

Right F146 = { Data.pads+3 , Data.formulas+23 };

LoopOf F26 = { { Data.pads+0 , Data.formulas+2 } };

BLoopOf F27 = { { &F151 , &F152 , &F153 , &F154 , &F155 , &F156 , &F157 , &F158 , &F159 , &F160 , &F161 , &F162 } };

StepOf F151 = { { Data.pads+2 } };

StepOf F152 = { { Data.formulas+8 } };

StepOf F153 = { { Data.formulas+9 } };

StepOf F154 = { { Data.formulas+1 } };

StepOf F155 = { { Data.formulas+12 } };

StepOf F156 = { { Data.formulas+11 } };

StepOf F157 = { { &F169 } };

Meet F169 = { Data.formulas+15 , Data.formulas+17 };

StepOf F158 = { { &F172 } };

Meet F172 = { Data.formulas+15 , Data.formulas+24 };

StepOf F159 = { { Data.formulas+28 } };

StepOf F160 = { { Data.formulas+29 } };

StepOf F161 = { { &F177 } };

Meet F177 = { Data.formulas+15 , Data.formulas+25 };

StepOf F162 = { { Data.formulas+13 } };

MoveLen F28 = { Data.formulas+24 , &F182 , Data.formulas+22 };

Mul F182 = { &F184 , Data.pads+3 };

Div F184 = { &F186 , &F187 };

Ratio F186 = { {5000000000000000h,-60} , 0 };

Ratio F187 = { {4000000000000000h,-59} , 0 };

MoveLen F29 = { Data.formulas+25 , &F189 , Data.formulas+23 };

Mul F189 = { &F191 , Data.pads+3 };

Div F191 = { &F193 , &F194 };

Ratio F193 = { {5000000000000000h,-60} , 0 };

Ratio F194 = { {4000000000000000h,-59} , 0 };

Loop Contour_path1=
 {
  {
   { { {41C0000000000000h,-54} , {4A60000000000000h,-53} , 0 } , True },
   { { {4CEE7CDFCAF30800h,-54} , {56E9D033E71EF400h,-55} , 0 } , True },
   { { {45F73E6FE5798400h,-53} , {56E9D033E71EF400h,-55} , 0 } , True },
   { { {48E0000000000000h,-53} , {4780000000000000h,-55} , 0 } , True },
   { { {470026429F456400h,-53} , {470D2F6E9DBA8000h,-54} , 0 } , True },
   { { {44E8E7D2B9CBE000h,-53} , {7EB08EA954560C00h,-55} , 0 } , True },
   { { {5ED1CFA57397C000h,-54} , {7EB08EA954560C00h,-55} , 0 } , True },
   { { {55C0000000000000h,-54} , {4A60000000000000h,-53} , 0 } , True }
  },
  0
 };

/*

SmoothDot Contour_path1[8]=
 {
  { { 269312 , 609280 } , Smooth::DotBreak },
  { { 315112 , 177999 } , Smooth::DotBreak },
  { { 573160 , 177999 } , Smooth::DotBreak },
  { { 596992 , 146432 } , Smooth::DotBreak },
  { { 581637 , 291027 } , Smooth::DotBreak },
  { { 564509 , 259460 } , Smooth::DotBreak },
  { { 388381 , 259460 } , Smooth::DotBreak },
  { { 351232 , 609280 } , Smooth::DotBreak }
 };

*/

Loop Contour_anchor=
 {
  {
   { { {69C0000000000000h,-54} , {5C40000000000000h,-54} , 0 } , False },
   { { {4DC0000000000000h,-54} , {4780000000000000h,-55} , 0 } , False }
  },
  0
 };

/*

SmoothDot Contour_anchor[2]=
 {
  { { 433152 , 377856 } , Smooth::DotSimple },
  { { 318464 , 146432 } , Smooth::DotSimple }
 };

*/

Loop Contour_path2=
 {
  {
   { { {41C0000000000000h,-54} , {4A60000000000000h,-53} , 0 } , True },
   { { {4CEE7CDFCAF30800h,-54} , {56E9D033E71EF400h,-55} , 0 } , True },
   { { {45F73E6FE5798400h,-53} , {56E9D033E71EF400h,-55} , 0 } , True },
   { { {48E0000000000000h,-53} , {4780000000000000h,-55} , 0 } , True },
   { { {470026429F456400h,-53} , {470D2F6E9DBA8000h,-54} , 0 } , True },
   { { {44E8E7D2B9CBE000h,-53} , {7EB08EA954560C00h,-55} , 0 } , True },
   { { {5ED1CFA57397C000h,-54} , {7EB08EA954560C00h,-55} , 0 } , True },
   { { {5CCE569D2BADA400h,-54} , {524E5062A4B23800h,-54} , 0 } , True },
   { { {734E569D2BADA400h,-54} , {524E5062A4B23800h,-54} , 0 } , True },
   { { {7131A962D4525C00h,-54} , {6631AF9D5B4DC800h,-54} , 0 } , True },
   { { {5AB1A962D4525C00h,-54} , {6631AF9D5B4DC800h,-54} , 0 } , True },
   { { {55C0000000000000h,-54} , {4A60000000000000h,-53} , 0 } , True }
  },
  0
 };

/*

SmoothDot Contour_path2[12]=
 {
  { { 269312 , 609280 } , Smooth::DotBreak },
  { { 315112 , 177999 } , Smooth::DotBreak },
  { { 573160 , 177999 } , Smooth::DotBreak },
  { { 596992 , 146432 } , Smooth::DotBreak },
  { { 581637 , 291027 } , Smooth::DotBreak },
  { { 564509 , 259460 } , Smooth::DotBreak },
  { { 388381 , 259460 } , Smooth::DotBreak },
  { { 380133 , 337125 } , Smooth::DotBreak },
  { { 472293 , 337125 } , Smooth::DotBreak },
  { { 463643 , 418587 } , Smooth::DotBreak },
  { { 371483 , 418587 } , Smooth::DotBreak },
  { { 351232 , 609280 } , Smooth::DotBreak }
 };

*/

