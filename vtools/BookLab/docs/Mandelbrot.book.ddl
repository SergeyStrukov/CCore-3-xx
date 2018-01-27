/* Mandelbrot.book.ddl */

include <Mandelbrot.style.ddl>

scope Pages {

Page page1 = { Pages#PageName , {
{ &o1 }
,{ &o2 }
,{ &o3 }
,{ &o4 }
,{ &o5 }
,{ &o6 }
,{ &o7 }
,{ &o8 }
,{ &o9 }
,{ &o10 }
,{ &o11 }
,{ &o12 }
,{ &o13 }
,{ &o14 }
,{ &o15 }
,{ &o16 }
,{ &o17 }
,{ &o18 }
,{ &o19 }
} };

Text o1 = { {
{"Mandelbrot"}
,{"scope"}
} , &fmt_h1 , &align_h1 } ;



Text o2 = { {
{"Introduction"}
} , &fmt_h2 , &align_h2 } ;



Bitmap o3 = { "img/Mandelbrot" + '.bitmap'  };



Text o4 = { {
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
,{"Benoit B. Mandelbrot",&fmt_h}
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
}} ;



Text o5 = { {
{"Navigation"}
} , &fmt_h2 , &align_h2 } ;



Text o6 = { {
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
}} ;



Text o7 = { {
{"Software"}
,{"options"}
} , &fmt_h2 , &align_h2 } ;



Text o8 = { {
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
}} ;



Bitmap o9 = { "img/Colors" + '.bitmap'  };



Text o10 = { {
{"There"}
,{"are"}
,{"several"}
,{"configuration"}
,{"options"}
,{"on"}
,{"this"}
,{"dialog."}
}} ;



Text o11 = { {
{"The"}
,{"spinor"}
,{"Cap",&fmt_b}
,{"controls"}
,{"the"}
,{"calculation"}
,{"depth."}
}} ;



Text o12 = { {
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
}} ;



Text o13 = { {
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
}} ;



Text o14 = { {
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
}} ;



Text o15 = { {
{"System"}
,{"requirements"}
} , &fmt_h2 , &align_h2 } ;



Text o16 = { {
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
}} ;



Text o17 = { {
{"Copyright"}
,{"notes"}
} , &fmt_h2 , &align_h2 } ;



Text o18 = { {
{"Copyright"}
,{"(c)"}
,{"2017"}
,{"Sergey"}
,{"Strukov."}
,{"All"}
,{"rights"}
,{"reserved."}
}} ;



Text o19 = { {
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
}} ;



} // scope Pages

Book Data = { Pages#BookName , {&Pages#page1} , Pages#Back , Pages#Fore } ;

