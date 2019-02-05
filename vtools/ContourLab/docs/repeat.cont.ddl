//#include <Contour.ddl>

Contour Data=
 {
  {
   { { 'O' , True , True , True } , 0 , &Pad0 },
   { { 'radius' , True , True , True } , 1 , &Pad1 },
   { { 'width' , True , True , True } , 2 , &Pad2 },
   { { 'start' , True , True , True } , 3 , &Pad3 },
   { { 'stop' , True , True , True } , 4 , &Pad4 }
  },
  {
  { { 'base' , True , True , True } , 0 , &F0 },
  { { 'C' , True , True , True } , 1 , &F1 },
  { { 'B' , True , True , True } , 2 , &F2 },
  { { 'A' , True , True , True } , 3 , &F3 }
  }
 };

Point Pad0 = { {65C0000000000000h,-54} , {5C00000000000000h,-54} , 0 };

Length Pad1 = { {6400000000000000h,-55} , 0 };

Ratio Pad2 = { {4CCCCCCCCCCCCC00h,-64} , 0 };

Angle Pad3 = { {6487ED5110B46000h,-63} , 0 };

Angle Pad4 = { {430548E0B5CD9400h,-64} , 0 };

CircleOf F0 = { Data.pads+0 , Data.pads+1 };

Rotate F1 = { Data.pads+0 , &F7 , &F8 };

Neg F7 = { Data.pads+4 };

Left F8 = { Data.pads+1 , Data.pads+0 };

Rotate F2 = { Data.pads+0 , &F13 , &F14 };

Neg F13 = { Data.pads+3 };

Left F14 = { &F16 , Data.pads+0 };

Mul F16 = { &F18 , Data.pads+1 };

Add F18 = { &F20 , Data.pads+2 };

Ratio F20 = { {4000000000000000h,-62} , 0 };

Rotate F3 = { Data.pads+0 , &F23 , &F24 };

Neg F23 = { Data.pads+3 };

Left F24 = { &F26 , Data.pads+0 };

Mul F26 = { &F28 , Data.pads+1 };

Sub F28 = { &F30 , Data.pads+2 };

Ratio F30 = { {4000000000000000h,-62} , 0 };

