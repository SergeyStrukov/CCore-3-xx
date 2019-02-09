//#include <Contour.ddl>

Contour Data=
 {
  {
   { { 'A1' , True , True , True } , 0 , &Pad0 },
   { { 'A2' , True , True , True } , 1 , &Pad1 },
   { { 'A3' , True , True , True } , 2 , &Pad2 },
   { { 'A4' , True , True , True } , 3 , &Pad3 },
   { { 'B1' , True , True , True } , 4 , &Pad4 },
   { { 'B2' , True , True , True } , 5 , &Pad5 },
   { { 'B3' , True , True , True } , 6 , &Pad6 }
  },
  {
  { { 'step1' , True , True , True } , 0 , &F0 },
  { { 'step2' , True , True , True } , 1 , &F1 },
  { { 'loop' , True , True , True } , 2 , &F2 },
  { { 'solid' , True , True , True } , 3 , &F3 }
  }
 };

Point Pad0 = { {6500000000000000h,-55} , {6200000000000000h,-55} , 0 };

Point Pad1 = { {5780000000000000h,-54} , {4380000000000000h,-54} , 0 };

Point Pad2 = { {43A0000000000000h,-53} , {6700000000000000h,-55} , 0 };

Point Pad3 = { {55E0000000000000h,-53} , {5080000000000000h,-54} , 0 };

Point Pad4 = { {4520000000000000h,-53} , {7A80000000000000h,-54} , 0 };

Point Pad5 = { {5DC0000000000000h,-54} , {6740000000000000h,-54} , 0 };

Point Pad6 = { {7900000000000000h,-56} , {4D00000000000000h,-54} , 0 };

StepOf F0 = { { Data.pads+0 , Data.pads+1 , Data.pads+2 , Data.pads+3 } };

StepOf F1 = { { Data.pads+4 , Data.pads+5 , Data.pads+6 } };

BLoopOf F2 = { { Data.formulas+0 , Data.formulas+1 } };

SolidOf F3 = { Data.formulas+2 };

Loop Contour_loop=
 {
  {
   { { {6500000000000000h,-55} , {6200000000000000h,-55} , 0 } , True },
   { { {5780000000000000h,-54} , {4380000000000000h,-54} , 0 } , False },
   { { {43A0000000000000h,-53} , {6700000000000000h,-55} , 0 } , False },
   { { {55E0000000000000h,-53} , {5080000000000000h,-54} , 0 } , False },
   { { {4520000000000000h,-53} , {7A80000000000000h,-54} , 0 } , True },
   { { {5DC0000000000000h,-54} , {6740000000000000h,-54} , 0 } , False },
   { { {7900000000000000h,-56} , {4D00000000000000h,-54} , 0 } , False }
  },
  0
 };

/*

SmoothDot Contour_loop[]=
 {
  { { 206848 , 200704 } , Smooth::DotBreak },
  { { 358400 , 276480 } , Smooth::DotSimple },
  { { 553984 , 210944 } , Smooth::DotSimple },
  { { 703488 , 329728 } , Smooth::DotSimple },
  { { 566272 , 501760 } , Smooth::DotBreak },
  { { 384000 , 422912 } , Smooth::DotSimple },
  { { 123904 , 315392 } , Smooth::DotSimple }
 };

*/

