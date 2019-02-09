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
  { { 'leny' , True , True , True } , 4 , &F4 }
  }
 };

Point Pad0 = { {7380000000000000h,-55} , {41C0000000000000h,-53} , 0 };

Point Pad1 = { {4300000000000000h,-54} , {4680000000000000h,-55} , 0 };

Length Pad2 = { {44C0000000000000h,-54} , 0 };

Ratio Pad3 = { {4CCCCCCCCCCCCC00h,-63} , 0 };

Ratio Pad4 = { {5999999999999800h,-63} , 0 };

Ratio Pad5 = { {6666666666666800h,-66} , 0 };

Ratio Pad6 = { {6666666666666800h,-66} , 0 };

Right F0 = { Data.pads+2 , Data.pads+1 };

Part F1 = { Data.pads+0 , Data.pads+1 , Data.pads+3 };

Right F2 = { &F10 , Data.formulas+1 };

Mul F10 = { Data.pads+4 , Data.pads+2 };

Mul F3 = { Data.pads+5 , Data.pads+2 };

Mul F4 = { Data.pads+6 , Data.pads+2 };

