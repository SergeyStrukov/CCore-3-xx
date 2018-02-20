/* test.book.ddl */

include <test.style.ddl>

scope Pages {

/* page1 */

Page page1 = { Pages#PageName , {
{ &o1 }
} };

TextList o1 = { {{"1.",{
{ &o2 , null , {0,0} , {0,0} }
}}
,{"2.",{
{ &o4 , null , {0,0} , {0,0} }
}}
} };

Text o2 = { {
{"page1",null,&link1}
} , &fmt_li , &align_li } ;

Link link1 = {1,0} ;

Text o4 = { {
{"page2",null,&link2}
} , &fmt_li , &align_li } ;

Link link2 = {2,0} ;

/* page2 */

Page page2 = { .name = Pages#PageName + " : page1" , .list = {
{ &o5 }
} , .top = &page1 , .next = &page3 };

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
} , .top = &page1 , .prev = &page2 };

Text o6 = { {
{"This"}
,{"is"}
,{"the"}
,{"page"}
,{"number"}
,{"2."}
}} ;

} // scope Pages

Book Data = { Pages#BookName , {&Pages#page1,&Pages#page2,&Pages#page3} , Pages#Back , Pages#Fore } ;

