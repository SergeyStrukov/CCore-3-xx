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

 // color names

VColor White = 0FFFFFFh ;

VColor Black = 0 ;

VColor Red = 0FF0000h ;

VColor Blue = 0FFh ;

VColor DarkGreen = 06400h ;

VColor Aqua = 0FFFFh ;

 // colors

VColor vc_h1 = Blue ;

VColor vc_h1_back = 0A9A9A9h ;

VColor vc_h2 = DarkGreen ;

VColor vc_h2_back = 0F5DEB3h ;

VColor vc_h3 = DarkGreen ;

VColor vc_h4 = Blue ;

VColor vc_a = Blue ;

VColor vc_Alert = Red ;

VColor vc_Hint = Blue ;

VColor vc_Att = Blue ;

VColor vc_Files = Aqua ;

 // font faces

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

Font font_text_i = font_text { .italic = True  } ;

Format fmt_text_i = { & font_text_i } ;

Format fmt_text_u = fmt_text { .effect=Format#Underline } ;

 // text_Files

Font font_text_Files = { fixed , 22 } ;

Format fmt_text_Files = { & font_text_Files , vc_Files } ;

Point inner_text_Files = DefaultInner ;

Point outer_text_Files = DefaultOuter ;

VColor back_text_Files = NoColor ;

OneLine align_text_Files = { OneLine#Left } ;

Font font_text_Files_b = font_text_Files { .bold = True  } ;

Format fmt_text_Files_b = fmt_text_Files { .font = & font_text_Files_b } ;

 // text_Alert

Format fmt_text_Alert = fmt_text { .fore = vc_Alert } ;

 // text_Hint

Format fmt_text_Hint = fmt_text { .fore = vc_Hint } ;

 // text_Att

Format fmt_text_Att = fmt_text { .fore = vc_Att } ;

 // h1

Font font_h1 = { face , 50 , True } ;

Format fmt_h1 = { & font_h1 , vc_h1_back , vc_h1 } ; 

Point inner_h1 = DefaultInner ;

Point outer_h1 = DefaultOuter ;

VColor back_h1 = NoColor ;

OneLine align_h1 = { OneLine#Center } ;

 // h2

Font font_h2 = { face , 36 } ;

Format fmt_h2 = { & font_h2 , vc_h2_back , vc_h2 } ;

Point inner_h2 = DefaultInner ;

Point outer_h2 = DefaultOuter ;

VColor back_h2 = NoColor ;

OneLine align_h2 = { OneLine#Left } ;

Format fmt_h2_a = fmt_h2 { .fore = vc_a , .effect = Format#Underline } ;

 // h3

Font font_h3 = { face , 30 } ;

Format fmt_h3 = { & font_h3 , NoColor , vc_h3 , Format#Underline } ;

Point inner_h3 = DefaultInner ;

Point outer_h3 = DefaultOuter ;

VColor back_h3 = NoColor ;

OneLine align_h3 = { OneLine#Left } ;

Font font_h3_i = font_h3 { .italic = True } ;

Format fmt_h3_i =  fmt_h3 { .font = & font_h3_i } ;

Font font_h3_b = font_h3 { .bold = True } ;

Format fmt_h3_b =  fmt_h3 { .font = & font_h3_b } ;

 // h4

Font font_h4 = { face , 24 } ;

Format fmt_h4 = { & font_h4 , NoColor , vc_h4 , Format#Underline } ;

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

Format fmt_list_a = fmt_list { .fore = vc_a , .effect = Format#Underline } ;

Format fmt_list_Alert = fmt_list { .fore = vc_Alert } ;

Font font_Cmd = { fixed , 22 } ;

Format fmt_list_Cmd = { &font_Cmd , White , Black } ;

 // img

Point inner_img = DefaultInner ;

Point outer_img = DefaultOuter ;

VColor back_img = NoColor ;

 // a

Format fmt_text_a = fmt_text { .fore = vc_a , .effect = Format#Underline } ;

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
,
{ "4." , { { & item4 , null , { 0 , 0 } , { 0 , 0 } } } }

}

} ;

OneLine align_item = { OneLine#Left } ;

Text item1 = { { { "Abort" , null , &link1 } } , null , & align_item } ;

Text item2 = { { { "Arrays" , null , &link2 } } , null , & align_item } ;

Text item3 = { { { "Lists" , null , &link3 } } , null , & align_item } ;

Text item4 = { { { "EllipticPi" , null , &link4 } } , null , & align_item } ;

Link link1 = { &page_Abort#page } ;

Link link2 = { &page_Arrays#page } ;

Link link3 = { &page_Lists#page } ;

Link link4 = { &page_EllipticPi#page } ;

include <test.bookinc.ddl>

}

Book Data = { .title = "CCore 3-xx" , .start = & Pages#content , .back = 0FFEFD5h , .fore = 00h } ;





