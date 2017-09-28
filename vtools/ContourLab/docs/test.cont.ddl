//#include <Contour.ddl>

Contour Data=
 {
  {
   { { 'A' , True , True , True } , 0 , &Pad0 },
   { { 'B' , True , True , True } , 1 , &Pad1 },
   { { 'C' , True , True , True } , 2 , &Pad2 },
   { { 'P1' , True , True , True } , 3 , &Pad3 },
   { { 'P2' , True , True , True } , 4 , &Pad4 },
   { { 'P3' , True , True , True } , 5 , &Pad5 },
   { { 'P4' , True , True , True } , 6 , &Pad6 }
  },
  {
  { { 'l' , True , True , True } , 0 , &F0 },
  { { 'линия' , True , True , True } , 1 , &F1 },
  { { 'D' , True , True , True } , 2 , &F2 },
  { { 'path' , False , True , True } , 3 , &F3 },
  { { 'step2' , True , True , True } , 4 , &F4 },
  { { 'path2' , True , True , False } , 5 , &F5 },
  { { 'step1' , True , True , True } , 6 , &F6 }
  }
 };

Point Pad0 = { {4160000000000000h,-53} , {5DC0000000000000h,-54} , 0 };

Point Pad1 = { {5F60000000000000h,-53} , {6980000000000000h,-55} , 0 };

Point Pad2 = { {7600000000000000h,-53} , {7E80000000000000h,-54} , 0 };

Point Pad3 = { {5060000000000000h,-53} , {46A0000000000000h,-53} , 0 };

Point Pad4 = { {4E80000000000000h,-54} , {50C0000000000000h,-54} , 0 };

Point Pad5 = { {4A00000000000000h,-54} , {7300000000000000h,-54} , 0 };

Point Pad6 = { {6C40000000000000h,-54} , {4D00000000000000h,-53} , 0 };

LengthOf F0 = { Data.pads+0 , Data.pads+1 };

LineOf F1 = { Data.pads+0 , Data.pads+1 };

MoveLen F2 = { &F11 , Data.formulas+0 , Data.pads+0 };

LineOf F11 = { Data.pads+0 , Data.pads+2 };

PathOf F3 = { { Data.pads+0 , Data.pads+1 , Data.pads+2 , Data.formulas+2 } };

StepOf F4 = { { Data.pads+3 , Data.pads+4 , Data.pads+5 , Data.pads+6 } };

BPathOf F5 = { { Data.formulas+6 , Data.formulas+4 } };

StepOf F6 = { { Data.pads+0 , Data.pads+1 , Data.pads+2 , Data.formulas+2 } };

Path Contour_path=
 {
  {
   { { {4160000000000000h,-53} , {5DC0000000000000h,-54} , 0 } , False },
   { { {5F60000000000000h,-53} , {6980000000000000h,-55} , 0 } , False },
   { { {7600000000000000h,-53} , {7E80000000000000h,-54} , 0 } , False },
   { { {6411C67E4AB8E400h,-53} , {7357602A1C426C00h,-54} , 0 } , False }
  },
  0
 };

/*

SmoothDot Contour_path[]=
 {
  { { 535552 , 384000 } , Smooth::DotSimple },
  { { 781312 , 216064 } , Smooth::DotSimple },
  { { 966656 , 518144 } , Smooth::DotSimple },
  { { 819769 , 472438 } , Smooth::DotSimple }
 };

*/

Path Contour_path2=
 {
  {
   { { {4160000000000000h,-53} , {5DC0000000000000h,-54} , 0 } , True },
   { { {5F60000000000000h,-53} , {6980000000000000h,-55} , 0 } , False },
   { { {7600000000000000h,-53} , {7E80000000000000h,-54} , 0 } , False },
   { { {6411C67E4AB8E400h,-53} , {7357602A1C426C00h,-54} , 0 } , False },
   { { {5060000000000000h,-53} , {46A0000000000000h,-53} , 0 } , True },
   { { {4E80000000000000h,-54} , {50C0000000000000h,-54} , 0 } , False },
   { { {4A00000000000000h,-54} , {7300000000000000h,-54} , 0 } , False },
   { { {6C40000000000000h,-54} , {4D00000000000000h,-53} , 0 } , False }
  },
  0
 };

/*

SmoothDot Contour_path2[]=
 {
  { { 535552 , 384000 } , Smooth::DotBreak },
  { { 781312 , 216064 } , Smooth::DotSimple },
  { { 966656 , 518144 } , Smooth::DotSimple },
  { { 819769 , 472438 } , Smooth::DotSimple },
  { { 658432 , 578560 } , Smooth::DotBreak },
  { { 321536 , 330752 } , Smooth::DotSimple },
  { { 303104 , 471040 } , Smooth::DotSimple },
  { { 443392 , 630784 } , Smooth::DotSimple }
 };

*/

