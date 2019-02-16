//#include <Contour.ddl>

Contour Data=
 {
  {
   { { 'O' , True , True , True } , 0 , &Pad0 },
   { { 'radius' , True , True , True } , 1 , &Pad1 },
   { { 'rat' , True , True , True } , 2 , &Pad2 },
   { { 'blen' , True , True , True } , 3 , &Pad3 },
   { { 'alen' , True , True , True } , 4 , &Pad4 },
   { { 'S1' , True , True , True } , 5 , &Pad5 },
   { { 'S2' , True , True , True } , 6 , &Pad6 },
   { { 'S3' , True , True , True } , 7 , &Pad7 },
   { { 'S4' , True , True , True } , 8 , &Pad8 },
   { { 'S5' , True , True , True } , 9 , &Pad9 },
   { { 'S6' , True , True , True } , 10 , &Pad10 }
  },
  {
  { { 'cir' , True , True , False } , 0 , &F0 },
  { { 'height' , True , True , True } , 1 , &F1 },
  { { 'Top' , True , True , True } , 2 , &F2 },
  { { 'anchor' , False , True , False } , 3 , &F3 },
  { { 'l' , True , True , False } , 4 , &F4 },
  { { 'B' , True , True , True } , 5 , &F5 },
  { { 'A' , True , True , True } , 6 , &F6 },
  { { 'T1' , True , True , True } , 7 , &F7 },
  { { 'T2' , True , True , True } , 8 , &F8 },
  { { 'T3' , True , True , True } , 9 , &F9 },
  { { 'T4' , True , True , True } , 10 , &F10 },
  { { 'T5' , True , True , True } , 11 , &F11 },
  { { 'T6' , True , True , True } , 12 , &F12 },
  { { 'step1' , True , True , True } , 13 , &F13 },
  { { 'step2' , True , True , True } , 14 , &F14 },
  { { 'loop' , True , True , True } , 15 , &F15 }
  }
 };

Point Pad0 = { {77C0000000000000h,-54} , {5340000000000000h,-54} , 0 };

Length Pad1 = { {4C80000000000000h,-54} , 0 };

Ratio Pad2 = { {6000000000000000h,-63} , 0 };

Length Pad3 = { {6000000000000000h,-55} , 0 };

Length Pad4 = { {4880000000000000h,-55} , 0 };

Point Pad5 = { {6A80000000000000h,-54} , {4C80000000000000h,-55} , 0 };

Point Pad6 = { {5580000000000000h,-54} , {5100000000000000h,-55} , 0 };

Point Pad7 = { {4A00000000000000h,-54} , {6E80000000000000h,-55} , 0 };

Point Pad8 = { {4B00000000000000h,-54} , {4B80000000000000h,-54} , 0 };

Point Pad9 = { {59C0000000000000h,-54} , {5FC0000000000000h,-54} , 0 };

Point Pad10 = { {6940000000000000h,-54} , {6E40000000000000h,-54} , 0 };

CircleOf F0 = { Data.pads+0 , Data.pads+1 };

Mul F1 = { Data.pads+2 , Data.pads+1 };

Up F2 = { Data.formulas+1 , Data.pads+0 };

LoopOf F3 = { { Data.pads+0 , Data.formulas+2 } };

LineOf F4 = { Data.pads+0 , Data.formulas+2 };

Down F5 = { Data.pads+3 , Data.pads+0 };

Up F6 = { Data.pads+4 , Data.pads+0 };

Right F7 = { &F30 , Data.pads+5 };

Mul F30 = { &F32 , &F33 };

Ratio F32 = { {4000000000000000h,-61} , 0 };

LengthOf F33 = { Data.pads+5 , &F35 };

Proj F35 = { Data.formulas+4 , Data.pads+5 };

Right F8 = { &F38 , Data.pads+6 };

Mul F38 = { &F40 , &F41 };

Ratio F40 = { {4000000000000000h,-61} , 0 };

LengthOf F41 = { Data.pads+6 , &F43 };

Proj F43 = { Data.formulas+4 , Data.pads+6 };

Right F9 = { &F46 , Data.pads+7 };

Mul F46 = { &F48 , &F49 };

Ratio F48 = { {4000000000000000h,-61} , 0 };

LengthOf F49 = { Data.pads+7 , &F51 };

