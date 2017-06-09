//#include <Contour.ddl>

Contour Data=
 {
  {
   { { 'A1' , True , True , True } , 0 , &Pad0 },
   { { 'A5' , True , True , True } , 1 , &Pad1 },
   { { 'A3' , True , True , True } , 2 , &Pad2 },
   { { 'A2' , True , True , True } , 3 , &Pad3 },
   { { 'A4' , True , True , True } , 4 , &Pad4 }
  },
  {
  { { 'S' , True , True , True } , 0 , &F0 }
  }
 };

Point Pad0={{45A0000000000000h,-53},{69C0000000000000h,-54},0};

Point Pad1={{4240000000000000h,-54},{4D80000000000000h,-55},0};

Point Pad2={{5AC0000000000000h,-53},{7580000000000000h,-55},0};

Point Pad3={{7140000000000000h,-53},{6E00000000000000h,-55},0};

Point Pad4={{4E00000000000000h,-54},{4520000000000000h,-53},0};

LoopOf F0={{Data.pads+0,Data.pads+3,Data.pads+2,Data.pads+4,Data.pads+1}};

Loop Contour_S=
 {
  {
   {{{45A0000000000000h,-53},{69C0000000000000h,-54},0},False},
   {{{7140000000000000h,-53},{6E00000000000000h,-55},0},False},
   {{{5AC0000000000000h,-53},{7580000000000000h,-55},0},False},
   {{{4E00000000000000h,-54},{4520000000000000h,-53},0},False},
   {{{4240000000000000h,-54},{4D80000000000000h,-55},0},False}
  },
  0
 };

/*

SmoothDot Contour_S[]=
 {
  {{570368,433152},Smooth::DotSimple},
  {{927744,225280},Smooth::DotSimple},
  {{743424,240640},Smooth::DotSimple},
  {{319488,566272},Smooth::DotSimple},
  {{271360,158720},Smooth::DotSimple}
 };

*/

