//#include <Contour.ddl>

Contour Data=
 {
  {
   { { 'A' , True , False , True } , 0 , &Pad0 },
   { { 'B' , True , False , True } , 1 , &Pad1 },
   { { 'C' , True , False , True } , 2 , &Pad2 }
  },
  {
  { { 'AB' , True , True , True } , 0 , &F0 },
  { { 'BC' , True , True , True } , 1 , &F1 },
  { { 'CA' , True , True , True } , 2 , &F2 },
  { { 'alpha' , True , True , True } , 3 , &F3 },
  { { 'bisA' , True , True , True } , 4 , &F4 },
  { { 'beta' , True , True , True } , 5 , &F5 },
  { { 'bisB' , True , True , True } , 6 , &F6 },
  { { 'gamma' , True , True , True } , 7 , &F7 },
  { { 'bisC' , True , True , True } , 8 , &F8 },
  { { 'O' , True , False , True } , 9 , &F9 },
  { { 'Inner' , True , True , True } , 10 , &F10 }
  }
 };

Point Pad0={{7AC0000000000000h,-54},{5080000000000000h,-55},0};

Point Pad1={{4E40000000000000h,-54},{4FE0000000000000h,-53},0};

Point Pad2={{76E0000000000000h,-53},{7F80000000000000h,-54},0};

LineOf F0={Data.pads+0,Data.pads+1};

LineOf F1={Data.pads+1,Data.pads+2};

LineOf F2={Data.pads+2,Data.pads+0};

AngleOf F3={Data.pads+1,Data.pads+0,Data.pads+2};

LineOf F4={Data.pads+0,&F21};

Rotate F21={Data.pads+0,&F23,Data.pads+1};

Div F23={Data.formulas+3,&F26};

Ratio F26={{4000000000000000h,-61},0};

AngleOf F5={Data.pads+2,Data.pads+1,Data.pads+0};

LineOf F6={Data.pads+1,&F31};

Rotate F31={Data.pads+1,&F33,Data.pads+2};

Div F33={Data.formulas+5,&F36};

Ratio F36={{4000000000000000h,-61},0};

AngleOf F7={Data.pads+0,Data.pads+2,Data.pads+1};

LineOf F8={Data.pads+2,&F41};

Rotate F41={Data.pads+2,&F43,Data.pads+0};

Div F43={Data.formulas+7,&F46};

Ratio F46={{4000000000000000h,-61},0};

Meet F9={Data.formulas+4,Data.formulas+6};

CircleOf F10={Data.formulas+9,&F50};

LengthOf F50={Data.formulas+9,&F52};

Proj F52={Data.formulas+0,Data.formulas+9};

