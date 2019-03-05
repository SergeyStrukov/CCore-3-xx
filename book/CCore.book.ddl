include <pretext:/Book1.ddl>

Book Data = { .title = "CCore 3-xx" , .start = & #Doc#Content#cover , .back = 0FFEFD5h , .fore = 00h } ;

scope Doc {

scope Content {

Point DefaultInner = { 10 , 10 } ;

Format DefaultFormat = { & font_text , NoColor , NoColor , 0 } ;

MultiLine DefaultPlacement = { { 1 , 1 } , { 2 , 1 } } ;

Font font_text = { "Bookman Old Style" , 20 , False , False , 0 } ;

Format fmt_text = { & font_text , NoColor , NoColor , 0 } ;

Font font_title = { "Bookman Old Style" , 80 , False , False , 0 } ;

Format fmt_title = { & font_title , NoColor , NoColor , 0 } ;

Font font_h1 = { "Bookman Old Style" , 32 , False , False , 0 } ;

Format fmt_h1 = { & font_h1 , NoColor , 0FFh , 0 } ;

Font font_list = { "Bookman Old Style" , 20 , False , False , 0 } ;

Font font_list2 = { "Bookman Old Style" , 18 , False , False , 0 } ;

Page cover = { "Cover" ,
{
{ & ANONYM1 , null , { 50 , 50 } , DefaultOuter , NoColor }
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

Page content = { "Content" ,
{
{ & ANONYM11 , null , { 10 , 30 } , DefaultOuter , NoColor }
,{ & List#list , null , DefaultInner , DefaultOuter , NoColor }
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

scope List {

Point DefaultInner = { 0 , 0 } ;

Coord DefaultBulletSpace = 10 ;

Coord DefaultItemSpace = 10 ;

Format DefaultCollapseFormat = { & font_list , NoColor , NoColor , 0 } ;

Format DefaultBulletFormat = { & font_list , NoColor , NoColor , 0 } ;

Format DefaultFormat = { & font_list , NoColor , NoColor , 0 } ;

OneLine DefaultPlacement = { 0 } ;

TextList list = {
{
{ "1." ,
{
{ & ANONYM13 , null , DefaultInner , DefaultOuter , NoColor }
}
}
,{ "2." ,
{
{ & ANONYM14 , null , DefaultInner , DefaultOuter , NoColor }
}
}
,{ "3." ,
{
{ & ANONYM15 , null , DefaultInner , DefaultOuter , NoColor }
}
}
}
, &DefaultBulletFormat , DefaultBulletSpace , DefaultItemSpace } ;

Text ANONYM13 = {
{
{ "Introduction." , null , null }
}
, &DefaultFormat , &DefaultPlacement } ;

Text ANONYM14 = {
{
{ "Installation." , null , null }
}
, &DefaultFormat , &DefaultPlacement } ;

Collapse ANONYM15 = { "Preliminary considerations" ,
{
{ & List2#list3 , null , DefaultInner , DefaultOuter , NoColor }
}
, &DefaultCollapseFormat , False , False } ;

scope List2 {

Coord DefaultBulletSpace = 5 ;

Coord DefaultItemSpace = 5 ;

Format DefaultBulletFormat = { & font_list2 , NoColor , NoColor , 0 } ;

Format DefaultFormat = { & font_list2 , NoColor , NoColor , 0 } ;

TextList list3 = {
{
{ "1." ,
{
{ & ANONYM16 , null , DefaultInner , DefaultOuter , NoColor }
}
}
,{ "2." ,
{
{ & ANONYM17 , null , DefaultInner , DefaultOuter , NoColor }
}
}
,{ "3." ,
{
{ & ANONYM18 , null , DefaultInner , DefaultOuter , NoColor }
}
}
}
, &DefaultBulletFormat , DefaultBulletSpace , DefaultItemSpace } ;

Text ANONYM16 = {
{
{ "Metaphysics" , null , null }
,{ "of" , null , null }
,{ "the" , null , null }
,{ "programming." , null , null }
}
, &DefaultFormat , &DefaultPlacement } ;

Text ANONYM17 = {
{
{ "Taxonomy" , null , null }
,{ "of" , null , null }
,{ "classes." , null , null }
}
, &DefaultFormat , &DefaultPlacement } ;

Text ANONYM18 = {
{
{ "CCore" , null , null }
,{ "general." , null , null }
}
, &DefaultFormat , &DefaultPlacement } ;

}

}

}

scope Pages {

include <page_Introduction.bookinc.ddl>

}


}

