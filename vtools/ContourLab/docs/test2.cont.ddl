//#include <Contour.ddl>

Contour Data=
 {
  {
  },
  {
  { { 'a' , True , True , True } , 0 , &F0 },
  { { 'b' , True , True , True } , 1 , &F1 }
  }
 };

Angle F0 = { {-5A9E8A554E178000h,-62} , 0 };

Mul F1 = { &F2 , Data.formulas+0 };

Ratio F2 = { {4000000000000000h,-61} , 0 };