Proj F51 = { Data.formulas+4 , Data.pads+7 };

Right F10 = { &F54 , Data.pads+8 };

Mul F54 = { &F56 , &F57 };

Ratio F56 = { {4000000000000000h,-61} , 0 };

LengthOf F57 = { Data.pads+8 , &F59 };

Proj F59 = { Data.formulas+4 , Data.pads+8 };

Right F11 = { &F62 , Data.pads+9 };

Mul F62 = { &F64 , &F65 };

Ratio F64 = { {4000000000000000h,-61} , 0 };

LengthOf F65 = { Data.pads+9 , &F67 };

Proj F67 = { Data.formulas+4 , Data.pads+9 };

Right F12 = { &F70 , Data.pads+10 };

Mul F70 = { &F72 , &F73 };

Ratio F72 = { {4000000000000000h,-61} , 0 };

LengthOf F73 = { Data.pads+10 , &F75 };

Proj F75 = { Data.formulas+4 , Data.pads+10 };

StepOf F13 = { { Data.formulas+6 , Data.pads+5 , Data.pads+6 , Data.pads+7 , Data.pads+8 , Data.pads+9 , Data.pads+10 } };

StepOf F14 = { { Data.formulas+5 , Data.formulas+12 , Data.formulas+11 , Data.formulas+10 , Data.formulas+9 , Data.formulas+8 , Data.formulas+7 } };

BLoopOf F15 = { { Data.formulas+13 , Data.formulas+14 } };

Loop Contour_anchor=
 {
  {
   { { {77C0000000000000h,-54} , {5340000000000000h,-54} , 0 } , False },
   { { {77C0000000000000h,-54} , {6780000000000000h,-56} , 0 } , False }
  },
  0
 };

/*

SmoothDot Contour_anchor[2]=
 {
  { { 490496 , 340992 } , Smooth::DotSimple },
  { { 490496 , 105984 } , Smooth::DotSimple }
 };

*/

Loop Contour_loop=
 {
  {
   { { {77C0000000000000h,-54} , {5E00000000000000h,-55} , 0 } , True },
   { { {6A80000000000000h,-54} , {4C80000000000000h,-55} , 0 } , False },
   { { {5580000000000000h,-54} , {5100000000000000h,-55} , 0 } , False },
   { { {4A00000000000000h,-54} , {6E80000000000000h,-55} , 0 } , False },
   { { {4B00000000000000h,-54} , {4B80000000000000h,-54} , 0 } , False },
   { { {59C0000000000000h,-54} , {5FC0000000000000h,-54} , 0 } , False },
   { { {6940000000000000h,-54} , {6E40000000000000h,-54} , 0 } , False },
   { { {77C0000000000000h,-54} , {41A0000000000000h,-53} , 0 } , True },
   { { {4320000000000000h,-53} , {6E40000000000000h,-54} , 0 } , False },
   { { {4AE0000000000000h,-53} , {5FC0000000000000h,-54} , 0 } , False },
   { { {5240000000000000h,-53} , {4B80000000000000h,-54} , 0 } , False },
   { { {52C0000000000000h,-53} , {6E80000000000000h,-55} , 0 } , False },
   { { {4D00000000000000h,-53} , {5100000000000000h,-55} , 0 } , False },
   { { {4280000000000000h,-53} , {4C80000000000000h,-55} , 0 } , False }
  },
  0
 };

/*

SmoothDot Contour_loop[14]=
 {
  { { 490496 , 192512 } , Smooth::DotBreak },
  { { 436224 , 156672 } , Smooth::DotSimple },
  { { 350208 , 165888 } , Smooth::DotSimple },
  { { 303104 , 226304 } , Smooth::DotSimple },
  { { 307200 , 309248 } , Smooth::DotSimple },
  { { 367616 , 392192 } , Smooth::DotSimple },
  { { 431104 , 451584 } , Smooth::DotSimple },
  { { 490496 , 537600 } , Smooth::DotBreak },
  { { 549888 , 451584 } , Smooth::DotSimple },
  { { 613376 , 392192 } , Smooth::DotSimple },
  { { 673792 , 309248 } , Smooth::DotSimple },
  { { 677888 , 226304 } , Smooth::DotSimple },
  { { 630784 , 165888 } , Smooth::DotSimple },
  { { 544768 , 156672 } , Smooth::DotSimple }
 };

*/

