//#include <Contour.ddl>

Contour Data=
 {
  {
   { { 'O' , True , True , True } , 0 , &Pad0 },
   { { 'radius1' , True , True , True } , 1 , &Pad1 },
   { { 'radius2' , True , True , True } , 2 , &Pad2 },
   { { 'delta' , True , True , True } , 3 , &Pad3 }
  },
  {
  { { 'cir1' , True , True , False } , 0 , &F0 },
  { { 'cir2' , True , True , False } , 1 , &F1 },
  { { 'A' , True , True , False } , 2 , &F2 },
  { { 'B' , True , True , False } , 3 , &F3 },
  { { 'C' , True , True , False } , 4 , &F4 },
  { { 'D' , True , True , False } , 5 , &F5 },
  { { 'alpha' , True , True , True } , 6 , &F6 },
  { { 'A1' , True , True , False } , 7 , &F7 },
  { { 'A2' , True , True , False } , 8 , &F8 },
  { { 'A3' , True , True , False } , 9 , &F9 },
  { { 'A4' , True , True , False } , 10 , &F10 },
  { { 'A5' , True , True , False } , 11 , &F11 },
  { { 'A6' , True , True , False } , 12 , &F12 },
  { { 'A7' , True , True , False } , 13 , &F13 },
  { { 'A8' , True , True , False } , 14 , &F14 },
  { { 'A9' , True , True , False } , 15 , &F15 },
  { { 'A10' , True , True , False } , 16 , &F16 },
  { { 'A11' , True , True , False } , 17 , &F17 },
  { { 'A12' , True , True , False } , 18 , &F18 },
  { { 'A13' , True , True , False } , 19 , &F19 },
  { { 'A14' , True , True , False } , 20 , &F20 },
  { { 'A15' , True , True , False } , 21 , &F21 },
  { { 'step1' , True , True , True } , 22 , &F22 },
  { { 'C1' , True , True , False } , 23 , &F23 },
  { { 'C2' , True , True , False } , 24 , &F24 },
  { { 'C3' , True , True , False } , 25 , &F25 },
  { { 'baseloop' , False , True , False } , 26 , &F26 },
  { { 'step2' , True , True , True } , 27 , &F27 },
  { { 'step3' , True , True , True } , 28 , &F28 },
  { { 'step4' , True , True , True } , 29 , &F29 },
  { { 'step5' , True , True , True } , 30 , &F30 },
  { { 'D1' , True , True , False } , 31 , &F31 },
  { { 'D2' , True , True , False } , 32 , &F32 },
  { { 'D3' , True , True , False } , 33 , &F33 },
  { { 'D4' , True , True , False } , 34 , &F34 },
  { { 'D5' , True , True , False } , 35 , &F35 },
  { { 'D6' , True , True , False } , 36 , &F36 },
  { { 'D7' , True , True , False } , 37 , &F37 },
  { { 'D8' , True , True , False } , 38 , &F38 },
  { { 'D9' , True , True , False } , 39 , &F39 },
  { { 'D10' , True , True , False } , 40 , &F40 },
  { { 'D11' , True , True , False } , 41 , &F41 },
  { { 'D12' , True , True , False } , 42 , &F42 },
  { { 'D13' , True , True , False } , 43 , &F43 },
  { { 'D14' , True , True , False } , 44 , &F44 },
  { { 'D15' , True , True , False } , 45 , &F45 },
  { { 'step6' , True , True , True } , 46 , &F46 },
  { { 'step7' , True , True , True } , 47 , &F47 },
  { { 'loop' , True , True , False } , 48 , &F48 },
  { { 'solid' , True , True , False } , 49 , &F49 }
  }
 };

Point Pad0 = { {5B40000000000000h,-54} , {4F80000000000000h,-54} , 0 };

Length Pad1 = { {4B00000000000000h,-56} , 0 };

Length Pad2 = { {4600000000000000h,-55} , 0 };

Ratio Pad3 = { {5555555555555400h,-63} , 0 };

CircleOf F0 = { Data.pads+0 , Data.pads+1 };

CircleOf F1 = { Data.pads+0 , Data.pads+2 };

