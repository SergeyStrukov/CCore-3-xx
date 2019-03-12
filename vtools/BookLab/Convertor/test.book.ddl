/* test.book.ddl */

include <pretext:/Book1.ddl>

scope Pages {

/* defaults */

Point DefaultInner = { 10 , 2 } ;

Point DefaultOuter = { 10 , 10 } ;

Coord DefaultBulletSpace = 10 ;

Coord DefaultItemSpace = 5 ;

Format DefaultBulletFormat = DefaultFormat ;

Format DefaultFormat = fmt_text ;

MultiLine DefaultPlacement = { { 12 , 10 } , { 2 , 1 } } ;

/* format */

 // font

text face = "Bookman Old Style" ;

text fixed = "Fixed" ;

 // text

Font font_text = { face , 20 } ;

Format fmt_text = { & font_text } ;

Point inner_text = DefaultInner ;

Point outer_text = DefaultOuter ;

VColor back_text = NoColor ;

MultiLine align_text = DefaultPlacement ;

Font font_text_b = font_text { .bold = True  } ;

Format fmt_text_b = { & font_text_b } ;

 // text_Files

Font font_text_Files = { fixed , 22 } ;

Format fmt_text_Files = { & font_text_Files , 0FFFFh } ;

Point inner_text_Files = DefaultInner ;

Point outer_text_Files = DefaultOuter ;

VColor back_text_Files = NoColor ;

OneLine align_text_Files = { OneLine#Left } ;

Font font_text_Files_b = font_text_Files { .bold = True  } ;

Format fmt_text_Files_b = { & font_text_Files_b , 0FFFFh } ;

 // h1

Font font_h1 = { face , 50 , True } ;

Format fmt_h1 = { & font_h1 , 0A9A9A9h , 0FFh } ; 

Point inner_h1 = DefaultInner ;

Point outer_h1 = DefaultOuter ;

VColor back_h1 = NoColor ;

OneLine align_h1 = { OneLine#Center } ;

 // h2

Font font_h2 = { face , 36 } ;

Format fmt_h2 = { & font_h2 , 0F5DEB3h , 06400h } ;

Point inner_h2 = DefaultInner ;

Point outer_h2 = DefaultOuter ;

VColor back_h2 = NoColor ;

OneLine align_h2 = { OneLine#Left } ;

 // h3

Font font_h3 = { face , 30 } ;

Format fmt_h3 = { & font_h3 , NoColor , 06400h , Format#Underline } ;

Point inner_h3 = DefaultInner ;

Point outer_h3 = DefaultOuter ;

VColor back_h3 = NoColor ;

OneLine align_h3 = { OneLine#Left } ;

 // h4

Font font_h4 = { face , 24 } ;

Format fmt_h4 = { & font_h4 , NoColor , 0FFh , Format#Underline } ;

Point inner_h4 = DefaultInner ;

Point outer_h4 = DefaultOuter ;

VColor back_h4 = NoColor ;

OneLine align_h4 = { OneLine#Left } ;

 // list

Format fmt_list = fmt_text ;

Point inner_list = { 0 , 0 } ;

Point outer_list = { 40 , 0 } ;

VColor back_list = NoColor ;

OneLine align_list = { OneLine#Left } ;

Point ItemInner = { 2 , 2 } ;

Point ItemOuter = { 0 , 0 } ;

Format fmt_list_b = fmt_text_b ;

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

Text item1 = { { { "item1" , null , &link1 } } , null , & align_item } ;

Text item2 = { { { "item2" , null , null } } , null , & align_item } ;

Text item3 = { { { "item3" , null , null } } , null , & align_item } ;

Link link1 = { & Page1#page } ;

scope Page1 {

include <test.bookinc.ddl>

}

}

Book Data = { .title = "CCore 3-xx" , .start = & Pages#Page1#page , .back = 0FFEFD5h , .fore = 00h } ;





