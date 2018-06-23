/* test.book.ddl */

include <test.style.ddl>

scope Pages {

Page page1 = { Pages#PageName , {
{ &o1 }
,{ &o2 }
,{ &o3 }
,{ &o4 }
,{ &o5 }
} };

Text o1 = { {
{"Arrays"}
} , &fmt_h2 , &align_h2 } ;



Text o2 = { {
{"Files"}
,{"CCore/inc/Array.h",&fmt_b}
,{"CCore/src/Array.cpp",&fmt_b}
}} ;



Text o3 = { {
{"Subfolders"}
,{"CCore/inc/array",&fmt_b}
,{"CCore/src/array",&fmt_b}
}} ;



Text o4 = { {
{"Helpers"}
} , &fmt_h3 , &align_h3 } ;



Text o5 = { {
{"There"}
,{"are"}
,{"several"}
,{"types"}
,{"that"}
,{"are"}
,{"used"}
,{"to"}
,{"specify"}
,{"the"}
,{"constructor"}
,{"behavior."}
}} ;



} // scope Pages

Book Data = { Pages#BookName , {&Pages#page1} , Pages#Back , Pages#Fore } ;