Right F2 = { Data.pads+1 , Data.pads+0 };

Right F3 = { Data.pads+2 , Data.pads+0 };

Up F4 = { Data.pads+1 , Data.pads+0 };

Up F5 = { Data.pads+2 , Data.pads+0 };

Angle F6 = { {4B65F1FCCC874800h,-64} , 0 };

Rotate F7 = { Data.pads+0 , &F63 , Data.formulas+2 };

Mul F63 = { &F65 , Data.formulas+6 };

Neg F65 = { &F67 };

Ratio F67 = { {4000000000000000h,-62} , 0 };

Rotate F8 = { Data.pads+0 , &F69 , Data.formulas+2 };

Mul F69 = { &F71 , Data.formulas+6 };

Neg F71 = { &F73 };

Ratio F73 = { {4000000000000000h,-61} , 0 };

Rotate F9 = { Data.pads+0 , &F75 , Data.formulas+2 };

Mul F75 = { &F77 , Data.formulas+6 };

Neg F77 = { &F79 };

Ratio F79 = { {6000000000000000h,-61} , 0 };

Rotate F10 = { Data.pads+0 , &F81 , Data.formulas+2 };

Mul F81 = { &F83 , Data.formulas+6 };

Neg F83 = { &F85 };

Ratio F85 = { {4000000000000000h,-60} , 0 };

Rotate F11 = { Data.pads+0 , &F87 , Data.formulas+2 };

Mul F87 = { &F89 , Data.formulas+6 };

Neg F89 = { &F91 };

Ratio F91 = { {5000000000000000h,-60} , 0 };

Rotate F12 = { Data.pads+0 , &F93 , Data.formulas+2 };

Mul F93 = { &F95 , Data.formulas+6 };

Neg F95 = { &F97 };

Ratio F97 = { {6000000000000000h,-60} , 0 };

Rotate F13 = { Data.pads+0 , &F99 , Data.formulas+2 };

Mul F99 = { &F101 , Data.formulas+6 };

Neg F101 = { &F103 };

Ratio F103 = { {7000000000000000h,-60} , 0 };

Rotate F14 = { Data.pads+0 , &F105 , Data.formulas+2 };

Mul F105 = { &F107 , Data.formulas+6 };

Neg F107 = { &F109 };

Ratio F109 = { {4000000000000000h,-59} , 0 };

Rotate F15 = { Data.pads+0 , &F111 , Data.formulas+2 };

Mul F111 = { &F113 , Data.formulas+6 };

Neg F113 = { &F115 };

Ratio F115 = { {4800000000000000h,-59} , 0 };

Rotate F16 = { Data.pads+0 , &F117 , Data.formulas+2 };

Mul F117 = { &F119 , Data.formulas+6 };

Neg F119 = { &F121 };

Ratio F121 = { {5000000000000000h,-59} , 0 };

Rotate F17 = { Data.pads+0 , &F123 , Data.formulas+2 };

Mul F123 = { &F125 , Data.formulas+6 };

Neg F125 = { &F127 };

Ratio F127 = { {5800000000000000h,-59} , 0 };

Rotate F18 = { Data.pads+0 , &F129 , Data.formulas+2 };

Mul F129 = { &F131 , Data.formulas+6 };

Neg F131 = { &F133 };

Ratio F133 = { {6000000000000000h,-59} , 0 };

Rotate F19 = { Data.pads+0 , &F135 , Data.formulas+2 };

Mul F135 = { &F137 , Data.formulas+6 };

Neg F137 = { &F139 };

Ratio F139 = { {6800000000000000h,-59} , 0 };

Rotate F20 = { Data.pads+0 , &F141 , Data.formulas+2 };

Mul F141 = { &F143 , Data.formulas+6 };

Neg F143 = { &F145 };

Ratio F145 = { {7000000000000000h,-59} , 0 };

Rotate F21 = { Data.pads+0 , &F147 , Data.formulas+2 };

Mul F147 = { &F149 , Data.formulas+6 };

Neg F149 = { &F151 };

Ratio F151 = { {7800000000000000h,-59} , 0 };

