/* main.book.ddl */

include <test.style.ddl>

scope Pages {

/* page1 */

Page page1 = { Pages#PageName , {
{ &bmp1 } , { &o1 }
} };

TextList o1 = { {{"1.",{
{ &o2 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o4 , null , {0,0} , {0,0} }
}}
} };

Text o2 = { {
{"page1",null,&page2}
} , &fmt_li , &align_li } ;

Link link1 = {&page2,{0}} ;

Text o4 = { {
{"page2",null,&page3}
} , &fmt_li , &align_li } ;

Link link2 = {&page3,{0}} ;

Bitmap bmp1 = { "img/Mandelbrot" + '.zipmap'  };

/* page2 */

Page page2 = { .name = Pages#PageName + " : page1" , .list = {
{ &o5 }
} , .up = &page1 , .next = &page3 };

Text o5 = { {
{"This"}
,{"is"}
,{"the"}
,{"page"}
,{"number"}
,{"1."}
}} ;

/* page3 */

Page page3 = { .name = Pages#PageName + " : page2" , .list = {
{ &o6 }
} , .up = &page1 , .prev = &page2 };

Text o6 = { {
{"This"}
,{"is"}
,{"the"}
,{"page"}
,{"number"}
,{"2."}
}} ;

} // scope Pages

Book Data = { Pages#BookName , &Pages#page1 , Pages#Back , Pages#Fore } ;

