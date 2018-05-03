//#include <Contour.ddl>

Contour Data=
 {
  {
   { { 'A1' , True , False , True } , 0 , &Pad0 },
   { { 'B1' , True , False , True } , 1 , &Pad1 },
   { { 'C1' , True , False , True } , 2 , &Pad2 },
   { { 'A2' , True , False , True } , 3 , &Pad3 },
   { { 'B2' , True , False , True } , 4 , &Pad4 },
   { { 'C2' , True , False , True } , 5 , &Pad5 }
  },
  {
  { { 'a' , True , True , True } , 0 , &F0 },
  { { 'b' , True , True , True } , 1 , &F1 },
  { { 'c' , True , True , True } , 2 , &F2 },
  { { 'c1' , True , True , True } , 3 , &F3 },
  { { 'c2' , True , True , True } , 4 , &F4 },
  { { 'C' , True , False , True } , 5 , &F5 },
  { { 'a1' , True , True , True } , 6 , &F6 },
  { { 'a2' , True , True , True } , 7 , &F7 },
  { { 'A' , True , False , True } , 8 , &F8 },
  { { 'b1' , True , True , True } , 9 , &F9 },
  { { 'b2' , True , True , True } , 10 , &F10 },
  { { 'B' , True , False , True } , 11 , &F11 },
  { { 'm' , True , True , True } , 12 , &F12 }
  }
 };

Point Pad0 = { {6940000000000000h,-54} , {7600000000000000h,-54} , 0 };

Point Pad1 = { {5C80000000000000h,-54} , {7200000000000000h,-56} , 0 };

Point Pad2 = { {4680000000000000h,-55} , {5C80000000000000h,-55} , 0 };

Point Pad3 = { {4B20000000000000h,-53} , {4120000000000000h,-53} , 0 };

Point Pad4 = { {6060000000000000h,-53} , {5E80000000000000h,-54} , 0 };

Point Pad5 = { {6B20000000000000h,-53} , {4060000000000000h,-53} , 0 };

LineOf F0 = { Data.pads+0 , Data.pads+3 };

LineOf F1 = { Data.pads+1 , Data.pads+4 };

LineOf F2 = { Data.pads+2 , Data.pads+5 };

LineOf F3 = { Data.pads+0 , Data.pads+1 };

LineOf F4 = { Data.pads+3 , Data.pads+4 };

Meet F5 = { Data.formulas+3 , Data.formulas+4 };

LineOf F6 = { Data.pads+1 , Data.pads+2 };

LineOf F7 = { Data.pads+4 , Data.pads+5 };

Meet F8 = { Data.formulas+6 , Data.formulas+7 };

LineOf F9 = { Data.pads+0 , Data.pads+2 };

LineOf F10 = { Data.pads+3 , Data.pads+5 };

Meet F11 = { Data.formulas+9 , Data.formulas+10 };

LineOf F12 = { Data.formulas+8 , Data.formulas+5 };