StepOf F22 = { { Data.formulas+2 , Data.formulas+7 , Data.formulas+8 , Data.formulas+9 , Data.formulas+10 , Data.formulas+11 , Data.formulas+12 , Data.formulas+13 , Data.formulas+14 , Data.formulas+15 , Data.formulas+16 , Data.formulas+17 , Data.formulas+18 , Data.formulas+19 , Data.formulas+20 , Data.formulas+21 } };

Part F23 = { Data.formulas+5 , Data.formulas+4 , &F170 };

Add F170 = { &F171 , Data.pads+3 };

Ratio F171 = { {4000000000000000h,-62} , 0 };

RotateOrt F24 = { &F173 , Data.formulas+23 };

Middle F173 = { Data.formulas+4 , Data.formulas+5 };

Part F25 = { Data.formulas+4 , Data.formulas+5 , &F179 };

Add F179 = { &F180 , Data.pads+3 };

Ratio F180 = { {4000000000000000h,-62} , 0 };

LoopOf F26 = { { Data.pads+0 , Data.formulas+25 } };

StepOf F27 = { { Data.formulas+4 } };

StepOf F28 = { { Data.formulas+23 } };

StepOf F29 = { { Data.formulas+24 } };

StepOf F30 = { { Data.formulas+25 } };

Rotate F31 = { Data.pads+0 , Data.formulas+6 , Data.formulas+5 };

Rotate F32 = { Data.pads+0 , &F192 , Data.formulas+5 };

Mul F192 = { &F194 , Data.formulas+6 };

Ratio F194 = { {4000000000000000h,-61} , 0 };

Rotate F33 = { Data.pads+0 , &F197 , Data.formulas+5 };

Mul F197 = { &F199 , Data.formulas+6 };

Ratio F199 = { {6000000000000000h,-61} , 0 };

Rotate F34 = { Data.pads+0 , &F202 , Data.formulas+5 };

Mul F202 = { &F204 , Data.formulas+6 };

Ratio F204 = { {4000000000000000h,-60} , 0 };

Rotate F35 = { Data.pads+0 , &F207 , Data.formulas+5 };

Mul F207 = { &F209 , Data.formulas+6 };

Ratio F209 = { {5000000000000000h,-60} , 0 };

Rotate F36 = { Data.pads+0 , &F212 , Data.formulas+5 };

Mul F212 = { &F214 , Data.formulas+6 };

Ratio F214 = { {6000000000000000h,-60} , 0 };

Rotate F37 = { Data.pads+0 , &F217 , Data.formulas+5 };

Mul F217 = { &F219 , Data.formulas+6 };

Ratio F219 = { {7000000000000000h,-60} , 0 };

Rotate F38 = { Data.pads+0 , &F222 , Data.formulas+5 };

Mul F222 = { &F224 , Data.formulas+6 };

Ratio F224 = { {4000000000000000h,-59} , 0 };

Rotate F39 = { Data.pads+0 , &F227 , Data.formulas+5 };

Mul F227 = { &F229 , Data.formulas+6 };

Ratio F229 = { {4800000000000000h,-59} , 0 };

Rotate F40 = { Data.pads+0 , &F232 , Data.formulas+5 };

Mul F232 = { &F234 , Data.formulas+6 };

Ratio F234 = { {5000000000000000h,-59} , 0 };

Rotate F41 = { Data.pads+0 , &F237 , Data.formulas+5 };

Mul F237 = { &F239 , Data.formulas+6 };

Ratio F239 = { {5800000000000000h,-59} , 0 };

Rotate F42 = { Data.pads+0 , &F242 , Data.formulas+5 };

Mul F242 = { &F244 , Data.formulas+6 };

Ratio F244 = { {6000000000000000h,-59} , 0 };

Rotate F43 = { Data.pads+0 , &F247 , Data.formulas+5 };

Mul F247 = { &F249 , Data.formulas+6 };

Ratio F249 = { {6800000000000000h,-59} , 0 };

Rotate F44 = { Data.pads+0 , &F252 , Data.formulas+5 };

Mul F252 = { &F254 , Data.formulas+6 };

