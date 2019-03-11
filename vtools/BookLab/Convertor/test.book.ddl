/* test.book.ddl */

include <pretext:/Book1.ddl>

scope Pages {

/* defaults */

Point DefaultInner = { 10 , 2 } ;

Point DefaultOuter = { 10 , 10 } ;

Coord DefaultBulletSpace = 10 ;

Coord DefaultItemSpace = 5 ;

Format DefaultBulletFormat = { & font_text } ;

Format DefaultFormat = { & font_text } ;

MultiLine DefaultPlacement = { { 12 , 10 } , { 2 , 1 } } ;

/* format */

Font font_text = { "Bookman Old Style" , 20 } ;

 // h1

Font font_h1 = { "Bookman Old Style" , 40 , True } ;

Format fmt_h1 = { & font_h1 , 0A9A9A9h , 0FFh } ;

OneLine align_h1 = { OneLine#Center } ;

 // h2

Font font_h2 = { "Bookman Old Style" , 30 } ;

Format fmt_h2 = { & font_h2 , 0F5DEB3h , 06400h } ;

OneLine align_h2 = { OneLine#Left } ;

/* content */

Page content = { "Content" ,

{
 { & list }
}

} ;

TextList list = {

{

{ "1." , { { & item1 , null , { 0 , 0 } , { 0 , 0 } } } }
,
{ "2." , { { & item2 , null , { 0 , 0 } , { 0 , 0 } } } }
,
{ "3." , { { & item3 , null , { 0 , 0 } , { 0 , 0 } } } }

}

} ;

OneLine align_item = { OneLine#Left } ;

Text item1 = { { { "item1" , null , &link1 } } , null , &align_item } ;

Text item2 = { { { "item2" , null , null } } , null , &align_item } ;

Text item3 = { { { "item3" , null , null } } , null , &align_item } ;

Link link1 = { &page1 } ;

include <test.bookinc.ddl>

}

Book Data = { .title = "CCore 3-xx" , .start = & Pages#content , .back = 0FFEFD5h , .fore = 00h } ;





