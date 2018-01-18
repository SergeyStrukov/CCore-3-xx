/* Mandelbrot.book.ddl */

include <Mandelbrot.style.ddl>

scope Pages {

Text text1 = { {
{"Mandelbrot"}
,{"scope"}
} , &fmt_h1 , &align_h1 } ;

Text text2 = { {
{"Introduction"}
} , &fmt_h2 , &align_h2 } ;

Bitmap text3 = {
};

Text text4 = { {
{"Mandelbrot",&fmt_b}
,{"scope",&fmt_b}
,{"(MScope.exe)"}
,{"is"}
,{"a"}
,{"software"}
,{"to"}
,{"display"}
,{"the"}
,{"Mandelbrot"}
,{"Set."}
,{"The"}
,{"Mandelbrot"}
,{"Set"}
,{"is"}
,{"a"}
,{"famous"}
,{"mathematical"}
,{"fractal"}
,{"set,"}
,{"it"}
,{"has"}
,{"been"}
,{"discovered"}
,{"by"}
,{"Benoit",&fmt_u}
,{"B.",&fmt_u}
,{"Mandelbrot",&fmt_u}
,{"."}
,{"The"}
,{"Mandelbrot"}
,{"Set"}
,{"itself"}
,{"cannot"}
,{"be"}
,{"calculated,"}
,{"because"}
,{"it"}
,{"requires"}
,{"infinite"}
,{"number"}
,{"of"}
,{"precise"}
,{"iteration"}
,{"per"}
,{"point."}
,{"But"}
,{"we"}
,{"can"}
,{"calculate"}
,{"and"}
,{"paint"}
,{"the"}
,{"outer"}
,{"of"}
,{"it"}
,{"up"}
,{"to"}
,{"some"}
,{"level."}
,{"The"}
,{"rest"}
,{"of"}
,{"the"}
,{"painted"}
,{"area"}
,{"is"}
,{"black"}
,{"and"}
,{"contains"}
,{"inside"}
,{"the"}
,{"true"}
,{"Mandelbrot"}
,{"Set,"}
,{"but"}
,{"we"}
,{"don't"}
,{"know"}
,{"which"}
,{"part."}
,{"The"}
,{"more"}
,{"deeper"}
,{"we"}
,{"calculate,"}
,{"the"}
,{"more"}
,{"closer"}
,{"we"}
,{"are"}
,{"coming"}
,{"to"}
,{"the"}
,{"true"}
,{"border."}
,{"You"}
,{"can"}
,{"select"}
,{"the"}
,{"depth"}
,{"in"}
,{"the"}
,{"Options",&fmt_i}
,{"menu."}
,{"You"}
,{"can"}
,{"also"}
,{"adjust"}
,{"the"}
,{"color"}
,{"palette"}
,{"to"}
,{"paint"}
,{"the"}
,{"outer"}
,{"part."}
} } ;

Text text5 = { {
{"Navigation"}
} , &fmt_h2 , &align_h2 } ;

Text text6 = { {
{"To"}
,{"move"}
,{"the"}
,{"picture"}
,{"drag"}
,{"it"}
,{"by"}
,{"the"}
,{"mouse."}
,{"To"}
,{"zoom/unzoom"}
,{"the"}
,{"picture"}
,{"use"}
,{"the"}
,{"mouse"}
,{"wheel."}
,{"To"}
,{"return"}
,{"to"}
,{"the"}
,{"top"}
,{"view"}
,{"use"}
,{"the"}
,{"key"}
,{"Home",&fmt_b}
,{"."}
} } ;

Text text7 = { {
{"Software"}
,{"options"}
} , &fmt_h2 , &align_h2 } ;

Text text8 = { {
{"The"}
,{"menu"}
,{"Options",&fmt_i}
,{"contains"}
,{"three"}
,{"submenus:"}
,{"Global",&fmt_i}
,{","}
,{"Application",&fmt_i}
,{","}
,{"Colors",&fmt_i}
,{"."}
,{"The"}
,{"first"}
,{"submenu"}
,{"opens"}
,{"the"}
,{"dialog"}
,{"to"}
,{"edit"}
,{"preferences,"}
,{"shared"}
,{"by"}
,{"all"}
,{"applications."}
,{"The"}
,{"second"}
,{"submenu"}
,{"opens"}
,{"the"}
,{"dialog"}
,{"to"}
,{"edit"}
,{"preferences,"}
,{"specific"}
,{"to"}
,{"the"}
,{"application."}
,{"The"}
,{"submenu"}
,{"Colors",&fmt_i}
,{"opens"}
,{"the"}
,{"dialog,"}
,{"used"}
,{"to"}
,{"change"}
,{"the"}
,{"color"}
,{"palette"}
,{"and"}
,{"the"}
,{"depth"}
,{"of"}
,{"the"}
,{"calculation."}
} } ;

Bitmap text9 = {
};

Text text10 = { {
{"There"}
,{"are"}
,{"several"}
,{"configuration"}
,{"options"}
,{"on"}
,{"this"}
,{"dialog."}
} } ;

Text text11 = { {
{"The"}
,{"spinor"}
,{"Cap",&fmt_b}
,{"controls"}
,{"the"}
,{"calculation"}
,{"depth."}
} } ;

Text text12 = { {
{"The"}
,{"spinor"}
,{"Len",&fmt_b}
,{"determines"}
,{"the"}
,{"number"}
,{"of"}
,{"colors"}
,{"between"}
,{"pivot"}
,{"colors."}
,{"The"}
,{"full"}
,{"color"}
,{"palette"}
,{"is"}
,{"built"}
,{"upon"}
,{"the"}
,{"pivot"}
,{"color"}
,{"list."}
,{"Between"}
,{"two"}
,{"consecutive"}
,{"pivot"}
,{"colors"}
,{"a"}
,{"number"}
,{"of"}
,{"intermediate"}
,{"colors"}
,{"are"}
,{"inserted,"}
,{"using"}
,{"progressive"}
,{"blending"}
,{"of"}
,{"edge"}
,{"colors."}
,{"The"}
,{"pivot"}
,{"list"}
,{"is"}
,{"cycled,"}
,{"when"}
,{"needed,"}
,{"except"}
,{"the"}
,{"first"}
,{"pivot"}
,{"color,"}
,{"which"}
,{"is"}
,{"usually"}
,{"Blue",&fmt_b}
,{"."}
} } ;

Text text13 = { {
{"The"}
,{"full"}
,{"color"}
,{"palette"}
,{"is"}
,{"shown"}
,{"on"}
,{"the"}
,{"bottom"}
,{"part"}
,{"of"}
,{"the"}
,{"dialog."}
} } ;

Text text14 = { {
{"The"}
,{"list"}
,{"of"}
,{"pivot"}
,{"colors"}
,{"is"}
,{"presented"}
,{"in"}
,{"the"}
,{"middle"}
,{"left"}
,{"part"}
,{"of"}
,{"the"}
,{"dialog."}
,{"You"}
,{"can"}
,{"insert"}
,{"a"}
,{"new"}
,{"element"}
,{"or"}
,{"delete"}
,{"an"}
,{"existing"}
,{"element"}
,{"from"}
,{"the"}
,{"list"}
,{"using"}
,{"buttons"}
,{"or"}
,{"keys"}
,{"Insert",&fmt_b}
,{"and"}
,{"Delete",&fmt_b}
,{"."}
,{"You"}
,{"can"}
,{"also"}
,{"change"}
,{"the"}
,{"selected"}
,{"color"}
,{"using"}
,{"RGB"}
,{"spinors"}
,{"or"}
,{"the"}
,{"color"}
,{"cube."}
} } ;

Text text15 = { {
{"System"}
,{"requirements"}
} , &fmt_h2 , &align_h2 } ;

Text text16 = { {
{"To"}
,{"run"}
,{"this"}
,{"software"}
,{"you"}
,{"will"}
,{"need"}
,{"a"}
,{"quit"}
,{"fast"}
,{"PC"}
,{"with"}
,{"GPU"}
,{"(or"}
,{"another"}
,{"OpenCL"}
,{"accelerator)."}
,{"Operating"}
,{"system"}
,{"Windows"}
,{"10"}
,{"is"}
,{"required,"}
,{"but"}
,{"you"}
,{"may"}
,{"try"}
,{"earlier"}
,{"versions"}
,{"(not"}
,{"guaranteed)."}
,{"To"}
,{"perform"}
,{"calculation"}
,{"an"}
,{"OpenCL"}
,{"provider"}
,{"is"}
,{"required."}
,{"It"}
,{"is"}
,{"installed"}
,{"automatically"}
,{"with"}
,{"modern"}
,{"GPU"}
,{"drivers."}
} } ;

Text text17 = { {
{"Copyright"}
,{"notes"}
} , &fmt_h2 , &align_h2 } ;

Text text18 = { {
{"Copyright"}
,{"(c)"}
,{"2017"}
,{"Sergey"}
,{"Strukov."}
,{"All"}
,{"rights"}
,{"reserved."}
} } ;

Text text19 = { {
{"This"}
,{"software"}
,{"is"}
,{"distributed"}
,{"under"}
,{"the"}
,{"commercial"}
,{"license,"}
,{"see"}
,{"the"}
,{"License.txt",&fmt_b}
,{"for"}
,{"details."}
} } ;

Page page1 = { Pages#PageName , {
{ &text1 }
,{ &text2 }
,{ &text3 }
,{ &text4 }
,{ &text5 }
,{ &text6 }
,{ &text7 }
,{ &text8 }
,{ &text9 }
,{ &text10 }
,{ &text11 }
,{ &text12 }
,{ &text13 }
,{ &text14 }
,{ &text15 }
,{ &text16 }
,{ &text17 }
,{ &text18 }
,{ &text19 }
} };

} // scope Pages

Book Data = { Pages#BookName , {&Pages#page1} , Pages#Back , Pages#Fore } ;