Ratio F254 = { {7000000000000000h,-59} , 0 };

Rotate F45 = { Data.pads+0 , &F257 , Data.formulas+5 };

Mul F257 = { &F259 , Data.formulas+6 };

Ratio F259 = { {7800000000000000h,-59} , 0 };

StepOf F46 = { { Data.formulas+5 , Data.formulas+31 , Data.formulas+32 , Data.formulas+33 , Data.formulas+34 , Data.formulas+35 , Data.formulas+36 , Data.formulas+37 , Data.formulas+38 , Data.formulas+39 , Data.formulas+40 , Data.formulas+41 , Data.formulas+42 , Data.formulas+43 , Data.formulas+44 , Data.formulas+45 } };

StepOf F47 = { { Data.formulas+3 } };

BLoopOf F48 = { { Data.formulas+22 , Data.formulas+27 , Data.formulas+28 , Data.formulas+29 , Data.formulas+30 , Data.formulas+46 , Data.formulas+47 } };

SolidOf F49 = { Data.formulas+48 };

Loop Contour_baseloop=
 {
  {
   { { {5B40000000000000h,-54} , {4F80000000000000h,-54} , 0 } , False },
   { { {5B40000000000000h,-54} , {4355555555555800h,-55} , 0 } , False }
  },
  0
 };

/*

SmoothDot Contour_baseloop[2]=
 {
  { { 373760 , 325632 } , Smooth::DotSimple },
  { { 373760 , 137899 } , Smooth::DotSimple }
 };

*/

Loop Contour_loop=
 {
  {
   { { {6E00000000000000h,-54} , {4F80000000000000h,-54} , 0 } , True },
   { { {6D315048D81EE000h,-54} , {54F15DCFB8959800h,-54} , 0 } , False },
   { { {6AD70DDC0E92B400h,-54} , {59EABCB3CC316400h,-54} , 0 } , False },
   { { {67251677B3577C00h,-54} , {5DFE733EBE5BA000h,-54} , 0 } , False },
   { { {626CE166D52BA000h,-54} , {60D29F2B679EC800h,-54} , 0 } , False },
   { { {5D167B76480DF400h,-54} , {6228E2FDFC8BC400h,-54} , 0 } , False },
   { { {5797910326862C00h,-54} , {61E3C4F3DAF05000h,-54} , 0 } , False },
   { { {52694BB095F5DC00h,-54} , {600938D9816F2800h,-54} , 0 } , False },
   { { {4DFDE32FF172F800h,-54} , {5CC21CD00E8D0800h,-54} , 0 } , False },
   { { {4AB6C7267E90DC00h,-54} , {5856B44F6A0A2400h,-54} , 0 } , False },
   { { {48DC3B0C250FB000h,-54} , {53286EFCD979D400h,-54} , 0 } , False },
   { { {48971D0203743C00h,-54} , {4DA98489B7F20C00h,-54} , 0 } , False },
   { { {49ED60D498613800h,-54} , {48531E992AD46000h,-54} , 0 } , False },
   { { {4CC18CC141A46000h,-54} , {439AE9884CA88400h,-54} , 0 } , False },
   { { {50D5434C33CE9C00h,-54} , {7FD1E447E2DA9400h,-55} , 0 } , False },
   { { {55CEA230476A6800h,-54} , {7B1D5F6E4FC24400h,-55} , 0 } , False },
   { { {5B40000000000000h,-54} , {7980000000000000h,-55} , 0 } , True },
   { { {5B40000000000000h,-54} , {4795555555555400h,-54} , 0 } , True },
   { { {6E35555555555400h,-54} , {6940000000000000h,-55} , 0 } , True },
   { { {5B40000000000000h,-54} , {4355555555555800h,-55} , 0 } , True },
   { { {5B40000000000000h,-54} , {5900000000000000h,-55} , 0 } , True },
   { { {51170C9E632D0800h,-54} , {5C03A1122E7BB400h,-55} , 0 } , False },
   { { {47CE1738E93D6400h,-54} , {64CC10862FFE6C00h,-55} , 0 } , False },
   { { {4031D38AE0EE9000h,-54} , {7297AC1EFC0EB800h,-55} , 0 } , False },
   { { {75D4142AC16AF800h,-55} , {421B280CD87B6000h,-54} , 0 } , False },
   { { {70D64A29A67EC000h,-55} , {4C11C434464C5C00h,-54} , 0 } , False },
   { { {71D853E912E54000h,-55} , {5654026084E36800h,-54} , 0 } , False },
   { { {78C3F88FB6610C00h,-55} , {5FFFB6FAA3CEA800h,-54} , 0 } , False },
   { { {428052BFE4D69800h,-54} , {683FAD401B296800h,-54} , 0 } , False },
   { { {4AC049055C315800h,-54} , {6E5E03B824CF7800h,-54} , 0 } , False },
   { { {546BFD9F7B1C9400h,-54} , {71D3D60B768D6000h,-54} , 0 } , False },
   { { {5EAE3BCBB9B3A400h,-54} , {7254DAEB2CC0A000h,-54} , 0 } , False },
   { { {68A4D7F32784A400h,-54} , {6FD5F5EA9F4A8400h,-54} , 0 } , False },
   { { {717429F081F8A000h,-54} , {6A8E2C751F117000h,-54} , 0 } , False },
   { { {7859F7BCE800CC00h,-54} , {62F1E8C716C29800h,-54} , 0 } , False },
   { { {7CBE2F76E8C22800h,-54} , {59A8F3619CD2F400h,-54} , 0 } , False },
   { { {7E40000000000000h,-54} , {4F80000000000000h,-54} , 0 } , True }
  },
  0
 };

