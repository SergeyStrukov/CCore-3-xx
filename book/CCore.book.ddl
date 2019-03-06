include <pretext:/Book1.ddl>

Book Data = { .title = "CCore 3-xx" , .start = & #Doc#Pages#Content#cover , .back = 0FFEFD5h , .fore = 00h } ;

scope Doc {

scope Pages {

Point DefaultInner = { 10 , 2 } ;

Point DefaultOuter = { 10 , 10 } ;

Coord DefaultBulletSpace = 10 ;

Coord DefaultItemSpace = 5 ;

Format DefaultBulletFormat = { & font_text , NoColor , NoColor , 0 } ;

Format DefaultFormat = { & font_text , NoColor , NoColor , 0 } ;

MultiLine DefaultPlacement = { { 12 , 10 } , { 2 , 1 } } ;

scope Content {

Point DefaultInner = { 10 , 10 } ;

Point DefaultOuter = { 0 , 0 } ;

Format DefaultFormat = { & font_text , NoColor , NoColor , 0 } ;

MultiLine DefaultPlacement = { { 1 , 1 } , { 2 , 1 } } ;

Font font_text = { "Bookman Old Style" , 20 , False , False , 0 } ;

Format fmt_text = { & font_text , NoColor , NoColor , 0 } ;

Font font_title = { "Bookman Old Style" , 80 , False , False , 0 } ;

Format fmt_title = { & font_title , NoColor , NoColor , 0 } ;

Font font_h1 = { "Bookman Old Style" , 32 , False , False , 0 } ;

Format fmt_h1 = { & font_h1 , NoColor , 0FFh , 0 } ;

Font font_list = { "Bookman Old Style" , 20 , False , False , 0 } ;

Format fmt_list = { & font_list , NoColor , NoColor , 0 } ;

Format fmt_underline = { & font_list , NoColor , NoColor , 1 } ;

Font font_list2 = { "Bookman Old Style" , 18 , False , False , 0 } ;

Format fmt_list2 = { & font_list2 , NoColor , NoColor , 0 } ;

Page cover = { "Cover" ,
{
{ & ANONYM1 , null , { 10 , 50 } , DefaultOuter , NoColor }
,{ & ANONYM2 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM3 , null , { 0 , 200 } , DefaultOuter , NoColor }
,{ & ANONYM4 , null , { 10 , 50 } , DefaultOuter , NoColor }
,{ & ANONYM5 , null , DefaultInner , DefaultOuter , NoColor }
,{ & ANONYM6 , null , { 50 , 20 } , DefaultOuter , NoColor }
}
, 0FFFFFFh , 00h , null , null , & content } ;

Text ANONYM1 = {
{
{ "CCore" , null , null }
}
, & fmt_title , & ANONYM7 } ;

Text ANONYM2 = {
{
{ "multi-target" , null , null }
,{ "development" , null , null }
,{ "platform" , null , null }
,{ "with" , null , null }
,{ "real-time" , null , null }
,{ "support" , null , null }
}
, &DefaultFormat , & ANONYM8 } ;

Text ANONYM3 = {
{
}
, &DefaultFormat , &DefaultPlacement } ;

Text ANONYM4 = {
{
{ "Sergey" , null , null }
,{ "Strukov" , null , null }
,{ "2019," , null , null }
,{ "version" , null , null }
,{ "3-xx" , null , null }
}
, &DefaultFormat , & ANONYM9 } ;

Text ANONYM5 = {
{
{ "Copyright" , null , null }
,{ "©" , null , null }
,{ "2019" , null , null }
,{ "Sergey" , null , null }
,{ "Strukov." , null , null }
,{ "All" , null , null }
,{ "rights" , null , null }
,{ "reserved." , null , null }
}
, &DefaultFormat , & ANONYM10 } ;

Text ANONYM6 = {
{
{ "This" , null , null }
,{ "document" , null , null }
,{ "is" , null , null }
,{ "public." , null , null }
,{ "You" , null , null }
,{ "may" , null , null }
,{ "freely" , null , null }
,{ "distribute" , null , null }
,{ "it" , null , null }
,{ "free" , null , null }
,{ "of" , null , null }
,{ "charge" , null , null }
,{ "as" , null , null }
,{ "far" , null , null }
,{ "as" , null , null }
,{ "it's" , null , null }
,{ "content," , null , null }
,{ "copyright" , null , null }
,{ "notice" , null , null }
,{ "and" , null , null }
,{ "authorship" , null , null }
,{ "is" , null , null }
,{ "unchanged." , null , null }
}
, &DefaultFormat , &DefaultPlacement } ;

OneLine ANONYM7 = { 2 } ;

OneLine ANONYM8 = { 2 } ;

OneLine ANONYM9 = { 2 } ;

OneLine ANONYM10 = { 2 } ;

Link test = { null , {  } } ;

Page content = { "Content" ,
{
{ & ANONYM11 , null , { 10 , 30 } , DefaultOuter , NoColor }
,{ & list , null , DefaultInner , DefaultOuter , NoColor }
}
, NoColor , NoColor , null , & cover , null } ;

Text ANONYM11 = {
{
{ "Table" , null , null }
,{ "of" , null , null }
,{ "content" , null , null }
}
, & fmt_h1 , & ANONYM12 } ;

OneLine ANONYM12 = { 2 } ;

TextList list = {
{
{ "1." ,
{
{ & ANONYM13 , null , { 0 , 0 } , { 0 , 0 } , NoColor }
}
}
,{ "2." ,
{
{ & ANONYM14 , null , { 0 , 0 } , { 0 , 0 } , NoColor }
}
}
,{ "3." ,
{
{ & ANONYM15 , null , { 0 , 0 } , { 0 , 0 } , NoColor }
}
}
}
, & fmt_list , 10 , 10 } ;

Text ANONYM13 = {
{
{ "Introduction." , & fmt_underline , & #Doc#Pages#link_Introduction }
}
, & fmt_list , & ANONYM16 } ;

Text ANONYM14 = {
{
{ "Installation." , & fmt_underline , null }
}
, & fmt_list , & ANONYM17 } ;

Collapse ANONYM15 = { "Preliminary considerations" ,
{
{ & list3 , null , { 5 , 5 } , { 0 , 0 } , NoColor }
}
, & fmt_list , False , False } ;

OneLine ANONYM16 = { 0 } ;

OneLine ANONYM17 = { 0 } ;

TextList list3 = {
{
{ "1." ,
{
{ & ANONYM18 , null , { 0 , 0 } , { 0 , 0 } , NoColor }
}
}
,{ "2." ,
{
{ & ANONYM19 , null , { 0 , 0 } , { 0 , 0 } , NoColor }
}
}
,{ "3." ,
{
{ & ANONYM20 , null , { 0 , 0 } , { 0 , 0 } , NoColor }
}
}
}
, & fmt_list2 , 5 , 5 } ;

Text ANONYM18 = {
{
{ "Metaphysics" , null , null }
,{ "of" , null , null }
,{ "the" , null , null }
,{ "programming." , null , null }
}
, & fmt_list2 , & ANONYM21 } ;

Text ANONYM19 = {
{
{ "Taxonomy" , null , null }
,{ "of" , null , null }
,{ "classes." , null , null }
}
, & fmt_list2 , & ANONYM22 } ;

Text ANONYM20 = {
{
{ "CCore" , null , null }
,{ "general." , null , null }
}
, & fmt_list2 , & ANONYM23 } ;

OneLine ANONYM21 = { 0 } ;

OneLine ANONYM22 = { 0 } ;

OneLine ANONYM23 = { 0 } ;

}

Font font_text = { "Bookman Old Style" , 20 , False , False , 0 } ;

Font font_h1 = { "Bookman Old Style" , 40 , True , False , 0 } ;

Format fmt_h1 = { & font_h1 , 0A9A9A9h , 0FFh , 0 } ;

OneLine align_h1 = { 2 } ;

Font font_h2 = { "Bookman Old Style" , 30 , False , False , 0 } ;

Format fmt_h2 = { & font_h2 , 0F5DEB3h , 06400h , 0 } ;

OneLine align_h2 = { 0 } ;

Font font_bold = { "Bookman Old Style" , 20 , True , False , 0 } ;

Format fmt_bold = { & font_bold , NoColor , NoColor , 0 } ;

Font font_italic = { "Bookman Old Style" , 20 , False , True , 0 } ;

Format fmt_italic = { & font_italic , NoColor , NoColor , 0 } ;

Format fmt_ext = { & font_text , NoColor , 0FFh , 1 } ;

Format fmt_red = { & font_text , NoColor , 0FF0000h , 0 } ;

include <page_Introduction.bookinc.ddl>

}


}

