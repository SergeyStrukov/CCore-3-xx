include <pretext:/Book1.ddl>

Book Data = { .title = "ContourLab manual" , .start = & #Doc#Pages#page1 , .back = 0C0C0C0h , .fore = 00h } ;

scope Doc {

scope Pages {

MultiLine DefaultPlacement = { { 12 , 10 } , { 2 , 1 } } ;

Font font_h1 = { "Bookman Old Style" , 60 , True , False , 0 } ;

Font font_h2 = { "Bookman Old Style" , 30 , False , False , 0 } ;

Font font = { "Cambria" , 22 , False , False , 15 } ;

Font font_bold = { "Cambria" , 22 , True , False , 15 } ;

Format fmt_h1 = { & font_h1 , NoColor , 0FFh , 0 } ;

Format fmt_h2 = { & font_h2 , NoColor , 06400h , 0 } ;

Format fmt = { & font , NoColor , 00h , 0 } ;

Format fmt_bold = { & font_bold , NoColor , 00h , 0 } ;

OneLine pl_h1 = { 2 } ;

OneLine pl_h2 = { 2 } ;

Page page1 = { "Introduction" ,
{
{ & ANONYM1 , null , DefaultInner , { 30 , 30 } , NoColor }
,{ & ANONYM2 , null , DefaultInner , { 20 , 20 } , NoColor }
,{ & ANONYM3 , null , DefaultInner , DefaultOuter , NoColor }
}
, NoColor , NoColor , null , null , null } ;

Text ANONYM1 = {
{
{ "ContourLab" , null , null }
,{ "manual" , null , null }
}
, & fmt_h1 , & pl_h1 } ;

Text ANONYM2 = {
{
{ "1." , null , null }
,{ "Introduction." , null , null }
}
, & fmt_h2 , & pl_h2 } ;

Text ANONYM3 = {
{
{ "ContourLab" , & fmt_bold , null }
,{ "is" , null , null }
,{ "a" , null , null }
,{ "tool" , null , null }
,{ "for" , null , null }
,{ "geometrical" , null , null }
,{ "drawing." , null , null }
}
, & fmt , &DefaultPlacement } ;

}


}