/*

SmoothDot Contour_loop[37]=
 {
  { { 450560 , 325632 } , Smooth::DotBreak },
  { { 447253 , 347926 } , Smooth::DotSimple },
  { { 437617 , 368300 } , Smooth::DotSimple },
  { { 422481 , 384999 } , Smooth::DotSimple },
  { { 403150 , 396586 } , Smooth::DotSimple },
  { { 381288 , 402062 } , Smooth::DotSimple },
  { { 358777 , 400956 } , Smooth::DotSimple },
  { { 337557 , 393364 } , Smooth::DotSimple },
  { { 319454 , 379938 } , Smooth::DotSimple },
  { { 306028 , 361835 } , Smooth::DotSimple },
  { { 298436 , 340615 } , Smooth::DotSimple },
  { { 297330 , 318104 } , Smooth::DotSimple },
  { { 302806 , 296242 } , Smooth::DotSimple },
  { { 314393 , 276911 } , Smooth::DotSimple },
  { { 331092 , 261775 } , Smooth::DotSimple },
  { { 351466 , 252139 } , Smooth::DotSimple },
  { { 373760 , 248832 } , Smooth::DotBreak },
  { { 373760 , 293205 } , Smooth::DotBreak },
  { { 451413 , 215552 } , Smooth::DotBreak },
  { { 373760 , 137899 } , Smooth::DotBreak },
  { { 373760 , 182272 } , Smooth::DotBreak },
  { { 332145 , 188445 } , Smooth::DotSimple },
  { { 294113 , 206433 } , Smooth::DotSimple },
  { { 262941 , 234685 } , Smooth::DotSimple },
  { { 241313 , 270771 } , Smooth::DotSimple },
  { { 231090 , 311580 } , Smooth::DotSimple },
  { { 233155 , 353600 } , Smooth::DotSimple },
  { { 247328 , 393211 } , Smooth::DotSimple },
  { { 272389 , 427003 } , Smooth::DotSimple },
  { { 306181 , 452064 } , Smooth::DotSimple },
  { { 345792 , 466237 } , Smooth::DotSimple },
  { { 387812 , 468302 } , Smooth::DotSimple },
  { { 428621 , 458079 } , Smooth::DotSimple },
  { { 464707 , 436451 } , Smooth::DotSimple },
  { { 492959 , 405279 } , Smooth::DotSimple },
  { { 510947 , 367247 } , Smooth::DotSimple },
  { { 517120 , 325632 } , Smooth::DotBreak }
 };

*/

